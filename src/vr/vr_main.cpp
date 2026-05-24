// -----------------------------------------------------------------------
//  vr_main.cpp  –  KisakBlack OpenVR integration
//
//  Submission pipeline (fast path – D3D9Ex shared texture, zero CPU copies):
//    For each eye:
//      1.  RB_Draw3DInternal renders scene into game's scene RT.
//      2.  VR_CaptureEye:  StretchRect  scene RT → s_d3d9EyeSharedSurf[eye]
//          (GPU→GPU blit directly into the D3D11-shared surface, no CPU).
//    VR_SubmitFrame:
//      3.  s_d3d11Context->Flush()  (non-blocking).
//      4.  VRCompositor::Submit (Left, Right).
//
//  Slow path (plain D3D9 fallback, pipelined staging):
//    For each eye:
//      1.  RB_Draw3DInternal renders scene.
//      2.  VR_CaptureEye:  StretchRect → eyeRT, GetRenderTargetData →
//          staging[eye][writeIdx]  (one GPU stall per eye, unavoidable).
//    VR_SubmitFrame:
//      3.  Upload staging[eye][readIdx] (previous frame, already in
//          sys-mem – no extra GPU stall) via UpdateSubresource.
//      4.  Flush + Submit.
//      5.  Swap staging ring indices.
//
//  Why D3D9Ex?
//    IDirect3DDevice9Ex::CreateTexture with a DXGI shared handle opens a
//    D3D11 texture as a D3D9 render target.  StretchRect to it is GPU-only,
//    eliminating GetRenderTargetData (stall), LockRect, UpdateSubresource,
//    and the old spin-wait query – all three GPU synchronisation points
//    collapse to a single non-blocking Flush.
//    A device created via IDirect3D9Ex::CreateDevice (which R_PreCreateWindow
//    now prefers) also implements IDirect3DDevice9Ex via QueryInterface.
// -----------------------------------------------------------------------

#include <openvr.h>
#include <d3d9.h>
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include <cgame_mp/cg_local_mp.h>
#include <qcommon/common.h>
#include <gfx_d3d/rb_backend.h>
#include <gfx_d3d/rb_state.h>
#include <gfx_d3d/r_init.h>
#include <gfx_d3d/r_rendercmds.h>
#include <gfx_d3d/r_stream.h>
#include <gfx_d3d/r_gfx.h>
#include <universal/com_math.h>
#include "vr_main.h"

// ---------------------------------------------------------------------------
static constexpr float VR_METRES_TO_UNITS = 39.37f;
static constexpr bool  VR_SWAP_SUBMIT_EYES = false;

static constexpr bool  VR_CENTER_CAMERA_ON_RIGHT_EYE = true;

// ---------------------------------------------------------------------------
// Module state
// ---------------------------------------------------------------------------
static vr::IVRSystem*           s_pVRSystem  = nullptr;
static bool                     s_vrEnabled  = false;
static vr::TrackedDevicePose_t  s_poses[vr::k_unMaxTrackedDeviceCount];
static uint32_t s_eyeWidth  = 0;
static uint32_t s_eyeHeight = 0;

// Per-eye transforms – static for the session, cached once in VR_Init.
static vr::HmdMatrix34_t s_eyeToHead[2];
static float s_eyeTanHalfFovX[2] = {};
static float s_eyeTanHalfFovY[2] = {};
static float s_eyeProjOffsetX[2] = {};
static float s_eyeProjOffsetY[2] = {};

// Current HMD center pose.
static vr::HmdMatrix34_t s_hmdCenter    = {};
static bool              s_hmdPoseValid = false;

// --- Fast path (D3D9Ex, GPU→GPU zero-copy) ---
static IDirect3DDevice9Ex*  s_d3d9ExDevice        = nullptr;
static IDirect3DTexture9*   s_d3d9EyeSharedTex[2] = {};
static IDirect3DSurface9*   s_d3d9EyeSharedSurf[2]= {};

