#include "stdint.h"
#include "init.h"
#include "board.h"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS
#include "am335x_intc.h"
#include "am335x_dmtimer.h"
#include "am335x_gpio.h"
#include "pin.h"
//ghj#include "clock.h"
#include "sys_timer.h"
#include "PRCM.h"
#include "DMTIMER1MS.h"
//#include "interrupt.h"
//#include "dmtimer.h"
//#include "soc_AM335x.h"

const uint32_t AM335X_VECTOR_BASE = 0x4030FC00;

extern "C" void Entry(void);
extern "C" void UndefInstHandler(void);
extern "C" void SVC_Handler(void);
extern "C" void AbortHandler(void);
extern "C" void IRQHandler(void);
extern "C" void FIQHandler(void);

// ~1ms system timer for system time
sys_timer sys_time(REGS::DMTIMER::AM335X_DMTIMER_2);
am335x_gpio gpio0(REGS::GPIO::AM335x_GPIO_0);
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

static void clearTimer1Int(void *p_obj)
{
	//HWREG(0x44e31018) = 0x2;  //TISR 
    dm_timer_1ms.IRQ_clear(REGS::DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags
}

static void initializeTimer1(void)
{
    REGS::PRCM::run_clk_DMTIMER_1ms(REGS::PRCM::MS1_M_OSC);
        
	//	wake up configs
	//HWREG(0x44e31010) = 0x214; //TIOCP_CFG  set EnaWakeup,SMART_IDLE,ClockActivity = 0x2

	//	enable overflow int
	//HWREG(0x44e3101c) = 0x2; //TIER

	//	enable overflow wakeup
	//HWREG(0x44e31020) = 0x2;  //TWER
    intc.register_handler(REGS::INTC::TINT1_1MS, clearTimer1Int);
    intc.priority_set(REGS::INTC::TINT1_1MS, 0);      
    intc.unmask_interrupt(REGS::INTC::TINT1_1MS);
    
    dm_timer_1ms.counter_set(SYS_TIMER_RLD_COUNT);                                  //Load the counter with the initial count value
    dm_timer_1ms.reload_set(SYS_TIMER_RLD_COUNT);                                   //Load the load register with the reload count value
    dm_timer_1ms.mode_configure(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE);   //Configure the DMTimer for Auto-reload and compare mode 
        
    dm_timer_1ms.IRQ_enable(REGS::DMTIMER::IRQ_OVF);
        
    dm_timer_1ms.enable(); 
    
    //IntSystemEnable(SYS_INT_TINT1_1MS);
    //IntPrioritySet(SYS_INT_TINT1_1MS, 0, AINTC_HOSTINT_ROUTE_IRQ);
    //IntRegister(SYS_INT_TINT1_1MS,clearTimer1Int);
}

void init_board(void)
{ 
    copy_vector_table();

    /// ��� ��������� ������ ����� �� ���� ��������� Cortex M3 ��������� �������� ������������ ���������, ��� � MMU.///
    InitMem();                          // Initiate MMU and instruction Cache  
    CP15BranchPredictionEnable();       // Enable Branch Prediction �������� ������������ ��������� - ����� ��� ��������� ������.    
    //__iar_dynamic_initialization();   // in case using RTOS
            
    intc.init();                       //Initializing the ARM Interrupt Controller.
    
    initializeTimer1();
    // setup system timer for 1ms interrupt 
    sys_time.setup(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE,
                   SYS_TIMER_RLD_COUNT,
                   (REGS::INTC::MAX_IRQ_PRIORITIES - 1));        
    
    gpio1.init();     
    USR_LED_0.sel_pinmode(PINS::e_GPMC_A5::gpio1_21);
    USR_LED_0.dir_set(REGS::GPIO::GPIO_OUTPUT); 
    
    USR_LED_3.sel_pinmode(PINS::e_GPMC_A8::gpio1_24);
    USR_LED_3.dir_set(REGS::GPIO::GPIO_OUTPUT);
    
    gpio0.init();
    END_STOP_X_2.sel_pinmode(PINS::e_GPMC_WAIT0::gpio0_30);
    END_STOP_X_2.dir_set(REGS::GPIO::GPIO_INPUT);
    END_STOP_X_2.pullup_enable(false);
    //END_STOP_X_2.sel_pull_type(REGS::CONTROL_MODULE::PULL_DOWN);
    END_STOP_X_2.sel_slewrate(REGS::CONTROL_MODULE::SLOW);
    
    intc.master_IRQ_enable();    
}
