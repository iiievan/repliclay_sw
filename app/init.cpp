#include "init.h"
#include "n_EDMA.h"
#include "cp15.h"
#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS

void init_board(void)
{ 

    /// ��� ��������� ������ ����� �� ���� ��������� Cortex M3 ��������� �������� ������������ ���������, ��� � MMU.///
    InitMem();                     // Initiate MMU and instruction Cache  
    CP15BranchPredictionEnable();    // Enable Branch Prediction �������� ������������ ��������� - ����� ��� ��������� ������.
    
    //__iar_dynamic_initialization();       // in case using RTOS
    UART_0.setup(); 
}
