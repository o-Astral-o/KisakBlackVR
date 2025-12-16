#include "rbc_def_ragdoll.h"

void __userpurge ragdoll_joint_limit_info::set_b1_ud_loc(
        ragdoll_joint_limit_info *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_ud_loc)
{
  phys_vec3 *v4; // eax
  phys_vec3 v5; // [esp-10h] [ebp-1Ch] BYREF
  int v6; // [esp+0h] [ebp-Ch]
  void *v7; // [esp+4h] [ebp-8h]
  void *retaddr; // [esp+Ch] [ebp+0h]

  v6 = a2;
  v7 = retaddr;
  v4 = phys_Unitize(&v5, b1_ud_loc);
  this->m_b1_ud_loc.x = v4->x;
  this->m_b1_ud_loc.y = v4->y;
  this->m_b1_ud_loc.z = v4->z;
  PHYS_ASSERT_UNIT(&this->m_b1_ud_loc);
}

void __thiscall rigid_body_constraint_ragdoll::set(
        rigid_body_constraint_ragdoll *this,
        const phys_vec3 *b1_r_loc,
        const phys_vec3 *b2_r_loc)
{
  this->m_b1_r_loc.x = b1_r_loc->x;
  this->m_b1_r_loc.y = b1_r_loc->y;
  this->m_b1_r_loc.z = b1_r_loc->z;
  this->m_b2_r_loc.x = b2_r_loc->x;
  this->m_b2_r_loc.y = b2_r_loc->y;
  this->m_b2_r_loc.z = b2_r_loc->z;
}

void __userpurge rigid_body_constraint_ragdoll::set_snider_style(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_axis_loc,
        const phys_vec3 *b1_ref_loc)
{
  phys_vec3 *v5; // eax
  phys_vec3 *v6; // eax
  double y; // st7
  const phys_vec3 *v8; // eax
  phys_vec3 v9; // [esp-20h] [ebp-2Ch] BYREF
  const phys_vec3 *p_m_b1_ref_loc; // [esp-4h] [ebp-10h]
  int v11; // [esp+0h] [ebp-Ch]
  void *v12; // [esp+4h] [ebp-8h]
  void *retaddr; // [esp+Ch] [ebp+0h]

  v11 = a2;
  v12 = retaddr;
  v5 = phys_Unitize(&v9, b1_axis_loc);
  this->m_b1_axis_loc.x = v5->x;
  this->m_b1_axis_loc.y = v5->y;
  this->m_b1_axis_loc.z = v5->z;
  v6 = phys_Unitize(&v9, b1_ref_loc);
  this->m_b1_ref_loc.x = v6->x;
  y = v6->y;
  p_m_b1_ref_loc = &this->m_b1_ref_loc;
  this->m_b1_ref_loc.y = y;
  this->m_b1_ref_loc.z = v6->z;
  if ( (this->m_flags & 4) != 0 )
  {
    v8 = construct_orth_ud(&v9, &this->m_b1_axis_loc);
    this->m_b1_a1_loc.x = v8->x;
    this->m_b1_a1_loc.y = v8->y;
    this->m_b1_a1_loc.z = v8->z;
    v9.x = this->m_b1_axis_loc.y * this->m_b1_a1_loc.z - this->m_b1_axis_loc.z * this->m_b1_a1_loc.y;
    v9.y = this->m_b1_a1_loc.x * this->m_b1_axis_loc.z - this->m_b1_axis_loc.x * this->m_b1_a1_loc.z;
    v9.z = this->m_b1_axis_loc.x * this->m_b1_a1_loc.y - this->m_b1_axis_loc.y * this->m_b1_a1_loc.x;
    this->m_b1_a2_loc.x = v9.x;
    this->m_b1_a2_loc.y = v9.y;
    this->m_b1_a2_loc.z = v9.z;
  }
  PHYS_ASSERT_UNIT(&this->m_b1_axis_loc);
  PHYS_ASSERT_UNIT(p_m_b1_ref_loc);
}

