#include <string.h>  // for memcpy
#include "fsm_sheduler.h"
#include "ring_buffer.h"
#include "fsm_types_capi.h"
//#include "board.hpp"
//#include "SEGGER_RTT.h"

static ring_buffer m_ACTIVE_FSM_LIST;
static uint8_t     m_ACTIVE_FSM_LIST_memory[MAX_FSM_FIFO_LEN*FSM_ITEM_SIZE];
static uint8_t     m_ACTIVE_FSM_LIST_retval[FSM_ITEM_SIZE];

static ring_buffer m_FSM_INPUT_DATA_BUF; 
static uint8_t     m_FSM_INPUT_DATA_BUF_memory[MAX_FSM_FIFO_LEN*FSM_PARAM_SIZE];
static uint8_t     m_FSM_INPUT_DATA_BUF_retval[FSM_PARAM_SIZE];

/**********************************  private members declaration  ********************************/
/*
* @brief get the number of running fsms
*/     
static uint8_t  m_get_running_number();

/**
* @brief check FSM is in list by uniqiue id
*/     
static int  m_is_in_list_uid(unique_id uid);

/**
* @brief check FSM is in list by fsm id(first comer in list)
*/   
static int  m_is_in_list_fid(fsm_id_t fsm_id);  

/**
* @brief remove stopped FSM from list by uid
*/      
static void  m_remove_from_list_uid(unique_id uid);

/**
* @brief remove stopped FSM from list by fsm id(first comer in list)
*/      
static void  m_remove_from_list_fid(fsm_id_t fsm_id);

/**
 * @brief reset fsm to not working state
 */
static void  m_fsm_reset(fsm_t* fsm); 

/**
 * @brief process fsm in sheduler
 * @trigger (true) charge fsm for execution from the beginning
 *          (false) - countinue fsm execution
 */
static void  m_fsm_processing(fsm_t* fsm, bool trigger);

/**
 * @brief unique id generator for fsm list search
 */
static uint32_t  m_generate_id(fsm_id_t id);

/**********************************  public members definition  ********************************/

void fsm_sheduler_init(void)
{
    ring_buffer_create(&m_ACTIVE_FSM_LIST, 
                       m_ACTIVE_FSM_LIST_memory, 
                       sizeof(m_ACTIVE_FSM_LIST_memory), 
                       FSM_ITEM_SIZE, 
                       &m_ACTIVE_FSM_LIST_retval[0]);

    ring_buffer_create(&m_FSM_INPUT_DATA_BUF, 
                       m_FSM_INPUT_DATA_BUF_memory, 
                       sizeof(m_FSM_INPUT_DATA_BUF_memory), 
                       FSM_PARAM_SIZE, 
                       &m_FSM_INPUT_DATA_BUF_retval[0]);

}

bool  fsm_sheduler_fsm_start(fsm_t* p_fsm, void* params, bool simult)
{
    bool func_result = false;
    FSM_PARAM_TYPE*  p_cmd;
    static FSM_PARAM_TYPE empty_cmd;

    if(params == NULL)
        p_cmd = &empty_cmd;
    else
        p_cmd =  (FSM_PARAM_TYPE*)params;

    // add FSM to queue if it is no longer there and if the size allows
    if (ring_buffer_get_free(&m_ACTIVE_FSM_LIST))
    {
        fsm_t fsm_copy = *p_fsm;
        fsm_copy.m_id = m_generate_id((fsm_id_t)p_fsm->m_id);
        fsm_copy.m_status = FSM_READY;

        // save input data for fsm execution
        if(ring_buffer_push(&m_FSM_INPUT_DATA_BUF,(uint8_t*)p_cmd))
        {
            fsm_copy.params = (void *)ring_buffer_peek_item(&m_FSM_INPUT_DATA_BUF,
                                                             (m_FSM_INPUT_DATA_BUF.avail - 1));
            func_result = true;
        }
        else
            func_result = false;

        // set if fsm can run simultaneously with others
        if(simult)
            fsm_copy.m_can_run_simultaneously = true;

        // place fsm in active list
        if(ring_buffer_push(&m_ACTIVE_FSM_LIST,(uint8_t*)&fsm_copy))
            func_result = true;
        else
            func_result = false;

    }

    return func_result;
}

