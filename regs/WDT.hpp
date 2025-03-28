#ifndef __WDT_HPP
#define __WDT_HPP

#include <stdint.h>
#include "utils.h"

namespace REGS
{ 
    namespace WDT
    {    
        
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_WATCHDOG_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      


        /* (offset = 0x00) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIDR - Watchdog Identification Register
                                                   * Contains IP revision information
                                                   */
            struct
            {
                uint32_t REVISION       :32;      // bits 0..31     (R)  IP revision identifier
            } b;
            uint32_t reg;
        } WIDR_reg_t;
        
        /* (offset = 0x10) [reset = 0x10] */
        typedef union
        {
                                                  /* WDT_WDSC - Watchdog System Control Register
                                                   * Controls various parameters of the L4 interface
                                                   */
            struct
            {
                uint32_t                : 1;       // bit  0         (R)  Reserved
                uint32_t SOFTRESET      : 1;       // bit  1         (R/W) Software reset control
                                                   //                      Writing 1 initiates software reset
                                                   //                      Reading 1 indicates reset ongoing
                                                   //                      [0x0 = no action/reset done
                                                   //                       0x1 = initiate reset/reset ongoing]
                uint32_t                : 1;       // bit  2         (R)  Reserved
                uint32_t IDLEMODE       : 2;       // bits 3,4       (R/W) Local target state management mode [see e_WDT_IDLEMODE]
                uint32_t EMUFREE        : 1;       // bit  5         (R/W) Emulation suspend sensitivity
                                                   //                      Controls behavior during debug suspend
                                                   //                      [0x0 = timer frozen during debug suspend
                                                   //                       0x1 = timer free-running, ignores suspend]
                uint32_t                :26;       // bits 6..31     (R)  Reserved
            } b;
            uint32_t reg;
        } WDSC_reg_t;
        
        /* Enums for multi-value fields */
        enum e_WDT_IDLEMODE : uint32_t
        {
            /* Configuration of local target state management mode
             * Target handles transactions when not in idle state
             */
            WDT_FORCE_IDLE        = 0x0,    // Force-idle mode: follows system idle requests unconditionally
                                            // Backup mode for debug only

            WDT_NO_IDLE           = 0x1,    // No-idle mode: never enters idle state
                                            // Backup mode for debug only   

            WDT_SMART_IDLE        = 0x2,    // Smart-idle mode: follows system idle requests based on
                                            // internal requirements. No wakeup events generated    

            WDT_SMART_IDLE_WAKEUP = 0x3     // Smart-idle wakeup-capable: follows system idle requests
                                            // based on internal requirements. Can generate wakeup events
                                          
        };
        
        /* (offset = 0x14) [reset = 0x1] */
        typedef union
        {
                                                  /* WDT_WDST - Watchdog Status Register
                                                   * Provides status information about the module
                                                   */
            struct
            {
                uint32_t RESETDONE      : 1;       // bit  0         (R)  Internal reset monitoring
                                                   //                     Indicates reset completion status
                                                   //                     [ 0x0 = reset ongoing
                                                   //                       0x1 = reset completed ]
                uint32_t                :31;       // bits 1..31     (R)  Reserved
            } b;
            uint32_t reg;
        } WDST_reg_t;
        
