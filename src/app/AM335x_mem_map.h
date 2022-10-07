#ifndef _AM335X_MEM_MAP_H_
#define _AM335X_MEM_MAP_H_

#include <stdint.h>
#include "app_utils.h"

#define     __R     volatile const       // 'read only' register
#define     __W     volatile             // 'write only' register 
#define     __RW    volatile             // 'read / write' register

namespace DMTIMER
{
    constexpr uint32_t AM335x_DMTIMER_0_BASE = 0x44E05000;    // only 32KHz RC Clock
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
        {                                      /* This read only register contains the revision number of the module.           */
                                               /* A write to this register has no effect.                                       */
                                               /* This register is used by software to track features, bugs, and compatibility. */
            uint32_t    Y_MINOR   :6;          // bit: 0..5    Minor Revision (Y).                   
            uint32_t    CUSTOM    :2;          // bit: 6,7     Indicates a special version for a particular device.          
            uint32_t    X_MAJOR   :3;          // bit: 8..10   Major Revision (X).
            uint32_t    R_RTL     :5;          // bit: 11..15  RTL Version (R).          
            uint32_t    FUNC      :12;         // bit: 16..27  Function indicates a software compatible module family. 
            uint32_t              :2;          // bit: 28,29   Reserved  
            uint32_t    SCHEME    :2;          // bit: 30,31   Used to distinguish between old scheme and current. 
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } TIDR_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This register allows controlling various parameters of the OCP interface. */
            uint32_t    SOFTRESET :1;          // bit: 0      Software reset. [0x0 = No action; 0x1 = reset ongoing]                  
            uint32_t    EMUFREE   :1;          // bit: 1      Sensitivity to emulation (debug) suspend event from Debug Subsystem. [0x0 = frozen during debug; 0x1 = debug suspend ignored]         
            uint32_t    IDLEMODE  :2;          // bit: 2,3    Power management[0x0 = force-idle mode; 0x1 = No idle mode; 0x2 = Smart-idle mode; 0x3 = smart-idle wakeup capable]
            uint32_t              :28;         // bit: 4..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } TIOCP_CFG_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                      /* This register must be written to after the DMA                                 */
                                               /* completes in order for subsequent DMA events to be triggered from this module. */
            uint32_t    DMAEvent_Ack :1;       // bit: 0      Write 0 to acknowledge DMA event has been completed.                   
            uint32_t                 :31;      // bit: 1..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } IRQ_EOI_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Check the corresponding secondary status register. Raw status is set             */
                                                  /* even if event is not enabled. Write 1 to set the (raw) status, mostly for debug. */
            uint32_t    MAT_IT_FLAG  :1;          // bit: 0      IRQ status for Match    [0x0 = No event pending; 0x1 = IRQ event pending]                   
            uint32_t    OVF_IT_FLAG  :1;          // bit: 1      IRQ status for Overflow [0x0 = No event pending; 0x1 = IRQ event pending]           
            uint32_t    TCAR_IT_FLAG :1;          // bit: 2      IRQ status for Capture  [0x0 = No event pending; 0x1 = IRQ event pending]  
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } IRQSTATUS_RAW_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Write 1 to clear the status after interrupt has been serviced. */
                                                  /* (raw status gets cleared, that is, even if not enabled).       */
            uint32_t    MAT_IT_FLAG  :1;          // bit: 0      IRQ status for Match    [0x0 = No event pending; 0x1 = IRQ event pending]                   
            uint32_t    OVF_IT_FLAG  :1;          // bit: 1      IRQ status for Overflow [0x0 = No event pending; 0x1 = IRQ event pending]           
            uint32_t    TCAR_IT_FLAG :1;          // bit: 2      IRQ status for Capture  [0x0 = No event pending; 0x1 = IRQ event pending]  
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } IRQSTATUS_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Write 1 to set (enable interrupt).      */
            uint32_t    MAT_EN_FLAG  :1;          // bit: 0      IRQ enable for Match    [0x0 = disabled; 0x1 = enabled]                   
            uint32_t    OVF_EN_FLAG  :1;          // bit: 1      IRQ enable for Overflow [0x0 = disabled; 0x1 = enabled]          
            uint32_t    TCAR_EN_FLAG :1;          // bit: 2      IRQ enable for Capture  [0x0 = disabled; 0x1 = enabled]  
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } IRQENABLE_SET_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Write 1 to clear (disable interrupt).      */
            uint32_t    MAT_EN_FLAG  :1;          // bit: 0      IRQ enable for Match    [0x0 = event disabled; 0x1 = Clear IRQ enable]                   
            uint32_t    OVF_EN_FLAG  :1;          // bit: 1      IRQ enable for Overflow [0x0 = event disabled; 0x1 = Clear IRQ enable]          
            uint32_t    TCAR_EN_FLAG :1;          // bit: 2      IRQ enable for Capture  [0x0 = event disabled; 0x1 = Clear IRQ enable]  
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } IRQENABLE_CLR_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Wakeup-enabled events taking place when module is      */ 
                                                  /* idle will generate an asynchronous wakeup.             */
            uint32_t    MAT_WUP_ENA  :1;          // bit: 0      Wakeup generation for Match  [0x0 = disabled; 0x1 = enabled]                   
            uint32_t    OVF_WUP_ENA  :1;          // bit: 1      Wakeup generation for Overflow  [0x0 = disabled; 0x1 = enabled]           
            uint32_t    TCAR_WUP_ENA :1;          // bit: 2      Wakeup generation for Capture  [0x0 = disabled; 0x1 = enabled]  
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } IRQWAKEEN_reg_t;

    enum e_IRQ_flags: uint32_t
    {
        IRQ_NONE = 0u,
        IRQ_MAT   = BIT(0),
        IRQ_OVF   = BIT(1),
        IRQ_TCAR  = BIT(2)      
    };

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Timer control register */                      
            uint32_t    ST        :1;             // bit: 0       automatically reset when the counter is overflowed(if AR = 0) [0x0 = counter is frozen; 0x1 = start timer] 
            uint32_t    AR        :1;             // bit: 1       [0x0 = One shot timer; 0x1 = Auto-reload timer] 
            uint32_t    PTV       :3;             // bit: 2..4    Pre-scale clock Timer value 
            uint32_t    PRE       :1;             // bit: 5       enable prescale  [0x0 = TIMER clock input pin clocks; 0x1 = divided input pin clocks] 
            uint32_t    CE        :1;             // bit: 6       compare mode [0x0 = disabled; 0x1 = enabled] 
            uint32_t    SCPWM     :1;             // bit: 7       [0x0 = clear PORTIMERPWM, sel positive pulse; 0x1 = set PORTIMERPWM, sel negative pulse]                   
            uint32_t    TCM       :2;             // bit: 8,9     Transition on PIEVENTCAPT in  [0x0 = No; 0x1 = low to high; 0x2 = high to low; 0x3 = both edge]           
            uint32_t    TRG       :2;             // bit: 10,11   Trigger on PORTIMERPWM out  [0x0 = No; 0x1 = on overflow; 0x2 = on overflow and match; 0x3 = Reserved]  
            uint32_t    PT        :1;             // bit: 12      mode on PORTIMERPWM out [0x0 = Pulse; 0x1 = Toggle] 
            uint32_t    CAPT_MODE :1;             // bit: 13      Capture mode.  [0x0 = Single capture; 0x1 = Capture on second event] 
            uint32_t    GPO_CFG   :1;             // bit: 14      drives directly the PORGPOCFG out [0x0 = PORGPOCFG->0, timer pin as out; 0x1 = PORGPOCFG->1, timer pin as in]
            uint32_t              :17;            // bit: 15..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TCLR_reg_t;

    enum e_DMTIMER_mode: uint32_t
    {
        MODE_NONE       = 0u,
        MODE_AUTORELOAD = BIT(1),
        MODE_COMPARE    = BIT(6)      
    };
    
    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* The MCU can perform a 32-bit access or two  16-bit accesses to access the register */ 
            uint32_t    TIMER_COUNTER  :32;       // bit: 0..31 Value of TIMER counter                  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TCRR_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* LOAD_VALUE must be different than the timer overflow value (0xFFFFFFFF). */ 
            uint32_t    LOAD_VALUE  :32;          // bit: 0..31 Timer counter value loaded on overflow in auto-reload mode or on TTGR write access                  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TLDR_reg_t;

   /* [reset state = 0xFFFFFFFF]*/
    typedef union 
    { 
        struct 
        {                                         /* The read value of this register is always 0xFFFFFFFF.                  */ 
                                                  /* Writing in the TTGR register, TCRR will be loaded from TLDR and        */
                                                  /* prescaler counter will be cleared.                                     */
                                                  /* Reload will be done regardless of the AR field value of TCLR register. */
            uint32_t    TTGR_VALUE  :32;          // bit: 0..31 Timer counter value loaded on overflow in auto-reload mode or on TTGR write access                  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TTGR_reg_t;

    constexpr uint32_t TTGR_DEF_VALUE = 0xFFFFFFFFu;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* In posted mode the software must read the pending write status bits             */ 
                                                  /* to insure that following write access will not be discarded due to on           */
                                                  /* going write synchronization process. These bits are automatically cleared       */                               
                                                  /* by internal logic when the write to the corresponding register is acknowledged. */                    
            uint32_t    W_PEND_TCLR :1;           // bit: 0  When equal to 1, a write is pending to the TCLR register
            uint32_t    W_PEND_TCRR :1;           // bit: 1  When equal to 1, a write is pending to the TCRR register
            uint32_t    W_PEND_TLDR :1;           // bit: 2  When equal to 1, a write is pending to the TLDR register
            uint32_t    W_PEND_TTGR :1;           // bit: 3  When equal to 1, a write is pending to the TTGR register
            uint32_t    W_PEND_TMAR :1;           // bit: 4  When equal to 1, a write is pending to the TMAR register
            uint32_t                :27;          // bit: 15..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TWPS_reg_t;

    enum e_TWPS_flags: uint32_t
    {
        F_PEND_NONE     = 0u,
        F_PEND_TCLR     = BIT(0),
        F_PEND_TCRR     = BIT(1),
        F_PEND_TLDR     = BIT(2),
        F_PEND_TTGR     = BIT(3),
        F_PEND_TMAR     = BIT(4), 
        F_PEND_ALL      = 0x1F  
    };
    

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* The compare logic consists of a 32-bit wide, read/write data TMAR register and      */   
                                                  /* logic to compare counter's current value with the value stored in the TMAR register.*/ 
            uint32_t    COMPARE_VALUE  :32;       // bit: 0..31 Value to be compared to the timer counter             
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TMAR_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* When the appropriate (rising, falling or both) transition is detected in           */
                                                  /* the edge detection logic the current counter value is stored to the TCAR1 register */
            uint32_t    CAPTURED_VALUE  :32;      // bit: 0..31 Timer counter value captured on an external event trigger             
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TCAR1_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* Access to this register is not stalled even if the timer is in non-posted mode configuration. */ 
                                                  /* Also in case of a wrong hardware PIFREQRATIO tied the POSTED field can be reprogrammed on */
                                                  /* the fly, so deadlock situation cannot happen */
            uint32_t                 :1;          // bit: 0      Reserved      
            uint32_t    SFT          :1;          // bit: 1      Resets all the function parts of the module. [0x0 = reset enabled; 0x1 = reset disabld]               
            uint32_t    POSTED       :1;          // bit: 2      PIFREQRATIO [0x0 = Posted mode inactive; 0x1 = Posted mode active] 
            uint32_t                 :29;         // bit: 3..31  Reserved  
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TSICR_reg_t;

    /* [reset state = 0x0]*/
    typedef union 
    { 
        struct 
        {                                         /* When the appropriate (rising, falling or both) transition is detected in               */
                                                  /* the edge detection logic and the capture on second event is activated from             */
                                                  /* the control register (TCLR), the current counter value is stored to the TCAR2 register.*/
            uint32_t    CAPTURED_VALUE  :32;      // bit: 0..31 Timer counter value captured on an external event trigger             
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } TCAR2_reg_t;

    typedef struct 
    {                                                                                      
        __RW  TIDR_reg_t            TIDR;                    // (0x00)  Identification Register
        __R   uint32_t              RESERVED1[3];
        __RW  TIOCP_CFG_reg_t       TIOCP_CFG;               // (0x10)  Timer OCP Configuration Register
        __R   uint32_t              RESERVED2[3];
        __RW  IRQ_EOI_reg_t         IRQ_EOI;                 // (0x20)  Timer IRQ End-of-Interrupt Register
        __RW  IRQSTATUS_RAW_reg_t   IRQSTATUS_RAW;           // (0x24)  Timer IRQ Status Raw Register
        __RW  IRQSTATUS_reg_t       IRQSTATUS;               // (0x28)  Timer IRQ Status Register
        __RW  IRQENABLE_SET_reg_t   IRQENABLE_SET;           // (0x2C)  Timer Interrupt Enable Set Registerr
        __RW  IRQENABLE_CLR_reg_t   IRQENABLE_CLR;           // (0x30)  Timer Interrupt Enable Clear Register
        __RW  IRQWAKEEN_reg_t       IRQWAKEEN;               // (0x34)  Timer IRQ Wakeup Enable Register
        __RW  TCLR_reg_t            TCLR;                    // (0x38)  Timer Control Register
        __RW  TCRR_reg_t            TCRR;                    // (0x3C)  Timer Counter Register
        __RW  TLDR_reg_t            TLDR;                    // (0x40)  Timer Load Register
        __W   TTGR_reg_t            TTGR;                    // (0x44)  Timer Trigger Register
        __RW  TWPS_reg_t            TWPS;                    // (0x48)  Timer Write Posting Bits Register
        __RW  TMAR_reg_t            TMAR;                    // (0x4C)  Timer Match Register
        __RW  TCAR1_reg_t           TCAR1;                   // (0x50)  Timer Capture Register 1
        __RW  TSICR_reg_t           TSICR;                   // (0x54)  Timer Synchronous Interface Control Register
        __RW  TCAR2_reg_t           TCAR2;                   // (0x58)  Timer Capture Register 2                                                                                                               
    } AM335x_DMTIMER_Type;
    
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_0 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_0_BASE); // only 32KHz RC Clock
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_1 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_1_BASE); // only 1ms timer
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_2 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_2_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_3 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_3_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_4 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_4_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_5 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_5_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_6 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_6_BASE);
    constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_7 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_7_BASE);
} 

