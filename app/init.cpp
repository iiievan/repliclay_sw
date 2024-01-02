#include "stdint.h"
#include "init.h"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS
#include "am335x_intc.h"
#include "am335x_dmtimer.h"
#include "am335x_gpio.h"
#include "pin.h"
#include "sys_timer.h"
#include "PRCM.h"


const uint32_t AM335X_VECTOR_BASE = 0x4030FC00;

extern "C" void Entry(void);
extern "C" void UndefInstHandler(void);
extern "C" void SVC_Handler(void);
extern "C" void AbortHandler(void);
extern "C" void IRQHandler(void);
extern "C" void FIQHandler(void);

// 1ms system timer for system time
sys_timer sys_time(REGS::DMTIMER::AM335X_DMTIMER_2);
//am335x_gpio gpio0(REGS::GPIO::AM335x_GPIO_0);
am335x_gpio gpio1(REGS::GPIO::AM335x_GPIO_1);
//am335x_gpio gpio2(REGS::GPIO::AM335x_GPIO_2);
//am335x_gpio gpio3(REGS::GPIO::AM335x_GPIO_3);



static uint32_t const vec_tbl[14]=
{
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018,    /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF014,    /* Opcode for loading PC with the contents of [PC + 0x14] */
    0xE24FF008,    /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    0xE59FF010,    /* Opcode for loading PC with the contents of [PC + 0x10] */
    (uint32_t)Entry,
    (uint32_t)UndefInstHandler,
    (uint32_t)SVC_Handler,
    (uint32_t)AbortHandler,
    (uint32_t)IRQHandler,
    (uint32_t)FIQHandler
};

static void copy_vector_table(void)
{
    uint32_t *dest = (uint32_t *)AM335X_VECTOR_BASE;
    uint32_t *src  = (uint32_t *)vec_tbl;
    uint32_t count;
  
    CP15VectorBaseAddrSet(AM335X_VECTOR_BASE);

    for(count = 0; count < sizeof(vec_tbl)/sizeof(vec_tbl[0]); count++)
    {
        dest[count] = src[count];
    }
}

void init_board(void)
{ 
    copy_vector_table();


    /// Для ускорения работы чтобы не было медленнее Cortex M3 требуется включать предсказание ветвления, кэш и MMU.///
    InitMem();                          // Initiate MMU and instruction Cache  
    CP15BranchPredictionEnable();       // Enable Branch Prediction включаем предсказание ветвления - нужно для ускорения работы.    
    //__iar_dynamic_initialization();   // in case using RTOS
        
    intc.init();                       //Initializing the ARM Interrupt Controller.
    
    // setup system timer for 1ms interrupt 
    sys_time.setup(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE,
                   SYS_TIMER_RLD_COUNT,
                   (REGS::INTC::MAX_IRQ_PRIORITIES - 1)); 
    
    gpio1.module_enable();
    gpio1.module_reset();
    
    APP_LED.init(); 
    APP_LED.switch_function(APP_PIN);
    APP_LED.dir_set(REGS::GPIO::GPIO_OUTPUT); 
    
    intc.master_IRQ_enable();       
}

