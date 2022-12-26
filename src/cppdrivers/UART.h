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
            uint32_t    RHR        :8;         // bit: 0..7    (RW) Transmit holding register.[Value 0 to FFh.]
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
            uint32_t    FIFO_EN         :1;    // bit: 0       (RW) Can be changed only when the baud clock is not running (DLL and DLH cleared to 0). [0x0 = Disables rcv FIFO; 0x1 = Enables rcv FIFO ]
            uint32_t    RX_FIFO_CLEAR   :1;    // bit: 1       (RW) THR interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    TX_FIFO_CLEAR   :1;    // bit: 2       (RW) Receive stop interrupt  [0x0 = inactive; 0x1 = active ]
            uint32_t    DMA_MODE        :1;    // bit: 3       (RW) RX overrun interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t    TX_FIFO_TRIG    :1;    // bit: 4,5     Reserved
            uint32_t    RX_FIFO_TRIG    :1;    // bit: 6,7     (RW) TX status interrupt [0x0 = inactive; 0x1 = active ]
            uint32_t                    :24;   // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } FCR_reg_t;

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
        IRDA_STS_FIFO            = BIT(4)
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

    /*! @brief    Refer to Section 19.3.7.1 to determine the mode(s) in which this register can be accessed.    
    *   @details  MCR[7:5] can only be written when EFR[4] = 1. Bits 3-0 control the interface with the modem, data set, or peripheral
    *             device that is emulating the modem.  
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {             
            uint32_t    DTR                     :1;         // bit: 0       (RW)  DTR. [0x0 = Force DTR (active-low) output (used in loopback mode) to inactive (high).;
                                                            //                     0x1 = Force DTR (active-low) output (used in loopback mode) to active (low). ]
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
            uint32_t    RXFIFOTRIGHALT          :1;         // bit: 0..3       (RW) RX FIFO trigger level to HALT transmission (0 to 60).
            uint32_t    RXFIFOTRIGSTART         :1;         // bit: 4..7       (RW) RX FIFO trigger level to RESTORE transmission (0 to 60).
            uint32_t                            :24;        // bit: 8..32       Reserved  
        } b;                                                // Structure used for bit access 
        uint32_t  reg;                                      // Type used for register access 
    } TCR_reg_t;


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

    struct AM335x_UART_Type
    {     
        union
        { 
            __RW   THR_reg_t               THR;                 // (0x00) - Transmit Holding Register
            __RW   RHR_reg_t               RHR;                 // (0x00) - Receiver Holding Register
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
            __  MDR1_reg_t                MDR1;                 // (0x20) - Mode Definition Register 1 
            __  MDR2_reg_t                MDR2;                 // (0x24) - Mode Definition Register 2
        union           
        {           
            __  TXFLL_reg_t               TXFLL;                // (0x28) - Transmit Frame Length Low Register
            __  SFLSR_reg_t               SFLSR;                // (0x28) - Status FIFO Line Status Register 
        };                  
        union               
        {                   
            __  RESUME_reg_t              RESUME;               // (0x2C) - RESUME Register
            __  TXFLH_reg_t               TXFLH;                // (0x2C) - Transmit Frame Length High Register 
        };                  
        union               
        {                   
            __  RXFLL_reg_t               RXFLL;                // (0x30) - Received Frame Length Low Register
            __  SFREGL_reg_t              SFREGL;               // (0x30) - Status FIFO Register Low 
        };                  
        union               
        {                   
            __  SFREGH_reg_t              SFREGH;               // (0x34) - Status FIFO Register High
            __  RXFLH_reg_t               RXFLH;                // (0x34) - Received Frame Length High Register 
        };      
        union      
        {        
            __  BLR_reg_t                 BLR;                  // (0x38) - BOF Control Register
            __  UASR_reg_t                UASR;                 // (0x38) - UART Autobauding Status Register 
        };              
            __  ACREG_reg_t               ACREG;                // (0x3C) - Auxiliary Control Register  
            __   SCR_reg_t                SCR;                  // (0x40) - Supplementary Control Register 
            __   SSR_reg_t                SSR;                  // (0x44) - Supplementary Status Register   
            __   EBLR_reg_t               EBLR;                 // (0x48) - BOF Length Register
            __   uint32_t                 RESERVED[1];
            __   MVR_reg_t                MVR;                  // (0x50) - Module Version Register 
            __   SYSC_reg_t               SYSC;                 // (0x54) - System Configuration Register   
            __   SYSS_reg_t               SYSS;                 // (0x58) - System Status Register
            __   WER_reg_t                WER;                  // (0x5C) - Wake-Up Enable Register  
            __   CFPS_reg_t               CFPS;                 // (0x60) - Carrier Frequency Prescaler Register  
            __   RXFIFO_LVL_reg_t         RXFIFO_LVL;           // (0x64) - Received FIFO Level Register 
            __   TXFIFO_LVL_reg_t         TXFIFO_LVL;           // (0x68) - Transmit FIFO Level Register   
            __   IER2_reg_t               IER2;                 // (0x6C) - IER2 Register
            __   ISR2_reg_t               ISR2;                 // (0x70) - ISR2 Register 
            __   FREQ_SEL_reg_t           FREQ_SEL;             // (0x74) - FREQ_SEL Register 
            __   uint32_t                 RESERVED1[2];  
            __   MDR3_reg_t               MDR3;                 // (0x80) - Mode Definition Register 3
            __   TX_DMA_THRESHOLD_reg_t   TX_DMA_THRESHOLD;     // (0x84) - TX DMA Threshold Register
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
}

#endif // _UART_H_