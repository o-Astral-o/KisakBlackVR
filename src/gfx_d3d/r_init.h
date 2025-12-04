#pragma once
#include <Windows.h>
#include <d3d9.h>

struct GfxGlobals // sizeof=0x24
{                                       // XREF: .data:GfxGlobals r_glob/r
    bool startedRenderThread;           // XREF: R_ShutdownInternal(int)+32/w
                                        // R_BeginRegistration(vidConfig_t *)+5A/r ...
    bool isMultiplayer;                 // XREF: R_SetIsMultiplayer(bool)+6/w
                                        // R_RegisterDvars(void)+4A5D/r ...
    // padding byte
    // padding byte
    volatile int endFrameFence;
    bool isRenderingRemoteUpdate;       // XREF: R_InitThreads(void)+3/r
                                        // R_ReleaseLostDeviceAssets2(void)+6C/r ...
    // padding byte
    // padding byte
    // padding byte
    volatile int screenUpdateNotify;    // XREF: R_BeginRemoteScreenUpdate(void):loc_A7D848/r
                                        // R_EndRemoteScreenUpdate(void (*)(void)):loc_A7D9E8/r ...
    volatile int remoteScreenUpdateNesting; // XREF: DB_Sleep:loc_58F143/r
                                        // R_SyncRenderThread(void):loc_A7A1B6/r ...
    volatile int remoteScreenUpdateInGame;
                                        // XREF: R_BeginRemoteScreenUpdate(void)+85/r
                                        // R_EndRemoteScreenUpdate(void (*)(void))+B9/r
    unsigned __int8 remoteScreenLastSceneResolveTarget;
                                        // XREF: R_Init(void)+13/w
                                        // R_PerMap_Init(void)+8/w
    // padding byte
    // padding byte
    // padding byte
    int backEndFrameCount;              // XREF: RB_DrawCoronaQuerySprite+53/r
                                        // RB_BeginFrame(void const *)+2D/r ...
    unsigned __int8 frameBuffer;
    unsigned __int8 displayBuffer;
    unsigned __int8 ui3dUseFrameBuffer;
    unsigned __int8 ui3dRenderTarget;
};

void __cdecl    R_FatalInitError(const char *msg);
void __cdecl    R_FatalLockError(HRESULT hr);
const char *__cdecl R_ErrorDescription(HRESULT hr);
void __cdecl R_SetColorMappings();
void __cdecl R_CalcGammaRamp(GfxGammaRamp *gammaRamp);
void __cdecl R_MakeDedicated(const GfxConfiguration *config);
void __cdecl SetGfxConfig(const GfxConfiguration *config);
void __cdecl R_ReleaseForShutdownOrReset();
void __cdecl R_UpdateGpuSyncType();
char __cdecl R_CreateDevice(const GfxWindowParms *wndParms);
void __cdecl R_SetD3DPresentParameters(_D3DPRESENT_PARAMETERS_ *d3dpp, const GfxWindowParms *wndParms);
void __cdecl R_SetupAntiAliasing(const GfxWindowParms *wndParms);
HRESULT __cdecl R_CreateDeviceInternal(HWND__ *hwnd, unsigned int behavior, _D3DPRESENT_PARAMETERS_ *d3dpp);
bool __cdecl R_GetMonitorDimensions(int *width, int *height);
int __cdecl R_GetDeviceType();
void __cdecl R_CheckResizeWindow();
void __cdecl R_ResizeWindow();
void __cdecl R_StoreWindowSettings(const GfxWindowParms *wndParms);
void __cdecl R_SetWndParms(GfxWindowParms *wndParms);
const char *__cdecl R_ClosestRefreshRateForMode(unsigned int width, unsigned int height, int refreshRate);
bool __cdecl R_SetCustomResolution(GfxWindowParms *wndParms);
void __cdecl R_AllocateMinimalResources();
void __cdecl R_SetIsMultiplayer(bool isMp);
void __cdecl R_InitThreads();
void __cdecl R_Init();
void R_InitGraphicsApi();
void R_InitSystems();
char __cdecl R_PreCreateWindow();
void __cdecl R_StoreDirect3DCaps(unsigned int adapterIndex);
void __cdecl R_GetDirect3DCaps(unsigned int adapterIndex, _D3DCAPS9 *caps);
void __cdecl R_PickRenderer(_D3DCAPS9 *caps);
bool __cdecl R_CheckTransparencyMsaa(unsigned int adapterIndex);
void __cdecl R_SetShadowmapFormats_DX(unsigned int adapterIndex);
void __cdecl R_EnumDisplayModes(unsigned int adapterIndex);
int __cdecl R_CompareDisplayModes(unsigned int *e0, unsigned int *e1);
int __cdecl R_AddValidRefreshRate(int refreshRate, int rateCount, int *availableRefreshRates);
int __cdecl R_CompareRefreshRates(unsigned int *e0, unsigned int *e1);
int __cdecl R_AddValidResolution(int width, int height, int resolutionCount, int (*availableResolutions)[2]);
unsigned int __cdecl R_ChooseAdapter();
HMONITOR__ *__cdecl R_ChooseMonitor();
int __stdcall R_MonitorEnumCallback(HMONITOR__ *monitorHandle, HDC__ *hdc, tagRECT *rect, unsigned int *userData);
char __cdecl R_CreateGameWindow(GfxWindowParms *wndParms);
char __cdecl R_InitHardware(const GfxWindowParms *wndParms);
void R_InitGamma();
void __cdecl R_FinishAttachingToWindow(const GfxWindowParms *wndParms);
char __cdecl R_CreateForInitOrReset();
IDirect3DQuery9 *__cdecl RB_HW_AllocOcclusionQuery();
char __cdecl R_CreateWindow(GfxWindowParms *wndParms);
char __cdecl R_ReduceWindowSettings();
void R_Register();
void R_InitGlobalStructs();
void __cdecl R_ShutdownStreams();
void __cdecl R_ShutdownInternal();
int R_ShutdownDirect3D();
int R_ShutdownDirect3DInternal();
void R_UnloadGraphicsAssets();
void __cdecl R_Shutdown(int destroyWindow);
void __cdecl R_UnloadWorld();
void __cdecl R_BeginRegistrationInternal();
void __cdecl R_BeginRegistration(vidConfig_t *vidConfigOut);
void __cdecl R_EndRegistration();
void __cdecl R_TrackStatistics(trStatistics_t *stats);
void __cdecl R_SyncGpu();
void __cdecl R_UpdateTeamColors(const float *color_allies, const float *color_axis);
void __cdecl R_ConfigureRenderer(const GfxConfiguration *config);
char __cdecl R_ReleaseLostDeviceAssets2();
char __cdecl R_RecoverLostDevice();
char __cdecl R_ResetDevice();
void __cdecl R_ComErrorCleanup();
bool __cdecl R_StereoActivated();