// --- Slow path (pipelined CPU readback) ---
static IDirect3DSurface9*   s_d3d9EyeRT[2]         = {};
static IDirect3DSurface9*   s_d3d9EyeStaging[2][2] = {};
static int                  s_stagingWriteIdx = 0;
static int                  s_stagingReadIdx  = 1;
static bool                 s_stagingPrimed   = false;

// --- D3D11 compositor eye textures ---
static ID3D11Device*        s_d3d11Device  = nullptr;
static ID3D11DeviceContext* s_d3d11Context = nullptr;
static ID3D11Texture2D*     s_eyeTexture[2] = {};

// --- Per-frame stereo state ---
static float s_eyeProjOffsetXCur[2] = {};
static float s_eyeProjOffsetYCur[2] = {};
static int   s_currentRenderEye     = -1;
static int   s_submitEye            = -1;
static bool  s_stereoRendered       = false;
static bool  s_eyeCaptured[2]       = {};

// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------
static void VR_ReleaseD3DResources();
static bool VR_CreateD3DResources(IDirect3DDevice9* dev);
static bool VR_UploadEyeToD3D11(int eye);

// ---------------------------------------------------------------------------
// Coordinate helpers
// ---------------------------------------------------------------------------
static inline void OVRVecToCoD(float a, float b, float c,
                                float& x, float& y, float& z)
{ x = -c; y = -a; z = b; }

static void OVRMatrixToCoD(const vr::HmdMatrix34_t& m,
                            float outAxis[3][3], float outPos[3])
{
    OVRVecToCoD(-m.m[0][2],-m.m[1][2],-m.m[2][2], outAxis[0][0],outAxis[0][1],outAxis[0][2]);
    OVRVecToCoD(-m.m[0][0],-m.m[1][0],-m.m[2][0], outAxis[1][0],outAxis[1][1],outAxis[1][2]);
    OVRVecToCoD( m.m[0][1], m.m[1][1], m.m[2][1], outAxis[2][0],outAxis[2][1],outAxis[2][2]);
    OVRVecToCoD(m.m[0][3], m.m[1][3], m.m[2][3], outPos[0], outPos[1], outPos[2]);
    outPos[0] *= VR_METRES_TO_UNITS;
    outPos[1] *= VR_METRES_TO_UNITS;
    outPos[2] *= VR_METRES_TO_UNITS;
}

static vr::HmdMatrix34_t OVRMul34(const vr::HmdMatrix34_t& a, const vr::HmdMatrix34_t& b)
{
    vr::HmdMatrix34_t r = {};
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 4; ++col)
        {
            r.m[row][col] = a.m[row][0]*b.m[0][col] + a.m[row][1]*b.m[1][col] + a.m[row][2]*b.m[2][col];
            if (col == 3) r.m[row][col] += a.m[row][3];
        }
    return r;
}

// ---------------------------------------------------------------------------
// Cache per-eye FOV + asymmetric projection offsets (constant for the session).
// Called once in VR_Init.
// ---------------------------------------------------------------------------
static void VR_CacheEyeProjections()
{
    for (int eye = 0; eye < 2; ++eye)
    {
        float l, r, t, b;
        s_pVRSystem->GetProjectionRaw(eye == 0 ? vr::Eye_Left : vr::Eye_Right, &l, &r, &t, &b);

        const float w = r - l;
        const float h = b - t;

        if (w > 0.0f && h > 0.0f)
        {
            s_eyeTanHalfFovX[eye] = w * 0.5f;
            s_eyeTanHalfFovY[eye] = h * 0.5f;
            s_eyeProjOffsetX[eye] = -(r + l) / w;
            s_eyeProjOffsetY[eye] = -(b + t) / h;
        }
        else
        {
            // Fallback from full projection matrix (should never be needed)
            const vr::HmdMatrix44_t P = s_pVRSystem->GetProjectionMatrix(
                eye == 0 ? vr::Eye_Left : vr::Eye_Right, 4.0f, 16384.0f);
            const float fl = (P.m[0][2]-1.0f)/P.m[0][0], fr = (P.m[0][2]+1.0f)/P.m[0][0];
            const float ft = (1.0f-P.m[1][2])/P.m[1][1], fb = (-1.0f-P.m[1][2])/P.m[1][1];
            const float fw = fr-fl, fh = ft-fb;
            s_eyeTanHalfFovX[eye] = fabsf(fw)*0.5f;
            s_eyeTanHalfFovY[eye] = fabsf(fh)*0.5f;
            s_eyeProjOffsetX[eye] = fw!=0.0f ? -(fr+fl)/fw : 0.0f;
            s_eyeProjOffsetY[eye] = fh!=0.0f ? -(ft+fb)/fh : 0.0f;
        }
    }
}

