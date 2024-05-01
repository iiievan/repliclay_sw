#ifndef __FSM_TYPES_CAPI_H
#define __FSM_TYPES_CAPI_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PGV_OFFSET_TO_METERS(mm) ((float) mm / 10000.0f)  // pgv gives in mm/10
#define NEGATIATE_ANGLE(a) ((a > 180.0f) ? (a -= 360.0f) : (a = a))

typedef struct  
{
    uint64_t  seconds;
    uint32_t  millis;
} timestamp_t;

/* struct for time setting */
typedef struct 
{   
    uint32_t              :7;     // bit: 0..6 
    uint32_t    MERIDIEM  :1;     // bit: 7      [ see e_meridiem] 
    uint32_t    SEC       :8;     // bit: 8..15        
    uint32_t    MIN       :8;     // bit: 16..23          
    uint32_t    HOUR      :8;     // bit: 24..31      
} abTime_t;

typedef struct 
{
       char  name[8];
    uint8_t  repetitions;
      float  rep_delay;         // in ms
   abTime_t  absolute_start_time;
}action_cmd;

typedef enum
{
    FSM_NOINIT = 0,
    FSM_TEST_A,
    FSM_TEST_B,
    FSM_TEST_C,
    FSM_NUM_MAX
} fsm_id_t;

typedef struct
{
    union
    {
        struct
        {
            uint16_t    uid;      // unique number for fsm search in list
            uint16_t    fsm_id;  // fsm_id_t
        };
        uint32_t  raw;
    };
}unique_id;

typedef struct fsmt fsm_t;
typedef struct fsm_step fsm_step_t;

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

/**********************************  sheduler functions capi  ********************************/

/**
 * @brief initiate shedulers buffers
 */
void fsm_sheduler_init(void);

/**
* @brief run FSM execution (add to list)
*/ 
bool  fsm_sheduler_fsm_start(fsm_t* fsm, void* params, bool simult);

/**
* @brief run FSM execution with time delay (add to list)
*/
bool fsm_sheduler_fsm_delayed_start(fsm_t *fsm, void* params, timestamp_t timestamp, bool simult);

/**
* @brief safe run FSM execution(add it to the list or delete it if it
*  is already in the list, but has not yet been processed) 
*/     
bool  fsm_sheduler_fsm_safe_start(fsm_t* p_fsm, void* params, bool simult);

/**
* @brief force terinate FSM by unique id
*/
bool  fsm_sheduler_fsm_force_terminate_uid(unique_id uid);

/**
* @brief force terinate FSM by fsm id
*/
bool  fsm_sheduler_fsm_force_terminate_fid(fsm_id_t fsm_id); 

/**
* @brief force terminate all in active list
*/
void  fsm_sheduler_force_terminate_all_list(void);

/**
* @brief fsm execution loop
*/     
void  fsm_sheduler_dispatch(void);


extern fsm_t test_fsm_a;
extern const fsm_step_t test_fsm_a_prog[];

extern fsm_t test_fsm_b;
extern const fsm_step_t test_fsm_b_prog[];

extern fsm_t test_fsm_c;
extern const fsm_step_t test_fsm_c_prog[];

/*
 * common for many fsms
 */
//extern int  stage_before_wait;
//extern encoder_pos_t encoder_pos_before_move;
//extern encoder_pos_t encoder_distance;

//bool wait_movement_end_common(fsm_t* p_fsm);
//encoder_pos_t get_encoders_distance_after_move();

#ifdef __cplusplus
}
#endif

#endif // __FSM_TYPES_CAPI_H