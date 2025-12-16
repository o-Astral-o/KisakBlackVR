#pragma once

#include "phys_local.h"
#include "phys_colgeom.h"

struct phys_gjk_geom_id_pair_key // sizeof=0x8
{                                       // XREF: phys_gjk_cache_info/r
    unsigned int m_id1;                 // XREF: phys_heap_gjk_cache_system_avl_tree::get_gjk_cache_info(uint,uint,bool)+8B/w
    unsigned int m_id2;                 // XREF: phys_heap_gjk_cache_system_avl_tree::get_gjk_cache_info(uint,uint,bool)+91/w
};

struct phys_gjk_cache_info // sizeof=0x80
{                                       // XREF: phys_heap_gjk_cache_system_avl_tree::phys_gjk_cache_info_internal/r
    phys_vec3 m_support_dir;
    cached_simplex_info m_support_a;
    cached_simplex_info m_support_b;
    int m_support_count;
    phys_gjk_geom_id_pair_key m_key;
    unsigned int m_flags;
};

struct __declspec(align(8)) gjk_entity_info_t // sizeof=0x50
{
    enum ENTITY_TYPE : __int32
    {                                       // XREF: gjk_entity_info_t/r
        ET_GENT  = 0x0,
        ET_CENT  = 0x1,
        ET_DENT  = 0x2,
        ET_GLASS = 0x3,
        ET_NONE  = 0x4,
    };
    phys_mat44 m_mat;
    gjk_entity_info_t::ENTITY_TYPE m_ent_type;
    const void *m_ent;
    int m_query_visitor_count;
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    const Glass *get_glass();
    const void *get_ent();

    const DynEntityDef *get_dent();
};

struct __declspec(align(16)) gjk_geom_info_t // sizeof=0x40
{
    phys_vec3 m_aabb_min;
    phys_vec3 m_aabb_max;
    gjk_base_t *m_cg;
    gjk_entity_info_t *m_ent_info;
    int m_query_visitor_count;
    float m_hit_time;
    gjk_geom_info_t *m_next_link;
    gjk_geom_info_t *m_total_next_link;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte

    void calc_aabb();
};

struct phys_gjk_geom // sizeof=0x4
{                                       // XREF: gjk_base_t/r
    //phys_gjk_geom_vtbl *__vftable;
    virtual void support(const phys_vec3 *, phys_vec3 *, phys_vec3 *);
    virtual void get_simplex(const cached_simplex_info *, const int, phys_vec3 *, phys_vec3 *);
    virtual void set_simplex(const phys_vec3 *, const int, const phys_vec3 *, cached_simplex_info *);
    virtual const phys_vec3 * get_center(const phys_vec3 * result);
    virtual void get_feature(phys_contact_manifold *);
    virtual float get_geom_radius();
    virtual void calc_aabb(const phys_mat44 *, phys_vec3 *, phys_vec3 *);
    virtual bool ray_cast(const phys_vec3 *, const phys_vec3 *, const float, float *, phys_vec3 *);
    virtual bool is_polyhedron();

    const phys_vec3 *support_only(const phys_vec3 *result, const phys_mat44 *xform, const phys_vec3 *v);
};

struct phys_gjk_collision_info // sizeof=0x30
{                                       // XREF: phys_gjk_info/r
    phys_vec3 m_p1;
    phys_vec3 m_p2;
    phys_vec3 m_n;
};

