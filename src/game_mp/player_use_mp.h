#pragma once
#include <bgame/bg_public.h>
#include "g_main_mp.h"

struct useList_t // sizeof=0x8
{                                       // XREF: ?Player_UpdateCursorHints@@YAXPAUgentity_s@@@Z/r
    gentity_s *ent;                     // XREF: Player_UpdateCursorHints(gentity_s *)+2EA/r
    float score;
};

char __cdecl Player_IsPlayerUsingTurretNearby(gentity_s *ent);
void __cdecl Player_UpdateActivate(gentity_s *ent);
char __cdecl Player_ActivateCmd(gentity_s *ent);
void __cdecl Player_ActivateHoldCmd(gentity_s *ent);
void __cdecl Player_UseEntity(gentity_s *playerEnt, gentity_s *useEnt);
void __cdecl Player_ActivateDoubleTapCmd(gentity_s *ent);
void __cdecl Player_UpdateCursorHints(gentity_s *ent);
int __cdecl Player_GetUseList(gentity_s *ent, MaterialMemory *useList, int prevHintEntIndex);
bool __cdecl BG_PlayerWeaponBlockPickupWeapon(const playerState_s *ps, unsigned int weaponIndex);
bool __cdecl compare_use(const useList_t *a, const useList_t *b);
int __cdecl Player_GetItemCursorHint(const gclient_s *client, const gentity_s *traceEnt);
void __cdecl Player_SetTurretDropHint(gentity_s *ent);
