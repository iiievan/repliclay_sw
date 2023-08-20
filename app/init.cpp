#include "init.h"
#include "n_EDMA.h"
//#include "cp15.h"
//#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS

void init_board(void)
{ 
      /// Initialize MMU,Cache,Branch prediction etc... ///
    //InitMem();                     // Initiate MMU and ... Invoke Cache  
    //CP15BranchPredictionEnable();  // Enable Branch Prediction Shit */
    
    //__iar_dynamic_initialization();       // in case using RTOS
    UART_0.setup(); 
}
