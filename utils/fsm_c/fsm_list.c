#include <stdbool.h>
#include <math.h>  // for fabs
#include "stdint.h"
#include "action.h"
#include "rfsm.h"
#include "rfsm_list_types.h"
#include "servo.h"
#include "wheel_pair.h"
#include "pgv.h"

#define ALIGN_ACC (2.0f)
#define ALIGN_DCC (2.0f)
#define ALIGN_SPEED (5.0f)

/*
 * common for many fsms
 */
// volatile static uint32_t wait_move_end_cntr = 0;
volatile static encoder_pos_t encoder_pos_before_move;
volatile static encoder_pos_t encoder_distance;
static int                    stage_before_movement_wait = 0;
static int                    wait_move_end_cntr         = 0;

static void wait_movement_end_common(rfsm_t* p_fsm)
{
    static encoder_pos_t last_encoder_pos = {0, 0};
    encoder_pos_t        curr_encoder_pos = wp_get_encoder_positions();

    if (last_encoder_pos.left == 0 && last_encoder_pos.right == 0)
    {
        last_encoder_pos = encoder_pos_before_move;
    }

    if (fabsf((float) last_encoder_pos.left) - fabsf((float) curr_encoder_pos.left) != 0 ||
        fabsf((float) last_encoder_pos.right) - fabsf((float) curr_encoder_pos.right) != 0)
    {
        //  robot is still moving, waiting until end
        last_encoder_pos = wp_get_encoder_positions();
        rfsm_repeat_step(p_fsm);

        encoder_distance.left  = fabsf((float) encoder_pos_before_move.left) - fabsf((float) last_encoder_pos.left);
        encoder_distance.right = fabsf((float) encoder_pos_before_move.right) - fabsf((float) last_encoder_pos.right);
    }
    else
    {
        // wait_move_end_cntr++;
        last_encoder_pos.left  = 0;
        last_encoder_pos.right = 0;
        // rfsm_repeat_step(p_fsm);
    }

    // if the movement never happened - go to next move iteration step
    /*
    if(wait_move_end_cntr >= WAIT_MOVE_ATTEMPTS &&
       fabsf((float)encoder_pos_before_move.left) - fabsf((float)curr_encoder_pos.left) == 0 &&
       fabsf((float)encoder_pos_before_move.right) - fabsf((float)curr_encoder_pos.right) == 0)
    {
        rfsm_go_to(p_fsm_tag_align_y_then_x,stage_before_movement_wait + 1);
    }
     */
}

//-------------------------------------------------------------------------------------------------
// FSM fsm_tag_align_y_then_x:
//-------------------------------------------------------------------------------------------------
rfsm_t  fsm_tag_align_y_then_x;
rfsm_t* p_fsm_tag_align_y_then_x = &fsm_tag_align_y_then_x;

#define WAIT_MOVE_ATTEMPTS (7)
#define WAIT_MOVEMENT_END_STEP (7)
#define X_AXIS_TURN_ANGLE_90 (90.0f)
#define Y_AXIS_TURN_ANGLE_N90 (-90.0f)
#define NEGATIATE_ANGLE(a) ((a > 180.0f) ? (a -= 360.0f) : (a = a))
#define PGV_OFFSET_TO_METERS(mm) ((float) mm / 10000.0f)  // pgv gives in mm/10

static struct
{
    float X;
    float Y;
    float angle;
} offset = {.X = 0.0f, .Y = 0.0f, .angle = 0.0f};

static bool tag_align_init(void* params)
{
    uint16_t status = pgv_tag_is_detect();

    if (status)
    {
        wp_mode_position_control();
        wp_absolute_positioning();
        wp_init_for_movement();
    }
    else
        rfsm_finish(p_fsm_tag_align_y_then_x);  // complete FSM, skip all next steps

    return false;
}

