#ifndef _AM335X_MEM_MAP_H_
#define _AM335X_MEM_MAP_H_

#include <stdint.h>
#include "utils.h"
#include "INTC.h"

namespace I2C
{      
   /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This read-only register contains the hard-coded revision number of the module.
                                                  A write to this register has no effect. I2C controller with interrupt using interrupt vector register (I2C_IV) is revision 1.x.
                                                  I2C controller with interrupt using status register bits (I2C_IRQSTATUS_RAW) is revision 2.x. */
                                                               
            uint32_t    MINOR   :6;            // bit: 0..5    Minor Revision. This field changes when features are scaled up or down.                        
            uint32_t    CUSTOM  :2;            // bit: 6,7     Indicates a special version for a particular device. [0 if non-custom.]                                 
            uint32_t    MAJOR   :3;            // bit: 8..10   Major Revision. This field changes when there is a major feature change.
            uint32_t    RTL     :5;            // bit: 11..15  RTL Version.          
            uint32_t            :16;           // bit: 16..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_REVNB_LO_reg_t;
    
    /* [reset state = 0x0]*/      
    typedef union 
    { 
        struct 
        {                                      /* A reset has no effect on the value returned. */
                                                               
            uint32_t    FUNC    :12;           // bit: 0..11   Function: Indicates a software compatible module family.                        
            uint32_t            :2;            // bit: 12,13   Reserved.                                 
            uint32_t    SCHEME  :2;            // bit: 14,15   Used to distinguish between old Scheme and current. Spare bit to encode future schemes.       
            uint32_t            :16;           // bit: 16..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_REVNB_HI_reg_t;
    
   /* [reset state = 0x0]*/ 
    typedef union 
    { 
        struct 
        {                                      /* This register allows controlling various parameters of the peripheral interface. */
                                                               
            uint32_t    AUTOIDLE       :1;     // bit: 0       Autoidle bit.  [ 0h = disabled. 1h = enabled]         
            uint32_t    SRST           :1;     // bit: 1       SoftReset bit. [0h = Normal mode. 1h = The module is reset.]                               
            uint32_t    ENAWAKEUP      :1;     // bit: 2       Enable wakeup mechanism.[ 0h = disabled. 1h = enabled.]
            uint32_t    IDLEMODE       :2;     // bit: 3,4     Enable Wakeup control bit. [see e_SYSC_IDLEMODE]
            uint32_t                   :3;     // bit: 5..7    Reserved
            uint32_t    CLKACTIVITY    :2;     // bit: 8,9     Clock Activity selection bits. [see e_SYSC_CLKACTIVITY]         
            uint32_t                   :22;    // bit: 10..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_SYSC_reg_t;

    enum e_SYSC_IDLEMODE : uint32_t
    {
        SYSC_NOIDLE         = 0x1,
        SYSC_SMARTIDLE      = 0x2,
        SYSC_SMARTIDLE_WKUP = 0x3,  // Available only on I2C0.
    };

    enum e_SYSC_CLKACTIVITY : uint32_t
    {
        SYSC_BOTH_CUTOFF      = 0x0,
        SYSC_INTOCPCLK_ACTIVE = 0x1,
        SYSC_SYSTEMCLK_ACTIVE = 0x2,
        SYSC_BOTH_ACTIVE      = 0x3
    };
    
   /* [reset state = 0x0]*/ 
    typedef union 
    { 
        struct 
        {                                      /* This register provides core status information for interrupt handling, showing all active events (enabled and not enabled).
                                                  The fields are read-write. Writing a 1 to a bit will set it to 1, that is, trigger the IRQ (mostly for debug).
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  Only enabled, active events will trigger an actual interrupt request on the IRQ output line. */
                                                               
            uint32_t    AL       :1;           // bit: 0       Arbitration lost IRQ status.  [0x0 = Normal operation; 0x1 = Arbitration lost detected]       
            uint32_t    NACK     :1;           // bit: 1       No acknowledgment IRQ status. [0x0 = Normal operation; 0x1 = Not Acknowledge detected]                                
            uint32_t    ARDY     :1;           // bit: 2       I2C mode only. [0x0 = No action; 0x1 = Access ready]
            uint32_t    RRDY     :1;           // bit: 3       Receive mode only (I2C mode). [0x0 = Receive FIFO threshold not reached; 0x1 = RX FIFO threshold reached]
            uint32_t    XRDY     :1;           // bit: 4       Transmit data ready IRQ status.[0x0 = Transmission ongoing; 0x1 = Transmit data ready]
            uint32_t    GC       :1;           // bit: 5       General call IRQ status. [0x0 = No general call detected; 0x1 = General call address detected]          
            uint32_t    STC      :1;           // bit: 6       Start Condition IRQ status. [0x0 = No action; 0x1 = Start Condition detected]  
            uint32_t    AERR     :1;           // bit: 7       Access Error IRQ status. [0x0 = No action; 0x1 = Access Error]  
            uint32_t    BF       :1;           // bit: 8       Set to 1 when BUS FREE. [0x0 = No action; 0x1 = Bus Free] 
            uint32_t    AAS      :1;           // bit: 9       Address recognized as slave IRQ status. [0x0 = No action; 0x1 = Address recognized]  
            uint32_t    XUDF     :1;           // bit: 10      Transmit underflow status. [0x0 = Normal operation; 0x1 = Transmit underflow]   
            uint32_t    ROVR     :1;           // bit: 11      Receive overrun status. [0x0 = Normal operation; 0x1 = Receiver overrun] 
            uint32_t    BB       :1;           // bit: 12      This read-only bit indicates the state of the serial bus. [0x0 = Bus is free; 0x1 = Bus is occupied]
            uint32_t    RDR      :1;           // bit: 13      Receive draining IRQ status. [0x0 = inactive; 0x1 = enabled]
            uint32_t    XDR      :1;           // bit: 14      Transmit draining IRQ status. [0x0 = inactive; 0x1 = enabled]
            uint32_t             :17;          // bit: 15..31  Reserved
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_IRQSTATUS_RAW_reg_t;
    // to mask this register please see --> e_IRQSTATUS_flags <--
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                  /* This register provides core status information for interrupt handling, showing all active and enabled events and masking the others. 
                                              The fields are read-write. Writing a 1 to a bit will clear it to 0, that is, clear the IRQ. 
                                              Writing a 0 will have no effect, that is, the register value will not be modified. 
                                              Only enabled, active events will trigger an actual interrupt request on the IRQ output line. 
                                              For all the internal fields of the I2C_IRQSTATUS register, the descriptions given in the I2C_IRQSTATUS_RAW subsection are valid.*/
                                                               
            uint32_t    AL       :1;       // bit: 0       Arbitration lost IRQ enabled status. During reads, it always returns 0. [0h = Normal operation. 1h = Arbitration lost detected]
            uint32_t    NACK     :1;       // bit: 1       No acknowledgment IRQ enabled status. Write '1' to clear this bit. [0h = Normal operation. 1h = Not Acknowledge detected]                                
            uint32_t    ARDY     :1;       // bit: 2       Register access ready IRQ enabled status. [0h = Module busy. 1h = Access ready.]
            uint32_t    RRDY     :1;       // bit: 3       Receive data ready IRQ enabled status. Write '1' to clear. [0h = No data available. 1h = Receive data available.]
            uint32_t    XRDY     :1;       // bit: 4       Transmit data ready IRQ enabled status. [0h = Transmission ongoing. 1h = Transmit data ready.]
            uint32_t    GC       :1;       // bit: 5       General call IRQ enabled status. [0h = No general call detected. 1h = General call address detected.]         
            uint32_t    STC      :1;       // bit: 6       Start Condition IRQ enabled status. [0h = No action. 1h = Start condition detected.]
            uint32_t    AERR     :1;       // bit: 7       Access Error IRQ enabled status. [0h = No action. 1h = Access error.]
            uint32_t    BF       :1;       // bit: 8       Bus Free IRQ enabled status. [0h = No action. 1h = Bus free.] 
            uint32_t    AAS      :1;       // bit: 9       Address recognized as slave IRQ enabled status.[ 0h = No action. 1h = Address recognized.]
            uint32_t    XUDF     :1;       // bit: 10      Transmit underflow enabled status. Writing into this bit has no effect. [0h = Normal operation. 1h = Transmit underflow]
            uint32_t    ROVR     :1;       // bit: 11      Receive overrun enabled status. Writing into this bit has no effect. [0h = Normal operation. 1h = Receiver overrun.]  
            uint32_t    BB       :1;       // bit: 12      Bus busy enabled status. Writing into this bit has no effect. [0h = Bus is free. 1h = Bus is occupied.]
            uint32_t    RDR      :1;       // bit: 13      Receive draining IRQ enabled status. [0h = Receive draining inactive. 1h = Receive draining enabled.]
            uint32_t    XDR      :1;       // bit: 14      Transmit draining IRQ enabled status. [0h = Transmit draining inactive. 1h = Transmit draining enabled.]
            uint32_t             :17;      // bit: 15..31  Reserved
        } b;                               // Structure used for bit access 
        uint32_t  reg;                     // Type used for register access 
    } I2C_IRQSTATUS_reg_t;
    // to mask this register please see --> e_IRQSTATUS_flags <--

    enum e_IRQSTATUS_flags: uint32_t
    {
        F_IRQSTATUS_NONE     = 0u,
        F_IRQSTATUS_AL       = BIT(0),
        F_IRQSTATUS_NACK     = BIT(1),
        F_IRQSTATUS_ARDY     = BIT(2),
        F_IRQSTATUS_RRDY     = BIT(3),
        F_IRQSTATUS_XRDY     = BIT(4),
        F_IRQSTATUS_GC       = BIT(5),
        F_IRQSTATUS_STC      = BIT(6),
        F_IRQSTATUS_AERR     = BIT(7),
        F_IRQSTATUS_BF       = BIT(8),
        F_IRQSTATUS_AAS      = BIT(9),
        F_IRQSTATUS_XUDF     = BIT(10),
        F_IRQSTATUS_ROVR     = BIT(11),
        F_IRQSTATUS_BB       = BIT(12),
        F_IRQSTATUS_RDR      = BIT(13),
        F_IRQSTATUS_XDR      = BIT(14),
        F_IRQSTATUS_ALL      = 0x7FFF
    };
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* All 1-bit fields enable a specific interrupt event to trigger an interrupt request. Writing a 1 to a bit will enable the field. 
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  For all the internal fields of the I2C_IRQENABLE_SET register, the descriptions given in the I2C_IRQSTATUS_RAW subsection are valid.*/
                                                               
            uint32_t    AL_IE       :1;       // bit: 0       Arbitration lost interrupt enable set. [0h = disabled. 1h = enabled.]
            uint32_t    NACK_IE     :1;       // bit: 1       No acknowledgment interrupt enable set. [0h = disabled. 1h = enabled.]                               
            uint32_t    ARDY_IE     :1;       // bit: 2       Register access ready interrupt enable set.  [0h = disabled. 1h = enabled.]
            uint32_t    RRDY_IE     :1;       // bit: 3       Receive data ready interrupt enable set.[ 0h = disabled. 1h = enabled.]
            uint32_t    XRDY_IE     :1;       // bit: 4       Transmit data ready interrupt enable set.  [0h = disabled. 1h =enabled.]
            uint32_t    GC_IE       :1;       // bit: 5       General call interrupt enable set.  [0h = disabled. 1h = enabled.]
            uint32_t    STC_IE      :1;       // bit: 6       Start condition interrupt enable set. [ 0h = disabled. 1h = enabled.]
            uint32_t    AERR_IE     :1;       // bit: 7       Access error interrupt enable set.  [0h = disabled. 1h = enabled.]
            uint32_t    BF_IE       :1;       // bit: 8       Bus free interrupt enable set. [0h =disabled. 1h = enabled.]
            uint32_t    AAS_IE      :1;       // bit: 9       Addressed as slave interrupt enable set. [0h = disabled. 1h = enabled.]
            uint32_t    XUDF        :1;       // bit: 10      Transmit underflow enable set. [0h = disabled. 1h = enabled.]
            uint32_t    ROVR        :1;       // bit: 11      Receive overrun enable set.[ 0h = disabled. 1h = enabled.]
            uint32_t                :1;       // bit: 12      Reserved
            uint32_t    RDR_IE      :1;       // bit: 13      Receive draining interrupt enable set.  [0h = disabled. 1h = enabled.]
            uint32_t    XDR_IE      :1;       // bit: 14      Transmit draining interrupt enable set. [0h = disabled. 1h = enabled.]
            uint32_t                :17;      // bit: 15..31  Reserved
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_IRQENABLE_SET_reg_t;
    // see --> e_IRQENABLE_flags <--

    enum e_IRQENABLE_flags: uint32_t
    {
        F_IRQENABLE_NONE        = 0u,
        F_IRQENABLE_AL_IE       = BIT(0),
        F_IRQENABLE_NACK_IE     = BIT(1),
        F_IRQENABLE_ARDY_IE     = BIT(2),
        F_IRQENABLE_RRDY_IE     = BIT(3),
        F_IRQENABLE_XRDY_IE     = BIT(4),
        F_IRQENABLE_GC_IE       = BIT(5),
        F_IRQENABLE_STC_IE      = BIT(6),
        F_IRQENABLE_AERR_IE     = BIT(7),
        F_IRQENABLE_BF_IE       = BIT(8),
        F_IRQENABLE_AAS_IE      = BIT(9),
        F_IRQENABLE_XUDF_IE     = BIT(10),
        F_IRQENABLE_ROVR_IE     = BIT(11),
        F_IRQENABLE_RDR_IE      = BIT(13),
        F_IRQENABLE_XDR_IE      = BIT(14),
        F_IRQENABLE_ALL         = 0x7FFF
    };
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* All 1-bit fields clear a specific interrupt event. Writing a 1 to a bit will disable the interrupt field. 
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  For all the internal fields of the I2C_IRQENABLE_CLR register, the descriptions given in the I2C_IRQSTATUS_RAW subsection arevalid. */
                                                               
            uint32_t    AL_IE       :1;       // bit: 0       Arbitration lost interrupt enable clear.  [0h = disabled. 1h = enabled.]
            uint32_t    NACK_IE     :1;       // bit: 1       No acknowledgment interrupt enable clear.  [0h = disabled. 1h = enabled.]                                
            uint32_t    ARDY_IE     :1;       // bit: 2       Register access ready interrupt enable clear. [0h = disabled. 1h = enabled.]
            uint32_t    RRDY_IE     :1;       // bit: 3       Receive data ready interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    XRDY_IE     :1;       // bit: 4       Transmit data ready interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    GC_IE       :1;       // bit: 5       General call interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    STC_IE      :1;       // bit: 6       Start condition interrupt enable clear.  [0h = disabled. 1h = enabled.]
            uint32_t    AERR_IE     :1;       // bit: 7       Access error interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    BF_IE       :1;       // bit: 8       Bus free interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    AAS_IE      :1;       // bit: 9       Addressed as slave interrupt enable clear.   [0h = disabled. 1h = enabled.]
            uint32_t    XUDF        :1;       // bit: 10      Transmit underflow enable clear.  [0h = disabled. 1h = enabled.]
            uint32_t    ROVR        :1;       // bit: 11      Receive overrun enable clear.  [0h = disabled. 1h = enabled.]
            uint32_t                :1;       // bit: 12      Reserved
            uint32_t    RDR_IE      :1;       // bit: 13      Receive draining interrupt enable clear.  [0h = disabled. 1h = enabled.]
            uint32_t    XDR_IE      :1;       // bit: 14      Transmit draining interrupt enable clear. [0h = disabled. 1h = enabled.]
            uint32_t                :17;      // bit: 15..31  Reserved
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_IRQENABLE_CLR_reg_t;
    // see --> e_IRQENABLE_flags <--
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* Every 1-bit field in the I2C_WE register enables a specific (synchronous) IRQ request source to generate an asynchronous wakeup (on the appropriate swakeup line). 
                                                  When a bit location is set to 1 by the local host, a wakeup is signaled to the local host if the corresponding event is captured by the core of the I2C controller. 
                                                  Value after reset is low (all bits).
                                                  There is no need for an Access Error WakeUp event, since this event occurs only when the module is in Active Mode (for Interface/OCP accesses to FIFO) and is signaled by an interrupt. 
                                                  With the exception of Start Condition WakeUp, which is asynchronously detected when the Functional clock is turned-off, all the other WakeUp events require the Functional (System) clock to be enabled. */
                                                               
            uint32_t    AL_WE       :1;       // bit: 0       Arbitration lost IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    NACK_WE     :1;       // bit: 1       No acknowledgment IRQ wakeup enable. [0h = disabled. 1h = enabled.]                                
            uint32_t    ARDY_WE     :1;       // bit: 2       Register access ready IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    RRDY_WE     :1;       // bit: 3       Receive/Transmit data ready IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t                :1;       // bit: 4       Reserved
            uint32_t    GC_WE       :1;       // bit: 5       General call IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    STC_WE      :1;       // bit: 6       Start condition IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t                :1;       // bit: 7       Reserved
            uint32_t    BF_WE       :1;       // bit: 8       Bus free IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    AAS_WE      :1;       // bit: 9       Address as slave IRQ wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    XUDF_WE     :1;       // bit: 10      Transmit underflow wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    ROVR_WE     :1;       // bit: 11      Receive overrun wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t                :1;       // bit: 12      Reserved
            uint32_t    RDR_WE      :1;       // bit: 13      Receive draining wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t    XDR_WE      :1;       // bit: 14      Transmit draining wakeup enable. [0h = disabled. 1h = enabled.]
            uint32_t                :17;      // bit: 15..31  Reserved
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_WE_reg_t;
    // see --> e_WE_flags <--
    
    enum e_WE_flags: uint32_t
    {
        F_WE_NONE        = 0u,
        F_WE_AL_WE       = BIT(0),
        F_WE_NACK_WE     = BIT(1),
        F_WE_ARDY_WE     = BIT(2),
        F_WE_RRDY_WE     = BIT(3),
        F_WE_GC_WE       = BIT(5),
        F_WE_STC_WE      = BIT(6),
        F_WE_BF_WE       = BIT(8),
        F_WE_AAS_WE      = BIT(9),
        F_WE_XUDF_WE     = BIT(10),
        F_WE_ROVR_WE     = BIT(11),
        F_WE_RDR_WE      = BIT(13),
        F_WE_XDR_WE      = BIT(14),
        F_WE_ALL         = 0x7FFF
    };

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* The 1-bit field enables a receive DMA request. Writing a 1 to this field will set it to 1. 
                                                  Writing a 0 will have no effect, that is, the register value is not modified.
                                                  Note that the I2C_BUF.RDMA_EN field is the global (slave) DMA enabler, and that it is disabled by default. 
                                                  The I2C_BUF.RDMA_EN field should also be set to 1 to enable a receive DMA request. */
                                                               
            uint32_t    DMARX_ENABLE_SET    :1;     // bit: 0  Receive DMA channel enable set.                        
            uint32_t                        :31;    // bit: 1..31  Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } I2C_DMARXENABLE_SET_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* The 1-bit field enables a transmit DMA request. Writing a 1 to this field will set it to 1. 
                                                  Writing a 0 will have no effect, that is, the register value is not modified.
                                                  Note that the I2C_BUF.XDMA_EN field is the global (slave) DMA enabler, and that it is disabled by default. 
                                                  The I2C_BUF.XDMA_EN field should also be set to 1 to enable a transmit DMA request. */
                                                               
            uint32_t   DMATX_TRANSMIT_SET    :1;    // bit: 0  Transmit DMA channel enable set.                       
            uint32_t                         :31;   // bit: 1..31  Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } I2C_DMATXENABLE_SET_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* The 1-bit field disables a receive DMA request. 
                                                  Writing a 1 to a bit will clear it to 0. 
                                                  Another result of setting to 1 the DMARX_ENABLE_CLEAR field, is the reset of the DMA RX request and wakeup lines.
                                                  Writing a 0 will have no effect, that is, the register value is not modified. */
                                                               
            uint32_t   DMARX_ENABLE_CLEAR   :1;     // bit: 0  Receive DMA channel enable clear.                       
            uint32_t                        :31;    // bit: 1..31  Reserved  
        } b;                                        // Structure used for bit access 
        uint32_t  reg;                              // Type used for register access 
    } I2C_DMARXENABLE_CLR_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* The 1-bit field disables a transmit DMA request. 
                                                  Writing a 1 to a bit will clear it to 0. 
                                                  Another result of setting to 1 the DMATX_ENABLE_CLEAR field, is the reset of the DMA TX request and wakeup lines.
                                                  Writing a 0 will have no effect, that is, the register value is not modified. */
                                                               
            uint32_t   DMATX_ENABLE_CLEAR   :1;           // bit: 0  Receive DMA channel enable clear.                       
            uint32_t                        :31;          // bit: 1..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_DMATXENABLE_CLR_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* All 1-bit fields enable a specific (synchronous) DMA request source to generate an asynchronous wakeup (on the appropriate swakeup line).
                                                  Note that the I2C_SYSC.ENAWAKEUP field is the global (slave) wakeup enabler, and that it is disabled by default. */
                                                               
            uint32_t    AL       :1;       // bit: 0       Arbitration lost IRQ wakeup set. 0h = Arbitration lost wakeup disabled. 1h = Arbitration lost wakeup enabled.
            uint32_t    NACK     :1;       // bit: 1       No acknowledgment IRQ wakeup set. [0h = disabled. 1h = enabled.]                               
            uint32_t    ARDY     :1;       // bit: 2       Register access ready IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    RRDY     :1;       // bit: 3       Receive/Transmit data ready IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t             :1;       // bit: 4       Reserved
            uint32_t    GC       :1;       // bit: 5       General call IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    STC      :1;       // bit: 6       Start condition IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t             :1;       // bit: 7       Reserved
            uint32_t    BF       :1;       // bit: 8       Bus free IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    AAS      :1;       // bit: 9       Address as slave IRQ wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    XUDF     :1;       // bit: 10      Transmit underflow wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    ROVR     :1;       // bit: 11      Receive overrun wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t             :1;       // bit: 12      Reserved
            uint32_t    RDR      :1;       // bit: 13      Receive draining wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t    XDR      :1;       // bit: 14      Transmit draining wakeup set. [0h = disabled. 1h = enabled.]
            uint32_t             :17;      // bit: 15..31  Reserved
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_DMARXWAKE_EN_reg_t;
    // see --> e_WE_flags <--
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* All 1-bit fields enable a specific (synchronous) DMA request source to generate an asynchronous wakeup (on the appropriate swakeup line).
                                                  Note that the I2C_SYSC.ENAWAKEUP field is the global (slave) wakeup enabler, and that it is disabled by default. */
                                                               
            uint32_t    AL       :1;       // bit: 0       Arbitration lost IRQ wakeup set. 0h = Arbitration lost wakeup disabled. 1h = Arbitration lost wakeup enabled.
            uint32_t    NACK     :1;       // bit: 1       No acknowledgment IRQ wakeup set. 0h = Not Acknowledge wakeup disabled. 1h = Not Acknowledge wakeup enabled.                                
            uint32_t    ARDY     :1;       // bit: 2       Register access ready IRQ wakeup set. 0h = Register access ready wakeup disabled. 1h = Register access ready wakeup enabled.
            uint32_t    RRDY     :1;       // bit: 3       Receive/Transmit data ready IRQ wakeup set. 0h = Receive data ready wakeup disabled. 1h = Receive data ready wakeup enabled.
            uint32_t             :1;       // bit: 4       Reserved
            uint32_t    GC       :1;       // bit: 5       General call IRQ wakeup set. 0h = General call wakeup disabled. 1h = General call wakeup enabled.
            uint32_t    STC      :1;       // bit: 6       Start condition IRQ wakeup set. 0h = Start condition wakeup disabled. 1h = Start condition wakeup enabled.
            uint32_t             :1;       // bit: 7       Reserved
            uint32_t    BF       :1;       // bit: 8       Bus free IRQ wakeup set. 0h = Bus free wakeup disabled. 1h = Bus free wakeup enabled.
            uint32_t    AAS      :1;       // bit: 9       Address as slave IRQ wakeup set. 0h = Addressed as slave wakeup disabled. 1h = Addressed as slave wakeup enabled.
            uint32_t    XUDF     :1;       // bit: 10      Transmit underflow wakeup set. 0h = Transmit underflow wakeup disabled. 1h = Transmit underflow wakeup enabled.
            uint32_t    ROVR     :1;       // bit: 11      Receive overrun wakeup set. 0h = Receive overrun wakeup disabled. 1h = Receive draining wakeup enabled.
            uint32_t             :1;       // bit: 12      Reserved
            uint32_t    RDR      :1;       // bit: 13      Receive draining wakeup set. 0h = Receive draining wakeup disabled. 1h = Receive draining wakeup enabled.
            uint32_t    XDR      :1;       // bit: 14      Transmit draining wakeup set. 0h = Transmit draining wakeup disabled. 1h = Transmit draining wakeup enabled.
            uint32_t             :17;      // bit: 15..31  Reserved
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_DMATXWAKE_EN_reg_t;
    // see --> e_WE_flags <--
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                   /* I2C_SYSS Register */
                                                               
            uint32_t   RDONE     :1;        // bit: 0  Reset done bit[.0h = Internal module reset in ongoing. 1h = Reset completed.]
            uint32_t             :31;       // bit: 1..31  Reserved  
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } I2C_SYSS_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This read/write register enables DMA transfers and allows the configuration of FIFO thresholds for the FIFO management 
                                                  (see the FIFO Management subsection). */
                                                               
            uint32_t    TXTRSH        :6;         // bit: 0..5    (RW)Threshold value for FIFO buffer in TX mode. [see e_BUF_TRSH_flags]
            uint32_t    TXFIFO_CLR    :1;         // bit: 6       Transmit FIFO clear. [0h = Normal mode. 1h = Tx FIFO is reset.]                                
            uint32_t    XDMA_EN       :1;         // bit: 7       Transmit DMA channel enable. [0h = disabled. 1h = enabled.]   
            uint32_t    RXTRSH        :6;         // bit: 8..13   Threshold value for FIFO buffer in RX mode. [see e_BUF_TRSH_flags]
            uint32_t    RXFIFO_CLR    :1;         // bit: 14      Receive FIFO clear. [0h = Normal mode. 1h = Tx FIFO is reset.]
            uint32_t    RDMA_EN       :1;         // bit: 15      Receive DMA channel enable. [0h = disabled. 1h = enabled.]
            uint32_t                  :16;        // bit: 16..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_BUF_reg_t;
    
    enum e_BUF_TRSH_flags : uint32_t
    {
        BUF_TRSH_1  = 0x0,
        BUF_TRSH_2  = 0x1,
        BUF_TRSH_64 = 0x3F        
    };
    
    /* [reset state = 0x0]*/
     typedef union 
    { 
        struct 
        {                                    /* CAUTION: During an active transfer phase (between STT having been set to 1 and reception of ARDY),
                                                  no modification must be done in this register. Changing it may result in an unpredictable behavior. 
                                                  This read/write register is used to control the numbers of bytes in the I2C data payload. */
                                                               
            uint32_t   DCOUNT     :16;       // bit: 0..15   Data count. [0h = Data counter = 65536 bytes (216). 1h = Data counter = 1 bytes. FFFFh = Data counter = 65535 bytes (216 - 1).]
            uint32_t              :16;       // bit: 16..31  Reserved  
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } I2C_CNT_reg_t;
    
    /* [reset state = 0x0]*/
     typedef union 
    { 
        struct 
        {                                   /* This register is the entry point for the local host to read data from or write data to the FIFO buffer. */
                                            /* Transmit/Receive data FIFO endpoint.
                                               When read, this register contains the received I2C data.
                                               When written, this register contains the byte value to transmit over
                                               the I2C data.
                                               In SYSTEST loop back mode (I2C_SYSTEST: TMODE = 11), this
                                               register is also the entry/receive point for the data.
                                               Values after reset are unknown (all
                                               8-bits). */
                                                               
            uint32_t   DATA     :8;         // bit: 0..7   Transmit/Receive data FIFO endpoint.
            uint32_t            :24;        // bit: 8..31  Reserved  
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } I2C_DATA_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* During an active transfer phase (between STT having been set to 1 and reception of ARDY), 
                                                  no modification must be done in this register (except STP enable). 
                                                  Changing it may result in an unpredictable behavior. */
                                                /* Note: DCOUNT is data count value in I2C_CNT register.
                                                   STT = 1, STP = 0, Conditions = Start, Bus Activities = S-A-D.
                                                   STT = 0, STP = 1, Conditions = Stop, Bus Activities = P.
                                                   STT = 1, STP = 1, Conditions = Start-Stop (DCOUNT=n), Bus
                                                   Activities = S-A-D..(n)..D-P.
                                                   STT = 1, STP = 0, Conditions = Start (DCOUNT=n), Bus Activities =
                                                   S-A-D..(n)..D. */
                                                               
            uint32_t    STT         :1;         // bit: 0      (RW) Start condition (I2C master mode only).[0h = No action or start condition detected. 1h = Start condition queried]
            uint32_t    STP         :1;         // bit: 1      (RW) Stop condition (I2C master mode only). [0h = No action or Stop condition detected. 1h = Stop condition queried]   
            uint32_t                :2;         // bit: 2,3     Reserved   
            uint32_t    XOA3        :1;         // bit: 4      (RW) Expand own address 3. [0h = 7-bit address mode. 1h = 10-bit address mode]
            uint32_t    XOA2        :1;         // bit: 5      (RW) Expand own address 2.(I2C mode only). [0h = 7-bit address mode (I2C mode only). 1h = 10-bit address mode]
            uint32_t    XOA1        :1;         // bit: 6      (RW) Expand own address 1.(I2C mode only). [0h = 7-bit address mode. 1h = 10-bit address mode]
            uint32_t    XOA0        :1;         // bit: 7      (RW) Expand own address 0.(I2C mode only). [0h = 7-bit address mode. 1h = 10-bit address mode]
            uint32_t    XSA         :1;         // bit: 8      (RW) Expand slave address.(I2C mode only). [0h = 7-bit address mode. 1h = 10-bit address mode]
            uint32_t    TRX         :1;         // bit: 9      (RW) Transmitter/receiver mode (i2C master mode only). [0h = Receiver mode. 1h = Transmitter mode]
            uint32_t    MST         :1;         // bit: 10     (RW) Master/slave mode (I2C mode only). [0h = Slave mode. 1h = Master mode]
            uint32_t    STB         :1;         // bit: 11     (RW) Start byte mode (I2C master mode only). [0h = Normal mode. 1h = Start byte mode]
            uint32_t    OPMODE      :2;         // bit: 12,13  (RW) Operation mode selection. [0h = I2C Fast/Standard mode 1h,2h,3h = Reserved]
            uint32_t                :1;         // bit: 14      Reserved
            uint32_t    I2C_EN      :1;         // bit: 15     (RW) I2C module enable. [0h = Controller in reset. FIFO are cleared and status bits are set to their default value. 1h = Module enabled]
            uint32_t                :16;        // bit: 16..31 Reserved 
        } b;                                    // Structure used for bit access
        uint32_t  reg;                          // Type used for register access
    } I2C_CON_reg_t;

    enum e_CON_flags: uint32_t
    {
        F_CON_NONE      =   0,
        F_CON_STT       =   BIT(0),
        F_CON_STP       =   BIT(1),
        F_CON_XOA3      =   BIT(4),
        F_CON_XOA2      =   BIT(5),
        F_CON_XOA1      =   BIT(6),
        F_CON_XOA0      =   BIT(7),
        F_CON_XSA       =   BIT(8),
        F_CON_TRX       =   BIT(9),
        F_CON_MST       =   BIT(10),
        F_CON_STB       =   BIT(11), 
        F_CON_OPMODE    =   BIT(12),         
        F_CON_I2C_EN    =   BIT(15),
        F_CON_ALL       =   0xFFFF
    };   
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active transfer phase (between STT having been set to 1 and reception of ARDY),
                                                  no modification must be done in this register. Changing it may result in an unpredictable behavior.
                                                  This register is used to specify the module s base I2C 7-bit or 10-bit address (base own address).*/
                                                               
            uint32_t    OA      :10;        // bit: 0..9      (RW) Own address.
            uint32_t            :22;        // bit: 10..31    Reserved  
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } I2C_OA_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active transfer phase (between STT having been set to 1 and reception of ARDY),
                                                  no modification must be done in this register. Changing it may result in an unpredictable behavior.
                                                  This register is used to specify the addressed I2C module 7-bit or 10-bit address (slave address).*/
                                                               
