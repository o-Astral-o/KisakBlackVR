#pragma once

#include "phys_colgeom.h"

struct colgeom_visitor_t : visitor_base_t // sizeof=0x70
{                                                                             // XREF: colgeom_visitor_inlined_t<200>/r
    //struct /*VFT*/ colgeom_visitor_t_vtbl // sizeof=0x18
    //{
    //    void (__thiscall *~colgeom_visitor_t)(struct colgeom_visitor_t *this);
    //    void (__thiscall *prolog)(colgeom_visitor_t *this);
    //    void (__thiscall *epilog)(colgeom_visitor_t *this);
    //    void (__thiscall *visit)(colgeom_visitor_t *this, const cbrush_t *);
    //    void (__thiscall *visit)(colgeom_visitor_t *this, const CollisionAabbTree *);
    //    void (__thiscall *update)(colgeom_visitor_t *this, const float *, const float *, int, const float *);
    //};

    colgeom_visitor_t();
    colgeom_visitor_t(const colgeom_visitor_t *__that);
    virtual ~colgeom_visitor_t();
    virtual void prolog();
    virtual void epilog(); 
    virtual void visit(const cbrush_t *);
    virtual void visit(const CollisionAabbTree *);
    virtual void update(const float *, const float *, int, const float *);

    colgeom_visitor_t &operator=(colgeom_visitor_t *that)
    {
        this->m_mn = that->m_mn;
        this->m_mx = that->m_mx;
        this->m_p0 = that->m_p0;
        this->m_p1 = that->m_p1;
        this->m_delta = that->m_delta;
        this->m_rvec = that->m_rvec;
        this->m_radius = that->m_radius;
        this->m_mask = that->m_mask;
        this->m_threadInfo = that->m_threadInfo;
    }

    hybrid_vector m_mn;                                 // XREF: query_brush_model_gjk_geom(ushort,int,gjk_collision_visitor *)+8F/o
    hybrid_vector m_mx;                                 // XREF: query_brush_model_gjk_geom(ushort,int,gjk_collision_visitor *)+8B/o
    hybrid_vector m_p0;
    hybrid_vector m_p1;
    hybrid_vector m_delta;
    hybrid_vector m_rvec;
    float m_radius;
    int m_mask;                                                 // XREF: query_brush_model_gjk_geom(ushort,int,gjk_collision_visitor *)+A3/w
    TraceThreadInfo *m_threadInfo;

    void intersect_box(float *mn, float *mx, int mask);
    void intersect_box_brushes(cLeaf_s *leaf);
    void intersect_box_partitions(cLeaf_s *leaf);
    void intersect_box_brushnode(cLeafBrushNode_s *node);
    void intersect_box_partitions_r(struct CollisionAabbTree *aabbTree);
};

struct static_colgeom_visitor_t : colgeom_visitor_t // sizeof=0x1078
{
    int ntrees;
    const CollisionAabbTree *trees[512];
    int nbrushes;
    const cbrush_t *brushes[512];

    //00000000 struct /*VFT*/ static_colgeom_visitor_t_vtbl // sizeof=0x18
    //00000000 {
    //00000000     void (__thiscall *~static_colgeom_visitor_t)(struct static_colgeom_visitor_t *this);
    //00000004     void (__thiscall *prolog)(struct static_colgeom_visitor_t *this);
    //00000008     void (__thiscall *epilog)(struct static_colgeom_visitor_t *this);
    //0000000C     void (__thiscall *visit)(struct static_colgeom_visitor_t *this, const cbrush_t *);
    //00000010     void (__thiscall *visit)(struct static_colgeom_visitor_t *this, const CollisionAabbTree *);
    //00000014     void (__thiscall *update)(struct static_colgeom_visitor_t *this, const float *, const float *, int, const float *);
    //00000018 };

    virtual ~static_colgeom_visitor_t();
    virtual void prolog();
    virtual void epilog();
    virtual void visit(const cbrush_t *);
    virtual void visit(const CollisionAabbTree *);
    virtual void update(const float *, const float *, int, const float *);

    void visit(const CollisionAabbTree *tree);
    void visit(const cbrush_t *brush);
    void update(
        const float *_mn,
        const float *_mx,
        int mask,
        const float *expand_vec);
};


