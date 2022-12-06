#ifndef _UART_H_
#define _UART_H_

#include <stdint.h>
#include "app_utils.h"
#include "INTC.h"

//This is UART class and his namespace
namespace UART
{ 
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_UART_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/      
   

    /*! @brief      The transmitter section consists of the transmit holding register and the transmit shift register.  
    *   @details    The transmit holding register is a 64-byte FIFO. The MPU writes data to the THR. The data is placed in the transmit shift
    *               register where it is shifted out serially on the TX output. If the FIFO is disabled, location zero of the FIFO
    *               is used to store the data.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {
             
            uint32_t    THR        :8;         // bit: 0..7    (RW) Transmit holding register.[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..24   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } THR_reg_t;

    /*! @brief      The receiver section consists of the receiver holding register and the receiver shift register.  
    *   @details    The RHR is actually a 64-byte FIFO. The receiver shift register receives serial data from RX input. The data is converted to parallel
    *               data and moved to the RHR. If the FIFO is disabled, location zero of the FIFO is used to store the single
    *               data character. If an overflow occurs, the data in the RHR is not overwritten.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHR        :8;         // bit: 0..7    (RW) Transmit holding register.[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..24   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } RHR_reg_t;

    /*! @brief      The divisor latches low register (DLL) with the DLH register stores the 14-bit divisor for generation of the baud clock in the baud rate generator.  
    *   @details    DLH stores the most-significant part of the divisor, DLL stores the leastsignificant
    *               part of the divisor. DLL and DLH can be written to only before sleep mode is enabled (before IER[4] is set).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CLOCK_LSB  :8;         // bit: 0..7    (RW) Divisor latches low.Stores the 8 LSB divisor value.[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..24   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } DLL_reg_t;

    typedef union
    {
        THR_reg_t  THR;
        RHR_reg_t  RHR;
        DLL_reg_t  DLL;
    } THR_RHR_DLL_reg_t;

    struct AM335x_UART_Type
    {     
        union
        { 
            __RW    THR_reg_t    THR;   // (0x00)
            __RW    RHR_reg_t    RHR;   // (0x00)
            __RW    DLL_reg_t    DLL;   // (0x00)
        }; 
            __   uint32_t   RESERVED[];  
        union
        {
            __  IER_IRDA_reg_t      IER_IRDA;   // (0x04) 
            __  IER_CIR_reg_t       IER_CIR;    // (0x04)
            __  IER_UART_reg_t      IER_UART;   // (0x04)
            __  DLH_reg_t           DLH;        // (0x04)
        };
        union
        {
            __   EFR_reg_t          EFR;        // (0x08) 
            __   IIR_UART_reg_t     IIR_UART;   // (0x08)
            __   IIR_CIR_reg_t      IIR_CIR;    // (0x08)
            __   FCR_reg_t          FCR;        // (0x08)
            __   IIR_IRDA_reg_t     IIR_IRDA;   // (0x08)
        };
            __   LCR_reg_t          LCR;         // (0x0C) 
        union
        { 
            __   MCR_reg_t          MCR;         // (0x10)
            __   XON1_ADDR1_reg_t   XON1_ADDR1;  // (0x10) 
        };
        union
        { 
            __   XON2_ADDR2_reg_t   XON2_ADDR2;  // (0x14)   
            __   LSR_CIR_reg_t      LSR_CIR;     // (0x14)
            __   LSR_IRDA_reg_t     LSR_IRDA;    // (0x14)
            __   LSR_UART_reg_t     LSR_UART;    // (0x14) 
        };
        union
        { 
            __  TCR_reg_t           TCR;         // (0x18)
            __  MSR_reg_t           MSR;         // (0x18) 
            __  XOFF1_reg_t         XOFF1;       // (0x18) 
        };  
        __  _reg_t             IDLE;          // (0x1C) 
        __  _reg_t     IRQ_PRIORITY;          // (0x20)  
        __  _reg_t     FIQ_PRIORITY;          // (0x24)
        __  _reg_t        THRESHOLD;          // (0x28)
        __   _reg_t            ITR0;          // (0x2C)  
        __  _reg_t             MIR0;          // (0x30)  
        __   _reg_t      MIR_CLEAR0;          // (0x34)  
        __   _reg_t        MIR_SET0;          // (0x38)  
        __  _reg_t         ISR_SET0;          // (0x3C)  
        __   _reg_t      ISR_CLEAR0;          // (0x40) 
        __   _reg_t    PENDING_IRQ0;          // (0x44)   
        __   _reg_t    PENDING_FIQ0;          // (0x48)
        __   _reg_t      ISR_CLEAR0;          // (0x50) 
        __   _reg_t    PENDING_IRQ0;          // (0x54)   
        __   _reg_t    PENDING_FIQ0;          // (0x58)
        __   _reg_t        MIR_SET0;          // (0x5C)  
        __  _reg_t         ISR_SET0;          // (0x60)  
        __   _reg_t      ISR_CLEAR0;          // (0x64) 
        __   _reg_t    PENDING_IRQ0;          // (0x68)   
        __   _reg_t    PENDING_FIQ0;          // (0x6C)
        __   _reg_t      ISR_CLEAR0;          // (0x70) 
        __   _reg_t    PENDING_IRQ0;          // (0x74)   
        __   _reg_t    PENDING_FIQ0;          // (0x80)
        __   _reg_t    PENDING_FIQ0;          // (0x84)
    };
}

#endif // _UART_H_