        /* (offset = 0x18) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WISR - Watchdog Interrupt Status Register
                                                   * Shows pending interrupt events
                                                   */
            struct
            {
                uint32_t OVF_IT_FLAG    : 1;       // bit  0         (R/W) Overflow interrupt status
                                                   //                      Writing 1 clears the status
                                                   //                      [ 0x0 = no interrupt/unchanged
                                                   //                        0x1 = pending/clear status ]
                uint32_t DLY_IT_FLAG    : 1;       // bit  1         (R/W) Delay interrupt status
                                                   //                      Writing 1 clears the status
                                                   //                      [ 0x0 = no interrupt/unchanged
                                                   //                        0x1 = pending/clear status ]
                uint32_t                :30;       // bits 2..31     (R)   Reserved
            } b;
            uint32_t reg;
        } WISR_reg_t;
        
        /* (offset = 0x1C) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIER - Watchdog Interrupt Enable Register
                                                   * Controls interrupt event enable/disable
                                                   */
            struct
            {
                uint32_t OVF_IT_ENA    : 1;       // bit  0         (R/W) Overflow interrupt enable
                                                  //                      [ 0x0 = disable interrupt
                                                  //                        0x1 = enable interrupt]
                uint32_t DLY_IT_ENA    : 1;       // bit  1         (R/W) Delay interrupt enable
                                                  //                      [ 0x0 = disable interrupt
                                                  //                        0x1 = enable interrupt ]
                uint32_t                :30;      // bits 2..31     (R)  Reserved
            } b;
            uint32_t reg;
        } WIER_reg_t;
        
        /* (offset = 0x24) [reset = 0x20] */
        typedef union
        {
                                                  /* WDT_WCLR - Watchdog Control Register
                                                   * Controls the prescaler stage of the counter
                                                   */
            struct
            {
                uint32_t                : 2;       // bits 0,1       (R)  Reserved
                uint32_t PTV            : 3;       // bits 2,3,4     (R/W) Prescaler value
                                                   //                      Timer counter prescaled by 2^PTV
                                                   //                      Example: PTV=3 means counter increments after 8 clock periods
                                                   //                      Reset value loaded from PLPTV_RESET_VALUE input
                uint32_t PRE            : 1;       // bit  5         (R/W) Prescaler enable
                                                   //                      [ 0x0 = prescaler disabled
                                                   //                        0x1 = prescaler enabled ]
                uint32_t                :26;       // bits 6..31     (R)   Reserved
            } b;
            uint32_t reg;
        } WCLR_reg_t;
        
        /* (offset = 0x28) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WCRR - Watchdog Counter Register
                                                   * Holds the value of the internal counter
                                                   */
            struct
            {
                uint32_t TIMER_COUNTER  :32;      // bits 0..31     (R/W) Current timer counter value
            } b;
            uint32_t reg;
        } WCRR_reg_t;
        
        /* (offset = 0x2C) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WLDR - Watchdog Load Register
                                                   * Holds the timer load value
                                                   */
            struct
            {
                uint32_t TIMER_LOAD     :32;      // bits 0..31     (R/W) Timer load register value
            } b;
            uint32_t reg;
        } WLDR_reg_t;
        
        /* (offset = 0x30) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WTGR - Watchdog Trigger Register
                                                   * Writing different value triggers counter reload
                                                   */
            struct
            {
                uint32_t TTGR_VALUE     :32;      // bits 0..31     (R/W) Trigger register value
            } b;
            uint32_t reg;
        } WTGR_reg_t;
        
        /* (offset = 0x34) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WWPS - Watchdog Write Posting Bits Register
                                                   * Contains write posting status for functional registers
                                                   */
            struct
            {
                uint32_t W_PEND_WCLR    : 1;       // bit  0         (R) WCLR write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t W_PEND_WCRR    : 1;       // bit  1         (R) WCRR write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t W_PEND_WLDR    : 1;       // bit  2         (R) WLDR write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t W_PEND_WTGR    : 1;       // bit  3         (R) WTGR write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t W_PEND_WSPR    : 1;       // bit  4         (R) WSPR write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t W_PEND_WDLY    : 1;       // bit  5         (R) WDLY write pending
                                                   //                    [ 0x0 = no write pending
                                                   //                      0x1 = write pending ]
                uint32_t                :26;       // bits 6..31     (R) Reserved
            } b;
            uint32_t reg;
        } WWPS_reg_t;
        
        /* (offset = 0x44) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WDLY - Watchdog Delay Configuration Register
                                                   * Holds delay value for pre-overflow event detection
                                                   */
            struct
            {
                uint32_t WDLY_VALUE     :32;      // bits 0..31     (R/W) Delay register value
            } b;
            uint32_t reg;
        } WDLY_reg_t;
        
        /* (offset = 0x48) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WSPR - Watchdog Start/Stop Register
                                                   * Controls internal start-stop FSM
                                                   */
            struct
            {
                uint32_t WSPR_VALUE     :32;      // bits 0..31     (R/W) Start-stop register value
            } b;
            uint32_t reg;
        } WSPR_reg_t;
        
        /* (offset = 0x54) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIROSTATRAW - Watchdog Raw Interrupt Status Register
                                                   * Shows unmasked interrupt status (debug)
                                                   */
            struct
            {
                uint32_t EVENT_OVF      : 1;       // bit  0         (R/W1S) Raw overflow event
                                                   //                        Status set even if event not enabled
                                                   //                        [ 0x0 = no event/no action
                                                   //                          0x1 = event pending/set event]
                uint32_t EVENT_DLY      : 1;       // bit  1         (R/W1S) Raw delay event
                                                   //                        Status set even if event not enabled
                                                   //                        [ 0x0 = no event/no action
                                                   //                          0x1 = event pending/set event ]
                uint32_t                :30;       // bits 2..31     (R)     Reserved
            } b;
            uint32_t reg;
        } WIRQSTATRAW_reg_t;
        
        /* (offset = 0x58) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIROSTAT - Watchdog Interrupt Status Register
                                                   * Shows masked interrupt status
                                                   */
            struct
            {
                uint32_t EVENT_OVF      : 1;       // bit  0         (R/W1C) Enabled overflow event
                                                   //                        Status not set unless event enabled
                                                   //                        [ 0x0 = no event/no action
                                                   //                          0x1 = event pending/clear event ]
                uint32_t EVENT_DLY      : 1;       // bit  1         (R/W1C) Enabled delay event
                                                   //                        Status not set unless event enabled
                                                   //                        [ 0x0 = no event/no action
                                                   //                          0x1 = event pending/clear event ]
                uint32_t                :30;       // bits 2..31     (R)     Reserved
            } b;
            uint32_t reg;
        } WIRQSTAT_reg_t;
        
        /* (offset = 0x5C) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIRQENSET - Watchdog Interrupt Enable Set Register
                                                   * Enables interrupt events
                                                   */
            struct
            {
                uint32_t ENABLE_OVF     : 1;       // bit  0         (R/W1S) Overflow interrupt enable
                                                   //                        [ 0x0 = no change/disabled
                                                   //                          0x1 = enable interrupt ]
                uint32_t ENABLE_DLY     : 1;       // bit  1         (R/W1S) Delay interrupt enable
                                                   //                        [ 0x0 = no change/disabled
                                                   //                          0x1 = enable interrupt ]
                uint32_t                :30;       // bits 2..31     (R)     Reserved
            } b;
            uint32_t reg;
        } WIRQENSET_reg_t;
        
        /* (offset = 0x60) [reset = 0x0] */
        typedef union
        {
                                                  /* WDT_WIRQENCLR - Watchdog Interrupt Enable Clear Register
                                                   * Disables interrupt events
                                                   */
            struct
            {
                uint32_t ENABLE_OVF     : 1;       // bit  0         (R/W1C) Overflow interrupt disable
                                                   //                        [ 0x0 = no change/enabled
                                                   //                          0x1 = disable interrupt ]
                uint32_t ENABLE_DLY     : 1;       // bit  1         (R/W1C) Delay interrupt disable
                                                   //                        [ 0x0 = no change/enabled
                                                   //                          0x1 = disable interrupt ]
                uint32_t                :30;       // bits 2..31     (R)     Reserved
            } b;
            uint32_t reg;
        } WIRQENCLR_reg_t;


        struct AM335x_WATCHDOG_Type
        {
            __R   WIDR_reg_t         WIDR;                // (0x00) Watchdog Identification Register
            __R   uint32_t           RESERVED1[3];    
            __RW  WDSC_reg_t         WDSC;                // (0x10) Watchdog System Control Register
            __R   WDST_reg_t         WDST;                // (0x14) Watchdog Status Register
            __RW  WISR_reg_t         WISR;                // (0x18) Watchdog Interrupt Status Register
            __RW  WIER_reg_t         WIER;                // (0x1C) Watchdog Interrupt Enable Register
            __R   uint32_t           RESERVED2[1];   
            __RW  WCLR_reg_t         WCLR;                // (0x24) Watchdog Control Register
            __RW  WCRR_reg_t         WCRR;                // (0x28) Watchdog Counter Register
            __RW  WLDR_reg_t         WLDR;                // (0x2C) Watchdog Load Register
            __RW  WTGR_reg_t         WTGR;                // (0x30) Watchdog Trigger Register
            __R   WWPS_reg_t         WWPS;                // (0x34) Watchdog Write Posting Bits Register
            __R   uint32_t           RESERVED3[3];   
            __RW  WDLY_reg_t         WDLY;                // (0x44) Watchdog Delay Configuration Register
            __RW  WSPR_reg_t         WSPR;                // (0x48) Watchdog Start/Stop Register
            __R   uint32_t           RESERVED4[2];   
            __RW  WIRQSTATRAW_reg_t  WIRQSTATRAW;         // (0x54) Watchdog Raw Interrupt Status Register
            __RW  WIRQSTAT_reg_t     WIRQSTAT;            // (0x58) Watchdog Interrupt Status Register
            __RW  WIRQENSET_reg_t    WIRQENSET;           // (0x5C) Watchdog Interrupt Enable Set Register
            __RW  WIRQENCLR_reg_t    WIRQENCLR;           // (0x60) Watchdog Interrupt Enable Clear Register
        };

        constexpr uint32_t AM335x_WDT1_BASE = 0x44E35000;

        constexpr AM335x_WATCHDOG_Type  *AM335x_WDT1 = reinterpret_cast<AM335x_WATCHDOG_Type *>(AM335x_WDT1_BASE);

    }   //namespace WDT

}   //namespace REGS

#endif //__WDT_HPP