void __thiscall rigid_body_constraint_ragdoll::set_damp_k(rigid_body_constraint_ragdoll *this, float damp_k)
{
  this->m_damp_k = damp_k;
  if ( damp_k <= 0.0 )
    this->m_flags &= ~0x40u;
  else
    this->m_flags |= 0x40u;
}

void __userpurge ragdoll_joint_limit_info::set(
        ragdoll_joint_limit_info *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_ud_loc,
        float theta_limit)
{
  phys_vec3 *v5; // eax
  double v6; // st7
  double v7; // st7
  phys_vec3 v8; // [esp-20h] [ebp-2Ch] BYREF
  const phys_vec3 *v9; // [esp-4h] [ebp-10h]
  int v10; // [esp+0h] [ebp-Ch]
  void *v11; // [esp+4h] [ebp-8h]
  void *retaddr; // [esp+Ch] [ebp+0h]

  v10 = a2;
  v11 = retaddr;
  if ( theta_limit <= 0.0 && _tlAssert("source/rbc_def_ragdoll.cpp", 7, "theta_limit > 0.0f", &toastPopupTitle) )
    __debugbreak();
  v5 = phys_Unitize(&v8, b1_ud_loc);
  this->m_b1_ud_loc.x = v5->x;
  this->m_b1_ud_loc.y = v5->y;
  this->m_b1_ud_loc.z = v5->z;
  *(float *)&v9 = cos(theta_limit);
  this->m_b1_ud_limit_co_ = *(float *)&v9;
  *(float *)&v9 = sin(theta_limit);
  this->m_b1_ud_limit_si_ = *(float *)&v9;
  *(float *)&v9 = theta_limit - 0.04363323003053665;
  v6 = *(float *)&v9;
  if ( *(float *)&v9 > 0.0 )
    v6 = 0.0;
  *(float *)&v9 = v6;
  *(float *)&v9 = cos(*(float *)&v9);
  v7 = *(float *)&v9;
  v9 = (const phys_vec3 *)this;
  this->m_b1_ud_active_limit_co_ = v7;
  PHYS_ASSERT_UNIT(v9);
}

void __thiscall ragdoll_joint_limit_info::set_theta_limit(ragdoll_joint_limit_info *this, float theta_limit)
{
  double v3; // st7
  float v4; // [esp+4h] [ebp-4h]
  float v5; // [esp+4h] [ebp-4h]
  float theta_limita; // [esp+10h] [ebp+8h]
  float theta_limitb; // [esp+10h] [ebp+8h]
  float theta_limitc; // [esp+10h] [ebp+8h]

  if ( theta_limit <= 0.0 && _tlAssert("source/rbc_def_ragdoll.cpp", 23, "theta_limit > 0.0f", &toastPopupTitle) )
    __debugbreak();
  v4 = cos(theta_limit);
  this->m_b1_ud_limit_co_ = v4;
  v5 = sin(theta_limit);
  this->m_b1_ud_limit_si_ = v5;
  theta_limita = theta_limit - 0.04363323003053665;
  v3 = theta_limita;
  if ( theta_limita > 0.0 )
    v3 = 0.0;
  theta_limitb = v3;
  theta_limitc = cos(theta_limitb);
  this->m_b1_ud_active_limit_co_ = theta_limitc;
}

