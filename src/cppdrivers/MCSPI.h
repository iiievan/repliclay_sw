#ifndef _MCSPI_H_
#define _MCSPI_H_

#include <stdint.h>
#include "app_utils.h"
#include "INTC.h"

namespace MCSPI
{   
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_MCSPI_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/      
 
     /*! @brief     The McSPI system configuration register (MCSPI_REVISION) allows control of various parameters of the
     *              module interface.    
     *   @details   It is not sensitive to software reset.      
    [reset state = 0x300000]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    Y_MINOR    :6;         // bit: 0..5       (RW)  Y_MINOR bit.
            uint32_t    CUSTOM     :2;         // bit: 6,7        (RW)  CUSTOM bit.
            uint32_t    X_MAJOR    :3;         // bit: 8..10      (R)   X_MAJOR bit.
            uint32_t    R_RTL      :5;         // bit: 11..15     (R)   R_RTL bit.
            uint32_t    FUNC       :12;        // bit: 16..27     (R)   Function indicates a software compatible module family.
                                               //                       If there is no level of software compatibility a new Func number (and
                                               //                       hence REVISION) should be assigned.
            uint32_t               :2;         // bit: 28.29      Reserved
            uint32_t    SCHEME     :2;         // bit: 30,31      (R)   Used to distinguish between old scheme and current. [0x0 = Legacy scheme.; 0x1 = Revision 0.8 scheme.]         
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } REVISION_reg_t;

     /*! @brief     The McSPI system configuration register (MCSPI_REVISION) allows control of various parameters of the
     *              module interface.    
     *   @details   It is not sensitive to software reset.      
    [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    AUTOIDLE          :1;     // bit: 0         (RW)  Internal OCP Clock gating strategy. [0x0 = free-running.; 0x1 = Automatic ]
            uint32_t    SOFTRESET         :1;     // bit: 1         (RW)  Software reset. [0x0 = Normal mode.; 0x1 = Reset. ]
            uint32_t                      :1;     // bit: 2         Reserved.
            uint32_t    SIDLEMODE         :2;     // bit: 3,4       (RW)  Power management. [see e_SYSCONFIG_SIDLEMODE]
            uint32_t                      :3;     // bit: 5..7      Reserved.

            uint32_t    CLOCKACTIVITY     :2;     // bit: 8,9       (RW)  Clocks activity during wake-up mode period.[see e_SYSCFG_CLKACTIVITY]
            uint32_t                      :22;    // bit: 10..31    Reserved        
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } SYSCONFIG_reg_t;

    enum e_SYSCONFIG_SIDLEMODE : uint32_t
    {
        SYSCFG_INACTIVE   = 0x0,  // If an idle request is detected, the McSPI acknowledges it
                                  // unconditionally and goes in Inactive mode. Interrupt, DMA requests
                                  // are unconditionally de-asserted.
        SYSCFG_NORMALLY   = 0x1,  // If an idle request is detected, the request is ignored and keeps
                                  // on behaving normally.
        SYSCFG_SMART_IDLE = 0x2,  // Smart-idle mode: local target's idle state eventually follows
                                  // (acknowledges) the system's idle requests, depending on the IP.
                                  // module's internal requirements.
        SYSCFG_RESERVED   = 0x3   // Reserved.
    };

    enum e_SYSCFG_CLKACTIVITY : uint32_t
    {
        BOTH_SWITCHED_OFF    = 0x0,  // OCP and Functional clocks may be switched off.
        OCP_MAINTAINED       = 0x1,  // OCP clock is maintained. Functional clock may be switched-off.
        FCLK_MAINTAINED      = 0x2,  // Functional clock is maintained. OCP clock may be switched-off.
        BOTH_MAINTAINED      = 0x3   // OCP and Functional clocks are maintained.
    };

    /*! @brief     The McSPI system status register (MCSPI_SYSSTATUS) provides status information about the module
     *             excluding the interrupt status information.    
     *   @details         
    [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    RESETDONE     :1;     // bit: 0       (R) Internal Reset Monitoring.[0x0 = Internal module reset is on-going.; 0x1 = Reset completed ]
            uint32_t                  :31;    // bit: 1..31    Reserved        
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } SYSSTATUS_reg_t;

    /*! @brief     The McSPI interrupt status register (MCSPI_IRQSTATUS) regroups all the status of the module internal
    *              events that can generate an interrupt    
    *   @details   For all interrupts (W)[0x0 = Event status bit is unchanged.; 0x1 = event status bit is reset. ]
    *                                 (R)[0x0 = Event false.; 0x1 = Event is pending. ]      
    [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    TX0_EMPTY       :1;     // bit: 0       (RW) Transmitter register empty or almost empty.Channel 1. [see @details] 
            uint32_t    TX0_UNDERFLOW   :1;     // bit: 1       (RW) Transmitter register underflow.Channel 0.[see @details] 
            uint32_t    RX0_FULL        :1;     // bit: 2       (RW) Receiver register full or almost full.Channel 0.[see @details] 
            uint32_t    RX0_OVERFLOW    :1;     // bit: 3       (RW) Receiver register overflow (slave mode only).Channel 0.[see @details] 
            uint32_t    TX1_EMPTY       :1;     // bit: 4       (RW) Transmitter register empty or almost empty.Channel 1.
                                                //                    This bit indicate FIFO almost full status when built-in FIFO is use for
                                                //                    transmit register (MCSPI_CH3CONF[FFE1W] is set).[see @details] 
            uint32_t    TX1_UNDERFLOW   :1;     // bit: 5       (RW) Transmitter register underflow.Channel 1.
            uint32_t    RX1_FULL        :1;     // bit: 6       (RW) Receiver register full or almost full.Channel 1.
                                                //                   This bit indicate FIFO almost full status when built-in FIFO is use for
                                                //                   receive register (MCSPI_CH3CONF[FFE1R] is set).[see @details] 
            uint32_t                    :1;     // bit: 7       Reserved
            uint32_t    TX2_EMPTY       :1;     // bit: 8       (RW) Transmitter register empty or almost empty.Channel 2.
                                                //                   This bit indicate FIFO almost full status when built-in FIFO is used
                                                //                   for transmit register (MCSPI_CH3CONF[FFE2W] is set).[see @details] 
            uint32_t    TX2_UNDERFLOW   :1;     // bit: 9       (RW) Transmitter register underflow.Channel 2.[see @details] 
            uint32_t    RX2_FULL        :1;     // bit: 10      (RW) Receiver register full or almost full.Channel 2.
                                                //                   This bit indicate FIFO almost full status when built-in
                                                //                   FIFO is used for receive register (MCSPI_CH3CONF[FFE2R] is set).[see @details] 
            uint32_t                    :1;     // bit: 11      Reserved
            uint32_t    TX3_EMPTY       :1;     // bit: 12      (RW) Transmitter register is empty or almost empty.
                                                //                   This bit indicate FIFO almost full status when built-in FIFO is used
                                                //                   for transmit register (MCSPI_CH3CONF[FFE3W] is set).
                                                //                   Note: Enabling the channel automatically raises this event.[see @details] 
            uint32_t    TX3_UNDERFLOW   :1;     // bit: 13      (RW) Transmitter register underflow.
                                                //                   Only when Channel 3 is enabled.
                                                //                   The transmitter register is empty (not updated by Host or DMA with
                                                //                   new data) before its time slot assignment.
                                                //                   Exception: No TX_underflow event when no data has been loaded
                                                //                   into the transmitter register since channel has been enabled.[see @details] 
            uint32_t    RX3_FULL        :1;     // bit: 14      (RW) Receiver register is full or almost full.
                                                //                   Only when Channel 3 is enabled.
                                                //                   This bit indicate FIFO almost full status when built-in FIFO is used
                                                //                   for receive register (MCSPI_CH3CONF[FFE3R] is set).[see @details] 
            uint32_t                    :2;     // bit: 15,16   Reserved
            uint32_t    EOW             :1;     // bit: 17      (RW) End of word (EOW) count event when a channel is enabled using
                                                //                   the FIFO buffer and the channel has sent the number of McSPI
                                                //                   words defined by the MCSPI_XFERLEVEL[WCNT].[see @details] 
            uint32_t                    :14;    // bit: 18..31   Reserved        
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } IRQSTATUS_reg_t;
    /** see e_IRQ_mask**/

