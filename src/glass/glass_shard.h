#pragma once
#include <universal/com_math.h>
#include <physics/phys_local.h>
#include <gfx_d3d/r_material.h>

struct ray2_t // sizeof=0x14
{                                       // XREF: GlassShard::Outline::Vertex/r
                                        // OutlineEdge/r
    float origin[2];
    float dir[2];                       // XREF: GlassClient::PlayShatterFX(int,float const * const,float const * const)+5AC/o
    float len;                          // XREF: GlassClient::PlayShatterFX(int,float const * const,float const * const)+481/r
                                        // GlassClient::PlayShatterFX(int,float const * const,float const * const)+4B3/r ...
};

struct __declspec(align(16)) GlassPhysics // sizeof=0xA0
{
    phys_mat44 m_mat;
    phys_vec3 m_inv_inertia;
    phys_vec3 m_t_vel;
    phys_vec3 m_a_vel;
    phys_vec3 m_force_sum;
    phys_vec3 m_torque_sum;
    float m_inv_mass;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct GlassDef // sizeof=0x3C
{                                       // XREF: GlassDefLoad/r
    const char *name;
    int maxHealth;
    float thickness;
    float minShardSize;
    float maxShardSize;
    float shardLifeProbablility;
    int maxShards;
    Material *pristineMaterial;
    Material *crackedMaterial;
    Material *shardMaterial;
    const char *crackSound;
    const char *shatterShound;
    const char *autoShatterShound;
    const FxEffectDef *crackEffect;
    const FxEffectDef *shatterEffect;
};

struct ShardGroup // sizeof=0x54
{
    unsigned int packedPos;
    const GlassDef *glassDef;
    struct GlassShard *head;
    float worldBBoxMin[3];
    float worldBBoxMax[3];
    float origin[3];
    float extent[3];
    bool invalidBBox;
    bool visible;
    bool highLod;
    // padding byte
    __int16 numShards;
    __int16 numIndices;
    __int16 numVerts;
    unsigned __int16 lightingHandle;
    GfxLightingInfo lightingInfo;
    unsigned __int16 *renderIndices;
};

struct GlassShard // sizeof=0x90
{
    struct Outline
    {
        struct Vertex
        {
            ray2_t edge;
            bool isOriginalEdge;                // XREF: GlassShard::Outline::Reverse(void)+1E7/w
            // padding byte
            // padding byte
            // padding byte
        };
        GlassShard::Outline::Vertex *verts; // XREF: GlassClient::Outlines::InitShards(GlassShard const *,GlassShard * * const,int)+4F/w
                                            // GlassShard::Create(Glass const *)+35/w ...
        float length;
        float area;
        unsigned __int8 numVerts;           // XREF: GlassClient::Outlines::InitShards(GlassShard const *,GlassShard * * const,int)+55/w
                                            // GlassShard::Create(Glass const *)+3B/w ...
        unsigned __int8 maxVerts;           // XREF: GlassClient::Outlines::InitShards(GlassShard const *,GlassShard * * const,int)+5C/w
                                            // GlassShard::Create(Glass const *)+42/w ...
        bool isClosed;                      // XREF: GlassClient::Outlines::InitShards(GlassShard const *,GlassShard * * const,int)+63/w
                                            // GlassShard::Create(Glass const *)+49/w ...
        // padding byte
    };

    struct __declspec(align(4)) Mesh // sizeof=0x10
    {                                       // XREF: GlassShard/r
        PackedUnitVec *normArray;
        unsigned __int8 *indices;
        unsigned __int8 numNorm;
        unsigned __int8 numVerts;
        unsigned __int8 numVertsLow;
        unsigned __int8 numIndices;
        unsigned __int8 numIndicesLow;
        // padding byte
        // padding byte
        // padding byte
    };

