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

namespace PRCM
{  
    constexpr uint32_t AM335x_PRCM_BASE         = 0x44E00000; 
    constexpr uint32_t AM335x_CM_PER_BASE       = AM335x_PRCM_BASE;       
    constexpr uint32_t AM335x_CM_WKUP_BASE      = 0x44E00400;
    constexpr uint32_t AM335x_CM_DPLL_BASE      = 0x44E00500;
    constexpr uint32_t AM335x_CM_MPU_BASE       = 0x44E00600;
    constexpr uint32_t AM335x_CM_DEVICE_BASE    = 0x44E00700;
    constexpr uint32_t AM335x_CM_RTC_BASE       = 0x44E00800;
    constexpr uint32_t AM335x_CM_GFX_BASE       = 0x44E00900;
    constexpr uint32_t AM335x_CM_CEFUSE_BASE    = 0x44E00A00;
    
    constexpr uint32_t AM335x_PRM_IRQ_BASE      = 0x44E00B00;    
    constexpr uint32_t AM335x_PRM_PER_BASE      = 0x44E00C00;    
    constexpr uint32_t AM335x_PRM_WKUP_BASE     = 0x44E00D00;
    constexpr uint32_t AM335x_PRM_MPU_BASE      = 0x44E00E00;
    constexpr uint32_t AM335x_PRM_DEVICE_BASE   = 0x44E00F00;
    constexpr uint32_t AM335x_PRM_RTC_BASE      = 0x44E01000;
    constexpr uint32_t AM335x_PRM_GFX_BASE      = 0x44E01100;
    constexpr uint32_t AM335x_PRM_CEFUSE_BASE   = 0x44E01200;
    
    /* [reset state = 0xC0102]*/
    typedef union 
    { 
        struct 
        {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                   /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                   :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                :6;   // bit: 2..7     Reserved                
            uint32_t    CLKACTIVITY_L4LS_GCLK       :1;   // bit: 8        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]
            uint32_t                                :1;   // bit: 9        Reserved
            uint32_t    CLKACTIVITY_UART_GFCLK      :1;   // bit: 10       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_CAN_CLK         :1;   // bit: 11       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                :1;   // bit: 12       Reserved
            uint32_t    CLKACTIVITY_TIMER7_GCLK     :1;   // bit: 13       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_TIMER2_GCLK     :1;   // bit: 14       (R)state of the clock in domain [0x0 = Inact; 0x1= Act]   
            uint32_t    CLKACTIVITY_TIMER3_GCLK     :1;   // bit: 15       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_TIMER4_GCLK     :1;   // bit: 16       (R)state of the clock in domain [0x0 = Inact; 0x1= Act]  
            uint32_t    CLKACTIVITY_LCDC_GCLK       :1;   // bit: 17       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                :1;   // bit: 18       Reserved
            uint32_t    CLKACTIVITY_GPIO_1_GDBCLK   :1;   // bit: 19       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_GPIO_2_GDBCLK   :1;   // bit: 20       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_GPIO_3_GDBCLK   :1;   // bit: 21       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                :2;   // bit: 22,23    Reserved
            uint32_t    CLKACTIVITY_I2C_FCLK        :1;   // bit: 24       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_SPI_GCLK        :1;   // bit: 25       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                :1;   // bit: 26       Reserved
            uint32_t    CLKACTIVITY_TIMER5_GCLK     :1;   // bit: 27       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_TIMER6_GCLK     :1;   // bit: 28       (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                :3;   // bit: 29..32   Reserved
        } b;                                      
        uint32_t  reg;                           
    } L4LS_CLKSTCTRL_reg_t;

