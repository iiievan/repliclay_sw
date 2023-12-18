#include "stdint.h"
#include "init.h"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS
#include "am335x_intc.h"
#include "am335x_dmtimer.h"
#include "PRCM.h"

extern "C" void Entry(void);
extern "C" void UndefInstHandler(void);
extern "C" void SVC_Handler(void);
extern "C" void AbortHandler(void);
extern "C" void IRQHandler(void);
extern "C" void FIQHandler(void);

static uint64_t time_from_boot = 0;

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

const uint32_t AM335X_VECTOR_BASE = 0x4030FC00;

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
    dmtimer_setup(); 
    
    REGS::PRCM::run_clk_GPIO1();
    

    GPIO1Pin23PinMuxSetup(); // GPIO1_23  
    GPIOModuleEnable(GPIO_INSTANCE_ADDRESS);
    GPIOModuleReset(GPIO_INSTANCE_ADDRESS);
    GPIODirModeSet(GPIO_INSTANCE_ADDRESS,
                   GPIO_INSTANCE_PIN_NUMBER,
                   GPIO_DIR_OUTPUT);
    
    intc.master_IRQ_enable();       
}

#define OS_TIMER dm_timer_2
#define OS_TIMER_INTERRUPT  (REGS::INTC::TINT2)

void dmtimer_setup(void)
{
    // run clock for timer instance
    REGS::PRCM::run_clk_DMTIMER(REGS::DMTIMER::TIMER_2); 

    // setup timer interrupt in INTC
    intc.register_handler(OS_TIMER_INTERRUPT,(isr_handler_t)dmtimer_irqhandler);     // Registering dmtimer_irqhandler
    intc.priority_set(OS_TIMER_INTERRUPT,(REGS::INTC::MAX_IRQ_PRIORITIES - 1));      // Set the lowest priority
    intc.unmask_interrupt(OS_TIMER_INTERRUPT); 
    
    OS_TIMER.counter_set(DMTIMER_RLD_COUNT); //Load the counter with the initial count value
    OS_TIMER.reload_set(DMTIMER_RLD_COUNT);    //Load the load register with the reload count value
    OS_TIMER.mode_configure(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE); //Configure the DMTimer for Auto-reload and compare mode 
    
    OS_TIMER.IRQ_enable(REGS::DMTIMER::IRQ_OVF);
    
    OS_TIMER.enable();
}

void dmtimer_irqhandler(void *p_obj)
{  
    OS_TIMER.IRQ_disable(REGS::DMTIMER::IRQ_OVF); // Disable the DMTimer interrupts    
    OS_TIMER.IRQ_clear(REGS::DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags 

    time_from_boot++;
    
    OS_TIMER.IRQ_enable(REGS::DMTIMER::IRQ_OVF);  // Enable the DM_Timer interrupts
    intc.unmask_interrupt(OS_TIMER_INTERRUPT);  
}
