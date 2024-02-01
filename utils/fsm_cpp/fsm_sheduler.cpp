#include <string.h>         // for memcpy
#include "fsm_sheduler.h"
#include "fsm_timer.h"
#include "board.hpp"
//#include "SEGGER_RTT.h"

fsm_sheduler action_cmd_sheduler;

bool  fsm_sheduler::fsm_start(fsm_t& fsm, void* params, bool simult)
{
    bool func_result = false;
    action_cmd*  p_cmd;
    static action_cmd empty_cmd;

    if(params == nullptr)
        p_cmd = &empty_cmd;
    else
        p_cmd =  (action_cmd*)params;

    // add FSM to queue if it is no longer there and if the size allows
    if (m_ACTIVE_FSM_LIST.get_free())
    {
        fsm_t fsm_copy = fsm;
        fsm_copy.m_id = m_generate_id((fsm_id_t)fsm.m_id);
        fsm_copy.m_status = FSM_READY;

        // save input data for fsm execution
        if(m_FSM_INPUT_DATA_BUF.push(*p_cmd))
        {
            fsm_copy.params = (void *)m_FSM_INPUT_DATA_BUF.peek_item(m_FSM_INPUT_DATA_BUF.get_avail() - 1);
            func_result = true;
        }
        else
            func_result = false;

        // fsm can run simultaneously with others
        if(simult)
            fsm_copy.m_can_run_simultaneously = true;

        // place fsm in active list
        if(m_ACTIVE_FSM_LIST.push(fsm_copy))
            func_result = true;
        else
            func_result = false;

    }

    return func_result;
}

bool  fsm_sheduler::fsm_safe_start(fsm_t& fsm, void* params)
{
    bool func_result = false;
    fsm_t *item;  
    unique_id uid;
    uid.raw = fsm.m_id;
    int list_index = m_is_in_list((fsm_id_t)uid.fsm_id);
    action_cmd*  p_cmd;
    static action_cmd empty_cmd;

    if(params == nullptr)
        p_cmd = &empty_cmd;
    else
        p_cmd =  (action_cmd*)params;
    
    // if the fsm with this id is on the list(for uid this not actual)
    if(list_index != -1)
    {
        item = m_ACTIVE_FSM_LIST.peek_item(list_index);
        
        // and not runnig yet
        if(item->m_status == FSM_READY)
        {
            // then remove it from the list
            m_remove_from_list((fsm_id_t)uid.fsm_id);
        }
    }
    
     // and re-add to the end of the list
     if (m_ACTIVE_FSM_LIST.get_free())
     {
         fsm_t fsm_copy = fsm;
         fsm_copy.m_id = m_generate_id((fsm_id_t)fsm.m_id);
         fsm_copy.m_status = FSM_READY;

         // save input data for fsm execution
         if(m_FSM_INPUT_DATA_BUF.push(*p_cmd))
         {
        	 fsm_copy.params = (void *)m_FSM_INPUT_DATA_BUF.peek_item(m_FSM_INPUT_DATA_BUF.get_avail() - 1);
             func_result = true;
         }
         else
             func_result = false;

         // place fsm in active list
         if(m_ACTIVE_FSM_LIST.push(fsm_copy))
             func_result = true;
         else
             func_result = false;
     } 
     
     return func_result;
}
 
bool  fsm_sheduler::fsm_force_terminate(unique_id uid)
{
    bool func_result = false;
    int list_index = m_is_in_list(uid); 
     
    if(list_index != -1)
    {        
        m_remove_from_list(uid);
    
        func_result = true;
    }  
   
    return func_result;
}

bool  fsm_sheduler::fsm_force_terminate(fsm_id_t fsm_id)
{
    bool func_result = false;
    int list_index = m_is_in_list(fsm_id); 
     
    if(list_index != -1)
    {        
        m_remove_from_list(fsm_id);
    
        func_result = true;
    }  
   
    return func_result;
}