// ---------------------------------------------------------------------------
bool VR_Init()
{
    if (s_vrEnabled) return true;

    vr::EVRInitError err = vr::VRInitError_None;
    s_pVRSystem = vr::VR_Init(&err, vr::VRApplication_Scene);
    if (!s_pVRSystem || err != vr::VRInitError_None)
    {
        Com_Printf(8, "[VR] VR_Init failed: %s\n", vr::VR_GetVRInitErrorAsEnglishDescription(err));
        s_pVRSystem = nullptr; return false;
    }
    if (!vr::VRCompositor())
    {
        Com_Printf(8, "[VR] VRCompositor not available.\n");
        vr::VR_Shutdown(); s_pVRSystem = nullptr; return false;
    }

    s_pVRSystem->GetRecommendedRenderTargetSize(&s_eyeWidth, &s_eyeHeight);
    Com_Printf(8, "[VR] Recommended eye resolution: %u x %u\n", s_eyeWidth, s_eyeHeight);

    for (int eye = 0; eye < 2; ++eye)
        s_eyeToHead[eye] = s_pVRSystem->GetEyeToHeadTransform(
            eye == 0 ? vr::Eye_Left : vr::Eye_Right);

    VR_CacheEyeProjections();
    Com_Printf(8, "[VR] Eye L: tanHalfFov=(%f,%f) projOffset=(%f,%f)\n",
        s_eyeTanHalfFovX[0],s_eyeTanHalfFovY[0],s_eyeProjOffsetX[0],s_eyeProjOffsetY[0]);
    Com_Printf(8, "[VR] Eye R: tanHalfFov=(%f,%f) projOffset=(%f,%f)\n",
        s_eyeTanHalfFovX[1],s_eyeTanHalfFovY[1],s_eyeProjOffsetX[1],s_eyeProjOffsetY[1]);

    // D3D11 device on the same adapter SteamVR is using.
    {
        const int adapterIdx = vr::VRSystem()->GetD3D9AdapterIndex();
        IDXGIFactory1* factory = nullptr;
        CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
        IDXGIAdapter* adapter = nullptr;
        if (factory && adapterIdx >= 0)
            factory->EnumAdapters((UINT)adapterIdx, &adapter);

        const D3D_FEATURE_LEVEL fl = D3D_FEATURE_LEVEL_11_0;
        D3D_FEATURE_LEVEL actualFL = {};
        HRESULT hr = D3D11CreateDevice(
            adapter,
            adapter ? D3D_DRIVER_TYPE_UNKNOWN : D3D_DRIVER_TYPE_HARDWARE,
            nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            &fl, 1, D3D11_SDK_VERSION,
            &s_d3d11Device, &actualFL, &s_d3d11Context);

        if (adapter) adapter->Release();
        if (factory) factory->Release();

        if (FAILED(hr))
        {
            Com_Printf(8, "[VR] D3D11CreateDevice failed: 0x%08X\n", (unsigned)hr);
            vr::VR_Shutdown(); s_pVRSystem = nullptr; return false;
        }
        Com_Printf(8, "[VR] D3D11 device OK.\n");
    }

    s_vrEnabled = true;
    return true;
}

