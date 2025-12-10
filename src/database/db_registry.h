#pragma once

enum FF_DIR : __int32
{                                       // XREF: XZoneName/r
                                        // UI_LoadModsMap/r ...
    FFD_DEFAULT  = 0x0,
    FFD_MOD_DIR  = 0x1,
    FFD_USER_MAP = 0x2,
};

enum XAssetType : __int32
{                                                                             // XREF: XAsset/r
    ASSET_TYPE_XMODELPIECES = 0x0,
    ASSET_TYPE_PHYSPRESET = 0x1,
    ASSET_TYPE_PHYSCONSTRAINTS = 0x2,
    ASSET_TYPE_DESTRUCTIBLEDEF = 0x3,
    ASSET_TYPE_XANIMPARTS = 0x4,
    ASSET_TYPE_XMODEL = 0x5,
    ASSET_TYPE_MATERIAL = 0x6,
    ASSET_TYPE_TECHNIQUE_SET = 0x7,
    ASSET_TYPE_IMAGE = 0x8,
    ASSET_TYPE_SOUND = 0x9,
    ASSET_TYPE_SOUND_PATCH = 0xA,
    ASSET_TYPE_CLIPMAP = 0xB,
    ASSET_TYPE_CLIPMAP_PVS = 0xC,
    ASSET_TYPE_COMWORLD = 0xD,
    ASSET_TYPE_GAMEWORLD_SP = 0xE,
    ASSET_TYPE_GAMEWORLD_MP = 0xF,
    ASSET_TYPE_MAP_ENTS = 0x10,
    ASSET_TYPE_GFXWORLD = 0x11,
    ASSET_TYPE_LIGHT_DEF = 0x12,
    ASSET_TYPE_UI_MAP = 0x13,
    ASSET_TYPE_FONT = 0x14,
    ASSET_TYPE_MENULIST = 0x15,
    ASSET_TYPE_MENU = 0x16,
    ASSET_TYPE_LOCALIZE_ENTRY = 0x17,
    ASSET_TYPE_WEAPON = 0x18,
    ASSET_TYPE_WEAPONDEF = 0x19,
    ASSET_TYPE_WEAPON_VARIANT = 0x1A,
    ASSET_TYPE_SNDDRIVER_GLOBALS = 0x1B,
    ASSET_TYPE_FX = 0x1C,
    ASSET_TYPE_IMPACT_FX = 0x1D,
    ASSET_TYPE_AITYPE = 0x1E,
    ASSET_TYPE_MPTYPE = 0x1F,
    ASSET_TYPE_MPBODY = 0x20,
    ASSET_TYPE_MPHEAD = 0x21,
    ASSET_TYPE_CHARACTER = 0x22,
    ASSET_TYPE_XMODELALIAS = 0x23,
    ASSET_TYPE_RAWFILE = 0x24,
    ASSET_TYPE_STRINGTABLE = 0x25,
    ASSET_TYPE_PACK_INDEX = 0x26,
    ASSET_TYPE_XGLOBALS = 0x27,
    ASSET_TYPE_DDL = 0x28,
    ASSET_TYPE_GLASSES = 0x29,
    ASSET_TYPE_EMBLEMSET = 0x2A,
    ASSET_TYPE_COUNT = 0x2B,
    ASSET_TYPE_STRING = 0x2B,
    ASSET_TYPE_ASSETLIST = 0x2C,
};

enum DBCloneMethod : __int32
{                                       // XREF: DB_DynamicCloneMenu/r
                                        // DB_CloneXAssetEntry/r ...
    DB_CLONE_NORMAL       = 0x0,
    DB_CLONE_FROM_DEFAULT = 0x1,
    DB_CLONE_SWAP         = 0x2,
};

struct RawFile // sizeof=0xC
{                                       // XREF: XAssetPoolEntry<RawFile>/r
    const char *name;
    int len;
    const char *buffer;
};