            uint32_t    SA      :10;        // bit: 0..9      (RW) Slave address.
            uint32_t            :22;        // bit: 10..31    Reserved  
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } I2C_SA_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active mode (I2C_EN bit in I2C_CON register is set to 1), 
                                                  no modification must be done in this register. Changing it may result in an unpredictable behavior. 
                                                  This register is used to specify the internal clocking of the I2C peripheral core. */
                                                               
            uint32_t    PSC      :8;         // bit: 0..7       (RW) Fast/Standard mode prescale sampling clock divider value. [0h = Divide by 1. 1h = Divide by 2. FFh = Divide by 256.]
            uint32_t             :22;        // bit: 8..31      Reserved  
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } I2C_PSC_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active mode (I2C_EN bit in I2C_CON register is set to 1), no modification must be done in this register. 
                                                  Changing it may result in an unpredictable behavior. 
                                                  This register is used to determine the SCL low time value when master. */
                                               /* This 8-bit value is used to generate the SCL low time value (tLOW) when
                                                  the peripheral is operated in master mode. tLOW = (SCLL + 7) * ICLK time period, 
                                                  Value after reset is low (all 8 bits).*/
                                                               
            uint32_t    SCLL      :8;         // bit: 0..7       (RW) Fast/Standard mode SCL low time.
            uint32_t              :22;        // bit: 8..31      Reserved  
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } I2C_SCLL_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active mode (I2C_EN bit in I2C_CON register is set to 1),
                                                  no modification must be done in this register.
                                                  Changing it may result in an unpredictable behavior. 
                                                  This register is used to determine the SCL high time value when master. */
                                               /* This 8-bit value is used to generate the SCL high time value (tHIGH)
                                                  when the peripheral is operated in master mode.
                                                  - tHIGH = (SCLH + 5) * ICLK time period.
                                                  Value after reset is low (all 8 bits).*/
                                                               
            uint32_t    SCLH      :8;         // bit: 0..7       (RW) Fast/Standard mode SCL low time.
            uint32_t              :22;        // bit: 8..31      Reserved  
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } I2C_SCLH_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: Never enable this register for normal I2C operation. 
                                                  This register is used to facilitate system-level tests by overriding some of the standard functional features of the peripheral. 
                                                  It allows testing of SCL counters, controlling the signals that connect to I/O pins, or creating digital loop-back for self-test when the module is configured in system test (SYSTEST) mode. 
                                                  It also provides stop/non-stop functionality in the debug mode. */
                                                               
            uint32_t    SDA_O         :1;         // bit: 0      (R) SDA line drive output value. [0h = Write 0 to SDA line. 1h = Write 1 to SDA line]
            uint32_t    SDA_I         :1;         // bit: 1      (R) SDA line sense input value. [0h (R) = Read 0 to SDA line. 1h (R) = Read 1 to SDA line]  
            uint32_t    SCL_O         :1;         // bit: 2      (R) SCL line drive output value. [0h (R) = Forces 0 on the SCL data line. 1h (R) = SCL output driver in high-impedance state]
            uint32_t    SCL_I         :1;         // bit: 3      (R) SCL line sense input value. [0h (R) = Read 0 from SCL line. 1h (R) = Read 1 from SCL line]
            uint32_t                  :1;         // bit: 4      Reserved
            uint32_t    SDA_O_FUNC    :1;         // bit: 5      (R) SDA line output value (functional mode). [0h (R) = Driven 0 to SDA line. 1h (R) = Driven 1 to SDA line]
            uint32_t    SDA_I_FUNC    :1;         // bit: 6      (R) SDA line input value (functional mode). [0h (R) = Read 0 from SDA line. 1h (R) = Read 1 from SDA line]
            uint32_t    SCL_O_FUNC    :1;         // bit: 7      (R) SCL line output value (functional mode). [0h (R) = Driven 0 on SCL line. 1h (R) = Driven 1 on SCL line]
            uint32_t    SCL_I_FUNC    :1;         // bit: 8      (R) SCL line input value (functional mode). [0h (R) = Driven 0 from SCL line. 1h (R) = Driven 1 from SCL line]
            uint32_t                  :2;         // bit: 9,10   Reserved
            uint32_t    SSB           :1;         // bit: 11     (RW) Set status bits. [0h = No action. 1h = Set all interrupt status bits to 1.]
            uint32_t    TMODE         :2;         // bit: 12,13  (RW) Test mode select. (see enum e_SYSTEST_TMODE)
            uint32_t    FREE          :1;         // bit: 14     (RW) Free running mode (on breakpoint).[0h = Stop mode (on breakpoint condition). 1h = Free running mode.]
            uint32_t    ST_EN         :1;         // bit: 15     (RW) System test enable. [0h = Normal mode. All others bits in register are read only.]
            uint32_t                  :16;        // bit: 16..31 Reserved                [1h = System test enabled. Permit other system test registers bits to be set.]

        } b;                                      // Structure used for bit access
        uint32_t  reg;                            // Type used for register access
    } I2C_SYSTEST_reg_t;
    
    enum e_SYSTEST_TMODE : uint32_t
    {
        FUNCTIONAL_MODE = 0x0,
        RESERVED        = 0x1,
        TEST_OF_SCL     = 0x2,
        LOOP_BACK_MODE  = 0x3       
    };
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This read-only register reflects the status of the internal buffers for the FIFO management 
                                                  (see the FIFO Management subsection). */
                                                               
            uint32_t    TXSTAT        :6;         // bit: 0..5     (R)TX buffer status. This read-only field indicates the number of data bytes still left to be written Value after reset is equal with 0.
            uint32_t                  :2;         // bit: 6,7       Reserved                       
            uint32_t    RXSTAT        :6;         // bit: 8..13    (R)RX buffer status. This read-only field indicates the number of bytes to be transferred. Value after reset is 0.      
            uint32_t    FIFODEPTH     :2;         // bit: 14,15    (R)Internal FIFO buffers depth. (lock enum e_BUFSTAT_FIFODEPTH)
            uint32_t                  :16;        // bit: 16..31    Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_BUFSTAT_reg_t;

    enum e_I2C_buffer_status : uint32_t
    {
        BUFSTAT_TXSTAT    = 0x0,
        BUFSTAT_RXSTAT    = 0x1,
        BUFSTAT_FIFODEPTH = 0x2
    };
    
    enum e_BUFSTAT_FIFODEPTH : uint32_t
    {
        FIFO_8  = 0x0,
        FIFO_16 = 0x1,
        FIFO_32 = 0x2,
        FIFO_64 = 0x3
    };
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active transfer phase (between STT has been set to 1 and receiving of ARDY), 
                                                  no modification must be done in this register.
                                                  Changing it may result in an unpredictable behavior. 
                                                  This register is used to specify the first alternative I2C 7-bit or 10-bit address (own address 1 - OA1). */
                                                               
            uint32_t     OA1      :10;        // bit: 0..9       (RW) Own address 1. Value after reset is low (all 10 bits).
                                                                /*  This field specifies either: A
                                                                    10-bit address coded on OA1
                                                                    [9:0] when XOA1 (Expand Own Address
                                                                    1 - XOA1, I2C_CON[6]) is set to 1.
                                                                    A
                                                                    7-bit address coded on OA1
                                                                    [6:0] when XOA1 (Expand Own Address 1 XOA1, I2C_CON[6]) is
                                                                    cleared to 0.
                                                                    In this case, OA1
                                                                    [9:7] bits must be cleared to 000 by application software.
                                                                    Value after reset is low (all 10 bits).*/
            uint32_t              :22;        // bit: 10..31     Reserved  
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_OA1_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active transfer phase (between STT has been set to 1 and receiving of ARDY), 
                                                  no modification must be done in this register.
                                                  Changing it may result in an unpredictable behavior. 
                                                  This register is used to specify the first alternative I2C 7-bit or 10-bit address (own address 2 - OA2). */
                                                               
            uint32_t     OA1      :10;        // bit: 0..9       (RW) Own address 2. Value after reset is low (all 10 bits).
                                                                  /*This field specifies either: A
                                                                    10-bit address coded on OA2
                                                                    [9:0] when XOA1 (Expand Own Address
                                                                    2 - XOA2, I2C_CON[5]) is set to 1.
                                                                    A
                                                                    7-bit address coded on OA2
                                                                    [6:0] when XOA2 (Expand Own Address 2 XOA2, I2C_CON[5]) is
                                                                    cleared to 0.
                                                                    In this case, OA2
                                                                    [9:7] bits must be cleared to 000 by application software.
                                                                    Value after reset is low (all 10 bits).*/
            uint32_t              :22;        // bit: 10..31      Reserved  
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_OA2_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* CAUTION: During an active transfer phase (between STT has been set to 1 and receiving of ARDY), 
                                                  no modification must be done in this register.
                                                  Changing it may result in an unpredictable behavior. 
                                                  This register is used to specify the first alternative I2C 7-bit or 10-bit address (own address 3 - OA3). */
                                                               
            uint32_t     OA1      :10;        // bit: 0..9       (RW) Own address 3. Value after reset is low (all 10 bits).
                                                                 /* This field specifies either: A
                                                                    10-bit address coded on OA3
                                                                    [9:0] when XOA3 (Expand Own Address
                                                                    3 - XOA3, I2C_CON[4]) is set to 1.
                                                                    A
                                                                    7-bit address coded on OA3
                                                                    [6:0] when XOA1 (Expand Own Address 3 XOA3, I2C_CON[4]) is
                                                                    cleared to 0.
                                                                    In this case, OA3
                                                                    [9:7] bits must be cleared to 000 by application */
            uint32_t              :22;        // bit: 10..31      Reserved  
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_OA3_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This read-only register is used to indicate which one of the module s four own addresses the external
                                                  master used when addressing the module. 
                                                  The CPU can read this register when the AAS indication was activated. 
                                                  The indication is cleared at the end of the transfer. */
                                                               
            uint32_t    OA0_ACT        :1;         // bit: 0      (R) Own address 0 active. [0h = inactive. 1h = active.]
            uint32_t    OA1_ACT        :1;         // bit: 1      (R) Own address 1 active. [0h = inactive. 1h = active.]                      
            uint32_t    OA2_ACT        :1;         // bit: 2      (R) Own address 2 active. [0h = inactive. 1h = active.]     
            uint32_t    OA3_ACT        :1;         // bit: 3      (R) Own address 3 active. [0h = inactive. 1h = active.]
            uint32_t                  :28;         // bit: 4..31   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_ACTOA_reg_t;
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This read/write register controls the automatic blocking of I2C clock feature in slave mode. 
                                                  It is used for the Local Host to configure for which of the 4 own addresses, 
                                                  the core must block the I2C clock (keep SCL line low) right after the Address Phase, when it is addressed as a slave. */
             
            uint32_t    OA0_EN        :1;         // bit: 0      (RW) Enable I2C clock blocking for own address 0. [0h = I2C clock released. 1h = I2C clock blocked.]
            uint32_t    OA1_EN        :1;         // bit: 1      (RW) Enable I2C clock blocking for own address 1. [0h = I2C clock released. 1h = I2C clock blocked.]                      
            uint32_t    OA2_EN        :1;         // bit: 2      (RW) Enable I2C clock blocking for own address 2. [0h = I2C clock released. 1h = I2C clock blocked.]     
            uint32_t    OA3_EN        :1;         // bit: 3      (RW) Enable I2C clock blocking for own address 3. [0h = I2C clock released. 1h = I2C clock blocked.]
            uint32_t                  :28;        // bit: 4..31   Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } I2C_SBLOCK_reg_t;

    enum e_OWN_ADDRESS_flags: uint32_t
    {
       
        F_OA0 = BIT(0),
        F_OA1 = BIT(1),
        F_OA2 = BIT(2),
        F_OA3 = BIT(3)
    };   
    
    typedef struct  
    {                                                                                      
        __R   I2C_REVNB_LO_reg_t                I2C_REVNB_LO;            // (0x00)  Module Revision Register (low bytes) 
        __R   I2C_REVNB_HI_reg_t                I2C_REVNB_HI;            // (0x04)  Module Revision Register (high bytes) 
        __R   uint32_t                          RESERVED1[2];
        __RW  I2C_SYSC_reg_t                    I2C_SYSC;                // (0x10)  System Configuration Register
        __R   uint32_t                          RESERVED2[4];
        __RW  I2C_IRQSTATUS_RAW_reg_t           I2C_IRQSTATUS_RAW;       // (0x24)  2C Status Raw Register
        __RW  I2C_IRQSTATUS_reg_t               I2C_IRQSTATUS;           // (0x28)  I2C Status Register
        __RW  I2C_IRQENABLE_SET_reg_t           I2C_IRQENABLE_SET;       // (0x2C)  I2C Interrupt Enable Set Register
        __RW  I2C_IRQENABLE_CLR_reg_t           I2C_IRQENABLE_CLR;       // (0x30)  I2C Interrupt Enable Clear Register
        __RW  I2C_WE_reg_t                      I2C_WE;                  // (0x34)  I2C Wakeup Enable Register
        __RW  I2C_DMARXENABLE_SET_reg_t         I2C_DMARXENABLE_SET;     // (0x38)  Receive DMA Enable Set Register
        __RW  I2C_DMATXENABLE_SET_reg_t         I2C_DMATXENABLE_SET;     // (0x3C)  Transmit DMA Enable Set Register
        __RW  I2C_DMARXENABLE_CLR_reg_t         I2C_DMARXENABLE_CLR;     // (0x40)  Receive DMA Enable Clear Register
        __RW  I2C_DMATXENABLE_CLR_reg_t         I2C_DMATXENABLE_CLR;     // (0x44)  Transmit DMA Enable Clear Register
        __RW  I2C_DMARXWAKE_EN_reg_t            I2C_DMARXWAKE_EN;        // (0x48)  Receive DMA Wakeup Register
        __RW  I2C_DMATXWAKE_EN_reg_t            I2C_DMATXWAKE_EN;        // (0x4C)  Transmit DMA Wakeup Register
        __R   uint32_t                          RESERVED3[16];
        __RW  I2C_SYSS_reg_t                    I2C_SYSS;                // (0x90)  System Status Register
        __RW  I2C_BUF_reg_t                     I2C_BUF;                 // (0x94)  Buffer Configuration Register
        __RW  I2C_CNT_reg_t                     I2C_CNT;                 // (0x98)  Data Counter Register    
        __RW  I2C_DATA_reg_t                    I2C_DATA;                // (0x9C)  Data Access Register
        __R   uint32_t                          RESERVED4[1];
        __RW  I2C_CON_reg_t                     I2C_CON;                 // (0xA4)  I2C Configuration Register
        __RW  I2C_OA_reg_t                      I2C_OA;                  // (0xA8)  I2C Own Address Register
        __RW  I2C_SA_reg_t                      I2C_SA;                  // (0xAC)  I2C Slave Address Register
        __RW  I2C_PSC_reg_t                     I2C_PSC;                 // (0xB0)  I2C Clock Prescaler Register
        __RW  I2C_SCLL_reg_t                    I2C_SCLL;                // (0xB4)  I2C SCL Low Time Register
        __RW  I2C_SCLH_reg_t                    I2C_SCLH;                // (0xB8)  I2C SCL High Time Register
        __RW  I2C_SYSTEST_reg_t                 I2C_SYSTEST;             // (0xBC)  System Test Register
        __R   I2C_BUFSTAT_reg_t                 I2C_BUFSTAT;             // (0xC0)  I2C Buffer Status Register
        __RW  I2C_OA1_reg_t                     I2C_OA1;                 // (0xC4)  I2C Own Address 1 Register
        __RW  I2C_OA2_reg_t                     I2C_OA2;                 // (0xC8)  I2C Own Address 2 Register
        __RW  I2C_OA3_reg_t                     I2C_OA3;                 // (0xCC)  I2C Own Address 3 Register
        __R   I2C_ACTOA_reg_t                   I2C_ACTOA;               // (0xD0)  Active Own Address Register
        __RW  I2C_SBLOCK_reg_t                  I2C_SBLOCK;              // (0xD4)  I2C Clock Blocking Enable Register
    } AM335x_I2C_Type;
    
    enum e_I2C_MODE : uint32_t
    {
        I2C_RX_MODE = 0x0,
        I2C_TX_MODE = 0x1
    };

    enum e_I2C_WAKE_UP : uint32_t
    {
        I2C_WAKE_UP_IRQ                = 0x0,
        I2C_WAKE_UP_DMA_RECV           = 0x1,
        I2C_WAKE_UP_DMA_TRANSMIT       = 0x2
    };
    
    enum e_I2C_SER_NUM : uint8_t
    {   
        I2C_NUM_NA  = 0x0,
        I2C_NUM_0   = 0x1,
        I2C_NUM_1   = 0x2,
        I2C_NUM_2   = 0x3                      
    };
    
    enum e_CLK_FREQUENCY : uint32_t
    {
        F_100KHz = 100000,
        F_250KHz = 250000,
        F_400KHz = 400000
    };

    constexpr uint32_t AM335x_I2C_0_BASE     = 0x44E0B000;    
    constexpr uint32_t AM335x_I2C_1_BASE     = 0x4802A000;    
    constexpr uint32_t AM335x_I2C_2_BASE     = 0x4819C000;  
     
    constexpr AM335x_I2C_Type * AM335X_I2C_0 = ((AM335x_I2C_Type *) AM335x_I2C_0_BASE); 
    constexpr AM335x_I2C_Type * AM335X_I2C_1 = ((AM335x_I2C_Type *) AM335x_I2C_1_BASE); 
    constexpr AM335x_I2C_Type * AM335X_I2C_2 = ((AM335x_I2C_Type *) AM335x_I2C_2_BASE);
        
}
        
