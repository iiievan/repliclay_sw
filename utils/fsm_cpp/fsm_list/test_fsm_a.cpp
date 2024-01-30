#include "stdint.h"
//#include "SEGGER_RTT.h"

#include "fsm.h"
#include "board.hpp"
#include "fsm_types_capi.h"
#include "fsm_timer.h"
//#include "tim.h"

//-------------------------------------------------------------------------------------------------
// FSM test_fsm_a:
//-------------------------------------------------------------------------------------------------
fsm_t  test_fsm_a;

#define WAIT_DELAY_STEP (3)

static float last_t = 0;
static float  ms = 0;
static  uint8_t repeats = 1;

static bool test_fsm_init(fsm_t* fsm)
{
    action_cmd* cmd = (action_cmd*) fsm->params;

    repeats = cmd->repetitions;
    stage_before_wait = 0;
    
    DBG_PIN1.set();
    last_t = fsm_time.get_ms(); 

    return false;
}

static bool test_fsm(fsm_t* fsm)
{     
    repeats--;    

    if (repeats)
    {
        USR_LED_0.toggle();
        
        stage_before_wait = fsm->stage;
        fsm_go_to(fsm, WAIT_DELAY_STEP);
    }
    

    return false;
}

static bool test_fsm_wait_delay(fsm_t* fsm)
{
    static uint32_t delay = 0;
    action_cmd* cmd = (action_cmd*) fsm->params;
    
    if(delay == 0u)
    {
        delay = (uint32_t)(cmd->rep_delay/FSM_TIME_DELTA);
        delay--;        

        fsm_repeat_step(fsm);
    }
    else
    {
        delay--;
        
        fsm_repeat_step(fsm);
        //DBG_PIN1.toggle();
        
        if(delay == 0u)
        {
            fsm_go_to(fsm, stage_before_wait);
            //DBG_PIN1.clear();
        }
    }

    return false;
}

static bool test_fsm_a_end(fsm_t* fsm)
{    
    USR_LED_0.clear();    

    repeats = 0;
    
    stage_before_wait = 0;
    
    fsm_finish(fsm);
    
    DBG_PIN1.clear();
    ms = fsm_time.get_ms();
    ms = 0;
    last_t = 0;

    return false;
}

const fsm_step_t test_fsm_a_prog[] = 
{
    /*0*/   {1, 5, (void const*) test_fsm_init},
    /*1*/   {1, 5, (void const*) test_fsm},
    /*2*/   {1, 5,  (void const*) test_fsm_a_end},
    /*3*/   {1, 5,  (void const*) test_fsm_wait_delay},
            {0}
};
//-------------------------------------------------------------------------------------------------
