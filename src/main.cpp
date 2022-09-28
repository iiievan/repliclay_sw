
#include "consoleUtils.h"
#include "soc_AM335x.h"
#include "hw_intc.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "dmtimer.h"
#include "error.h"


#include "hal_bspInit.h"
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
  
extern void Entry(void);

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
static  void  AppTaskCreate             (void);
static  void  AppEventCreate            (void);
extern void  OS_CPU_ExceptHndlr (CPU_INT32U  src_id);
extern void  BSP_IntHandler       (CPU_INT32U     src_nbr);
extern void  BSP_IntClr (CPU_INT08U  int_id);

#define  REG_INTCPS_SIR_IRQ      (*(CPU_REG32 *)(SOC_AINTC_REGS + INTC_SIR_IRQ))
#define  REG_INTCPS_SIR_FIQ      (*(CPU_REG32 *)(SOC_AINTC_REGS + INTC_SIR_FIQ))
#define  REG_INTCPS_CONTROL      (*(CPU_REG32 *)(SOC_AINTC_REGS + INTC_CONTROL))
#define  REG_INTCPS_ISR_CLEAR(x) (*(CPU_REG32 *)(SOC_AINTC_REGS + INTC_ISR_CLEAR(x)))
#define  ACTIVE_IRQ_MASK                                (0x7F)
#define  ACTIVE_FIQ_MASK                                (0x7F)

static CPU_FNCT_PTR BSP_IntVectTbl[SYS_INT_ID_MAX];

void init(void)
{
	halBspInit();
}

static  void  OS_BSP_ExceptHandler (CPU_INT08U  except_type)
{
    switch (except_type) {
        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
             while (DEF_TRUE) {
                 ;
             }
    }
}

void  OS_CPU_ExceptHndlr (CPU_INT32U  src_id)
{
    switch (src_id) {
        case OS_CPU_ARM_EXCEPT_IRQ:
        case OS_CPU_ARM_EXCEPT_FIQ:
             BSP_IntHandler((CPU_INT32U)src_id);
             break;

        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
        default:
             OS_BSP_ExceptHandler((CPU_INT08U)src_id);
             break;
    }
}

void  BSP_IntClr (CPU_INT08U  int_id)
{
    CPU_INT08U  reg_nbr;


    if (int_id > SYS_INT_ID_MAX) {
        return;
    }

    reg_nbr = int_id / 32;

    REG_INTCPS_ISR_CLEAR(reg_nbr) = DEF_BIT(int_id % 32);
}

void  BSP_IntHandler (CPU_INT32U  src_nbr)
{
    CPU_INT32U    int_nbr;
    CPU_FNCT_PTR  isr;


    switch (src_nbr) {
        case OS_CPU_ARM_EXCEPT_IRQ:
             int_nbr = REG_INTCPS_SIR_IRQ;

             isr = BSP_IntVectTbl[int_nbr & ACTIVE_IRQ_MASK];
             if (isr != (CPU_FNCT_PTR)0) {
                 isr((void *)int_nbr);
             }
			 BSP_IntClr(int_nbr);                               /* Clear interrupt									   	*/

			 REG_INTCPS_CONTROL = INTC_CONTROL_NEWIRQAGR;
             break;

        case OS_CPU_ARM_EXCEPT_FIQ:
             int_nbr = REG_INTCPS_SIR_FIQ;

             isr = BSP_IntVectTbl[int_nbr & ACTIVE_FIQ_MASK];
             if (isr != (CPU_FNCT_PTR)0) {
                 isr((void *)int_nbr);
             }
			 BSP_IntClr(int_nbr);                       		/* Clear interrupt									   	*/

			 REG_INTCPS_CONTROL = INTC_CONTROL_NEWFIQAGR;
             break;

        default:
             break;
    }
}



static  void  AppTaskStart (void *p_arg)
{
    (void)p_arg;
    CPU_INT32U i;
    
    Mem_Init();                                                 /* Initialize memory managment module                   */
    Math_Init();
    
 #if (OS_TASK_STAT_EN > 0)
    OSStatInit();                                               /* Determine CPU capacity                               */
#endif
  
      while (DEF_TRUE) {
        ConsoleUtilsPrintf("Task 1 message %d!\r\n", i++);
        OSTimeDlyHMSM(0, 0, 0, 100);
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
 
    //BSP_BranchPredictorEn();                                    /* Enable Branch Predictor and Cache.                   */
    //BSP_CachesEn();
    
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

