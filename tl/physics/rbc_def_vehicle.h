#pragma once

void __thiscall pulse_sum_normal::set_pulse_sum_limits_parent_ratio(
        pulse_sum_normal *this,
        float limit_ratio,
        pulse_sum_normal *const parent);
void __thiscall pulse_sum_wheel::set_side_fwd_ratios(
        pulse_sum_wheel *this,
        float side_ratio,
        float fwd_ratio,
        float side_fric_max);
void __thiscall rigid_body_constraint_wheel::set_wheel_state_accelerating(
        rigid_body_constraint_wheel *this,
        float desired_speed_k,
        float acceleration_factor_k);
void __thiscall rigid_body_constraint_wheel::get_wheel_state_accelerating(
        rigid_body_constraint_wheel *this,
        float *desired_speed_k,
        float *acceleration_factor_k);
void __thiscall rigid_body_constraint_wheel::set_wheel_state_braking(
        rigid_body_constraint_wheel *this,
        float braking_factor_k);
void __thiscall rigid_body_constraint_wheel::set_no_collision(rigid_body_constraint_wheel *this);
void __thiscall rigid_body_constraint_wheel::set_collision(
        rigid_body_constraint_wheel *this,
        rigid_body *const rb,
        const phys_vec3 *hitp_loc,
        const phys_vec3 *hitn_loc);
double __cdecl lerp_float(const float tgt, float cur, float rate, float delta_t);
void __thiscall rigid_body_constraint_wheel::set(
        rigid_body_constraint_wheel *this,
        const phys_vec3 *wheel_center_loc,
        const phys_vec3 *suspension_dir_loc,
        const phys_vec3 *wheel_axis_loc,
        float wheel_radius,
        float fwd_fric_k,
        float side_fric_k,
        float suspension_stiffness_k,
        float suspension_damp_k,
        float hard_limit_dist,
        float roll_stability_factor,
        float pitch_stability_factor,
        float side_fric_max);
void __userpurge rigid_body_constraint_wheel::get_wheel_collide_segment(
        rigid_body_constraint_wheel *this@<ecx>,
        int a2@<ebp>,
        const phys_mat44 *b1_mat,
        phys_vec3 *const p0,
        phys_vec3 *const p1);
void __userpurge rigid_body_constraint_wheel::epilog_vel_constraint(
        rigid_body_constraint_wheel *this@<ecx>,
        int a2@<ebp>,
        float delta_t);
// local variable allocation has failed, the output may be wrong!
void __userpurge rigid_body_constraint_wheel::setup_constraint(
        rigid_body_constraint_wheel *this@<ecx>,
        int a2@<ebp>,
        pulse_sum_constraint_solver *psys,
        float delta_t);
void __thiscall pulse_sum_normal::setup_vel_uni_standard(
        pulse_sum_normal *this,
        float delta_t,
        float max_penalty_restitution_vel);
pulse_sum_normal *__thiscall pulse_sum_constraint_solver::create_pulse_sum_wheel_fwd(
        pulse_sum_constraint_solver *this,
        pulse_sum_wheel *psw);
pulse_sum_wheel *__thiscall pulse_sum_constraint_solver::create_pulse_sum_wheel(pulse_sum_constraint_solver *this);