    enum e_IRQ_mask: uint32_t
    {
        M_IRQ_NONE            = 0x0,
        M_IRQ_TX0_EMPTY       = BIT(0),
        M_IRQ_TX0_UNDERFLOW   = BIT(1),
        M_IRQ_RX0_FULL        = BIT(2),
        M_IRQ_RX0_OVERFLOW    = BIT(3),
        M_IRQ_TX1_EMPTY       = BIT(4),

        M_IRQ_TX1_UNDERFLOW   = BIT(5),
        M_IRQ_RX1_FULL        = BIT(6),
        M_IRQ_TX2_EMPTY       = BIT(8),
        M_IRQ_TX2_UNDERFLOW   = BIT(9),
        M_IRQ_RX2_FULL        = BIT(10),
        M_IRQ_TX3_EMPTY       = BIT(12),
        M_IRQ_TX3_UNDERFLOW   = BIT(13),
        M_IRQ_RX3_FULL        = BIT(14),
        M_IRQ_EOW             = BIT(17),
        M_IRQ_ALL             = 0x3FFFF
    };

    /*! @brief     This McSPI interrupt enable register (MCSPI_IRQENABLE) enables/disables the module internal sources
    *              of interrupt, on an event-by-event basis.         
    [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    TX0_EMPTY_ENABLE       :1;     // bit: 0       (RW) TX0 transmitter register empty or almost empty interruptenable (channel 0).[0x0 =  disabled.; 0x1 =  enabled. ]
            uint32_t    TX0_UNDERFLOW_ENABLE   :1;     // bit: 1       (RW) TX0 transmitter register underflow interrupt enable (channel0).[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t    RX0_FULL_ENABLE        :1;     // bit: 2       (RW) RX0 receiver register full or almost full interrupt enable(channel 0).[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t    RX0_OVERFLOW_ENABLE    :1;     // bit: 3       (RW) RX0 receivier register overflow interrupt enable (channel 0).[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t    TX1_EMPTY_ENABLE       :1;     // bit: 4       (RW) TX1 transmitter register empty or almost empty interruptenable (channel 1).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t    TX1_UNDERFLOW_ENABLE   :1;     // bit: 5       (RW) TX1 transmitter register underflow interrupt enable (channel1).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t    RX1_FULL_ENABLE        :1;     // bit: 6       (RW) RX1 receiver register full or almost full interrupt enable(channel 1)[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t                           :1;     // bit: 7       Reserved
            uint32_t    TX2_EMPTY_ENABLE       :1;     // bit: 8       (RW) TX2 transmitter register empty or almost empty interrupt enable (channel 2).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t    TX2_UNDERFLOW_ENABLE   :1;     // bit: 9       (RW) TX2 transmitter register underflow interrupt enable (channel2).[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t    RX2_FULL_ENABLE        :1;     // bit: 10      (RW) RX2 receiver register full or almost full interrupt enable(channel 2).[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t                           :1;     // bit: 11      Reserved
            uint32_t    TX3_EMPTY_ENABLE       :1;     // bit: 12      (RW) TX3 transmitter register empty or almost empty interrupt enable (channel 3).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t    TX3_UNDERFLOW_ENABLE   :1;     // bit: 13      (RW) TX3 transmitter register underflow interrupt enable (channel3).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t    RX3_FULL_ENABLE        :1;     // bit: 14      (RW) RX3 receiver register full or almost full interrupt enable(channel 3).[0x0 = disabled.; 0x1 = enabled. ]
            uint32_t                           :2;     // bit: 15,16   Reserved
            uint32_t    EOWKE                  :1;     // bit: 17      (RW) End of word count interrupt enable.[0x0 = disabled.; 0x1 = enabled. ] 
            uint32_t                           :14;    // bit: 18..31   Reserved        
        } b;                                           // Structure used for bit access 
        uint32_t  reg;                                 // Type used for register access 
    } IRQENABLE_reg_t;
    /** see e_IRQ_mask**/

