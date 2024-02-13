#ifndef _FSM_H
#define _FSM_H

#include <stdbool.h>
#include "stdint.h"
#include "fsm_types_capi.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FSM_TIME_DELTA (5.0f)       // quantum of fsm tick reference 5ms
#define FSM_POLLING_DELTA (4.999f)  // interval of processing all FSMs in the list. 4.999ms

#if defined(STM32F765xx)
#    include "cmsis_os.h"
#endif

#ifdef CMSIS_OS_H_
    #include "FreeRTOS.h"
    #define GET_MS()   (MX_TIM6_get_ms())       // float
    #define GET_MS10() (MX_TIM6_get_ms10())     // ms*10 - tenths of a microseconds
#elif defined(am335x)
    #include "fsm_timer_capi.h"
    #define GET_MS()      (fsm_tmr_get_ms())    // float with ms.us value
    #define REBOOT_MS()   (fsm_tmr_reboot())    // reboot ms timer for fsm if no available fsms in progress
#else
    #include "stm32f7xx_hal.h"
    #define GET_MS_FROM_BOOT HAL_GetTick()
#endif

typedef enum
{
    FSM_NA,             // initial status of the fsm when the system is initialized, with this status the FSM does not start.
    FSM_READY,          // fsm ready for execution
    FSM_RUN,            // fsm works and performs the steps
    FSM_RELEASE,        // fsm just finished work
    FSM_DELAYED_START   // delayed start of the fsm, the start will be at the moment of the next check of the status of
                        // the machine.
} fsm_status_t;

struct fsm_step
{
    uint16_t    count;      // how many times
    uint16_t    interval;   // at what interval in ms
    void const* step_func;  // pointer to function in step
};

typedef struct fsm_step fsm_step_t;


/**
instructions on the transition to the steps of a hypothetical automaton
{
step  0     {  1,   5, step_ini  },   //in func_n() call fsm_go_to(0);
step  1     {  1,   5, func_1    },
step  2     {  1, 500, nullptr   },
step  3     {  3, 150, func_2    },   // in func_1 call fsm_go_to(3);
           ......................
step  n     {  3, 150, func_n    },
step n+1    {  1,   5, func_last },  // in func_2 call fsm_go_to_last() or fsm_go_to(n+1);
           {0}                      // in step_ini call fsm_finish()
};
**/

struct fsmt 
{
    int   stage;         // the current step of the fsm.
    int   count;         // how many times it remains to be repeated.
    int   interval;      // at what interval.
    bool  user_trigger;  // user trigger for servicing the functions of the fsm
    void* params;        // fsm input parameters pointer

    const fsm_step_t* m_program;      // ptr on fsm program
    uint32_t          m_id;           // fsm id.
    fsm_status_t      m_status;       // current fsm status
    uint32_t          m_total_steps;  // count the steps of fsm and transition between them.
       bool  m_fsm_transition;        // to be able to move along the other steps during the execution of fsm(out of order)
      float  m_interval_end_time;

      float  m_fsm_start_delay;             //  period for which the start of fsm is postponed
      float  m_fsm_absolute_start_time;     // absolute time when fsm was queued
       bool  m_can_run_simultaneously;      // flag that fsm can run simultaneously with other fsms

};

typedef struct fsmt fsm_t; 

typedef bool (*step_func_t)(fsm_t* fsm);  // a function that is executed in each step of the fsm.

/**********************************  fsm creation  ********************************/
/**
 * @brief initiate fsm allocatd in stack or flash memory
 * @return pointer on initiated fsm
 */
void fsm_construct_static(fsm_t* p_fsm, fsm_id_t id, const fsm_step_t* fsm_prog);

/**
 * @brief initiate fsm allocatd in heap memory
 * @return pointer on initiated fsm
 */
fsm_t* fsm_construct_heap(fsm_id_t id, const fsm_step_t* fsm_prog);

/**
 * @brief free fsm allocatd in heap memory
 */
void fsm_free(fsm_t* p_fsm);

/******************************  fsm branching control  *****************************/
/**
 * @brief set next step to finish his execution:
 * execute step  {0} in m_program
 */
inline void  fsm_finish(fsm_t* p_fsm);  

/**
 * @brief set next step to last step of fsm
 * execute last step before {0} in m_program 
 */     
inline void  fsm_go_to_last(fsm_t* p_fsm); 
    
 
/**
 * @brief go to the specific step
 */
inline void  fsm_go_to(fsm_t* p_fsm, uint32_t step);                                

 
/**
 * @brief repeates current step once more
 */
inline void  fsm_repeat_step(fsm_t* p_fsm);            



#ifdef __cplusplus
}
#endif
 
#endif // _FSM_H