    GlassShard *groupNext;
    unsigned __int8 *memoryPtr;
    unsigned __int16 memorySize;
    unsigned __int16 glassIndex;
    GlassShard::Outline outline;
    float thickness;
    float uvScale;
    GlassShard::Mesh mesh;
    float axis[3][3];
    float origin[3];
    int physObjId;
    GlassPhysics *glassPhysics;
    float timeUntilAction;
    float worldBBoxMin[3];
    float worldBBoxMax[3];
    ShardGroup *group;
    bool isOriginalEdge;
    bool remove;
    bool inGroupChange;
    bool delayedDrop;
};


void __cdecl GlassShard::Defrag(GlassShard *ptr);
void __userpurge GlassPhysics::CreateAxis(
                GlassPhysics *this@<ecx>,
                int a2@<ebp>,
                float *position,
                const float (*axis)[3],
                float *tVel,
                float *aVel,
                float mass,
                float *localBBoxMin,
                float *localBBoxMax);
void __userpurge GlassPhysics::AddForce(GlassPhysics *this@<ecx>, int a2@<ebp>, float *worldPos, float *impulse);
void __thiscall GlassPhysics::SetVelocity(GlassPhysics *this, float *t_vel);
void __thiscall GlassPhysics::SetAngularVelocity(GlassPhysics *this, float *a_vel);
void __thiscall GlassPhysics::Step(GlassPhysics *this, float deltaTime);
void __userpurge GlassPhysics::tensor_transform_principle(
                GlassPhysics *this@<ecx>,
                int a2@<ebp>,
                const phys_vec3 *diag,
                const phys_mat44 *mat,
                phys_mat44 *tensor);
void __userpurge GlassPhysics::IntegrateVelocity(GlassPhysics *this@<ecx>, int a2@<ebp>, float deltaTime);
void __userpurge GlassPhysics::IntegratePos(GlassPhysics *this@<ecx>, int a2@<ebp>, float deltaTime);
void __thiscall GlassPhysics::GetPosition(GlassPhysics *this, float *position, float (*axis)[3]);
int __thiscall GlassShard::Outline::Init(
                GlassShard::Outline *this,
                GlassShard::Outline::Vertex *ptr,
                unsigned __int8 num);
int __thiscall GlassShard::Outline::SetPointers(GlassShard::Outline *this, unsigned __int8 *ptr);
GlassShard::Outline *__thiscall GlassShard::Outline::operator=(GlassShard::Outline *this, GlassShard::Outline *o);
double __thiscall GlassShard::Outline::Length(GlassShard::Outline *this);
GlassShard::Outline::Vertex *__thiscall GlassShard::Outline::Add(GlassShard::Outline *this, const float *pos);
GlassShard::Outline::Vertex *__thiscall GlassShard::Outline::Add(GlassShard::Outline *this, float *dir, float len);
char __thiscall GlassShard::Outline::CloseOutline(GlassShard::Outline *this);
void __thiscall GlassShard::Outline::Vertex::operator=(
                GlassShard::Outline::Vertex *this,
                const GlassShard::Outline::Vertex *other);
void __thiscall GlassShard::Outline::GetBBox(GlassShard::Outline *this, float *mn, float *mx);
double __thiscall GlassShard::Outline::Extent(GlassShard::Outline *this);
void __thiscall GlassShard::Outline::Recenter(GlassShard::Outline *this, bool flip, float *offset);
bool __thiscall GlassShard::Outline::HasNarrowAngle(GlassShard::Outline *this);
bool __thiscall GlassShard::Outline::IsNarrow(GlassShard::Outline *this);
void __thiscall GlassShard::Outline::Reverse(GlassShard::Outline *this);
int __thiscall GlassShard::Outline::GetNumIntersections(
                GlassShard::Outline *this,
                const float *start,
                const float *dir,
                float *nearestDist,
                int *nearestedge);
double __cdecl GetSegmentParam(const float *a1, const float *a2, const float *p);
bool __cdecl Vec2IntersectSegments(const float *a1, const float *a2, const float *b1, const float *b2, float *ret);
char __cdecl Vec2IntesectLines(const float *a1, const float *a2, const float *b1, const float *b2, float *ret);
char __thiscall GlassShard::Outline::DoesIntersect(
                GlassShard::Outline *this,
                const float *start,
                const float *dir,
                float len,
                float padding);
void __thiscall GlassShard::Outline::GetNearestDistances(
                GlassShard::Outline *this,
                const float *p,
                GlassShard::Outline::EdgeDistance *dists,
                int nDists);
void __thiscall GlassShard::Outline::Verify(GlassShard::Outline *this);
void __thiscall GlassShard::Mesh::Clear(GlassShard::Mesh *this);
void __thiscall GlassShard::Mesh::SetTriangles(
                GlassShard::Mesh *this,
                unsigned __int8 *ptr,
                unsigned __int8 *triangles,
                unsigned int numTriIdxs);
int __thiscall GlassShard::Mesh::SetPointers(GlassShard::Mesh *this, PackedUnitVec *ptr);
void __thiscall GlassShard::Mesh::Init(
                GlassShard::Mesh *this,
                const GlassShard::Outline *outline,
                float thickness,
                const float *tangt);
void __cdecl GlassShard::Mesh::InitVertexList(unsigned __int8 numOutlineVerts, GlassShardMeshVertex *verts);
unsigned int __cdecl GlassShard::Mesh::GetMemorySize(unsigned int numOutineVerts);
void __thiscall GlassShard::Triangles::Triangles(GlassShard::Triangles *this, const GlassShard::Outline *ol);
double __thiscall GlassShard::Triangles::CalcCross(GlassShard::Triangles *this, int idx1, int idx2, int idx3);
char __thiscall GlassShard::Triangles::AddTri(
                GlassShard::Triangles *this,
                unsigned __int8 v1,
                unsigned __int8 v2,
                unsigned __int8 v3);
char __thiscall GlassShard::Triangles::Triangulate(GlassShard::Triangles *this);
bool __cdecl IsInside(const float *v1, const float *v2, const float *v3, const float *p);
void __thiscall GlassShard::Init(GlassShard *this);
void __thiscall GlassShard::Destroy(GlassShard *this);
double __thiscall GlassShard::EdgeRatio(GlassShard *this);
void __thiscall GlassShard::UnEdge(GlassShard *this);
void __thiscall GlassShard::Outline::MarkAllEdge(GlassShard::Outline *this, bool e);
char __thiscall GlassShard::Create(GlassShard *this, const Glass *glass);
bool __thiscall GlassShard::CanSplit(GlassShard *this, float maxShardSize, float minShardSize);
bool __thiscall GlassShard::CanSplit(GlassShard *this, bool shatter);
int __thiscall GlassShard::Shatter(GlassShard *this, GlassShard **newShards, int maxNewShards);
int __cdecl compareShards(const void *s1, const GlassShard **s2);
void __thiscall GlassShard::InitPhysics(
                GlassShard *this,
                GlassShard **newShards,
                int numNewShards,
                float glassExtent,
                const float *pos,
                const float *dir);
void __thiscall GlassShard::InitMesh(GlassShard *this);
char __thiscall GlassShard::AllocateMemory(
                GlassShard *this,
                unsigned int nHull,
                const GlassShard::Triangles *triangles);
void __thiscall GlassShard::FreeMemory(GlassShard *this);
void __thiscall GlassShard::Defrag(GlassShard *this);
void __thiscall GlassShard::ToWorldPos(GlassShard *this, float *pLocal, float *pWorld, bool is3D);
void __thiscall GlassShard::ToWorldDir(GlassShard *this, float *dLocal, float *dWorld, bool is3D);
void __thiscall GlassShard::ToLocal(GlassShard *this, float *pos, float *dir, float *localPos, float *localDir);
bool __thiscall GlassShard::Intersect(GlassShard *this, float *pos, float *dir, float *hitPoint);
void __thiscall GlassShard::ExplosionEvent(
                GlassShard *this,
                const float *expOrigin,
                float damageInner,
                float damageOuter,
                float radius,
                int mod);
char __thiscall GlassShard::TracePoint(
                GlassShard *this,
                float *p0,
                const float *p1,
                float *dir,
                float length,
                const float *mins,
                float *maxs);
void __cdecl Vec3Avg(const float *a, const float *b, float *sum);
void __cdecl Vec3Mul(const float *a, const float *b, float *product);
void __thiscall GlassShard::GetLocalBBox(GlassShard *this, float *mins, float *maxs);
void __thiscall GlassShard::UpdateBBox(GlassShard *this);
void __thiscall GlassShard::Update(GlassShard *this, float deltaTime);
void __thiscall GlassShard::ChangeGroup(GlassShard *this);
void __thiscall GlassShard::Remove(GlassShard *this, GlassShard::RemoveReason reason, bool delay);
void __thiscall GlassShard::GenerateVerts(
                GlassShard *this,
                bool highLod,
                GfxPackedVertex *baseVerts,
                unsigned __int16 vertsBaseIndex,
                unsigned __int16 *idxOut);
int __thiscall GlassShard::Split(
                GlassShard *this,
                GlassShard **newShards,
                float minShardSize,
                unsigned int startEdge,
                float startEdgeParam);
int __thiscall GlassShard::Chip(
                GlassShard *this,
                const GlassShard::Outline::EdgeDistance *dist,
                const float *hitPoint,
                GlassShard **newShards,
                float minShardSize);
int __thiscall GlassShard::InitSplitShards(
                GlassShard *this,
                GlassShard::Outline *outline1,
                GlassShard::Outline *outline2,
                GlassShard **newShards,
                float minShardSize);
char __thiscall GlassShard::Init(
                GlassShard *this,
                const GlassShard *other,
                GlassShard::Outline *newOutline,
                float *offset);
double __thiscall GlassShard::GetMass(GlassShard *this);
bool __thiscall GlassShard::InitPhysicsObj(GlassShard *this, bool enableCollisions);
void __thiscall GlassShard::DestroyPhysicsObj(GlassShard *this);
void __thiscall GlassShard::DisableCollisions(GlassShard *this);
void __thiscall GlassShard::AddForce(GlassShard *this, float *pos, const float *forceIn);
void __thiscall GlassShard::SetVelocity(GlassShard *this, float *t_vel, float *a_vel);
bool __thiscall GlassShard::LeaveOnEdge(GlassShard *this, float stickiness);
bool __thiscall GlassShard::IsOnBottomEdge(GlassShard *this);
void __thiscall GlassShard::Recenter(GlassShard *this);
char __thiscall GlassShard::InitPhysics(
                GlassShard *this,
                bool enableCollisions,
                const float *hitPos,
                const float *hitDir,
                float glassSize,
                float stickiness);
void __thiscall GlassShard::DrawOutline(GlassShard *this);
