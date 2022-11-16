
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "hw_intc.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"


#include "init.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "PRCM.h"
#include "INTC.h"
#include "I2C_EEPROM.h"
#include  <uC_cpu.h>
#include  <app_cfg.h>
#include  <cpu_cfg.h>
#include  <cpu_core.h>
#include  <os.h>
#include  <lib_mem.h>
#include  <lib_math.h>

#include <string>

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
uint8_t data_read[50];
uint8_t temp;
	
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
    
    BRDINFO_24LC32A.EEPROM_Read(data_read);
      
    for(uint32_t i = 0; i < 50; i++)
    {
        /* Collecting the Most Significant Nibble of the data byte. */
        temp = ((data_read[i] & 0xF0) >> 4);
    
        if(temp < 10)
            ConsoleUtilsPrintf("%c", (temp + 0x30));
        else
            ConsoleUtilsPrintf("%c", (temp + 0x37));
    
        /* Collecting the Least Significant Nibble of the data byte. */
        temp = (data_read[i] & 0x0F);
    
        if(temp < 10)
            ConsoleUtilsPrintf("%c", (temp + 0x30));
        else
            ConsoleUtilsPrintf("%c", (temp + 0x37));
    
        ConsoleUtilsPrintf("%c", ',');
    }
      
    while (DEF_TRUE) 
    {
        ConsoleUtilsPrintf("Task 1 message %d!\r\n", tm++);
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
