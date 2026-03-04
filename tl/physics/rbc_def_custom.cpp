#include "rbc_def_custom.h"
#include "rbc_def_generic.h"
#include <physics/physics_system_internal.h>
#include <physics/phys_constraint_solver_multithreaded.h>

float psa_spring_d = 5.0;
float psa_spring_k = 100.0;
float psa_spring_d_0 = 5.0;
float psa_spring_k_0 = 100.0;
float psn_spring_d = 12.0;
float psn_spring_k = 50.0;


const phys_vec3 * rbint::mul_L(
        phys_vec3 *result,
        const rigid_body *rb,
        const phys_vec3 *t)
{
  phys_vec3 v5; // [esp-20h] [ebp-2Ch] BYREF
  float v6; // [esp-10h] [ebp-1Ch]
  float v7; // [esp-Ch] [ebp-18h]
  float v8; // [esp-8h] [ebp-14h]
  //int v9; // [esp+0h] [ebp-Ch]
  //void *v10; // [esp+4h] [ebp-8h]
  //void *retaddr; // [esp+Ch] [ebp+0h]
  //
  //v9 = a1;
  //v10 = retaddr;
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
        pulse_sum_constraint_solver *psys,
        float delta_t)
{
    double v3; // st7
    bool v6; // c0
    phys_mat44 *p_m_mat; // ecx
    phys_mat44 *v8; // edi
    pulse_sum_angular *psa; // eax
    pulse_sum_angular *psa2; // eax
    pulse_sum_angular *psa3; // eax
    pulse_sum_angular *psa4; // eax
    double v13; // st7
    double pos; // st7
    double v15; // st6
    double v16; // st5
    pulse_sum_angular *psa5; // eax
    float *v18; // ebx
    double v19; // st7
    double v20; // st7
    double v21; // st6
    phys_vec3 *b2_r; // [esp+Ch] [ebp-Ch]
    float roll; // [esp+10h] [ebp-8h]
    const phys_mat44 *b2_mat; // [esp+14h] [ebp-4h]
    float b2_matb; // [esp+14h] [ebp-4h]
    phys_mat44 *b2_mata; // [esp+14h] [ebp-4h]
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
    if (v6)
    {
        pitchd = this->m_torque_resistance_pitch_roll * 10.0;
        psa = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            &this->b1->m_mat.z,
            this->b2,
            &p_m_mat->z,
            &this->b1->m_mat.y,
            this->m_ps_cache_list);
        psa->m_pulse_sum_min = -10000000.0;
        psa->m_pulse_sum_max = 10000000.0;
        pitche = 1.0 / (pitchd * delta_t);
        psa->m_right_side = 0.0;
        psa->m_big_dirt = 0.0;
        psa->m_cfm = pitche;
        psa->m_denom = pitche + psa->m_denom;
        psa2 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            &v8->z,
            this->b2,
            &b2_mat->z,
            &v8->x,
            &this->m_ps_cache_list[1]);
        p_m_mat = (phys_mat44 *)b2_mat;
        psa2->m_pulse_sum_min = -10000000.0;
        psa2->m_pulse_sum_max = 10000000.0;
        v3 = 0.0;
        psa2->m_right_side = 0.0;
        psa2->m_big_dirt = 0.0;
        psa2->m_cfm = pitche;
        psa2->m_denom = pitche + psa2->m_denom;
    }
    if (v3 < this->m_torque_resistance_yaw)
    {
        pitchf = this->m_torque_resistance_yaw * 10.0;
        psa3 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            &v8->x,
            this->b2,
            &p_m_mat->x,
            &v8->z,
            &this->m_ps_cache_list[2]);
        psa3->m_pulse_sum_min = -10000000.0;
        p_m_mat = (phys_mat44 *)b2_mat;
        psa3->m_pulse_sum_max = 10000000.0;
        pitchg = 1.0 / (pitchf * delta_t);
        v3 = 0.0;
        psa3->m_right_side = 0.0;
        psa3->m_big_dirt = 0.0;
        psa3->m_cfm = pitchg;
        psa3->m_denom = pitchg + psa3->m_denom;
    }
    if (this->m_active && v3 < this->m_upright_strength)
    {
        pitchh = fabs(this->b1->m_mat.y.z);
        roll = pitchh;
        pitch = fabs(this->b1->m_mat.x.z);
        if (v3 > this->b1->m_mat.z.z)
        {
            pitch = 1.0;
            roll = 1.0;
        }
        b2_r = &p_m_mat->z;
        b2_matb = this->m_upright_strength * 30.0 * delta_t;
        pitcha = b2_matb * pitch;
        psa4 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            &v8->z,
            this->b2,
            &p_m_mat->z,
            &v8->y,
            &this->m_ps_cache_list[3]);
        b2_mata = (phys_mat44 *)psa4;
        if (this->m_no_orientation_correction)
        {
            v13 = 0.0;
            if (v8->x.z >= 0.0)
            {
                psa4->m_pulse_sum_min = 0.0;
                v13 = pitcha;
            }
            else
            {
                psa4->m_pulse_sum_min = -pitcha;
            }
            psa4->m_pulse_sum_max = v13;
            //pos = pulse_sum_angular::get_pos(psa4);
            pos = psa4->get_pos();
            v15 = delta_t;
            v16 = -0.0 / delta_t;
        }
        else
        {
            psa4->m_pulse_sum_min = -pitcha;
            psa4->m_pulse_sum_max = pitcha;
            //pos = pulse_sum_angular::get_pos(psa4);
            pos = psa4->get_pos();
            v15 = delta_t;
            v16 = -1.0 / delta_t;
        }
        b2_mata[1].z.w = pos * v16;
        b2_mata[1].w.x = 0.0;
        b2_mata[1].w.y = 0.0;
        b2_mata[1].w.z = b2_mata[1].w.z + 0.0;
        pitchi = v15 * (this->m_upright_strength * 100.0);
        pitchb = pitchi * roll;
        psa5 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            &v8->z,
            this->b2,
            b2_r,
            &v8->x,
            &this->m_ps_cache_list[4]);
        v18 = (float *)psa5;
        if (this->m_no_orientation_correction)
        {
            pitchc = pitchb * 0.5;
            v19 = 0.0;
            if (v8->y.z <= 0.0)
            {
                psa5->m_pulse_sum_min = 0.0;
                v19 = pitchc;
            }
            else
            {
                psa5->m_pulse_sum_min = -pitchc;
            }
            psa5->m_pulse_sum_max = v19;
            //v20 = pulse_sum_angular::get_pos(psa5);
            v20 = psa5->get_pos();
            v21 = -0.0 / delta_t;
        }
        else
        {
            psa5->m_pulse_sum_min = -pitchb;
            psa5->m_pulse_sum_max = pitchb;
            //v20 = pulse_sum_angular::get_pos(psa5);
            v20 = psa5->get_pos();
            v21 = -1.0 / delta_t;
        }
        v18[27] = v20 * v21;
        v18[28] = 0.0;
        v18[29] = 0.0;
        v18[30] = v18[30] + 0.0;
    }
}