union XAssetHeader // sizeof=0x4
{                                                                             // XREF: CG_AddVisionSetMenuItem+13/r
    struct XModelPieces *xmodelPieces;
    struct PhysPreset *physPreset;
    struct PhysConstraints *physConstraints;
    struct DestructibleDef *destructibleDef;
    struct XAnimParts *parts;
    struct XModel *model;
    struct Material *material;
    struct MaterialPixelShader *pixelShader;
    struct MaterialVertexShader *vertexShader;
    struct MaterialTechniqueSet *techniqueSet;
    struct GfxImage *image;
    struct SndBank *sound;
    struct SndPatch *soundPatch;
    struct clipMap_t *clipMap;
    struct ComWorld *comWorld;
    struct GameWorldSp *gameWorldSp;
    struct GameWorldMp *gameWorldMp;
    struct MapEnts *mapEnts;
    struct GfxWorld *gfxWorld;
    struct GfxLightDef *lightDef;
    struct Font_s *font;
    struct MenuList *menuList;
    struct menuDef_t *menu;
    struct LocalizeEntry *localize;
    struct WeaponVariantDef *weapon;
    struct SndDriverGlobals *sndDriverGlobals;
    struct FxEffectDef *fx;
    struct FxImpactTable *impactFx;
    struct RawFile *rawfile;
    struct StringTable *stringTable;
    struct PackIndex *packIndex;
    struct XGlobals *xGlobals;
    struct ddlRoot_t *ddlRoot;
    struct Glasses *glasses;
    struct TextureList *textureList;
    struct EmblemSet *emblemSet;
    void *data;
};

struct XAsset // sizeof=0x8
{                                       // XREF: XAssetEntry/r
    XAssetType type;                    // XREF: DB_CreateDefaultEntry+7B/w
    XAssetHeader header;                // XREF: DB_CreateDefaultEntry+19/w
};

struct ScriptStringList // sizeof=0x8
{                                       // XREF: XAssetList/r
    int count;
    const char **strings;
};

struct XAssetList // sizeof=0x10
{                                       // XREF: .data:g_varXAssetList/r
    ScriptStringList stringList;
    int assetCount;
    XAsset *assets;
};

template <typename T>
union XAssetPoolEntry//<LocalizeEntry> // sizeof=0x8
{                                       // XREF: XAssetPool<LocalizeEntry,10240>/r
    //LocalizeEntry entry;
    T entry;
    XAssetPoolEntry<T> *next;
};

struct PhysConstraints;
struct PhysPreset;
struct XAnimParts;
struct DestructibleDef;
struct XModel;
struct GfxImage;
struct windowDef_t;

struct XAssetEntry // sizeof=0x10
{                                       // XREF: XAssetEntryPoolEntry/r
                                        // DB_AddXAsset/r
    XAsset asset;                       // XREF: DB_AddXAsset+9/w
                                        // DB_AddXAsset+F/w
    unsigned __int8 zoneIndex;
    bool inuse;
    unsigned __int16 nextHash;
    unsigned __int16 nextOverride;
    unsigned __int16 usageFrame;
};

struct DBReorderAssetEntry // sizeof=0x10
{                                       // XREF: $73C9AB3B505E60D629E435B147795978/r
    unsigned int sequence;
    int type;
    const char *typeString;
    const char *assetName;
};

struct XZoneInfo // sizeof=0xC
{                                       // XREF: DB_UpdateDebugZone(void)+1E/w
    const char *name;                   // XREF: DB_UpdateDebugZone(void)+15/w
    int allocFlags;                     // XREF: DB_UpdateDebugZone(void)+18/w
    int freeFlags;                      // XREF: DB_UpdateDebugZone(void)+1B/w
};

union XAssetEntryPoolEntry // sizeof=0x10
{                                       // XREF: DB_Init+AB/w
    XAssetEntry entry;
    XAssetEntryPoolEntry *next;
};

struct XBlock // sizeof=0x8
{                                       // XREF: XZone/r
    unsigned __int8 *data;
    unsigned int size;
};

