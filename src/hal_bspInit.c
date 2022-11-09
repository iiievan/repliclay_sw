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
#include "OS_Timer.h"
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
    intc.init(); //Initializing the ARM Interrupt Controller.
    
    /* Enable Branch Prediction Shit */
    CP15BranchPredictionEnable();
    
    /* Initialize the UART console */
    ConsoleUtilsInit();

    /* Select the console type based on compile time check */
    ConsoleUtilsSetType(CONSOLE_UART);
    
    os_timer.setup(OS_TIMER_RLD_COUNT);
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