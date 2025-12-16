#include "rbc_def_custom.h"

const phys_vec3 * rbint::mul_L@<eax>(
        int a1@<ebp>,
        const phys_vec3 *result,
        const rigid_body *rb,
        const phys_vec3 *t)
{
  phys_vec3 v5; // [esp-20h] [ebp-2Ch] BYREF
  float v6; // [esp-10h] [ebp-1Ch]
  float v7; // [esp-Ch] [ebp-18h]
  float v8; // [esp-8h] [ebp-14h]
  int v9; // [esp+0h] [ebp-Ch]
  void *v10; // [esp+4h] [ebp-8h]
  void *retaddr; // [esp+Ch] [ebp+0h]

  v9 = a1;
  v10 = retaddr;
  v6 = rb->m_mat.x.y * t->y + rb->m_mat.x.x * t->x + rb->m_mat.x.z * t->z;
  v7 = rb->m_mat.y.y * t->y + rb->m_mat.y.x * t->x + rb->m_mat.y.z * t->z;
  v8 = rb->m_mat.z.y * t->y + t->x * rb->m_mat.z.x + rb->m_mat.z.z * t->z;
  v5.x = v6 / rb->m_inv_inertia.x;
  v5.y = v7 / rb->m_inv_inertia.y;
  v5.z = v8 / rb->m_inv_inertia.z;
  phys_multiply(result, &rb->m_mat, &v5);
  return result;
}

