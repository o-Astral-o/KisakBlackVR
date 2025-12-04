#pragma once

enum eAttachmentPoint : __int32
{                                       // XREF: WeaponComponent/r
                                        // AttachmentTableEntry/r ...
    ATTACHMENT_POINT_NONE    = 0x0,
    ATTACHMENT_POINT_TOP     = 0x1,
    ATTACHMENT_POINT_FIRST   = 0x1,
    ATTACHMENT_POINT_BOTTOM  = 0x2,
    ATTACHMENT_POINT_TRIGGER = 0x3,
    ATTACHMENT_POINT_MUZZLE  = 0x4,
    ATTACHMENT_POINT_COUNT   = 0x5,
    ATTACHMENT_POINT_INVALID = 0x5,
};

struct WeaponDef;
struct WeaponVariantDef;

unsigned int __cdecl BG_GetNumWeapons();
const WeaponVariantDef *__cdecl BG_GetWeaponVariantDef(unsigned int weaponIndex);
const WeaponDef *__cdecl BG_GetWeaponDef(unsigned int weaponIndex);
unsigned int __cdecl BG_GetWeaponIndex(const WeaponVariantDef *weapVariantDef);
void __cdecl BG_ShutdownWeaponDefFiles();
void BG_FreeWeaponDefStrings();
void __cdecl BG_InitDefaultWeaponDef();
void __cdecl BG_ClearWeaponDef();
void __cdecl BG_FillInAllWeaponItems();
void __cdecl BG_SetupWeaponIndex(unsigned int weapIndex);
void __cdecl BG_FillInWeaponItems(unsigned int weapIndex);
void __cdecl BG_SetUpAmmoForWeapon(unsigned int weapIndex);
void __cdecl BG_SetupAmmoIndexes(unsigned int weapIndex);
void __cdecl BG_SetupSharedAmmoIndexes(unsigned int weapIndex);
void __cdecl BG_SetupClipIndexes(unsigned int weapIndex);
int __cdecl BG_FindWeaponIndexForName(const char *name);
int __cdecl BG_WeaponVariantNameHashCompare(unsigned int *a, unsigned int *b);
int __cdecl BG_GetWeaponIndexForName(char *name, void (__cdecl *regWeap)(unsigned int));
int __cdecl BG_SetupWeaponVariantDef(WeaponVariantDef *weapVariantDef, void (__cdecl *regWeap)(unsigned int));
void __cdecl BG_SetupWeaponAlts(unsigned int weapIndex, void (__cdecl *regWeap)(unsigned int));
void __cdecl BG_SetupDualWieldAlts(unsigned int weapIndex, void (__cdecl *regWeap)(unsigned int));
void __cdecl BG_SetupWeaponMountedVersions(unsigned int weaponIndex, void (__cdecl *regWeap)(unsigned int));
bool __cdecl BG_IsDefaultWeapon(const char *name);
int __cdecl BG_GetWeaponIndexForName(char *name);
int __cdecl BG_GetWeaponTableItemIndex(int weaponIndex);
char __cdecl BG_LoadWeaponTable(const char *weaponNamePostfix, void (__cdecl *regWeap)(unsigned int));
char __cdecl BG_LoadWeaponTableBaseAndVariants(
                int weaponTableItemIndex,
                const char *weaponNamePostfix,
                void (__cdecl *regWeap)(unsigned int));
char __cdecl BG_WeaponVariantPrecache_r(
                int weaponTableItemIndex,
                int baseWeaponIndex,
                void (__cdecl *regWeap)(unsigned int),
                const char *namePrefix,
                const char *namePostfix,
                eAttachmentPoint point,
                int index,
                bool alreadyRegistered);
void __cdecl BG_WeaponVariantPrecache(
                int baseWeaponIndex,
                void (__cdecl *regWeap)(unsigned int),
                const char *namePrefix,
                const char *namePostfix);