void __userpurge rigid_body_constraint_ragdoll::set_theta_min_max(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b2_ref_loc,
        float theta_min,
        float theta_max)
{
  phys_vec3 *p_m_b2_axis_loc; // edi
  const phys_vec3 *v7; // eax
  phys_vec3 *v8; // eax
  const phys_vec3 *v9; // eax
  phys_vec3 *v10; // eax
  _BYTE v11[12]; // [esp+18h] [ebp-7Ch] BYREF
  phys_mat44 rv; // [esp+24h] [ebp-70h] BYREF
  phys_vec3 v13; // [esp+68h] [ebp-2Ch] BYREF
  phys_vec3 v14; // [esp+78h] [ebp-1Ch] BYREF
  unsigned int v15[3]; // [esp+88h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+94h] [ebp+0h]

  v15[0] = a2;
  v15[1] = retaddr;
  p_m_b2_axis_loc = &this->m_b2_axis_loc;
  make_rotate((int)v15, (phys_mat44 *)v11, &this->m_b2_axis_loc, theta_min, 1000.0);
  v7 = phys_multiply(&v14, (const phys_mat44 *)v11, b2_ref_loc);
  v8 = phys_Unitize(&v13, v7);
  this->m_b2_ref_min_loc.x = v8->x;
  this->m_b2_ref_min_loc.y = v8->y;
  this->m_b2_ref_min_loc.z = v8->z;
  make_rotate((int)v15, (phys_mat44 *)v11, p_m_b2_axis_loc, theta_max, 1000.0);
  v9 = phys_multiply(&v13, (const phys_mat44 *)v11, b2_ref_loc);
  v10 = phys_Unitize((phys_vec3 *)&rv.w.y, v9);
  this->m_b2_ref_max_loc.x = v10->x;
  this->m_b2_ref_max_loc.y = v10->y;
  this->m_b2_ref_max_loc.z = v10->z;
}

void __userpurge rigid_body_constraint_ragdoll::set_hinge(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_axis_loc,
        const phys_vec3 *b2_axis_loc,
        const phys_vec3 *b1_ref_loc,
        const phys_vec3 *b2_ref_loc,
        float theta_min,
        float theta_max)
{
  phys_vec3 *v9; // eax
  phys_vec3 *v10; // eax
  phys_vec3 *v11; // eax
  const phys_vec3 *v12; // eax
  const phys_vec3 *v13; // eax
  phys_vec3 *v14; // eax
  const phys_vec3 *v15; // eax
  phys_vec3 *v16; // eax
  _BYTE v17[12]; // [esp+18h] [ebp-7Ch] BYREF
  phys_mat44 rv; // [esp+24h] [ebp-70h] BYREF
  phys_vec3 v19; // [esp+68h] [ebp-2Ch] BYREF
  phys_vec3 v20; // [esp+78h] [ebp-1Ch] BYREF
  unsigned int v21[3]; // [esp+88h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+94h] [ebp+0h]

  v21[0] = a2;
  v21[1] = retaddr;
  v9 = phys_Unitize(&v20, b1_axis_loc);
  this->m_b1_axis_loc.x = v9->x;
  this->m_b1_axis_loc.y = v9->y;
  this->m_b1_axis_loc.z = v9->z;
  v10 = phys_Unitize(&v20, b2_axis_loc);
  this->m_b2_axis_loc.x = v10->x;
  this->m_b2_axis_loc.y = v10->y;
  this->m_b2_axis_loc.z = v10->z;
  v11 = phys_Unitize(&v20, b1_ref_loc);
  this->m_b1_ref_loc.x = v11->x;
  this->m_b1_ref_loc.y = v11->y;
  this->m_b1_ref_loc.z = v11->z;
  this->m_flags |= 4u;
  v12 = construct_orth_ud(&v20, &this->m_b1_axis_loc);
  this->m_b1_a1_loc.x = v12->x;
  this->m_b1_a1_loc.y = v12->y;
  this->m_b1_a1_loc.z = v12->z;
  v20.x = this->m_b1_axis_loc.y * this->m_b1_a1_loc.z - this->m_b1_axis_loc.z * this->m_b1_a1_loc.y;
  v20.y = this->m_b1_axis_loc.z * this->m_b1_a1_loc.x - this->m_b1_axis_loc.x * this->m_b1_a1_loc.z;
  v20.z = this->m_b1_axis_loc.x * this->m_b1_a1_loc.y - this->m_b1_axis_loc.y * this->m_b1_a1_loc.x;
  this->m_b1_a2_loc.x = v20.x;
  this->m_b1_a2_loc.y = v20.y;
  this->m_b1_a2_loc.z = v20.z;
  make_rotate((int)v21, (phys_mat44 *)v17, &this->m_b2_axis_loc, theta_min, 1000.0);
  v13 = phys_multiply(&v20, (const phys_mat44 *)v17, b2_ref_loc);
  v14 = phys_Unitize(&v19, v13);
  this->m_b2_ref_min_loc.x = v14->x;
  this->m_b2_ref_min_loc.y = v14->y;
  this->m_b2_ref_min_loc.z = v14->z;
  make_rotate((int)v21, (phys_mat44 *)v17, &this->m_b2_axis_loc, theta_max, 1000.0);
  v15 = phys_multiply(&v19, (const phys_mat44 *)v17, b2_ref_loc);
  v16 = phys_Unitize((phys_vec3 *)&rv.w.y, v15);
  this->m_b2_ref_max_loc.x = v16->x;
  this->m_b2_ref_max_loc.y = v16->y;
  this->m_b2_ref_max_loc.z = v16->z;
}