struct XZone // sizeof=0x40
{                                       // XREF: .data:g_zones/r
    unsigned __int16 index;
    // padding byte
    // padding byte
    int flags;                          // XREF: DB_UnloadXAssetsMemoryForZone+31/r
    XBlock blocks[7];
};

void __cdecl DB_InitSingleton(void *pool, int size);
void __cdecl Load_PhysPresetAsset(XAssetHeader *physPreset);
void __cdecl Mark_PhysPresetAsset(PhysPreset *physPreset);
void __cdecl Load_PhysConstraintsAsset(XAssetHeader *physConstraints);
void __cdecl Mark_PhysConstraintsAsset(PhysConstraints *physConstraints);
void __cdecl Load_DestructibleDefAsset(XAssetHeader *destructibleDef);
void __cdecl Mark_DestructibleDefAsset(DestructibleDef *destructibleDef);
void __cdecl Load_XAnimPartsAsset(XAssetHeader *parts);
void __cdecl Mark_XAnimPartsAsset(XAnimParts *parts);
void __cdecl Load_XModelAsset(XAssetHeader *model);
void __cdecl Mark_XModelAsset(XModel *model);
void __cdecl DB_RemoveXModel(XAssetHeader header);
void __cdecl Load_MaterialAsset(XAssetHeader *material);
void __cdecl Mark_MaterialAsset(Material *material);
void __cdecl Load_MaterialTechniqueSetAsset(XAssetHeader *techniqueSet);
void __cdecl Mark_MaterialTechniqueSetAsset(MaterialTechniqueSet *techniqueSet);
void __cdecl Load_GfxImageAsset(XAssetHeader *image);
void __cdecl Mark_GfxImageAsset(GfxImage *image);
void __cdecl DB_RemoveImage(XAssetHeader header);
void __cdecl Load_SndBankAsset(XAssetHeader *sound);
void __cdecl Mark_SndBankAsset(SndBank *sound);
void __cdecl Load_SndPatchAsset(XAssetHeader *soundPatch);
void __cdecl Mark_SndPatchAsset(SndPatch *soundPatch);
void __cdecl DB_RemoveSound(XAssetHeader header);
void __cdecl DB_RemoveSoundPatch(XAssetHeader header);
void __cdecl Load_ClipMapAsset(XAssetHeader *clipMap);
void __cdecl Mark_ClipMapAsset(clipMap_t *clipMap);
void __cdecl DB_RemoveClipMap();
void __cdecl Load_ComWorldAsset(XAssetHeader *comWorld);
void __cdecl Mark_ComWorldAsset(ComWorld *comWorld);
void __cdecl DB_RemoveComWorld();
void __cdecl Load_GameWorldSpAsset(XAssetHeader *gameWorldSp);
void __cdecl Mark_GameWorldSpAsset(GameWorldSp *gameWorldSp);
void __cdecl Load_GameWorldMpAsset(XAssetHeader *gameWorldMp);
void __cdecl Mark_GameWorldMpAsset(GameWorldMp *gameWorldMp);
void __cdecl Load_MapEntsAsset(XAssetHeader *mapEnts);
void __cdecl Mark_MapEntsAsset(MapEnts *mapEnts);
void __cdecl Load_DDLAsset(XAssetHeader *ddlRoot);
void __cdecl Mark_DDLAsset(ddlRoot_t *ddlRoot);
void __cdecl Load_GfxWorldAsset(XAssetHeader *gfxWorld);
void __cdecl Mark_GfxWorldAsset(GfxWorld *gfxWorld);
void __cdecl DB_RemoveGfxWorld();
void __cdecl Load_LightDefAsset(XAssetHeader *lightDef);
void __cdecl Mark_LightDefAsset(GfxLightDef *lightDef);
void __cdecl Load_FontAsset(XAssetHeader *font);
void __cdecl Mark_FontAsset(Font_s *font);
void __cdecl Load_MenuListAsset(XAssetHeader *menuList);
void __cdecl Mark_MenuListAsset(MenuList *menuList);
void __cdecl Load_MenuAsset(XAssetHeader *menu);
void __cdecl Mark_MenuAsset(menuDef_t *menu);
void __cdecl DB_DynamicCloneMenu(XAssetHeader from, XAssetHeader to);
void __cdecl DB_RemoveWindowFocus(windowDef_t *window);
void __cdecl Load_LocalizeEntryAsset(XAssetHeader *localize);
void __cdecl Mark_LocalizeEntryAsset(LocalizeEntry *localize);
void __cdecl Load_WeaponVariantDefAsset(XAssetHeader *weapon);
void __cdecl Mark_WeaponVariantDefAsset(WeaponVariantDef *weapon);
void __cdecl Load_SndDriverGlobalsAsset(XAssetHeader *sndDriverGlobals);
void __cdecl Mark_SndDriverGlobalsAsset(SndDriverGlobals *sndDriverGlobals);
void __cdecl Load_FxEffectDefAsset(XAssetHeader *fx);
void __cdecl Mark_FxEffectDefAsset(FxEffectDef *fx);
void __cdecl Load_FxEffectDefFromName(const char **name);
void __cdecl Load_FxImpactTableAsset(XAssetHeader *impactFx);
void __cdecl Mark_FxImpactTableAsset(FxImpactTable *impactFx);
void __cdecl Load_RawFileAsset(XAssetHeader *rawfile);
void __cdecl Mark_RawFileAsset(RawFile *rawfile);
void __cdecl Load_StringTableAsset(XAssetHeader *stringTable);
void __cdecl Mark_StringTableAsset(StringTable *stringTable);
void __cdecl Load_PackIndexAsset(XAssetHeader *packIndex);
void __cdecl Mark_PackIndexAsset(PackIndex *packIndex);
void __cdecl Load_XGlobalsAsset(XAssetHeader *xGlobals);
void __cdecl Mark_XGlobalsAsset(XGlobals *xGlobals);
void __cdecl Load_GlassesAsset(XAssetHeader *glasses);
void __cdecl Mark_GlassesAsset(Glasses *glasses);
void __cdecl Load_EmblemSetAsset(XAssetHeader *emblemSet);
void __cdecl Mark_EmblemSetAsset(EmblemSet *emblemSet);
XAssetHeader __cdecl DB_AllocMaterial(XAssetHeader *pool);
void __cdecl DB_FreeMaterial(XAssetPoolEntry<EmblemSet> **pool, XAssetHeader header);
void __cdecl DB_RemoveGfxImage(XAssetHeader header);
void __cdecl DB_FreeGfxImage(XAssetPoolEntry<EmblemSet> **pool, XAssetHeader header);
void __cdecl DB_FreeMenu(XAssetPoolEntry<EmblemSet> **pool, XAssetHeader header);
void __cdecl DB_FreeXGlobals(XAssetPoolEntry<EmblemSet> **pool, XAssetHeader header);
void __cdecl DB_MarkAssetTypeUsageDirty();
void __cdecl DB_GetAssetTypeUsageInfo(XAssetType assetType, const char **outName, int *outUsed, int *outPool);
void __cdecl DB_PrintXAssetsForType_FastFile(XAssetType type, void *inData, bool includeOverride);
void __cdecl DB_PrintXAssetsForType(
                XAssetType type,
                void (__cdecl *func)(XAssetHeader, void *),
                void *inData,
                bool includeOverride);
