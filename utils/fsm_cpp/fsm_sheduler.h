#ifndef FSM_SHEDULER_H
#define FSM_SHEDULER_H

#include <stdbool.h>
#include "stdint.h"
#include "fsm.h"
#include "ring_buffer.hpp"
#include "fsm_types_capi.h"

#define MAX_FSM_FIFO_LEN    (16U)       // fsm list length
#define MAX_ACTIVE_FSM      (2)         // number of simultaneously operating FSMs at the moment

class fsm_sheduler
{
public:    
    fsm_sheduler() { } 

    ~fsm_sheduler() { } 
  
    /**
    * @brief run FSM execution (add to list)
    */ 
    bool  fsm_start(fsm_t& fsm, void* params, bool simult = false);
 
    /**
    * @brief safe run FSM execution(add it to the list or delete it if it
    *  is already in the list, but has not yet been processed) 
    */     
    bool  fsm_safe_start(fsm_t& fsm, void* params);

    /**
    * @brief force terinate FSM by fsm id
    */
    bool  fsm_force_terminate(unique_id uid); 

    /**
    * @brief force terinate FSM by fsm id
    */
    bool  fsm_force_terminate(fsm_id_t fsm_id); 

     /**
     * @brief force terminate all in active list
     */
     void  force_terminate_all_list(void);
     
     /**
     * @brief fsm execution loop
     */     
     void  dispatch(void);


private: 
   /*
    * @brief get the number of running fsms
    */     
    uint8_t  m_get_running_number();

    /**
    * @brief check FSM is in list by uniqiue id
    */     
    int  m_is_in_list(unique_id uid);

    /**
    * @brief check FSM is in list by fsm id(first comer in list)
    */   
    int  m_is_in_list(fsm_id_t fsm_id);  

    /**
    * @brief remove stopped FSM from list by uid
    */      
    void  m_remove_from_list(unique_id uid);

    /**
    * @brief remove stopped FSM from list by fsm id(first comer in list)
    */      
    void  m_remove_from_list(fsm_id_t fsm_id);

    /**
     * @brief reset fsm to not working state
     */
    inline void  m_fsm_reset(fsm_t& fsm) 
    { fsm.count = fsm.interval = 0; fsm.stage = -1; fsm.user_trigger = false; } 

    /**
     * @brief process fsm in sheduler
     * @trigger (true) charge fsm for execution from the beginning
     *          (false) - countinue fsm execution
     */
    void  m_fsm_processing(fsm_t& fsm, bool trigger);

    /**
     * @brief unique id generator for fsm list search
     */
    uint32_t  m_generate_id(fsm_id_t id);

        ring_buffer<fsm_t, MAX_FSM_FIFO_LEN>  m_ACTIVE_FSM_LIST;   // list of ready or running fsms
    ring_buffer<action_cmd,MAX_FSM_FIFO_LEN>  m_FSM_INPUT_DATA_BUF;
};

extern fsm_sheduler action_cmd_sheduler;

#endif  // FSM_SHEDULER_H