void __userpurge rigid_body_constraint_ragdoll::set_swivel(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_axis_loc,
        const phys_vec3 *b2_axis_loc,
        const phys_vec3 *b1_ref_loc,
        const phys_vec3 *b2_ref_loc,
        float theta_min,
        float theta_max)
{
  phys_vec3 *v9; // eax
  phys_vec3 *v10; // eax
  phys_vec3 *v11; // eax
  const phys_vec3 *v12; // eax
  phys_vec3 *v13; // eax
  const phys_vec3 *v14; // eax
  phys_vec3 *v15; // eax
  _BYTE v16[12]; // [esp+18h] [ebp-7Ch] BYREF
  phys_mat44 rv; // [esp+24h] [ebp-70h] BYREF
  phys_vec3 v18; // [esp+68h] [ebp-2Ch] BYREF
  phys_vec3 v19; // [esp+78h] [ebp-1Ch] BYREF
  unsigned int v20[3]; // [esp+88h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+94h] [ebp+0h]

  v20[0] = a2;
  v20[1] = retaddr;
  v9 = phys_Unitize(&v19, b1_axis_loc);
  this->m_b1_axis_loc.x = v9->x;
  this->m_b1_axis_loc.y = v9->y;
  this->m_b1_axis_loc.z = v9->z;
  v10 = phys_Unitize(&v19, b2_axis_loc);
  this->m_b2_axis_loc.x = v10->x;
  this->m_b2_axis_loc.y = v10->y;
  this->m_b2_axis_loc.z = v10->z;
  v11 = phys_Unitize(&v19, b1_ref_loc);
  this->m_b1_ref_loc.x = v11->x;
  this->m_b1_ref_loc.y = v11->y;
  this->m_b1_ref_loc.z = v11->z;
  this->m_flags |= 8u;
  make_rotate((int)v20, (phys_mat44 *)v16, &this->m_b2_axis_loc, theta_min, 1000.0);
  v12 = phys_multiply(&v19, (const phys_mat44 *)v16, b2_ref_loc);
  v13 = phys_Unitize(&v18, v12);
  this->m_b2_ref_min_loc.x = v13->x;
  this->m_b2_ref_min_loc.y = v13->y;
  this->m_b2_ref_min_loc.z = v13->z;
  make_rotate((int)v20, (phys_mat44 *)v16, &this->m_b2_axis_loc, theta_max, 1000.0);
  v14 = phys_multiply(&v18, (const phys_mat44 *)v16, b2_ref_loc);
  v15 = phys_Unitize((phys_vec3 *)&rv.w.y, v14);
  this->m_b2_ref_max_loc.x = v15->x;
  this->m_b2_ref_max_loc.y = v15->y;
  this->m_b2_ref_max_loc.z = v15->z;
}

void __thiscall rigid_body_constraint_ragdoll::add_joint_limit(
        rigid_body_constraint_ragdoll *this,
        const phys_vec3 *b1_ud_loc,
        float theta_limit)
{
  int savedregs; // [esp+8h] [ebp+0h] BYREF

  if ( this->m_joint_limits_count >= 2
    && _tlAssert("source/rbc_def_ragdoll.cpp", 102, "m_joint_limits_count < MAX_JOINT_LIMITS", &toastPopupTitle) )
  {
    __debugbreak();
  }
  ragdoll_joint_limit_info::set(
    &this->m_joint_limits[this->m_joint_limits_count],
    (int)&savedregs,
    b1_ud_loc,
    theta_limit);
  ++this->m_joint_limits_count;
}

