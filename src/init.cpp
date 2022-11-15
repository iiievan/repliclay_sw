
#include "init.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "hw_cm_per.h"
#include "hw_cm_wkup.h"
#include "beaglebone.h"

#include "gpio_v2.h"
#include "consoleUtils.h"
#include "interrupt.h"

#include "dmtimer.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "HS_I2C.h"
#include "I2C_EEPROM.h"
#include "error.h"
#include "cp15.h"
#include "hal_mmu.h"

#ifndef beaglebone_black    // such a timer has not yet been described in DM_Timer.h
     OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_1);
#endif
OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_2);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_3);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_4);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_5);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_6);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_7);

I2C_EEPROM CAT24C256WI(I2C::AM335X_I2C_0, I2C_SLAVE_ADDR);

void init_board(void)   
{ 
    InitMem();                     // Initiate MMU and ... Invoke Cache  
    CP15BranchPredictionEnable();  // Enable Branch Prediction Shit */
 
    intc.master_IRQ_enable();      // Enable IRQ in CPSR
    intc.init();                   // Initializing the ARM Interrupt Controller.
    
    /* Initialize the UART console */
    ConsoleUtilsInit();
    ConsoleUtilsSetType(CONSOLE_UART); // Select the console type based on compile time check
    
    os_timer.setup(OS_TIMER_RLD_COUNT);
    CAT24C256WI.setup();
    
    GPIOModuleClkConfig(1);             // Enabling functional clocks for GPIO1 instance.
    GPIOModuleEnable(SOC_GPIO_1_REGS);  // Enabling the GPIO module.
    GPIOModuleReset(SOC_GPIO_1_REGS);   // Resetting the GPIO module. */
}

void GPIOModuleClkConfig(CPU_INT32U x)
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