struct __declspec(align(8)) phys_gjk_input // sizeof=0x50
{                                       // XREF: ?gjk_trace@@YAXABUgjk_trace_input_t@@PAUlist_gjk_trace_output@@@Z/r
                                        // ?do_initial_tunnel_test@@YAXPAVbroad_phase_group@@ABVbroad_phase_environement_query_results@@@Z/r ...
    phys_vec3 m_cg1_translation;
    phys_vec3 m_cg2_translation;
    float m_start_time;
    float m_end_time;
    const phys_gjk_geom *gjk_cg1;
    const phys_gjk_geom *gjk_cg2;
    const phys_mat44 *cg1_to_world_xform;
    const phys_mat44 *cg2_to_world_xform;
    phys_gjk_cache_info *gjk_ci;
    float cg1_radius;
    float cg2_radius;
    float m_sep_thresh;
    bool m_intersection_test_only;      // XREF: phys_collide_do_gjk_collide_and_contact_manifold(phys_collision_pair *,phys_gjk_info *,phys_contact_manifold_process *)+10/w
    bool m_continuous_collision;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct phys_gjk_info // sizeof=0x3A0
{                                       // XREF: ?gjk_trace@@YAXABUgjk_trace_input_t@@PAUlist_gjk_trace_output@@@Z/r
    enum gjk_retval_e : __int32
    {                                       // XREF: ?phys_collide_do_gjk_collide@phys_gjk_info@@QAE?B_NPBVphys_gjk_input@@@Z/r
        GJK_SEPARATED   = 0x0,
        GJK_VALID       = 0x1,
        GJK_PENETRATING = 0x2,
        GJK_INVALID     = 0x3,
    };
    struct phys_gjk_set_info // sizeof=0x14
    {                                       // XREF: phys_gjk_info/r
        float m_lamda[4];
        int m_candidate;
    };

    gjk_retval_e gjk(const phys_gjk_input *d, const phys_vec3 *initial_support_dir, bool in_separation_loop);

    int seed_simplex(int cached_vert_count);
    int gjk_subalgorithm(int w_set, int new_index);
    gjk_retval_e gjk_ray_cast(
        const phys_gjk_input *d,
        const phys_vec3 *initial_support_dir,
        bool in_separation_loop);
    gjk_retval_e collide(const phys_gjk_input *d);
    char phys_collide_do_gjk_collide(const phys_gjk_input *d);
    int compress_verts(char w_set);
    void comp_closest_points(int w_set, phys_vec3 *a, phys_vec3 *b);
    void gjk_cache_update_invalid(const phys_gjk_input *d);
    const phys_vec3 *get_initial_support_dir(phys_vec3 *result, const phys_gjk_input *d);
    void gjk_cache_update_test_only_valid(const phys_gjk_input *d);
    void gjk_cache_update_colliding(const phys_gjk_input *d);
    void gjk_cache_update_test_only_penetrating(const phys_gjk_input *d);
    void comp_v(int w_set, phys_vec3 *v);
    int init_gjk(
        const phys_gjk_input *d,
        const phys_vec3 *initial_support_dir,
        bool in_separation_loop);

    phys_mat44 cg2_to_cg1_xform;
    phys_vec3 m_cg1_relative_translation_loc;
    float m_continuous_collision_lambda;
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
    phys_gjk_collision_info cg1_cinfo_loc;
    phys_vec3 m_gjk_origin;
    phys_vec3 m_w_verts[4];
    phys_vec3 m_a_verts[4];
    phys_vec3 m_b_verts[4];
    phys_vec3 m_a_inds[4];
    phys_vec3 m_b_inds[4];
    phys_vec3 m_support_dir;
    float m_geom_radii_sum;
    int m_cc_reset_iter;
    int m_flags;
    int m_w_set;
    int m_last_w_set;
    int m_gjk_iter;
    float m_gjk_sep_thresh;
    float m_gjk_pen_thresh_sq;
    float m_upper_dist_sq;
    float m_lower_dist_sq;
    float m_dot_ij[4][4];
    phys_gjk_info::phys_gjk_set_info m_set_list[16];
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

// local variable allocation has failed, the output may be wrong!
void    phys_full_inv_multiply_mat(
                phys_mat44 *dest,
                const phys_mat44 *left,
                const phys_mat44 *right);
void __cdecl get_simplex(
                phys_gjk_geom *cg1,
                phys_gjk_geom *cg2,
                phys_gjk_cache_info *gjk_ci,
                phys_vec3 *a_verts,
                phys_vec3 *a_inds,
                phys_vec3 *b_verts,
                phys_vec3 *b_inds,
                int *vert_count);
void __cdecl set_simplex(
                phys_gjk_geom *cg1,
                phys_gjk_geom *cg2,
                phys_gjk_cache_info *gjk_ci,
                const phys_vec3 *a_normal,
                const phys_vec3 *b_normal,
                const phys_vec3 *a_inds,
                const phys_vec3 *b_inds,
                int w_set);
int    backup1(phys_gjk_info *gjk_info, int new_index, bool seed_simplex);

void __cdecl setup_gjk_input_from_pcp(phys_gjk_input *pgi, phys_collision_pair *pcp);