double  rigid_body_constraint_ragdoll::pull_together@<st0>(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>)
{
  rigid_body *b2; // edi
  const phys_vec3 *v4; // eax
  rigid_body *b1; // ecx
  const phys_vec3 *v6; // eax
  phys_vec3 v8; // [esp-2Ch] [ebp-4Ch] BYREF
  phys_vec3 v9; // [esp-1Ch] [ebp-3Ch] BYREF
  float v10; // [esp-Ch] [ebp-2Ch]
  float v11; // [esp-8h] [ebp-28h]
  float v12; // [esp-4h] [ebp-24h]
  float v13; // [esp+10h] [ebp-10h]
  unsigned int v14[3]; // [esp+14h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+20h] [ebp+0h]

  v14[0] = a2;
  v14[1] = retaddr;
  b2 = this->b2;
  *(float *)&v4 = COERCE_FLOAT(phys_full_multiply((int)v14, &v9, &b2->m_mat, &this->m_b2_r_loc));
  b1 = this->b1;
  v13 = *(float *)&v4;
  v6 = phys_full_multiply((int)v14, &v8, &b1->m_mat, &this->m_b1_r_loc);
  v10 = v6->x - *(float *)LODWORD(v13);
  v11 = v6->y - *(float *)(LODWORD(v13) + 4);
  v12 = v6->z - *(float *)(LODWORD(v13) + 8);
  b2->m_mat.w.x = b2->m_mat.w.x + v10;
  b2->m_mat.w.y = b2->m_mat.w.y + v11;
  b2->m_mat.w.z = b2->m_mat.w.z + v12;
  v13 = fabs(b2->m_mat.w.x);
  if ( v13 > 100000.0 || (v13 = fabs(b2->m_mat.w.y), v13 > 100000.0) || (v13 = fabs(b2->m_mat.w.z), v13 > 100000.0) )
    phys_exec_debug_callback(b2);
  return (float)(v12 * v12 + v10 * v10 + v11 * v11);
}