// local variable allocation has failed, the output may be wrong!
void rigid_body_constraint_custom_path::setup_constraint(pulse_sum_constraint_solver *psys, float delta_t)
{
    rigid_body *b1; // ecx
    double v6; // st6
    double v7; // st4
    double v8; // st6
    pulse_sum_normal *psn; // edi
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
    pulse_sum_angular *v20; // edi
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
    phys_vec3 v38; // [esp-Ch] [ebp-8Ch] BYREF
    phys_vec3 b1_r_4; // [esp+4h] [ebp-7Ch] BYREF
    float b2_r_4[3]; // [esp+14h] [ebp-6Ch] BYREF
    phys_vec3 v41; // [esp+24h] [ebp-5Ch] BYREF
    float b1_r__4; // [esp+34h] [ebp-4Ch] BYREF
    float b1_r__8; // [esp+38h] [ebp-48h]
    float b1_r__12; // [esp+3Ch] [ebp-44h]
    phys_vec3 axis; // [esp+40h] [ebp-40h] BYREF
    float b1_ud; // [esp+50h] [ebp-30h]
    float v47[2]; // [esp+5Ch] [ebp-24h] OVERLAPPED
    float v48; // [esp+64h] [ebp-1Ch]
    float y; // [esp+68h] [ebp-18h]
    float v50[2]; // [esp+6Ch] [ebp-14h]
    //_UNKNOWN *v51[2]; // [esp+74h] [ebp-Ch] BYREF
    //int vars0; // [esp+80h] [ebp+0h]
    //
    //v51[0] = a2;
    //v51[1] = (_UNKNOWN *)vars0;
    v41.x = 0.0;
    b1 = this->b1;
    v41.y = 0.0;
    v41.z = 0.0;
    phys_multiply(&v38, &b1->m_mat, &this->b1_r_loc);
    phys_multiply(&b1_r_4, &this->b2->m_mat, &v41);
    if (!this->m_urb && _tlAssert("source/rbc_def_custom.cpp", 148, "m_urb", ""))
        __debugbreak();
    v50[1] = 1.0 / this->b1->m_inv_mass;
    v6 = v50[1];
    v50[1] = psn_spring_k * v50[1];
    v50[1] = v50[1] * delta_t;
    v7 = v6 * psn_spring_d;
    v8 = v50[1] * delta_t;
    v50[1] = v7;
    v50[1] = delta_t * v50[1];
    v50[1] = 1.0 / (v50[1] + v8);
    v47[1] = v8 * v50[1];
    //psn = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
    psn = psys->create_pulse_sum_normal();
    //pulse_sum_normal::set(
        psn->set(
        this->b1,
        &v38,
        this->b2,
        &b1_r_4,
        &PHYS_X_VEC,
        this->m_list_psc,
        &PHYS_ZERO_VEC);
    *(double *)v47 = -v47[1] / delta_t;
    //pos = pulse_sum_normal::get_pos(psn, (int)v51);
    pos = psn->get_pos();
    psn->m_right_side = pos * *(double *)v47;
    psn->m_big_dirt = 0.0;
    v11 = v50[1];
    psn->m_cfm = v50[1];
    psn->m_denom = v11 + psn->m_denom;
    psn->m_pulse_sum_min = -10000000.0;
    psn->m_pulse_sum_max = 10000000.0;
    //v12 = pulse_sum_constraint_solver::create_pulse_sum_normal(psys);
    v12 = psys->create_pulse_sum_normal();
    //pulse_sum_normal::set(
        v12->set(
        this->b1,
        &v38,
        this->b2,
        &b1_r_4,
        &PHYS_Y_VEC,
        &this->m_list_psc[1],
        &PHYS_ZERO_VEC);
    //v13 = pulse_sum_normal::get_pos(v12, (int)v51);
    v13 = v12->get_pos();
    v12->m_right_side = v13 * *(double *)v47;
    v12->m_big_dirt = 0.0;
    v14 = v50[1];
    v12->m_cfm = v50[1];
    v12->m_denom = v14 + v12->m_denom;
    v12->m_pulse_sum_min = -10000000.0;
    v12->m_pulse_sum_max = 10000000.0;
    v15 = this->b1;
    b1_r__4 = this->b1->m_mat.x.x;
    b1_r__8 = v15->m_mat.x.y;
    b2 = this->b2;
    b1_r__12 = v15->m_mat.x.z;
    b2 = (rigid_body *)((char *)b2 + 64);
    axis.x = v15->m_mat.x.w;
    x = b2->m_last_position.x;
    y = b2->m_last_position.y;
    v48 = x;
    v50[0] = b2->m_last_position.z;
    v50[1] = b2->m_last_position.w;
    v47[1] = x * b1_r__4 + y * b1_r__8 + v50[0] * b1_r__12;
    v41.x = x * v47[1];
    v41.y = y * v47[1];
    v41.z = v50[0] * v47[1];
    axis.y = b1_r__4 - v41.x;
    axis.z = b1_r__8 - v41.y;
    axis.w = b1_r__12 - v41.z;
    v47[1] = axis.y * axis.y + axis.z * axis.z + axis.w * axis.w;
    v47[1] = sqrt(v47[1]);
    if (v47[1] <= 0.00009999999747378752)
    {
        v23 = 0.0;
    }
    else
    {
        v47[1] = 1.0 / v47[1];
        axis.y = axis.y * v47[1];
        axis.z = axis.z * v47[1];
        axis.w = v47[1] * axis.w;
        v41.x = axis.w * y - axis.z * v50[0];
        v41.y = v50[0] * axis.y - axis.w * v48;
        v41.z = v48 * axis.z - axis.y * y;
        //v18 = rbint::mul_L((int)v51, (const phys_vec3 *)b2_r_4, v15, &v41);
        v18 = rbint::mul_L((phys_vec3 *)b2_r_4, v15, &v41);
        v47[1] = v18->y * v41.y + v18->x * v41.x + v18->z * v41.z;
        v19 = v47[1];
        v47[1] = psa_spring_k_0 * v47[1];
        v47[1] = v47[1] * delta_t;
        *(double *)v50 = v47[1] * delta_t;
        v47[1] = v19 * psa_spring_d_0;
        v47[1] = delta_t * v47[1];
        v47[1] = 1.0 / (*(double *)v50 + v47[1]);
        v20 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            this->b1,
            (const phys_vec3 *)&b1_r__4,
            this->b2,
            (phys_vec3 *)&axis.y,
            &v41,
            &this->m_list_psc[2]);
        //v21 = pulse_sum_angular::get_pos(v20);
        v21 = v20->get_pos();
        v22 = v47[1];
        v47[1] = *(double *)v50 * v47[1];
        v20->m_right_side = v21 * (-v47[1] / delta_t);
        v20->m_big_dirt = 0.0;
        v23 = 0.0;
        v20->m_cfm = v22;
        v20->m_denom = v22 + v20->m_denom;
        v20->m_pulse_sum_min = -10000000.0;
        v20->m_pulse_sum_max = 10000000.0;
    }
    v24 = this->b1->m_mat.z.y;
    p_z = &this->b1->m_mat.z;
    axis.y = p_z->x;
    z = p_z->z;
    w = p_z->w;
    b2_r_4[0] = v23;
    b2_r_4[1] = v23;
    axis.z = v24;
    axis.w = z;
    b2_r_4[2] = 1.0;
    b1_ud = w;
    v47[1] = v24 * 0.0 + axis.y * 0.0 + z;
    v41.x = axis.y * v47[1];
    v41.y = v24 * v47[1];
    v41.z = v47[1] * z;
    b1_r__4 = 0.0 - v41.x;
    b1_r__8 = 0.0 - v41.y;
    b1_r__12 = 1.0 - v41.z;
    v47[1] = b1_r__4 * b1_r__4 + b1_r__8 * b1_r__8 + b1_r__12 * b1_r__12;
    v47[1] = sqrt(v47[1]);
    if (v47[1] >= 0.00009999999747378752)
    {
        v28 = axis.y;
        v48 = axis.y * 0.5;
        y = axis.z * 0.5;
        v29 = axis.w;
        v50[0] = 0.5 * axis.w;
        v30 = axis.z;
        v47[1] = 0.8660253882408142 / v47[1];
        axis.y = b1_r__4 * v47[1];
        axis.z = b1_r__8 * v47[1];
        axis.w = v47[1] * b1_r__12;
        v41.x = axis.y + v48;
        v41.y = axis.z + y;
        v41.z = axis.w + v50[0];
        axis.y = v41.y * v29 - v41.z * v30;
        axis.z = v41.z * v28 - v29 * v41.x;
        axis.w = v41.x * v30 - v28 * v41.y;
        b1_r__4 = axis.y * 1.154700517654419;
        b1_r__8 = axis.z * 1.154700517654419;
        b1_r__12 = 1.154700517654419 * axis.w;
        PHYS_ASSERT_UNIT((const phys_vec3 *)&b1_r__4);
        v31 = rbint::mul_L((phys_vec3 *)&axis.y, this->b1, (const phys_vec3 *)&b1_r__4);
        v32 = this->b1;
        v37 = this->b2;
        v47[1] = v31->y * b1_r__8 + v31->x * b1_r__4 + v31->z * b1_r__12;
        v33 = v47[1];
        v47[1] = v47[1] * psa_spring_k;
        v47[1] = v47[1] * delta_t;
        *(double *)v50 = v47[1] * delta_t;
        v47[1] = v33 * psa_spring_d;
        v47[1] = delta_t * v47[1];
        v47[1] = 1.0 / (*(double *)v50 + v47[1]);
        v34 = //pulse_sum_constraint_solver::create_pulse_sum_angular(
            psys->create_pulse_sum_angular(
            v32,
            &v41,
            v37,
            (const phys_vec3 *)b2_r_4,
            (const phys_vec3 *)&b1_r__4,
            &this->m_list_psc[3]);
        v34->m_pulse_sum_min = -10000000.0;
        v34->m_pulse_sum_max = 0.0;
        //v35 = pulse_sum_angular::get_pos(v34);
        v35 = v34->get_pos();
        v36 = v47[1];
        v47[1] = *(double *)v50 * v47[1];
        v34->m_right_side = v35 * (-v47[1] / delta_t);
        v34->m_big_dirt = 0.0;
        v34->m_cfm = v36;
        v34->m_denom = v36 + v34->m_denom;
    }
}