// ---------------------------------------------------------------------------
static bool VR_CreateD3DResources(IDirect3DDevice9* dev)
{
    // Try to get IDirect3DDevice9Ex via QI.
    // Succeeds when dx.d3d9 was created via Direct3DCreate9Ex (WDDM, Vista+).
    {
        IDirect3DDevice9Ex* devEx = nullptr;
        if (SUCCEEDED(dev->QueryInterface(__uuidof(IDirect3DDevice9Ex), (void**)&devEx)) && devEx)
        {
            devEx->Release(); // release QI ref – borrow dx.device's ref
            s_d3d9ExDevice = devEx;
            Com_Printf(8, "[VR] IDirect3DDevice9Ex available – trying zero-copy path.\n");
        }
    }

    for (int eye = 0; eye < 2; ++eye)
    {
        // D3D11 shared eye texture (submitted to SteamVR compositor).
        // D3D11_BIND_RENDER_TARGET is required for D3D9Ex sharing to work.
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = s_eyeWidth; desc.Height = s_eyeHeight;
        desc.MipLevels = 1; desc.ArraySize = 1;
        desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        desc.MiscFlags = D3D11_RESOURCE_MISC_SHARED;

        HRESULT hr = s_d3d11Device->CreateTexture2D(&desc, nullptr, &s_eyeTexture[eye]);
        if (FAILED(hr)) { Com_Printf(8,"[VR] CreateTexture2D eye%d failed: 0x%08X\n",eye,(unsigned)hr); return false; }

        if (s_d3d9ExDevice)
        {
            IDXGIResource* dxgiRes = nullptr;
            s_eyeTexture[eye]->QueryInterface(__uuidof(IDXGIResource), (void**)&dxgiRes);
            HANDLE sharedHandle = nullptr;
            if (dxgiRes) { dxgiRes->GetSharedHandle(&sharedHandle); dxgiRes->Release(); }

            if (sharedHandle)
            {
                hr = s_d3d9ExDevice->CreateTexture(
                    s_eyeWidth, s_eyeHeight, 1,
                    D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8,
                    D3DPOOL_DEFAULT, &s_d3d9EyeSharedTex[eye], &sharedHandle);
                if (SUCCEEDED(hr) && s_d3d9EyeSharedTex[eye])
                {
                    s_d3d9EyeSharedTex[eye]->GetSurfaceLevel(0, &s_d3d9EyeSharedSurf[eye]);
                    Com_Printf(8, "[VR] Eye%d: D3D9Ex shared surface OK.\n", eye);
                    continue;
                }
                Com_Printf(8, "[VR] Eye%d: shared CreateTexture failed 0x%08X – falling back.\n", eye, (unsigned)hr);
            }
            s_d3d9ExDevice = nullptr; // fast path failed; disable for all eyes
        }

        // Slow path resources.
        hr = dev->CreateRenderTarget(s_eyeWidth, s_eyeHeight,
            D3DFMT_A8R8G8B8, D3DMULTISAMPLE_NONE, 0, FALSE, &s_d3d9EyeRT[eye], nullptr);
        if (FAILED(hr)) { Com_Printf(8,"[VR] CreateRT eye%d failed: 0x%08X\n",eye,(unsigned)hr); return false; }

        for (int b = 0; b < 2; ++b)
        {
            hr = dev->CreateOffscreenPlainSurface(s_eyeWidth, s_eyeHeight, D3DFMT_A8R8G8B8,
                D3DPOOL_SYSTEMMEM, &s_d3d9EyeStaging[eye][b], nullptr);
            if (FAILED(hr)) { Com_Printf(8,"[VR] CreateStaging eye%d buf%d failed: 0x%08X\n",eye,b,(unsigned)hr); return false; }
        }
    }

    const bool fastPath = s_d3d9EyeSharedSurf[0] && s_d3d9EyeSharedSurf[1];
    if (!fastPath) s_d3d9ExDevice = nullptr;

    Com_Printf(8, "[VR] D3D resources ready (%u x %u per eye, %s).\n",
        s_eyeWidth, s_eyeHeight,
        fastPath ? "D3D9Ex ZERO-COPY fast path" : "pipelined CPU readback (slow path)");
    return true;
}