static bool turn_on_y(void* params)
{
    uint16_t warning = pgv_get_warnings();

    if (warning == PGV_WARNING_NA)
    {
        offset.angle = (float) (pgv_get_angle() / 10);

        NEGATIATE_ANGLE(offset.angle);

        // turn robot to normal position
        if (offset.angle > 0.0f || offset.angle < 0.0f)
        {
            wp_set_profile_acceleration_mpss(ALIGN_ACC);
            wp_set_profile_deceleration_mpss(ALIGN_DCC);
            wp_set_profile_speed_mps(ALIGN_SPEED);
            encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
            wp_turn_angle(-offset.angle);

            // save stage and go to wait movement
            stage_before_movement_wait = p_fsm_tag_align_y_then_x->stage;
            rfsm_go_to(p_fsm_tag_align_y_then_x, WAIT_MOVEMENT_END_STEP);
        }
    }
    else
        rfsm_finish(p_fsm_tag_align_y_then_x);  // complete FSM, skip all next steps

    return false;
}

static bool wait_movement_end(void* params)
{
    wait_movement_end_common(p_fsm_tag_align_y_then_x);
    return false;
}

static bool wait_inertion_end(void* params)
{
    encoder_distance.left  = 0;
    encoder_distance.right = 0;

    rfsm_go_to(p_fsm_tag_align_y_then_x, stage_before_movement_wait + 1);

    return false;
}

static bool align_y(void* params)
{
    // get rid Y offset
    offset.Y = PGV_OFFSET_TO_METERS(pgv_get_y_pos());
    if (offset.Y < 0)
    {
        wp_set_profile_acceleration_mpss(ALIGN_ACC);
        wp_set_profile_deceleration_mpss(ALIGN_DCC);
        wp_set_profile_speed_mps(ALIGN_SPEED);
        encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
        wp_shift_distance(fabsf(offset.Y), robot_side__front);
    }
    else
    {
        wp_set_profile_acceleration_mpss(ALIGN_ACC);
        wp_set_profile_deceleration_mpss(ALIGN_DCC);
        wp_set_profile_speed_mps(ALIGN_SPEED);
        encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
        wp_shift_distance(fabsf(offset.Y), robot_side__back);
    }

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_tag_align_y_then_x->stage;
    rfsm_go_to(p_fsm_tag_align_y_then_x, WAIT_MOVEMENT_END_STEP);
    return false;
}

static bool turn_on_x(void* params)
{
    // turn on X axis
    wp_set_profile_acceleration_mpss(ALIGN_ACC);
    wp_set_profile_deceleration_mpss(ALIGN_DCC);
    wp_set_profile_speed_mps(ALIGN_SPEED);
    encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
    wp_turn_angle(X_AXIS_TURN_ANGLE_90);

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_tag_align_y_then_x->stage;
    rfsm_go_to(p_fsm_tag_align_y_then_x, WAIT_MOVEMENT_END_STEP);
    return false;
}

static bool align_x(void* params)
{
    // get rid Y offset. Y is X axis now
    offset.Y = PGV_OFFSET_TO_METERS(pgv_get_x_pos());
    if (offset.Y < 0)
    {
        wp_set_profile_acceleration_mpss(ALIGN_ACC);
        wp_set_profile_deceleration_mpss(ALIGN_DCC);
        wp_set_profile_speed_mps(ALIGN_SPEED);
        encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
        wp_shift_distance(fabsf((float) offset.Y), robot_side__front);
    }
    else
    {
        wp_set_profile_acceleration_mpss(ALIGN_ACC);
        wp_set_profile_deceleration_mpss(ALIGN_DCC);
        wp_set_profile_speed_mps(ALIGN_SPEED);
        encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
        wp_shift_distance(fabsf((float) offset.Y), robot_side__back);
    }

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_tag_align_y_then_x->stage;
    rfsm_go_to(p_fsm_tag_align_y_then_x, WAIT_MOVEMENT_END_STEP);

    return false;
}

