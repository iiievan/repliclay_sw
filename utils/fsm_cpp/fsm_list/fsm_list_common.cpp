#include <math.h>  // for fabs
#include "stdint.h"

#include "fsm.h"
#include "fsm_types_capi.h"
//#include "wheel_pair.h"
//#include "SEGGER_RTT.h"

/*
 * common for many fsms
 */
// volatile static uint32_t wait_move_end_cntr = 0;
//encoder_pos_t encoder_pos_before_move = {0, 0};
//encoder_pos_t encoder_distance = {0, 0};
int  stage_before_wait = 0;
/*
bool wait_movement_end_common(fsm_t* p_fsm)
{
    static encoder_pos_t last_encoder_pos = {0, 0};
    encoder_pos_t        curr_encoder_pos = wp_get_encoder_positions();
    float left_enc_delta = 0.0f;
    float right_enc_delta = 0.0f;
   static uint32_t inertion_wait = 0;

   static uint32_t left_zero_counter = 0;
   static uint32_t right_zero_counter = 0;
   static uint32_t zero_counter_tmr = 0;

    zero_counter_tmr++;

    if (last_encoder_pos.left == 0 &&
    	last_encoder_pos.right == 0 &&
		inertion_wait == 0)
    {
        last_encoder_pos = encoder_pos_before_move;
        //SEGGER_RTT_printf(0, "enc_before_move(l,r:%d:%d)\r\n",encoder_pos_before_move.left,encoder_pos_before_move.right);
    }

    left_enc_delta = fabsf((float) last_encoder_pos.left) - fabsf((float) curr_encoder_pos.left);
    right_enc_delta = fabsf((float) last_encoder_pos.right) - fabsf((float) curr_encoder_pos.right);
    //SEGGER_RTT_printf(0, "encdlta(l,r:%d:%d:)\r\n",((int)(left_enc_delta*1000.f))/1000,((int)(right_enc_delta*1000.f))/1000);

    if(left_enc_delta == 0.0f &&
       zero_counter_tmr > 5)
        left_zero_counter++;

    if(right_enc_delta == 0.0f &&
       zero_counter_tmr > 5)
        right_zero_counter++;

    if (left_enc_delta != 0.0f ||
    	right_enc_delta != 0.0f ||inertion_wait < 5)
    {
        //  robot is still moving, waiting until end
        last_encoder_pos = wp_get_encoder_positions();

        if(!inertion_wait)
        	inertion_wait = 1;

        if(left_enc_delta == 0.0f ||right_enc_delta == 0.0f)
        	inertion_wait++;
        else
        	inertion_wait = 1;

        fsm_repeat_step(p_fsm);
    }

    if(left_zero_counter > 2 || right_zero_counter > 2)
    {
        last_encoder_pos.left  = 0;
        last_encoder_pos.right = 0;
        left_zero_counter = 0;
        right_zero_counter = 0;
        zero_counter_tmr = 0;
        inertion_wait = 0;

        fsm_go_to_last(p_fsm);
    }

    return false;
}

encoder_pos_t get_encoders_distance_after_move()
{
    encoder_pos_t encoder_pos_after_move = wp_get_encoder_positions();  // save encoder positions

    encoder_distance.left  = fabsf((float) encoder_pos_after_move.left) - fabsf((float) encoder_pos_before_move.left) ;
    encoder_distance.right = fabsf((float) encoder_pos_after_move.right) - fabsf((float) encoder_pos_before_move.right);

    float distance_left = ((float)(encoder_distance.left/10000) * 61.5f * M_PI); //mm
    float distance_right = ((float)(encoder_distance.right/10000) * 61.5f * M_PI); //mm
    SEGGER_RTT_printf(0, "encoders_distance(l_tics:r_tics:l_mm:r_mm)\r\n");
    SEGGER_RTT_printf(0, "%d:%d:%d:%d\r\n",encoder_distance.left,encoder_distance.right,(int)distance_left,(int)distance_right);

    return encoder_distance;
}
*/