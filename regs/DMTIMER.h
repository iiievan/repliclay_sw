#ifndef __DMTIMER_H
#define __DMTIMER_H

#include <stdint.h>

namespace REGS
{ 
    namespace DMTIMER
    {    
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
                uint32_t    AR        :1;             // bit: 1       [0x0 = One shot timer; 0x1 = Auto-reload timer] [see e_DMTIMER_mode] 
                uint32_t    PTV       :3;             // bit: 2..4    Pre-scale clock Timer value [see e_PRSC] 
                uint32_t    PRE       :1;             // bit: 5       enable prescale  [0x0 = TIMER clock input pin clocks; 0x1 = divided input pin clocks] 
                uint32_t    CE        :1;             // bit: 6       compare mode [0x0 = disabled; 0x1 = enabled] [see e_DMTIMER_mode] 
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
            MODE_ONESHOT_NOCMP_ENABLE = 0U,
            MODE_AUTORLD_NOCMP_ENABLE = BIT(1),
            MODE_ONESHOT_CMP_ENABLE   = BIT(6),            
            MODE_AUTORLD_CMP_ENABLE   = BIT(1)|BIT(6)   
        };

        enum e_PRSC: uint8_t
        {
            CLK_DIV_BY_2   = 0x0,
            CLK_DIV_BY_4   = 0x1,
            CLK_DIV_BY_8   = 0x2,
            CLK_DIV_BY_16  = 0x3,
            CLK_DIV_BY_32  = 0x4,
            CLK_DIV_BY_64  = 0x5,
            CLK_DIV_BY_128 = 0x6,
            CLK_DIV_BY_256 = 0x7
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
    
        struct AM335x_DMTIMER_Type 
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
        };
        
        enum e_TIMER_NUM : uint8_t
        {   
            TIMER_NA  = 0x0,
            TIMER_0   = 0x1,
            TIMER_1ms = 0x2,    // see namespace DMTIMER1MS
            TIMER_2   = 0x3,
            TIMER_3   = 0x4,
            TIMER_4   = 0x5,
            TIMER_5   = 0x6,
            TIMER_6   = 0x7,
            TIMER_7   = 0x8                      
        };

        constexpr uint32_t AM335x_DMTIMER_0_BASE = 0x44E05000;    // only 32KHz RC Clock
        constexpr uint32_t AM335x_DMTIMER_2_BASE = 0x48040000;
        constexpr uint32_t AM335x_DMTIMER_3_BASE = 0x48042000;
        constexpr uint32_t AM335x_DMTIMER_4_BASE = 0x48044000;
        constexpr uint32_t AM335x_DMTIMER_5_BASE = 0x48046000;
        constexpr uint32_t AM335x_DMTIMER_6_BASE = 0x48048000;
        constexpr uint32_t AM335x_DMTIMER_7_BASE = 0x4804A000;
        
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_0 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_0_BASE); // only 32KHz RC Clock
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_2 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_2_BASE);
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_3 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_3_BASE);
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_4 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_4_BASE);
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_5 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_5_BASE);
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_6 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_6_BASE);
        constexpr AM335x_DMTIMER_Type * AM335X_DMTIMER_7 = ((AM335x_DMTIMER_Type *) AM335x_DMTIMER_7_BASE);

    }   //namespace DMTIMER

}   //namespace REGS

#endif //__DMTIMER_H