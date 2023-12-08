#include "init.h"
#include "cp15.h"
#include "hal_mmu.h"
#include "stdint.h"
//#include "iar_dynamic_init.h" // in case using RTOS
#include "PRCM.h"

extern "C" void Entry(void);
extern "C" void UndefInstHandler(void);
extern "C" void SVC_Handler(void);
extern "C" void AbortHandler(void);
extern "C" void IRQHandler(void);
extern "C" void FIQHandler(void);

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
    
    REGS::PRCM::run_clk_GPIO1();
    //GPIO1ModuleClkConfig();

    GPIO1Pin23PinMuxSetup(); // GPIO1_23  
    GPIOModuleEnable(GPIO_INSTANCE_ADDRESS);
    GPIOModuleReset(GPIO_INSTANCE_ADDRESS);
    GPIODirModeSet(GPIO_INSTANCE_ADDRESS,
                   GPIO_INSTANCE_PIN_NUMBER,
                   GPIO_DIR_OUTPUT);
    
}
