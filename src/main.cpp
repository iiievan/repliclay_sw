
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "hw_intc.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"


#include "hal_bspInit.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "PRCM.h"
#include "INTC.h"
#include  <uC_cpu.h>
#include  <app_cfg.h>
#include  <cpu_cfg.h>
#include  <cpu_core.h>
#include  <os.h>
#include  <lib_mem.h>
#include  <lib_math.h>

#include <string>

using namespace std;

#ifndef beaglebone_black    // such a timer has not yet been described in DM_Timer.h
     OS_Timer os_timer(*DMTIMER::AM335X_DMTIMER_1);
#endif
// OS_Timer os_timer(*DMTIMER::AM335X_DMTIMER_2);
// OS_Timer os_timer(*DMTIMER::AM335X_DMTIMER_3);
// OS_Timer os_timer*DMTIMER::AM335X_DMTIMER_4);
OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_5);
// OS_Timer os_timer(*DMTIMER::AM335X_DMTIMER_6);
// OS_Timer os_timer(*DMTIMER::AM335X_DMTIMER_7);

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

void init(void)
{
	halBspInit();
}

static  void  AppTaskStart (void *p_arg)
{
    (void)p_arg;
    CPU_INT32U i;
	
    ConsoleUtilsPrintf("Enabling timer interrupt!\r\n");
    
    os_timer.IRQ_enable(DMTIMER::IRQ_OVF);
	
    Mem_Init();                                                 /* Initialize memory managment module                   */
    Math_Init();
    
 #if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif
      //ConsoleUtilsPrintf("\n\n\r");
      //ConsoleUtilsPrintf("Creating Application Objects...\n\r");
      //AppEventCreate();                                           /* Create Application Events                            */
      //ConsoleUtilsPrintf("Creating Application Tasks...\n\r");
      //AppTaskCreate();                                            /* Create Application Tasks                             */
    
      while (DEF_TRUE) {
        ConsoleUtilsPrintf("Task 1 message %d!\r\n", i++);
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
    init();
	
    CPU_IntDis();
    ConsoleUtilsPrintf("Platform initialized.\r\n");
	
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

    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II.   */


}

void DMTimer_irqhandler(void *p_obj)
{  
    os_timer.IRQ_disable(DMTIMER::IRQ_OVF); // Disable the DMTimer interrupts    
    os_timer.IRQ_clear(DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags 

    OSTimeTick();
    
    os_timer.IRQ_enable(DMTIMER::IRQ_OVF);  // Enable the DM_Timer interrupts
    intc.system_enable(OS_TIMER_INTERRUPT);  
}

