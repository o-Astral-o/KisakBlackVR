#include "rbc_def_generic.h"

const phys_vec3 *__cdecl construct_orth_ud(const phys_vec3 *result, const phys_vec3 *ud)
{
  double v2; // st7
  const phys_vec3 *v3; // eax
  float v4; // [esp-20h] [ebp-2Ch]
  float y; // [esp-20h] [ebp-2Ch]
  float v6; // [esp-1Ch] [ebp-28h]
  float x; // [esp-18h] [ebp-24h]
  double v8; // [esp-10h] [ebp-1Ch]
  float v9; // [esp-4h] [ebp-10h]
  float v10; // [esp-4h] [ebp-10h]
  float v11; // [esp-4h] [ebp-10h]
  float v12; // [esp-4h] [ebp-10h]
  float z; // [esp-4h] [ebp-10h]
  float v14; // [esp-4h] [ebp-10h]
  float v15; // [esp-4h] [ebp-10h]
  float v16; // [esp-4h] [ebp-10h]
  float v17; // [esp-4h] [ebp-10h]
  float v18; // [esp-4h] [ebp-10h]
  float v19; // [esp-4h] [ebp-10h]

  v9 = ud->y * ud->y + ud->x * ud->x + ud->z * ud->z;
  v10 = sqrt(v9);
  v11 = v10 - 1.0;
  v12 = fabs(v11);
  if ( v12 >= 0.00009999999747378752
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\old_phys_math.h",
         298,
         "fabsf(nud - 1.0f) < .0001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  result->x = 0.0;
  z = ud->z;
  v2 = z;
  result->y = z;
  v14 = -ud->y;
  result->z = v14;
  v8 = 0.0 * 0.0;
  v15 = v2 * v2 + 0.0 * 0.0 + v14 * v14;
  v16 = sqrt(v15);
  if ( v16 < 0.00009999999747378752 )
  {
    v4 = -ud->z;
    x = ud->x;
    result->x = v4;
    result->y = 0.0;
    result->z = x;
    v17 = x * x + v4 * v4 + v8;
    v16 = sqrt(v17);
    if ( v16 < 0.00009999999747378752 )
    {
      y = ud->y;
      v6 = -ud->x;
      result->x = y;
      result->y = v6;
      result->z = 0.0;
      v18 = y * y + v6 * v6 + v8;
      v16 = sqrt(v18);
      if ( v16 < 0.00009999999747378752 )
      {
        if ( _tlAssert("c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\old_phys_math.h", 313, "0", "not possible") )
          __debugbreak();
      }
    }
  }
  v3 = result;
  v19 = 1.0 / v16;
  result->x = result->x * v19;
  result->y = v19 * result->y;
  result->z = v19 * result->z;
  return v3;
}

void __cdecl PHYS_ASSERT_UNIT(const phys_vec3 *v)
{
  float va; // [esp+8h] [ebp+8h]
  float vb; // [esp+8h] [ebp+8h]
  float vc; // [esp+8h] [ebp+8h]
  float vd; // [esp+8h] [ebp+8h]

  va = v->y * v->y + v->x * v->x + v->z * v->z;
  vb = sqrt(va);
  vc = vb - 1.0;
  vd = fabs(vc);
  if ( vd >= 0.001 )
  {
    if ( _tlAssert(
           "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
           420,
           "fabsf(nv - 1.0f) < 0.001f",
           &toastPopupTitle) )
    {
      __debugbreak();
    }
  }
}

void __cdecl PHYS_ASSERT_ORTHOGONAL(const phys_vec3 *v1, const phys_vec3 *v2)
{
  float v1a; // [esp+8h] [ebp+8h]
  float v1b; // [esp+8h] [ebp+8h]

  v1a = v1->y * v2->y + v1->x * v2->x + v1->z * v2->z;
  v1b = fabs(v1a);
  if ( v1b >= 0.001 )
  {
    if ( _tlAssert(
           "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
           425,
           "fabsf(d) < 0.001f",
           &toastPopupTitle) )
    {
      __debugbreak();
    }
  }
}

void __cdecl PHYS_ASSERT_ORTHONORMAL(const phys_mat44 *m)
{
  float dyz; // [esp+4h] [ebp-14h]
  float dxz; // [esp+8h] [ebp-10h]
  float dxy; // [esp+Ch] [ebp-Ch]
  float nz; // [esp+10h] [ebp-8h]
  float ny; // [esp+14h] [ebp-4h]
  float ma; // [esp+20h] [ebp+8h]
  float mb; // [esp+20h] [ebp+8h]
  float mc; // [esp+20h] [ebp+8h]
  float md; // [esp+20h] [ebp+8h]
  float me; // [esp+20h] [ebp+8h]
  float mf; // [esp+20h] [ebp+8h]
  float mg; // [esp+20h] [ebp+8h]
  float mh; // [esp+20h] [ebp+8h]
  float mi; // [esp+20h] [ebp+8h]
  float mj; // [esp+20h] [ebp+8h]
  float mk; // [esp+20h] [ebp+8h]
  float ml; // [esp+20h] [ebp+8h]
  float mm; // [esp+20h] [ebp+8h]
  float mn; // [esp+20h] [ebp+8h]
  float mo; // [esp+20h] [ebp+8h]

  ma = m->y.y * m->y.y + m->y.x * m->y.x + m->y.z * m->y.z;
  mb = sqrt(ma);
  ny = mb;
  mc = m->z.y * m->z.y + m->z.x * m->z.x + m->z.z * m->z.z;
  md = sqrt(mc);
  nz = md;
  dxy = m->y.y * m->x.y + m->y.x * m->x.x + m->y.z * m->x.z;
  dxz = m->z.y * m->x.y + m->z.x * m->x.x + m->z.z * m->x.z;
  dyz = m->y.y * m->z.y + m->z.x * m->y.x + m->y.z * m->z.z;
  me = m->x.z * m->x.z + m->x.x * m->x.x + m->x.y * m->x.y;
  mf = sqrt(me);
  mg = mf - 1.0;
  mh = fabs(mg);
  if ( mh >= 0.001
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
         435,
         "fabsf(nx - 1.0f) < 0.001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  mi = ny - 1.0;
  mj = fabs(mi);
  if ( mj >= 0.001
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
         436,
         "fabsf(ny - 1.0f) < 0.001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  mk = nz - 1.0;
  ml = fabs(mk);
  if ( ml >= 0.001
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
         437,
         "fabsf(nz - 1.0f) < 0.001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  mm = fabs(dxy);
  if ( mm >= 0.001
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
         438,
         "fabsf(dxy) < 0.001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  mn = fabs(dxz);
  if ( mn >= 0.001
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
         439,
         "fabsf(dxz) < 0.001f",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  mo = fabs(dyz);
  if ( mo >= 0.001 )
  {
    if ( _tlAssert(
           "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_math.h",
           440,
           "fabsf(dyz) < 0.001f",
           &toastPopupTitle) )
    {
      __debugbreak();
    }
  }
}

const phys_vec3 *__cdecl rbint::sub_pos(const phys_vec3 *result, rigid_body *const b, const phys_vec3 *p)
{
  const phys_vec3 *v3; // eax

  v3 = result;
  result->x = p->x - b->m_mat.w.x;
  result->y = p->y - b->m_mat.w.y;
  result->z = p->z - b->m_mat.w.z;
  return v3;
}

void __thiscall rigid_body_constraint_point::set(
        rigid_body_constraint_point *this,
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

void __thiscall rigid_body_constraint_point::epilog_vel_constraint(rigid_body_constraint_point *this, float __formal)
{
  this->m_stress = this->m_ps_cache_list[1].m_pulse_sum * this->m_ps_cache_list[1].m_pulse_sum
                 + this->m_ps_cache_list[0].m_pulse_sum * this->m_ps_cache_list[0].m_pulse_sum
                 + this->m_ps_cache_list[2].m_pulse_sum * this->m_ps_cache_list[2].m_pulse_sum;
}

void __thiscall rigid_body_constraint_distance::set(
        rigid_body_constraint_distance *this,
        const phys_vec3 *b1_r_loc,
        const phys_vec3 *b2_r_loc,
        float min_distance,
        float max_distance)
{
  this->m_b1_r_loc.x = b1_r_loc->x;
  this->m_b1_r_loc.y = b1_r_loc->y;
  this->m_b1_r_loc.z = b1_r_loc->z;
  this->m_b2_r_loc.x = b2_r_loc->x;
  this->m_b2_r_loc.y = b2_r_loc->y;
  this->m_b2_r_loc.z = b2_r_loc->z;
  this->m_flags = 1;
  this->m_min_distance = min_distance;
  this->m_max_distance = max_distance;
  this->m_next_max_distance = max_distance;
  this->m_max_distance_vel = 0.0;
  this->m_damp_coef = 0.0;
}

void __thiscall rigid_body_constraint_distance::outer_prolog_update(
        rigid_body_constraint_distance *this,
        float delta_t)
{
  this->m_max_distance_vel = (this->m_next_max_distance - this->m_max_distance) / delta_t;
}

void __thiscall rigid_body_constraint_distance::inner_update(rigid_body_constraint_distance *this, float delta_t)
{
  this->m_max_distance = this->m_max_distance_vel * delta_t + this->m_max_distance;
}

void __thiscall rigid_body_constraint_distance::outer_epilog_update(
        rigid_body_constraint_distance *this,
        const float __formal)
{
  this->m_max_distance = this->m_next_max_distance;
}

void __thiscall rigid_body_constraint_angular_actuator::set(
        rigid_body_constraint_angular_actuator *this,
        float power,
        const phys_mat44 *target_mat)
{
  this->m_power = power;
  this->m_power_scale = 1.0;
  this->m_target_mat.x.x = target_mat->x.x;
  this->m_target_mat.x.y = target_mat->x.y;
  this->m_target_mat.x.z = target_mat->x.z;
  this->m_target_mat.y.x = target_mat->y.x;
  this->m_target_mat.y.y = target_mat->y.y;
  this->m_target_mat.y.z = target_mat->y.z;
  this->m_target_mat.z.x = target_mat->z.x;
  this->m_target_mat.z.y = target_mat->z.y;
  this->m_target_mat.z.z = target_mat->z.z;
  this->m_target_mat.w.x = target_mat->w.x;
  this->m_target_mat.w.y = target_mat->w.y;
  this->m_target_mat.w.z = target_mat->w.z;
  this->m_next_target_mat.x.x = target_mat->x.x;
  this->m_next_target_mat.x.y = target_mat->x.y;
  this->m_next_target_mat.x.z = target_mat->x.z;
  this->m_next_target_mat.y.x = target_mat->y.x;
  this->m_next_target_mat.y.y = target_mat->y.y;
  this->m_next_target_mat.y.z = target_mat->y.z;
  this->m_next_target_mat.z.x = target_mat->z.x;
  this->m_next_target_mat.z.y = target_mat->z.y;
  this->m_next_target_mat.z.z = target_mat->z.z;
  this->m_next_target_mat.w.x = target_mat->w.x;
  this->m_next_target_mat.w.y = target_mat->w.y;
  this->m_next_target_mat.w.z = target_mat->w.z;
  this->m_a_vel.x = 0.0;
  this->m_a_vel.y = 0.0;
  this->m_a_vel.z = 0.0;
  this->m_enabled = 1;
  PHYS_ASSERT_ORTHONORMAL(&this->m_target_mat);
}

void __userpurge rigid_body_constraint_angular_actuator::outer_prolog_update(
        rigid_body_constraint_angular_actuator *this@<ecx>,
        float a2@<ebp>,
        float delta_t)
{
  int v3; // [esp+Ch] [ebp-1Ch] BYREF
  phys_vec3 t_vel; // [esp+18h] [ebp-10h] BYREF
  float retaddr; // [esp+28h] [ebp+0h]

  t_vel.y = a2;
  t_vel.z = retaddr;
  this->m_target_mat.w.x = 0.0;
  this->m_target_mat.w.y = 0.0;
  this->m_target_mat.w.z = 0.0;
  this->m_next_target_mat.w.x = 0.0;
  this->m_next_target_mat.w.y = 0.0;
  this->m_next_target_mat.w.z = 0.0;
  nuge::calc_velocities(
    COERCE_FLOAT((phys_vec3 *)&t_vel.y),
    &this->m_target_mat,
    &this->m_next_target_mat,
    delta_t,
    (phys_vec3 *)&v3,
    &this->m_a_vel);
}

void __thiscall rigid_body_constraint_angular_actuator::outer_epilog_update(
        rigid_body_constraint_angular_actuator *this,
        const float __formal)
{
  this->m_target_mat.x.x = this->m_next_target_mat.x.x;
  this->m_target_mat.x.y = this->m_next_target_mat.x.y;
  this->m_target_mat.x.z = this->m_next_target_mat.x.z;
  this->m_target_mat.y.x = this->m_next_target_mat.y.x;
  this->m_target_mat.y.y = this->m_next_target_mat.y.y;
  this->m_target_mat.y.z = this->m_next_target_mat.y.z;
  this->m_target_mat.z.x = this->m_next_target_mat.z.x;
  this->m_target_mat.z.y = this->m_next_target_mat.z.y;
  this->m_target_mat.z.z = this->m_next_target_mat.z.z;
  this->m_target_mat.w.x = this->m_next_target_mat.w.x;
  this->m_target_mat.w.y = this->m_next_target_mat.w.y;
  this->m_target_mat.w.z = this->m_next_target_mat.w.z;
}

double __thiscall rigid_body_constraint_upright::calc_current_lean_angle(rigid_body_constraint_upright *this)
{
  float v2; // [esp-Ch] [ebp-2Ch]
  float v3; // [esp-8h] [ebp-28h]
  float v4; // [esp-4h] [ebp-24h]
  float b2_up_axis_12; // [esp+Ch] [ebp-14h]
  float v7; // [esp+10h] [ebp-10h]
  float v8; // [esp+10h] [ebp-10h]

  v2 = this->b1->m_mat.x.y * this->m_b2_up_axis_loc.y
     + this->b1->m_mat.x.x * this->m_b2_up_axis_loc.x
     + this->b1->m_mat.x.z * this->m_b2_up_axis_loc.z;
  v3 = this->b1->m_mat.y.y * this->m_b2_up_axis_loc.y
     + this->m_b2_up_axis_loc.x * this->b1->m_mat.y.x
     + this->b1->m_mat.y.z * this->m_b2_up_axis_loc.z;
  v4 = this->b1->m_mat.z.y * this->m_b2_up_axis_loc.y
     + this->m_b2_up_axis_loc.x * this->b1->m_mat.z.x
     + this->b1->m_mat.z.z * this->m_b2_up_axis_loc.z;
  b2_up_axis_12 = this->m_b1_up_axis_loc.z * v4 + this->m_b1_up_axis_loc.x * v2 + this->m_b1_up_axis_loc.y * v3;
  v7 = v2 * this->m_b1_right_axis_loc.x + v3 * this->m_b1_right_axis_loc.y + v4 * this->m_b1_right_axis_loc.z;
  v8 = -v7;
  if ( v8 * v8 + b2_up_axis_12 * b2_up_axis_12 <= 0.000000009999999051046871 )
    return 0.0;
  return (float)atan2(v8, b2_up_axis_12);
}

const phys_vec3 *__thiscall rigid_body_constraint_upright::calc_b1_lean_axis_loc(
        rigid_body_constraint_upright *this,
        const phys_vec3 *result,
        float lean_angle)
{
  const phys_vec3 *v3; // eax
  float v4; // [esp-30h] [ebp-3Ch]
  float v5; // [esp-2Ch] [ebp-38h]
  float v6; // [esp-28h] [ebp-34h]
  float v7; // [esp-20h] [ebp-2Ch]
  float v8; // [esp-1Ch] [ebp-28h]
  float v9; // [esp-18h] [ebp-24h]
  float v10; // [esp-4h] [ebp-10h]
  float v11; // [esp-4h] [ebp-10h]

  v10 = sin(lean_angle);
  v4 = this->m_b1_right_axis_loc.x * v10;
  v5 = this->m_b1_right_axis_loc.y * v10;
  v6 = v10 * this->m_b1_right_axis_loc.z;
  v11 = cos(lean_angle);
  v3 = result;
  v7 = this->m_b1_up_axis_loc.x * v11;
  v8 = this->m_b1_up_axis_loc.y * v11;
  v9 = v11 * this->m_b1_up_axis_loc.z;
  result->x = v7 - v4;
  result->y = v8 - v5;
  result->z = v9 - v6;
  return v3;
}

void __userpurge rigid_body_constraint_hinge::set(
        rigid_body_constraint_hinge *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_r_loc,
        const phys_vec3 *b2_r_loc,
        const phys_vec3 *b1_axis_loc,
        const phys_vec3 *b2_axis_loc,
        const phys_vec3 *b1_ref_loc,
        const phys_vec3 *b2_ref_loc,
        float theta_min,
        float theta_max,
        float damp_k)
{
  phys_vec3 *v12; // eax
  phys_vec3 *p_m_b1_axis_loc; // edi
  phys_vec3 *v14; // eax
  phys_vec3 *v15; // eax
  double y; // st7
  const phys_vec3 *v17; // eax
  double v18; // st7
  double v19; // st7
  const phys_vec3 *v20; // ecx
  double v21; // st6
  const phys_vec3 *v22; // eax
  phys_vec3 *v23; // eax
  const phys_vec3 *v24; // eax
  phys_vec3 *v25; // eax
  const phys_vec3 *v26; // esi
  _BYTE v27[12]; // [esp+18h] [ebp-9Ch] BYREF
  phys_mat44 rv; // [esp+24h] [ebp-90h] BYREF
  phys_vec3 v29; // [esp+68h] [ebp-4Ch] BYREF
  const phys_vec3 *p_m_b1_ref_loc; // [esp+7Ch] [ebp-38h]
  const phys_vec3 *p_m_b2_ref_max_loc; // [esp+80h] [ebp-34h]
  const phys_vec3 *p_m_b2_ref_min_loc; // [esp+84h] [ebp-30h]
  phys_vec3 v33; // [esp+88h] [ebp-2Ch] BYREF
  const phys_vec3 *p_m_b1_a1_loc; // [esp+9Ch] [ebp-18h]
  const phys_vec3 *p_m_b1_a2_loc; // [esp+A0h] [ebp-14h]
  const phys_vec3 *p_m_b2_axis_loc; // [esp+A4h] [ebp-10h]
  unsigned int v37[3]; // [esp+A8h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+B4h] [ebp+0h]

  v37[0] = a2;
  v37[1] = retaddr;
  this->m_flags = 0;
  this->m_b1_r_loc.x = b1_r_loc->x;
  this->m_b1_r_loc.y = b1_r_loc->y;
  this->m_b1_r_loc.z = b1_r_loc->z;
  this->m_b2_r_loc.x = b2_r_loc->x;
  this->m_b2_r_loc.y = b2_r_loc->y;
  this->m_b2_r_loc.z = b2_r_loc->z;
  v12 = phys_Unitize(&v33, b1_axis_loc);
  this->m_b1_axis_loc.x = v12->x;
  p_m_b1_axis_loc = &this->m_b1_axis_loc;
  this->m_b1_axis_loc.y = v12->y;
  this->m_b1_axis_loc.z = v12->z;
  v14 = phys_Unitize(&v33, b2_axis_loc);
  this->m_b2_axis_loc.x = v14->x;
  p_m_b2_axis_loc = &this->m_b2_axis_loc;
  this->m_b2_axis_loc.y = v14->y;
  this->m_b2_axis_loc.z = v14->z;
  v15 = phys_Unitize(&v33, b1_ref_loc);
  this->m_b1_ref_loc.x = v15->x;
  y = v15->y;
  p_m_b1_ref_loc = &this->m_b1_ref_loc;
  this->m_b1_ref_loc.y = y;
  this->m_b1_ref_loc.z = v15->z;
  v17 = construct_orth_ud(&v33, &this->m_b1_axis_loc);
  this->m_b1_a1_loc.x = v17->x;
  v18 = v17->y;
  p_m_b1_a1_loc = &this->m_b1_a1_loc;
  this->m_b1_a1_loc.y = v18;
  this->m_b1_a1_loc.z = v17->z;
  v33.x = this->m_b1_axis_loc.y * this->m_b1_a1_loc.z - this->m_b1_axis_loc.z * this->m_b1_a1_loc.y;
  v33.y = this->m_b1_a1_loc.x * this->m_b1_axis_loc.z - this->m_b1_a1_loc.z * this->m_b1_axis_loc.x;
  v19 = this->m_b1_a1_loc.y * this->m_b1_axis_loc.x;
  v20 = p_m_b2_axis_loc;
  v21 = this->m_b1_a1_loc.x * this->m_b1_axis_loc.y;
  p_m_b1_a2_loc = &this->m_b1_a2_loc;
  v33.z = v19 - v21;
  this->m_b1_a2_loc.x = v33.x;
  this->m_b1_a2_loc.y = v33.y;
  this->m_b1_a2_loc.z = v33.z;
  make_rotate((int)v37, (phys_mat44 *)v27, v20, theta_min, 1000.0);
  v22 = phys_multiply(&v33, (const phys_mat44 *)v27, b2_ref_loc);
  v23 = phys_Unitize(&v29, v22);
  this->m_b2_ref_min_loc.x = v23->x;
  this->m_b2_ref_min_loc.y = v23->y;
  p_m_b2_ref_min_loc = &this->m_b2_ref_min_loc;
  this->m_b2_ref_min_loc.z = v23->z;
  make_rotate((int)v37, (phys_mat44 *)v27, p_m_b2_axis_loc, theta_max, 1000.0);
  v24 = phys_multiply(&v29, (const phys_mat44 *)v27, b2_ref_loc);
  v25 = phys_Unitize((phys_vec3 *)&rv.w.y, v24);
  this->m_b2_ref_max_loc.x = v25->x;
  this->m_b2_ref_max_loc.y = v25->y;
  p_m_b2_ref_max_loc = &this->m_b2_ref_max_loc;
  this->m_b2_ref_max_loc.z = v25->z;
  this->m_damp_k = damp_k;
  PHYS_ASSERT_UNIT(&this->m_b1_axis_loc);
  PHYS_ASSERT_UNIT(p_m_b2_axis_loc);
  v26 = p_m_b1_ref_loc;
  PHYS_ASSERT_UNIT(p_m_b1_ref_loc);
  PHYS_ASSERT_UNIT(p_m_b1_a1_loc);
  PHYS_ASSERT_UNIT(p_m_b1_a2_loc);
  PHYS_ASSERT_UNIT(p_m_b2_ref_min_loc);
  PHYS_ASSERT_UNIT(p_m_b2_ref_max_loc);
  PHYS_ASSERT_ORTHOGONAL(p_m_b1_axis_loc, v26);
  PHYS_ASSERT_ORTHOGONAL(p_m_b1_a1_loc, p_m_b1_a2_loc);
}

void __userpurge rigid_body_constraint_angular_actuator::inner_update(
        rigid_body_constraint_angular_actuator *this@<ecx>,
        float a2@<ebp>,
        float delta_t)
{
  _BYTE v4[12]; // [esp+18h] [ebp-4Ch] BYREF
  phys_mat44 rv; // [esp+24h] [ebp-40h] BYREF
  float retaddr; // [esp+64h] [ebp+0h]

  rv.w.y = a2;
  rv.w.z = retaddr;
  make_rotate((int)&rv.w.y, (phys_mat44 *)v4, &this->m_a_vel, delta_t, 1000.0);
  phys_multiply_mat((int)&rv.w.y, &this->m_target_mat, (const phys_mat44 *)v4, &this->m_target_mat);
}

void __thiscall rigid_body_constraint_upright::epilog_vel_constraint(
        rigid_body_constraint_upright *this,
        float delta_t)
{
  if ( this->m_enabled )
  {
    this->m_lean_angle = rigid_body_constraint_upright::calc_current_lean_angle(this);
    this->m_lean_angle_calc_delta_t = this->m_lean_angle_calc_delta_t + delta_t;
  }
}

void __userpurge rigid_body_constraint_upright::update_lean_axis(
        rigid_body_constraint_upright *this@<ecx>,
        int a2@<ebp>,
        const phys_vec3 *b1_lean_center,
        const phys_vec3 *b1_lean_axis_loc)
{
  phys_vec3 *p_m_b1_lean_axis_loc; // edi
  float x; // eax
  float z; // edx
  const phys_vec3 *v8; // eax
  double v9; // st7
  phys_mat44 *p_m_mat; // eax
  rigid_body *b1; // esi
  _BYTE v12[12]; // [esp-Ch] [ebp-7Ch] BYREF
  phys_mat44 lean_mat; // [esp+0h] [ebp-70h] BYREF
  phys_vec3 b1_lean_axis; // [esp+40h] [ebp-30h] BYREF
  phys_vec3 b2_up_axis; // [esp+50h] [ebp-20h]
  float v16; // [esp+60h] [ebp-10h]
  unsigned int v17[2]; // [esp+64h] [ebp-Ch] BYREF
  _UNKNOWN *retaddr; // [esp+70h] [ebp+0h]

  v17[0] = a2;
  v17[1] = retaddr;
  this->m_b1_lean_axis_loc.x = b1_lean_axis_loc->x;
  p_m_b1_lean_axis_loc = &this->m_b1_lean_axis_loc;
  this->m_b1_lean_axis_loc.y = b1_lean_axis_loc->y;
  this->m_b1_lean_axis_loc.z = b1_lean_axis_loc->z;
  if ( this->m_enabled )
  {
    LODWORD(b2_up_axis.w) = &this->b1->m_mat;
    phys_multiply(
      (const phys_vec3 *)&lean_mat.w.y,
      (const phys_mat44 *)LODWORD(b2_up_axis.w),
      &this->m_b1_forward_axis_loc);
    x = this->m_b2_up_axis_loc.x;
    z = this->m_b2_up_axis_loc.z;
    b1_lean_axis.z = this->m_b2_up_axis_loc.y;
    b1_lean_axis.y = x;
    b1_lean_axis.w = z;
    b2_up_axis.x = this->m_b2_up_axis_loc.w;
    v16 = lean_mat.w.y * x + lean_mat.w.z * b1_lean_axis.z + lean_mat.w.w * z;
    lean_mat.w.y = lean_mat.w.y * v16;
    lean_mat.w.z = lean_mat.w.z * v16;
    lean_mat.w.w = lean_mat.w.w * v16;
    b1_lean_axis.y = x - lean_mat.w.y;
    b1_lean_axis.z = b1_lean_axis.z - lean_mat.w.z;
    b1_lean_axis.w = z - lean_mat.w.w;
    v16 = b1_lean_axis.z * b1_lean_axis.z + b1_lean_axis.y * b1_lean_axis.y + b1_lean_axis.w * b1_lean_axis.w;
    v16 = sqrt(v16);
    if ( v16 > 0.0000099999997 )
    {
      v16 = 1.0 / v16;
      b1_lean_axis.y = v16 * b1_lean_axis.y;
      b1_lean_axis.z = b1_lean_axis.z * v16;
      b1_lean_axis.w = v16 * b1_lean_axis.w;
      phys_multiply((const phys_vec3 *)&lean_mat.w.y, (const phys_mat44 *)LODWORD(b2_up_axis.w), p_m_b1_lean_axis_loc);
      make_rotate(COERCE_FLOAT(v17), (phys_mat44 *)v12, (const phys_vec3 *)&lean_mat.w.y, (phys_vec3 *)&b1_lean_axis.y);
      v8 = phys_multiply((phys_vec3 *)&b1_lean_axis.y, (const phys_mat44 *)v12, b1_lean_center);
      lean_mat.w.y = b1_lean_center->x - v8->x;
      lean_mat.w.z = b1_lean_center->y - v8->y;
      v9 = b1_lean_center->z - v8->z;
      p_m_mat = &this->b1->m_mat;
      lean_mat.w.w = v9;
      lean_mat.z.y = lean_mat.w.y;
      lean_mat.z.z = lean_mat.w.z;
      lean_mat.z.w = lean_mat.w.w;
      phys_full_multiply_mat((int)v17, p_m_mat, (const phys_mat44 *)v12, p_m_mat);
      b1 = this->b1;
      b2_up_axis.w = fabs(b1->m_mat.w.x);
      if ( b2_up_axis.w > 100000.0
        || (b2_up_axis.w = fabs(b1->m_mat.w.y), b2_up_axis.w > 100000.0)
        || (b2_up_axis.w = fabs(b1->m_mat.w.z), b2_up_axis.w > 100000.0) )
      {
        phys_exec_debug_callback(b1);
      }
    }
  }
}

void __userpurge rigid_body_constraint_point::setup_constraint(
        rigid_body_constraint_point *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b2; // edi
  phys_vec3 v6; // [esp+20h] [ebp-3Ch] BYREF
  phys_vec3 v7; // [esp+30h] [ebp-2Ch] BYREF
  rigid_body *b1; // [esp+4Ch] [ebp-10h]
  int v9; // [esp+50h] [ebp-Ch]
  void *v10; // [esp+54h] [ebp-8h]
  void *retaddr; // [esp+5Ch] [ebp+0h]

  v9 = a2;
  v10 = retaddr;
  b2 = this->b2;
  phys_multiply(&v7, &b2->m_mat, &this->m_b2_r_loc);
  b1 = this->b1;
  phys_multiply(&v6, &b1->m_mat, &this->m_b1_r_loc);
  pulse_sum_constraint_solver::create_point(
    psys,
    b1,
    &v6,
    b2,
    &v7,
    this->m_ps_cache_list,
    delta_t,
    this->m_spring_enabled,
    this->m_spring_k,
    this->m_damp_k);
}

void __userpurge rigid_body_constraint_hinge::setup_constraint(
        rigid_body_constraint_hinge *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b2; // edi
  phys_mat44 *p_m_mat; // edi
  pulse_sum_angular *pulse_sum_angular; // eax
  double v8; // st7
  phys_mat44 *v9; // edi
  double w; // st7
  unsigned int m_flags; // ecx
  double z; // st6
  double v13; // st5
  double v14; // st4
  double v15; // st2
  double v16; // st5
  unsigned int v17; // ecx
  double v18; // st2
  double v19; // st4
  double v20; // st3
  unsigned int v21; // ecx
  double v22; // st2
  rigid_body *v23; // eax
  pulse_sum_angular *v24; // eax
  pulse_sum_angular *v25; // eax
  _BYTE v26[12]; // [esp+20h] [ebp-8Ch] BYREF
  phys_vec3 b1_axis; // [esp+2Ch] [ebp-80h] BYREF
  phys_vec3 v28; // [esp+40h] [ebp-6Ch] BYREF
  float v29; // [esp+50h] [ebp-5Ch] BYREF
  float v30; // [esp+54h] [ebp-58h]
  float v31; // [esp+58h] [ebp-54h]
  phys_vec3 b1_ref; // [esp+5Ch] [ebp-50h] BYREF
  phys_vec3 b2_axis; // [esp+6Ch] [ebp-40h] BYREF
  phys_vec3 b2_ref_max; // [esp+7Ch] [ebp-30h] BYREF
  float v35; // [esp+9Ch] [ebp-10h]
  int v36; // [esp+A0h] [ebp-Ch]
  void *v37; // [esp+A4h] [ebp-8h]
  void *retaddr; // [esp+ACh] [ebp+0h]

  v36 = a2;
  v37 = retaddr;
  if ( (this->m_flags & 0x10) == 0 )
  {
    b2 = this->b2;
    phys_multiply(&v28, &b2->m_mat, &this->m_b2_r_loc);
    phys_multiply((phys_vec3 *)&b1_axis.y, &this->b1->m_mat, &this->m_b1_r_loc);
    pulse_sum_constraint_solver::create_point(
      psys,
      this->b1,
      (phys_vec3 *)&b1_axis.y,
      b2,
      &v28,
      this->m_ps_cache,
      delta_t,
      0,
      0.0,
      0.0);
  }
  p_m_mat = &this->b1->m_mat;
  phys_multiply((const phys_vec3 *)v26, p_m_mat, &this->m_b1_axis_loc);
  phys_multiply((phys_vec3 *)&b1_ref.y, &this->b2->m_mat, &this->m_b2_axis_loc);
  phys_multiply((phys_vec3 *)&b1_axis.y, p_m_mat, &this->m_b1_a2_loc);
  phys_multiply(&v28, p_m_mat, &this->m_b1_a1_loc);
  pulse_sum_constraint_solver::create_hinge(
    psys,
    this->b1,
    (const phys_vec3 *)v26,
    this->b2,
    (phys_vec3 *)&b1_ref.y,
    &v28,
    (phys_vec3 *)&b1_axis.y,
    &this->m_ps_cache[4],
    delta_t);
  if ( this->m_damp_k > 0.0000099999997 )
  {
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          this->b1,
                          &PHYS_ZERO_VEC_74,
                          this->b2,
                          &PHYS_ZERO_VEC_74,
                          (phys_vec3 *)&b1_ref.y,
                          &this->m_ps_cache[3]);
    pulse_sum_angular->m_right_side = 0.0;
    pulse_sum_angular->m_big_dirt = 0.0;
    pulse_sum_angular->m_cfm = 0.0;
    v35 = delta_t * this->m_damp_k;
    v8 = v35;
    pulse_sum_angular->m_pulse_sum_min = -v35;
    pulse_sum_angular->m_pulse_sum_max = v8;
  }
  phys_multiply((const phys_vec3 *)&v29, &this->b1->m_mat, &this->m_b1_ref_loc);
  v9 = &this->b2->m_mat;
  phys_multiply((phys_vec3 *)&b2_ref_max.y, v9, &this->m_b2_ref_min_loc);
  phys_multiply((phys_vec3 *)&b2_axis.y, v9, &this->m_b2_ref_max_loc);
  w = b1_ref.w;
  m_flags = this->m_flags;
  z = b1_ref.z;
  v13 = v30;
  v14 = v30;
  if ( (m_flags & 8) != 0 )
  {
    v35 = b2_ref_max.y * v29 + v14 * b2_ref_max.z + v31 * b2_ref_max.w;
    v15 = v13 * b2_axis.z;
    v16 = v35;
    v35 = v29 * b2_axis.y + v15 + v31 * b2_axis.w;
    if ( v35 > v16 )
    {
      this->m_flags = m_flags & 0xFFFFFFFC | 2;
    }
    else
    {
      v17 = m_flags | 1;
      this->m_flags = v17;
      this->m_flags = v17 & 0xFFFFFFFD;
    }
  }
  else
  {
    v18 = v14 * b2_ref_max.w - v31 * b2_ref_max.z;
    v19 = v31;
    v28.x = v18;
    v20 = v29;
    v28.y = v31 * b2_ref_max.y - b2_ref_max.w * v29;
    v28.z = v29 * b2_ref_max.z - v13 * b2_ref_max.y;
    v35 = z * v28.y + v28.x * b1_ref.y + w * v28.z;
    if ( v35 < -0.043618999 )
      v21 = m_flags & 0xFFFFFFFE;
    else
      v21 = m_flags | 1;
    v22 = b2_axis.w;
    this->m_flags = v21;
    v28.x = v22 * v13 - b2_axis.z * v19;
    v28.y = v19 * b2_axis.y - b2_axis.w * v20;
    v28.z = v20 * b2_axis.z - b2_axis.y * v13;
    v35 = v28.y * z + v28.x * b1_ref.y + v28.z * w;
    if ( v35 > 0.043618999 )
      this->m_flags &= ~2u;
    else
      this->m_flags |= 2u;
  }
  if ( (this->m_flags & 1) != 0 )
  {
    v28.x = -b1_ref.y;
    v23 = this->b2;
    v28.y = -z;
    v28.z = -w;
    v24 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            (const phys_vec3 *)&v29,
            v23,
            (phys_vec3 *)&b2_ref_max.y,
            &v28,
            &this->m_ps_cache[6]);
    v24->m_pulse_sum_min = -10000000.0;
    v24->m_pulse_sum_max = 0.0;
    pulse_sum_angular::setup_vel_uni_standard(v24, delta_t, 5.0);
  }
  if ( (this->m_flags & 2) != 0 )
  {
    v25 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            (const phys_vec3 *)&v29,
            this->b2,
            (phys_vec3 *)&b2_axis.y,
            (phys_vec3 *)&b1_ref.y,
            &this->m_ps_cache[7]);
    v25->m_pulse_sum_min = -10000000.0;
    v25->m_pulse_sum_max = 0.0;
    pulse_sum_angular::setup_vel_uni_standard(v25, delta_t, 5.0);
  }
}

void __userpurge rigid_body_constraint_distance::setup_constraint(
        rigid_body_constraint_distance *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b1; // edi
  rigid_body *b2; // eax
  pulse_sum_normal *pulse_sum_normal; // edi
  rigid_body *v8; // eax
  pulse_sum_normal *v9; // eax
  float v10; // ecx
  phys_vec3 *v11; // eax
  double w; // st7
  const phys_vec3 *v13; // eax
  phys_vec3 *v14; // eax
  pulse_sum_normal *v15; // edi
  const phys_vec3 *v16; // eax
  double v17; // st7
  rigid_body *v18; // ecx
  const phys_vec3 *v19; // eax
  double v20; // st7
  rigid_body *v21; // [esp-10h] [ebp-C8h]
  rigid_body *v22; // [esp-8h] [ebp-C0h]
  float pos_adjust; // [esp+4h] [ebp-B4h]
  float pos_adjusta; // [esp+4h] [ebp-B4h]
  float pos_adjustb; // [esp+4h] [ebp-B4h]
  float y; // [esp+1Ch] [ebp-9Ch] BYREF
  float z; // [esp+20h] [ebp-98h]
  float v28; // [esp+24h] [ebp-94h]
  phys_vec3 r2; // [esp+28h] [ebp-90h] BYREF
  phys_vec3 b2_pt; // [esp+38h] [ebp-80h] BYREF
  phys_vec3 b1_pt; // [esp+48h] [ebp-70h] BYREF
  phys_vec3 b1_r; // [esp+58h] [ebp-60h] BYREF
  phys_vec3 b2_r; // [esp+68h] [ebp-50h] BYREF
  phys_vec3 ud; // [esp+78h] [ebp-40h] BYREF
  phys_vec3 r1; // [esp+88h] [ebp-30h] BYREF
  phys_vec3 damp_dir; // [esp+98h] [ebp-20h]
  float v37; // [esp+A8h] [ebp-10h]
  int v38; // [esp+ACh] [ebp-Ch] BYREF
  float ndamp_dir; // [esp+B0h] [ebp-8h]
  float retaddr; // [esp+B8h] [ebp+0h]

  v38 = a2;
  ndamp_dir = retaddr;
  if ( (this->m_flags & 1) != 0 )
  {
    if ( this->m_min_distance < 0.0
      && _tlAssert("source/rbc_def_generic.cpp", 137, "m_min_distance >= 0.0f", &toastPopupTitle) )
    {
      __debugbreak();
    }
    if ( this->m_max_distance < (double)this->m_min_distance
      && _tlAssert("source/rbc_def_generic.cpp", 138, "m_min_distance <= m_max_distance", &toastPopupTitle) )
    {
      __debugbreak();
    }
    b1 = this->b1;
    phys_multiply((phys_vec3 *)&b1_pt.y, &this->b1->m_mat, &this->m_b1_r_loc);
    phys_multiply((phys_vec3 *)&b1_r.y, &this->b2->m_mat, &this->m_b2_r_loc);
    b2 = this->b2;
    b2_pt.y = b1->m_mat.w.x + b1_pt.y;
    b2_pt.z = b1->m_mat.w.y + b1_pt.z;
    b2_pt.w = b1->m_mat.w.z + b1_pt.w;
    r2.y = b2->m_mat.w.x + b1_r.y;
    r2.z = b2->m_mat.w.y + b1_r.z;
    r2.w = b2->m_mat.w.z + b1_r.w;
    r1.y = r2.y - b2_pt.y;
    r1.z = r2.z - b2_pt.z;
    r1.w = r2.w - b2_pt.w;
    damp_dir.w = r1.z * r1.z + r1.y * r1.y + r1.w * r1.w;
    if ( damp_dir.w >= 0.0000010000001 )
    {
      v37 = sqrt(damp_dir.w);
      v37 = 1.0 / v37;
      b2_r.y = r1.y * v37;
      b2_r.z = r1.z * v37;
      b2_r.w = v37 * r1.w;
      pulse_sum_normal = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
      ud.y = -b2_r.y;
      v8 = this->b2;
      ud.z = -b2_r.z;
      ud.w = -b2_r.w;
      pulse_sum_normal::set(
        pulse_sum_normal,
        (int)&v38,
        this->b1,
        (phys_vec3 *)&b1_pt.y,
        v8,
        (phys_vec3 *)&b1_r.y,
        (phys_vec3 *)&ud.y,
        this->m_ps_cache_list,
        &PHYS_ZERO_VEC_74);
      pulse_sum_normal->m_pulse_sum_min = -10000000.0;
      pulse_sum_normal->m_pulse_sum_max = 0.0;
      pos_adjust = -this->m_max_distance;
      pulse_sum_normal::setup_vel_uni_standard_pos_adjust(pulse_sum_normal, delta_t, pos_adjust, 1700.0);
      pulse_sum_normal->m_right_side = this->m_max_distance_vel + pulse_sum_normal->m_right_side;
      if ( this->m_min_distance > 0.0099999998 )
      {
        *(float *)&v9 = COERCE_FLOAT(pulse_sum_constraint_solver::create_pulse_sum_normal(psys));
        v22 = this->b2;
        v21 = this->b1;
        v37 = *(float *)&v9;
        pulse_sum_normal::set(
          v9,
          (int)&v38,
          v21,
          (phys_vec3 *)&b1_pt.y,
          v22,
          (phys_vec3 *)&b1_r.y,
          (phys_vec3 *)&b2_r.y,
          &this->m_ps_cache_list[1],
          &PHYS_ZERO_VEC_74);
        v10 = v37;
        *(float *)(LODWORD(v37) + 96) = -10000000.0;
        *(float *)(LODWORD(v10) + 100) = 0.0;
        pulse_sum_normal::setup_vel_uni_standard_pos_adjust(
          (pulse_sum_normal *)LODWORD(v10),
          delta_t,
          this->m_min_distance,
          1700.0);
      }
      if ( this->m_damp_coef > 0.0000099999997 )
      {
        v37 = this->m_max_distance - 0.1000000014901161;
        v37 = v37 * v37;
        if ( v37 <= (double)damp_dir.w )
        {
          v37 = this->m_max_distance + 0.1000000014901161;
          v37 = v37 * v37;
          if ( v37 >= (double)damp_dir.w )
          {
            pulse_sum_normal::get_relative_velocity(pulse_sum_normal, (int)&v38, (phys_vec3 *)&r1.y);
            pos_adjusta = phys_dot((phys_vec3 *)&r1.y, (phys_vec3 *)&b2_r.y);
            v11 = operator*((phys_vec3 *)&ud.y, pos_adjusta, (phys_vec3 *)&b2_r.y);
            phys_vec3::operator-=((phys_vec3 *)&r1.y, v11);
            damp_dir.w = Abs(&r1.y);
            w = damp_dir.w;
            if ( damp_dir.w < 0.00009999999747378752 )
            {
              v13 = pulse_sum_normal::get_relative_velocity_change_dir(pulse_sum_normal, (phys_vec3 *)&ud.y);
              r1.y = v13->x;
              r1.z = v13->y;
              r1.w = v13->z;
              pos_adjustb = phys_dot((phys_vec3 *)&r1.y, (phys_vec3 *)&b2_r.y);
              v14 = operator*((phys_vec3 *)&ud.y, pos_adjustb, (phys_vec3 *)&b2_r.y);
              phys_vec3::operator-=((phys_vec3 *)&r1.y, v14);
              damp_dir.w = Abs(&r1.y);
              w = damp_dir.w;
            }
            if ( w > 0.00009999999747378752 )
            {
              v37 = 1.0 / w;
              phys_vec3::operator*=((phys_vec3 *)&r1.y, v37);
              v15 = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
              if ( (this->m_flags & 2) != 0 )
              {
                v16 = rbint::sub_pos((phys_vec3 *)&b2_pt.y, this->b1, (phys_vec3 *)&r2.y);
                ud.y = v16->x;
                ud.z = v16->y;
                ud.w = v16->z;
                y = b1_r.y;
                z = b1_r.z;
                v17 = b1_r.w;
              }
              else
              {
                v18 = this->b2;
                ud.y = b1_pt.y;
                ud.z = b1_pt.z;
                ud.w = b1_pt.w;
                v19 = rbint::sub_pos((phys_vec3 *)&r2.y, v18, (phys_vec3 *)&b2_pt.y);
                y = v19->x;
                z = v19->y;
                v17 = v19->z;
              }
              v28 = v17;
              pulse_sum_normal::set(
                v15,
                (int)&v38,
                this->b1,
                (phys_vec3 *)&ud.y,
                this->b2,
                (const phys_vec3 *)&y,
                (phys_vec3 *)&r1.y,
                &this->m_ps_cache_list[2],
                &PHYS_ZERO_VEC_74);
              v37 = 1.0 / (this->m_damp_coef * delta_t);
              v15->m_right_side = 0.0;
              v15->m_big_dirt = 0.0;
              v20 = v37;
              v15->m_cfm = v37;
              v15->m_denom = v20 + v15->m_denom;
              v15->m_pulse_sum_min = -10000000.0;
              v15->m_pulse_sum_max = 10000000.0;
            }
          }
        }
      }
    }
  }
}

// local variable allocation has failed, the output may be wrong!
void __userpurge rigid_body_constraint_angular_actuator::setup_constraint(
        rigid_body_constraint_angular_actuator *this@<ecx>,
        const phys_mat44 *a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  phys_mat44 *v5; // edi
  const phys_vec3 *v6; // eax
  rigid_body *b2; // edx
  pulse_sum_angular *pulse_sum_angular; // eax
  double v9; // st7
  float *v10; // edi
  double pos; // st7
  pulse_sum_angular *v12; // edi
  double v13; // st7
  const phys_vec3 *v14; // eax
  pulse_sum_angular *v15; // esi
  double v16; // st7
  phys_mat44 *p_m_mat; // [esp-24h] [ebp-94h]
  float v18[3]; // [esp-Ch] [ebp-7Ch] BYREF
  phys_mat44 mat; // [esp+0h] [ebp-70h] BYREF
  phys_vec3 a_vel_4; // [esp+44h] [ebp-2Ch] OVERLAPPED BYREF
  float v21; // [esp+54h] [ebp-1Ch]
  const phys_vec3 *p_x; // [esp+58h] [ebp-18h]
  float v23; // [esp+5Ch] [ebp-14h]
  float v24; // [esp+60h] [ebp-10h]
  const phys_mat44 *b2_mat; // [esp+64h] [ebp-Ch] BYREF
  float ps_limit; // [esp+68h] [ebp-8h]
  float retaddr; // [esp+70h] [ebp+0h]

  b2_mat = a2;
  ps_limit = retaddr;
  if ( this->m_enabled )
  {
    p_m_mat = &this->b1->m_mat;
    v5 = &this->b2->m_mat;
    v23 = this->m_power * delta_t * this->m_power_scale;
    p_x = &v5->x;
    phys_multiply_mat((int)&b2_mat, (phys_mat44 *)v18, p_m_mat, &this->m_target_mat);
    v6 = phys_multiply(&a_vel_4, &this->b1->m_mat, &this->m_a_vel);
    b2 = this->b2;
    mat.w.y = v6->x;
    mat.w.z = v6->y;
    mat.w.w = v6->z;
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          this->b1,
                          (const phys_vec3 *)v18,
                          b2,
                          &v5->x,
                          (const phys_vec3 *)&mat.x.y,
                          this->m_ps_cache_list);
    v9 = v23;
    v10 = (float *)pulse_sum_angular;
    v24 = -v23;
    pulse_sum_angular->m_pulse_sum_min = v24;
    pulse_sum_angular->m_pulse_sum_max = v9;
    *(double *)&a_vel_4.z = -1.0 / delta_t;
    pos = pulse_sum_angular::get_pos(pulse_sum_angular);
    v10[28] = pos * *(double *)&a_vel_4.z;
    v10[27] = 0.0;
    v10[29] = 0.0;
    v10[30] = v10[30] + 0.0;
    v21 = mat.x.z * mat.w.z + mat.x.y * mat.w.y + mat.x.w * mat.w.w;
    v10[27] = 0.0 - v21;
    v12 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            (const phys_vec3 *)&mat.x.y,
            this->b2,
            p_x + 1,
            (const phys_vec3 *)&mat.y.y,
            &this->m_ps_cache_list[1]);
    v12->m_pulse_sum_min = v24;
    v12->m_pulse_sum_max = v23;
    v13 = pulse_sum_angular::get_pos(v12);
    v14 = p_x;
    v12->m_big_dirt = v13 * *(double *)&a_vel_4.z;
    v12->m_right_side = 0.0;
    v12->m_cfm = 0.0;
    v12->m_denom = v12->m_denom + 0.0;
    v21 = mat.y.y * mat.w.y + mat.y.z * mat.w.z + mat.y.w * mat.w.w;
    v12->m_right_side = 0.0 - v21;
    v15 = pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys,
            this->b1,
            (const phys_vec3 *)&mat.y.y,
            this->b2,
            v14 + 2,
            (const phys_vec3 *)v18,
            &this->m_ps_cache_list[2]);
    v15->m_pulse_sum_min = v24;
    v15->m_pulse_sum_max = v23;
    v16 = pulse_sum_angular::get_pos(v15);
    v15->m_big_dirt = v16 * *(double *)&a_vel_4.z;
    v15->m_right_side = 0.0;
    v15->m_cfm = 0.0;
    v15->m_denom = v15->m_denom + 0.0;
    v21 = v18[1] * mat.w.z + v18[0] * mat.w.y + v18[2] * mat.w.w;
    v15->m_right_side = 0.0 - v21;
  }
}

void __userpurge rigid_body_constraint_upright::setup_constraint(
        rigid_body_constraint_upright *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
  rigid_body *b1; // edi
  pulse_sum_angular *pulse_sum_angular; // esi
  double v7; // st7
  double pos; // st7
  _BYTE v9[12]; // [esp-Ch] [ebp-3Ch] BYREF
  phys_vec3 b1_lean_axis; // [esp+0h] [ebp-30h] BYREF
  float v11; // [esp+20h] [ebp-10h]
  int v12; // [esp+24h] [ebp-Ch]
  void *v13; // [esp+28h] [ebp-8h]
  void *retaddr; // [esp+30h] [ebp+0h]

  v12 = a2;
  v13 = retaddr;
  if ( this->m_enabled )
  {
    b1 = this->b1;
    phys_multiply((phys_vec3 *)&b1_lean_axis.y, &this->b1->m_mat, &this->m_b1_forward_axis_loc);
    phys_multiply((const phys_vec3 *)v9, &b1->m_mat, &this->m_b1_lean_axis_loc);
    pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                          psys,
                          b1,
                          (const phys_vec3 *)v9,
                          this->b2,
                          &this->m_b2_up_axis_loc,
                          (phys_vec3 *)&b1_lean_axis.y,
                          this->m_ps_cache_list);
    pulse_sum_angular->m_pulse_sum_min = -10000000.0;
    pulse_sum_angular->m_pulse_sum_max = 10000000.0;
    v7 = 0.016666668;
    if ( delta_t > 0.016666668 )
      v7 = delta_t;
    v11 = v7;
    pos = pulse_sum_angular::get_pos(pulse_sum_angular);
    pulse_sum_angular->m_big_dirt = pos * (-0.5 / v11);
    pulse_sum_angular->m_right_side = 0.0;
    pulse_sum_angular->m_cfm = 0.0;
  }
}