    /* [reset state = 0xA]*/
    typedef union 
    { 
        struct 
        {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                   /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */ 
            uint32_t    CLKTRCTRL            :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED]     
            uint32_t                         :1;   // bit: 2        Reserved            
            uint32_t    CLKACTIVITY_L3S_GCLK :1;   // bit: 3        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]     
            uint32_t                         :28;  // bit: 4..31    Reserved
        } b;                                      
        uint32_t  reg;                           
    } L3S_CLKSTCTRL_reg_t;

    /* [reset state = 0x12]*/
    typedef union 
    { 
        struct 
        {                                          /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                   /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                 :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED]         
            uint32_t    CLKACTIVITY_EMIF_GCLK     :1;   // bit: 2        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t    CLKACTIVITY_MMC_FCLK      :1;   // bit: 3        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_L3_GCLK       :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                              :1;   // bit: 5        Reserved
            uint32_t    CLKACTIVITY_CPTS_RFT_GCLK :1;   // bit: 6        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_MCASP_GCLK    :1;   // bit: 7        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                              :24;  // bit: 8..31
        } b;                                      
        uint32_t  reg;                           
    } L3_CLKSTCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the CPSW clocks. */ 
                                         /* These bits is warm reset insensitively when CPSW RESET_ISO enabled */
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } CPGMAC0_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the LCD clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } LCDC_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the USB clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } USB0_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TPTC clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TPTC0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the EMIF clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } EMIF_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the OCMC clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } OCMCRAM_CLKCTRL_reg_t;

    /* [reset state = 0x30002]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the GPMC clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } GPMC_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MCASP0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MCASP0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the UART5 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } UART5_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MMC0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MMC0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the ELM clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } ELM_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the I2C2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } I2C2_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the I2C1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } I2C1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the SPI0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } SPI0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the SPI1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } SPI1_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the L4LS clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } L4LS_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MCASP1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MCASP1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the UART1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } UART1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the UART2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } UART2_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the UART3 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } UART3_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the UART4 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } UART4_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER7 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER7_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER2_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER3 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER3_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER4 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER4_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                                                /* This register manages the GPIO1 clocks. */ 
            uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t                            :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    OPTFCLKEN_GPIO_1_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
            uint32_t                            :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } GPIO1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                                                /* This register manages the GPIO2 clocks. */ 
            uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t                            :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    OPTFCLKEN_GPIO_2_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
            uint32_t                            :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } GPIO2_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                                                /* This register manages the GPIO3 clocks. */ 
            uint32_t    MODULEMODE              :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t                            :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST                  :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    OPTFCLKEN_GPIO_3_GDBCLK :1;   // bit: 18         (RW)Optional functional clock control [0x0 = FCLK_DIS; 0x1 = FCLK_EN]
            uint32_t                            :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } GPIO3_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TPCC clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TPCC_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the DCAN0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } DCAN0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the DCAN1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } DCAN1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the PWMSS1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } EPWMSS1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the PWMSS0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } EPWMSS0_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the PWMSS2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } EPWMSS2_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the L3 INSTR clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } L3_INSTR_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the L3 Interconnect clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } L3_CLKCTRL_reg_t;

    /* [reset state = 0x70002]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the IEEE1500 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } IEEE5000_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the PRU-ICSS clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } PRU_ICSS_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER5 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER5_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TIMER6 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TIMER6_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MMC1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MMC1_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MMC2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MMC2_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TPTC1 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TPTC1_CLKCTRL_reg_t;

    /* [reset state = 0x70000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the TPTC2 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } TPTC2_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the SPINLOCK clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } SPINLOCK_CLKCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the MAILBOX0 clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } MAILBOX0_CLKCTRL_reg_t;

    /* [reset state = 0x7A]*/
    typedef union 
    { 
        struct 
        {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                              /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :1;   // bit: 2        Reserved        
            uint32_t    CLKACTIVITY_L4HS_GCLK           :1;   // bit: 3        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t    CLKACTIVITY_CPSW_250MHZ_GCLK    :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_CPSW_50MHZ_GCLK     :1;   // bit: 5        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_CPSW_5MHZ_GCLK      :1;   // bit: 6        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                    :25;  // bit: 7..31    Reserved
        } b;                                      
        uint32_t  reg;                           
    } L4HS_CLKSTCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the L4 Fast clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } L4HS_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                            /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :2;   // bit: 2,3      Reserved        
            uint32_t    CLKACTIVITY_OCPWP_L3_GCLK       :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t    CLKACTIVITY_OCPWP_L4_GCLK       :1;   // bit: 5        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                    :26;  // bit: 6..31    Reserved 
        } b;                                      
        uint32_t  reg;                           
    } OCPWP_L3_CLKSTCTRL_reg_t;


    /* [reset state = 0x70002]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the OCPWP clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t    STBYST     :1;   // bit: 18         (R)Module standby status.[0x0 = Func; 0x1= Standby]
            uint32_t               :13;  // bit: 19..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } OCPWP_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                            /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :2;   // bit: 2,3      Reserved        
            uint32_t    CLKACTIVITY_PRU_ICSS_OCP_GCLK   :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t    CLKACTIVITY_PRU_ICSS_IEP_GCLK   :1;   // bit: 5        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t    CLKACTIVITY_PRU_ICSS_UART_GCLK  :1;   // bit: 6        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                    :25;  // bit: 7..31    Reserved 
        } b;                                      
        uint32_t  reg;                           
    } PRUICSS_CLKSTCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                                   /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                            /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :2;   // bit: 2,3      Reserved        
            uint32_t    CLKACTIVITY_CPSW_125MHz_GCLK    :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t                                    :27;  // bit: 5..31    Reserved 
        } b;                                      
        uint32_t  reg;                           
    } CPSW_CLKSTCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                              /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :2;   // bit: 2,3      Reserved        
            uint32_t    CLKACTIVITY_LCDC_L3_OCP_GCLK    :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t    CLKACTIVITY_LCDC_L4_OCP_GCLK    :1;   // bit: 5        (R)state of the clock in domain [0x0 = Inact; 0x1= Act] 
            uint32_t                                    :26;  // bit: 6..31    Reserved 
        } b;                                      
        uint32_t  reg;                           
    } LCDC_CLKSTCTRL_reg_t;

    /* [reset state = 0x30000]*/
    typedef union 
    { 
        struct 
        {                                /* This register manages the CLKDIV32K clocks. */ 
            uint32_t    MODULEMODE :2;   // bit: 0,1        (RW)Control the way mandatory clocks are managed.[0x0 = DISABLED; 0x1 = RESERVED_1; 0x2 = ENABLE; 0x3 = RESERVED] 
            uint32_t               :14;  // bit: 2..15      Reserved                    
            uint32_t    IDLEST     :2;   // bit: 16,17      (R)Module idle status.[0x0 = Func; 0x1 = Trans; 0x2 = Idle; 0x3 = Disable] 
            uint32_t               :14;  // bit: 18..31     Reserved
        } b;                                      
        uint32_t  reg;                           
    } CLKDIV32K_CLKCTRL_reg_t;

    /* [reset state = 0x2]*/
    typedef union 
    { 
        struct 
        {                                                     /* This register enables the domain power state transition. It controls the SW supervised clock domain state */
                                                              /* transition between ON-ACTIVE and ON-INACTIVE states.                                                      */
            uint32_t    CLKTRCTRL                       :2;   // bit: 0,1      (RW)Clock state transition[0x0 = NO_SLEEP; 0x1 = SW_SLEEP; 0x2 = SW_WKUP; 0x3 = RESERVED] 
            uint32_t                                    :2;   // bit: 2,3      Reserved        
            uint32_t    CLKACTIVITY_CLK_24MHZ_GCLK      :1;   // bit: 4        (R)state of the clock in domain [0x0 = Inact; 0x1= Act]             
            uint32_t                                    :27;  // bit: 5..31    Reserved 
        } b;                                      
        uint32_t  reg;                           
    } CLKSTCTRL_24MHz_reg_t;

    typedef struct 
    {                                                                                      
        __RW  L4LS_CLKSTCTRL_reg_t        L4LS_CLKSTCTRL;      // (0x00)  
        __RW  L3S_CLKSTCTRL_reg_t         L3S_CLKSTCTRL;       // (0x04) 
        __R   uint32_t                    RESERVED1[1]; 
        __RW  L3_CLKSTCTRL_reg_t          L3_CLKSTCTRL;        // (0x0C) 
        __R   uint32_t                    RESERVED2[1];  
        __RW  CPGMAC0_CLKCTRL_reg_t       CPGMAC0_CLKCTRL;     // (0x14)  
        __RW  LCDC_CLKCTRL_reg_t          LCDC_CLKCTRL;        // (0x18)  
        __RW  USB0_CLKCTRL_reg_t          USB0_CLKCTRL;        // (0x1C)
        __R   uint32_t                    RESERVED3[1];   
        __RW  TPTC0_CLKCTRL_reg_t         TPTC0_CLKCTRL;       // (0x24)  
        __RW  EMIF_CLKCTRL_reg_t          EMIF_CLKCTRL;        // (0x28)  
        __RW  OCMCRAM_CLKCTRL_reg_t       OCMCRAM_CLKCTRL;     // (0x2C)  
        __RW  GPMC_CLKCTRL_reg_t          GPMC_CLKCTRL;        // (0x30)  
        __RW  MCASP0_CLKCTRL_reg_t        MCASP0_CLKCTRL;      // (0x34)  
        __RW  UART5_CLKCTRL_reg_t         UART5_CLKCTRL;       // (0x38)  
        __RW  MMC0_CLKCTRL_reg_t          MMC0_CLKCTRL;        // (0x3C)  
        __RW  ELM_CLKCTRL_reg_t           ELM_CLKCTRL;         // (0x40)  
        __RW  I2C2_CLKCTRL_reg_t          I2C2_CLKCTRL;        // (0x44)  
        __RW  I2C1_CLKCTRL_reg_t          I2C1_CLKCTRL;        // (0x48)  
        __RW  SPI0_CLKCTRL_reg_t          SPI0_CLKCTRL;        // (0x4C) 
        __RW  SPI1_CLKCTRL_reg_t          SPI1_CLKCTRL;        // (0x50) 
        __R   uint32_t                    RESERVED4[3];  
        __RW  L4LS_CLKCTRL_reg_t          L4LS_CLKCTRL;        // (0x60)
        __R   uint32_t                    RESERVED5[1];   
        __RW  MCASP1_CLKCTRL_reg_t        MCASP1_CLKCTRL;      // (0x68)  
        __RW  UART1_CLKCTRL_reg_t         UART1_CLKCTRL;       // (0x6C)  
        __RW  UART2_CLKCTRL_reg_t         UART2_CLKCTRL;       // (0x70)  
        __RW  UART3_CLKCTRL_reg_t         UART3_CLKCTRL;       // (0x74)  
        __RW  UART4_CLKCTRL_reg_t         UART4_CLKCTRL;       // (0x78)  
        __RW  TIMER7_CLKCTRL_reg_t        TIMER7_CLKCTRL;      // (0x7C)  
        __RW  TIMER2_CLKCTRL_reg_t        TIMER2_CLKCTRL;      // (0x80)  
        __RW  TIMER3_CLKCTRL_reg_t        TIMER3_CLKCTRL;      // (0x84)  
        __RW  TIMER4_CLKCTRL_reg_t        TIMER4_CLKCTRL;      // (0x88)
        __R   uint32_t                    RESERVED6[8];   
        __RW  GPIO1_CLKCTRL_reg_t         GPIO1_CLKCTRL;       // (0xAC)  
        __RW  GPIO2_CLKCTRL_reg_t         GPIO2_CLKCTRL;       // (0xB0)  
        __RW  GPIO3_CLKCTRL_reg_t         GPIO3_CLKCTRL;       // (0xB4)  
        __RW  TPCC_CLKCTRL_reg_t          TPCC_CLKCTRL;        // (0xBC)  
        __RW  DCAN0_CLKCTRL_reg_t         DCAN0_CLKCTRL;       // (0xC0)  
        __RW  DCAN1_CLKCTRL_reg_t         DCAN1_CLKCTRL;       // (0xC4)  
        __RW  EPWMSS1_CLKCTRL_reg_t       EPWMSS1_CLKCTRL;     // (0xCC) 
        __R   uint32_t                    RESERVED7[1]; 
        __RW  EPWMSS0_CLKCTRL_reg_t       EPWMSS0_CLKCTRL;     // (0xD4)  
        __RW  EPWMSS2_CLKCTRL_reg_t       EPWMSS2_CLKCTRL;     // (0xD8)  
        __RW  L3_INSTR_CLKCTRL_reg_t      L3_INSTR_CLKCTRL;    // (0xDC)  
        __RW  L3_CLKCTRL_reg_t            L3_CLKCTRL;          // (0xE0) 
        __RW  IEEE5000_CLKCTRL_reg_t      IEEE5000_CLKCTRL;    // (0xE4)  
        __RW  PRU_ICSS_CLKCTRL_reg_t      PRU_ICSS_CLKCTRL;    // (0xE8)  
        __RW  TIMER5_CLKCTRL_reg_t        TIMER5_CLKCTRL;      // (0xEC)  
        __RW  TIMER6_CLKCTRL_reg_t        TIMER6_CLKCTRL;      // (0xF0)  
        __RW  MMC1_CLKCTRL_reg_t          MMC1_CLKCTRL;        // (0xF4)  
        __RW  MMC2_CLKCTRL_reg_t          MMC2_CLKCTRL;        // (0xF8) 
        __RW  TPTC1_CLKCTRL_reg_t         TPTC1_CLKCTRL;       // (0xFC)  
        __RW  TPTC2_CLKCTRL_reg_t         TPTC2_CLKCTRL;       // (0x100)  
        __R   uint32_t                    RESERVED8[2]; 
        __RW  SPINLOCK_CLKCTRL_reg_t      SPINLOCK_CLKCTRL;    // (0x10C)  
        __RW  MAILBOX0_CLKCTRL_reg_t      MAILBOX0_CLKCTRL;    // (0x110)
        __R   uint32_t                    RESERVED9[2];  
        __RW  L4HS_CLKSTCTRL_reg_t        L4HS_CLKSTCTRL;      // (0x11C)  
        __RW  L4HS_CLKCTRL_reg_t          L4HS_CLKCTRL;        // (0x120)
        __R   uint32_t                    RESERVED10[2];  
        __RW  OCPWP_L3_CLKSTCTRL_reg_t    OCPWP_L3_CLKSTCTRL;  // (0x12C) 
        __RW  OCPWP_CLKCTRL_reg_t         OCPWP_CLKCTRL;       // (0x130) 
        __R   uint32_t                    RESERVED11[3];  
        __RW  PRUICSS_CLKSTCTRL_reg_t     PRUICSS_CLKSTCTRL;   // (0x140)  
        __RW  CPSW_CLKSTCTRL_reg_t        CPSW_CLKSTCTRL;      // (0x144) 
        __RW  LCDC_CLKSTCTRL_reg_t        LCDC_CLKSTCTRL;      // (0x148)  
        __RW  CLKDIV32K_CLKCTRL_reg_t     CLKDIV32K_CLKCTRL;   // (0x14C) 
        __RW  CLKSTCTRL_24MHz_reg_t       CLKSTCTRL_24MHz;     // (0x150)                                                                                     
    } AM335x_CM_PER_Type;

    constexpr AM335x_CM_PER_Type * AM335X_CM_PER = ((AM335x_CM_PER_Type *) AM335x_CM_PER_BASE); 

    /* [reset state = 0x0]*/
    //typedef union 
    //{ 
    //    struct 
    //    {               /*  */ 
    //        uint32_t    R :1;   // bit: 0        
    //        uint32_t    R :1;   // bit: 1                    
    //        uint32_t    R :1;   // bit: 2      
    //        uint32_t    R :1;   // bit: 3
    //        uint32_t    R :1;   // bit: 4
    //        uint32_t    R :1;   // bit: 5
    //        uint32_t    R :1;   // bit: 6
    //        uint32_t    R :1;   // bit: 7
    //        uint32_t    R :1;   // bit: 8
    //    } b;                                      
    //    uint32_t  reg;                           
    //} _reg_t;
  
}


#endif //_AM335X_MEM_MAP_H_