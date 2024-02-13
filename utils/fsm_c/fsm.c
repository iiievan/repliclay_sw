#include <stdlib.h>
#include "fsm.h"
//#include "fsm_timer.h"

void fsm_construct_static(fsm_t* p_fsm, fsm_id_t id, const fsm_step_t* fsm_prog)
{
    p_fsm->m_program = fsm_prog;
    p_fsm->m_id        = id;

    p_fsm->count = p_fsm->interval = 0; 
    p_fsm->stage = -1; 
    p_fsm->user_trigger = false;
    p_fsm->m_status            = FSM_NA;
    p_fsm->m_total_steps       = 0;
    p_fsm->m_fsm_transition    = false;
    p_fsm->m_interval_end_time = 0.0f;
    p_fsm->params              = NULL;

    p_fsm->m_fsm_start_delay = 0.0f;
    p_fsm->m_fsm_absolute_start_time = 0.0f;
    p_fsm->m_can_run_simultaneously = false;

    // calculate total number of steps of the FSM
    while (p_fsm->m_program[p_fsm->m_total_steps].count != 0)
        p_fsm->m_total_steps++;
}

fsm_t* fsm_construct_heap(fsm_id_t id, const fsm_step_t* fsm_prog)
{
    fsm_t* p_fsm = (fsm_t*) malloc(sizeof(fsm_t));
    if (NULL == p_fsm)
        return NULL;

    p_fsm->m_program = fsm_prog;
    p_fsm->m_id      = id;

    p_fsm->count = p_fsm->interval = 0; 
    p_fsm->stage = -1; 
    p_fsm->user_trigger = false;
    p_fsm->m_status            = FSM_NA;
    p_fsm->m_total_steps       = 0;
    p_fsm->m_fsm_transition    = false;
    p_fsm->m_interval_end_time = 0.0f;
    p_fsm->params              = NULL;
    
    p_fsm->m_fsm_start_delay = 0.0f;
    p_fsm->m_fsm_absolute_start_time = 0.0f;
    p_fsm->m_can_run_simultaneously = false;

    // calculate total number of steps of the FSM
    while (p_fsm->m_program[p_fsm->m_total_steps].count != 0)
        p_fsm->m_total_steps++;

    return p_fsm;
}

void fsm_free(fsm_t* p_fsm)
{
    free(p_fsm);
}

void  fsm_finish(fsm_t* p_fsm) 
{
    p_fsm->stage = (int)p_fsm->m_total_steps; 
}  
   
void  fsm_go_to_last(fsm_t* p_fsm) 
{ 
    p_fsm->stage = (int)(p_fsm->m_total_steps - 1); 
}  
    
void  fsm_go_to(fsm_t* p_fsm, uint32_t step)                                 
{                                
    if(step > p_fsm->m_total_steps)
        fsm_finish(p_fsm);
    else
        p_fsm->stage = (int)step;
}
 
void  fsm_repeat_step(fsm_t* p_fsm)            
{ 
    p_fsm->m_fsm_transition = true;  p_fsm->count = 1; 
}