void __thiscall pulse_sum_normal::setup_vel_uni_standard_pos_adjust(
        pulse_sum_normal *this,
        float delta_t,
        float pos_adjust,
        float max_penalty_restitution_vel)
{
  double v4; // st7
  int savedregs; // [esp+4h] [ebp+0h] BYREF
  float delta_tc; // [esp+Ch] [ebp+8h]
  float delta_ta; // [esp+Ch] [ebp+8h]
  float delta_tb; // [esp+Ch] [ebp+8h]

  v4 = 0.016666668;
  if ( delta_t > 0.016666668 )
    v4 = delta_t;
  delta_tc = v4;
  delta_ta = -((pulse_sum_normal::get_pos(this, (int)&savedregs) + pos_adjust) / delta_tc);
  this->m_big_dirt = delta_ta;
  if ( delta_ta < 0.0 )
    this->m_big_dirt = delta_ta * 0.300000011920929;
  delta_tb = -max_penalty_restitution_vel;
  if ( delta_tb > (double)this->m_big_dirt )
    this->m_big_dirt = delta_tb;
  if ( this->m_big_dirt < 0.0 )
  {
    this->m_right_side = 0.0;
  }
  else
  {
    this->m_right_side = this->m_big_dirt;
    this->m_big_dirt = 0.0;
  }
  this->m_cfm = 0.0;
}

