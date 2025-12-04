#pragma once
#include "r_material.h"

struct FxSpawnDefLooping // sizeof=0x8
{                                       // XREF: FxSpawnDef/r
                                        // FxEditorElemDef/r
    int intervalMsec;
    int count;
};

struct FxIntRange // sizeof=0x8
{                                       // XREF: FxSpawnDefOneShot/r
                                        // FxElemDefUnion/r ...
    int base;                           // XREF: FX_DrawElem_Cloud_Main+12/w
                                        // FX_DrawElem_Cloud_Main+42/r ...
    int amplitude;                      // XREF: FX_DrawElem_Cloud_Main+21/w
                                        // FX_DrawElem_Cloud_Main+24/r ...
};

struct FxSpawnDefOneShot // sizeof=0x8
{                                       // XREF: FxSpawnDef/r
                                        // FxEditorElemDef/r
    FxIntRange count;
};

union FxSpawnDef // sizeof=0x8
{                                       // XREF: FxElemDef/r
    FxSpawnDefLooping looping;
    FxSpawnDefOneShot oneShot;
};

struct FxFloatRange // sizeof=0x8
{                                       // XREF: FxElemDef/r
                                        // FxElemDef/r ...
    float base;
    float amplitude;
};

struct FxElemAtlas // sizeof=0x8
{                                       // XREF: FxElemDef/r
    unsigned __int8 behavior;
    unsigned __int8 index;
    unsigned __int8 fps;
    unsigned __int8 loopCount;
    unsigned __int8 colIndexBits;
    unsigned __int8 rowIndexBits;
    unsigned __int16 entryCountAndIndexRange;
};

struct FxElemVec3Range // sizeof=0x18
{                                       // XREF: FxElemVelStateInFrame/r
                                        // FxElemVelStateInFrame/r
    float base[3];
    float amplitude[3];
};

struct FxElemVelStateInFrame // sizeof=0x30
{                                       // XREF: FxElemVelStateSample/r
                                        // FxElemVelStateSample/r
    FxElemVec3Range velocity;
    FxElemVec3Range totalDelta;
};

const struct FxElemVelStateSample // sizeof=0x60
{
    FxElemVelStateInFrame local;
    FxElemVelStateInFrame world;
};

struct FxElemVisualState // sizeof=0x18
{                                       // XREF: FxElemVisStateSample/r
                                        // FxElemVisStateSample/r ...
    unsigned __int8 color[4];
    float rotationDelta;
    float rotationTotal;                // XREF: FX_CreateImpactMarkInternal+174/r
    float size[2];                      // XREF: FX_CreateImpactMarkInternal+A1/w
                                        // FX_CreateImpactMarkInternal+169/r
    float scale;
};

const struct FxElemVisStateSample // sizeof=0x30
{
    FxElemVisualState base;
    FxElemVisualState amplitude;
};

struct FxElemMarkVisuals // sizeof=0x8
{                                       // XREF: $02AC52774A03C1B6F49B7C17F56F8A85/r
    Material *materials[2];
};

union FxEffectDefRef // sizeof=0x4
{                                       // XREF: FxElemVisuals/r
                                        // FxElemDef/r ...
    const FxEffectDef *handle;
    const char *name;
};

union FxElemVisuals // sizeof=0x4
{                                       // XREF: FX_GenSpriteVerts+4C/w
                                        // FX_GenSpriteVerts+52/r ...
    const void *anonymous;
    Material *material;
    XModel *model;
    FxEffectDefRef effectDef;
    const char *soundName;
};

union FxElemDefVisuals // sizeof=0x4
{                                       // XREF: FxElemDef/r
    FxElemMarkVisuals *markArray;
    FxElemVisuals *array;
    FxElemVisuals instance;
};

struct FxTrailVertex // sizeof=0x14
{                                       // XREF: FxEditorTrailDef/r
    float pos[2];
    float normal[2];
    float texCoord;
};

