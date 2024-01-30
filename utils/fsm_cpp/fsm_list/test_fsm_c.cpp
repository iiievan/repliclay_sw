#include "stdint.h"
//#include "SEGGER_RTT.h"

#include "fsm.h"
#include "fsm_types_capi.h"
//#include "tim.h"

//-------------------------------------------------------------------------------------------------
// FSM test_fsm_c:
//-------------------------------------------------------------------------------------------------
fsm_t  test_fsm_c;

#define REPEATES_NUM (7)
static float last_dt = 0.0f;
static uint32_t repeats = 1;
static float  ms = 0;

static bool test_fsm_init(fsm_t* fsm)
{
    repeats = 0;
    ms = GET_MS();
    //SEGGER_RTT_printf(0, "dti(:%d:)\r\n", ms);

    return false;
}

static bool test_fsm(fsm_t* fsm)
{
    repeats++;
    ms = GET_MS();

    if (repeats < REPEATES_NUM)
        fsm_repeat_step(fsm);

    //SEGGER_RTT_printf(0, "dt(:%d:)\r\n", ms);
    last_dt = GET_MS();

    return false;
}

static bool test_fsm_c_end(fsm_t* fsm)
{
    if (repeats < REPEATES_NUM)
        fsm_go_to(fsm, 1);
    else
    	ms = 0;

    return false;
}

const fsm_step_t test_fsm_c_prog[] = 
{
     /*0*/  {1, 10,     (void const*) test_fsm_init},
     /*1*/  {1, 10,     (void const*) test_fsm},
     /*2*/  {1, 100,    (void const*) NULL},
     /*3*/  {1, 5,      (void const*) test_fsm_c_end},
            {0}
};
//-------------------------------------------------------------------------------------------------
