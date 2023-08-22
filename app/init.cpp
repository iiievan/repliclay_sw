#include "init.h"
#include "n_EDMA.h"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS

void init_board(void)
{ 

    /// Для ускорения работы чтобы не было медленнее Cortex M3 требуется включать предсказание ветвления, кэш и MMU.///
    InitMem();                     // Initiate MMU and instruction Cache  
    CP15BranchPredictionEnable();    // Enable Branch Prediction включаем предсказание ветвления - нужно для ускорения работы.
    
    //__iar_dynamic_initialization();       // in case using RTOS
    UART_0.setup(); 
}