// ---------------------------------------------------------------------------
static void VR_ReleaseD3DResources()
{
    for (int i = 0; i < 2; ++i)
    {
        if (s_d3d9EyeSharedSurf[i]) { s_d3d9EyeSharedSurf[i]->Release(); s_d3d9EyeSharedSurf[i]=nullptr; }
        if (s_d3d9EyeSharedTex[i])  { s_d3d9EyeSharedTex[i]->Release();  s_d3d9EyeSharedTex[i] =nullptr; }
        if (s_d3d9EyeRT[i])         { s_d3d9EyeRT[i]->Release();         s_d3d9EyeRT[i]         =nullptr; }
        for (int b = 0; b < 2; ++b)
            if (s_d3d9EyeStaging[i][b]) { s_d3d9EyeStaging[i][b]->Release(); s_d3d9EyeStaging[i][b]=nullptr; }
        if (s_eyeTexture[i]) { s_eyeTexture[i]->Release(); s_eyeTexture[i]=nullptr; }
    }
    if (s_d3d11Context) { s_d3d11Context->Release(); s_d3d11Context=nullptr; }
    if (s_d3d11Device)  { s_d3d11Device->Release();  s_d3d11Device =nullptr; }
    s_d3d9ExDevice = nullptr;
    s_stagingPrimed = false;
}

// ---------------------------------------------------------------------------
static bool VR_UploadEyeToD3D11(int eye)
{
    IDirect3DSurface9* surf = s_d3d9EyeStaging[eye][s_stagingReadIdx];
    if (!surf) return false;

    D3DLOCKED_RECT lr = {};
    // DONOTWAIT: should always succeed (staging[read] was written last frame).
    HRESULT hr = surf->LockRect(&lr, nullptr, D3DLOCK_READONLY | D3DLOCK_DONOTWAIT);
    if (FAILED(hr)) hr = surf->LockRect(&lr, nullptr, D3DLOCK_READONLY);
    if (FAILED(hr)) { Com_Printf(8,"[VR] UploadEye(%d): LockRect failed 0x%08X\n",eye,(unsigned)hr); return false; }

    s_d3d11Context->UpdateSubresource(s_eyeTexture[eye], 0, nullptr, lr.pBits, (UINT)lr.Pitch, 0);
    surf->UnlockRect();
    return true;
}

// ---------------------------------------------------------------------------
void VR_Shutdown()
{
    if (!s_vrEnabled) return;
    VR_ReleaseD3DResources();
    vr::VR_Shutdown();
    s_pVRSystem = nullptr;
    s_vrEnabled  = false;
    Com_Printf(8, "[VR] Shutdown.\n");
}

bool VR_IsEnabled() { return s_vrEnabled; }

// ---------------------------------------------------------------------------
// HMD angle helpers
// ---------------------------------------------------------------------------
static float s_prevHmdPitch = 0.0f, s_prevHmdYaw = 0.0f;
static bool  s_hmdAnglesInitialized = false;

static inline float VR_AngleNorm180(float a)
{
    a = fmodf(a, 360.0f);
    if (a >  180.0f) a -= 360.0f;
    if (a < -180.0f) a += 360.0f;
    return a;
}

static bool VR_ComputeHMDAngles(float& outPitch, float& outYaw)
{
    if (!s_vrEnabled || !s_hmdPoseValid) return false;
    float axis[3][3], pos[3];
    OVRMatrixToCoD(s_hmdCenter, axis, pos);
    const float fX = axis[0][0], fY = axis[0][1], fZ = axis[0][2];
    const float xyLen = sqrtf(fX*fX + fY*fY);
    const float R2D = 180.0f / 3.14159265358979f;
    outYaw   =  atan2f(fY, fX) * R2D;
    outPitch = -(atan2f(fZ, xyLen) * R2D);
    return true;
}

