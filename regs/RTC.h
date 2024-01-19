#ifndef __RTC_H
#define __RTC_H

#include <stdint.h>

namespace REGS
{ 
    namespace RTC
    { 
        /* [reset state = 0x0] [offset = 0x]*/
        typedef union 
        {                                 /* The SECONDS_REG is used to program the required seconds value of the current time. Seconds are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. If the seconds value is 45, then the value of SEC0 is 5 and value of SEC1 is 4.  
                                           */
            struct 
            {                                         
                uint32_t    SEC0  :4;      // bit: 0..3     (RW) 1st digit of seconds, Range is 0 to 9  
                uint32_t    SEC1  :3;      // bit: 4..6     (RW) 2nd digit of seconds, Range is 0 to 5 
                uint32_t          :25;     // bit: 1..31    (R)  Reserved             
            } b;                           // Structure used for bit access 
            uint32_t  reg;                 // Type used for register access 
        } SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x4]*/
        typedef union 
        {                                 /* The MINUTES_REG is used to program the minutes value of the current time. Minutes are stored as BCD
                                           * format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. If the
                                           * minutes value is 32, then the value of MIN0 is 2 and value of MIN1 is 3.  
                                           */
            struct 
            {                                         
                uint32_t    MIN0  :4;      // bit: 0..3  (RW) 1st digit of minutes, Range is 0 to 9 
                uint32_t    MIN1  :3;      // bit: 4..6  (RW) 2nd digit of minutes, Range is 0 to 5
                uint32_t          :25;     // bit: 1..31 (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x8]*/
        typedef union 
        {                                 /* The HOURS_REG is used to program the hours value of the current time. Hours are stored as BCD
                                           * format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. In 24Hr
                                           * time mode if you want to set the hour as 18, then HOUR0 is set as 8 and HOUR1 is set as 1.  
                                           */
            struct 
            {                                         
                uint32_t    HOUR0   :4;     // bit: 0..3    (RW) 1st digit of hours, Range is 0 to 9 
                uint32_t    HOUR1   :2;     // bit: 4,5     (RW) 2nd digit of hours, Range is 0 to 2 
                uint32_t            :1;     // bit: 6       (R)  Reserved
                uint32_t    PM_nAM  :1;     // bit: 7       (RW) Only used in PM_AM mode (otherwise 0) [ 0h = AM; 1h = PM]
                uint32_t            :24;    // bit: 8..31   (R)  Reserved             
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } HOURS_reg_t;

        /* [reset state = 0x1] [offset = 0xC]*/
        typedef union 
        {                                 /* The DAYS_REG is used to program the day of the month value of the current date. Days are stored as
                                           * BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. If
                                           * the day value of the date is 28, DAY0 is set as 8 and DAY1 is set as 2. 
                                           */
            struct 
            {                                         
                uint32_t    DAY0  :4;      // bit: 0..3     (RW) 1st digit of days, Range is 0 to 9 
                uint32_t    DAY1  :2;      // bit: 4,5      (RW) 2nd digit of days, Range is 0 to 3
                uint32_t          :26;     // bit: 6..31    (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } DAYS_reg_t;

        /* [reset state = 0x1] [offset = 0x10]*/
        typedef union 
        {                                 /* The MONTHS_REG is used to set the month in the year value of the current date. Months are stored as
                                           * BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent.
                                           * Usual notation is taken for month value: 1 = January, 2 = February, continuing until 12 = December.
                                           */
            struct 
            {                                         
                uint32_t    MONTH0  :4;      // bit: 0..3  (RW) 1st digit of months, Range is 0 to 9
                uint32_t    MONTH1  :1;      // bit: 4     (RW) 2nd digit of months, Range is 0 to 1 
                uint32_t            :27;     // bit: 5..31 (R)  Reserved             
            } b;                             // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x14]*/
        typedef union 
        {                                 /* The YEARS_REG is used to program the year value of the current date. The year value is represented by
                                           * only the last 2 digits and is stored as BCD format. In BCD format, the decimal numbers 0 through 9 are
                                           * encoded with their binary equivalent. The year 1979 is programmed as 79 with YEAR0 set as 9 and
                                           * YEAR1 set as 7.  
                                           */
            struct 
            {                                         
                uint32_t    YEAR0  :4;      // bit: 0..3     (RW) 1st digit of years, Range is 0 to 9 
                uint32_t    YEAR1  :4;      // bit: 4..7     (RW) 2nd digit of years, Range is 0 to 9
                uint32_t           :31;     // bit: 1..31 (R)  Reserved             
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x18]*/
        typedef union 
        {                                 /* The WEEKS_REG is used to program the day of the week value of the current date. The day of the week
                                           * is stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. Sunday is treated as 0, Monday 1, and ending at Saturday with 6.  
                                           */
            struct 
            {                                         
                uint32_t    WEEK  :3;      // bit: 0..2     (RW) 1st digit of days in a week, Range from 0 (Sunday) to 6 (Saturday)
                uint32_t          :29;     // bit: 3..31    (R)  Reserved             
            } b;                           // Structure used for bit access 
            uint32_t  reg;                 // Type used for register access 
        } WEEKS_reg_t;

        /* [reset state = 0x0] [offset = 0x20]*/
        typedef union 
        {                                 /* The ALARM_SECONDS_REG is used to program the second value for the alarm interrupt. Seconds are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARMSEC0  :4;      // bit: 0..3     (RW) 1st digit of seconds, Range is 0 to 9 
                uint32_t    ALARMSEC1  :3;      // bit: 4..6     (RW) 2nd digit of seconds, Range is 0 to 5 
                uint32_t               :25;     // bit: 7..31 (R)  Reserved             
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } ALARM_SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x24]*/
        typedef union 
        {                                 /* The ALARM_MINUTES_REG is used to program the minute value for the alarm interrupt. Minutes are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM_MIN0  :4;      // bit: 0..3     (RW) 1st digit of minutes, Range is 0 to 9 
                uint32_t    ALARM_MIN1  :3;      // bit: 4..6     (RW) 2nd digit of minutes, Range is 0 to 5 
                uint32_t                :25;     // bit: 7..31    (R)  Reserved             
            } b;                                 // Structure used for bit access 
            uint32_t  reg;                       // Type used for register access 
        } ALARM_MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x28]*/
        typedef union 
        {                                 /* The ALARM_HOURS_REG is used to program the hour value for the alarm interrupt. Hours are stored as
                                           * BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM_HOUR0   :4;      // bit: 0..3     (RW) 1st digit of hours, Range is 0 to 9 
                uint32_t    ALARM_HOUR1   :2;      // bit: 4,5      (RW) 2nd digit of hours, Range is 0 to 2
                uint32_t                  :1;      // bit: 6        (R)  Reserved 
                uint32_t    ALARM_PM_nAM  :1;      // bit: 7        (RW) Only used in PM_AM mode (otherwise 0) [0x0 = AM; 0x1 = PM]
                uint32_t                  :24;     // bit: 8..31    (R)  Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } ALARM_HOURS_reg_t;

        /* [reset state = 0x0] [offset = 0x2C]*/
        typedef union 
        {                                 /* The ALARM_DAYS_REG is used to program the day of the month value for the alarm interrupt. Days are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM_DAY0  :4;      // bit: 0..3    (RW) 1st digit for days, Range from 0 to 9 
                uint32_t    ALARM_DAY1  :2;      // bit: 4,5     (RW) 2nd digit for days, Range from 0 to 3
                uint32_t                :26;     // bit: 6..31   (R)  Reserved             
            } b;                                 // Structure used for bit access 
            uint32_t  reg;                       // Type used for register access 
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