void __thiscall pulse_sum_angular::setup_vel_uni_standard(
        pulse_sum_angular *this,
        float delta_t,
        float max_penalty_restitution_vel)
{
  double v3; // st7
  float delta_tc; // [esp+Ch] [ebp+8h]
  float delta_ta; // [esp+Ch] [ebp+8h]
  float delta_tb; // [esp+Ch] [ebp+8h]

  v3 = 0.016666668;
  if ( delta_t > 0.016666668 )
    v3 = delta_t;
  delta_tc = v3;
  delta_ta = -pulse_sum_angular::get_pos(this) / delta_tc;
  this->m_big_dirt = delta_ta;
  if ( delta_ta < 0.0 )
    this->m_big_dirt = delta_ta * 0.300000011920929;
  delta_tb = -max_penalty_restitution_vel;
  if ( delta_tb > (double)this->m_big_dirt )
    this->m_big_dirt = delta_tb;
  if ( this->m_big_dirt < 0.0 )
  {
    this->m_right_side = 0.0;
  }
  else
  {
    this->m_right_side = this->m_big_dirt;
    this->m_big_dirt = 0.0;
  }
  this->m_cfm = 0.0;
}

pulse_sum_normal *__thiscall pulse_sum_constraint_solver::create_pulse_sum_normal(pulse_sum_constraint_solver *this)
{
  pulse_sum_normal **v2; // edi
  pulse_sum_normal **m_last_next_ptr; // ecx

  v2 = (pulse_sum_normal **)phys_transient_allocator::allocate(
                              &this->m_solver_memory_allocator,
                              160,
                              16,
                              0,
                              SOLVER_MEMORY_ALLOCATOR_ERROR_MSG);
  if ( !this->m_list_pulse_sum_normal.m_last_next_ptr
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_mem.h",
         230,
         "m_last_next_ptr",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  *v2 = 0;
  m_last_next_ptr = this->m_list_pulse_sum_normal.m_last_next_ptr;
  ++this->m_list_pulse_sum_normal.m_alloc_count;
  *m_last_next_ptr = (pulse_sum_normal *)v2;
  this->m_list_pulse_sum_normal.m_last_next_ptr = v2;
  return (pulse_sum_normal *)v2;
}

void __thiscall pulse_sum_constraint_solver::create_point(
        pulse_sum_constraint_solver *this,
        rigid_body *const b1,
        const phys_vec3 *b1_r,
        rigid_body *const b2,
        const phys_vec3 *b2_r,
        pulse_sum_cache *const ps_cache,
        float delta_t,
        bool is_spring,
        float spring_k,
        float damp_k)
{
  pulse_sum_point *v11; // edi
  pulse_sum_point **m_last_next_ptr; // ecx
  int savedregs; // [esp+18h] [ebp+0h] BYREF

  v11 = (pulse_sum_point *)phys_transient_allocator::allocate(
                             &this->m_solver_memory_allocator,
                             272,
                             16,
                             0,
                             SOLVER_MEMORY_ALLOCATOR_ERROR_MSG);
  if ( !this->m_list_pulse_sum_point.m_last_next_ptr
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_mem.h",
         230,
         "m_last_next_ptr",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  v11->m_next_link = 0;
  m_last_next_ptr = this->m_list_pulse_sum_point.m_last_next_ptr;
  ++this->m_list_pulse_sum_point.m_alloc_count;
  *m_last_next_ptr = v11;
  this->m_list_pulse_sum_point.m_last_next_ptr = &v11->m_next_link;
  pulse_sum_point::set(v11, (int)&savedregs, b1, b1_r, b2, b2_r, ps_cache, delta_t, is_spring, spring_k, damp_k);
}

pulse_sum_angular *__thiscall pulse_sum_constraint_solver::create_pulse_sum_angular(
        pulse_sum_constraint_solver *this,
        rigid_body *const b1,
        const phys_vec3 *b1_r,
        rigid_body *const b2,
        const phys_vec3 *b2_r,
        const phys_vec3 *ud,
        pulse_sum_cache *const ps_cache)
{
  pulse_sum_angular *v8; // edi
  pulse_sum_angular **m_last_next_ptr; // ecx
  int savedregs; // [esp+8h] [ebp+0h] BYREF

  v8 = (pulse_sum_angular *)phys_transient_allocator::allocate(
                              &this->m_solver_memory_allocator,
                              144,
                              16,
                              0,
                              SOLVER_MEMORY_ALLOCATOR_ERROR_MSG);
  if ( !this->m_list_pulse_sum_angular.m_last_next_ptr
    && _tlAssert(
         "c:\\projects_pc\\cod\\codsrc\\tl\\physics\\include\\phys_mem.h",
         230,
         "m_last_next_ptr",
         &toastPopupTitle) )
  {
    __debugbreak();
  }
  v8->m_next_link = 0;
  m_last_next_ptr = this->m_list_pulse_sum_angular.m_last_next_ptr;
  ++this->m_list_pulse_sum_angular.m_alloc_count;
  *m_last_next_ptr = v8;
  this->m_list_pulse_sum_angular.m_last_next_ptr = &v8->m_next_link;
  pulse_sum_angular::set(v8, (int)&savedregs, b1, b1_r, b2, b2_r, ud, ps_cache);
  return v8;
}

void __thiscall pulse_sum_constraint_solver::create_hinge(
        pulse_sum_constraint_solver *this,
        rigid_body *const b1,
        const phys_vec3 *b1_axis,
        rigid_body *const b2,
        const phys_vec3 *b2_axis,
        const phys_vec3 *a1,
        const phys_vec3 *a2,
        pulse_sum_cache *const ps_cache,
        float delta_t)
{
  pulse_sum_angular *pulse_sum_angular; // esi
  double v12; // st7
  pulse_sum_angular *v13; // esi
  double v14; // st7
  float b2_axisa; // [esp+20h] [ebp+14h]
  float ps_cachea; // [esp+2Ch] [ebp+20h]

  pulse_sum_angular = pulse_sum_constraint_solver::create_pulse_sum_angular(
                        this,
                        b1,
                        b1_axis,
                        b2,
                        b2_axis,
                        a1,
                        ps_cache);
  pulse_sum_angular->m_pulse_sum_min = -10000000.0;
  pulse_sum_angular->m_pulse_sum_max = 10000000.0;
  v12 = 0.016666668;
  if ( delta_t > 0.016666668 )
    v12 = delta_t;
  ps_cachea = v12;
  pulse_sum_angular->m_big_dirt = pulse_sum_angular::get_pos(pulse_sum_angular) * (-0.5 / ps_cachea);
  pulse_sum_angular->m_right_side = 0.0;
  pulse_sum_angular->m_cfm = 0.0;
  v13 = pulse_sum_constraint_solver::create_pulse_sum_angular(this, b1, b1_axis, b2, b2_axis, a2, ps_cache + 1);
  v13->m_pulse_sum_min = -10000000.0;
  v13->m_pulse_sum_max = 10000000.0;
  v14 = 0.016666668;
  if ( delta_t > 0.016666668 )
    v14 = delta_t;
  b2_axisa = v14;
  v13->m_big_dirt = pulse_sum_angular::get_pos(v13) * (-0.5 / b2_axisa);
  v13->m_right_side = 0.0;
  v13->m_cfm = 0.0;
}