bool fsm_sheduler_fsm_safe_start(fsm_t* p_fsm, void* params, bool simult)
{
    bool func_result = false;
    fsm_t *item;  
    unique_id uid;
    uid.raw = p_fsm->m_id;
    int list_index = m_is_in_list_fid((fsm_id_t)uid.fsm_id);
    FSM_PARAM_TYPE*  p_cmd;
    static FSM_PARAM_TYPE empty_cmd;

    if(params == NULL)
        p_cmd = &empty_cmd;
    else
        p_cmd =  (FSM_PARAM_TYPE*)params;

    // if the fsm with this id is on the list(for uid this not actual)
    if(list_index != -1)
    {
        item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, list_index);
        
        // and not runnig yet
        if(item->m_status == FSM_READY)
        {
            // then remove it from the list
            m_remove_from_list_fid((fsm_id_t)uid.fsm_id);
        }
    }

    // and re-add to the end of the list
    if (ring_buffer_get_free(&m_ACTIVE_FSM_LIST))
    {
        fsm_t fsm_copy = *p_fsm;
        fsm_copy.m_id = m_generate_id((fsm_id_t)p_fsm->m_id);
        fsm_copy.m_status = FSM_READY;

        // save input data for fsm execution
        if(ring_buffer_push(&m_FSM_INPUT_DATA_BUF, (uint8_t*)p_cmd))
        {
            // peek from HEAD
            fsm_copy.params = (void *)ring_buffer_peek_item(&m_FSM_INPUT_DATA_BUF,
                                                             (m_FSM_INPUT_DATA_BUF.avail - 1));
            func_result = true;
        }
        else
            func_result = false;

        // set if fsm can run simultaneously with others
        if(simult)
            fsm_copy.m_can_run_simultaneously = true;

        // place fsm in active list
        if(ring_buffer_push(&m_ACTIVE_FSM_LIST,(uint8_t*)&fsm_copy))
            func_result = true;
        else
            func_result = false;;
    } 
    
    return func_result;
}

bool  fsm_sheduler_fsm_force_terminate_uid(unique_id uid)
{
    bool func_result = false;
    int list_index = m_is_in_list_uid(uid); 
     
    if(list_index != -1)
    {        
        m_remove_from_list_uid(uid);
    
        func_result = true;
    }  
   
    return func_result;
}

bool  fsm_sheduler_fsm_force_terminate_fid(fsm_id_t fsm_id)
{
    bool func_result = false;
    int list_index = m_is_in_list_fid(fsm_id); 
     
    if(list_index != -1)
    {        
        m_remove_from_list_fid(fsm_id);
    
        func_result = true;
    }  
   
    return func_result;
}

void fsm_sheduler_force_terminate_all_list(void)
{
    while(ring_buffer_get_avail(&m_ACTIVE_FSM_LIST) > 0)
    {
        fsm_t* item = (fsm_t*)ring_buffer_peek(&m_ACTIVE_FSM_LIST);

        item->m_status = FSM_NA;
        m_fsm_reset(item);

        ring_buffer_pop(&m_ACTIVE_FSM_LIST);
    }
}

//#define DBG_FSM_DISPATCHER (1)
void fsm_sheduler_dispatch(void)
{
    static float execute_interval_tmr = 0;

    if((GET_MS() - execute_interval_tmr) > FSM_POLLING_DELTA)
    {
        //DBG_PIN4.set();
        execute_interval_tmr = GET_MS();

        uint32_t available_FSMs = ring_buffer_get_avail(&m_ACTIVE_FSM_LIST);
        uint32_t current_fsm    = 0;
         uint8_t running_number = m_get_running_number();
        unique_id uid = { 0 ,FSM_NOINIT};
         
        // initialization of FSM (when new execution commands appear)
        do
        {   
            if(available_FSMs > 0)
            {    
                fsm_t* item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, current_fsm);
                
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
                        m_fsm_processing(item, true);
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
                    m_fsm_processing(item, false);
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
            m_remove_from_list_uid(uid);
        }
        
        //DBG_PIN4.clear();
    }
}

/**********************************  private members definition  ********************************/

static uint8_t  m_get_running_number()
{
    uint8_t  number_of_running = 0;
     size_t  list_index   = 0;
     size_t  curr_fifo_avail = ring_buffer_get_avail(&m_ACTIVE_FSM_LIST);
      fsm_t* item = NULL;

    if(curr_fifo_avail == 0)
        return number_of_running;    

    while(curr_fifo_avail > list_index)
    {
        item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, list_index);
        
        if(item->m_status == FSM_RUN)
        {
            number_of_running++;
        }
        
        list_index++;        
    }
    
    return number_of_running; 
}

static int m_is_in_list_uid(unique_id uid)
{
        int  func_result  = -1;
     size_t  list_index   = 0;
     size_t  curr_fifo_avail = ring_buffer_get_avail(&m_ACTIVE_FSM_LIST);
      fsm_t* item = NULL;

    if(curr_fifo_avail == 0)
        return func_result;    

    while(curr_fifo_avail > list_index)
    {
        item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, list_index);
        
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

static int m_is_in_list_fid(fsm_id_t fsm_id)
{
        int  func_result  = -1;
     size_t  list_index   = 0;
     size_t  curr_fifo_avail = ring_buffer_get_avail(&m_ACTIVE_FSM_LIST);
      fsm_t* item = NULL;

    if(curr_fifo_avail == 0)
        return func_result;    

    while(curr_fifo_avail > list_index)
    {
        item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, list_index);
        
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

static void m_remove_from_list_uid(unique_id uid)
{    
    for (size_t i = 0; i < ring_buffer_get_avail(&m_ACTIVE_FSM_LIST); i++)
    {
        fsm_t* removed_fsm = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, i);

        if (removed_fsm->m_id == uid.raw)
        {
            removed_fsm->m_status = FSM_NA;
            m_fsm_reset(removed_fsm);

            ring_buffer_pop_item(&m_ACTIVE_FSM_LIST, i);
            ring_buffer_pop_item(&m_FSM_INPUT_DATA_BUF, i);
            
            // remap pointers and their data
            for (size_t y = 0; y < ring_buffer_get_avail(&m_ACTIVE_FSM_LIST); y++)
            {
                fsm_t* item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, y);
                
                item->params = (void *)ring_buffer_peek_item(&m_FSM_INPUT_DATA_BUF, y);
            }
            break;
        }        
    }     
}

