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

    enum e_CIR_IRQSTATUS_flags
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

    struct AM335x_UART_Type
    {     
        union
        { 
            __RW    THR_reg_t             THR;                  // (0x00) - Transmit Holding Register
            __RW    RHR_reg_t             RHR;                  // (0x00) - Receiver Holding Register
            __RW    DLL_reg_t             DLL;                  // (0x00) - Divisor Latches Low Register
        };   
        union
        {
            __RW    IER_IRDA_reg_t        IER_IRDA;             // (0x04) - Interrupt Enable Register (IrDA)
            __RW    IER_CIR_reg_t         IER_CIR;              // (0x04) - Interrupt Enable Register (CIR)
            __RW    IER_UART_reg_t        IER_UART;             // (0x04) - Interrupt Enable Register (UART)
            __RW    DLH_reg_t             DLH;                  // (0x04) - Divisor Latches High Register
        };      
        union      
        {      
            __RW   EFR_reg_t              EFR;                  // (0x08) - Enhanced Feature Register 
            __R    IIR_UART_reg_t         IIR_UART;             // (0x08) - Interrupt Identification Register (UART)
            __R    IIR_CIR_reg_t          IIR_CIR;              // (0x08) - Interrupt Identification Register (CIR)
            __W    FCR_reg_t              FCR;                  // (0x08) - FIFO Control Register
            __   IIR_IRDA_reg_t           IIR_IRDA;             // (0x08) - Interrupt Identification Register (IrDA)
        };                  
            __   LCR_reg_t                LCR;                  // (0x0C) - Line Control Register 
        union               
        {                   
            __   MCR_reg_t                MCR;                  // (0x10) - Modem Control Register
            __   XON1_ADDR1_reg_t         XON1_ADDR1;           // (0x10) - XON1/ADDR1 Register 
        };          
        union           
        {           
            __   XON2_ADDR2_reg_t         XON2_ADDR2;           // (0x14) - XON2/ADDR2 Register   
            __   LSR_CIR_reg_t            LSR_CIR;              // (0x14) - Line Status Register (CIR)
            __   LSR_IRDA_reg_t           LSR_IRDA;             // (0x14) - Line Status Register (IrDA)
            __   LSR_UART_reg_t           LSR_UART;             // (0x14) - Line Status Register (UART) 
        };          
        union           
        {           
            __  TCR_reg_t                 TCR;                  // (0x18) - Transmission Control Register
            __  MSR_reg_t                 MSR;                  // (0x18) - Modem Status Register 
            __  XOFF1_reg_t               XOFF1;                // (0x18) - XOFF1 Register 
        };          
        union
        {  
            __  SPR_reg_t                 SPR;                  // (0x1C) - Scratchpad Register
            __  TLR_reg_t                 TLR;                  // (0x1C) - Trigger Level Register
            __  XOFF2_reg_t               XOFF2;                // (0x1C) - XOFF2 Register 
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
}

#endif // _UART_H_