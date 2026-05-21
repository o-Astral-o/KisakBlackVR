#pragma once

// -----------------------------------------------------------------------
//  vr_main.h  –  KisakBlack OpenVR integration
//
//  Phase 1: HMD head-tracking applied to refdef camera.
//  Phase 2: Frame submission to SteamVR compositor via D3D11 interop.
//  Phase 3: True stereo – scene rendered twice (L+R) with per-eye IPD
//            offset and per-eye asymmetric projection matrix.
// -----------------------------------------------------------------------

struct refdef_s;
struct IDirect3DDevice9;
struct GfxViewParms;

// ---- Lifecycle ---------------------------------------------------------

// Initialise OpenVR + D3D11 interop.  Call once after dx.device exists.
// Returns true on success; sets g_vrEnabled accordingly.
bool VR_Init();

// Shut down OpenVR.  Call on quit / device loss.
void VR_Shutdown();

// Returns true when VR was successfully initialised.
bool VR_IsEnabled();

// ---- Per-frame hooks ---------------------------------------------------

// Phase 1: Apply HMD orientation + position to refdef (center/cyclopean).
// Call at the END of CG_CalcViewValues.
void VR_ApplyHMDPoseToRefdef(refdef_s* refdef);

void VR_ApplyFovToRefdef(refdef_s* refdef);

// Phase 3: Replace the single CL_RenderScene call with a two-pass stereo
// render.  Internally calls renderFn twice — once per eye — with the
// correct per-eye camera and projection applied to a copy of *refdef*.
// Each eye renders into its own D3D9 render target.
// renderFn signature matches CL_RenderScene / R_RenderScene.
using VR_RenderFn = void(*)(refdef_s*, int);
void VR_RenderStereoScene(refdef_s* refdef, int frameTime, VR_RenderFn renderFn);

// Phase 3c: Inject the asymmetric per-eye projection center offset into the
// freshly-built GfxViewParms after InfinitePerspectiveMatrix runs.
// Call from R_SetViewParmsForScene after R_SetupViewProjectionMatrices.
void VR_OverrideViewParmProjection(GfxViewParms* viewParms);

// Input overlay: write HMD yaw+pitch (CoD angles, degrees) into *pitch / *yaw.
bool VR_GetHMDViewAngles(float* pitch, float* yaw);

// Returns the frame-to-frame change in HMD pitch/yaw (CoD degrees).
// Add this to viewangles each frame so mouse/gamepad input accumulates on
// top of HMD head rotation.  Returns false on the first valid frame or
// when no pose is available.
bool VR_GetHMDAngleDelta(float* deltaPitch, float* deltaYaw);

// Phase 3b: Capture one eye's rendered scene into its per-eye staging buffer.
// Call from RB_StandardDrawCommandsCommon after each viewInfo renders.
void VR_CaptureEye(int eyeIndex, IDirect3DDevice9* device);

// Phase 2: Submit the two pre-rendered eye RTs to the SteamVR compositor.
// Call in RB_SwapBuffers BEFORE Present().
void VR_SubmitFrame(IDirect3DDevice9* device);
