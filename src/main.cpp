
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "hw_intc.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"


#include "init.h"
#include "n_UART.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "PRCM.h"
#include "INTC.h"
#include "I2C_EEPROM.h"
#include "app_utils.h"
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
uint8_t data_read[64];
EEPROM_byte_address_t addr1 = {.addr = 0x0002};
EEPROM_byte_address_t addr2 = {.addr = 0x0050};
EEPROM_byte_address_t addr3 = {.addr = 0x0030};

char str2[] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz123456123456";
	
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
      

    //CAT24C256WI.write({.addr = 0x0000},(uint8_t *)str2, (sizeof(str2) - 1));    // get rid of /0 symbol
      CAT24C256WI.write_byte(addr1, 0xEE);
      CAT24C256WI.write_byte(addr2, 0xAA);
      CAT24C256WI.write_byte(addr3, 0x55);


        
    //uint8_t * p_Read = CAT24C256WI.read({.addr = 0x0002},64);
    uint8_t p_Read = CAT24C256WI.read_byte(addr1);
            p_Read = CAT24C256WI.read_byte(addr2);
            p_Read = CAT24C256WI.read_byte(addr3);

       
    //std::memcpy(&data_read[0],p_Read, sizeof(data_read));    
    
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