void __userpurge rigid_body_constraint_ragdoll::setup_hinge(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        const phys_vec3 *b1_ref,
        const phys_vec3 *b2_axis,
        float delta_t)
{
  rigid_body *b2; // eax
  rigid_body *b1; // edx
  rigid_body *v8; // ecx
  pulse_sum_angular *pulse_sum_angular; // eax
  pulse_sum_angular *v10; // eax
  float v11; // [esp+18h] [ebp-4Ch] BYREF
  float v12; // [esp+1Ch] [ebp-48h]
  float v13; // [esp+20h] [ebp-44h]
  phys_vec3 b2_ref_max; // [esp+24h] [ebp-40h] BYREF
  phys_vec3 b2_ref_min; // [esp+34h] [ebp-30h] BYREF
  float v16; // [esp+50h] [ebp-14h]
  rigid_body_constraint_ragdoll *v17; // [esp+54h] [ebp-10h]
  int v18; // [esp+58h] [ebp-Ch]
  void *v19; // [esp+5Ch] [ebp-8h]
  void *retaddr; // [esp+64h] [ebp+0h]

  v18 = a2;
  v19 = retaddr;
  b2 = this->b2;
  v17 = this;
  phys_multiply((phys_vec3 *)&b2_ref_max.y, &b2->m_mat, &this->m_b2_ref_min_loc);
  b2_ref_min.y = b1_ref->y * b2_ref_max.w - b1_ref->z * b2_ref_max.z;
  b2_ref_min.z = b1_ref->z * b2_ref_max.y - b2_ref_max.w * b1_ref->x;
  b2_ref_min.w = b2_ref_max.z * b1_ref->x - b2_ref_max.y * b1_ref->y;
  v16 = b2_axis->y * b2_ref_min.z + b2_axis->x * b2_ref_min.y + b2_axis->z * b2_ref_min.w;
  if ( v16 >= -0.043618999 )
  {
    b2_ref_min.y = -b2_axis->x;
    b1 = v17->b1;
    b2_ref_min.z = -b2_axis->y;
    v8 = v17->b2;
    b2_ref_min.w = -b2_axis->z;
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          b1,
                          b1_ref,
                          v8,
                          (phys_vec3 *)&b2_ref_max.y,
                          (phys_vec3 *)&b2_ref_min.y,
                          &v17->m_ps_cache_list[6]);
    pulse_sum_angular->m_pulse_sum_min = -10000000.0;
    pulse_sum_angular->m_pulse_sum_max = 0.0;
    pulse_sum_angular::setup_vel_uni_standard(pulse_sum_angular, delta_t, 5.0);
  }
  phys_multiply((const phys_vec3 *)&v11, &v17->b2->m_mat, &v17->m_b2_ref_max_loc);
  b2_ref_min.y = b1_ref->y * v13 - b1_ref->z * v12;
  b2_ref_min.z = b1_ref->z * v11 - v13 * b1_ref->x;
  b2_ref_min.w = v12 * b1_ref->x - v11 * b1_ref->y;
  v16 = b2_axis->x * b2_ref_min.y + b2_axis->y * b2_ref_min.z + b2_axis->z * b2_ref_min.w;
  if ( v16 <= 0.043618999 )
  {
    v10 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            v17->b1,
            b1_ref,
            v17->b2,
            (const phys_vec3 *)&v11,
            b2_axis,
            &v17->m_ps_cache_list[7]);
    v10->m_pulse_sum_min = -10000000.0;
    v10->m_pulse_sum_max = 0.0;
    pulse_sum_angular::setup_vel_uni_standard(v10, delta_t, 5.0);
  }
}

