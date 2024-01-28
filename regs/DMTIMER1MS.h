#ifndef __DMTIMER1MS_H
#define __DMTIMER1MS_H

#include <stdint.h>
#include "utils.h"

namespace REGS
{ 
    namespace DMTIMER1MS
    {    
        /* [reset state = 0x15]*/
        typedef union 
        { 
            /* This register contains the IP revision code */
            union
            {
                struct 
                {                                  
                    uint32_t    MINOR     :4;          // bit: 0..3    (R) Minor Revision.                   
                    uint32_t    MAJOR     :4;          // bit: 4..7    (R) Major Revision.           
                    uint32_t              :24;         // bit: 8..31   (R) Reserved 
                }mm;  
                struct 
                {                                  
                    uint32_t    TID_REV   :8;          // bit: 0..7    (R) IP revision.                             
                    uint32_t              :24;         // bit: 8..31   (R) Reserved 
                }ip; 
            }b;                                        // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } TIDR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        { 
            struct 
            {                                           /* This register controls the various parameters of the OCP interface */
                uint32_t    AutoIdle       :1;          // bit: 0       (RW) Internal OCP clock gating strategy 
                                                        //              [0x0 = clkfree; OCP clock is free-running 
                                                        //               0x1 = clkgate; Automatic OCP clock gating strategy is applied, based
                                                        //               on the OCP interface activity]
                uint32_t    SoftReset      :1;          // bit: 1       (RW) Software reset.This bit is automatically reset by the hardware. 
                                                        //              During reads, it always return 0
                                                        //              [0x0 = nmode;Normal mode 
                                                        //               0x1 = rstmode; The module is reset]
                uint32_t    EnaWakeup      :1;          // bit: 2       (RW) Wake-up feature global control
                                                        //              [0x0 = nowake:No wakeup line assertion in idle mode
                                                        //               0x1 = enbwake; Wakeup line assertion enabled in smart-idle mode]                         
                uint32_t    IdleMode       :2;          // bit: 3,4     (RW) Power Management, req/ack control   [see e_IDLEMODE]        
                uint32_t    EmuFree        :1;          // bit: 5       (RW) Sensitivity to emulation (debug) suspend event from Debug Subsystem.
                                                        //              [0x0 = timer_frozen:Timer counter frozen during a debug suspend event.
                                                        //               0x1 = timer_free: Timer counter free-running. Debug suspend event is ignored.]             
                uint32_t                   :2;          // bit: 6,7     (R)  Reserved
                uint32_t    ClockActivity  :2;          // bit: 8,9     (RW) 
                uint32_t                   :22;         // bit: 10..31  (R)  Reserved  
            } b;                                        // Structure used for bit access 
            uint32_t  reg;                              // Type used for register access 
        } TIOCP_CFG_reg_t; 

        enum e_IDLEMODE : uint32_t
        {
            FORCE_IDLE        = 0x0,    // Force-idle. An idle request is acknowledged unconditionally       
            NO_IDLE           = 0x1,    // No-idle. An idle request is never acknowledged
            SMART_IDLE        = 0x2,    // Smart-idle. Acknowledgment to an idle request is given based on the internal activity of the module 
            SMART_IDLE_WAKEUP = 0x3     // Acknowledgment to an idle request is given based on the internal activity of the module. The module
                                        // may generate wakeup events when in idle state
        };