void fsm_sheduler::force_terminate_all_list(void)
{
    while(m_ACTIVE_FSM_LIST.get_avail() > 0)
    {
        fsm_t* item = m_ACTIVE_FSM_LIST.peek();

        item->m_status = FSM_NA;
        m_fsm_reset(*item);

        m_ACTIVE_FSM_LIST.pop();
    }
}

//#define DBG_FSM_DISPATCHER (1)
void fsm_sheduler::dispatch(void)
{
    static float execute_interval_tmr = 0;

    if((GET_MS() - execute_interval_tmr) > FSM_POLLING_DELTA)
    {
        DBG_PIN4.set();
        execute_interval_tmr = GET_MS();
        uint32_t available_FSMs = m_ACTIVE_FSM_LIST.get_avail();
        uint32_t current_fsm    = 0;
         uint8_t running_number = m_get_running_number();
        unique_id uid = { 0 ,FSM_NOINIT};
         
        // initialization of FSM (when new execution commands appear)
        do
        {   
            if(available_FSMs > 0)
            {    
                fsm_t* item = m_ACTIVE_FSM_LIST.peek_item(current_fsm);
                
                if (item->m_status == FSM_DELAYED_START)
                {
                    if(item->m_fsm_absolute_start_time >= GET_MS())
                        item->m_status = FSM_READY;
                }

                // do not allow more than MAX_ACTIVE_FSM of FSMs to operate simultaneously
                if (item->m_status == FSM_READY)
                {
                    if((running_number == 0) ||
                       ((running_number > 0) && 
                        (running_number < MAX_ACTIVE_FSM) && 
                        item->m_can_run_simultaneously))
                    {
                        // charge fsm for execution from the beginning
                        m_fsm_processing(*item,true);
                    }
                    
#if defined(DBG_FSM_DISPATCHER)
                    SEGGER_RTT_printf(0, "fsm(%d):STARTED.\r\n", (int)item->m_id);
                    SEGGER_RTT_printf(0, "fsm_avail:simult_runned:current_fsm.\r\n");
                    SEGGER_RTT_printf(0, "%d:", (int)available_FSMs);
                    SEGGER_RTT_printf(0, "%d:", (int)running_number);
                    SEGGER_RTT_printf(0, "%d.\r\n", (int)current_fsm);
#endif          
                }

                if (item->m_status == FSM_RUN)
                {
                    // continue running fsm until completion
                    m_fsm_processing(*item,false);
                }
                
                running_number = m_get_running_number();

                if (FSM_RELEASE == item->m_status)
                {
                    // if the FSM has finished its work, remove it from the list later
                    uid.raw = item->m_id;                    
                }

                current_fsm++;
                available_FSMs--;
            }
            else
            {
                REBOOT_MS();    // reboot ms timer for fsm if no available fsms in progress
                execute_interval_tmr = 0;
            }
        }  
        while (available_FSMs);

        if(uid.raw != 0U)
        {
            m_remove_from_list(uid);
        }
        
        DBG_PIN4.clear();
    }
}
    
uint8_t  fsm_sheduler::m_get_running_number()
{
    uint8_t number_of_running = 0;
    auto  list_index   = 0;
    auto  curr_fifo_avail = m_ACTIVE_FSM_LIST.get_avail();
   fsm_t* item = nullptr;

    if(curr_fifo_avail == 0)
        return number_of_running;    

    while(curr_fifo_avail > list_index)
    {
        item = m_ACTIVE_FSM_LIST.peek_item(list_index);
        
        if(item->m_status == FSM_RUN)
        {
            number_of_running++;
        }
        
        list_index++;        
    }
    
    return number_of_running; 
}

