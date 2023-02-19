
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "hw_intc.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"
#include "utils.h"


#include "init.h"
#include "n_UART.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "PRCM.h"
#include "INTC.h"
#include "I2C_EEPROM.h"
#include "utils.h"
#include  "utils/paired_buffer.h"
#include  "utils/frame_buffer.h"
#include  "utils/ring_buffer.h"
#include  "terminal/x_Print.h"
#include  <uC_cpu.h>
#include  <app_cfg.h>
#include  <cpu_cfg.h>
#include  <cpu_core.h>
#include  <os.h>
#include  <lib_mem.h>
#include  <lib_math.h>

#include <string>
#include <cstring>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
 /*
*********************************************************************************************************
*                                             LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                            LOCAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK        AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart              (void *p_arg);
//static  void  AppTaskCreate             (void);
//static  void  AppEventCreate            (void);

static  void  AppTaskStart (void *p_arg)
{
    (void)p_arg;
    CPU_INT32U tm;
	
    print.ln("Enabling timer interrupt!");
    
    os_timer.IRQ_enable(DMTIMER::IRQ_OVF);
	
    Mem_Init();                                                 /* Initialize memory managment module                   */
    Math_Init();
    
#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif
    //print.ln("\n");
    //print.ln("Creating Application Objects...");
    //AppEventCreate();                                           /* Create Application Events                            */
    //print.ln("Creating Application Tasks...");
    //AppTaskCreate();                                            /* Create Application Tasks                             */
      
    while (DEF_TRUE) 
    {
        print.ln("Task 1 message %d!", tm++);
        OSTimeDlyHMSM(0, 0, 5,0);
    }
}

#ifdef __cplusplus
}
#endif

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int main() 
{
    CPU_INT08U	os_err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR  cpu_err;
#endif
    init_board();
	
    CPU_IntDis();
    print.ln("Platform initialized.");
	
    OSInit();                                                   /* Init uC/OS-II                                        */

    OSTaskCreateExt(AppTaskStart,                               /* Create the start task.                               */
                    (void *)0,
                    (OS_STK *)&AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
                    APP_CFG_TASK_START_PRIO,
                    APP_CFG_TASK_START_PRIO,
                    (OS_STK *)&AppTaskStartStk[0],
                    APP_CFG_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_EN > 0)
    OSTaskNameSet((INT8U  )APP_CFG_TASK_START_PRIO,
                  (INT8U *)"Start Task",
                  (INT8U *)&os_err);
#endif

    OSStart();  /* Start multitasking (i.e. give control to uC/OS-II.   */
}
