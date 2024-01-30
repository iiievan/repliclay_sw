#include "stdint.h"

#include "fsm.h"
#include "board.hpp"
#include "fsm_types_capi.h"
#include "fsm_timer.h"

//-------------------------------------------------------------------------------------------------
// FSM test_fsm_b:
//-------------------------------------------------------------------------------------------------
fsm_t  test_fsm_b;

#define WAIT_DELAY_STEP (3)

static float last_t = 0;
static float  ms = 0;
static  uint8_t repeats = 1;

static uint32_t m_stage_before_wait = 0;

static bool test_fsm_init(fsm_t* fsm)
{
    action_cmd* cmd = (action_cmd*) fsm->params;

    repeats = cmd->repetitions;
    m_stage_before_wait = 0;
    
    DBG_PIN2.set();
    last_t = fsm_time.get_ms(); 

    return false;
}

static bool test_fsm(fsm_t* fsm)
{
    repeats--;    

    if (repeats)
    {
        USR_LED_1.toggle();
        
        m_stage_before_wait = fsm->stage;
        fsm_go_to(fsm, WAIT_DELAY_STEP);
    }    

    return false;
}

static bool test_fsm_b_end(fsm_t* fsm)
{
    DBG_PIN2.set();
    USR_LED_1.clear();    

    repeats = 0;    
    m_stage_before_wait = 0;
    
    fsm_finish(fsm);
    
    ms = fsm_time.get_ms();
    ms = 0;
    last_t = 0;

    DBG_PIN2.clear();

    return false;
}

static bool test_fsm_wait_delay(fsm_t* fsm)
{
    static uint32_t delay = 0;
    action_cmd* cmd = (action_cmd*) fsm->params;

    DBG_PIN2.toggle();
    
    if(delay == 0u)
        delay = (uint32_t)(cmd->rep_delay/FSM_TIME_DELTA); 
    
    delay--;
    
    if(delay == 0u)
      fsm_go_to(fsm, m_stage_before_wait);
    else
      fsm_repeat_step(fsm);      

    return false;
}

const fsm_step_t test_fsm_b_prog[] = 
{
     /*0*/  {1, 5,  (void const*) test_fsm_init},
     /*1*/  {1, 5,  (void const*) test_fsm},
     /*2*/  {1, 5,  (void const*) test_fsm_b_end},
     /*3*/  {1, 5,  (void const*) test_fsm_wait_delay},
            {0}
};
//-------------------------------------------------------------------------------------------------