void __thiscall rigid_body_constraint_custom_orientation::setup_constraint(
        rigid_body_constraint_custom_orientation *this,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  double v3; // st7
  bool v6; // c0
  phys_mat44 *p_m_mat; // ecx
  phys_mat44 *v8; // edi
  pulse_sum_angular *pulse_sum_angular; // eax
  pulse_sum_angular *v10; // eax
  pulse_sum_angular *v11; // eax
  pulse_sum_angular *v12; // eax
  double v13; // st7
  double pos; // st7
  double v15; // st6
  double v16; // st5
  pulse_sum_angular *v17; // eax
  float *v18; // ebx
  double v19; // st7
  double v20; // st7
  double v21; // st6
  phys_vec3 *b2_r; // [esp+Ch] [ebp-Ch]
  float roll; // [esp+10h] [ebp-8h]
  const phys_mat44 *b2_mat; // [esp+14h] [ebp-4h]
  float b2_matb; // [esp+14h] [ebp-4h]
  const phys_mat44 *b2_mata; // [esp+14h] [ebp-4h]
  float pitchd; // [esp+20h] [ebp+8h]
  float pitche; // [esp+20h] [ebp+8h]
  float pitchf; // [esp+20h] [ebp+8h]
  float pitchg; // [esp+20h] [ebp+8h]
  float pitchh; // [esp+20h] [ebp+8h]
  float pitch; // [esp+20h] [ebp+8h]
  float pitcha; // [esp+20h] [ebp+8h]
  float pitchi; // [esp+20h] [ebp+8h]
  float pitchb; // [esp+20h] [ebp+8h]
  float pitchc; // [esp+20h] [ebp+8h]

  v3 = 0.0;
  v6 = this->m_torque_resistance_pitch_roll > 0.0;
  p_m_mat = &this->b2->m_mat;
  v8 = &this->b1->m_mat;
  b2_mat = p_m_mat;
  if ( v6 )
  {
    pitchd = this->m_torque_resistance_pitch_roll * 10.0;
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          this->b1,
                          &this->b1->m_mat.z,
                          this->b2,
                          &p_m_mat->z,
                          &this->b1->m_mat.y,
                          this->m_ps_cache_list);
    pulse_sum_angular->m_pulse_sum_min = -10000000.0;
    pulse_sum_angular->m_pulse_sum_max = 10000000.0;
    pitche = 1.0 / (pitchd * delta_t);
    pulse_sum_angular->m_right_side = 0.0;
    pulse_sum_angular->m_big_dirt = 0.0;
    pulse_sum_angular->m_cfm = pitche;
    pulse_sum_angular->m_denom = pitche + pulse_sum_angular->m_denom;
    v10 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            &v8->z,
            this->b2,
            &b2_mat->z,
            &v8->x,
            &this->m_ps_cache_list[1]);
    p_m_mat = (phys_mat44 *)b2_mat;
    v10->m_pulse_sum_min = -10000000.0;
    v10->m_pulse_sum_max = 10000000.0;
    v3 = 0.0;
    v10->m_right_side = 0.0;
    v10->m_big_dirt = 0.0;
    v10->m_cfm = pitche;
    v10->m_denom = pitche + v10->m_denom;
  }
  if ( v3 < this->m_torque_resistance_yaw )
  {
    pitchf = this->m_torque_resistance_yaw * 10.0;
    v11 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            &v8->x,
            this->b2,
            &p_m_mat->x,
            &v8->z,
            &this->m_ps_cache_list[2]);
    v11->m_pulse_sum_min = -10000000.0;
    p_m_mat = (phys_mat44 *)b2_mat;
    v11->m_pulse_sum_max = 10000000.0;
    pitchg = 1.0 / (pitchf * delta_t);
    v3 = 0.0;
    v11->m_right_side = 0.0;
    v11->m_big_dirt = 0.0;
    v11->m_cfm = pitchg;
    v11->m_denom = pitchg + v11->m_denom;
  }
  if ( this->m_active && v3 < this->m_upright_strength )
  {
    pitchh = fabs(this->b1->m_mat.y.z);
    roll = pitchh;
    pitch = fabs(this->b1->m_mat.x.z);
    if ( v3 > this->b1->m_mat.z.z )
    {
      pitch = 1.0;
      roll = 1.0;
    }
    b2_r = &p_m_mat->z;
    b2_matb = this->m_upright_strength * 30.0 * delta_t;
    pitcha = b2_matb * pitch;
    v12 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            &v8->z,
            this->b2,
            &p_m_mat->z,
            &v8->y,
            &this->m_ps_cache_list[3]);
    b2_mata = (const phys_mat44 *)v12;
    if ( this->m_no_orientation_correction )
    {
      v13 = 0.0;
      if ( v8->x.z >= 0.0 )
      {
        v12->m_pulse_sum_min = 0.0;
        v13 = pitcha;
      }
      else
      {
        v12->m_pulse_sum_min = -pitcha;
      }
      v12->m_pulse_sum_max = v13;
      pos = pulse_sum_angular::get_pos(v12);
      v15 = delta_t;
      v16 = -0.0 / delta_t;
    }
    else
    {
      v12->m_pulse_sum_min = -pitcha;
      v12->m_pulse_sum_max = pitcha;
      pos = pulse_sum_angular::get_pos(v12);
      v15 = delta_t;
      v16 = -1.0 / delta_t;
    }
    b2_mata[1].z.w = pos * v16;
    b2_mata[1].w.x = 0.0;
    b2_mata[1].w.y = 0.0;
    b2_mata[1].w.z = b2_mata[1].w.z + 0.0;
    pitchi = v15 * (this->m_upright_strength * 100.0);
    pitchb = pitchi * roll;
    v17 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            &v8->z,
            this->b2,
            b2_r,
            &v8->x,
            &this->m_ps_cache_list[4]);
    v18 = (float *)v17;
    if ( this->m_no_orientation_correction )
    {
      pitchc = pitchb * 0.5;
      v19 = 0.0;
      if ( v8->y.z <= 0.0 )
      {
        v17->m_pulse_sum_min = 0.0;
        v19 = pitchc;
      }
      else
      {
        v17->m_pulse_sum_min = -pitchc;
      }
      v17->m_pulse_sum_max = v19;
      v20 = pulse_sum_angular::get_pos(v17);
      v21 = -0.0 / delta_t;
    }
    else
    {
      v17->m_pulse_sum_min = -pitchb;
      v17->m_pulse_sum_max = pitchb;
      v20 = pulse_sum_angular::get_pos(v17);
      v21 = -1.0 / delta_t;
    }
    v18[27] = v20 * v21;
    v18[28] = 0.0;
    v18[29] = 0.0;
    v18[30] = v18[30] + 0.0;
  }
}