static void m_remove_from_list_fid(fsm_id_t fsm_id)
{    
    for (size_t i = 0; i < ring_buffer_get_avail(&m_ACTIVE_FSM_LIST); i++)
    {
        fsm_t* removed_fsm = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, i);

        unique_id removed_fsm_id;
        removed_fsm_id.raw = removed_fsm->m_id;

        if(removed_fsm_id.fsm_id == fsm_id)
        { 
            removed_fsm->m_status =  FSM_NA;
            m_fsm_reset(removed_fsm);

            ring_buffer_pop_item(&m_ACTIVE_FSM_LIST, i);
            ring_buffer_pop_item(&m_FSM_INPUT_DATA_BUF, i);
            
            // remap pointers and their data
            for (size_t y = 0; y < ring_buffer_get_avail(&m_ACTIVE_FSM_LIST); y++)
            {
                fsm_t* item = (fsm_t*)ring_buffer_peek_item(&m_ACTIVE_FSM_LIST, y);
                
                item->params = (void *)ring_buffer_peek_item(&m_FSM_INPUT_DATA_BUF, y);
            }
            break;
        }
    }      
}

static void  m_fsm_reset(fsm_t* fsm) 
{ 
    fsm->count = fsm->interval = 0; 
    fsm->stage = -1; 
    fsm->user_trigger = false; 
} 

static void m_fsm_processing(fsm_t* fsm, bool trigger)
{
   fsm_status_t result = FSM_RUN;
           bool step_function_result;
            
    if (trigger)
    {
        // charge FSM for execution from the beginning
        // fsm not initiated
        if (fsm->stage == -1)
        {
            fsm->count = fsm->m_program[0].count;

            if (fsm->count == 0)
            {
                fsm->m_status = FSM_NA;
                return;
            }

            fsm->stage    = 0;
            fsm->interval = 0; 
            fsm->user_trigger = true;            
        }
        
        fsm->m_status = result;
        return;                     
    } 
    else
    {
        // continue running the FSM until completion
        if (fsm->stage == -1)
        {
            fsm->m_status = FSM_NA;
            return;     
        }
    }

    do
    {
        if (fsm->interval == 0)
        {
            // before the action - so that you can correct it in the modifier handler
            fsm->interval = (int)((float)fsm->m_program[fsm->stage].interval)/FSM_TIME_DELTA;  //tenths of a millisecond
            
            if (fsm->interval < 1)
            {
                fsm->interval = 1; 
                // rounding up a multiple of TICK_COUNT_INTERVAL
                fsm->m_interval_end_time = GET_MS() + FSM_POLLING_DELTA;
            }
            else
            {
                fsm->m_interval_end_time = GET_MS() + (float)fsm->m_program[fsm->stage].interval;
            }

            // perform the step function if there is one
            if(fsm->m_program[fsm->stage].step_func != NULL)
            {   
                step_func_t step_function = (step_func_t)(fsm->m_program[fsm->stage].step_func);
                int old_stage = fsm->stage;

                step_function_result = step_function(fsm);
                
                if(old_stage != fsm->stage)
                {
                    fsm->m_fsm_transition = true;
                    fsm->count = 1;
                    if(fsm->stage < 0)
                        fsm->stage = 0;
                }
            }
        } 
        else
        {     
            fsm->interval--;

            if (fsm->interval == 0 ||
                (GET_MS() >= (float)fsm->m_interval_end_time))
            {
                // the interval has ended, we perform the step again,
                // or move on to the next
                fsm->interval = 0;
                fsm->count--;

                if (fsm->count == 0) 
                {
                    // the number of repetitions of this step has ended, 
                    // let's move on to the next step
                    if(!fsm->m_fsm_transition)
                        fsm->stage++;
                    else
                        fsm->m_fsm_transition = false;

                    fsm->count = fsm->m_program[fsm->stage].count;

                    if (fsm->count == 0) 
                    {
                        // this is the last step, release the fsm
                        fsm->stage = -1;
                        result = FSM_RELEASE;
                        break;                                                      
                    }
                }
            }
        }
    } while (fsm->interval == 0);

    step_function_result = step_function_result; // UNUSED
    fsm->m_status = result;
}

// for id generation
static unique_id m_unique_id = { 1 ,FSM_NOINIT};

static uint32_t  m_generate_id(fsm_id_t id)
{
    unique_id  result;

    m_unique_id.uid++;

    result.uid = m_unique_id.uid;
    result.fsm_id     = (uint16_t)id;

    return result.raw;
}