struct FxTrailDef // sizeof=0x1C
{
    int scrollTimeMsec;
    int repeatDist;
    int splitDist;
    int vertCount;
    //$A41F6DDA83A77139D9FD89879C7CFB09 ___u4;
    union //$A41F6DDA83A77139D9FD89879C7CFB09 // sizeof=0x4
    {                                       // XREF: FxTrailDef/r
        FxTrailVertex *vertsEA;
        FxTrailVertex *verts;
    };
    int indCount;
    //$D31B43AE1E46D24CA4A859818848B5E1 ___u6;
    union //$D31B43AE1E46D24CA4A859818848B5E1 // sizeof=0x4
    {                                       // XREF: FxTrailDef/r
        unsigned __int16 *indsEA;
        unsigned __int16 *inds;
    };
};

struct FxBillboardTrim // sizeof=0x8
{                                       // XREF: FxElemDefUnion/r
    float topWidth;
    float bottomWidth;
};

union FxElemDefUnion // sizeof=0x8
{                                       // XREF: FxElemDef/r
    FxBillboardTrim billboard;
    FxIntRange cloudDensityRange;
};

struct FxElemSpawnSound // sizeof=0x4
{                                       // XREF: FxElemDef/r
                                        // FxEditorElemDef/r
    const char *spawnSound;
};

const struct FxElemDef // sizeof=0x124
{
    int flags;
    FxSpawnDef spawn;
    FxFloatRange spawnRange;
    FxFloatRange fadeInRange;
    FxFloatRange fadeOutRange;
    float spawnFrustumCullRadius;
    FxIntRange spawnDelayMsec;
    FxIntRange lifeSpanMsec;
    FxFloatRange spawnOrigin[3];
    FxFloatRange spawnOffsetRadius;
    FxFloatRange spawnOffsetHeight;
    FxFloatRange spawnAngles[3];
    FxFloatRange angularVelocity[3];
    FxFloatRange initialRotation;
    unsigned int rotationAxis;
    FxFloatRange gravity;
    FxFloatRange reflectionFactor;
    FxElemAtlas atlas;
    float windInfluence;
    unsigned __int8 elemType;
    unsigned __int8 visualCount;
    unsigned __int8 velIntervalCount;
    unsigned __int8 visStateIntervalCount;
    const FxElemVelStateSample *velSamples;
    const FxElemVisStateSample *visSamples;
    FxElemDefVisuals visuals;
    float collMins[3];
    float collMaxs[3];
    FxEffectDefRef effectOnImpact;
    FxEffectDefRef effectOnDeath;
    FxEffectDefRef effectEmitted;
    FxFloatRange emitDist;
    FxFloatRange emitDistVariance;
    FxEffectDefRef effectAttached;
    //$6560A5492D3E60888A9CD1F2E81D900E ___u34;
    union //$6560A5492D3E60888A9CD1F2E81D900E // sizeof=0x4
    {                                       // XREF: FxElemDef/r
        FxTrailDef *localTrailDef;
        FxTrailDef *trailDef;
    };
    unsigned __int8 sortOrder;
    unsigned __int8 lightingFrac;
    unsigned __int8 unused[2];
    unsigned __int16 alphaFadeTimeMsec;
    unsigned __int16 maxWindStrength;
    unsigned __int16 spawnIntervalAtMaxWind;
    unsigned __int16 lifespanAtMaxWind;
    FxElemDefUnion u;
    FxElemSpawnSound spawnSound;
    float billboardPivot[2];
};

const struct FxEffectDef // sizeof=0x3C
{                                       // XREF: XAssetPoolEntry<FxEffectDef>/r
    const char *name;
    unsigned __int8 flags;
    unsigned __int8 efPriority;
    unsigned __int8 reserved[2];
    int totalSize;
    int msecLoopingLife;
    int elemDefCountLooping;
    int elemDefCountOneShot;
    int elemDefCountEmission;
    //$7BD2F22D4D2E155DDD2F5AE6C1F591D8 ___u9;
    union //$7BD2F22D4D2E155DDD2F5AE6C1F591D8 // sizeof=0x4
    {                                       // XREF: FxEffectDef/r
        const FxElemDef *elemDefsEA;
        const FxElemDef *elemDefs;
    };
    float boundingBoxDim[3];
    float boundingSphere[4];
};