// local variable allocation has failed, the output may be wrong!
void __userpurge rigid_body_constraint_custom_path::setup_constraint(
        rigid_body_constraint_custom_path *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b1; // ecx
  double v6; // st6
  double v7; // st4
  double v8; // st6
  pulse_sum_normal *pulse_sum_normal; // edi
  double pos; // st7
  double v11; // st7
  pulse_sum_normal *v12; // edi
  double v13; // st7
  double v14; // st7
  rigid_body *v15; // edi
  rigid_body *b2; // eax
  float x; // ecx
  const phys_vec3 *v18; // eax
  double v19; // st7
  pulse_sum_angular *pulse_sum_angular; // edi
  double v21; // st7
  double v22; // st6
  double v23; // st7
  float v24; // ecx
  phys_vec3 *p_z; // eax
  float z; // edx
  float w; // eax
  double v28; // st6
  double v29; // st5
  double v30; // rt0
  const phys_vec3 *v31; // eax
  rigid_body *v32; // ecx
  double v33; // st7
  pulse_sum_angular *v34; // esi
  double v35; // st7
  double v36; // st6
  rigid_body *v37; // [esp-2Ch] [ebp-ACh]
  _BYTE v38[12]; // [esp-Ch] [ebp-8Ch] BYREF
  phys_vec3 b1_r; // [esp+0h] [ebp-80h] BYREF
  phys_vec3 b2_r; // [esp+10h] [ebp-70h] BYREF
  phys_vec3 b2_pt; // [esp+20h] [ebp-60h] BYREF
  phys_vec3 b1_r_; // [esp+30h] [ebp-50h] BYREF
  phys_vec3 axis; // [esp+40h] [ebp-40h] BYREF
  _BYTE b1_ud[20]; // [esp+50h] [ebp-30h] OVERLAPPED
  float v45; // [esp+64h] [ebp-1Ch]
  float y; // [esp+68h] [ebp-18h]
  double psa_cfm; // [esp+6Ch] [ebp-14h] OVERLAPPED
  unsigned int v48[2]; // [esp+74h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+80h] [ebp+0h]

  v48[0] = a2;
  v48[1] = retaddr;
  b2_pt.y = 0.0;
  b1 = this->b1;
  b2_pt.z = 0.0;
  b2_pt.w = 0.0;
  phys_multiply((const phys_vec3 *)v38, &b1->m_mat, &this->b1_r_loc);
  phys_multiply((phys_vec3 *)&b1_r.y, &this->b2->m_mat, (phys_vec3 *)&b2_pt.y);
  if ( !this->m_urb && _tlAssert("source/rbc_def_custom.cpp", 148, "m_urb", &toastPopupTitle) )
    __debugbreak();
  *((float *)&psa_cfm + 1) = 1.0 / this->b1->m_inv_mass;
  v6 = *((float *)&psa_cfm + 1);
  *((float *)&psa_cfm + 1) = psn_spring_k * *((float *)&psa_cfm + 1);
  *((float *)&psa_cfm + 1) = *((float *)&psa_cfm + 1) * delta_t;
  v7 = v6 * psn_spring_d;
  v8 = *((float *)&psa_cfm + 1) * delta_t;
  *((float *)&psa_cfm + 1) = v7;
  *((float *)&psa_cfm + 1) = delta_t * *((float *)&psa_cfm + 1);
  *((float *)&psa_cfm + 1) = 1.0 / (*((float *)&psa_cfm + 1) + v8);
  *(float *)&b1_ud[16] = v8 * *((float *)&psa_cfm + 1);
  pulse_sum_normal = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
  pulse_sum_normal::set(
    pulse_sum_normal,
    (int)v48,
    this->b1,
    (const phys_vec3 *)v38,
    this->b2,
    (phys_vec3 *)&b1_r.y,
    &PHYS_X_VEC_17,
    this->m_list_psc,
    &PHYS_ZERO_VEC_87);
  *(double *)&b1_ud[12] = -*(float *)&b1_ud[16] / delta_t;
  pos = pulse_sum_normal::get_pos(pulse_sum_normal, (int)v48);
  pulse_sum_normal->m_right_side = pos * *(double *)&b1_ud[12];
  pulse_sum_normal->m_big_dirt = 0.0;
  v11 = *((float *)&psa_cfm + 1);
  pulse_sum_normal->m_cfm = *((float *)&psa_cfm + 1);
  pulse_sum_normal->m_denom = v11 + pulse_sum_normal->m_denom;
  pulse_sum_normal->m_pulse_sum_min = -10000000.0;
  pulse_sum_normal->m_pulse_sum_max = 10000000.0;
  v12 = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
  pulse_sum_normal::set(
    v12,
    (int)v48,
    this->b1,
    (const phys_vec3 *)v38,
    this->b2,
    (phys_vec3 *)&b1_r.y,
    &PHYS_Y_VEC_17,
    &this->m_list_psc[1],
    &PHYS_ZERO_VEC_87);
  v13 = pulse_sum_normal::get_pos(v12, (int)v48);
  v12->m_right_side = v13 * *(double *)&b1_ud[12];
  v12->m_big_dirt = 0.0;
  v14 = *((float *)&psa_cfm + 1);
  v12->m_cfm = *((float *)&psa_cfm + 1);
  v12->m_denom = v14 + v12->m_denom;
  v12->m_pulse_sum_min = -10000000.0;
  v12->m_pulse_sum_max = 10000000.0;
  v15 = this->b1;
  b1_r_.y = this->b1->m_mat.x.x;
  b1_r_.z = v15->m_mat.x.y;
  b2 = this->b2;
  b1_r_.w = v15->m_mat.x.z;
  b2 = (rigid_body *)((char *)b2 + 64);
  axis.x = v15->m_mat.x.w;
  x = b2->m_last_position.x;
  y = b2->m_last_position.y;
  v45 = x;
  psa_cfm = *(double *)&b2->m_last_position.z;
  *(float *)&b1_ud[16] = x * b1_r_.y + y * b1_r_.z + *(float *)&psa_cfm * b1_r_.w;
  b2_pt.y = x * *(float *)&b1_ud[16];
  b2_pt.z = y * *(float *)&b1_ud[16];
  b2_pt.w = *(float *)&psa_cfm * *(float *)&b1_ud[16];
  axis.y = b1_r_.y - b2_pt.y;
  axis.z = b1_r_.z - b2_pt.z;
  axis.w = b1_r_.w - b2_pt.w;
  *(float *)&b1_ud[16] = axis.y * axis.y + axis.z * axis.z + axis.w * axis.w;
  *(float *)&b1_ud[16] = sqrt(*(float *)&b1_ud[16]);
  if ( *(float *)&b1_ud[16] <= 0.00009999999747378752 )
  {
    v23 = 0.0;
  }
  else
  {
    *(float *)&b1_ud[16] = 1.0 / *(float *)&b1_ud[16];
    axis.y = axis.y * *(float *)&b1_ud[16];
    axis.z = axis.z * *(float *)&b1_ud[16];
    axis.w = *(float *)&b1_ud[16] * axis.w;
    b2_pt.y = axis.w * y - axis.z * *(float *)&psa_cfm;
    b2_pt.z = *(float *)&psa_cfm * axis.y - axis.w * v45;
    b2_pt.w = v45 * axis.z - axis.y * y;
    v18 = rbint::mul_L((int)v48, (phys_vec3 *)&b2_r.y, v15, (phys_vec3 *)&b2_pt.y);
    *(float *)&b1_ud[16] = v18->y * b2_pt.z + v18->x * b2_pt.y + v18->z * b2_pt.w;
    v19 = *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = psa_spring_k_0 * *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = *(float *)&b1_ud[16] * delta_t;
    psa_cfm = *(float *)&b1_ud[16] * delta_t;
    *(float *)&b1_ud[16] = v19 * psa_spring_d_0;
    *(float *)&b1_ud[16] = delta_t * *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = 1.0 / (psa_cfm + *(float *)&b1_ud[16]);
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          this->b1,
                          (phys_vec3 *)&b1_r_.y,
                          this->b2,
                          (phys_vec3 *)&axis.y,
                          (phys_vec3 *)&b2_pt.y,
                          &this->m_list_psc[2]);
    v21 = pulse_sum_angular::get_pos(pulse_sum_angular);
    v22 = *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = psa_cfm * *(float *)&b1_ud[16];
    pulse_sum_angular->m_right_side = v21 * (-*(float *)&b1_ud[16] / delta_t);
    pulse_sum_angular->m_big_dirt = 0.0;
    v23 = 0.0;
    pulse_sum_angular->m_cfm = v22;
    pulse_sum_angular->m_denom = v22 + pulse_sum_angular->m_denom;
    pulse_sum_angular->m_pulse_sum_min = -10000000.0;
    pulse_sum_angular->m_pulse_sum_max = 10000000.0;
  }
  v24 = this->b1->m_mat.z.y;
  p_z = &this->b1->m_mat.z;
  axis.y = p_z->x;
  z = p_z->z;
  w = p_z->w;
  b2_r.y = v23;
  b2_r.z = v23;
  axis.z = v24;
  axis.w = z;
  b2_r.w = 1.0;
  *(float *)b1_ud = w;
  *(float *)&b1_ud[16] = v24 * 0.0 + axis.y * 0.0 + z;
  b2_pt.y = axis.y * *(float *)&b1_ud[16];
  b2_pt.z = v24 * *(float *)&b1_ud[16];
  b2_pt.w = *(float *)&b1_ud[16] * z;
  b1_r_.y = 0.0 - b2_pt.y;
  b1_r_.z = 0.0 - b2_pt.z;
  b1_r_.w = 1.0 - b2_pt.w;
  *(float *)&b1_ud[16] = b1_r_.y * b1_r_.y + b1_r_.z * b1_r_.z + b1_r_.w * b1_r_.w;
  *(float *)&b1_ud[16] = sqrt(*(float *)&b1_ud[16]);
  if ( *(float *)&b1_ud[16] >= 0.00009999999747378752 )
  {
    v28 = axis.y;
    v45 = axis.y * 0.5;
    y = axis.z * 0.5;
    v29 = axis.w;
    *(float *)&psa_cfm = 0.5 * axis.w;
    v30 = axis.z;
    *(float *)&b1_ud[16] = 0.8660253882408142 / *(float *)&b1_ud[16];
    axis.y = b1_r_.y * *(float *)&b1_ud[16];
    axis.z = b1_r_.z * *(float *)&b1_ud[16];
    axis.w = *(float *)&b1_ud[16] * b1_r_.w;
    b2_pt.y = axis.y + v45;
    b2_pt.z = axis.z + y;
    b2_pt.w = axis.w + *(float *)&psa_cfm;
    axis.y = b2_pt.z * v29 - b2_pt.w * v30;
    axis.z = b2_pt.w * v28 - v29 * b2_pt.y;
    axis.w = b2_pt.y * v30 - v28 * b2_pt.z;
    b1_r_.y = axis.y * 1.154700517654419;
    b1_r_.z = axis.z * 1.154700517654419;
    b1_r_.w = 1.154700517654419 * axis.w;
    PHYS_ASSERT_UNIT((phys_vec3 *)&b1_r_.y);
    v31 = rbint::mul_L((int)v48, (phys_vec3 *)&axis.y, this->b1, (phys_vec3 *)&b1_r_.y);
    v32 = this->b1;
    v37 = this->b2;
    *(float *)&b1_ud[16] = v31->y * b1_r_.z + v31->x * b1_r_.y + v31->z * b1_r_.w;
    v33 = *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = *(float *)&b1_ud[16] * psa_spring_k;
    *(float *)&b1_ud[16] = *(float *)&b1_ud[16] * delta_t;
    psa_cfm = *(float *)&b1_ud[16] * delta_t;
    *(float *)&b1_ud[16] = v33 * psa_spring_d;
    *(float *)&b1_ud[16] = delta_t * *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = 1.0 / (psa_cfm + *(float *)&b1_ud[16]);
    v34 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            v32,
            (phys_vec3 *)&b2_pt.y,
            v37,
            (phys_vec3 *)&b2_r.y,
            (phys_vec3 *)&b1_r_.y,
            &this->m_list_psc[3]);
    v34->m_pulse_sum_min = -10000000.0;
    v34->m_pulse_sum_max = 0.0;
    v35 = pulse_sum_angular::get_pos(v34);
    v36 = *(float *)&b1_ud[16];
    *(float *)&b1_ud[16] = psa_cfm * *(float *)&b1_ud[16];
    v34->m_right_side = v35 * (-*(float *)&b1_ud[16] / delta_t);
    v34->m_big_dirt = 0.0;
    v34->m_cfm = v36;
    v34->m_denom = v36 + v34->m_denom;
  }
}

