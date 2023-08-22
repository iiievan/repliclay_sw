#ifndef _N_UART_H_
#define _N_UART_H_

#include <stdint.h>
#include "utils.h"
#include "INTC.h"
#include "ring_buffer.h"
#include "frame_buffer.h"
#include "Paired_buffer.h"
#include "sw_Timer.h"

//This is UART class and his namespace
namespace n_UART
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
             
            uint32_t    THR        :8;         // bit: 0..7    (W) Transmit holding register.[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..32   Reserved  
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
            uint32_t    RHR        :8;         // bit: 0..7    (R) Receive holding register..[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..32   Reserved  
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
            uint32_t               :24;        // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } DLL_reg_t;

    /*! @brief      The following interrupt enable register (IER) description is for IrDA mode.  
    *   @details    Refer to Section 19.3.7.1 to
    *               determine the mode(s) in which this register can be accessed. In IrDA mode, EFR[4] has no impact on the
    *               access to IER[7:4]. The IrDA interrupt enable register (IER) can be programmed to enable/disable any
    *               interrupt. There are 8 types of interrupt in these modes, received EOF, LSR interrupt, TX status, status
    *               FIFO interrupt, RX overrun, last byte in RX FIFO, THR interrupt, and RHR interrupt. Each interrupt can be
    *               enabled/disabled individually. The TXSTATUSIT interrupt reflects two possible conditions. The MDR2[0]
    *               bit should be read to determine the status in the event of this interrupt.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHRIT          :1;     // bit: 0      (RW) RHR interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    THRIT          :1;     // bit: 1      (RW) THR interrupt [0x0 = disable; 0x1 = enable ] 
            uint32_t    LASTRXBYTEIT   :1;     // bit: 2      (RW) last byte of frame in RX FIFO interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    RXOVERRUNIT    :1;     // bit: 3      (RW) RX overrun interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    STSFIFOTRIGIT  :1;     // bit: 4      (RW) status FIFO trigger level interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    TXSTATUSIT     :1;     // bit: 5      (RW) TX status interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    LINESTSIT      :1;     // bit: 6      (RW) receiver line status interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    EOFIT          :1;     // bit: 7      (RW) received EOF interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t                   :24;    // bit: 8..32  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IER_IRDA_reg_t;

    /*! @brief      The following interrupt enable register (IER) description is for CIR mode.  
    *   @details    Refer to Section 19.3.7.1 to
    *               determine the mode(s) in which this register can be accessed. In IrDA mode, EFR[4] has no impact on the
    *               access to IER[7:4]. The CIR interrupt enable register (IER) can be programmed to enable/disable any
    *               interrupt. There are 5 types of interrupt in these modes, TX status, RX overrun, RX stop interrupt, THR
    *               interrupt, and RHR interrupt. Each interrupt can be enabled/disabled individually. In CIR mode, the
    *               TXSTATUSIT bit has only one meaning corresponding to the case MDR2[0] = 0. The RXSTOPIT interrupt
    *               is generated based on the value set in the BOF Length register (EBLR).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHRIT          :1;     // bit: 0        (RW) RHR interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    THRIT          :1;     // bit: 1        (RW) THR interrupt [0x0 = disable; 0x1 = enable ] 
            uint32_t    RXSTOPIT       :1;     // bit: 2        (RW) RX stop interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    RXOVERRUNIT    :1;     // bit: 3        (RW) RX overrun interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t                   :1;     // bit: 4        Reserved
            uint32_t    TXSTATUSIT     :1;     // bit: 5        (RW) TX status interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t                   :26;    // bit: 6..32    Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IER_CIR_reg_t;

    /*! @brief      The following interrupt enable register (IER) description is for UART mode.  
    *   @details    Refer to Section 19.3.7.1 to
    *               determine the mode(s) in which this register can be accessed. In UART mode, IER[7:4] can only be
    *               written when EFR[4] = 1 The interrupt enable register (IER) can be programmed to enable/disable any
    *               interrupt. There are seven types of interrupt in this mode: receiver error, RHR interrupt, THR interrupt,
    *               XOFF received and CTS (active-low)/RTS (active-low) change of state from low to high. Each interrupt
    *               can be enabled/disabled individually. There is also a sleep mode enable bit. The UART interrupt enable
    *               register (IER) is shown in and described in .
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHRIT       :1;     // bit: 0      (RW) RHR interrupt and time out interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    THRIT       :1;     // bit: 1      (RW) THR interrupt [0x0 = disable; 0x1 = enable ] 
            uint32_t    LINESTSIT   :1;     // bit: 2      (RW) receiver line status interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    MODEMSTSIT  :1;     // bit: 3      (RW) modem status register interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    SLEEPMODE   :1;     // bit: 4      (RW) Can be only written when EFR[4] = 1. Sleep mode
                                            //             stops baud rate clock when the module is inactive [0x0 = disable; 0x1 = enable ]
            uint32_t    XOFFIT      :1;     // bit: 5      (RW) Can be written only when EFR[4] = 1. XOFF interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    RTSIT       :1;     // bit: 6      (RW) Can be written only when EFR[4] = 1. RTS (active-low) interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t    CTSIT       :1;     // bit: 7      (RW) Can be written only when EFR[4] = 1. CTS (active-low) interrupt [0x0 = disable; 0x1 = enable ]
            uint32_t                :24;    // bit: 8..32  Reserved  
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } IER_UART_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.  
    *   @details    The divisor latches high register (DLH) with the DLL register stores the 14-bit divisor for generation of the baud clock
    *               in the baud rate generator. DLH stores the most-significant part of the divisor, DLL stores the leastsignificant
    *               part of the divisor. DLL and DLH can be written to only before sleep mode is enabled (before
    *               IER[4] is set).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CLOCK_MSB  :6;         // bit: 0..5    (RW)Divisor latches high. Stores the 6 MSB divisor value.[Value 0x0 to 0x3F.]
            uint32_t               :26;        // bit: 6..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } DLH_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed  
    *   @details    The enhanced feature register (EFR) enables or disables enhanced features. Most enhanced functions apply only to
    *               UART modes, but EFR[4] enables write accesses to FCR[5:4], the TX trigger level, which is also used in IrDA modes.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    SWFLOWCONTROL       :4;     // bit: 0..3   (RW) Combinations of software flow control can be selected by programming this bit. [ see e_SW_TX_FLOW_CTRL and  e_SW_RX_FLOW_CTRL]
            uint32_t    ENHANCEDEN          :1;     // bit: 4      (RW) Enhanced functions write enable bit.Writing to IER[7:4], FCR[5:4], and MCR[7:5].[0x0 = disable; 0x1 = enable ] 
            uint32_t    SPECIALCHARDETECT   :1;     // bit: 5      (RW) Special character detect (UART mode only).[0x0 = Normal operation.; 0x1 = Special character 
                                                    //                  detect enable. Received data is compared
                                                    //                  with XOFF2 data. If a match occurs, the received data is transferred
                                                    //                  to RX FIFO and the IIR[4] bit is set to 1 to indicate that a special
                                                    //                  character was detected. ]
            uint32_t    AUTORTSEN           :1;     // bit: 6      (RW) Auto-RTS enable bit (UART mode only). [0x0 = Normal operation.; 0x1 = Auto-RTS flow control is enabled; RTS (active-low) pin goes
                                                    //                  high (inactive) when the receiver FIFO HALT trigger level, TCR[3:0],
                                                    //                  is reached and goes low (active) when the receiver FIFO RESTORE
                                                    //                  transmission trigger level is reached. ]
            uint32_t    AUTOCTSEN           :1;     // bit: 7      (RW) Auto-CTS enable bit (UART mode only). [0x0 = Normal operation.; 0x1 = Auto-CTS flow control is enabled; transmission is halted when
                                                    //                  the CTS (active-low) pin is high (inactive).
            uint32_t                        :24;    // bit: 8..32  Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } EFR_reg_t;

    enum e_SW_TX_FLOW_CTRL
    {
        // XON1 and XON2 should be set to different values if the software
        // flow control is enabled. The TX and RX software flow control options are as follows.
        SW_TX_FLOW_MODE_0 = 0x00,  // No transmit flow control.
        SW_TX_FLOW_MODE_1 = 0x10,  // Transmit XON1, XOFF1.
        SW_TX_FLOW_MODE_2 = 0x20,  // Transmit XON2, XOFF2.
        SW_TX_FLOW_MODE_3 = 0x30,  // Transmit XON1, XON2 or XOFF1, XOFF2.
    };

    enum e_SW_RX_FLOW_CTRL
    {
        SW_RX_FLOW_MODE_0 = 0x00,  // No receive flow control.
        SW_RX_FLOW_MODE_1 = 0x01,  // Receiver compares XON1, XOFF1.
        SW_RX_FLOW_MODE_2 = 0x02,  // Receiver compares XON2, XOFF2.
        SW_RX_FLOW_MODE_3 = 0x03,  // Receiver compares XON1, XON2 or XOFF1, XOFF2.

    };

    /*! @brief      The following interrupt identification register (IIR) description is for UART mode.  
    *   @details    Refer to Section 19.3.7.1
    *               to determine the mode(s) in which this register can be accessed. The UART interrupt identification register
    *               (IIR) is a read-only register that provides the source of the interrupt. An interrupt source can be flagged
    *               only if enabled in the IER register.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    IT_PENDING  :1;        // bit: 0       (RW) Interrupt pending. [0x0 = An interrupt is pending.; 0x1 = No interrupt is pending.]
            uint32_t    IT_TYPE     :5;        // bit: 1..5    (RW) Seven possible interrupts in UART mode. Other combinations never occur: [see e_IT_TYPES]
            uint32_t    FCR_MIRROR  :2;        // bit: 6..7    (RW) Mirror the contents of FCR[0] on both bits.
            uint32_t                :24;       // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IIR_UART_reg_t;

    enum e_IT_TYPES : uint32_t
    {
        MODEM_IT            = 0x0,  // Priority = 4.
        THR_IT              = 0x1,  // Priority = 3.
        RHR_IT              = 0x2,  // Priority = 2.
        RX_LINE_STS_ERR     = 0x3,  // Priority = 1.
        RX_TOUT_IT          = 0x6,  // Priority = 2.
        XOFF_SPECCHAR_IT    = 0x8,  // Priority = 5.
        CTS_RTS_DSR_IT      = 0x10  // Priority = 6.
    };

    /*! @brief      The following interrupt identification register (IIR) description is for CIR mode.  
    *   @details    Refer to Section 19.3.7.1 to
    *               determine the mode(s) in which this register can be accessed. The CIR interrupt identification register
    *               (IIR) is a read-only register that provides the source of the interrupt. An interrupt source can be flagged
    *               only if enabled in the IER register.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHRIT       :1;        // bit: 0       (RW) RHR interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    THRIT       :1;        // bit: 1       (RW) THR interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    RXSTOPIT    :1;        // bit: 2       (RW) Receive stop interrupt  [0x0 = inactive; 0x1 = active ]
            uint32_t    RXOEIT      :1;        // bit: 3       (RW) RX overrun interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t                :1;        // bit: 4       Reserved
            uint32_t    TXSTATUSIT  :1;        // bit: 5       (RW) TX status interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t                :26;       // bit: 6..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IIR_CIR_reg_t;
    // to mask this register please see --> e_CIR_IRQSTATUS_flags <--

    enum e_CIR_IRQSTATUS_flags : uint32_t
    {
        CIR_RHR      = BIT(0),
        CIR_THR      = BIT(1),
        CIR_RXSTOP   = BIT(2),
        CIR_RXOE     = BIT(3),
        CIR_TXSTATUS = BIT(5)
    };


    /*! @brief      FIFO Control Register. 
    *   @details    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed. FCR[5:4] can
    *               only be written when EFR[4] = 1.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    FIFO_EN         :1;     // bit: 0       (W) Can be changed only when the baud clock is not running (DLL and DLH cleared to 0). [0x0 = Disables rcv FIFO; 0x1 = Enables rcv FIFO ]
            uint32_t    RX_FIFO_CLEAR   :1;     // bit: 1       (W) [ 0x0 = No change.; 
                                                //                    0x1 = Clears the receive FIFO and resets its counter logic to 0. Returns to 0 after clearing FIFO. ]
            uint32_t    TX_FIFO_CLEAR   :1;     // bit: 2       (W)  [ 0x0 = No change.; 
                                                //                     0x1 = Clears the transmit FIFO and resets its counter logic to 0. Returns to 0 after clearing FIFO. ]
            uint32_t    DMA_MODE        :1;     // bit: 3       (W) Can be changed only when the baud clock is not running (DLL and DLH cleared to 0).
                                                //                    If SCR[0] = 0, this register is considered. [0x0 = DMA_MODE 0 (No DMA).; 
                                                //                                                                 0x1 = DMA_MODE 1 (UART_NDMA_REQ[0] in TX, UART_NDMA_REQ[1] in RX). ]
            uint32_t    TX_FIFO_TRIG    :2;     // bit: 4,5     (W) Can be written only if EFR[4] = 1. Sets the trigger level for the TX FIFO: If SCR[6] = 0 and TLR[3] to
                                                //                  TLR[0] not equal to 0000, TX_FIFO_TRIG is not considered.
                                                //                  If SCR[6] = 1, TX_FIFO_TRIG is 2 LSB of the trigger level (1 to 63
                                                //                  on 6 bits) with a granularity of 1.
                                                //                  If SCR[6] = 0 and TLR[3] to TLR[0] = 0000, then: [ see e_FCR_TX_FIFO_TRIG ]
            uint32_t    RX_FIFO_TRIG    :2;     // bit: 6,7     (RW) Sets the trigger level for the RX FIFO: If SCR[7] = 0 and TLR[7] to
                                                //                   TLR[4] not equal to 0000, RX_FIFO_TRIG is not considered.
                                                //                   If SCR[7] = 1, RX_FIFO_TRIG is 2 LSB of the trigger level (1 to 63
                                                //                   on 6 bits) with the granularity 1.
                                                //                   If SCR[7] = 0 and TLR[7] to TLR[4] = 0000, then: [ see e_FCR_RX_FIFO_TRIG ]
            uint32_t                    :24;    // bit: 8..32   Reserved  
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } FCR_reg_t;

    enum e_FCR_BITMASK : uint32_t
    {
        FCR_FIFO_EN         = BIT(0),
        FCR_RX_FIFO_CLEAR   = BIT(1),
        FCR_TX_FIFO_CLEAR   = BIT(2),
        FCR_DMA_MODE        = BIT(3),
        FCR_TX_FIFO_TRIG    = (BIT(4) | BIT(5)),
        FCR_RX_FIFO_TRIG    = (BIT(6) | BIT(7))
    };

    constexpr uint32_t FCR_RX_FIFO_CLEAR_SHIFT     = 0x00000001;
    constexpr uint32_t FCR_TX_FIFO_CLEAR_SHIFT     = 0x00000002;
    constexpr uint32_t FCR_DMA_MODE_SHIFT          = 0x00000003;
    constexpr uint32_t FCR_TX_FIFO_TRIG_SHIFT      = 0x00000004;
    constexpr uint32_t FCR_RX_FIFO_TRIG_SHIFT      = 0x00000006;

    // Values used to choose the path for configuring the DMA Mode.
    // DMA Mode could be configured either through FCR or SCR.
    constexpr uint32_t DMA_EN_PATH_FCR = 0x0;             
    constexpr uint32_t DMA_EN_PATH_SCR = 0x1;             

    enum e_FCR_TX_FIFO_TRIG : uint32_t
    {
        FCR_TX_FIFO_TRIG_8CHARS    = 0x0,
        FCR_TX_FIFO_TRIG_16CHARS   = 0x1,
        FCR_TX_FIFO_TRIG_32CHARS   = 0x2,
        FCR_TX_FIFO_TRIG_56CHARS   = 0x3,
    };

    enum e_FCR_RX_FIFO_TRIG : uint32_t
    {
        FCR_RX_FIFO_TRIG_8CHARS    = 0x0,
        FCR_RX_FIFO_TRIG_16CHARS   = 0x1,
        FCR_RX_FIFO_TRIG_56CHARS   = 0x2,
        FCR_RX_FIFO_TRIG_60CHARS   = 0x3,
    };

    /*! @brief        
    *   @details    
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RHRIT                   :1;         // bit: 0       (R) RHR interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    THRIT                   :1;         // bit: 1       (R) THR interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    RX_FIFO_LAST_BYTE_IT    :1;         // bit: 2       (R) Last byte of frame in RX FIFO interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    RXOEIT                  :1;         // bit: 3       (R) RX overrun interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    STS_FIFO_IT             :1;         // bit: 4       (R) Status FIFO trigger level interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    TX_STATUS_IT            :1;         // bit: 5       (R) TX status interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    LINE_STS_IT             :1;         // bit: 6       (R) Receiver line status interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    EOF_IT                  :1;         // bit: 7       (R) Received EOF [0x0 = inactive; 0x1 = active ]
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IIR_IRDA_reg_t;

    enum e_IRDA_IRQSTATUS_flags : uint32_t
    {
        IRDA_RHR                 = BIT(0),
        IRDA_THR                 = BIT(1),
        IRDA_RX_FIFO_LAST_BYTE   = BIT(2),
        IRDA_RXOE                = BIT(3),
        IRDA_STS_FIFO            = BIT(4),
        IRDA_TX_STATUS           = BIT(5),
        IRDA_LINE_STS            = BIT(6),
        IRDA_EOF                 = BIT(7)
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.       
    *   @details    As soon as LCR[6] is set to 1, the TX line is forced to 0 and remains in this state as long as LCR[6] = 1.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CHAR_LENGTH     :2;        // bit: 0,1     (RW) Specifies the word length to be transmitted or received. [ see e_CHAR_LENGHT ]
            uint32_t    NB_STOP         :1;        // bit: 2       (RW) Specifies the number of stop bits. [0x0 = 1 stop bit (word length = 5, 6, 7, 8).;
                                                   //                                                       0x1 = 1.5 stop bits (word length = 5) or 2 stop bits (word length = 6, 7, 8). ]
            uint32_t    PARITY_EN       :1;        // bit: 3       (RW) Parity bit. [0x0 = No parity; 
                                                   //                                0x1 = A parity bit is generated during transmission, and the receiver checks for received parity. ]
            uint32_t    PARITY_TYPE1    :1;        // bit: 4       (RW) If LCR[3] = 1, then: [0x0 = Odd parity is generated.; 0x1 = Even parity is generated. ]
            uint32_t    PARITY_TYPE2    :1;        // bit: 5       (RW) If LCR[3] = 1, then: [0x0 = If LCR[5] = 0, LCR[4] selects the forced parity format.; 
                                                   //                                         0x1 = If LCR[5] = 1 and LCR[4] = 0, the parity bit is forced to 1 in the
                                                   //                                         transmitted and received data. If LCR[5] = 1 and LCR[4] = 1, the
                                                   //                                         parity bit is forced to 0 in the transmitted and received data. ]
            uint32_t    BREAK_EN        :1;        // bit: 6       (RW) Break control bit. Note: When LCR[6] is set to 1, the TX line is forced to 0 and remains
                                                   //                   in this state as long as LCR[6] = 1.
                                                   //                   [0x0 = Normal operating condition.; 
                                                   //                    0x1 = Forces the transmitter output to go low to alert the communication terminal ]
            uint32_t    DIV_EN          :1;        // bit: 7       (RW) Divisor latch enable. [0x0 = Normal operating condition.; 
                                                   //                                          0x1 = Divisor latch enable. Allows access to DLL and DLH. ]
            uint32_t                    :24;       // bit: 8..32   Reserved  
        } b;                                       // Structure used for bit access 
        uint32_t  reg;                             // Type used for register access 
    } LCR_reg_t;

    enum e_CHAR_LENGHT : uint32_t
    {
        CHL_5_BITS = 0x00,
        CHL_6_BITS = 0x01,
        CHL_7_BITS = 0x02,
        CHL_8_BITS = 0x03
    };
    
    enum e_STOP_BIT : uint8_t
    {
        STOP_1    = 0x00,      // 1 stop bit (word length = 5, 6, 7, 8).;
        STOP_15_2 = 0x01       // 1.5 stop bits (word length = 5) or 2 stop bits (word length = 6, 7, 8).
    };

    enum e_LCR_BITMASK : uint32_t
    {
        LCR_CHAR_LENGTH  = 0x03,
        LCR_NB_STOP      = BIT(2),
        LCR_PARITY_EN    = BIT(3),
        LCR_PARITY_TYPE1 = BIT(4),
        LCR_PARITY_TYPE2 = BIT(5),
        LCR_BREAK_EN     = BIT(6),
        LCR_DIV_EN       = BIT(7)
    };
    
    enum e_LCR_PARITY : uint8_t
    {
         PARITY_NONE     = (0x00 << 3),
         PARITY_ODD      = (0x01 << 3),
         PARITY_EVEN     = (0x02 << 3),
         PARITY_FORCED_1 = (0x04 << 3),
         PARITY_FORCED_0 = (0x06 << 3)
    };
    
    constexpr uint32_t LCR_Parity_mask = LCR_PARITY_EN | LCR_PARITY_TYPE1 |LCR_PARITY_TYPE2;

    /*! @brief    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.    
    *   @details  MCR[7:5] can only be written when EFR[4] = 1. Bits 3-0 control the interface with the modem, data set, or peripheral
    *             device that is emulating the modem.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    DTR                     :1;         // bit: 0       (RW)  DTR. [0x0 = Force DTR (active-low) output (used in loopback mode) to inactive (high).;
                                                            //                          0x1 = Force DTR (active-low) output (used in loopback mode) to active (low). ]
            uint32_t    RTS                     :1;         // bit: 1       (RW)  In loopback mode, controls MSR[4]. If auto-RTS is enabled, the RTS (active-low) output is controlled by
                                                            //                     hardware flow control.[0x0 = Force RTS (active-low) output to inactive (high).; 
                                                            //                                            0x1 = Force RTS (active-low) output to active (low). ]
            uint32_t    RISTSCH                 :1;         // bit: 2       (RW)  RISTSCH. [ 0x0 = In loopback mode, forces RI (active-low) input inactive (high).;
                                                            //                               0x1 = In loopback mode, forces RI (active-low) input active (low). ]
            uint32_t    CDSTSCH                 :1;         // bit: 3       (RW)  CDSTSCH. [0x0 = In loopback mode, forces DCD (active-low) input high and IRQ outputs to INACTIVE state.;
                                                            //                              0x1 = In loopback mode, forces DCD (active-low) input low and IRQ outputs to INACTIVE state. ]
            uint32_t    LOOPBACKEN              :1;         // bit: 4       (RW)  Loopback mode enable. [0x0 = Normal operating mode.; 0x1 = Enable local loopback mode (internal). In this mode, the
                                                            //                                           MCR[3:0] signals are looped back into MSR[7:4]. The transmit output
                                                            //                                           is looped back to the receive input internally. ]
            uint32_t    XONEN                   :1;         // bit: 5       (RW) Can be written only when EFR[4] = 1. [0x0 = Disable XON any function.; 0x1 = Enable XON any function. ]
            uint32_t    TCRTLR                  :1;         // bit: 6       (RW) Can be written only when EFR[4] = 1. [0x0 = No action.; 0x1 = Enables access to the TCR and TLR registers. ]
            uint32_t                            :25;        // bit: 7..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } MCR_reg_t;

    enum e_MODEM_CTRL_SET : uint32_t
    {
        MODEM_DTR     = BIT(0),
        MODEM_RTS     = BIT(1),
        MODEM_RISTSCH = BIT(2),
        MODEM_CDSTSCH = BIT(3)
    };

    /*! @brief    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details  In UART mode, XON1 character; in IrDA mode, ADDR1 address 1.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    XONWORD1    :8;        // bit: 0..7    (RW) Stores the 8 bit XON1 character in UART modes and ADDR1 address 1 in IrDA modes.
            uint32_t                :24;       // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } XON1_ADDR1_reg_t;

    /*! @brief    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed     
    *   @details  UART mode, XON2 character; in IrDA mode, ADDR2 address 2.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    XONWORD2    :8;        // bit: 0..7    (RW) Stores the 8 bit XON2 character in UART modes and ADDR2 address 2 in IrDA modes.
            uint32_t                :24;       // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } XON2_ADDR2_reg_t;

    /*! @brief  The following line status register (LSR) description is for CIR mode.       
    *   @details  Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.  
    [reset state = 0x81] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFIFOE           :1;           // bit: 0       (R) RXFIFOE. [0x0 = At least one data character in the RX FIFO.; 
                                                        //                            0x1 = No data in the receive FIFO. ]
            uint32_t                      :4;           // bit: 1..4    Reserved
            uint32_t    RXSTOP            :1;           // bit: 2       (R) The RXSTOP is generated based on the value set in the BOF
                                                        //                   Length register (EBLR). [ 0x0 = Reception is on going or waiting for a new frame.; 
                                                        //                                             0x1 = Reception is completed. It is cleared on a single read of the LSR register. ]
            uint32_t                      :1;           // bit: 3       Reserved
            uint32_t    THREMPTY          :1;           // bit: 4       (R) THREMPTY. [ 0x0 = Transmit holding register (TX FIFO) is not empty.; 
                                                        //                              0x1 = Transmit hold register (TX FIFO) is empty. The transmission is not necessarily completed. ]
            uint32_t                      :24;          // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } LSR_CIR_reg_t;

    /*! @brief      The following line status register (LSR) description is for IrDA mode. Refer to Section 19.3.7.1 to
    **              determine the mode(s) in which this register can be accessed.      
    *   @details    When the IrDA line status register (LSR) is
    *               read, LSR[4:2] reflect the error bits (FL, CRC, ABORT) of the frame at the top of the status FIFO (next
    *               frame status to be read).  
    [reset state = 0xA3] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RX_FIFO_E               :1;         // bit: 0       (R) [0x0 = At least one data character in the RX FIFO.; 0x1 = No data in the receive FIFO. ]
            uint32_t    STS_FIFO_E              :1;         // bit: 1       (R) [0x0 = Status FIFO is not empty.; 0x1 = Status FIFO is empty. ]
            uint32_t    CRC                     :1;         // bit: 2       (R) [0x0 = No CRC error in frame.; 0x1 = CRC error in the frame at the top of the status FIFO (next character to be read). ]
            uint32_t    ABORT                   :1;         // bit: 3       (R) [0x0 = No abort pattern error in frame.; 0x1 = Abort pattern received. SIR and MIabort pattern. FIR: Illegal symbol. ]
            uint32_t    FRAME_TOO_LONG          :1;         // bit: 4       (R) [0x0 = No frame-too-long error in frame.; 0x1 = Frame-too-long error in the frame at the top of the status FIFO
                                                            //                   (next character to be read). This bit is set to 1 when a frame
                                                            //                   exceeding the maximum length (set by RXFLH and RXFLL registers)
                                                            //                   is received. When this error is detected, current frame reception is
                                                            //                   terminated. Reception is stopped until the next START flag is
                                                            //                   detected. ]
            uint32_t    RX_LAST_BYTE            :1;         // bit: 5       (R) [0x0 = The RX FIFO (RHR) does not contain the last byte of the frame to be read.;
                                                            //                   0x1 = The RX FIFO (RHR) contains the last byte of the frame to be read. This bit is set to 1 only when the last byte of a frame is
                                                            //                   available to be read. It is used to determine the frame boundary. It is
                                                            //                   cleared on a single read of the LSR register. ]
            uint32_t    STS_FIFO_FULL           :1;         // bit: 6       (R) [0x0 = Status FIFO is not full.; 0x1 = Status FIFO is full. ]
            uint32_t    THR_EMPTY               :1;         // bit: 7       (R) [0x0 = Transmit holding register (TX FIFO) is not empty; 
                                                            //                   0x1 = Transmit hold register (TX FIFO) is empty. The transmission is not necessarily completed. ]
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } LSR_IRDA_reg_t;

    /*! @brief      The following line status register (LSR) description is for UART mode. Refer to Section 19.3.7.1 to
    *               determine the mode(s) in which this register can be accessed.       
    *   @details    When the UART line status register (LSR)
    *               is read, LSR[4:2] reflect the error bits (BI, FE, PE) of the character at the top of the RX FIFO (next
    *               character to be read). Therefore, reading the LSR and then reading the RHR identifies errors in a
    *               character. Reading RHR updates BI, FE, and PE. LSR [7] is set when there is an error anywhere in the
    *               RX FIFO and is cleared only when there are no more errors remaining in the RX FIFO. Reading the LSR
    *               does not cause an increment of the RX FIFO read pointer. The RX FIFO read pointer is incremented by
    *               reading the RHR. Reading LSR clears OE if set.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFIFOE          :1;        // bit: 0       (R) [0x0 = No data in the receive FIFO.; 0x1 = At least one data character in the RX FIFO. ]
            uint32_t    RXOE             :1;        // bit: 1       (R) [0x0 = No overrun error.; 0x1 = Overrun error occurred. Set when the character held in the
                                                    //                  receive shift register is not transferred to the RX FIFO. This case
                                                    //                  occurs only when receive FIFO is full. ]
            uint32_t    RXPE             :1;        // bit: 2       (R) [0x0 = No parity error in data being read from RX FIFO.; 0x1 = Parity error in data being read from RX FIFO. ]
            uint32_t    RXFE             :1;        // bit: 3       (R) [0x0 = No framing error in data being read from RX FIFO.; 
                                                    //                   0x1 = Framing error occurred in data being read from RX FIFO (received data did not have a valid stop bit). ]
            uint32_t    RXBI             :1;        // bit: 4       (R) [0x0 = No break condition.; 0x1 = A break was detected while the data being read from the RX
                                                    //                   FIFO was being received (RX input was low for one character + 1 bit time frame). ]
            uint32_t    TXFIFOE          :1;        // bit: 5       (R) [0x0 = Transmit hold register (TX FIFO) is not empty.; 
                                                    //                   0x1 = Transmit hold register (TX FIFO) is empty. The transmission is not necessarily completed. ]
            uint32_t    TXSRE            :1;        // bit: 6       (R) [0x0 = Transmitter hold (TX FIFO) and shift registers are not empty.; 
                                                    //                   0x1 = Transmitter hold (TX FIFO) and shift registers are empty. ]
            uint32_t    RXFIFOSTS        :1;        // bit: 7       (R) [0x0 = Normal operation.; 
                                                    //                   0x1 = At least one parity error, framing error, or break indication in the
                                                    //                   RX FIFO. Bit 7 is cleared when no errors are present in the RXFIFO. ]
            uint32_t                     :24;       // bit: 8..32   Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } LSR_UART_reg_t;

    enum e_RX_ERRORS : uint32_t
    {
        ERR_RX_OVERRUN      = BIT(1),
        ERR_RX_PARITY       = BIT(2),
        ERR_RX_FRAMING      = BIT(3),
        ERR_RX_BRAK_COND    = BIT(4),
        ERR_RX_FIFO         = BIT(7)
    };

    /*! @brief        Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.
    *   @details      The TCR is accessible only when EFR[4] = 1 and MCR[6] = 1. The transmission control register (TCR) stores the
    *                 receive FIFO threshold levels to start/stop transmission during hardware flow control. Trigger levels from
    *                 0-60 bytes are available with a granularity of 4. Trigger level = 4 x [4-bit register value]. You must ensure
    *                 that TCR[3:0] > TCR[7:4], whenever auto-RTS or software flow control is enabled to avoid a misoperation
    *                 of the device. In FIFO interrupt mode with flow control, you have to also ensure that the trigger level to
    *                 HALT transmission is greater or equal to receive FIFO trigger level (either TLR[7:4] or FCR[7:6]);
    *                 otherwise, FIFO operation stalls. In FIFO DMA mode with flow control, this concept does not exist
    *                 because the DMA request is sent each time a byte is received.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFIFOTRIGHALT          :4;         // bit: 0..3       (RW) RX FIFO trigger level to HALT transmission (0 to 60).
            uint32_t    RXFIFOTRIGSTART         :4;         // bit: 4..7       (RW) RX FIFO trigger level to RESTORE transmission (0 to 60).
            uint32_t                            :24;        // bit: 8..32       Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } TCR_reg_t;

constexpr uint32_t TCR_RX_FIFO_TRIG_HALT        = 0x0000000F;
constexpr uint32_t TCR_RX_FIFO_TRIG_HALT_SHIFT  = 0x00000000;
constexpr uint32_t TCR_RX_FIFO_TRIG_START       = 0x000000F0;
constexpr uint32_t TCR_RX_FIFO_TRIG_START_SHIFT = 0x00000004;


    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.       
    *   @details    The modem
    *               status register (MSR) provides information about the current state of the control lines from the modem,
    *               data set, or peripheral device to the Local Host. It also indicates when a control input from the modem
    *               changes state.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CTS_STS                 :1;         // bit: 0       (R) CTS_STS.[0x0 = No change.; 0x1 = Indicates that CTS (active-low) input (or MCR[1] in loopback
                                                            //                           mode) changed state. Cleared on a read. ]
            uint32_t    DSR_STS                 :1;         // bit: 1       (R) DSR_STS.[0x0 = No change.; 0x1 = Indicates that DSR (active-low) input (or MCR[0] in loopback
                                                            //                           mode) changed state. Cleared on a read. ]
            uint32_t    RI_STS                  :1;         // bit: 2       (R) RI_STS. [0x0 = No change.; 0x1 = Indicates that RI (active-low) input (or MCR[2] in loopback
                                                            //                           mode) changed state from low to high. Cleared on a read. ]
            uint32_t    DCD_STS                 :1;         // bit: 3       (R) DCD_STS.[0x0 = No change.; 0x1 = Indicates that DCD (active-low) input (or MCR[3] in loopback
                                                            //                           mode) has changed. Cleared on a read. ]
            uint32_t    NCTS_STS                :1;         // bit: 4       (R) This bit is the complement of the CTS (active-low) input.
                                                            //                  In loopback mode, it is equivalent to MCR[1].
            uint32_t    NDSR_STS                :1;         // bit: 5       (R) This bit is the complement of the DSR (active-low) input.
                                                            //                  In loopback mode, it is equivalent to MCR[0].
            uint32_t    NRI_STS                 :1;         // bit: 6       (R) This bit is the complement of the RI (active-low) input.
                                                            //                  In loopback mode, it is equivalent to MCR[2].
            uint32_t    NCD_STS                 :1;         // bit: 7       (R) This bit is the complement of the DCD (active-low) input.
                                                            //                  In loopback mode, it is equivalent to MCR[3].
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } MSR_reg_t;

    enum e_MSR_BITMASK : uint32_t
    {
        BIT_CTS_STS  = BIT(0),
        BIT_DSR_STS  = BIT(1),
        BIT_RI_STS   = BIT(2),
        BIT_DCD_STS  = BIT(3),
        BIT_NCTS_STS = BIT(4),
        BIT_NDSR_STS = BIT(5),
        BIT_NRI_STS  = BIT(6),
        BIT_NCD_STS  = BIT(7)
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed      
    *   @details    In UART mode, XOFF1 character.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    XOFFWORD1               :8;         // bit: 0..7    (RW) Stores the 8 bit XOFF1 character in UART modes.
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } XOFF1_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The scratchpad register (SPR) is a read/write register that does not control the module. It is a scratchpad
    *               register used to hold temporary data.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    SPR_WORD               :8;         // bit: 0..7    (RW) Scratchpad register.
            uint32_t                           :24;        // bit: 8..32   Reserved  
        } b;                                               // Structure used for bit access 
        uint32_t  reg;                                     // Type used for register access 
    } SPR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The TLR is accessible only when EFR[4] = 1 and MCR[6] = 1. This register stores the programmable transmit and
    *               receive FIFO trigger levels used for DMA and IRQ generation.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TX_FIFO_TRIG_DMA       :4;          // bit: 0..3    (RW) Transmit FIFO trigger level.
                                                            //                   Following is a summary of settings for the TX FIFO trigger level.
                                                            //                   SCR[6] = 0, and TLR[3] to TLR[0] = 0, then: Defined by FCR[5] and
                                                            //                   FCR[4] (either 8, 16, 32, 56 characters).
                                                            //                   SCR[6] = 0, and TLR[3] to TLR[0] not equal to 0000, then: Defined
                                                            //                   by TLR[3] to TLR[0] (from 4 to 60 characters with a granularity of 4
                                                            //                   characters).
                                                            //                   SCR[6] = 1, and TLR[3] to TLR[0] = any value, then: Defined by the
                                                            //                   concatenated value of TLR[3] and TLR[0] and FCR[5] and FCR[4]
                                                            //                   (from 1 to 63 characters with a granularity of 1 character).
                                                            //                   Note: the combination of TLR[3] to TLR[0] = 0000 and FCR[5] and
                                                            //                   FCR[4] = 00 (all zeros) is not supported (minimum of 1 character is
                                                            //                   required).
                                                            //                   All zeros results in unpredictable behavior.
            uint32_t    RX_FIFO_TRIG_DMA       :4;          // bit: 4..7    (RW) Receive FIFO trigger level.
                                                            //                   Following is a summary of settings for the RX FIFO trigger level.
                                                            //                   SCR[7] = 0, and TLR[7] to TLR[4]=0, then: Defined by FCR[7] and
                                                            //                   FCR[6] (either 8, 16, 56, 60 characters).
                                                            //                   SCR[7] = 0, and TLR[7] to TLR[4] not equal to 0000, then: Defined
                                                            //                   by TLR[7] to TLR[4] (from 4 to 60 characters with a granularity of 4
                                                            //                   characters).
                                                            //                   SCR[7] = 1, and TLR[7] to TLR[4] = any value, then: Defined by the
                                                            //                   concatenated value of TLR[7] to TLR[4] and FCR[7] and FCR[6]
                                                            //                   (from 1 to 63 characters with a granularity of 1 character).
                                                            //                   Note: the combination of TLR[7] to TLR[4] = 0000 and FCR[7] and
                                                            //                   FCR[6] = 00 (all zeros) is not supported (minimum of 1 character is
                                                            //                   required).
                                                            //                   All zeros results in unpredictable behavior.
            uint32_t                           :24;         // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } TLR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    In UART mode, XOFF2 character.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    XOFFWORD2               :8;         // bit: 0..7    (RW) Stores the 8 bit XOFF2 character in UART modes.
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } XOFF2_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    The mode of operation is programmed by writing to MDR1[2:0]; therefore, the mode definition register 1 (MDR1) must
    *               be programmed on startup after configuration of the configuration registers (DLL, DLH, and LCR). The
    *               value of MDR1[2:0] must not be changed again during normal operation. If the module is disabled by
    *               setting the MODESELECT field to 7h, interrupt requests can still be generated unless disabled through the
    *               interrupt enable register (IER). In this case, UART mode interrupts are visible. Reading the interrupt
    *               identification register (IIR) shows the UART mode interrupt flags.  
    [reset state = 0x7] */ 
    typedef union 
    { 
        // !!!!!! ERRATA Advisory 1.0.35 UART: Transactions to MDR1 Register May Cause Undesired Effect on UART Operation
        // ! The UART logic may generate an internal glitch when accessing the MDR1 registers that
        // ! causes a dummy under-run condition that will freeze the UART in IrDA transmission. In
        // ! UART mode, this may corrupt the transferred data (received or transmitted).
        struct 
        {             
            uint32_t    MODESELECT              :3;             // bit: 0..2    (RW) UART/IrDA/CIR mode selection. [ see e_MODESELECT ]
            uint32_t    IRSLEEP                 :1;             // bit: 3       (RW) IrDA/CIR sleep mode. [0x0 = disabled; 0x1 = enabled ]
            uint32_t    SETTXIR                 :1;             // bit: 4       (RW) Used to configure the infrared transceiver. [0x0 = If MDR2[7] = 0, no action; if MDR2[7] = 1, TXIR pin output is forced low.; 
                                                                //                                                                0x1 = TXIR pin output is forced high (not dependant of MDR2[7] value). ]
            uint32_t    SCT                     :1;             // bit: 5       (RW) Store and control the transmission. [0x0 = Starts the infrared transmission when a value is written to the THR register.; 
                                                                //                                                        0x1 = Starts the infrared transmission with the control of ACREG[2]. ]
                                                                //                   !! Note: Before starting any transmission, there must be no reception ongoing !!
            uint32_t    SIPMODE                 :1;             // bit: 6       (RW) MIR/FIR modes only. [0x0 = Manual SIP mode: SIP is generated with the control of ACREG[3].; 
                                                                //                                        0x1 = Automatic SIP mode: SIP is generated after each transmission. ]
            uint32_t    FRAMEENDMODE            :1;             // bit: 7       (RW) IrDA mode only. [0x0 = Frame-length method.; 0x1 = Set EOT bit method. ]
            uint32_t                            :24;            // bit: 8..32   Reserved  
        } b;                                                    // Structure used for bit access 
        uint32_t  reg;                                          // Type used for register access 
    } MDR1_reg_t;

    enum e_MODESELECT : uint32_t
    {
        MODE_UART_16x           = 0x0,
        MODE_SIR                = 0x1,
        MODE_UART_16x_AUTOBAUD  = 0x2,
        MODE_UART_13x           = 0x3,
        MODE_MIR                = 0x4,
        MODE_FIR                = 0x5,
        MODE_CIR                = 0x6,
        MODE_DISABLE            = 0x7,  // default state
    };

    /*! @brief    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed    
    *   @details  The MDR2[0] bit describes the status of the TX status interrupt in IIR[5]. The IRTXUNDERRUN bit must be read after a
    *             TX status interrupt occurs. The MDR2[2:1] bits set the trigger level for the frame status FIFO (8 entries)
    *             and must be programmed before the mode is programmed in MDR1[2:0]. The MDR2[6] bit gives the
    *             flexibility to invert the RX pin inside the UART module to ensure that the protocol at the input of the
    *             transceiver module has the same polarity at module level. By default, the RX pin is inverted because most
    *             of transceiver invert the IR receive pin.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    IRTXUNDERRUN            :1;         // bit: 0       (R)  IrDA transmission status interrupt. [0x0 = frame was transmitted successfully without error.; 
                                                            //                                                        0x1 = An underrun occurred. The last bit of the frame was transmitted
                                                            //                                                        but with an underrun error. The bit is reset to 0 when the RESUME register is read. ]
            uint32_t    STSFIFOTRIG             :2;         // bit: 1,2     (RW) Only for IrDA mode.Frame status FIFO threshold select: [see e_IRDA_FIFO_TIRGLVL ]
            uint32_t    UARTPULSE               :1;         // bit: 3       (RW) UART mode only.Used to allow pulse shaping in UART mode.[0x0 = Normal UART mode.; 0x1 = UART mode with pulse shaping. ]
            uint32_t    CIRPULSEMODE            :2;         // bit: 4,5     (RW) CIR pulse modulation definition. Defines high level of the pulse width associated with a digit:[ see e_CIRPULSE_MODULATION ]
            uint32_t    IRRXINVERT              :1;         // bit: 6       (RW) Only for IR mode (IrDA and CIR).
                                                            //                   Invert RX pin in the module before the voting or sampling system
                                                            //                   logic of the infrared block.
                                                            //                   This does not affect the RX path in UART modem modes.[0x0 = Inversion is performed.; 0x1 = No inversion is performed. ]
            uint32_t    SETTXIRALT              :1;         // bit: 7       (RW) Provides alternate functionality for MDR1[4]. [0x0 = Normal mode; 0x1 = Alternate mode for SETTXIR ]
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } MDR2_reg_t;

    enum e_IRDA_FIFO_TIRGLVL : uint32_t
    {
        TRIGLVL_1_ENTRY = 0x0,
        TRIGLVL_4_ENTRY = 0x1,
        TRIGLVL_7_ENTRY = 0x2,
        TRIGLVL_8_ENTRY = 0x3,
    };

    enum e_CIRPULSE_MODULATION : uint32_t
    {
        PULSE_WIDTH_3_12_CYCLES = 0x0,
        PULSE_WIDTH_4_12_CYCLES = 0x1,
        PULSE_WIDTH_5_12_CYCLES = 0x2,
        PULSE_WIDTH_6_12_CYCLES = 0x3,
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The transmit frame length low register (TXFLL) and the TXFLH register hold the 13-bit transmit frame length
    *               (expressed in bytes). TXFLL holds the LSBs and TXFLH holds the MSBs. The frame length value is used
    *               if the frame length method of frame closing is used.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TXFLL               :8;         // bit: 0..7    (W) LSB register used to specify the frame length.
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } TXFLL_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    Reading the status FIFO line status register (SFLSR) effectively reads frame status information from the status FIFO.
    *               This register does not physically exist. Reading this register increments the status FIFO read pointer
    *               (SFREGL and SFREGH must be read first). Top of RX FIFO = Next frame to be read from RX FIFO.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t                            :1;         // bit: 0       Reserved
            uint32_t    CRC_ERROR               :1;         // bit: 1       (R) [0x0 = No error; 0x1 = CRC error in frame at top of RX FIFO. ]
            uint32_t    ABORT_DETECT            :1;         // bit: 2       (R) [0x0 = No error; 0x1 = Abort pattern detected in frame at top of RX FIFO. ]
            uint32_t    FRAME_TOO_LONG_ERROR    :1;         // bit: 3       (R) [0x0 = No error; 0x1 = Frame-length too long error in frame at top of RX FIFO. ]
            uint32_t    OE_ERROR                :1;         // bit: 4       (R) [0x0 = No error; 0x1 = Overrun error in RX FIFO when frame at top of RX FIFO was received. ]
            uint32_t                            :27;        // bit: 5..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } SFLSR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed      
    *   @details    The RESUME register is used to clear internal flags, which halt transmission/reception when an underrun/overrun error
    *               occurs. Reading this register resumes the halted operation. This register does not physically exist and
    *               always reads as 00.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RESUME              :8;         // bit: 0..7    (R) Dummy read to restart the TX or RX, value 0 to FFh.
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } RESUME_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The transmit frame length high register (TXFLH) and the TXFLL register hold the 13-bit transmit frame length
    *               (expressed in bytes). TXFLL holds the LSBs and TXFLH holds the MSBs. The frame length value is used
    *               if the frame length method of frame closing is used.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TXFLH               :5;         // bit: 0..4    (W) MSB register used to specify the frame length, value 0 to 1Fh.
            uint32_t                        :27;        // bit: 5..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } TXFLH_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The received frame length low register (RXFLL) and the RXFLH register hold the 12-bit receive maximum frame length.
    *               RXFLL holds the LSBs and RXFLH holds the MSBs. If the intended maximum receive frame length is n
    *               bytes, program RXFLL and RXFLH to be n + 3 in SIR or MIR modes and n + 6 in FIR mode (+3 and +6
    *               are the result of frame format with CRC and stop flag; two bytes are associated with the FIR stop flag).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFLL               :8;         // bit: 0..7    (W) LSB register used to specify the frame length in reception, value 0 to FFh.
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } RXFLL_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The frame lengths of received frames are written into the status FIFO. This information can be read by reading the
    *               status FIFO register low (SFREGL) and the status FIFO register high (SFREGH). These registers do not
    *               physically exist. The LSBs are read from SFREGL and the MSBs are read from SFREGH. Reading these
    *               registers does not alter the status FIFO read pointer. These registers must be read before the pointer is
    *               incremented by reading the SFLSR.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    SFREGL              :8;         // bit: 0..7    (R) LSB register used to specify the frame length in reception, value 0 to FFh.
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } SFREGL_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The frame lengths of received frames are written into the status FIFO. This information can be read by reading the
    *               status FIFO register low (SFREGL) and the status FIFO register high (SFREGH). These registers do not
    *               physically exist. The LSBs are read from SFREGL and the MSBs are read from SFREGH. Reading these
    *               registers does not alter the status FIFO read pointer. These registers must be read before the pointer is
    *               incremented by reading the SFLSR.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    SFREGH              :4;         // bit: 0..3    (R) MSB part of the frame length, value 0 to Fh.
            uint32_t                        :28;        // bit: 4..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } SFREGH_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The received frame length high register (RXFLH) and the RXFLL register hold the 12-bit receive maximum frame length.
    *               RXFLL holds the LSBs and RXFLH holds the MSBs. If the intended maximum receive frame length is n
    *               bytes, program RXFLL and RXFLH to be n + 3 in SIR or MIR modes and n + 6 in FIR mode (+3 and +6
    *               are the result of frame format with CRC and stop flag; two bytes are associated with the FIR stop flag).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFLH               :4;         // bit: 0..3    (W) MSB register used to specify the frame length in reception, value 0 to Fh.
            uint32_t                        :28;        // bit: 4..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } RXFLH_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    The BLR[6] bit is used to select whether C0h or FFh start patterns are to be used, when multiple start flags are required
    *               in SIR mode. If only one start flag is required, this is always C0h. If n start flags are required, either (n - 1)
    *               C0h or (n -1) FFh flags are sent, followed by a single C0h flag (immediately preceding the first data byte).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t                            :6;         // bit: 0..5    Reserved
            uint32_t    XBOFTYPE                :1;         // bit: 6       (RW) SIR xBOF select.[0x0 = FFh start pattern is used.; 0x1 = C0h start pattern is used. ]
            uint32_t    STSFIFORESET            :1;         // bit: 7       (RW) Status FIFO reset.This bit is self-clearing.
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } BLR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    The UART autobauding status register (UASR) returns the speed, the number of bits by characters, and the type of
    *               parity in UART autobauding mode. In autobauding mode, the input frequency of the UART modem must
    *               be fixed to 48 MHz. Any other module clock frequency results in incorrect baud rate recognition. This
    *               register is used to set up transmission according to characteristics of previous reception, instead of LCR,
    *               DLL, and DLH registers when UART is in autobauding mode. To reset the autobauding hardware (to start
    *               a new AT detection) or to set the UART in standard mode (no autobaud), MDR1[2:0] must be set to 7h
    *               (reset state), then set to 2h (UART in autobaud mode) or cleared to 0 (UART in standard mode). Usage
    *               limitation: Only 7 and 8 bits character (5 and 6 bits not supported). 7 bits character with space parity not
    *               supported. Baud rate between 1200 and 115 200 bp/s (10 possibilities).
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    SPEED                   :5;         // bit: 0..4    (R) Speed. [ see e_AUTOBAUD_SPEED ]
            uint32_t    BITBYCHAR               :1;         // bit: 5       (R) Number of bits by characters. [ 0x0 = 7-bit character identified.; 
                                                            //                                                  0x1 = 8-bit character identified. ]
            uint32_t    PARITYTYPE              :2;         // bit: 6,7     (R) Type of the parity in UART autobauding mode. [ see e_PARITY_TYPE ]
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } UASR_reg_t;

    enum e_AUTOBAUD_SPEED : uint32_t
    {
        ABAUD_NOSPEED = 0x0,
        ABAUD_115200  = 0x1,
        ABAUD_57600   = 0x2,
        ABAUD_38400   = 0x3,
        ABAUD_28800   = 0x4,
        ABAUD_19200   = 0x5,
        ABAUD_14400   = 0x6,
        ABAUD_9600    = 0x7,
        ABAUD_4800    = 0x8,
        ABAUD_2400    = 0x9,
        ABAUD_1200    = 0xA,
    };


    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.    
    *   @details    If transmit FIFO is not empty and MDR1[5] = 1, IrDA starts a new transfer with data of previous frame as soon as
    *               abort frame has been sent. Therefore, TX FIFO must be reset before sending an abort frame. It is
    *               recommended to disable TX FIFO underrun capability by masking corresponding underrun interrupt. When
    *               disabling underrun by setting ACREG[4] = 1, unknown data is sent over TX line.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    EOTEN             :1;           // bit: 0       (RW) EOT (end-of-transmission) bit. The LH writes 1 to this bit just before it writes the last byte to the TX
                                                        //                   FIFO in the set-EOT bit frame-closing method. This bit is automatically cleared when the LH writes to the THR (TXFIFO).
            uint32_t    ABORTEN           :1;           // bit: 1       (RW) Frame abort. The LH can intentionally abort transmission of a frame by writing 1 to
                                                        //                   this bit.Neither the end flag nor the CRC bits are appended to the frame.
            uint32_t    SCTXEN            :1;           // bit: 2       (RW) Store and control TX start. When MDR1[5] = 1 and the LH writes 1 to this bit, the TX statemachine
                                                        //                   starts frame transmission. This bit is self-clearing.
            uint32_t    SENDSIP           :1;           // bit: 3       (RW) MIR/FIR modes only. Send serial infrared interaction pulse (SIP).
                                                        //                   If this bit is set during an MIR/FIR transmission, the SIP is sent at the end of it.
                                                        //                   This bit is automatically cleared at the end of the SIP transmission.[0x0 = No action.; 0x1 = Send SIP pulse. ]
            uint32_t    DISTXUNDERRUN     :1;           // bit: 4       (RW) Disable TX underrun. [ 0x0 = Long stop bits cannot be transmitted. TX underrun is enabled.; 
                                                        //                                          0x1 = Long stop bits can be transmitted. ]
            uint32_t    DISIRRX           :1;           // bit: 5       (RW) Disable RX input. [0x0 = Normal operation (RX input automatically disabled during
                                                        //                                      transmit, but enabled outside of transmit operation).; 
                                                        //                                      0x1 = Disables RX input (permanent state; independent of transmit). ]
            uint32_t    SDMOD             :1;           // bit: 6       (RW) Primary output used to configure transceivers.Connected to the SD/MODE input pin of IrDA transceivers.[0x0 = SD pin is set to high.;
                                                        //                                                                                                                          0x1 = SD pin is set to low. ]
            uint32_t    PULSETYPE         :1;           // bit: 7       (RW) SIR pulse-width select: [0x0 = 3/16 of baud-rate pulse width; 0x1 = 1.6 microseconds ]
            uint32_t                      :24;          // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } ACREG_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    Bit 4 enables the wake-up interrupt, but this interrupt is not mapped into the IIR register. Therefore, when an interrupt
    *               occurs and there is no interrupt pending in the IIR register, the SSR[1] bit must be checked. To clear the
    *               wake-up interrupt, bit SCR[4] must be reset to 0.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    DMAMODECTL              :1;         // bit: 0       (RW) [0x0 = The DMAMODE is set with FCR[3].; 0x1 = The DMAMODE is set with SCR[2:1]. ]
            uint32_t    DMAMODE2                :2;         // bit: 1,2     (RW) Specifies the DMA mode valid if SCR[0] = 1, then:[ see e_SCR_DMA_MODE ]
            uint32_t    TXEMPTYCTLIT            :1;         // bit: 3       (RW) [0x0 = Normal mode for THR interrupt.; 0x1 = THR interrupt is generated when TX FIFO and TX shift register are empty. ]
            uint32_t    RXCTSDSRWAKEUPENABLE    :1;         // bit: 4       (RW) [0x0 = Disables the WAKE UP interrupt and clears SSR[1].; 
                                                            //                    0x1 = Waits for a falling edge of RX, CTS (active-low), or DSR (active-low) pins to generate an interrupt. ]
            uint32_t    DSRIT                   :1;         // bit: 5       (RW) [0x0 = Disables DSR (active-low) interrupt.; 0x1 = Enables DSR (active-low) interrupt. ]
            uint32_t    TXTRIGGRANU1            :1;         // bit: 6       (RW) [0x0 = Disables the granularity of 1 for trigger TX level.; 0x1 = Enables the granularity of 1 for trigger TX level. ]
            uint32_t    RXTRIGGRANU1            :1;         // bit: 7       (RW) [0x0 = Disables the granularity of 1 for trigger RX level.; 0x1 = Enables the granularity of 1 for trigger RX level. ]
            uint32_t                            :24;        // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } SCR_reg_t;

    enum  e_SCR_DMA_MODE : uint32_t
    {
        SCR_DMA_MODE_0 = 0x0,   //  no DMA.
        SCR_DMA_MODE_1 = 0x1,   //  UARTnDMAREQ[0] in TX, UARTnDMAREQ[1] in RX
        SCR_DMA_MODE_2 = 0x2,   //  UARTnDMAREQ[0] in RX
        SCR_DMA_MODE_3 = 0x3,   //  UARTnDMAREQ[0] in TX
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    Bit 1 is reset only when SCR[4] is reset to 0.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TXFIFOFULL              :1;         // bit: 0       (R)  [ 0x0 = TX FIFO is not full.; 0x1 = TX FIFO is full. ]
            uint32_t    RXCTSDSRWAKEUPSTS       :1;         // bit: 1       (R)  Pin falling edge detection: Reset only when SCR[4] is reset to 0. [0x0 = No falling-edge event on RX, CTS (active-low), and DSR
                                                            //                                                                                      (active-low).;
                                                            //                                                                                      0x1 = A falling edge occurred on RX, CTS (active-low), or DSR
                                                            //                                                                                      (active-low). ]
            uint32_t    DMACOUNTERRST           :1;         // bit: 2       (RW) [  0x0 = The DMA counter will not be reset, if the corresponding FIFO is reset (via FCR[1] or FCR[2]).; 
                                                            //                      0x1 = The DMA counter will be reset, if the corresponding FIFO is reset (via FCR[1] or FCR[2]). ]
            uint32_t                            :29;        // bit: 3..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } SSR_reg_t;



    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.      
    *   @details    In IrDA SIR operation, the BOF length register (EBLR) specifies the number of BOF + xBOFs to transmit. The value
    *               set into this register must consider the BOF character; therefore, to send only one BOF with no XBOF, this
    *               register must be set to 1. To send one BOF with n XBOFs, this register must be set to n + 1. Furthermore,
    *               the value 0 sends 1 BOF plus 255 XBOFs. In IrDA MIR mode, the BOF length register (EBLR) specifies
    *               the number of additional start flags (MIR protocol mandates a minimum of 2 start flags). In CIR mode, the
    *               BOF length register (EBLR) specifies the number of consecutive zeros to be received before generating
    *               the RXSTOP interrupt (IIR[2]). All the received zeros are stored in the RX FIFO. When the register is
    *               cleared to 0, this feature is deactivated and always in reception state, which is disabled by setting the
    *               ACREG[5] bit to 1. If the RX_STOP interrupt occurs before a byte boundary, the remaining bits of the last
    *               byte are filled with zeros and then passed into the RX FIFO.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    EBLR                :8;         // bit: 0..7    (RW) IrDA mode: This register allows definition of up to 176 xBOFs, the
                                                        //                   maximum required by IrDA specification.
                                                        //                   CIR mode: This register specifies the number of consecutive zeros
                                                        //                   to be received before generating the RXSTOP interrupt (IIR[2]).
                                                        //                   0h = Feature disabled.
                                                        //                   1h = Generate RXSTOP interrupt after receiving 1 zero bit.
                                                        //                   FFh = Generate RXSTOP interrupt after receiving 255 zero bits.
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } EBLR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    The reset value is fixed by hardware and corresponds to the RTL revision of this module. A reset has no effect on
    *               the value returned.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    MINORREV_               :6;         // bit: 0..5    (R)  Minor revision number of the module.
            uint32_t                            :2;         // bit: 6,7     Reserved
            uint32_t    MAJORREV                :3;         // bit: 8..9    (R)  Major revision number of the module. 
            uint32_t                            :21;        // bit: 3..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } MVR_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details    The AUTOIDLE bit controls a power-saving technique to reduce the logic power consumption of the module
    *               interface; that is, when the feature is enabled, the interface clock is gated off until the module interface is
    *               accessed. When the SOFTRESET bit is set high, it causes a full device reset.   
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    AUTOIDLE        :1;         // bit: 0       (RW) Internal interface clock-gating strategy. [0x0 = Clock is running.; 0x1 = Reserved. ]
            uint32_t    SOFTRESET       :1;         // bit: 1       (RW)  Software reset. Set this bit to 1 to trigger a module reset.
                                                    //                    This bit is automatically reset by the hardware. Read returns 0.[0x0 = Normal mode.; 0x1 = Module is reset. ]
            uint32_t    ENAWAKEUP       :1;         // bit: 2       (RW) Wakeup control. [0x0 = Wakeup is disabled.; 0x1 = Wakeup capability is enabled. ]
            uint32_t    IDLEMODE        :2;         // bit: 3,4     (RW) Power management req/ack control. [ see e_IDLEMODE]
            uint32_t                    :27;        // bit: 5..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } SYSC_reg_t;

    enum e_IDLEMODE : uint32_t
    {
        FORCE_IDLE       = 0x0,     // Idle request is acknowledged unconditionally.
        NO_IDLE          = 0x1,     // Idle request is never acknowledged.
        SMART_IDLE       = 0x2,     // Acknowledgement to an idle request is given based
                                    // in the internal activity of the module.
        SMART_IDLE_WKUP  = 0x3      // Acknowledgement to an idle request is
                                    // given based in the internal activity of the module. The module is
                                    // allowed to generate wakeup request. Only available on UART0
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RESETDONE       :1;         // bit: 0       (RW) Internal reset monitoring. [0x0 = Internal module reset is ongoing.; 0x1 = Reset complete. ]
            uint32_t                    :31;        // bit: 1..32   Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } SYSS_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.   
    *   @details    The wake-up enable register (WER) is used to mask and unmask a UART event that subsequently notifies the system.
    *               An event is any activity in the logic that can cause an interrupt and/or an activity that requires the system
    *               to wake up. Even if wakeup is disabled for certain events, if these events are also an interrupt to the
    *               UART, the UART still registers the interrupt as such.   
    [reset state = 0xFF] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CTS__ACTIVITY       :1;         // bit: 0       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    DSR_ACTIVITY        :1;         // bit: 1       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    RI__ACTIVITY        :1;         // bit: 2       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    DCD_ACTIVITY        :1;         // bit: 3       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    RX__ACTIVITY        :1;         // bit: 4       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    RHR__INTERRUPT      :1;         // bit: 5       (RW) [0x0 = Event is not allowed to wake up the system.; 
                                                        //                    0x1 = Event can wake up the system. ]
            uint32_t    RLS__INTERRUPT      :1;         // bit: 6       (RW) Receiver line status interrupt. [0x0 = Event is not allowed to wake up the system.; 
                                                        //                                                    0x1 = Event can wake up the system. ]
            uint32_t    TXWAKEUPEN          :1;         // bit: 7       (RW) Wake-up interrupt. [0x0 = Event is not allowed to wake up the system.; 
                                                        //                                       0x1 = Event can wake up the system: Event can be: THRIT or
                                                        //                                             TXDMA request and/or TXSATUSIT. ]
            uint32_t                        :24;        // bit: 8..32   Reserved  
        } b;                                            // Structure used for bit access 
        uint32_t  reg;                                  // Type used for register access 
    } WER_reg_t;

    enum e_WER_EVENTS : uint32_t
    {
        EVENT_0_CTS_ACTIVITY    = BIT(0),
        EVENT_1_DSR_ACTIVITY    = BIT(1),
        EVENT_2_RI_ACTIVITY     = BIT(2),
        EVENT_3_DCD_CD_ACTIVITY = BIT(3),
        EVENT_4_RX_ACTIVITY     = BIT(4),
        EVENT_5_RHR_INTERRUPT   = BIT(5),
        EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT = BIT(6),
        EVENT_7_TX_WAKEUP_EN    = BIT(7)
    };       

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.       
    *   @details    Since the consumer IR (CIR) works at modulation rates of 30-56.8 kHz, the 48 MHz clock must be prescaled before
    *               the clock can drive the IR logic. The carrier frequency prescaler register (CFPS) sets the divisor rate to
    *               give a range to accommodate the remote control requirements in BAUD multiples of 12x. The value of the
    *               CFPS at reset is 105 decimal (69h), which equates to a 38.1 kHz output from starting conditions. The 48
    *               MHz carrier is prescaled by the CFPS that is then divided by the 12x BAUD multiple.    
    [reset state = 0x69] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    CFPS                   :8;          // bit: 0       System clock frequency prescaler at (12x multiple).CFPS = 0 is not supported. [ see e_TARGET_CIR_FREQ]
                                                            //              Examples for CFPS values follow.
                                                            //              Target Frequency (kHz) = 30, CFPS (decimal) = 133, Actual
                                                            //              Frequency (kHz) = 30.08.
                                                            //              Target Frequency (kHz) = 32.75, CFPS (decimal) = 122, Actual
                                                            //              Frequency (kHz) = 32.79.
                                                            //              Target Frequency (kHz) = 36, CFPS (decimal) = 111, Actual
                                                            //              Frequency (kHz) = 36.04.
                                                            //              Target Frequency (kHz) = 36.7, CFPS (decimal) = 109, Actual
                                                            //              Frequency (kHz) = 36.69.
                                                            //              Target Frequency (kHz) = 38, CFPS (decimal) = 105, Actual
                                                            //              Frequency (kHz) = 38.1.
                                                            //              Target Frequency (kHz) = 40, CFPS (decimal) = 100, Actual
                                                            //              Frequency (kHz) = 40.
                                                            //              Target Frequency (kHz) = 56.8, CFPS (decimal) = 70, Actual
                                                            //              Frequency (kHz) = 57.14.
            uint32_t                           :24;         // bit: 8..32   Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } CFPS_reg_t;   

    //  for example CIR modualtion frequiencies
    enum e_TARGET_CIR_FREQ : uint32_t
    {
        TARGET_CIR_56_800 = 70,     // Actual Frequency (kHz) = 57.14.
        TARGET_CIR_40_000 = 100,    // Actual Frequency (kHz) = 40.00.
        TARGET_CIR_38_000 = 105,    // Actual Frequency (kHz) = 38.10.
        TARGET_CIR_36_700 = 109,    // Actual Frequency (kHz) = 36.69.
        TARGET_CIR_36_000 = 111,    // Actual Frequency (kHz) = 36.04.
        TARGET_CIR_32_750 = 122,    // Actual Frequency (kHz) = 32.79.
        TARGET_CIR_30_000 = 133     // Actual Frequency (kHz) = 30.08.
    };

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    RXFIFO_LVL      :8;         // bit: 0..7    (R) Level of the RX FIFO.
            uint32_t                    :24;        // bit: 8..32   Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } RXFIFO_LVL_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TXFIFO_LVL      :8;         // bit: 0..7    (R) Level of the TX FIFO
            uint32_t                    :24;        // bit: 8..32   Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } TXFIFO_LVL_reg_t;


    /*! @brief      The IER2 enables RX/TX FIFOs empty corresponding interrupts. Refer to Section 19.3.7.1 to determine
    *               the mode(s) in which this register can be accessed.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    EN_RXFIFO_EMPTY      :1;         // bit: 0    (R) [0x0 = Disables EN_RXFIFO_EMPTY interrupt.; 0x1 = Enables EN_RXFIFO_EMPTY interrupt. ]
            uint32_t    EN_TXFIFO_EMPTY      :1;         // bit: 1    (R) [0x0 = Disables EN_TXFIFO_EMPTY interrupt.; 0x1 = Enables EN_TXFIFO_EMPTY interrupt. ]
            uint32_t                         :30;        // bit: 2..32   Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } IER2_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed. The ISR2
    *               displays the status of RX/TX FIFOs empty corresponding interrupts.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TXFIFO_EMPTY_STS     :1;         // bit: 0    (R) [0x0 = TXFIFO_EMPTY interrupt not pending.; 0x1 = TXFIFO_EMPTY interrupt pending. ]
            uint32_t    RXFIFO_EMPTY_STS     :1;         // bit: 1    (R) [0x0 = RXFIFO_EMPTY interrupt not pending.; 0x1 = RXFIFO_EMPTY interrupt pending. ]
            uint32_t                         :30;        // bit: 2..32   Reserved  
        } b;                                             // Structure used for bit access 
        uint32_t  reg;                                   // Type used for register access 
    } ISR2_reg_t;


    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.     
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    FREQ_SEL       :8;          // bit: 0..7       (RW) Sets the sample per bit if non default frequency is used.
                                                    //                      MDR3[1] must be set to 1 after this value is set. Must be equal or higher then 6.
            uint32_t                   :24;         // bit: 8..32      Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } FREQ_SEL_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.    
    *   @details    The DISABLE_CIR_RX_DEMOD register bit will force the CIR receiver to bypass demodulation of received
    *               data if set. See the CIR Mode Block Components. The NONDEFAULT_FREQ register bit allows the user
    *               to set sample per bit by writing it into FREQ_SEL register. Set it if non-default (48 MHz) fclk frequency is
    *               used to achieve a less than 2% error rate. Changing this bit (to any value) will automatically disable the
    *               device by setting MDR[2:0] to 111 .     
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    DISABLE_CIR_RX_DEMOD       :1;          // bit: 0         (RW) [ 0x0 = Enables CIR RX demodulation.; 
                                                                //                       0x1 = Disables CIR RX demodulation. ]
            uint32_t    NONDEFAULT_FREQ            :1;          // bit: 1         (RW) [ 0x0 = Disables using NONDEFAULT fclk frequencies.; 
                                                                //                       0x1 = Enables using NONDEFAULT fclk frequencies (set FREQ_SEL and DLH/DLL). ]
            uint32_t    SET_DMA_TX_THRESHOLD       :1;          // bit: 2         (RW) [ 0x0 = Disable use of TX DMA Threshold register. Use 64-TX trigger  as DMA threshold.;
                                                                //                       0x1 = Enable to set different TX DMA threshold in the TX DMA Threshold register. ]
            uint32_t                               :29;         // bit: 3..32      Reserved  
        } b;                                                    // Structure used for bit access 
        uint32_t  reg;                                          // Type used for register access 
    } MDR3_reg_t;

    /*! @brief      Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.    
    *   @details       
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    TX_DMA_THRESHOLD    :6;     // bit: 0..5       (RW) Used to manually set the TX DMA threshold level.
                                                    //                      UART_MDR3[2] SET_TX_DMA_THRESHOLD must be 1 and must
                                                    //                      be value + tx_trigger_level = 64 (TX FIFO size).
                                                    //                      If not, 64_tx_trigger_level will be used without modifying the value of
                                                    //                      this register.
            uint32_t                        :26;    // bit: 6..32      Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } TX_DMA_THRESHOLD_reg_t;

    struct AM335x_UART_Type
    {     
        union
        { 
            __W    THR_reg_t               THR;                 // (0x00) - Transmit Holding Register
            __R    RHR_reg_t               RHR;                 // (0x00) - Receiver Holding Register
            __RW   DLL_reg_t               DLL;                 // (0x00) - Divisor Latches Low Register
        };   
        union
        {
            __RW   IER_IRDA_reg_t          IER_IRDA;            // (0x04) - Interrupt Enable Register (IrDA)
            __RW   IER_CIR_reg_t           IER_CIR;             // (0x04) - Interrupt Enable Register (CIR)
            __RW   IER_UART_reg_t          IER_UART;            // (0x04) - Interrupt Enable Register (UART)
            __RW   DLH_reg_t               DLH;                 // (0x04) - Divisor Latches High Register
        };      
        union      
        {      
            __RW   EFR_reg_t               EFR;                 // (0x08) - Enhanced Feature Register 
            __R    IIR_UART_reg_t          IIR_UART;            // (0x08) - Interrupt Identification Register (UART)
            __R    IIR_CIR_reg_t           IIR_CIR;             // (0x08) - Interrupt Identification Register (CIR)
            __W    FCR_reg_t               FCR;                 // (0x08) - FIFO Control Register
            __R    IIR_IRDA_reg_t          IIR_IRDA;            // (0x08) - Interrupt Identification Register (IrDA)
        };                   
            __RW   LCR_reg_t               LCR;                 // (0x0C) - Line Control Register 
        union               
        {                   
            __RW   MCR_reg_t               MCR;                 // (0x10) - Modem Control Register
            __RW   XON1_ADDR1_reg_t        XON1_ADDR1;          // (0x10) - XON1/ADDR1 Register 
        };          
        union           
        {           
            __RW   XON2_ADDR2_reg_t        XON2_ADDR2;          // (0x14) - XON2/ADDR2 Register   
            __R    LSR_CIR_reg_t           LSR_CIR;             // (0x14) - Line Status Register (CIR)
            __R    LSR_IRDA_reg_t          LSR_IRDA;            // (0x14) - Line Status Register (IrDA)
            __R    LSR_UART_reg_t          LSR_UART;            // (0x14) - Line Status Register (UART) 
        };          
        union           
        {           
            __RW   TCR_reg_t               TCR;                 // (0x18) - Transmission Control Register
            __R    MSR_reg_t               MSR;                 // (0x18) - Modem Status Register 
            __RW   XOFF1_reg_t             XOFF1;               // (0x18) - XOFF1 Register 
        };          
        union
        {  
            __RW   SPR_reg_t               SPR;                 // (0x1C) - Scratchpad Register
            __RW   TLR_reg_t               TLR;                 // (0x1C) - Trigger Level Register
            __RW   XOFF2_reg_t             XOFF2;               // (0x1C) - XOFF2 Register 
        };              
            __RW   MDR1_reg_t              MDR1;                // (0x20) - Mode Definition Register 1 
            __RW   MDR2_reg_t              MDR2;                // (0x24) - Mode Definition Register 2
        union           
        {           
            __W    TXFLL_reg_t             TXFLL;               // (0x28) - Transmit Frame Length Low Register
            __R    SFLSR_reg_t             SFLSR;               // (0x28) - Status FIFO Line Status Register 
        };                  
        union               
        {                   
            __R    RESUME_reg_t            RESUME;              // (0x2C) - RESUME Register
            __W    TXFLH_reg_t             TXFLH;               // (0x2C) - Transmit Frame Length High Register 
        };                  
        union               
        {                   
            __W    RXFLL_reg_t             RXFLL;                // (0x30) - Received Frame Length Low Register
            __R    SFREGL_reg_t            SFREGL;               // (0x30) - Status FIFO Register Low 
        };                  
        union               
        {                   
            __R    SFREGH_reg_t            SFREGH;               // (0x34) - Status FIFO Register High
            __W    RXFLH_reg_t             RXFLH;                // (0x34) - Received Frame Length High Register 
        };      
        union      
        {        
            __RW   BLR_reg_t               BLR;                  // (0x38) - BOF Control Register
            __R    UASR_reg_t              UASR;                 // (0x38) - UART Autobauding Status Register 
        };              
            __RW   ACREG_reg_t             ACREG;                // (0x3C) - Auxiliary Control Register  
            __RW   SCR_reg_t               SCR;                  // (0x40) - Supplementary Control Register 
            __RW   SSR_reg_t               SSR;                  // (0x44) - Supplementary Status Register   
            __RW   EBLR_reg_t              EBLR;                 // (0x48) - BOF Length Register
            __R    uint32_t                RESERVED[1];
            __R    MVR_reg_t               MVR;                  // (0x50) - Module Version Register 
            __RW   SYSC_reg_t              SYSC;                 // (0x54) - System Configuration Register   
            __R    SYSS_reg_t              SYSS;                 // (0x58) - System Status Register
            __RW   WER_reg_t               WER;                  // (0x5C) - Wake-Up Enable Register  
            __RW   CFPS_reg_t              CFPS;                 // (0x60) - Carrier Frequency Prescaler Register  
            __R    RXFIFO_LVL_reg_t        RXFIFO_LVL;           // (0x64) - Received FIFO Level Register 
            __R    TXFIFO_LVL_reg_t        TXFIFO_LVL;           // (0x68) - Transmit FIFO Level Register   
            __RW   IER2_reg_t              IER2;                 // (0x6C) - IER2 Register
            __RW   ISR2_reg_t              ISR2;                 // (0x70) - ISR2 Register 
            __RW   FREQ_SEL_reg_t          FREQ_SEL;             // (0x74) - FREQ_SEL Register 
            __R    uint32_t                RESERVED1[2];  
            __RW   MDR3_reg_t              MDR3;                 // (0x80) - Mode Definition Register 3
            __RW   TX_DMA_THRESHOLD_reg_t  TX_DMA_THRESHOLD;     // (0x84) - TX DMA Threshold Register
    };

    constexpr uint32_t AM335x_UART_0_BASE     = 0x44E09000;    
    constexpr uint32_t AM335x_UART_1_BASE     = 0x48022000;    
    constexpr uint32_t AM335x_UART_2_BASE     = 0x48024000;
    constexpr uint32_t AM335x_UART_3_BASE     = 0x481A6000;    
    constexpr uint32_t AM335x_UART_4_BASE     = 0x481A8000;    
    constexpr uint32_t AM335x_UART_5_BASE     = 0x481AA000;   
     
    constexpr AM335x_UART_Type * AM335X_UART_0_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_0_BASE);
    constexpr AM335x_UART_Type * AM335X_UART_1_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_1_BASE);
    constexpr AM335x_UART_Type * AM335X_UART_2_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_2_BASE);
    constexpr AM335x_UART_Type * AM335X_UART_3_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_3_BASE);
    constexpr AM335x_UART_Type * AM335X_UART_4_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_4_BASE);
    constexpr AM335x_UART_Type * AM335X_UART_5_regs = reinterpret_cast<AM335x_UART_Type *>(AM335x_UART_5_BASE); 

    //-> Values used to choose the trigger level granularity. <-//
    enum e_UART_MODULE_TRIG_GRNAULARITY  : uint32_t
    {
        TRIG_LVL_GRANULARITY_4 = 0x0,      
        TRIG_LVL_GRANULARITY_1 = 0x1       
    };

    //-> Values to be used while switching between register configuration modes. <-//
    enum e_UART_CONFIG_MODE  : uint32_t
    {
        CONFIG_MODE_A      = 0x0080,
        CONFIG_MODE_B      = 0x00BF,
        OPERATIONAL_MODE   = 0x007F,
    };
    
    enum e_UART_INSTANCE_NUM : int
    {
        UART_INSTANCE_NA  = -1,
        UART_INSTANCE_0   = 0x0,
        UART_INSTANCE_1   = 0x1,
        UART_INSTANCE_2   = 0x2,
        UART_INSTANCE_3   = 0x3,
        UART_INSTANCE_4   = 0x4,
        UART_INSTANCE_5   = 0x5
    };
    
    constexpr uint32_t RX_FIFO_MAX = 64U;    // must be same as embedded FIFO of AM335x UART
    constexpr uint32_t TX_FIFO_MAX = 64U;    // must be same as embedded FIFO of AM335x UART
}


class sw_Timer;
extern sw_Timer RX_end_timer;
extern void RX_end_callback(void * p_Obj);

class AM335x_UART
{
    enum e_UART_RX_fsm_sts : uint32_t
    {
        RX_IDLE             = 0x0,  // nothing to happen, ready to operation
        RX_IN_PROGESS       = 0x1,  // RX transaction started and in progress 
        RX_CHUNK_RECEIVED   = 0x2,  // one of two of RX paired buffer is full
        RX_TOUT_IS_OUT      = 0x3,  // timeout after the last received byte has expired, the reception is over
        RX_STOPPED          = 0x4   // receiver stopped 
    };
    
    friend void  RX_end_callback(void * p_Obj);
    
public:
            AM335x_UART(n_UART::AM335x_UART_Type *p_uart_regs);
           ~AM335x_UART() {}
     
      void  module_reset();
      void  FIFO_configure_no_DMA(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl);
      void  FIFO_configure_DMA_RxTx(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl);
      
n_UART::FCR_reg_t  FIFO_config(n_UART::SCR_reg_t  cfg_scr, 
                               n_UART::TLR_reg_t  fifo_trigger_lvl, 
                               n_UART::FCR_reg_t  cfg_fcr);

      void  BAUD_set(unsigned int baud_rate);
  uint32_t  reg_config_mode_enable(n_UART::e_UART_CONFIG_MODE mode_flag);
      //void  line_char_config(uint32_t wlen_stb_flag, uint32_t parity_flag);
      // Programming the Line Characteristics. 
      void  char_len_config(n_UART::e_CHAR_LENGHT len);
      void  stop_bit_config(n_UART::e_STOP_BIT stop_bit);
      void  parity_config(n_UART::e_LCR_PARITY parity);

  n_UART::e_MODESELECT  operating_mode_select(n_UART::e_MODESELECT mode_flag);
  uint32_t  divisor_val_compute(uint32_t  module_clk,
                                uint32_t  baud_rate,
                    n_UART::e_MODESELECT  mode_flag,
                                uint32_t  mir_over_samp_rate);
  uint32_t  divisor_latch_write(uint32_t divisor_value);
      void  divisor_latch_enable();
      void  divisor_latch_disable();
      void  reg_conf_mode_restore(uint32_t lcr_reg_value);
      void  break_ctl(bool break_state);
      void  parity_mode_set(uint32_t parity_flag);
  uint32_t  parity_mode_get();
  
 n_UART::e_UART_INSTANCE_NUM  get_UART_inst_number();
       INTC::e_SYS_INTERRUPT  get_UART_sys_interrupt();

      void  DMA_enable(n_UART::e_SCR_DMA_MODE dma_mode_flag);
      void  DMA_disable();
      void  FIFO_register_write(n_UART::FCR_reg_t  cfg_fcr);
  uint32_t  enhan_func_enable();
      void  enhan_func_bit_val_restore(bool enhan_fn_bit_val);
  uint32_t  sub_config_MSRSPR_mode_en();
  uint32_t  sub_config_TCRTLR_mode_en();
  uint32_t  sub_config_XOFF_mode_en();
      void  TCRTLR_bit_val_restore(uint32_t tcr_tlr_bit_val);
      void  int_enable(uint32_t int_flag);
      void  int_disable(uint32_t int_flag);
  uint32_t  space_avail();
  uint32_t  chars_avail();
  uint32_t  char_put_non_blocking(uint8_t byte_write);
      char  char_get_non_blocking();
      char  char_get();
       int  char_get_timeout(uint32_t time_out_val);
      void  char_put(uint8_t byte_tx);
      void  FIFO_char_put(uint8_t byte_tx);
      char  FIFO_char_get();
  uint32_t  FIFO_write(uint8_t *p_Buf, uint32_t num_tx_bytes);
  uint32_t  RX_error_get();
  uint32_t  int_identity_get();
      bool  int_pending_status_get();
      bool  FIFO_enable_status_get();
      void  auto_RTS_auto_CTS_control(uint32_t auto_cts_control, uint32_t auto_rts_control);
      void  special_char_detect_control(uint32_t control_flag);
      void  software_flow_ctrl_opt_set(uint32_t sw_flow_ctrl);
      void  pulse_shaping_control(uint32_t shape_control);
      
      void  idle_mode_configure(n_UART::e_IDLEMODE mode_flag);
      void  wakeup_control(uint32_t control_flag);
      void  auto_idle_mode_control(uint32_t mode_flag);
      void  flow_ctrl_trig_lvl_config(uint32_t rts_halt_flag, uint32_t rts_start_flag);
      void  XON1XOFF1_val_program(uint8_t xon1_value, uint8_t xoff1_value);
      void  XON2XOFF2_val_program(uint8_t xon2_value, uint8_t xoff2_value);
      void  XON_any_feature_control(uint32_t control_flag);
      void  loopback_mode_control(uint32_t control_flag);
      void  modem_control_set(uint32_t mode_flag);
      void  modem_control_clear(uint32_t mode_flag);
  uint32_t  modem_ctatus_get();
  uint32_t  modem_ctatus_change_check();
      void  resume_operation();
      void  wakeup_events_enable(uint32_t wakeup_flag);
      void  wakeup_events_disable(uint32_t wakeup_flag);
      void  FIFO_trig_lvl_gran_control(uint32_t rx_FIFO_gran_ctrl, uint32_t tx_FIFO_gran_ctrl);
      void  DSR_interrupt_control(uint32_t control_flag);
      void  TX_empty_int_control(uint32_t control_flag);
      void  RXCTSDSR_wakeup_configure(uint32_t wake_up_flag);
  uint32_t  RXCTSDSR_transition_status_get();
      void  DMA_counter_reset_control(uint32_t control_flag);
      bool  TX_FIFO_full_status_get();
  uint32_t  TX_FIFO_level_get();
  uint32_t  RX_FIFO_level_get();
  uint32_t  autobaud_parity_get();
  uint32_t  autobaud_word_len_get();
  uint32_t  autobaud_speed_get();
      void  scratchpad_reg_write(uint32_t scratch_value);
  uint32_t  scratchpad_reg_read();
  uint32_t  module_version_number_get();
      void  TX_DMA_threshold_control(bool thrs_ctrl_flag);
      void  TX_DMA_threshold_val_config(uint32_t thrs_value);
      
       bool  is_RX_data_rdy(ring_buffer<n_UART::RX_FIFO_MAX*4>* p_Data); 
                  
       void  rx_irq(void);                  // need to be placed in IRQ_Handler if RX used
       void  tx_irq(void);                  // need to be placed in IRQ_Handler if TX used
       
       void  write(const char *data, size_t len);
       
paired_buffer<char, n_UART::RX_FIFO_MAX>  m_RX_data;   // cumulative received data buffer
paired_buffer<char, n_UART::TX_FIFO_MAX>  m_TX_data;   // storage data buffer for sending
       
private:
        n_UART::AM335x_UART_Type &m_UART_regs; 
        
                            void  m_Start_TX(size_t amount);
                            void  m_Start_RX(size_t amount);
                            bool  m_TX_busy;
               e_UART_RX_fsm_sts  m_RX_sts;
};

extern AM335x_UART uart_0;
#endif // _N_UART_H_