bool VR_GetHMDViewAngles(float* pitch, float* yaw)
{
    if (!pitch || !yaw) return false;
    return VR_ComputeHMDAngles(*pitch, *yaw);
}

bool VR_GetHMDAngleDelta(float* deltaPitch, float* deltaYaw)
{
    if (!deltaPitch || !deltaYaw) return false;
    float cp, cy;
    if (!VR_ComputeHMDAngles(cp, cy)) { s_hmdAnglesInitialized = false; return false; }
    if (!s_hmdAnglesInitialized)
    {
        s_prevHmdPitch = cp; s_prevHmdYaw = cy;
        s_hmdAnglesInitialized = true;
        *deltaPitch = 0.0f; *deltaYaw = 0.0f;
        return false;
    }
    *deltaPitch = VR_AngleNorm180(cp - s_prevHmdPitch);
    *deltaYaw   = VR_AngleNorm180(cy - s_prevHmdYaw);
    s_prevHmdPitch = cp; s_prevHmdYaw = cy;
    return true;
}

// ---------------------------------------------------------------------------
void VR_ApplyHMDPoseToRefdef(refdef_s* refdef)
{
    if (!s_vrEnabled || !s_pVRSystem) return;

    vr::VRCompositor()->WaitGetPoses(s_poses, vr::k_unMaxTrackedDeviceCount, nullptr, 0);

    const vr::TrackedDevicePose_t& hmdPose = s_poses[vr::k_unTrackedDeviceIndex_Hmd];
    if (!hmdPose.bPoseIsValid) { s_hmdPoseValid = false; return; }

    s_hmdCenter    = hmdPose.mDeviceToAbsoluteTracking;
    s_hmdPoseValid = true;
    s_stereoRendered = false;

    (void)refdef; // camera driven by player input only
}

// ---------------------------------------------------------------------------
int VR_GetCurrentSubmitEye() { return s_submitEye; }