int fsm_sheduler::m_is_in_list(unique_id uid)
{
    auto  func_result  = -1;
    auto  list_index   = 0;
    auto  curr_fifo_avail = m_ACTIVE_FSM_LIST.get_avail();
    fsm_t* item = nullptr;

    if(curr_fifo_avail == 0)
        return func_result;    

    while(curr_fifo_avail > list_index)
    {
        item = m_ACTIVE_FSM_LIST.peek_item(list_index);
        
        if(item->m_id == uid.raw)
            break;
        
        list_index++;        
    }

    if(list_index > curr_fifo_avail)
        func_result = -1;       // not in list
    else 
        func_result = list_index; 

    return func_result;
}  

int fsm_sheduler::m_is_in_list(fsm_id_t fsm_id)
{
    auto  func_result  = -1;
    auto  list_index   = 0;
    auto  curr_fifo_avail = m_ACTIVE_FSM_LIST.get_avail();
    fsm_t* item = nullptr;

    if(curr_fifo_avail == 0)
        return func_result;    

    while(curr_fifo_avail > list_index)
    {
        item = m_ACTIVE_FSM_LIST.peek_item(list_index);
        
        unique_id item_fsm_id;
        item_fsm_id.raw = item->m_id;

        if(item_fsm_id.fsm_id == fsm_id)
            break;
        
        list_index++;        
    }

    if(list_index > curr_fifo_avail)
        func_result = -1;       // not in list
    else 
        func_result = list_index; 

    return func_result;
} 

void fsm_sheduler::m_remove_from_list(unique_id uid)
{    
    for (size_t i = 0; i < m_ACTIVE_FSM_LIST.get_avail(); i++)
    {
        fsm_t* removed_fsm = m_ACTIVE_FSM_LIST.peek_item(i);

        if (removed_fsm->m_id == uid.raw)
        {
            removed_fsm->m_status = FSM_NA;
            m_fsm_reset(*removed_fsm);

            m_ACTIVE_FSM_LIST.pop_item(i);
            m_FSM_INPUT_DATA_BUF.pop_item(i);
            
            // remap pointers and their data
            for (size_t y = 0; y < m_ACTIVE_FSM_LIST.get_avail(); y++)
            {
                fsm_t* item = m_ACTIVE_FSM_LIST.peek_item(y);
                
                item->params = (void *)m_FSM_INPUT_DATA_BUF.peek_item(y);
            }
            break;
        }        
    }     
}

void fsm_sheduler::m_remove_from_list(fsm_id_t fsm_id)
{    
    for (size_t i = 0; i < m_ACTIVE_FSM_LIST.get_avail(); i++)
    {
        fsm_t* removed_fsm = m_ACTIVE_FSM_LIST.peek_item(i);

        unique_id removed_fsm_id;
        removed_fsm_id.raw = removed_fsm->m_id;

        if(removed_fsm_id.fsm_id == fsm_id)
        { 
            removed_fsm->m_status =  FSM_NA;
            m_fsm_reset(*removed_fsm);

            m_ACTIVE_FSM_LIST.pop_item(i);
            m_FSM_INPUT_DATA_BUF.pop_item(i);
            
            // remap pointers and their data
            for (size_t y = 0; y < m_ACTIVE_FSM_LIST.get_avail(); y++)
            {
                fsm_t* item = m_ACTIVE_FSM_LIST.peek_item(y);
                
                item->params = (void *)m_FSM_INPUT_DATA_BUF.peek_item(y);
            }
            break;
        }
    }      
}