     /*! @brief     This McSPI system register (MCSPI_SYST) is used to configure the system interconnect either internally
     *              to the peripheral bus or externally to the device I/O pads, when the module is configured in the system
     *              test (SYSTEST) mode    
     *   @details        
    [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {              
            uint32_t    SPIEN_0          :1;     // bit: 0         (RW)  SPIEN[0] line (signal data value)  [see e_LINE_MODE]
            uint32_t    SPIEN_1          :1;     // bit: 1         (RW)  SPIEN[1] line (signal data value)  [see e_LINE_MODE]
            uint32_t    SPIEN_2          :1;     // bit: 2         (RW)  SPIEN[2] line (signal data value)  [see e_LINE_MODE]
            uint32_t    SPIEN_3          :1;     // bit: 3         (RW)  SPIEN[3] line (signal data value)  [see e_LINE_MODE]
            uint32_t    SPIDAT_0         :1;     // bit: 4         (RW)  SPIDAT[0] line (signal data value) [see e_LINE_MODE]
            uint32_t    SPIDAT_1         :1;     // bit: 5         (RW)  SPIDAT[1] line (signal data value) [see e_LINE_MODE]
            uint32_t    SPICLK           :1;     // bit: 6         (RW)  SPICLK line (signal data value)    [see e_LINE_MODE]
            uint32_t                     :1;     // bit: 7         Reserved
            uint32_t    SPIDATDIR0       :1;     // bit: 8         (RW)   Sets the direction of the SPIDAT[0].[see e_CH_DIR]
            uint32_t    SPIDATDIR1       :1;     // bit: 9         (RW)   Sets the direction of the SPIDAT[1].[see e_CH_DIR]
            uint32_t    SPIENDIR         :1;     // bit: 10        (RW)   Sets the direction of the SPIEN[3:0] lines and SPICLK line.[ see e_CH_DIR]
            uint32_t    SSB              :1;     // bit: 11        (RW)   Set status bit. This bit must be cleared prior attempting to clear a status bit of the MCSPI_ IRQSTATUS register.
                                                 //                       [ 0x0 = No action. Writing 0 does not clear already set status bits. This
                                                 //                         bit must be cleared prior attempting to clear a status bit of the
                                                 //                         MCSPI_IRQSTATUS register.;
                                                 //                         0x1 = Writing 1 sets to 1 all status bits contained in the
                                                 //                         MCSPI_IRQSTATUS register. Writing 1 into this bit sets to 1 all
                                                 //                         status bits contained in the MCSPI_IRQSTATUS register. ]
            uint32_t                     :20;    // bit: 12..31    Reserved.     
        } b;                                     // Structure used for bit access 
        uint32_t  reg;                           // Type used for register access 
    } SYST_reg_t;

    enum e_LINE_MODE : uint32_t
    {
        OUTPUT_MODE_DIR = 0x0,  // the line is driven high or low according to the value written into this register.
        INPUT_MODE_DIR  = 0x1   // this bit returns the value on the line (high or low), and a write into this bit has no effect.
    };

    enum e_CH_DIR : uint32_t
    {
        CH_OUTPUT = 0x0,  
        CH_INPUT  = 0x1   
    };

    struct AM335x_MCSPI_Type 
    {                                                                                      
        __RW  REVISION_reg_t        REVISION;       // (0x0)    McSPI revision register
        __R   uint32_t              RESERVED[67];
        __RW  SYSCONFIG_reg_t       SYSCONFIG;      // (0x110)   McSPI system configuration register
        __R   SYSSTATUS_reg_t       SYSSTATUS;      // (0x114)   McSPI system status register
        __RW  IRQSTATUS_reg_t       IRQSTATUS;      // (0x118)   McSPI interrupt status register
        __RW  IRQENABLE_reg_t       IRQENABLE;      // (0x11C)   McSPI interrupt enable register
        __R   uint32_t              RESERVED[1];
        __RW  SYST_reg_t            SYST;           // (0x124)   McSPI system register
        __  MODULCTRL_reg_t       MODULCTRL;      // (0x128)   McSPI module control register
        __  CH0CONF_reg_t         CH0CONF;        // (0x12C)   McSPI channel 0 configuration register
        __  CH0STAT_reg_t         CH0STAT;        // (0x130)   McSPI channel 0 status register
        __  CH0CTRL_reg_t         CH0CTRL;        // (0x134)   McSPI channel 0 control register
        __  TX0_reg_t             TX0;            // (0x138)   McSPI channel 0 FIFO transmit buffer register
        __  RX0_reg_t             RX0;            // (0x13C)   McSPI channel 0 FIFO receive buffer register
        __  CH1CONF_reg_t         CH1CONF;        // (0x140)   McSPI channel 1 configuration register
        __  CH1STAT_reg_t         CH1STAT;        // (0x144)   McSPI channel 1 status register
        __  CH1CTRL_reg_t         CH1CTRL;        // (0x148)   McSPI channel 1 control register
        __  TX1_reg_t             TX1;            // (0x14C)   McSPI channel 1 FIFO transmit buffer register
        __  RX1_reg_t             RX1;            // (0x150)   McSPI channel 1 FIFO receive buffer register 
        __  CH2CONF_reg_t         CH2CONF;        // (0x154)   McSPI channel 2 configuration register
        __  CH2STAT_reg_t         CH2STAT;        // (0x158)   McSPI channel 2 status register
        __  CH2CTRL_reg_t         CH2CTRL;        // (0x15C)   McSPI channel 2 control register
        __  TX2_reg_t             TX2;            // (0x160)   McSPI channel 2 FIFO transmit buffer register
        __  RX2_reg_t             RX2;            // (0x164)   McSPI channel 2 FIFO receive buffer register
        __  CH3CONF_reg_t         CH3CONF;        // (0x168)   McSPI channel 3 configuration register
        __  CH3STAT_reg_t         CH3STAT;        // (0x16C)   McSPI channel 3 status register
        __  CH3CTRL_reg_t         CH3CTRL;        // (0x170)   McSPI channel 3 control register
        __  TX3_reg_t             TX3;            // (0x174)   McSPI channel 3 FIFO transmit buffer register
        __  RX3_reg_t             RX3;            // (0x178)   McSPI channel 3 FIFO receive buffer register
        __  XFERLEVEL_reg_t       XFERLEVEL;      // (0x17C)   McSPI transfer levels register
        __  DAFTX_reg_t           DAFTX;          // (0x180)   McSPI DMA address aligned FIFO transmitter register
        __R  uint32_t              RESERVED[7];
        __  DAFRX_reg_t           DAFRX;          // (0x1A0)   McSPI DMA address aligned FIFO receiver register

    };
    
    constexpr uint32_t AM335x_MCSPI_0_BASE     = 0x48030000;    
    constexpr uint32_t AM335x_MCSPI_1_BASE     = 0x481A0000;     
     
    constexpr AM335x_MCSPI_Type * AM335X_MCSPI_0 = ((AM335x_MCSPI_Type *) AM335x_MCSPI_0_BASE); 
    constexpr AM335x_MCSPI_Type * AM335X_MCSPI_1 = ((AM335x_MCSPI_Type *) AM335x_MCSPI_1_BASE);         
} // namespace MCSPI
        

 

#endif //_MCSPI_H_
        
