#ifndef _AM335X_MEM_MAP_H_
#define _AM335X_MEM_MAP_H_

#include <stdint.h>

#define   __R     volatile const       // 'read only' register
#define   __W     volatile             // 'write only' register 
#define   __RW    volatile             // 'read / write' register

namespace DMTIMER
{
    constexpr uint32_t AM335x_DMTIMER_0_BASE = 0x44E05000;
    constexpr uint32_t AM335x_DMTIMER_1_BASE = 0x44E31000;    // 1ms timer
    constexpr uint32_t AM335x_DMTIMER_2_BASE = 0x48040000;
    constexpr uint32_t AM335x_DMTIMER_3_BASE = 0x48042000;
    constexpr uint32_t AM335x_DMTIMER_4_BASE = 0x48044000;
    constexpr uint32_t AM335x_DMTIMER_5_BASE = 0x48046000;
    constexpr uint32_t AM335x_DMTIMER_6_BASE = 0x48048000;
    constexpr uint32_t AM335x_DMTIMER_7_BASE = 0x4804A000;

    /* [reset state = 0x40000100]*/
    typedef union 
    { 
        struct 
        {
            uint32_t  Y_MINOR   :6;          // bit: 0..5    Minor Revision (Y).                   
            uint32_t  CUSTOM    :2;          // bit: 6,7     Indicates a special version for a particular device.          
            uint32_t  X_MAJOR   :3;          // bit: 8..10   Major Revision (X).
            uint32_t  R_RTL     :5;          // bit: 11..15  RTL Version (R).          
            uint32_t  FUNC      :12;         // bit: 16..27  Function indicates a software compatible module family. 
            uint32_t            :2;          // bit: 28,29   Reserved  
            uint32_t  SCHEME    :2;          // bit: 30,31   Used to distinguish between old scheme and current. 
        } b;                                 // Structure used for bit  access 
        uint32_t  reg;                       // Type used for register access 
    } TIDR_reg_t;
    
    typedef struct 
    {                                                                                      
        __RW  TIDR_reg_t    TIDR;                    // (0x00)  Identification Register
        __R   uint32_t      RESERVED1[3];
        __RW  uint32_t      TIOCP_CFG;               // (0x10)  Timer OCP Configuration Register
        __R   uint32_t      RESERVED2[3];
        __RW  uint32_t      IRQ_EOI;                 // (0x20)  Timer IRQ End-of-Interrupt Register
        __RW  uint32_t      IRQSTATUS_RAW;           // (0x24)  Timer IRQ Status Raw Register
        __RW  uint32_t      IRQSTATUS;               // (0x28)  Timer IRQ Status Register
        __RW  uint32_t      IRQENABLE_SET;           // (0x2C)  Timer Interrupt Enable Set Registerr
        __RW  uint32_t      IRQENABLE_CLR;           // (0x30)  Timer Interrupt Enable Clear Register
        __RW  uint32_t      IRQWAKEEN;               // (0x34)  Timer IRQ Wakeup Enable Register
        __RW  uint32_t      TCLR;                    // (0x38)  Timer Control Register
        __RW  uint32_t      TCRR;                    // (0x3C)  Timer Counter Register
        __RW  uint32_t      TLDR;                    // (0x40)  Timer Load Register
        __W   uint32_t      TTGR;                    // (0x44)  Timer Trigger Register
        __RW  uint32_t      TWPS;                    // (0x48)  Timer Write Posting Bits Register
        __RW  uint32_t      TMAR;                    // (0x4C)  Timer Match Register
        __RW  uint32_t      TCAR1;                   // (0x50)  Timer Capture Register 1
        __RW  uint32_t      TSICR;                   // (0x54)  Timer Synchronous Interface Control Register
        __RW  uint32_t      TCAR2;                   // (0x58)  Timer Capture Register 2                                                                                                               
    } AM335x_DMTIMER_Type;
    
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_0 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_0_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_1 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_1_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_2 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_2_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_3 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_3_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_4 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_4_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_5 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_5_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_6 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_6_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_7 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_7_BASE);
} 


#endif //_AM335X_MEM_MAP_H_