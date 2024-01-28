#ifndef __RTC_H
#define __RTC_H

#include <stdint.h>

namespace REGS
{ 
    namespace RTC
    { 
        /* [reset state = 0x0] [offset = 0x0]*/
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
                uint32_t    PM_nAM  :1;     // bit: 7       (RW) Only used in PM_AM mode (otherwise 0) [ see e_meridiem ]
                uint32_t            :24;    // bit: 8..31   (R)  Reserved             
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } HOURS_reg_t;

        /* struct for time setting */
        typedef struct 
        {   
            uint32_t              :7;     // bit: 0..6 
            uint32_t    MERIDIEM  :1;     // bit: 7      [ see e_meridiem] 
            uint32_t    SEC       :8;     // bit: 8..15        
            uint32_t    MIN       :8;     // bit: 16..23          
            uint32_t    HOUR      :8;     // bit: 24..31      
        } TIME_t;

        enum e_meridiem : uint8_t
        {
            AM = 0x0,
            PM = 0x1
        };

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
                uint32_t           :24;     // bit: 1..31 (R)  Reserved             
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
                uint32_t    DOTW  :3;      // bit: 0..2     (RW) 1st digit of days in a week, Range from 0 (Sunday) to 6 (Saturday)
                uint32_t          :29;     // bit: 3..31    (R)  Reserved             
            } b;                           // Structure used for bit access 
            uint32_t  reg;                 // Type used for register access 
        } WEEKS_reg_t;

        enum e_DOTW : uint8_t
        {
            DOTW_SUN = 0x0, // indicating Sunday.    // воск 
            DOTW_MON = 0x1, // indicating Monday.    // пн  
            DOTW_TUE = 0x2, // indicating Tuesday.   // вторн  
            DOTW_WED = 0x3, // indicating Wednesday. // ср   
            DOTW_THU = 0x4, // indicating Thursday.  // чтврг  
            DOTW_FRI = 0x5, // indicating Friday.    // пятн 
            DOTW_SAT = 0x6  // indicating Saturday.  // суббота 
        };

        /* struct for calendar setting */
        typedef struct 
        {   
            uint32_t    DOTW      :3;     // bit: 0..2       
            uint32_t              :1;     // bit: 3 
            uint32_t    YEAR      :8;     // bit: 8..15        
            uint32_t    MONTH     :5;     // bit: 16..20 
            uint32_t              :1;     // bit: 21..23         
            uint32_t    DAY       :6;     // bit: 24..29
            uint32_t              :2;     // bit: 30,31      
        } CALENDAR_t;

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
                uint32_t    ALARM_PM_nAM  :1;      // bit: 7        (RW) Only used in PM_AM mode (otherwise 0) [ see e_meridiem ]
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

        /* [reset state = 0x1] [offset = 0x30]*/
        typedef union 
        {                                 /* The ALARM_MONTHS_REG is used to program the month in the year value for the alarm interrupt. The
                                           * month is stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their
                                           * binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM_MONTH0  :4;      // bit: 0..3  (RW) 1st digit of months, Range from 0 to 9 
                uint32_t    ALARM_MONTH1  :1;      // bit: 4     (RW) 2nd digit of months, Range from 0 to 1 
                uint32_t                  :27;     // bit: 5..31 (R)  Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } ALARM_MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x34]*/
        typedef union 
        {                                 /* The ALARM_YEARS_REG is used to program the year for the alarm interrupt. Only the last two digits are
                                           * used to represent the year and is stored as BCD format. In BCD format, the decimal numbers 0 through 9
                                           * are encoded with their binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM_YEAR0  :4;      // bit: 0..3     (RW) 1st digit of years, Range from 0 to 9
                uint32_t    ALARM_YEAR1  :4;      // bit: 4..7     (RW) 2nd digit of years, Range from 0 to 9
                uint32_t                 :24;     // bit: 8..31 (R)  Reserved             
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } ALARM_YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x40]*/
        typedef union 
        {                                 /* The RTC_CTRL_REG contains the controls to enable/disable the RTC, set the 12/24 hour time mode, to
                                           * enable the 30 second rounding feature, and to STOP/START the RTC. The SET_32_COUNTER bit must
                                           * only be used when the RTC is frozen. The RTC_DISABLE bit must only be used to completely disable the
                                           * RTC function. When this bit is set, the 32 kHz clock is gated and the RTC is frozen. From this point,
                                           * resetting this bit to zero can lead to unexpected behavior. This bit should only be used if the RTC function
                                           * is unwanted in the application, in order to save power. MODE_12_24: It is possible to switch between the
                                           * two modes at any time without disturbing the RTC. Read or write is always performed with the current
                                           * mode. Auto compensation is enabled by the AUTO_COMP bit. If the COMP_REG value is positive,
                                           * compensation occurs after the second change event. COMP_REG cycles are removed from the next
                                           * second. If the COMP_REG value is negative, compensation occurs before the second change event.
                                           * COMP_REG cycles are added to the current second. This enables it to compensate with one 32-kHz
                                           * period accuracy each hour. The ROUND_30S bit is a toggle bit; the ARM can only write 1 and the RTC
                                           * clears it. If the ARM sets the ROUND_30S bit and then reads it, the ARM reads 1 until the round-to-theclosest-
                                           * minute is performed at the next second. The ARM can stop the RTC by clearing the STOP_RTC
                                           * bit (owing to internal resynchronization, the RUN bit of the status register (STATUS_REG) must be
                                           * checked to ensure that the RTC is frozen), then update TC values, and re-start the RTC by resetting the
                                           * STOP_RTC bit. 
                                           */
            struct 
            {                                         
                uint32_t    STOP_RTC        :1;      // bit: 0     (RW) Stop the RTC32-kHz counter. [0x0 = RTC is frozen; 0x1 = RTC is running]
                uint32_t    ROUND_30S       :1;      // bit: 1     (RW) Enable one-time rounding to nearest 
                                                     //                 minute on next time register read.
                                                     //                 [0x0 = No update; 0x1 = Time is rounded to the nearest minute]
                uint32_t    AUTO_COMP       :1;      // bit: 2     (RW) Enable oscillator compensation mode. [0x0 = No auto compensation; 0x1 = Auto compensation enabled] 
                uint32_t    MODE_12_24      :1;      // bit: 3     (RW) Enable 12-hour mode for HOURS and ALARMHOURS registers. [0x0 = 24-hr mode; 0x1 = 12-hour mode]
                uint32_t    TEST_MODE       :1;      // bit: 4     (RW) Test mode. 
                                                     //                 [0x0 = Functional mode;
                                                     //                  0x1 = Test mode (Auto compensation is enabled when the 32Khz counter reaches its end)]
                uint32_t    SET_32_COUNTER  :1;      // bit: 5     (RW) Set the 32-kHz counter with the value stored in the compensation registers
                                                     //                 when the SET_32_COUNTER bit is set
                                                     //                  [0x0 = No action.; 
                                                     //                   0x1 = Set the 32Khz counter with compensation registers value]
                uint32_t    RTC_DISABLE     :1;      // bit: 6     (RW) Disable RTC module and gate 32-kHz reference clock.
                                                     //                 [0x0 = RTC enable; 
                                                     //                  0x1 = RTC disable (no 32 kHz clock)]
                uint32_t                    :25;     // bit: 7..31 (R)  Reserved             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } RTC_CTRL_reg_t;

        enum e_12_24_HR_MODE : uint8_t
        {
            MODE_24HR = 0x0,
            MODE_12HR = 0x1,
        };

        /* [reset state = 0x0] [offset = 0x44]*/
        typedef union 
        {                                 /* The RTC_STATUS_REG contains bits that signal the status of interrupts, events to the processor. Status
                                           * for the alarm interrupt and timer events are notified by the register. The alarm interrupt keeps its low level
                                           * until the ARM writes 1 in the ALARM bit of the RTC_STATUS_REG register. ALARM2: This bit will
                                           * indicate the status of the alarm interrupt. Writing a 1 to the bit clears the interrupt. ALARM: This bit will
                                           * indicate the status of the alarm interrupt. Writing a 1 to the bit clears the interrupt. ONE_DAY_EVENT1:
                                           * This bit will indicate if a day event has occurred. An interrupt will be generated to the processor based on
                                           * the masking of the interrupt controller. ONE_HR_EVENT1: This bit will indicate if an hour event has
                                           * occurred. An interrupt will be generated to the processor based on the masking of the interrupt controller.
                                           * ONE_MIN_EVENT1: This bit will indicate if a minute event has occurred. An interrupt will be generated to
                                           * the processor based on the masking of the interrupt controller. ONE_SEC_EVENT1: This bit will indicate if
                                           * a second event has occurred. An interrupt will be generated to the processor based on the masking of the
                                           * interrupt controller. RUN: This bit will indicate if RTC is frozen or it is running. The RUN bit shows the real
                                           * state of the RTC. Indeed, because the STOP_RTC signal is resynchronized on 32-kHz clock the action of
                                           * this bit is delayed. BUSY: This bit will give the status of RTC module. The Time and alarm registers can
                                           * be modified only when this bit is 0. The timer interrupt is a negative edge sensitive low-level pulse (1 OCP
                                           * cycle duration). 
                                           */
            struct 
            {                                         
                uint32_t    BUSY            :1;      // bit: 0     (RW) Status of RTC module.
                                                     //                 [0x0 = Updating event in more than 15 s; 
                                                     //                  0x1 = Updating event] 
                uint32_t    RUN             :1;      // bit: 1     (RW) RTC is frozen or is running.
                                                     //                 [0x0 = RTC is frozen; 
                                                     //                  0x1 = RTC is running] 
                uint32_t    ONE_SEC_EVENT   :1;      // bit: 2     (RW) One second has occurred
                uint32_t    ONE_MIN_EVENT   :1;      // bit: 3     (RW) One minute has occurred
                uint32_t    ONE_HR_EVENT    :1;      // bit: 4     (RW) One hour has occurred
                uint32_t    ONE_DAY_EVENT   :1;      // bit: 5     (RW) One day has occurred
                uint32_t    ALARM           :1;      // bit: 6     (RW) Indicates that an alarm interrupt has been generated
                uint32_t    ALARM2          :1;      // bit: 7     (RW) Indicates that an alarm2 interrupt has been generated.
                                                     //                 Software needs to wait 31 us before it clears this status to allow
                                                     //                 pmic_pwr_enable 1->0 transition.
                uint32_t                    :24;     // bit: 8..31 (R)  Reserved             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } RTC_STATUS_reg_t;

        enum e_STATUS_EVT_flags: uint32_t
        {
            FLG_ONE_SEC_EVENT            = BIT(2),
            FLG_ONE_MIN_EVENT            = BIT(3),
            FLG_ONE_SEC_MIN_EVENT        = BIT(2) | BIT(3),
            FLG_ONE_HR_EVENT             = BIT(4),
            FLG_ONE_SEC_MIN_HR_EVENT     = BIT(2) | BIT(3) | BIT(4),
            FLG_ONE_DAY_EVENT            = BIT(5),
            FLG_ONE_SEC_MIN_HR_DAY_EVENT = BIT(2) | BIT(3) | BIT(4) | BIT(5),      
        };

        /* [reset state = 0x0] [offset = 0x48]*/
        typedef union 
        {                                 /* The RTC_INTERRUPTS_REG is used to enable or disable the RTC from generating interrupts. The timer
                                           * interrupt and alarm interrupt can be controlled using this register. The ARM must respect the BUSY period
                                           * to prevent spurious interrupt. To set a period timer interrupt, the respective period value must be set in the
                                           * EVERY field. For example, to set a periodic timer interrupt for every hour, the EVERY field has to be set
                                           * to 2. Along with this the IT_TIMER bit also has to be set for the periodic interrupt to be generated.
                                           * IT_ALARM bit has to be set to generate an alarm interrupt. 
                                           */
            struct 
            {                                         
                uint32_t    EVERY      :2;      // bit: 0,1     (RW) Interrupt period. [ see e_ISR_PERIOD]
                uint32_t    IT_TIMER   :1;      // bit: 2       (RW) Enable periodic interrupt.
                                                //                  [0x0 = Interrupt disabled; 
                                                //                   0x1 = Interrupt enabled]
                uint32_t    IT_ALARM   :1;      // bit: 3       (RW) Enable one interrupt when the alarm value is reached (TC ALARM
                                                //                   registers) by the TC registers
                uint32_t    IT_ALARM2  :1;      // bit: 4       (RW) Enable one interrupt when the alarm value is reached (TC ALARM2
                                                //                   registers) by the TC registers
                uint32_t               :27;     // bit: 5..31   (R)  Reserved             
            } b;                                // Structure used for bit access 
            uint32_t  reg;                      // Type used for register access 
        } RTC_INTERRUPTS_reg_t;

        enum e_ISR_PERIOD : uint8_t
        {
            EVERY_SECOND    = 0x0, 
            EVERY_MINUTE    = 0x1, 
            EVERY_HOUR      = 0x2,
            EVERY_DAY       = 0x3
        };

        /* [reset state = 0x0] [offset = 0x4C]*/
        typedef union 
        {                                 /* The COMP_LSB_REG is used to program the LSB value of the 32 kHz periods to be added to the 32 kHz
                                           * counter every hour. This is used to compensate the oscillator drift. The COMP_LSB_REG works together
                                           * with the compensation (MSB) register (COMP_MSB_REG). The AUTOCOMP bit in the control register
                                           * (CTRL_REG) must be enabled for compensation to take place. This register must be written in two's
                                           * complement. That means that to add one 32-kHz oscillator period every hour, the ARM must write FFFFh
                                           * into RTC_COMP_MSB_REG and RTC_COMP_LSB_REG. To remove one 32-kHz oscillator period every
                                           * hour, the ARM must write 0001h into RTC_COMP_MSB_REG and RTC_COMP_LSB_REG. The 7FFFh
                                           * value is forbidden. 
                                           */
            struct 
            {                                         
                uint32_t    LSB  :8;      // bit: 0..7     (RW) Indicates number of
                                          //                    32-kHz periods to be added into the
                                          //                    32-kHz counter every hour 
                uint32_t         :24;     // bit: 8..31    (R)  Reserved             
            } b;                 // Structure used for bit access 
            uint32_t  reg;       // Type used for register access 
        } RTC_COMP_LSB_reg_t;

        /* [reset state = 0x0] [offset = 0x50]*/
        typedef union 
        {                                 /* The COMP_LSB_REG is used to program the LSB value of the 32 kHz periods to be added to the 32 kHz
                                           * counter every hour. This is used to compensate the oscillator drift. The COMP_LSB_REG works together
                                           * with the compensation (MSB) register (COMP_MSB_REG). The AUTOCOMP bit in the control register
                                           * (CTRL_REG) must be enabled for compensation to take place. This register must be written in two's
                                           * complement. That means that to add one 32-kHz oscillator period every hour, the ARM must write FFFFh
                                           * into RTC_COMP_MSB_REG and RTC_COMP_LSB_REG. To remove one 32-kHz oscillator period every
                                           * hour, the ARM must write 0001h into RTC_COMP_MSB_REG and RTC_COMP_LSB_REG. The 7FFFh
                                           * value is forbidden. 
                                           */
            struct 
            {                                         
                uint32_t    MSB  :8;      // bit: 0..7     (RW) Indicates number of
                                          //                    32-kHz periods to be added into the
                                          //                    32-kHz counter every hour
                uint32_t         :24;     // bit: 8..31    (R)  Reserved             
            } b;                          // Structure used for bit access 
            uint32_t  reg;                // Type used for register access 
        } RTC_COMP_MSB_reg_t;

        /* type used for compensation */
        typedef union 
        {                                         
            struct 
            {                                         
                uint16_t    LSB  :8;      //
                uint16_t    MSB  :8;      //              
            } m;                          // Structure used for bit access 
            uint16_t  comp;               // Type used for register access 
        } COMPENSATION_t;

        /* [reset state = 0x10] [offset = 0x54]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    SW1             :1;      // bit: 0     (RW) Inverter size adjustment 
                uint32_t    SW2             :1;      // bit: 1     (RW) Inverter size adjustment
                uint32_t    RES_SELECT      :1;      // bit: 2     (RW) External feedback resistor [ 0x0 = Internal; 0x1 = External]
                uint32_t    SEL_32KCLK_SRC  :1;      // bit: 3     (RW) 32-kHz clock source select [ see e_32KCLKSOURCE]
                uint32_t    OSC32K_GZ       :1;      // bit: 4     (RW) Disable the oscillator and apply high impedance to the output 
                                                     //                 [0x0 = Enable; 
                                                     //                  0x1 = Disabled and high impedance]
                uint32_t                    :1;      // bit: 5     (R)  Reserved  
                uint32_t    EN_32KCLK       :1;      // bit: 6     (RW) 32-kHz clock enable post clock mux of rtc_32k_clk_rtc_32k_aux_clk
                                                     //                 and rtc_32k_clk_rtc_32k_clk [ 0x0 = Disable.; 0x1 = Enable.]

                uint32_t                    :25;     // bit: 7..31 (R)  Reserved             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } RTC_OSC_reg_t;

        constexpr uint32_t  OSC_OSC32K_GZ_MSK = 0x00000010u;

        //----- Definition specific to RTC IP in AM1808 ----------
        constexpr uint32_t OSC_SWRESET = 0x00000020u;

        enum e_32KCLKSOURCE : uint8_t
        {
            CLK32K_INTERNAL = 0x0,  // Selects internal clock source, namely rtc_32k_clk_rtc_32k_aux_clk;
            CLK32K_EXTERNAL = 0x1   // Selects external clock source, namely rtc_32k_clk_rtc_32k_clk that is from the 32-kHz oscillator 
        };

        /* [reset state = 0x0] [offset = 0x60]*/
        typedef union 
        {                                         /* The RTC_SCRATCH0_REG is used to hold some required values for the RTC register. */
            struct 
            {                                         
                uint32_t    RTCSCRATCH0  :32;      // bit: 0..31    (RW) Scratch registers, available to program             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } RTC_SCRATCH0_reg_t;

        /* [reset state = 0x0] [offset = 0x64]*/
        typedef union 
        {                                         /* The RTC_SCRATCH1_REG is used to hold some required values for the RTC register. */
            struct 
            {                                         
                uint32_t    RTCSCRATCH1  :32;      // bit: 0..31    (RW) Scratch registers, available to program             
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } RTC_SCRATCH1_reg_t;

        /* [reset state = 0x0] [offset = 0x68]*/
        typedef union 
        {                                 /* The RTC_SCRATCH2_REG is used to hold some required values for the RTC register. */
            struct 
            {                                         
                uint32_t    RTCSCRATCH2  :32;      // bit: 0..31    (RW) Scratch registers, available to program             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } RTC_SCRATCH2_reg_t;

        typedef struct 
        {
            uint32_t SCRATCH0;
            uint32_t SCRATCH1;
            uint32_t SCRATCH2;
        } SCRATCH_t;

        /* [reset state = 0x0] [offset = 0x6C]*/
        typedef union 
        {                                 /* The kick registers (KICKnR) are used to enable and disable write protection on the RTC registers. Out of
                                           *  reset, the RTC registers are write-protected. To disable write protection, correct keys must be written to
                                           *  the KICKnR registers. The Kick0 register allows writing to unlock the kick0 data. To disable RTC register
                                           *  write protection, the value of 83E7 0B13h must be written to KICK0R, followed by the value of 95A4
                                           *  F1E0h written to KICK1R. RTC register write protection is enabled when any value is written to KICK0R. 
                                           */
            struct 
            {                                         
                uint32_t    KICK0  :32;      // bit: 0..31     (W) Kick0 data             
            } b;                             // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } KICK0R_reg_t;

        /* [reset state = 0x0] [offset = 0x70]*/
        typedef union 
        {                                 /* The kick registers (KICKnR) are used to enable and disable write protection on the RTC registers. Out of
                                           *  reset, the RTC registers are write-protected. To disable write protection, correct keys must be written to
                                           *  the KICKnR registers. The Kick1 register allows writing to unlock the kick1 data and the kicker mechanism
                                           *  to write to other MMRs. To disable RTC register write protection, the value of 83E7 0B13h must be written
                                           *  to KICK0R, followed by the value of 95A4 F1E0h written to KICK1R. 
                                           */
            struct 
            {                                         
                uint32_t    KICK1  :32;      // bit: 0..31     (W) Kick1 data             
            } b;                             // Structure used for bit access 
            uint32_t  reg;                   // Type used for register access 
        } KICK1R_reg_t;

        /* [reset state = 0x4EB00904] [offset = 0x74]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    Y_MINOR  :6;      // bit: 0..5      (R) Minor Revision (Y)
                uint32_t    CUSTOM   :2;      // bit: 6,7       (R) Indicates a special version for a particular device
                uint32_t    X_MAJOR  :3;      // bit: 8..10     (R) Major Revision
                uint32_t    R_RTL    :5;      // bit: 11..15    (R) RTL Version (R)
                uint32_t    FUNC     :12;     // bit: 16..27    (R) Function indicates a software compatible module family 
                uint32_t             :2;      // bit: 28,29     (R) Reserved  
                uint32_t    SCHEME   :2;      // bit: 30,31     (R) Used to distinguish between old scheme and current          
            } b;                              // Structure used for bit access 
            uint32_t  reg;                    // Type used for register access 
        } RTC_REVISION_reg_t;

        /* [reset state = 0x2] [offset = 0x78]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    IDLEMODE  :2;      // bit: 0,1       (RW) Configuration of the local target state management mode, By
                                               //                     definition target can handle read/write transaction as 
                                               //                     long as it is out of IDLE state. [see e_RTC_IDLE] 
                uint32_t              :30;     // bit: 2..31     (R) Reserved           
            } b;                              // Structure used for bit access 
            uint32_t  reg;                    // Type used for register access 
        } RTC_SYSCONFIG_reg_t;

        enum e_RTC_IDLE : uint8_t
        {
            FORCE_IDLE              = 0x0,  // local target's idle state follows (acknowledges)
                                            // the system's idle requests unconditionally, i.e., regardless of the IP
                                            // module's internal requirements; Backup mode, for debug only.
            NO_IDLE                 = 0x1,  // local target never enters idle state, Backup
                                            // mode, for debug only.
            SMART_IDLE              = 0x2,  // local target's state eventually follows
                                            // (acknowledges) the system's idle requests, depending on the IP
                                            // module's internal requirements, IP module shall not generate (IRQor
                                            // DMA-request-related) wakeup events.
            SMART_IDLE_WKUP_CAPABLE = 0x3   // local target's idle state
                                            // eventually follows (acknowledges the system's idle requests,
                                            // depending on the IP module's internal requirements, IP module may
                                            // generate (IRQ- or DMA-request-related) wakeup events when in idle
                                            // state.
        };

        /* [reset state = 0x0] [offset = 0x7C]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    TIMER_WAKEEN  :1;      // bit: 0     (RW) Wakeup generation for event Timer. 
                                                   //                 [ 0x0 = Wakeup disabled;
                                                   //                   0x1 = Wakeup enabled]
                uint32_t    ALARM_WAKEEN  :1;      // bit: 1     (RW) Wakeup generation for event Alarm. 
                                                   //                 [ 0x0 = Wakeup disabled;
                                                   //                   0x1 = Wakeup enabled]
                uint32_t                  :30;     // bit: 2..31 (R)  Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } RTC_IRQWAKEEN_reg_t;

        /* [reset state = 0x0] [offset = 0x80]*/
        typedef union 
        {                                 /* The ALARM2_SECONDS_REG is used to program the second value for the alarm2 time. Seconds are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_SEC0  :4;      // bit: 0..3     (RW) 1st digit of seconds, Range is 0 to 9 
                uint32_t    ALARM2_SEC1  :3;      // bit: 4..6     (RW) 2nd digit of seconds, Range is 0 to 5
                uint32_t                 :25;     // bit: 7..31    (R)  Reserved             
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } ALARM2_SECONDS_reg_t;

        /* [reset state = 0x0] [offset = 0x84]*/
        typedef union 
        {                                 /* The ALARM2_MINUTES_REG is used to program the minute value for the alarm2 time. Minutes are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_MIN0  :4;      // bit: 0..3     (RW) 1st digit of minutes, Range is 0 to 9
                uint32_t    ALARM2_MIN1  :3;      // bit: 4..6     (RW) 2nd digit of minutes, Range is 0 to 5 
                uint32_t                 :25;     // bit: 7..31    (R)  Reserved             
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } ALARM2_MINUTES_reg_t;

        /* [reset state = 0x0] [offset = 0x88]*/
        typedef union 
        {                                 /* The ALARM2_HOURS_REG is used to program the hour value for the alarm2 time. Hours are stored as
                                           *BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_HOUR0  :4;      // bit: 0..3    (RW) 1st digit of hours, Range is 0 to 9 
                uint32_t    ALARM2_HOUR1  :2;      // bit: 4,5     (RW) 2nd digit of hours, Range is 0 to 2
                uint32_t                  :1;      // bit: 6       (R)  Reserved 
                uint32_t    ALARM2_PM_nAM :1;      // bit: 7       (RW) Only used in PM_AM mode (otherwise 0) 
                                                   //                 [ see e_meridiem ]
                uint32_t                  :24;     // bit: 8..31   (R)  Reserved            
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } ALARM2_HOURS_reg_t;


        /* [reset state = 0x1] [offset = 0x8C]*/
        typedef union 
        {                                 /* The ALARM2_DAYS_REG is used to program the day of the month value for the alarm2 date. Days are
                                           * stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their binary
                                           * equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_DAY0  :4;      // bit: 0..3     (RW) 1st digit for days, Range from 0 to 9
                uint32_t    ALARM2_DAY1  :2;      // bit: 4,5      (RW) 2nd digit for days, Range from 0 to 3
                uint32_t                 :26;     // bit: 6..31    (R)  Reserved             
            } b;                                  // Structure used for bit access 
            uint32_t  reg;                        // Type used for register access 
        } ALARM2_DAYS_reg_t;

        /* [reset state = 0x1] [offset = 0x90]*/
        typedef union 
        {                                 /* The ALARM2_MONTHS_REG is used to program the month in the year value for the alarm2 date. The
                                           * month is stored as BCD format. In BCD format, the decimal numbers 0 through 9 are encoded with their
                                           * binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_MONTH0  :4;      // bit: 0..3    (RW) 1st digit of months, Range from 0 to 9 
                uint32_t    ALARM2_MONTH1  :1;      // bit: 4       (RW) 2nd digit of months, Range from 0 to 1 
                uint32_t                   :27;     // bit: 5..31   (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } ALARM2_MONTHS_reg_t;

        /* [reset state = 0x0] [offset = 0x94]*/
        typedef union 
        {                                 /* The ALARM2_YEARS_REG is used to program the year for the alarm2 date. Only the last two digits are
                                           * used to represent the year and stored as BCD format. In BCD format, the decimal numbers 0 through 9
                                           * are encoded with their binary equivalent. 
                                           */
            struct 
            {                                         
                uint32_t    ALARM2_YEAR0  :4;      // bit: 0..3     (RW) 1st digit of years, Range from 0 to 9 
                uint32_t    ALARM2_YEAR1  :4;      // bit: 4..7     (RW) 2nd digit of years, Range from 0 to 9 
                uint32_t                  :24;     // bit: 8..31    (R)  Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } ALARM2_YEARS_reg_t;

        /* [reset state = 0x0] [offset = 0x98]*/
        typedef union 
        {                                 /*  */
            struct 
            {                                         
                uint32_t    EXT_WAKEUP_EN      :4;      // bit: 0..3    (RW) Enable external wakeup inputs.
                                                        //                   EXT_WAKEUP_EN[n] controls ext_wakeup[n].
                                                        //                 [ 0x0 = External wakeup disabled.;
                                                        //                   0x1 = External wakeup enabled. ] 
                uint32_t    EXT_WAKEUP_POL     :4;      // bit: 4..7    (RW) External wakeup inputs polarity.
                                                        //                   EXT_WAKEUP_POL[n] controls ext_wakeup[n].
                                                        //                 [ 0x0 = Active high.;
                                                        //                   0x1 = Active low. ]
                uint32_t    EXT_WAKEUP_DB_EN   :4;      // bit: 8..11   (RW) External wakeup debounce enabled.
                                                        //                   EXT_WAKEUP_DB_EN[n] controls ext_wakeup[n].
                                                        //                   When enabled, RTC_DEBOUNCE_REG defines the debounce time.
                                                        //                 [ 0x0 = Disable.;
                                                        //                   0x1 = Enable. ]
                uint32_t    EXT_WAKEUP_STATUS  :4;      // bit: 12..15  (RW) External wakeup status.
                                                        //                   Write 1 to clear EXT_WAKEUP_STATUS[n] status of ext_wakeup[n].
                                                        //                 [ 0x0 = External wakeup event has not occurred.;
                                                        //                   0x1 = External wakeup event has occurred. ]
                uint32_t    PWR_ENABLE_EN      :1;      // bit: 16      (RW) Enable for PMIC_POWER_EN signal.
                                                        //                 [ 0x0 = Disable.;
                                                        //                   When Disabled, pmic_power_en signal will always be driven as 1,
                                                        //                   ON state.
                                                        //                   0x1 = Enable.
                                                        //                   When Enabled: pmic_power_en signal will be controlled by
                                                        //                   ext_wakeup, alarm, and alarm2
                                                        //                   ON -> OFF (Turn OFF) only by ALARM2 event
                                                        //                   OFF -> ON (TURN ON) only by ALARM event OR ext_wakeup
                                                        //                   event. ]
                uint32_t    PWR_ENABLE_SM      :2;      // bit: 17,18   (R)  Power state machine state. [ see e_PWR_STATE_SM]
                uint32_t                       :13;     // bit: 19..31  (R)  Reserved             
            } b;                                        // Structure used for bit access 
            uint32_t  reg;                              // Type used for register access 
        } RTC_PMIC_reg_t;

        enum e_EXT_WAKEUP_IN : uint8_t
        {
            EXT_WKUP0 = 0x0,    // ext_wakeup0 input
            EXT_WKUP1 = 0x1,    // ext_wakeup1 input usually connected to gnd
            EXT_WKUP2 = 0x2,    // ext_wakeup2 input usually connected to gnd
            EXT_WKUP3 = 0x3,    // ext_wakeup3 input usually connected to gnd

        };

        enum e_PWR_STATE_SM : uint8_t
        {
            IDLE_DEFAULT       = 0x0,
            SHTDN              = 0x1, // (ALARM2 and PWR_ENABLE_EN is set to 1). Note: 31 us latency from ALARM2 event).
            TIME_BASED_WKUP    = 0x2, // (ALARM status is set).
            EXT_EVT_BASED_WKUP = 0x3  // (one or more bit set in EXT_WAKEUP_STATUS).
        };

        /* [reset state = 0x0] [offset = 0x9C]*/
        typedef union 
        {                                 /* The debounce timer uses the 32768-Hz clock. It allows choosing the timing or the accuracy of
                                           * debouncing . A register receives a bit from the reference pin. You will choose the timing if you use the
                                           * debouncing like a timer, or you will choose the accuracy if you use the debouncing like a real debouncing.
                                           * The debouncing will be finished when the reference pin will stay the same value (defined in
                                           * DEBOUNCE_REG) for a defined time. 
                                           */
            struct 
            {                                         
                uint32_t    DEBOUNCE_REG  :8;      // bit: 0..7     (RW)  Debounce time.
                                                   //                     A value, n, other than 0 results in a debounce time of 30.52 s*(n+1).
                                                   //                     0h = Debounce time is 30.52 s. 
                uint32_t                  :24;     // bit: 8..31    (R)  Reserved             
            } b;                                   // Structure used for bit access 
            uint32_t  reg;                         // Type used for register access 
        } RTC_DEBOUNCE_reg_t;
    
        struct AM335x_RTC_Type 
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
            __W   KICK0R_reg_t          KICK0R;          // (0x6C) Kick 0 Register (Write Protect) 
            __W   KICK1R_reg_t          KICK1R;          // (0x70) Kick 1 Register (Write Protect) 
            __R   RTC_REVISION_reg_t    RTC_REVISION;    // (0x74) Revision Register 
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

        // used by write_protect_disable() API.
        constexpr uint32_t KICK0R_KEY_DIS = 0x83E70B13u;
        constexpr uint32_t KICK1R_KEY_DIS = 0x95A4F1E0u;

        constexpr uint32_t KICK0_KICK0_KEY_EN = 0xFFFFFFFFu;
        constexpr uint32_t KICK1_KICK1_KEY_EN = 0xFFFFFFFFu;

        // Values that help identify the SoC(Platform) in use.
        constexpr uint32_t REV_AM1808 =  1U;
        constexpr uint32_t REV_AM335X =  2U;

        // Definition specific to RTC IP in AM1808 
        constexpr uint32_t AM1808_CTRL_SPLITPOWER = 0x00000080u;
        constexpr uint32_t    AM1808__OSC_SWRESET = 0x00000020u;

        constexpr uint32_t AM335x_RTC_BASE = 0x44E3E000;

        constexpr AM335x_RTC_Type * AM335X_RTC = ((AM335x_RTC_Type *) AM335x_RTC_BASE);

    }   //namespace RTC

}   //namespace REGS

#endif  //  __RTC_H
