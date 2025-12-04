#pragma once

#include <qcommon/msg_mp.h>

enum pmoveVehAnimState_t : __int32
{                                                                             // XREF: pmove_t/r
                                                                                // ?G_VehicleFinishedAnimating@@YAXPAUgentity_s@@W4pmoveVehAnimState_t@@@Z/r
        PMOVE_VEH_ANIM_STATE_PLAYING     = 0x0,
        PMOVE_VEH_ANIM_STATE_END_STAGE = 0x1,
        PMOVE_VEH_ANIM_STATE_COMPLETE    = 0x2,
};

struct pmove_t // sizeof=0x910
{                                                                             // XREF: .data:pmove_t * g_pmove/r
                                                                                // UIViewer/r ...
        struct playerState_s *ps;
        usercmd_s cmd;                                            // XREF: PlayerCmd_Revive(scr_entref_t)+149/o
                                                                                // PlayerCmd_Revive(scr_entref_t)+18D/o
        usercmd_s oldcmd;
        int tracemask;
        int numtouch;
        int touchents[32];
        int numGlassTouch;
        int touchGlasses[32];
        float mins[3];
        float maxs[3];
        float xyspeed;
        float currentPitch;
        float averagePitch;
        int nextPitch;
        float pitchHistory[30];
        int proneChange;
        float maxSprintTimeMultiplier;
        bool mantleStarted;
        // padding byte
        // padding byte
        // padding byte
        float mantleEndPos[3];
        int mantleDuration;
        int viewChangeTime;
        float viewChange;
        float vehicleAngles[3];
        pmoveVehAnimState_t vehAnimState;
        unsigned __int8 handler;
        // padding byte
        // padding byte
        // padding byte
        int localClientNum;
        const struct gjkcc_input_t *m_gjkcc_input;
        colgeom_visitor_inlined_t<200> proximity_data;
                                                                                // XREF: PlayerCmd_Revive(scr_entref_t)+25C/w
                                                                                // G_ShutdownGame(int)+18/o ...
};

struct pmoveHandler_t // sizeof=0x20
{                                       // XREF: .data:pmoveHandler_t * pmoveHandlers/r
    void (__cdecl *trace)(struct trace_t *, const float *, const float *, const float *, const float *, int, int, struct col_context_t *);
    void (__cdecl *playerEvent)(int, int);
    bool (__cdecl *getEntityOriginAngles)(int, int, float *, float *);
    unsigned __int16 (__cdecl *getVehicleTypeString)(int, int);
    void (__cdecl *entityLinkFromPMove)(unsigned int, int, int);
    int (__cdecl *getPlayerWeapon)(const struct playerState_s *, const int);
    void (__cdecl *setVehDriverInputs)(const int, const int, struct usercmd_s *);
    bool (__cdecl *isEntWalkable)(int, int);
};


// duplicate prototypes
void __cdecl CG_TraceCapsule(
    struct trace_t *results,
    const float *start,
    const float *mins,
    const float *maxs,
    const float *end,
    int passEntityNum,
    int contentMask,
    struct col_context_t *context);
bool __cdecl CG_GetEntityOriginAngles(int localClientNum, int entityNum, float *origin, float *angles);
unsigned __int16 __cdecl CG_GetVehicleTypeString(int clientNum, int entityNum);
int __cdecl CG_GetPlayerWeapon(const struct playerState_s *ps, int localClientNum);
void __cdecl CG_SetVehDriverInputs(int localClientNum, int vehEntNum, struct usercmd_s *cmd);
bool __cdecl CG_IsEntWalkable(int localClientNum, int entityNum);

void __cdecl G_TraceCapsule(
    struct trace_t *results,
    const float *start,
    const float *mins,
    const float *maxs,
    const float *end,
    int passEntityNum,
    int contentmask,
    struct col_context_t *context);
void __cdecl G_PlayerEvent(int clientNum, int event);
bool __cdecl G_GetEntityOriginAngles(int localClientNum, int entityNum, float *origin, float *angles);
unsigned __int16 __cdecl G_GetVehicleTypeString(int clientNum, int entityNum);
void __cdecl G_EntityLinkFromPMove(unsigned int entityNum, int parentEntityNum, int tagName);
int __cdecl G_GetPlayerWeapon(const struct playerState_s *ps, int localClientNum);
void __cdecl G_SetVehDriverInputs(int localClientNum, int vehEntNum, usercmd_s *cmd);
bool __cdecl G_IsEntWalkable(int localClientNum, int entityNum);

static const pmoveHandler_t pmoveHandlers[2] =
{
  {
    CG_TraceCapsule,
    NULL,
    CG_GetEntityOriginAngles,
    CG_GetVehicleTypeString,
    NULL,
    CG_GetPlayerWeapon,
    CG_SetVehDriverInputs,
    CG_IsEntWalkable
  },
  {
    G_TraceCapsule,
    G_PlayerEvent,
    G_GetEntityOriginAngles,
    G_GetVehicleTypeString,
    G_EntityLinkFromPMove,
    G_GetPlayerWeapon,
    G_SetVehDriverInputs,
    G_IsEntWalkable
  }
};