void __userpurge rigid_body_constraint_ragdoll::setup_constraint(
        rigid_body_constraint_ragdoll *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b2; // edi
  rigid_body *b1; // edi
  rigid_body *v7; // eax
  double v8; // st7
  pulse_sum_angular *pulse_sum_angular; // eax
  double v10; // st7
  double v11; // st7
  rigid_body *v12; // edi
  unsigned int m_flags; // eax
  bool v14; // cc
  float *p_m_b1_ud_limit_si; // edi
  double v16; // st2
  double v17; // st7
  pulse_sum_angular *v18; // eax
  const phys_vec3 *v19; // eax
  _BYTE v20[12]; // [esp+20h] [ebp-FCh] BYREF
  phys_mat44 rv; // [esp+2Ch] [ebp-F0h] BYREF
  phys_vec3 b1_axis; // [esp+6Ch] [ebp-B0h]
  float v23; // [esp+80h] [ebp-9Ch]
  float v24; // [esp+84h] [ebp-98h]
  float v25; // [esp+88h] [ebp-94h]
  float v26; // [esp+90h] [ebp-8Ch]
  float v27; // [esp+94h] [ebp-88h]
  float v28; // [esp+98h] [ebp-84h]
  float v29; // [esp+A0h] [ebp-7Ch] BYREF
  float v30; // [esp+A4h] [ebp-78h]
  float v31; // [esp+A8h] [ebp-74h]
  phys_vec3 b1_r_; // [esp+ACh] [ebp-70h] BYREF
  phys_vec3 b1_ud; // [esp+BCh] [ebp-60h] BYREF
  float v34; // [esp+D0h] [ebp-4Ch] BYREF
  float v35; // [esp+D4h] [ebp-48h]
  float v36; // [esp+D8h] [ebp-44h]
  phys_vec3 b2_axis; // [esp+DCh] [ebp-40h] BYREF
  phys_vec3 axis; // [esp+ECh] [ebp-30h] BYREF
  phys_vec3 b1_r_length; // [esp+FCh] [ebp-20h]
  float v40; // [esp+10Ch] [ebp-10h]
  int i[2]; // [esp+110h] [ebp-Ch] BYREF
  int retaddr; // [esp+11Ch] [ebp+0h]

  i[0] = a2;
  i[1] = retaddr;
  b2 = this->b2;
  phys_multiply((phys_vec3 *)&b2_axis.y, &b2->m_mat, &this->m_b2_r_loc);
  phys_multiply((phys_vec3 *)&b1_ud.y, &this->b1->m_mat, &this->m_b1_r_loc);
  pulse_sum_constraint_solver::create_point(
    psys,
    this->b1,
    (phys_vec3 *)&b1_ud.y,
    b2,
    (phys_vec3 *)&b2_axis.y,
    this->m_ps_cache_list,
    delta_t,
    0,
    0.0,
    0.0);
  b1 = this->b1;
  phys_multiply((const phys_vec3 *)&rv.w.y, &this->b1->m_mat, &this->m_b1_axis_loc);
  phys_multiply((const phys_vec3 *)&v34, &this->b2->m_mat, &this->m_b2_axis_loc);
  if ( (this->m_flags & 0x40) != 0 )
  {
    v7 = this->b2;
    b1_r_length.w = v7->m_a_vel.y - b1->m_a_vel.y;
    b1_r_length.z = v7->m_a_vel.z - b1->m_a_vel.z;
    axis.y = v7->m_a_vel.x - b1->m_a_vel.x;
    v40 = b1_r_length.w * b1_r_length.w + axis.y * axis.y + b1_r_length.z * b1_r_length.z;
    v40 = sqrt(v40);
    if ( v40 <= 0.00009999999747378752 )
    {
      axis.y = v34;
      axis.z = v35;
      v8 = v36;
    }
    else
    {
      v40 = 1.0 / v40;
      axis.y = v40 * axis.y;
      axis.z = v40 * b1_r_length.w;
      v8 = v40 * b1_r_length.z;
    }
    axis.w = v8;
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          b1,
                          &PHYS_ZERO_VEC_82,
                          this->b2,
                          &PHYS_ZERO_VEC_82,
                          (phys_vec3 *)&axis.y,
                          &this->m_ps_cache_list[3]);
    if ( (this->m_flags & 0x200) != 0 )
    {
      v40 = 1.0 / (this->m_damp_k * delta_t);
      pulse_sum_angular->m_right_side = 0.0;
      pulse_sum_angular->m_big_dirt = 0.0;
      v10 = v40;
      pulse_sum_angular->m_cfm = v40;
      pulse_sum_angular->m_denom = v10 + pulse_sum_angular->m_denom;
      pulse_sum_angular->m_pulse_sum_min = -10000000.0;
      v11 = 10000000.0;
    }
    else
    {
      pulse_sum_angular->m_right_side = 0.0;
      pulse_sum_angular->m_big_dirt = 0.0;
      pulse_sum_angular->m_cfm = 0.0;
      v40 = this->m_damp_k * delta_t;
      v11 = v40;
      pulse_sum_angular->m_pulse_sum_min = -v40;
    }
    pulse_sum_angular->m_pulse_sum_max = v11;
  }
  if ( (this->m_flags & 4) != 0 )
  {
    v12 = this->b1;
    phys_multiply((phys_vec3 *)&b2_axis.y, &this->b1->m_mat, &this->m_b1_a2_loc);
    phys_multiply((phys_vec3 *)&b1_ud.y, &v12->m_mat, &this->m_b1_a1_loc);
    pulse_sum_constraint_solver::create_hinge(
      psys,
      v12,
      (const phys_vec3 *)&rv.w.y,
      this->b2,
      (const phys_vec3 *)&v34,
      (phys_vec3 *)&b1_ud.y,
      (phys_vec3 *)&b2_axis.y,
      &this->m_ps_cache_list[4],
      delta_t);
    phys_multiply((phys_vec3 *)&b2_axis.y, &this->b1->m_mat, &this->m_b1_ref_loc);
    rigid_body_constraint_ragdoll::setup_hinge(
      this,
      (int)i,
      psys,
      (phys_vec3 *)&b2_axis.y,
      (const phys_vec3 *)&v34,
      delta_t);
  }
  m_flags = this->m_flags;
  if ( (m_flags & 8) != 0 )
  {
    if ( (m_flags & 0x100) == 0 )
    {
      v14 = this->m_joint_limits_count <= 0;
      b1_r_length.z = 0.0;
      if ( !v14 )
      {
        LODWORD(b1_r_length.w) = &this->m_ps_cache_list[8];
        p_m_b1_ud_limit_si = &this->m_joint_limits[0].m_b1_ud_limit_si_;
        do
        {
          phys_multiply((phys_vec3 *)&b1_r_.y, &this->b1->m_mat, (const phys_vec3 *)(p_m_b1_ud_limit_si - 5));
          v40 = b1_r_.w * v36 + b1_r_.y * v34 + b1_r_.z * v35;
          v16 = v40;
          if ( p_m_b1_ud_limit_si[1] >= (double)v40 )
          {
            b1_axis.y = b1_r_.y * v16;
            b1_axis.z = b1_r_.z * v16;
            b1_axis.w = v16 * b1_r_.w;
            axis.y = v34 - b1_axis.y;
            axis.z = v35 - b1_axis.z;
            axis.w = v36 - b1_axis.w;
            v40 = axis.z * axis.z + axis.y * axis.y + axis.w * axis.w;
            v40 = sqrt(v40);
            v17 = v40;
            if ( v40 >= 0.00009999999747378752 )
            {
              v40 = *(p_m_b1_ud_limit_si - 1);
              v23 = v40 * b1_r_.y;
              v24 = b1_r_.z * v40;
              v25 = v40 * b1_r_.w;
              v40 = *p_m_b1_ud_limit_si / v17;
              v26 = axis.y * v40;
              v27 = axis.z * v40;
              v28 = v40 * axis.w;
              v29 = v26 + v23;
              v30 = v27 + v24;
              v31 = v28 + v25;
              b1_ud.y = v30 * b1_r_.w - v31 * b1_r_.z;
              b1_ud.z = v31 * b1_r_.y - b1_r_.w * v29;
              b1_ud.w = v29 * b1_r_.z - v30 * b1_r_.y;
              v40 = 1.0 / *p_m_b1_ud_limit_si;
              b2_axis.y = b1_ud.y * v40;
              b2_axis.z = b1_ud.z * v40;
              b2_axis.w = v40 * b1_ud.w;
              PHYS_ASSERT_UNIT((phys_vec3 *)&b2_axis.y);
              v18 = pulse_sum_constraint_solver::create_pulse_sum_angular(
                      psys,
                      this->b1,
                      (const phys_vec3 *)&v29,
                      this->b2,
                      (const phys_vec3 *)&v34,
                      (phys_vec3 *)&b2_axis.y,
                      (pulse_sum_cache *const)LODWORD(b1_r_length.w));
              v18->m_pulse_sum_min = -10000000.0;
              v18->m_pulse_sum_max = 0.0;
              pulse_sum_angular::setup_vel_uni_standard(v18, delta_t, 5.0);
            }
          }
          LODWORD(b1_r_length.w) += 4;
          p_m_b1_ud_limit_si += 8;
          v14 = ++LODWORD(b1_r_length.z) < this->m_joint_limits_count;
        }
        while ( v14 );
      }
    }
    make_rotate(COERCE_FLOAT(i), (phys_mat44 *)v20, (const phys_vec3 *)&rv.w.y, (const phys_vec3 *)&v34);
    phys_multiply((phys_vec3 *)&b2_axis.y, &this->b1->m_mat, &this->m_b1_ref_loc);
    v19 = phys_multiply((phys_vec3 *)&b1_ud.y, (const phys_mat44 *)v20, (phys_vec3 *)&b2_axis.y);
    rigid_body_constraint_ragdoll::setup_hinge(this, (int)i, psys, v19, (const phys_vec3 *)&v34, delta_t);
  }
}

