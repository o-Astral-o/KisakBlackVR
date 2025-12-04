#include "db_assetnames.h"
#include "db_registry.h"

#include <gfx_d3d/r_material.h>

#include <xanim/xmodel.h>
#include <universal/q_shared.h>

const char *(__cdecl *DB_XAssetGetNameHandler[43])(const XAssetHeader *) =
{
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_ImageGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  NULL,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_LocalizeEntryGetName,
  &DB_DDLGetName,
  NULL,
  NULL,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_DDLGetName,
  &DB_GetEmblemSetName
};

const char *g_assetNames[] =
{
  "xmodelpieces",
  "physpreset",
  "physconstraints",
  "destructibledef",
  "xanim",
  "xmodel",
  "material",
  "techset",
  "image",
  "sound",
  "sound_patch",
  "col_map_sp",
  "col_map_mp",
  "com_map",
  "game_map_sp",
  "game_map_mp",
  "map_ents",
  "gfx_map",
  "lightdef",
  "ui_map",
  "font",
  "menufile",
  "menu",
  "localize",
  "weapon",
  "weapondef",
  "weaponvariant",
  "snddriverglobals",
  "fx",
  "impactfx",
  "aitype",
  "mptype",
  "mpbody",
  "mphead",
  "character",
  "xmodelalias",
  "rawfile",
  "stringtable",
  "packindex",
  "xGlobals",
  "ddl",
  "glasses",
  "emblemset"
};

void(__cdecl *DB_XAssetSetNameHandler[43])(XAssetHeader *, const char *) =
{
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_ImageSetName,
  &DB_DDLSetname,
  NULL,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  NULL,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_LocalizeEntrySetName,
  &DB_DDLSetname,
  NULL,
  NULL,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  &DB_DDLSetname,
  NULL,
  NULL
};

int __cdecl DB_SizeofXAsset_RawFile_()
{
    iassert(sizeof(RawFile) == 12);
    return 12;
}
int(__cdecl *DB_GetXAssetSizeHandler[43])() =
{
  &DB_SizeofXAsset_RawFile_,
  &DB_SizeofXAsset_PhysPreset_,
  &DB_SizeofXAsset_PhysConstraints_,
  &SV_GetMaxAttachCount,
  &PM_MediumLandingForSurface,
  &DB_SizeofXAsset_XModel_,
  &DB_SizeofXAsset_Material_,
  &DB_SizeofXAsset_MaterialTechniqueSet_,
  &DB_SizeofXAsset_SndDriverGlobals_,
  &DB_SizeofXAsset_XGlobals_,
  &DB_SizeofXAsset_StringTable_,
  &DB_SizeofXAsset_clipMap_t_,
  &DB_SizeofXAsset_clipMap_t_,
  &DB_SizeofXAsset_ComWorld_,
  &DB_SizeofXAsset_EmblemSet_,
  &DB_SizeofXAsset_EmblemSet_,
  &DB_SizeofXAsset_RawFile_,
  &DB_SizeofXAsset_GfxWorld_,
  &DB_SizeofXAsset_GfxLightDef_,
  NULL,
  &SV_GetMaxAttachCount,
  &DB_SizeofXAsset_RawFile_,
  &DB_SizeofXAsset_menuDef_t_,
  &XAnimTreeSize,
  &DB_SizeofXAsset_WeaponVariantDef_,
  NULL,
  NULL,
  &DB_SizeofXAsset_SndDriverGlobals_,
  &DB_SizeofXAsset_FxEffectDef_,
  &XAnimTreeSize,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  NULL,
  &DB_SizeofXAsset_RawFile_,
  &DB_SizeofXAsset_StringTable_,
  &DB_SizeofXAsset_PackIndex_,
  &DB_SizeofXAsset_XGlobals_,
  &XAnimTreeSize,
  &DB_SizeofXAsset_Glasses_,
  &DB_SizeofXAsset_EmblemSet_
};





const char *__cdecl DB_ImageGetName(const XAssetHeader *header)
{
    return header->image->name;
}

void __cdecl DB_ImageSetName(XAssetHeader *header, const char *name)
{
    //header->xmodelPieces[3].pieces = name;
    header->image->name = name;
}

const char *__cdecl DB_LocalizeEntryGetName(const XAssetHeader *header)
{
    return (const char *)header->xmodelPieces->numpieces;
}

void __cdecl DB_LocalizeEntrySetName(XAssetHeader *header, const char *name)
{
    header->xmodelPieces->numpieces = (int)name;
}

void __cdecl DB_DDLSetname(XAssetHeader *header, const char *name)
{
    header->xmodelPieces->name = name;
}

const char *__cdecl DB_DDLGetName(const XAssetHeader *header)
{
    return header->xmodelPieces->name;
}

const char *__cdecl DB_GetEmblemSetName(const XAssetHeader *header)
{
    return "emblemset";
}

const char *__cdecl DB_GetXAssetHeaderName(int type, const XAssetHeader *header)
{
    const char *v2; // eax
    const char *name; // [esp+0h] [ebp-4h]

    if ( !header
        && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp", 687, 0, "%s", "header") )
    {
        __debugbreak();
    }
    if ( !DB_XAssetGetNameHandler[type]
        && !Assert_MyHandler(
                    "C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp",
                    688,
                    0,
                    "%s",
                    "DB_XAssetGetNameHandler[type]") )
    {
        __debugbreak();
    }
    if ( !header->xmodelPieces
        && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp", 689, 0, "%s", "header->data") )
    {
        __debugbreak();
    }
    name = DB_XAssetGetNameHandler[type](header);
    if ( !name )
    {
        v2 = va("Name \"%s\" not found for asset type %s\n", 0, g_assetNames[type]);
        if ( !Assert_MyHandler(
                        "C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp",
                        691,
                        0,
                        "%s\n\t%s",
                        "name",
                        v2) )
            __debugbreak();
    }
    return name;
}

const char *__cdecl DB_GetXAssetName(const XAsset *asset)
{
    if ( !asset
        && !Assert_MyHandler("C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp", 698, 0, "%s", "asset") )
    {
        __debugbreak();
    }
    return DB_GetXAssetHeaderName(asset->type, &asset->header);
}

void __cdecl DB_SetXAssetName(XAsset *asset, const char *name)
{
    if ( !DB_XAssetSetNameHandler[asset->type]
        && !Assert_MyHandler(
                    "C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp",
                    705,
                    0,
                    "%s",
                    "DB_XAssetSetNameHandler[asset->type]") )
    {
        __debugbreak();
    }
    DB_XAssetSetNameHandler[asset->type](&asset->header, name);
}

int __cdecl DB_GetXAssetTypeSize(int type)
{
    if ( !DB_GetXAssetSizeHandler[type]
        && !Assert_MyHandler(
                    "C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp",
                    712,
                    0,
                    "%s",
                    "DB_GetXAssetSizeHandler[type]") )
    {
        __debugbreak();
    }
    return DB_GetXAssetSizeHandler[type]();
}

const char *__cdecl DB_GetXAssetTypeName(unsigned int type)
{
    if ( type > 0x2A
        && !Assert_MyHandler(
                    "C:\\projects_pc\\cod\\codsrc\\src\\database\\db_assetnames.cpp",
                    718,
                    0,
                    "%s",
                    "type >= 0 && type < ASSET_TYPE_COUNT") )
    {
        __debugbreak();
    }
    return g_assetNames[type];
}