class HS_I2C
{
public:
                       typedef struct i2cContext 
                       {
                            uint32_t prescalar;
                            uint32_t lowdivider;
                            uint32_t highdivider;
                            uint32_t ownaddr;
                       }I2CCONTEXT;
                    
                        HS_I2C(I2C::AM335x_I2C_Type *p_i2c_regs);
                       ~HS_I2C() {};

                  /** i2c initial setup methods **/
                  void  master_enable();              
                  void  master_disable();
                  void  auto_idle_enable();
                  void  auto_idle_disable();
                  void  master_init_exp_clk(uint32_t sys_clk, uint32_t internal_clk, uint32_t output_clk);
                  void  master_slave_addr_set(uint16_t slave_add);
    I2C::e_I2C_SER_NUM  get_I2C_ser_number();
 INTC::e_SYS_INTERRUPT  get_I2C_sys_interrupt();                  
                  
                  /** i2c transaction management methods **/
                  void  master_control(uint32_t cmd);   // see I2C::e_CON_flags
                  void  set_data_count(uint16_t count);
              uint16_t  data_count_get();
                  void  master_data_put(uint8_t data);
               uint8_t  master_data_get();
                  bool  master_bus_busy();
                  bool  master_nack_status();
              uint32_t  master_int_raw_status();
                  void  master_stop();
                  void  master_start();
                  void  master_int_enable_ex(uint32_t int_flag);  // see e_IRQENABLE_flags
                  void  master_int_clear_ex(uint32_t int_flag);   // see e_IRQSTATUS_flags
                  void  master_int_disable_ex(uint32_t int_flag); // see e_IRQENABLE_flags

