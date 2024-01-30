#include "stdint.h"
#include "init.h"
#include "board.hpp"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS
#include "am335x_intc.h"
#include "am335x_dmtimer.h"
#include "am335x_gpio.h"
#include "am335x_rtc.h"
#include "pin.h"
//ghj#include "clock.h"
#include "sys_timer.h"
#include "fsm_timer.h"
#include "PRCM.h"
#include "DMTIMER1MS.h"
#include "fsm_types_capi.h"

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

// precision 1ms system timer for system time
sys_timer<SYST_t> sys_time(SYST_TIMER_ptr);
fsm_timer<FSMT_t> fsm_time(FSMT_TIMER_ptr);
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

void init_board(void)
{ 
    copy_vector_table();

    /// ��� ��������� ������ ����� �� ���� ��������� Cortex M3 ��������� �������� ������������ ���������, ��� � MMU.///
    InitMem();                          // Initiate MMU and instruction Cache  
    CP15BranchPredictionEnable();       // Enable Branch Prediction �������� ������������ ��������� - ����� ��� ��������� ������.    
    //__iar_dynamic_initialization();   // in case using RTOS
            
    intc.init();                       //Initializing the ARM Interrupt Controller. 
    
    REGS::RTC::TIME_t time = {.HOUR = 12, .MIN = 34, .SEC = 0};
    REGS::RTC::CALENDAR_t calendar = {.YEAR = 24, .MONTH = 1, .DAY = 25};    
    
    rtc_module.setup(time,calendar, REGS::RTC::CLK32K_EXTERNAL);
    
    // setup system timer for 1ms interrupt 
    sys_time.init();
    
    gpio1.init();     
    USR_LED_0.sel_pinmode(PINS::e_GPMC_A5::gpio1_21);
    USR_LED_0.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_1.sel_pinmode(PINS::e_GPMC_A6::gpio1_22);
    USR_LED_1.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_2.sel_pinmode(PINS::e_GPMC_A7::gpio1_23);
    USR_LED_2.dir_set(REGS::GPIO::GPIO_OUTPUT);    
    USR_LED_3.sel_pinmode(PINS::e_GPMC_A8::gpio1_24);
    USR_LED_3.dir_set(REGS::GPIO::GPIO_OUTPUT);
    DBG_PIN1.sel_pinmode(PINS::e_UART0_TXD::gpio1_11);
    DBG_PIN1.dir_set(REGS::GPIO::GPIO_OUTPUT);
    
    DBG_PIN1.clear();
    
    gpio0.init();
    END_STOP_X_2.sel_pinmode(PINS::e_GPMC_WAIT0::gpio0_30);
    END_STOP_X_2.dir_set(REGS::GPIO::GPIO_INPUT);
    END_STOP_X_2.pullup_enable(false);
    //END_STOP_X_2.sel_pull_type(REGS::CONTROL_MODULE::PULL_DOWN);
    END_STOP_X_2.sel_slewrate(REGS::CONTROL_MODULE::SLOW);
    
    intc.master_IRQ_enable();    
}

void init_fsm(void)
{
  action_cmd usr_led_0_cmd = { .name = "usrled0", 
                               .repetitions = 8, 
                               .rep_delay = 250 ,
                               {.HOUR = 12, .MIN = 35, .SEC = 30} };
    fsm_construct_static(&test_fsm_a,FSM_TEST_A, test_fsm_a_prog);
    //test_fsm_a.m_can_run_simultaneously = true;
    
    fsm_start(&test_fsm_a,(void *)&usr_led_0_cmd);
    
    fsm_time.init(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE);
    fsm_time.enable();
}