// ---------------------------------------------------------------------------
void VR_RenderStereoScene(refdef_s* refdef, int frameTime, VR_RenderFn renderFn)
{
    if (!s_vrEnabled || !s_pVRSystem || !refdef || !renderFn) { renderFn(refdef, frameTime); return; }
    if (!s_hmdPoseValid) { renderFn(refdef, frameTime); return; }

    if (!s_d3d9EyeRT[0] && !s_d3d9EyeSharedSurf[0])
    {
        if (!VR_CreateD3DResources(dx.device))
        {
            Com_Printf(8, "[VR] D3D resource creation failed – disabling VR.\n");
            s_vrEnabled = false; renderFn(refdef, frameTime); return;
        }
    }

    s_eyeCaptured[0] = s_eyeCaptured[1] = false;

    float centerAxis[3][3], centerPos[3];
    OVRMatrixToCoD(s_hmdCenter, centerAxis, centerPos);
    
    const int centerEye = VR_CENTER_CAMERA_ON_RIGHT_EYE ? 1 : 0;
    vr::HmdMatrix34_t centerEyeWorld = OVRMul34(s_hmdCenter, s_eyeToHead[centerEye]);
    float centerEyeAxis[3][3], centerEyePos[3];
    OVRMatrixToCoD(centerEyeWorld, centerEyeAxis, centerEyePos);

    const float centerEyeX = centerEyePos[0]-centerPos[0];
    const float centerEyeY = centerEyePos[1]-centerPos[1];
    const float centerEyeZ = centerEyePos[2]-centerPos[2];
    const float centerEyeIpdDist = centerEyeX*centerAxis[1][0] + centerEyeY*centerAxis[1][1] + centerEyeZ*centerAxis[1][2];

    for (int eye = 0; eye < 2; ++eye)
    {
        refdef_s eyeRefdef = *refdef;

        // IPD offset along player lateral axis.
        vr::HmdMatrix34_t eyeWorld = OVRMul34(s_hmdCenter, s_eyeToHead[eye]);
        float eyeAxis[3][3], eyePos[3];
        OVRMatrixToCoD(eyeWorld, eyeAxis, eyePos);

        const float ipdX = eyePos[0]-centerPos[0], ipdY = eyePos[1]-centerPos[1], ipdZ = eyePos[2]-centerPos[2];
        const float ipdDist = (ipdX*centerAxis[1][0] + ipdY*centerAxis[1][1] + ipdZ*centerAxis[1][2]) - centerEyeIpdDist;

        for (int i = 0; i < 3; ++i)
        {
            eyeRefdef.viewaxis[0][i] = refdef->viewaxis[0][i];
            eyeRefdef.viewaxis[1][i] = refdef->viewaxis[1][i];
            eyeRefdef.viewaxis[2][i] = refdef->viewaxis[2][i];
        }
        eyeRefdef.vieworg[0] = refdef->vieworg[0] + refdef->viewaxis[1][0]*ipdDist;
        eyeRefdef.vieworg[1] = refdef->vieworg[1] + refdef->viewaxis[1][1]*ipdDist;
        eyeRefdef.vieworg[2] = refdef->vieworg[2] + refdef->viewaxis[1][2]*ipdDist;

        // Apply pre-cached per-eye FOV (no runtime API calls).
        eyeRefdef.tanHalfFovX = s_eyeTanHalfFovX[eye];
        eyeRefdef.tanHalfFovY = s_eyeTanHalfFovY[eye];
        eyeRefdef.fov_x = 2.0f * atanf(eyeRefdef.tanHalfFovX) * (180.0f / 3.14159265f);
        s_eyeProjOffsetXCur[eye] = s_eyeProjOffsetX[eye];
        s_eyeProjOffsetYCur[eye] = s_eyeProjOffsetY[eye];

        if (eye == 0)
        {
            rg.viewInfoCount = 0;
            if (frontEndDataOut) frontEndDataOut->viewInfoCount = 0;
        }
        streamFrontendGlob.queryClient = -1;

        s_currentRenderEye = eye;
        s_submitEye = eye;
        renderFn(&eyeRefdef, frameTime);
        s_submitEye = -1;
        s_currentRenderEye = -1;
        
        // R_RenderScene updates refdef exposure in-place for auto-exposure.
        // Stereo renders use temporary per-eye copies, so preserve the updated
        // value from the eye that represents the gameplay camera.
        if (eye == centerEye)
        {
            refdef->exposure = eyeRefdef.exposure;
            refdef->exposureValue = eyeRefdef.exposureValue;
        }
    }

    s_stereoRendered = true;
}

// ---------------------------------------------------------------------------
void VR_ApplyFovToRefdef(refdef_s* refdef)
{
    if (!s_vrEnabled || !s_pVRSystem || !refdef) return;
    const float vrFov = 150.0f;
    refdef->fov_x       = vrFov;
    refdef->tanHalfFovX = tanf(vrFov * 0.5f * 0.01745329252f);
    refdef->tanHalfFovY = tanf(vrFov * 0.5f * 0.01745329252f);
}

// ---------------------------------------------------------------------------
void VR_OverrideViewParmProjection(GfxViewParms* viewParms)
{
    if (!s_vrEnabled || s_currentRenderEye < 0 || s_currentRenderEye >= 2 || !viewParms) return;
    const int eye = s_currentRenderEye;
    // GfxMatrix is column-major: m[col][row].
    viewParms->projectionMatrix.m[2][0] = s_eyeProjOffsetXCur[eye];
    viewParms->projectionMatrix.m[2][1] = s_eyeProjOffsetYCur[eye];
    MatrixMultiply44(viewParms->viewMatrix.m, viewParms->projectionMatrix.m, viewParms->viewProjectionMatrix.m);
    MatrixInverse44(viewParms->viewProjectionMatrix.m, viewParms->inverseViewProjectionMatrix.m);
}