static bool turn_on_next_tag(void* params)
{
    ActionCmd* action_cmd     = (ActionCmd*) params;
    float      next_tag_angle = (float) action_cmd->rotate.trajectory_angle;

    wp_set_profile_acceleration_mpss(ALIGN_ACC);
    wp_set_profile_deceleration_mpss(ALIGN_ACC);
    wp_set_profile_speed_mps(ALIGN_SPEED);
    encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions

    if (ROBOT_ROTATE_DIRECTION__to_ccw == action_cmd->rotate.direction)
        next_tag_angle *= (-1.0f);

    if (next_tag_angle != 0.0f)
        wp_turn_angle(Y_AXIS_TURN_ANGLE_N90 + next_tag_angle);  // turn on next tag
    else
        wp_turn_angle(Y_AXIS_TURN_ANGLE_N90);  // turn on Y axis (normal direction of the current tag)

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_tag_align_y_then_x->stage;
    rfsm_go_to(p_fsm_tag_align_y_then_x, WAIT_MOVEMENT_END_STEP);

    return false;
}

static bool tag_align_end(void* params)
{
    offset.X     = 0.0f;
    offset.Y     = 0.0f;
    offset.angle = 0.0f;
    // wait_move_end_cntr = 0;
    stage_before_movement_wait = 0;
    wp_init_for_standing();

    // bypass movement wait functions
    rfsm_finish(p_fsm_tag_align_y_then_x);
    return false;
}

const fsm_step_t tag_align_y_then_x_prog[] = {
    /*0*/ {1, 10, (void const*) tag_align_init},
    /*1*/ {1, 100, (void const*) turn_on_y},
    /*2*/ {1, 100, (void const*) align_y},
    /*3*/ {1, 100, (void const*) turn_on_x},
    /*4*/ {1, 100, (void const*) align_x},
    /*5*/ {1, 100, (void const*) turn_on_next_tag},
    /*6*/ {1, 5, (void const*) tag_align_end},
    /*7*/ {1, 50, (void const*) wait_movement_end},  // redefine WAIT_MOVEMENT_END_STEP if total steps changed
    /*8*/ {1, 500, (void const*) wait_inertion_end},
    {0}};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// FSM fsm_go_to_next_tag:
//-------------------------------------------------------------------------------------------------
#define MTT_WAIT_MOVEMENT_END_STEP (3)
rfsm_t  fsm_go_to_next_tag;
rfsm_t* p_fsm_go_to_next_tag = &fsm_go_to_next_tag;

static bool move_to_tag_init(void* params)
{
    stage_before_movement_wait = 0;
    wp_mode_position_control();
    wp_absolute_positioning();
    wp_init_for_movement();
    return false;
}

static bool move_to_tag(void* params)
{
    ActionCmd* action_cmd = (ActionCmd*) params;

    wp_set_profile_acceleration_mpss(action_cmd->manual_shift.motion_acceleration);
    wp_set_profile_deceleration_mpss(action_cmd->manual_shift.motion_deceleration);
    wp_set_profile_speed_mps(action_cmd->manual_shift.motion_speed);
    encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions
    wp_shift_distance(action_cmd->manual_shift.distance, action_cmd->manual_shift.side);

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_go_to_next_tag->stage;
    rfsm_go_to(p_fsm_go_to_next_tag, MTT_WAIT_MOVEMENT_END_STEP);
}

static bool move_to_tag_end(void* params)
{
    stage_before_movement_wait = 0;
    wp_init_for_standing();
    // bypass movement wait functions
    rfsm_finish(p_fsm_go_to_next_tag);
    return false;
}

static bool mtt_wait_movement_end(void* params)
{
    wait_movement_end_common(p_fsm_go_to_next_tag);

    return false;
}

static bool mtt_wait_inertion_end(void* params)
{
    encoder_distance.left  = 0;
    encoder_distance.right = 0;

    rfsm_go_to(p_fsm_go_to_next_tag, stage_before_movement_wait + 1);

    return false;
}

const fsm_step_t go_to_next_tag_prog[] = {
    /*0*/ {1, 10, (void const*) move_to_tag_init},
    /*1*/ {1, 100, (void const*) move_to_tag},
    /*2*/ {1, 5, (void const*) move_to_tag_end},
    /*3*/ {1, 50, (void const*) mtt_wait_movement_end},  // redefine MTT_WAIT_MOVEMENT_END_STEP if total steps changed
    /*4*/ {1, 500, (void const*) mtt_wait_inertion_end},
    {0}};
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// FSM fsm_manual_turn:
//-------------------------------------------------------------------------------------------------
#define MT_WAIT_MOVEMENT_END_STEP (3)
rfsm_t  fsm_manual_turn;
rfsm_t* p_fsm_manual_turn = &fsm_manual_turn;

