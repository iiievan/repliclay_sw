/* 
 * \file   hal_bspInit.c
 *
 * \brief  Overall Board Init Module for AM335X(CA8 + INTC) Port of FreeRTOS
*/
/*
    Author: Abhinav Tripathi <mr dot a dot tripathi at gmail dot com>

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
    MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
    SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
    OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
    IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
    OF SUCH DAMAGE.

    Copyright (c) 2018 Abhinav Tripathi.
    All Rights Reserved.
*/
#ifndef HAL_BSPINIT_C
#define HAL_BSPINIT_C
/**************************************************************************************************************************/
/*                                                     INCLUDE FILES                                                      */
/**************************************************************************************************************************/
#include "hw_types.h"
#include "soc_AM335x.h"
#include "hw_cm_per.h"
#include "hw_cm_wkup.h"
#include "beaglebone.h"

#include "gpio_v2.h"
#include "hal_bspInit.h"
#include "consoleUtils.h"
#include "interrupt.h"

#include "dmtimer.h"
#include "DM_Timer.h"
#include "error.h"
#include "cp15.h"
#include "hal_mmu.h"
#include <uC_cpu.h>
#include  <os.h>

/**************************************************************************************************************************/
/*                                                     CONFIGURATIONS                                                     */
/**************************************************************************************************************************/


/**************************************************************************************************************************/
/*                                                         MACROS                                                         */
/**************************************************************************************************************************/


/**************************************************************************************************************************/
/*                                                        LITERALS                                                        */
/**************************************************************************************************************************/


/**************************************************************************************************************************/
/*                                                       DATA TYPES                                                       */
/**************************************************************************************************************************/


/**************************************************************************************************************************/
/*                                                  FUNCTION PROTOTYPES                                                   */
/**************************************************************************************************************************/

static void DMTimerAintcConfigure(void);
static void DMTimerSetUp(void);
static void GPIOModuleClkConfig(CPU_INT32U x);

/**************************************************************************************************************************/
/*                                                    GLOBAL VARIABLES                                                    */
/**************************************************************************************************************************/

extern volatile CPU_INT32U ulPortYieldRequired;
volatile unsigned int cntValue = 0;
static volatile unsigned int flagIsr = 0;

/**************************************************************************************************************************/
/*                                                          LUTS                                                          */
/**************************************************************************************************************************/


/**************************************************************************************************************************/
/*                                                          CODE                                                          */
/**************************************************************************************************************************/

void configure_platform(void)
{
    /* Initiate MMU and ... Invoke Cache */
    InitMem(); 
    
     /* Initializing the ARM Interrupt Controller. */
    IntAINTCInit();
    
    //BSP_IntInit();
    
    /* Enable Branch Prediction Shit */
    CP15BranchPredictionEnable();
    
    /* Initialize the UART console */
    ConsoleUtilsInit();

    /* Select the console type based on compile time check */
    ConsoleUtilsSetType(CONSOLE_UART);

    /* This function will enable clocks for the DMTimer2 instance */
    //DMTimer2ModuleClkConfig();
    OS_TIMER.init();
    /* Register DMTimer2 interrupts on to AINTC */
    DMTimerAintcConfigure();

    /* Perform the necessary configurations for DMTimer */
    DMTimerSetUp();
}

void halBspInit(void)   
{
    configure_platform();
    /* Enabling functional clocks for GPIO1 instance. */
    GPIOModuleClkConfig(1);

	/* Enabling the GPIO module. */
	GPIOModuleEnable(SOC_GPIO_1_REGS);

	/* Resetting the GPIO module. */
	GPIOModuleReset(SOC_GPIO_1_REGS);
}


/*
** Do the necessary DMTimer configurations on to AINTC.
*/
#define configMAX_IRQ_PRIORITIES                ((CPU_INT32U)(0x3Ful))

static void DMTimerAintcConfigure(void)
{
    /* Registering DMTimerIsr */
    //IntRegister(SYS_INT_TINT2, DMTimerIsr);
    BSP_IntVectReg(SYS_INT_TINT2,(CPU_FNCT_PTR)DMTimer_irqhandler);
    /* Set the priority */
    IntPrioritySet(SYS_INT_TINT2,(configMAX_IRQ_PRIORITIES -1), AINTC_HOSTINT_ROUTE_IRQ); /* Lowest Priority */

    /* Enable the system interrupt */
    IntSystemEnable(SYS_INT_TINT2);
}


/*
** Setup the timer for one-shot and compare mode.
** Setup the timer 2 to generate the tick interrupts at the required frequency.
 */

#define DMTIMER2_INITIAL_COUNT             (0xffffa261) // 1ms approximate
#define DMTIMER2_RLD_COUNT                 (0xffffa261) // 1ms approximate

static void DMTimerSetUp(void)
{
    uint32_t dmtimer_mode =  DMTIMER::MODE_AUTORELOAD | (!DMTIMER::MODE_COMPARE); //  mode : autoreload and no compare
    /* Load the counter with the initial count value */
    OS_TIMER.counter_set(DMTIMER2_INITIAL_COUNT);
    /* Load the load register with the reload count value */
    OS_TIMER.reload_set(DMTIMER2_RLD_COUNT);
    /* Configure the DMTimer for Auto-reload and compare mode */
    OS_TIMER.mode_configure((DMTIMER::e_DMTIMER_mode)dmtimer_mode);
}

static void GPIOModuleClkConfig(CPU_INT32U x)
{
    switch(x)
    {
        case 0:
            GPIO0ModuleClkConfig();
        break;
        case 1:
            GPIO1ModuleClkConfig();
        break;
    }
}

void hal_init(void)
{
    halBspInit();
}

#endif /* #ifndef HAL_BSPINIT_C */