// ---------------------------------------------------------------------------
void VR_CaptureEye(int eye, IDirect3DDevice9* device)
{
    if (!s_vrEnabled || eye < 0 || eye >= 2 || !device) return;

    IDirect3DSurface9* sceneSurf = gfxRenderTargets[R_RENDERTARGET_SCENE].surface.color;
    if (!sceneSurf) return;

    // Fast path: GPU→GPU blit, zero CPU involvement.
    if (s_d3d9EyeSharedSurf[eye])
    {
        HRESULT hr = device->StretchRect(sceneSurf, nullptr, s_d3d9EyeSharedSurf[eye], nullptr, D3DTEXF_LINEAR);
        if (SUCCEEDED(hr)) s_eyeCaptured[eye] = true;
        else Com_Printf(8,"[VR] CaptureEye(%d) fast StretchRect failed 0x%08X\n",eye,(unsigned)hr);
        return;
    }

    // Slow path: blit to GPU RT then readback to sys-mem (one GPU stall per eye).
    if (!s_d3d9EyeRT[eye] || !s_d3d9EyeStaging[eye][s_stagingWriteIdx]) return;

    HRESULT hr = device->StretchRect(sceneSurf, nullptr, s_d3d9EyeRT[eye], nullptr, D3DTEXF_LINEAR);
    if (FAILED(hr)) { Com_Printf(8,"[VR] CaptureEye(%d) StretchRect failed 0x%08X\n",eye,(unsigned)hr); return; }

    hr = device->GetRenderTargetData(s_d3d9EyeRT[eye], s_d3d9EyeStaging[eye][s_stagingWriteIdx]);
    if (FAILED(hr)) { Com_Printf(8,"[VR] CaptureEye(%d) GetRenderTargetData failed 0x%08X\n",eye,(unsigned)hr); return; }

    s_eyeCaptured[eye] = true;
}

// ---------------------------------------------------------------------------
void VR_SubmitFrame(IDirect3DDevice9* device)
{
    if (!s_vrEnabled || !s_pVRSystem || !device) return;

    const bool hasFast = s_d3d9EyeSharedSurf[0] != nullptr;
    const bool hasSlow = s_d3d9EyeRT[0] != nullptr;
    if (!hasFast && !hasSlow) return;

    if (hasFast)
    {
        // All StretchRect work is already on the GPU; non-blocking flush
        // ensures the driver queue is committed before the compositor reads.
        s_d3d11Context->Flush();
    }
    else
    {
        // Upload previous frame's data (already in sys-mem, no GPU stall).
        if (s_stagingPrimed)
            for (int eye = 0; eye < 2; ++eye)
                VR_UploadEyeToD3D11(eye);

        // Non-blocking flush: gets UpdateSubresource into the driver queue.
        s_d3d11Context->Flush();

        // Advance the staging ring.
        const int tmp   = s_stagingWriteIdx;
        s_stagingWriteIdx = s_stagingReadIdx;
        s_stagingReadIdx  = tmp;
        s_stagingPrimed   = true;
    }

    const int lIdx = VR_SWAP_SUBMIT_EYES ? 1 : 0;
    const int rIdx = VR_SWAP_SUBMIT_EYES ? 0 : 1;

    vr::Texture_t lTex = { s_eyeTexture[lIdx], vr::TextureType_DirectX, vr::ColorSpace_Auto };
    vr::Texture_t rTex = { s_eyeTexture[rIdx], vr::TextureType_DirectX, vr::ColorSpace_Auto };

    vr::EVRCompositorError eL = vr::VRCompositor()->Submit(vr::Eye_Left,  &lTex, nullptr, vr::Submit_Default);
    vr::EVRCompositorError eR = vr::VRCompositor()->Submit(vr::Eye_Right, &rTex, nullptr, vr::Submit_Default);
    if (eL != vr::VRCompositorError_None) Com_Printf(8,"[VR] Submit Left failed: %d\n",(int)eL);
    if (eR != vr::VRCompositorError_None) Com_Printf(8,"[VR] Submit Right failed: %d\n",(int)eR);

    s_stereoRendered = false;
}

int VR_GetCurrentRenderEye() { return s_currentRenderEye; }
