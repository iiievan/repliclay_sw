#include "stdint.h"
//#include "SEGGER_RTT.h"

#include "fsm.h"
//#include "tim.h"

//-------------------------------------------------------------------------------------------------
// FSM test_fsm_a:
//-------------------------------------------------------------------------------------------------
#define REPEATES_NUM (7)
fsm_t  test_fsm_a;
static float last_t = 0;
static uint32_t repeats = 1;
static float  ms = 0;

static bool test_fsm_init(fsm_t* fsm)
{
    repeats = 0;
    last_t = GET_MS();
    //SEGGER_RTT_printf(0, "step0.test_fsm_a_init\r\n");

    return false;
}

static bool test_fsm(fsm_t* fsm)
{
    repeats++;
    ms = GET_MS();

    if (repeats < REPEATES_NUM)
    	fsm_repeat_step(fsm);

    //SEGGER_RTT_printf(0, "step1.test_fsm_a.dt(%d)\r\n", (int)(ms - last_t));
    last_t = GET_MS();

    return false;
}

static bool test_fsm_a_end(fsm_t* fsm)
{
    ms = GET_MS();
    //SEGGER_RTT_printf(0, "step3.test_fsm_a_end(%d:)\r\n", (int)last_t);

	repeats = 0;
    ms = 0;
    last_t = 0;

    return false;
}

const fsm_step_t test_fsm_a_prog[] = 
{
    /*0*/   {1, 10,   (void const*) test_fsm_init},
    /*1*/   {1, 50,   (void const*) test_fsm},
    /*2*/   {1, 100,  (void const*) NULL},
    /*3*/   {1, 5,    (void const*) test_fsm_a_end},
            {0}
};
//-------------------------------------------------------------------------------------------------