        /* [reset state = 0x0]*/
        typedef union 
        {                                   /* This register provides status information about the module, excluding the interrupt status information */
            struct 
            {                                 
                uint32_t    ResetDone :1;    // bit: 0      (R) 
                uint32_t              :31;   // bit: 1..31  (R) Reserved  
            } b;                             // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } TISTAT_reg_t;   

        /* [reset state = 0x0]*/
        typedef union 
        {                                              /* The Timer Status Register is used to determine which of the timer events requested an interrupt. */
            struct 
            { 
                uint32_t   MAT_IT_FLAG   :1;           // bit: 0        (RW) the compare result of TCRR and TMAR 
                                                       //                    [0x0 = no compare interrupt request; 
                                                       //                     0x1 = compare interrupt pending]
                uint32_t   OVF_IT_FLAG   :1;           // bit: 1        (RW) TCRR overflow
                                                       //                    [0x0 = no overflow interrupt request; 
                                                       //                     0x1 = overflow interrupt pending]
                uint32_t   TCAR_IT_FLAG  :1;           // bit: 2        (RW) indicates when an external pulse transition of the correct polarity is
                                                       //                    detected on the external pin PIEVENTCAPT
                                                       //                    [0x0 = no capture interrupt request; 
                                                       //                     0x1 = capture interrupt request]
                uint32_t                 :29;          // bit: 3..31    (R)  Reserved  
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } TISR_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register controls (enable/disable) the interrupt events */
            struct 
            { 
                uint32_t   MAT_IT_ENA  :1;             // bit: 0       (RW) Enable match interrupt
                                                       //                   [0x0 = Dsb_match : Disable match interrupt; 
                                                       //                    0x1 = Enb_match : Enable match interrupt]
                uint32_t   OVF_IT_ENA  :1;             // bit: 1       (RW) Enable overflow interrupt
                                                       //                   [0x0 = Dsb_ovf : Disable overflow interrupt; 
                                                       //                    0x1 = Enb_ovf : Enable overflow interrupt]
                uint32_t   TCAR_IT_ENA :1;             // bit: 2       (RW) Enable capture interrupt
                                                       //                   [0x0 = Dsb_capt : Disable capture interrupt; 
                                                       //                    0x1 = Enb_capt : Enable capture interrupt]
                uint32_t               :29;            // bit: 3..31   (R)  Reserved  
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } TIER_reg_t; 

        /* [reset state = 0x0]*/
        typedef union 
        {                                              /* This register controls (enable/disable) the wakeup feature on specific interrupt events */
            struct 
            { 
                uint32_t   MAT_WUP_ENA  :1;            // bit: 0       (RW) Enable match wake-up
                                                       //                   [0x0 = DsbWupMat : Disable match wake-up; 
                                                       //                    0x1 = EnbWupMat : Enable match wake-up]
                uint32_t   OVF_WUP_ENA  :1;            // bit: 1       (RW) Enable overflow wake-up
                                                       //                   [0x0 = DsbWupOvf : Disable overflow wake-up; 
                                                       //                    0x1 = EnbWupOvf : Enable overflow wake-up]
                uint32_t   TCAR_WUP_ENA :1;            // bit: 2       (RW) Enable capture wake-up
                                                       //                   [0x0 = DsbWupCap : Disable capture wake-up; 
                                                       //                    0x1 = EnbWupCapt : Enable capture wake-up]
                uint32_t                :29;           // bit: 3..31   (R)  Reserved   
            } b;                                       // Structure used for bit access 
            uint32_t  reg;                             // Type used for register access 
        } TWER_reg_t;   
                       
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register controls optional features specific to the timer functionality */
            struct 
            {                                                               
                uint32_t    ST        :1;             // bit: 0       (RW) automatically reset when the counter is overflowed(if AR = 0) [0x0 = counter is frozen; 0x1 = start timer] 
                uint32_t    AR        :1;             // bit: 1       (RW) Auto-reload mode [0x0 = One shot timer; 0x1 = Auto-reload timer] [see e_DMTIMER_mode] 
                uint32_t    PTV       :3;             // bit: 2..4    (RW) Pre-scale clock Timer value. [see e_DMTIMER_prescaler]
                uint32_t    PRE       :1;             // bit: 5       (RW) enable prescale  [0x0 = TIMER clock input pin clocks; 0x1 = divided input pin clocks] 
                uint32_t    CE        :1;             // bit: 6       (RW) compare mode [0x0 = disabled; 0x1 = enabled] [see e_DMTIMER_mode] 
                uint32_t    SCPWM     :1;             // bit: 7       (RW) Pulse Width Modulation output pin default value 
                                                      //                   [0x0 = clear PORPWM:, sel positive pulse; 
                                                      //                    0x1 = set PORPWM:, sel negative pulse]                   
                uint32_t    TCM       :2;             // bit: 8,9     (RW) Transition Capture Mode on PIEVENTCAPT in  [see e_CAPTURE]           
                uint32_t    TRG       :2;             // bit: 10,11   (RW) Trigger Output Mode on PORTIMERPWM out  [see e_TRIGGER]  
                uint32_t    PT        :1;             // bit: 12      (RW) Pulse or Toggle select bit [0x0 = pulse modulation; 0x1 = toggle modulation] 
                uint32_t    CAPT_MODE :1;             // bit: 13      (RW) Capture mode select bit (first/second)  
                                                      //                   [0x0 = First_capt : Capture the first enabled capture event in TCAR1; 
                                                      //                    0x1 = Sec_capt : Capture the second enabled capture event in TCAR2] 
                uint32_t    GPO_CFG   :1;             // bit: 14      (RW) drives directly the PORGPOCFG out [0x0 = PORGPOCFG->0, timer pin as out; 0x1 = PORGPOCFG->1, timer pin as in]
                uint32_t              :17;            // bit: 15..31  Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TCLR_reg_t;

        enum e_CAPTURE: uint32_t
        {
            CPT_NO_EDGE   = 0x0,    // No capture
            CPT_RISE_EDGE = 0x1,    // Capture on rising edges of PIEVETCAPT
            CPT_FALL_EDGE = 0x2,    // Capture on falling edges of PIEVETCAPT
            CPT_BOTH_EDGE = 0x3     // Reserved
        };

        enum e_TRIGGER: uint32_t
        {
            TRG_NO_TRG      = 0x0,    // No trigger
            TRG_OVF_TRG     = 0x1,    // Overflow trigger
            TRG_OVF_MAT_TRG = 0x2,    // Overflow and match trigger
            TRG_RESERVED    = 0x3     // Capture on booth edges of PIEVETCAPT
        };
    
        enum e_DMTIMER_mode: uint32_t
        {
            MODE_ONESHOT_NOCMP_ENABLE = 0U,
            MODE_AUTORLD_NOCMP_ENABLE = BIT(1),
            MODE_ONESHOT_CMP_ENABLE   = BIT(6),            
            MODE_AUTORLD_CMP_ENABLE   = BIT(1)|BIT(6)   
        };

        enum e_DMTIMER_prescaler: uint32_t
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
        {                                             /* This register holds the value of the internal counter */
            struct 
            {                                          
                uint32_t    TIMER_COUNTER  :32;       // bit: 0..31 (RW) Value of TIMER counter                  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TCRR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register holds the timer's load value */
            struct 
            {                                          
                uint32_t    LOAD_VALUE  :32;          // bit: 0..31 (RW) Timer counter value loaded on overflow in auto-reload mode or on TTGR write access                  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TLDR_reg_t;
    
       /* [reset state = 0xFFFFFFFF]*/
        typedef union 
        {                                             /* This register triggers a counter reload of timer by writing any value in it. */
            struct 
            {   
                uint32_t    TTGR_VALUE  :32;          // bit: 0..31 (RW) Timer counter value loaded on overflow in auto-reload mode or on TTGR write access                  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TTGR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register contains the write posting bits for all writable functional registers */
            struct 
            {                       
                uint32_t    W_PEND_TCLR :1;           // bit: 0  (R) Write pending for register TCLR
                                                      //             [0x0 = CLR_nPend : No Control Register write pending;
                                                      //              0x1 = CLR_Pend : Control Register write pending]
                uint32_t    W_PEND_TCRR :1;           // bit: 1  (R) Write pending for register TCRR
                                                      //             [0x0 = CRR_nPend : No Counter Register write pending;
                                                      //              0x1 = CRR_Pend : Counter Register write pending]
                uint32_t    W_PEND_TLDR :1;           // bit: 2  (R) Write pending for register TLDR
                                                      //             [0x0 = LDR_nPend : No Load Register write pending;
                                                      //              0x1 = LDR_Pend : Load Register write pending]
                uint32_t    W_PEND_TTGR :1;           // bit: 3  (R) Write pending for register TTGR
                                                      //             [0x0 = TGR_nPend : No Trigger Register write pending;
                                                      //              0x1 = TGR_Pend : Trigger Register write pending]
                uint32_t    W_PEND_TMAR :1;           // bit: 4  (R) Write pending for register TMAR
                                                      //             [0x0 = MAR_nPend : No Match Register write pending;
                                                      //              0x1 = MAR_Pend : Match Register write pending]
                uint32_t    W_PEND_TPIR :1;           // bit: 5  (R) Write pending for register TPIR
                                                      //             [0x0 = PIR_nPend : No Positive Increment Register write pending.;
                                                      //              0x1 = PIR_Pend : Positive Increment Register write pending.]
                uint32_t    W_PEND_TNIR :1;           // bit: 6  (R) Write pending for register TNIR
                                                      //             [0x0 = NIR_nPend : No Negativ Increment Register write pending;
                                                      //              0x1 = NIR_Pend : Negativ Increment Register write pending]
                uint32_t    W_PEND_TCVR :1;           // bit: 7  (R) Write pending for register TCVR
                                                      //             [0x0 = CVR_nPend : No Counter Register write pending.;
                                                      //              0x1 = CVR_Pend : Counter Register write pending]
                uint32_t    W_PEND_TOCR :1;           // bit: 8  (R) Write pending for register TOCR
                                                      //             [0x0 = OCR_nPend : No Overflow Counter Register write pending;
                                                      //              0x1 = OCR_Pend : Overflow Counter Register write pending]
                uint32_t    W_PEND_TOWR :1;           // bit: 9  (R) Write pending for register TOWR
                                                      //             [0x0 = OWR_nPend : No Overflow Wrapping Register write pending.;
                                                      //              0x1 = OWR_Pend : Overflow Wrapping Register write pending]
                uint32_t                :22;          // bit: 10..31  Reserved  
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
            F_PEND_TPIR     = BIT(5),
            F_PEND_TNIR     = BIT(6),
            F_PEND_TCVR     = BIT(7),
            F_PEND_TOCR     = BIT(8),
            F_PEND_TOWR     = BIT(9),
            F_PEND_ALL      = 0x3FF  
        };
        
    
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register holds the match value to be compared with the counter's value */
            struct 
            {    
                uint32_t    COMPARE_VALUE  :32;       // bit: 0..31 (RW) Value to be compared to the timer counter             
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TMAR_reg_t;
    
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register holds the value of the first counter register capture */
            struct 
            {   
                uint32_t    CAPTURED_VALUE  :32;      // bit: 0..31  (R) Timer counter value captured on an external event trigger             
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TCAR1_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                        /* Timer Synchronous Interface Control Register */
            struct 
            { 
                uint32_t           :1;           // bit: 0      (R)  Reserved
                uint32_t  SFT      :1;           // bit: 1      (RW) This bit reset all the functional part of the module
                                                 //                  [0x0 = SFT_0 : software reset is disabled;
                                                 //                   0x1 = SFT_1 : software reset is enabled]
                uint32_t  POSTED   :1;           // bit: 2      (RW) [0x0 = Posted mode inactive: will delay the command accept output signal.
                                                 //                   0x1 = Posted mode active (clocks ratio needs to fit freq (timer) less
                                                 //                         than freq (OCP)/4 frequency requirement).]
                uint32_t           :29;          // bit: 3..31  (R)  Reserved  
            } b;                                 // Structure used for bit access 
            uint32_t  reg;                       // Type used for register access 
        } TSICR_reg_t;
        
        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register holds the value of the second counter register capture */
            struct 
            {   
                uint32_t    CAPTURED_VALUE  :32;      // bit: 0..31 (R) Timer counter value captured on an external event trigger             
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TCAR2_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register is used for 1ms tick generation. The TPIR register holds the value of the positive increment.
                                                       * The value of this register is added with the value of the TCVR to define whether next value loaded in
                                                       * TCRR will be the sub-period value or the over-period value. 
                                                       */
            struct 
            { 
                uint32_t  POSITIVE_INC_VALUE   :32;   // bit: 0..31 (RW) The value of the positive increment.   
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TPIR_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register is used for 1ms tick generation. The TNIR register holds the value of the negative increment.
                                                       * The value of this register is added with the value of the TCVR to define whether next value loaded in
                                                       * TCRR will be the sub-period value or the over-period value. 
                                                       */
            struct 
            { 
                uint32_t  NEGATIVE_INC_VALUE  :32;    // bit: 0..31 (RW) The value of the negative increment.  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TNIR_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register is used for 1ms tick generation. The TCVR register defines whether next value loaded in
                                                       * TCRR will be the sub-period value or the over-period value.
                                                       */
            struct 
            { 
                uint32_t  COUNTER_VALUE :32;          // bit: 0..31  (RW) The value of CVR counter. 
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TCVR_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                           /* This register is used to mask the tick interrupt for a selected number of ticks. */
            struct 
            { 
                uint32_t   OVF_COUNTER_VALUE  :24;  // bit: 0..23  (RW) The number of overflow events. 
                uint32_t                      :8;   // bit: 24..31 (R)  Reserved
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } TOCR_reg_t;

        /* [reset state = 0x0]*/
        typedef union 
        {                                             /* This register holds the number of masked overflow interrupts. */
            struct 
            { 
                uint32_t   OVF_WRAPPING_VALUE  :24;   // bit: 0..23  (RW) The number of masked interrupts. 
                uint32_t                       :8;    // bit: 24..31 (R)  Reserved  
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } TOWR_reg_t;
    
        struct AM335x_DMTIMER1MS_Type 
        {                                                                                      
            __R   TIDR_reg_t           TIDR;                  // (0x0)  This register contains the IP revision code
            __R   uint32_t             RESERVED1[3];
            __RW  TIOCP_CFG_reg_t      TIOCP_CFG;             // (0x10)  This register controls the various parameters of the OCP interface
            __R   TISTAT_reg_t         TISTAT;                // (0x14)  This register provides status information about the module, excluding the interrupt status information
            __RW  TISR_reg_t           TISR;                  // (0x18)  The Timer Status Register is used to determine which of the timer events requested an interrupt. 
            __RW  TIER_reg_t           TIER;                  // (0x1C)  This register controls (enable/disable) the interrupt events 
            __RW  TWER_reg_t           TWER;                  // (0x20)  This register controls (enable/disable) the wakeup feature on specific interrupt events
            __RW  TCLR_reg_t           TCLR;                  // (0x24)  This register controls optional features specific to the timer functionality
            __RW  TCRR_reg_t           TCRR;                  // (0x28)  This register holds the value of the internal counter
            __RW  TLDR_reg_t           TLDR;                  // (0x2C)  This register holds the timer's load value
            __RW  TTGR_reg_t           TTGR;                  // (0x30)  This register triggers a counter reload of timer by writing any value in it.
            __R   TWPS_reg_t           TWPS;                  // (0x34)  This register contains the write posting bits for all writable functional registers
            __RW  TMAR_reg_t           TMAR;                  // (0x38)  This register holds the match value to be compared with the counter's value
            __R   TCAR1_reg_t          TCAR1;                 // (0x3C)  This register holds the value of the first counter register capture
            __RW  TSICR_reg_t          TSICR;                 // (0x40)  Timer Synchronous Interface Control Register
            __R   TCAR2_reg_t          TCAR2;                 // (0x44)  This register holds the value of the second counter register capture
            __RW  TPIR_reg_t           TPIR;                  // (0x48)  This register is used for 1ms tick generation.
                                                              //         The TPIR register holds the value of the positiv increment.
                                                              //         The value of this register is added with the value of the
                                                              //         TCVR to define whether next value loaded in TCRR will
                                                              //         be the sub-period value or the over-period value.
            __RW  TNIR_reg_t            TNIR;                 // (0x4C)  This register is used for 1ms tick generation.
                                                              //         The TNIR register holds the value of the negative increment.
                                                              //         The value of this register is added with the value of the
                                                              //         TCVR to define whether next value loaded in TCRR will
                                                              //         be the sub-period value or the over-period value.  
            __RW  TCVR_reg_t            TCVR;                 // (0x50)  This register is used for 1ms tick generation.
                                                              //         The TCVR register defines whether next value loaded in
                                                              //         TCRR will be the sub-period value or the over-period value.
            __RW  TOCR_reg_t            TOCR;                 // (0x54)  This register is used to mask the tick interrupt for a selected number of ticks. 
            __RW  TOWR_reg_t            TOWR;                 // (0x58)  This register holds the number of masked overflow interrupts.                                                                                                            
        };
        
        constexpr uint32_t AM335x_DMTIMER_1MS_BASE = 0x44E31000;    // 1ms timer

        constexpr AM335x_DMTIMER1MS_Type * AM335X_DMTIMER_1MS = ((AM335x_DMTIMER1MS_Type *) AM335x_DMTIMER_1MS_BASE); // only 1ms timer


    }   //namespace DMTIMER1MS

}   //namespace REGS

#endif //__DMTIMER1MS_H