static bool manual_turn_init(void* params)
{
    stage_before_movement_wait = 0;

    wp_mode_position_control();
    wp_absolute_positioning();
    wp_init_for_movement();
    return false;
}

static bool manual_turn(void* params)
{
    ActionCmd* action_cmd = (ActionCmd*) params;

    wp_set_profile_acceleration_radpss(action_cmd->manual_turn.rotate_acceleration);
    wp_set_profile_deceleration_radpss(action_cmd->manual_turn.rotate_acceleration);
    wp_set_profile_speed_radps(action_cmd->manual_turn.rotate_speed);
    wp_turn_angle((float) action_cmd->manual_turn.angle / 10);
    encoder_pos_before_move = wp_get_encoder_positions();  // save encoder positions

    // save stage and go to wait movement
    stage_before_movement_wait = p_fsm_manual_turn->stage;
    rfsm_go_to(p_fsm_manual_turn, MT_WAIT_MOVEMENT_END_STEP);
}

static bool manual_turn_end(void* params)
{
    stage_before_movement_wait = 0;
    wp_init_for_standing();
    // bypass movement wait functions
    rfsm_finish(p_fsm_manual_turn);
    return false;
}

static bool mt_wait_movement_end(void* params)
{
    wait_movement_end_common(p_fsm_manual_turn);

    return false;
}

static bool mt_wait_inertion_end(void* params)
{
    encoder_distance.left  = 0;
    encoder_distance.right = 0;

    rfsm_go_to(p_fsm_manual_turn, stage_before_movement_wait + 1);

    return false;
}

const fsm_step_t manual_turn_prog[] = {
    /*0*/ {1, 10, (void const*) manual_turn_init},
    /*1*/ {1, 100, (void const*) manual_turn},
    /*2*/ {1, 5, (void const*) manual_turn_end},
    /*3*/ {1, 50, (void const*) mt_wait_movement_end},  // redefine MT_WAIT_MOVEMENT_END_STEP if total steps changed
    /*4*/ {1, 500, (void const*) mt_wait_inertion_end},
    {0}};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// FSM test_FSM_A:
//-------------------------------------------------------------------------------------------------
#define REPEATES_NUM (5)
rfsm_t  test_FSM_A;
rfsm_t* p_test_FSM_A = &test_FSM_A;

static uint32_t repeats = 1;

static bool test_FSM_init(void* params)
{
    repeats = 0;

    return false;
}

static bool test_FSM(void* params)
{
    repeats++;

    return false;
}

static bool test_FSM_A_end(void* params)
{
    if (repeats < REPEATES_NUM)
        rfsm_go_to(p_test_FSM_A, 1);

    return false;
}

const fsm_step_t test_FSM_A_prog[] = {
    /*0*/ {1, 10, (void const*) test_FSM_init},
    /*1*/ {1, 10, (void const*) test_FSM},
    /*2*/ {1, 100, (void const*) NULL},
    /*3*/ {1, 5, (void const*) test_FSM_A_end},
    {0}};
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// FSM test_FSM_A:
//-------------------------------------------------------------------------------------------------
rfsm_t  test_FSM_B;
rfsm_t* p_test_FSM_B = &test_FSM_B;

static bool test_FSM_B_end(void* params)
{
    if (repeats < REPEATES_NUM)
        rfsm_go_to(p_test_FSM_B, 1);

    return false;
}

const fsm_step_t test_FSM_B_prog[] = {
    /*0*/ {1, 10, (void const*) test_FSM_init},
    /*1*/ {1, 10, (void const*) test_FSM},
    /*2*/ {1, 100, (void const*) NULL},
    /*3*/ {1, 5, (void const*) test_FSM_B_end},
    {0}};
//-------------------------------------------------------------------------------------------------