void fsm_sheduler::m_fsm_processing(fsm_t& fsm, bool trigger)
{
   fsm_status_t result = FSM_RUN;
           bool step_function_result;
            
    if (trigger)
    {
        // charge FSM for execution from the beginning
        // fsm not initiated
        if (fsm.stage == -1)
        {
            fsm.count = fsm.m_program[0].count;

            if (fsm.count == 0)
            {
                fsm.m_status = FSM_NA;
                return;
            }

            fsm.stage    = 0;
            fsm.interval = 0; 
            fsm.user_trigger = true;            
        }
        
        fsm.m_status = result;
        return;                     
    } 
    else
    {
        // continue running the FSM until completion
        if (fsm.stage == -1)
        {
            fsm.m_status = FSM_NA;
            return;     
        }
    }

    do
    {
        if (fsm.interval == 0)
        {
            // before the action - so that you can correct it in the modifier handler
            fsm.interval = (int)((float)fsm.m_program[fsm.stage].interval)/FSM_TIME_DELTA;  //tenths of a millisecond
            
            if (fsm.interval < 1)
            {
                fsm.interval = 1; 
                // rounding up a multiple of TICK_COUNT_INTERVAL
                fsm.m_interval_end_time = GET_MS() + FSM_POLLING_DELTA;
            }
            else
            {
                fsm.m_interval_end_time = GET_MS() + (float)fsm.m_program[fsm.stage].interval;
            }

            // perform the step function if there is one
            if(fsm.m_program[fsm.stage].step_func != nullptr)
            {   
                step_func_t step_function = (step_func_t)(fsm.m_program[fsm.stage].step_func);
                int old_stage = fsm.stage;

                step_function_result = step_function(&fsm);
                
                if(old_stage != fsm.stage)
                {
                    fsm.m_fsm_transition = true;
                    fsm.count = 1;
                    if(fsm.stage < 0)
                        fsm.stage = 0;
                }
            }
        } 
        else
        {     
            fsm.interval--;

            if (fsm.interval == 0 ||
                (GET_MS() >= (float)fsm.m_interval_end_time))
            {
                // the interval has ended, we perform the step again,
                // or move on to the next
                fsm.interval = 0;
                fsm.count--;

                if (fsm.count == 0) 
                {
                    // the number of repetitions of this step has ended, 
                    // let's move on to the next step
                    if(!fsm.m_fsm_transition)
                        fsm.stage++;
                    else
                        fsm.m_fsm_transition = false;

                    fsm.count = fsm.m_program[fsm.stage].count;

                    if (fsm.count == 0) 
                    {
                        // this is the last step, release the fsm
                        fsm.stage = -1;
                        result = FSM_RELEASE;
                        break;                                                      
                    }
                }
            }
        }
    } while (fsm.interval == 0);

    step_function_result = step_function_result; // UNUSED
    fsm.m_status = result;
}

// for id generation
static unique_id m_unique_id = { 1 ,FSM_NOINIT};

uint32_t  fsm_sheduler::m_generate_id(fsm_id_t id)
{
    unique_id  result;

    m_unique_id.uid++;

    result.uid = m_unique_id.uid;
    result.fsm_id     = (uint16_t)id;

    return result.raw;
}

/**********************************  sheduler functions capi  ********************************/
void fsm_sheduler_dispatch(void)
{
    action_cmd_sheduler.dispatch();
}

/**
* @brief run FSM execution (add to list)
*/
bool fsm_start(fsm_t *fsm, void* params, bool simult)
{
    return action_cmd_sheduler.fsm_start(*fsm,params,simult);
}

/**
* @brief safe run FSM execution(add it to the list or delete it if it
*  is already in the list, but has not yet been processed)
*/
bool fsm_safe_start(fsm_t *fsm, void* params)
{
    return action_cmd_sheduler.fsm_safe_start(*fsm,params);
}

/**
* @brief force terinate FSM by fsm id
*/
bool fsm_force_terminate_uid(unique_id uid)
{
    return action_cmd_sheduler.fsm_force_terminate(uid);
}

/**
* @brief force terinate FSM by fsm id
*/
bool fsm_force_terminate_fsm_id(fsm_id_t fsm_id)
{
    return action_cmd_sheduler.fsm_force_terminate(fsm_id);
}

/**
* @brief force terminate all in active list
*/
void fsm_force_terminate_all_list(void)
{
    action_cmd_sheduler.force_terminate_all_list();
}
