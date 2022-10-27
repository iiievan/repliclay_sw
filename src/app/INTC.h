#ifndef _INTC_H_
#define _INTC_H_

#include <stdint.h>
#include "app_utils.h"

//This is interrupt controller class and his namespace
namespace INTC
{ 
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_INTC_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/      

    struct AM335x_INTC_Type
    {                                                                                      
        __RW  REVISION_reg_t        REVISION;           // (0x00)
        __R   uint32_t              RESERVED[3];  
        __RW  SYSCONFIG_reg_t       SYSCONFIG;          // (0x10) 
        __RW  SYSSTATUS_reg_t       SYSSTATUS;          // (0x14) 
        __R   uint32_t              RESERVED1[10];  
        __RW  SIR_IRQ_reg_t         SIR_IRQ;            // (0x40)  
        __RW  SIR_FIQ_reg_t         SIR_FIQ;            // (0x44)  
        __RW  CONTROL_reg_t         CONTROL;            // (0x48)  
        __RW  PROTECTION_reg_t      PROTECTION;         // (0x4C)  
        __RW  IDLE_reg_t            IDLE;               // (0x50) 
        __R   uint32_t              RESERVED2[3]; 
        __RW  IRQ_PRIORITY_reg_t    IRQ_PRIORITY;       // (0x60)  
        __RW  FIQ_PRIORITY_reg_t    FIQ_PRIORITY;       // (0x64)
        __RW  THRESHOLD_reg_t       THRESHOLD;          // (0x68)
        __R   uint32_t              RESERVED2[5];   
        __RW  ITR0_reg_t            ITR0;               // (0x80)  
        __RW  MIR0_reg_t            MIR0;               // (0x84)  
        __RW  MIR_CLEAR0_reg_t      MIR_CLEAR0;         // (0x88)  
        __RW  MIR_SET0_reg_t        MIR_SET0;           // (0x8C)  
        __RW  ISR_SET0_reg_t        ISR_SET0;           // (0x90)  
        __RW  ISR_CLEAR0_reg_t      ISR_CLEAR0;         // (0x94) 
        __RW  PENDING_IRQ0_reg_t    PENDING_IRQ0;       // (0x98)   
        __RW  PENDING_FIQ0_reg_t    PENDING_FIQ0;       // (0x9C)  
        __RW  ITR1_reg_t            ITR1;               // (0xA0)
        __RW  MIR1_reg_t            MIR1;               // (0xA4)  
        __RW  MIR_CLEAR1_reg_t      MIR_CLEAR1;         // (0xA8)  
        __RW  MIR_SET1_reg_t        MIR_SET1;           // (0xAC)  
        __RW  ISR_SET1_reg_t        ISR_SET1;           // (0xB0)  
        __RW  ISR_CLEAR1_reg_t      ISR_CLEAR1;         // (0xB4)  
        __RW  PENDING_IRQ1_reg_t    PENDING_IRQ1;       // (0xB8)  
        __RW  PENDING_FIQ1_reg_t    PENDING_FIQ1;       // (0xBC)  
        __RW  ITR2_reg_t            ITR2;               // (0xC0)   
        __RW  MIR2_reg_t            MIR2;               // (0xC4)  
        __RW  MIR_CLEAR2_reg_t      MIR_CLEAR2;         // (0xC8)
        __RW  MIR_SET2_reg_t        MIR_SET2;           // (0xCC)
        __RW  ISR_SET2_reg_t        ISR_SET2;           // (0xD0)  
        __RW  ISR_CLEAR2_reg_t      ISR_CLEAR2;         // (0xD4)  
        __RW  PENDING_IRQ2_reg_t    PENDING_IRQ2;       // (0xD8)
        __RW  PENDING_FIQ2_reg_t    PENDING_FIQ2;       // (0xDC) 
        __RW  ITR3_reg_t            ITR3;               // (0xE0)  
        __RW  MIR3_reg_t            MIR3;               // (0xE4)  
        __RW  MIR_CLEAR3_reg_t      MIR_CLEAR3;         // (0xE8)  
        __RW  MIR_SET3_reg_t        MIR_SET3;           // (0xEC) 
        __RW  ISR_SET3_reg_t        ISR_SET3;           // (0xF0)
        __RW  ISR_CLEAR3_reg_t      ISR_CLEAR3;         // (0xF4)  
        __RW  PENDING_IRQ3_reg_t    PENDING_IRQ3;       // (0xF8)  
        __RW  PENDING_FIQ3_reg_t    PENDING_FIQ3;       // (0xFC)

        __RW  INTC_ILR_reg_t        INTC_ILR_0;         // (0x100)                                                                                     
    }; 

    constexpr uint32_t AM335x_INTC_BASE     = 0x48200000;
    constexpr AM335x_INTC_Type *AM335x_INTC = ((AM335x_INTC_Type *) AM335x_INTC_BASE); 
    
    uint32_t debug_dump_INTC(AM335x_INTC_Type &sINTC = *AM335x_INTC);
    
    /* for testing purpose */
    inline uint32_t debug_dump_INTC(AM335x_INTC_Type &sINTC)
    {
        constexpr uint32_t COUNTOF_INTC = sizeof(AM335x_INTC_Type)/sizeof(uint32_t);
        volatile uint32_t TSTREG[COUNTOF_INTC] = {0};          
        uint32_t *pAM335x_INTC = (uint32_t *)&sINTC;
        volatile uint32_t SIZEOF_INTC = sizeof(AM335x_INTC_Type); 
        
        for(uint32_t i = 0 ; i < COUNTOF_INTC; i++)
        {   
            TSTREG[i] = pAM335x_INTC[i];
        }
        
        return SIZEOF_INTC;
    }
}

#endif //_INTC_H_