GfxImage *__cdecl DB_AllocTempImage();
XAssetHeader __cdecl DB_AllocXAssetHeader(XAssetType type);
void __cdecl DB_PrintAssetName(XAssetHeader header, int *data);
void __cdecl DB_FreeXAssetHeader(XAssetType type);
XAssetType __cdecl DB_HashForName(const char *name, XAssetType type);
void __cdecl DB_LogMissingAsset(XAssetType type, const char *name);
void __cdecl DB_EnumXAssets_FastFile(
                XAssetType type,
                void (__cdecl *func)(XAssetHeader, void *),
                void *inData,
                bool includeOverride);
void __cdecl DB_LoadDelayedImages();
XAssetHeader __cdecl DB_FindXAssetDefaultHeaderInternal(XAssetType type);
const char *__cdecl DB_FindXAssetNameFromHash(XAssetType type, unsigned int hash);
XAssetHeader __cdecl DB_FindXAssetHeader(XAssetType type, char *name, bool errorIfMissing, int waitTime);
void __cdecl DB_RegisteredReorderAsset(int type, const char *assetName, XAssetEntry *assetEntry);
void __cdecl Sys_LockWrite(FastCriticalSection *critSect);
void __cdecl Sys_UnlockWrite(FastCriticalSection *critSect);
void DB_EndReorderZone();
char __cdecl DB_CompareReorderEntries(const DBReorderAssetEntry *e0, const DBReorderAssetEntry *e1);
void DB_SetReorderIncludeSequence();
char __cdecl DB_RegisterAllReorderAssetsOfType(int type, XAssetEntry *assetEntry);
void __cdecl DB_Sleep(unsigned intmsec);
XAssetEntryPoolEntry *__cdecl DB_FindXAssetEntry(XAssetType type, const char *name);
XAssetEntry *__cdecl DB_CreateDefaultEntry(XAssetType type, const char *name);
XAssetEntryPoolEntry *__cdecl DB_AllocXAssetEntry(XAssetType type, unsigned __int8 zoneIndex);
void __cdecl DB_CloneXAssetInternal(const XAsset *from, XAsset *to);
void __cdecl PrintWaitedError(XAssetType type, char *name, int waitedMsec);
bool __cdecl IsConfigFile(char *name);
void __cdecl DB_Update();
void __cdecl DB_SetInitializing(bool inUse);
bool __cdecl DB_GetInitializing();
bool __cdecl DB_IsXAssetDefault(XAssetType type, const char *name);
int __cdecl DB_GetAllXAssetOfType_FastFile(XAssetType type, XAssetHeader *assets, int maxCount);
void __cdecl DB_BeginRecoverLostDevice();
void __cdecl DB_EndRecoverLostDevice();
int __cdecl DB_GetZonePriority(int zone);
XAssetHeader __cdecl DB_AddXAsset(XAssetType type, XAssetHeader header);
void DB_SyncLostDevice();
XAssetEntryPoolEntry *__cdecl DB_LinkXAssetEntry(XAssetEntry *newEntry, int allowOverride);
void __cdecl DB_FreeXAssetEntry(XAssetEntryPoolEntry *assetEntry);
void __cdecl DB_CloneXAssetEntry(const XAssetEntry *from, XAssetEntry *to, DBCloneMethod cloneMethod);
void __cdecl DB_CloneXAsset(const XAsset *from, XAsset *to, DBCloneMethod cloneMethod);
char __cdecl DB_DynamicCloneXAsset(XAssetHeader from, XAssetHeader to, XAssetType type, DBCloneMethod cloneMethod);
void __cdecl DB_SwapXAsset(XAsset *from, XAsset *to);
void __cdecl DB_DelayedCloneXAsset(XAssetEntry *newEntry);
bool __cdecl DB_OverrideAsset(unsigned int newZoneIndex, unsigned int existingZoneIndex);
void __cdecl DB_GetXAsset(XAssetType type, XAssetHeader header);
void __cdecl DB_BuildOSPath(const char *zoneName, const char *ext, unsigned int size, char *filename);
char __cdecl DB_IsUsingGermanPaths();
void __cdecl DB_BuildOSPath_Unlocalized(const char *zoneName, const char *ext, unsigned int size, char *filename);
void DB_PostLoadXZone();
void __cdecl DB_UpdateDebugZone();
void __cdecl DB_SyncXAssets();
bool __cdecl DB_IsZoneLoaded(const char *name);
char __cdecl DB_IsZoneTypeLoaded(int zoneType);
void __cdecl DB_LoadXAssets(XZoneInfo *zoneInfo, unsigned int zoneCount, int sync);
void DB_Init();
void __cdecl DB_InitPoolHeader(XAssetType type);
void __cdecl DB_ListDefaultEntries_f();
void __cdecl DB_ListAssetPool_f();
void __cdecl DB_ListAssetPool(XAssetType type);
void __cdecl DB_DumpMaterialList_f();
void __cdecl DB_LoadXZone(XZoneInfo *zoneInfo, unsigned int zoneCount);
void __cdecl DB_LoadZone_f();
void __cdecl DB_InitThread();
void __cdecl    DB_Thread(unsigned int threadContext);
void DB_TryLoadXFile();
int __cdecl DB_TryLoadXFileInternal(const char *zoneName, int zoneFlags);
void __cdecl DB_BeginReorderZone(const char *zoneName);
void __cdecl DB_AddReorderAsset(const char *typeString, const char *assetName);
char __cdecl DB_NextZoneCsvToken(const char **parse, char *token, unsigned int tokenSize, bool allowNewLine);
bool __cdecl DB_GetZoneAllocType(int zoneFlags);
void __cdecl DB_ModXFileHandle(const char *zoneName, void **zoneFile, FF_DIR *zoneDir);
void __cdecl DB_BuildOSPath_FromSource(const char *zoneName, FF_DIR source, unsigned int size, char *filename);
void __cdecl DB_BuildOSPath_ForUsermap(const char *zoneName, unsigned int size, char *filename);
void __cdecl DB_UnloadXZone(XZone *zone, bool createDefault);
void __cdecl DB_UnloadXZoneInternal(unsigned int zoneIndex, bool createDefault);
void __cdecl DB_RemoveXAsset(XAsset *asset);
void __cdecl DB_ReleaseXAssets();
void __cdecl DB_ShutdownXAssets();
void __cdecl DB_UnloadXZoneMemory(XZone *zone);
void DB_FreeDefaultEntries();
void __cdecl DB_UnloadXAssetsMemoryForZone(int zoneFreeFlags, int zoneFreeBit);
void __cdecl DB_UnloadXAssetsMemory(XZone *zone);
void __cdecl DB_ReplaceModel(const char *original, const char *replacement);
void __cdecl DB_ReplaceXAsset(XAssetType type, const char *original, const char *replacement);
void __cdecl DB_SyncExternalAssetsInternal();
void DB_SyncExternalAssets();
void DB_ArchiveAssets();
void DB_FreeUnusedResources();
void __cdecl DB_EnableInUseCache(unsigned __int16 *data);
bool DB_DisableInUseCache();
void DB_ExternalInitAssets();
void DB_StreamCompletePreload();
void DB_UnarchiveAssets();
void __cdecl DB_Cleanup();
int __cdecl DB_GetImageIndex(const GfxImage *image);
XAssetPoolEntry<GfxImage> *__cdecl DB_GetImageAtIndex(unsigned int index);
int __cdecl DB_GetMaterialIndex(const Material *material);
XAssetPoolEntry<Material> *__cdecl DB_GetMaterialAtIndex(unsigned int index);
int __cdecl DB_GetXModelIndex(const XModel *model);
XAssetPoolEntry<XModel> *__cdecl DB_GetXModelAtIndex(unsigned int index);
char *__cdecl DB_ReferencedFFChecksums();
char *__cdecl DB_ReferencedFFNameList();
int __cdecl DB_FileSize(const char *zoneName, FF_DIR source);
char __cdecl DB_FileExists(const char *zoneName, FF_DIR source);
char __cdecl DB_ModFileExists();
void __cdecl DB_AddUserMapDir(char *zoneName);
void __cdecl DB_LoadFastFilesForPC();
void __cdecl DB_LoadGraphicsAssetsForPC();