namespace I2C
{
    typedef struct 
    {                                                                                      
        __R   I2C_REVNB_LO_reg_t                I2C_REVNB_LO;            // (0x00)  Module Revision Register (low bytes) 
        __R   I2C_REVNB_HI_reg_t                I2C_REVNB_HI;            // (0x04)  Module Revision Register (high bytes) 
        __R   uint32_t                          RESERVED1[3];
        __RW  I2C_SYSC_reg_t                    I2C_SYSC;                // (0x10)  System Configuration Register
        __RW  I2C_IRQSTATUS_RAW_reg_t           I2C_IRQSTATUS_RAW;       // (0x24)  2C Status Raw Register
        __R   uint32_t                          RESERVED2[8];
        __RW  I2C_IRQSTATUS_reg_t               I2C_IRQSTATUS;           // (0x28)  I2C Status Register
        __RW  I2C_IRQENABLE_SET_reg_t           I2C_IRQENABLE_SET;       // (0x2C)  I2C Interrupt Enable Set Register
        __RW  I2C_IRQENABLE_CLR_reg_t           I2C_IRQENABLE_CLR;       // (0x30)  I2C Interrupt Enable Clear Register
        __RW  I2C_WE_reg_t                      I2C_WE;                  // (0x34)  I2C Wakeup Enable Register
        __RW  I2C_DMARXENABLE_SET_reg_t         I2C_DMARXENABLE_SET;     // (0x38)  Receive DMA Enable Set Register
        __RW  I2C_DMATXENABLE_SET_reg_t         I2C_DMATXENABLE_SET;     // (0x3C)  Transmit DMA Enable Set Register
        __RW  I2C_DMARXENABLE_CLR_reg_t         I2C_DMARXENABLE_CLR;     // (0x40)  Receive DMA Enable Clear Register
        __RW   I2C_DMATXENABLE_CLR_reg_t        I2C_DMATXENABLE_CLR;     // (0x44)  Transmit DMA Enable Clear Register
        __RW  I2C_DMARXWAKE_EN_reg_t            I2C_DMARXWAKE_EN;        // (0x48)  Receive DMA Wakeup Register
        __RW  I2C_DMATXWAKE_EN_reg_t            I2C_DMATXWAKE_EN;        // (0x4C)  Transmit DMA Wakeup Register
        __R   uint32_t                          RESERVED3[17];
        __RW  I2C_SYSS_reg_t                    I2C_SYSS;                // (0x90)  System Status Register
        __RW  I2C_BUF_reg_t                     I2C_BUF;                 // (0x94)  Buffer Configuration Register
        __RW  I2C_CNT_reg_t                     I2C_CNT;                 // (0x98)  Data Counter Register    
        __RW  I2C_DATA_reg_t                    I2C_DATA;                // (0x9C)  Data Access Register
        __R   uint32_t                          RESERVED4[2];
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
        
    typedef union 
    { 
        struct 
        {                                      /* This read-only register contains the hard-coded revision number of the module.
                                                  A write to this register has no effect. I2C controller with interrupt using interrupt vector register (I2C_IV) is revision 1.x.
                                                 I2C controller with interrupt using status register bits (I2C_IRQSTATUS_RAW) is revision 2.x. */
                                                               
            uint32_t    MINOR   :6;            // bit: 0..5    Minor Revision. This field changes when features are scaled up or down. This field does not change due to bug fix, or major feature change.                        
            uint32_t    CUSTOM  :2;            // bit: 6,7     Indicates a special version for a particular device. Consequence of use may avoid use of standard Chip Support.Library (CSL) / Drivers.0 if non-custom.                                 
            uint32_t    MAJOR   :3;            // bit: 8..10   Major Revision. This field changes when there is a major feature change. This field does not change due to bug fix, or minor feature change.
            uint32_t    RTL     :5;            // bit: 11..15  RTL Version.          
            uint32_t            :16;           // bit: 16..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_REVNB_LO_reg_t;
          
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
    
    typedef union 
    { 
        struct 
        {                                      /* This register allows controlling various parameters of the peripheral interface. */
                                                               
            uint32_t    AUTOIDLE       :1;         // bit: 0       Autoidle bit. When this bit is set to 1, the module activates its own idle mode mechanism. By evaluating its internal state, the module can decide to gate part of his internal clock tree in order to improve the overall power consumption.Value after reset is high. 0h = Auto Idle mechanism is disabled. 1h = Auto Idle mechanism is enabled.         
            uint32_t    SRST           :1;         // bit: 1       SoftReset bit. When this bit is set to 1, entire module is reset as for the hardware reset. This bit is automatically cleared to 0 by the core and it is only reset by the hardware reset. During reads, it always returns 0. Value after reset is low. 0h = Normal mode. 1h = The module is reset.                               
            uint32_t    ENAWAKEUP      :1;         // bit: 2       Enable Wakeup control bit. When this bit is set to 1, the module enables its own wakeup mechanism. Value after reset is low. 0h = Wakeup mechanism is disabled. 1h = Wakeup mechanism is enabled.
            uint32_t    IDLEMODE       :2;         // bit: 3,4     Enable Wakeup control bit. When this bit is set to 1, the module enables its own wakeup mechanism. Value after reset is low. 0h = Wakeup mechanism is disabled. 1h = Wakeup mechanism is enabled.
            uint32_t                   :3;         // bit: 5..7    Reserved
            uint32_t    CLKACTIVITY    :2;         // bit: 8,9     Clock Activity selection bits.          
            uint32_t                   :22;        // bit: 10..31  Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_SYSC_reg_t;
    
    typedef union 
    { 
        struct 
        {                                      /* This register provides core status information for interrupt handling, showing all active events (enabled and not enabled).
                                                  The fields are read-write. Writing a 1 to a bit will set it to 1, that is, trigger the IRQ (mostly for debug).
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  Only enabled, active events will trigger an actual interrupt request on the IRQ output line. */
                                                               
            uint32_t    AL       :1;       // bit: 0       Arbitration lost IRQ status.        
            uint32_t    NACK     :1;       // bit: 1       No acknowledgment IRQ status.                               
            uint32_t    ARDY     :1;       // bit: 2       I2C mode only.
            uint32_t    RRDY     :1;       // bit: 3       Receive mode only (I2C mode).
            uint32_t    XRDY     :1;       // bit: 4       Transmit data ready IRQ status.
            uint32_t    GC       :1;       // bit: 5       General call IRQ status.          
            uint32_t    STC      :1;       // bit: 6       Start Condition IRQ status.  
            uint32_t    AERR     :1;       // bit: 7       Access Error IRQ status.  
            uint32_t    BF       :1;       // bit: 8       I2C mode only.  
            uint32_t    AAS      :1;       // bit: 9       Address recognized as slave IRQ status.  
            uint32_t    XUDF     :1;       // bit: 10      Transmit underflow status.  
            uint32_t    ROVR     :1;       // bit: 11      Receive overrun status.  
            uint32_t    BB       :1;       // bit: 12      This read-only bit indicates the state of the serial bus.
            uint32_t    RDR      :1;       // bit: 13      Receive draining IRQ status.
            uint32_t    XDR      :1;       // bit: 14      Transmit draining IRQ status.
            uint32_t             :17;      // bit: 15..31  Reserved
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_IRQSTATUS_RAW_reg_t;
    
    typedef union 
    { 
        struct 
        {                                      /* This register provides core status information for interrupt handling, showing all active and enabled events and masking the others. 
                                                  The fields are read-write. Writing a 1 to a bit will clear it to 0, that is, clear the IRQ. 
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  Only enabled, active events will trigger an actual interrupt request on the IRQ output line. 
                                                  For all the internal fields of the I2C_IRQSTATUS register, the descriptions given in the I2C_IRQSTATUS_RAW subsection are valid.*/
                                                               
            uint32_t    AL       :1;       // bit: 0       Arbitration lost IRQ enabled status. During reads, it always returns 0. 0h = Normal operation. 1h = Arbitration lost detected
            uint32_t    NACK     :1;       // bit: 1       No acknowledgment IRQ enabled status. Write '1' to clear this bit. 0h = Normal operation. 1h = Not Acknowledge detected                                
            uint32_t    ARDY     :1;       // bit: 2       Register access ready IRQ enabled status. 0h = Module busy. 1h = Access ready.
            uint32_t    RRDY     :1;       // bit: 3       Receive data ready IRQ enabled status. Write '1' to clear. 0h = No data available. 1h = Receive data available.
            uint32_t    XRDY     :1;       // bit: 4       Transmit data ready IRQ enabled status. 0h = Transmission ongoing. 1h = Transmit data ready.
            uint32_t    GC       :1;       // bit: 5       General call IRQ enabled status. 0h = No general call detected. 1h = General call address detected.         
            uint32_t    STC      :1;       // bit: 6       Start Condition IRQ enabled status. 0h = No action. 1h = Start condition detected.
            uint32_t    AERR     :1;       // bit: 7       Access Error IRQ enabled status. 0h = No action. 1h = Access error.
            uint32_t    BF       :1;       // bit: 8       Bus Free IRQ enabled status. 0h = No action. 1h = Bus free. 
            uint32_t    AAS      :1;       // bit: 9       Address recognized as slave IRQ enabled status. 0h = No action. 1h = Address recognized.
            uint32_t    XUDF     :1;       // bit: 10      Transmit underflow enabled status. Writing into this bit has no effect. 0h = Normal operation. 1h = Transmit underflow
            uint32_t    ROVR     :1;       // bit: 11      Receive overrun enabled status. Writing into this bit has no effect. 0h = Normal operation. 1h = Receiver overrun.  
            uint32_t    BB       :1;       // bit: 12      Bus busy enabled status. Writing into this bit has no effect. 0h = Bus is free. 1h = Bus is occupied.
            uint32_t    RDR      :1;       // bit: 13      Receive draining IRQ enabled status.0h = Receive draining inactive. 1h = Receive draining enabled.
            uint32_t    XDR      :1;       // bit: 14      Transmit draining IRQ enabled status. 0h = Transmit draining inactive. 1h = Transmit draining enabled.
            uint32_t             :17;      // bit: 15..31  Reserved
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } I2C_IRQSTATUS_reg_t;
    
    typedef union 
    { 
        struct 
        {                                      /* All 1-bit fields enable a specific interrupt event to trigger an interrupt request. Writing a 1 to a bit will enable the field. 
                                                  Writing a 0 will have no effect, that is, the register value will not be modified. 
                                                  For all the internal fields of the I2C_IRQENABLE_SET register, the descriptions given in the I2C_IRQSTATUS_RAW subsection are valid.*/
                                                               
            uint32_t    AL_IE       :1;       // bit: 0       Arbitration lost interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[AL]. 0h = Arbitration lost interrupt disabled. 1h = Arbitration lost interrupt enabled.
            uint32_t    NACK_IE     :1;       // bit: 1       No acknowledgment interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[NACK]. 0h = Not Acknowledge interrupt disabled. 1h = Not Acknowledge interrupt enabled.                                
            uint32_t    ARDY_IE     :1;       // bit: 2       Register access ready interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[ARDY]. 0h = Register access ready interrupt disabled. 1h = Register access ready interrupt enabled.
            uint32_t    RRDY_IE     :1;       // bit: 3       Receive data ready interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[RRDY]. 0h = Receive data ready interrupt disabled. 1h = Receive data ready interrupt enabled.
            uint32_t    XRDY_IE     :1;       // bit: 4       Transmit data ready interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[XRDY]. 0h = Transmit data ready interrupt disabled. 1h = Transmit data ready interrupt enabled.
            uint32_t    GC_IE       :1;       // bit: 5       General call interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[GC]. 0h = General call interrupt disabled. 1h = General call interrupt enabled.
            uint32_t    STC_IE      :1;       // bit: 6       Start condition interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[STC]. 0h = Start condition interrupt disabled. 1h = Start condition interrupt enabled.
            uint32_t    AERR_IE     :1;       // bit: 7       Access error interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[AERR]. 0h = Access error interrupt disabled. 1h = Access error interrupt enabled.
            uint32_t    BF_IE       :1;       // bit: 8       Bus free interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[BF]. 0h = Bus free interrupt disabled. 1h = Bus free interrupt enabled.
            uint32_t    AAS_IE      :1;       // bit: 9       Addressed as slave interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[AAS]. 0h = Addressed as slave interrupt disabled. 1h = Addressed as slave interrupt enabled.
            uint32_t    XUDF        :1;       // bit: 10      Transmit underflow enable set. 0h = Transmit underflow interrupt disabled. 1h = Transmit underflow interrupt enabled.
            uint32_t    ROVR        :1;       // bit: 11      Receive overrun enable set. 0h = Receive overrun interrupt disabled. 1h = Receive draining interrupt enabled.
            uint32_t                :1;       // bit: 12      Reserved
            uint32_t    RDR_IE      :1;       // bit: 13      Receive draining interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[RDR]. 0h = Receive draining interrupt disabled. 1h = Receive draining interrupt enabled.
            uint32_t    XDR_IE      :1;       // bit: 14      Transmit draining interrupt enable set. Mask or unmask the interrupt signaled by bit in I2C_STAT[XDR]. 0h = Transmit draining interrupt disabled. 1h = Transmit draining interrupt enabled.
            uint32_t                :17;      // bit: 15..31  Reserved
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } I2C_IRQENABLE_SET_reg_t;
    
    } AM335x_I2C_Type;

#endif //_AM335X_MEM_MAP_H_