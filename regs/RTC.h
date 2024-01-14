#ifndef __RTC_H
#define __RTC_H

#include <stdint.h>

namespace REGS
{ 
    namespace RTC
    { 
        /* [reset state = 0x0] [offset = 0x]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x4]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x8]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } HOURS_reg_t;

        /* [reset state = 0x0] [offset = 0xC]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } DAYS_reg_t;

        /* [reset state = 0x0] [offset = 0x10]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x14]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x18]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } WEEKS_reg_t;

        /* [reset state = 0x0] [offset = 0x20]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x24]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x28]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_HOURS_reg_t;

        /* [reset state = 0x0] [offset = 0x2C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_DAYS_reg_t;

        /* [reset state = 0x0] [offset = 0x30]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x34]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM_YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x40]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_CTRL_reg_t;

        /* [reset state = 0x0] [offset = 0x44]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_STATUS_reg_t;

        /* [reset state = 0x0] [offset = 0x48]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_INTERRUPTS_reg_t;

        /* [reset state = 0x0] [offset = 0x4C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_COMP_LSB_reg_t;

        /* [reset state = 0x0] [offset = 0x50]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_COMP_MSB_reg_t;

        /* [reset state = 0x0] [offset = 0x54]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_OSC_reg_t;

        /* [reset state = 0x0] [offset = 0x60]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_SCRATCH0_reg_t;

        /* [reset state = 0x0] [offset = 0x64]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_SCRATCH1_reg_t;

        /* [reset state = 0x0] [offset = 0x68]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_SCRATCH2_reg_t;

        /* [reset state = 0x0] [offset = 0x6C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } KICK0R_reg_t;

        /* [reset state = 0x0] [offset = 0x70]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } KICK1R_reg_t;

        /* [reset state = 0x0] [offset = 0x74]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_REVISION_reg_t;

        /* [reset state = 0x0] [offset = 0x78]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_SYSCONFIG_reg_t;

        /* [reset state = 0x0] [offset = 0x7C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_IRQWAKEEN_reg_t;

        /* [reset state = 0x0] [offset = 0x80]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x84]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x88]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_HOURS_reg_t;

        /* [reset state = 0x0] [offset = 0x8C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_DAYS_reg_t;

        /* [reset state = 0x0] [offset = 0x90]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x94]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } ALARM2_YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x98]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_PMIC_reg_t;

        /* [reset state = 0x0] [offset = 0x9C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    val  :1;      // bit: 0     (RW) T 
                uint32_t         :31;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_DEBOUNCE_reg_t;
    
        struct AM335x_DMTIMER_Type 
        {                                                                                      
            __RW  SECONDS_reg_t         SECONDS;         // (0x0)  Seconds Register 
            __RW  MINUTES_reg_t         MINUTES;         // (0x4)  Minutes Register 
            __RW  HOURS_reg_t           HOURS;           // (0x8)  Hours Register 
            __RW  DAYS_reg_t            DAYS;            // (0xC)  Day of the Month Register 
            __RW  MONTHS_reg_t          MONTHS;          // (0x10) Month Register
            __RW  YEARS_reg_t           YEARS;           // (0x14) Year Register
            __RW  WEEKS_reg_t           WEEKS;           // (0x18) Day of the Week Register
            __R   uint32_t              RESERVED[1]; 
            __RW  ALARM_SECONDS_reg_t   ALARM_SECONDS;   // (0x20) Alarm Seconds Register 
            __RW  ALARM_MINUTES_reg_t   ALARM_MINUTES;   // (0x24) Alarm Minutes Register 
            __RW  ALARM_HOURS_reg_t     ALARM_HOURS;     // (0x28) Alarm Hours Register
            __RW  ALARM_DAYS_reg_t      ALARM_DAYS;      // (0x2C) Alarm Day of the Month Register 
            __RW  ALARM_MONTHS_reg_t    ALARM_MONTHS;    // (0x30) Alarm Months Register 
            __RW  ALARM_YEARS_reg_t     ALARM_YEARS;     // (0x34) Alarm Years Register
            __R   uint32_t              RESERVED1[2];  
            __RW  RTC_CTRL_reg_t        RTC_CTRL;        // (0x40) Control Register 
            __RW  RTC_STATUS_reg_t      RTC_STATUS;      // (0x44) Status Register 
            __RW  RTC_INTERRUPTS_reg_t  RTC_INTERRUPTS;  // (0x48) Interrupt Enable Register 
            __RW  RTC_COMP_LSB_reg_t    RTC_COMP_LSB;    // (0x4C) Compensation (LSB) Register
            __RW  RTC_COMP_MSB_reg_t    RTC_COMP_MSB;    // (0x50) Compensation (MSB) Register 
            __RW  RTC_OSC_reg_t         RTC_OSC;         // (0x54) Oscillator Register
            __R   uint32_t              RESERVED2[2];  
            __RW  RTC_SCRATCH0_reg_t    RTC_SCRATCH0;    // (0x60) Scratch 0 Register (General-Purpose)
            __RW  RTC_SCRATCH1_reg_t    RTC_SCRATCH1;    // (0x64) Scratch 1 Register (General-Purpose) 
            __RW  RTC_SCRATCH2_reg_t    RTC_SCRATCH2;    // (0x68) Scratch 2 Register (General-Purpose)
            __W  KICK0R_reg_t           KICK0R;          // (0x6C) Kick 0 Register (Write Protect) 
            __W  KICK1R_reg_t           KICK1R;          // (0x70) Kick 1 Register (Write Protect) 
            __R  RTC_REVISION_reg_t     RTC_REVISION;    // (0x74) Revision Register 
            __RW  RTC_SYSCONFIG_reg_t   RTC_SYSCONFIG;   // (0x78) System Configuration Register
            __RW  RTC_IRQWAKEEN_reg_t   RTC_IRQWAKEEN;   // (0x7C) Wakeup Enable Register 
            __RW  ALARM2_SECONDS_reg_t  ALARM2_SECONDS;  // (0x80) Alarm2 Seconds Register
            __RW  ALARM2_MINUTES_reg_t  ALARM2_MINUTES;  // (0x84) Alarm2 Minutes Register 
            __RW  ALARM2_HOURS_reg_t    ALARM2_HOURS;    // (0x88) Alarm2 Hours Register 
            __RW  ALARM2_DAYS_reg_t     ALARM2_DAYS;     // (0x8C) Alarm2 Day of the Month Register 
            __RW  ALARM2_MONTHS_reg_t   ALARM2_MONTHS;   // (0x90) Alarm2 Months Register 
            __RW  ALARM2_YEARS_reg_t    ALARM2_YEARS;    // (0x94) Alarm2 Years Register 
            __RW  RTC_PMIC_reg_t        RTC_PMIC;        // (0x98) RTC PMIC Register 
            __RW  RTC_DEBOUNCE_reg_t    RTC_DEBOUNCE;    // (0x9C) RTC Debounce Register                                                                                             
        };

    }   //namespace RTC

}   //namespace REGS