                  /** not frequently used methods! **/
                  void  soft_reset();
                  void  DMATx_event_enable();
                  void  DMARx_event_enable();
                  void  DMATx_event_disable();
                  void  DMARx_event_disable();                 
              uint32_t  master_err();           // check by I2C::e_IRQSTATUS_flags
                  void  global_wake_up_enable();             
                  void  global_wake_up_disable(); 
              uint32_t  master_busy();
              uint32_t  master_int_status();    //check by I2C::e_IRQSTATUS_flags  
                  bool  system_status_get();
              uint32_t  active_own_address_get();
                  void  FIFO_clear(I2C::e_I2C_MODE flag);
                  void  slave_data_put(uint32_t data); 
                  void  idle_mode_select(I2C::e_SYSC_IDLEMODE flag);
                  void  wake_up_enable(I2C::e_WE_flags event_flag, I2C::e_I2C_WAKE_UP flag);
                  void  wake_up_disable(I2C::e_WE_flags event_flag, I2C::e_I2C_WAKE_UP flag);
                  void  own_address_set(uint32_t slave_add, I2C::e_OWN_ADDRESS_flags flag);
                  void  clock_activity_select(I2C::e_SYSC_CLKACTIVITY flag);
              uint32_t  buffer_status(I2C::e_I2C_buffer_status flag);
                  void  FIFO_threshold_config(I2C::e_BUF_TRSH_flags threshlod_val, I2C::e_I2C_MODE flag);
                  void  master_int_raw_status_clear_ex(I2C::e_IRQSTATUS_flags int_flag);
              uint32_t  master_int_status_ex(I2C::e_IRQSTATUS_flags int_flag);
              uint16_t  master_slave_addr_get(uint32_t slave_add);
              uint32_t  master_int_raw_status_ex(I2C::e_IRQSTATUS_flags int_flag);
                  void  clock_blocking_control(bool ownAdd0, bool ownAdd1, bool ownAdd2, bool ownAdd3);
                  void  context_save(I2CCONTEXT *contextPtr);
                  void  context_restore(I2CCONTEXT *contextPtr);

            /** not existing methods, but desired! **/
            //uint32_t  slave_data_get();
            //uint32_t  slave_int_status();
            //uint32_t  slave_int_raw_status();
                //void  slave_int_enable_ex(uint32_t int_flag);
                //void  slave_int_clear_ex(uint32_t int_flag);
                //void  slave_int_disable_ex(uint32_t int_flag);
                //void  slave_int_raw_status_clear_ex(uint32_t int_flag);
            //uint32_t  slave_int_status_ex(uint32_t int_flag);
            //uint32_t  slave_int_raw_status_ex(uint32_t int_flag); 

private:

  I2C::AM335x_I2C_Type &m_I2C_regs; 
}; 
 

#endif //__DM_TIMER_H
        
