
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
#include "n_UART.h"
#include "error.h"
#include "cp15.h"
#include "hal_mmu.h"
#include "uart_irda_cir.h"
#include "UART_DT_driver.h"
#include "terminal/x_Print.h"

#ifndef beaglebone_black    // such a timer has not yet been described in DM_Timer.h
     OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_1);
#endif
OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_2);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_3);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_4);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_5);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_6);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_7);

extern void  BRDINFO_24LC32A_irqhandler(void *p_obj);
extern void  CAT24C256WI_irqhandler(void *p_obj);

I2C_EEPROM<(32*1024),32> BRDINFO_24LC32A(I2C::AM335X_I2C_0, SLAVE_ADDR_24LC32A, BRDINFO_24LC32A_irqhandler);
I2C_EEPROM<(32*1024),64> CAT24C256WI(I2C::AM335X_I2C_2, SLAVE_ADDR_CAT24C256, CAT24C256WI_irqhandler);

void init_board(void)   
{ 
    /// Initialize MMU,Cache,Branch prediction etc... ///
    InitMem();                     // Initiate MMU and ... Invoke Cache  
    CP15BranchPredictionEnable();  // Enable Branch Prediction Shit */
    
    /// Initialize Interrupt controller /// 
    intc.master_IRQ_enable();      // Enable IRQ in CPSR
    intc.init();                   // Initializing the ARM Interrupt Controller.
    
    /// Initialize the OS-tick timer console /// 
    os_timer.setup(OS_TIMER_RLD_COUNT);
    
    /// Initialize the UART console /// 
    // If UART interrupts are used, 
    // setup them before the interrupt controller (INTC) is initiated
    uart_driver.probe((void *)&print);  // set read and write methods to "print" obj
    uart_driver.init();   
    
    print.ln("AM335x UART Driver started!");
    
    /// Initialize GPIO's ///
    GPIOModuleClkConfig(1);             // Enabling functional clocks for GPIO1 instance.
    GPIOModuleEnable(SOC_GPIO_1_REGS);  // Enabling the GPIO module.
    GPIOModuleReset(SOC_GPIO_1_REGS);   // Resetting the GPIO module. */
    
    //board_info_check((uint8_t *)BBB_A3_VERSION);
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

uint32_t board_info_check(uint8_t *board_ver)
{
    uint8_t  board_id[30];
    uint8_t *p_Read = BRDINFO_24LC32A.read({.addr = 0x0000},30);
    
    std::memcpy(&board_id[0],p_Read, sizeof(board_id));
    
    if(!(strcmp(BBB_BOARD_NAME, (char *)board_id)))
    {
        if(!(strcmp(BBB_A1_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A1;
        }
        else if(!(strcmp(BBB_A2_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A2;
        }
        else if(!(strcmp(BBB_A3_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A3;
        }
        else if(!(strcmp(BBB_A5_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A5;
        }
        else if(!(strcmp(BBB_A6_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A6;
        }
        else
        {
            return BOARD_VER_UNKNOWN;
        }
    }
    else
    {
        return BOARD_UNKNOWN;
    }
}

