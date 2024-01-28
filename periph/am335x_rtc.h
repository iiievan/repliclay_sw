#ifndef _AM335X_RTC_H_
#define _AM335X_RTC_H_

#include <stdint.h>
#include "INTC.h"
#include "RTC.hpp"

class am335x_rtc
{
private:
    REGS::RTC::e_12_24_HR_MODE  m_hours_mode;
    REGS::RTC::AM335x_RTC_Type &m_regs;

public:
             am335x_rtc(REGS::RTC::AM335x_RTC_Type *p_rtc_regs);
            ~am335x_rtc() {}

        /******************************************************************************
         **         APIs common to the RTC IPs of both AM1808 and AM335x.
         ******************************************************************************/
        
        /*
         * @brief   This function generally set up RTC module 
         *
         * @param   time  - sets rtc start time    
         * @param   calendar  - sets rtc start date  
         * @param   clksource  - sets type of clk source 32.768k:
         *          REGS::RTC::CLK32K_INTERNAL - selects internal clk source
         *          REGS::RTC::CLK32K_EXTERNAL - selects external clk source (ceramic oscillator)
         *
         * @note    If the application uses RTC, then it should be borne in mind that 
         *          register RTC_OSC_reg_t settings  may affect the DMTIMER_1ms settings if it 
         *          also run from 32768Hz.Шt is necessary that they both use the same clock source (CLK32K_INTERNAL or CLK32K_EXTERNAL) 
         */
       void  setup(REGS::RTC::TIME_t time, REGS::RTC::CALENDAR_t calendar, REGS::RTC::e_32KCLKSOURCE clksource);

        /*
         * @brief    This function sets the 32KHz counter to run.
         */
       void  run();

        /*
         * @brief   This function stops the 32KHz counter.
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete. 
         */
       void  stop();

        /*
         * @brief   This function enables write-protection for RTC registers. 
         *
         * @note    To enable write-protection for RTC registers, the KICK registers
         *          have to be programmed with any value other than their key values. 
         */
       void  write_protect_enable();

        /*
         * @brief   This function disables write-protection for RTC registers. 
         *
         * @note    To disable write-protection for RTC registers, the KICK registers
         *          namely KICK0R and KICK1R have to be programmed with specific key 
         *          values . 
         *          The pre-requisite to write to any RTC registers except KICK  
         *          registers is that the KICK registers have to be programmed with
         *          specific key values mentioned in the RTC peripheral user manual. 
         */
       void  write_protect_disable();

        /*
         * @brief   This function enables ALARM interrupts.
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         *          By ALARM, the functional specification effectively means ALARM1,
         *          although it does not use the name ALARM1. This comes into context
         *          in the RTC IP of AM335x where an ALARM2 feature is also provided.
         */
       void  int_alarm_enable();
       void  int_alarm2_enable();

        /*
         * @brief   This function disables the ALARM interrupts.
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete. 
         */
       void  int_alarm_disable();
       void  int_alarm2_disable();

        /*
         * @brief   This function enables the periodic timer interrupt. 
         *
         * @param   timer_period  This specifies the period between two consecutive 
         *                       interrupts. This can take one of the following values: 
         *                       REGS::RTC::EVERY_SECOND  
         *                       REGS::RTC::EVERY_MINUTE  
         *                       REGS::RTC::EVERY_HOUR    
         *                       REGS::RTC::EVERY_DAY     
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  int_timer_enable(REGS::RTC::e_ISR_PERIOD timer_period);

        /*
         * @brief   This function disables the periodic timer interrupts. 
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  int_timer_disable();

        /*
         * @brief  This function indicates whether or not RTC is busy in updating its
         *         time and calendar registers. 
         *
         * @return The functions returns either of the below two values: 
         *         1> true - indicating that RTC is busy in updating its registers. 
         *         2> false - indicating that RTC is currently free and is not
         *                    updating its registers. 
         */
   bool  busy_status_get() const;

        /*
         * @brief   This function indicates whether RTC is currently running or 
         *          stopped. 
         *
         * @return  This function returns either of the following two values: 
         *          1> true - indicating that RTC is in running state. 
         *          2> false - indicating that RTC is in stopped state. 
         * 
         */
   bool  run_status_get() const;

        /*
         * @brief   This function indicates whether RTC ALARM interrupt has been
         *          generated or not. 
         *
         * @return  This function returns either of the below two values: 
         *          true - indicating that a new ALARM interrupt
         *          has been generated. 
         *          falst - indicating that no new ALARM interrupt
         *          has been generated.  
         * 
         * @note    It is important to invoke the function RTCSAlarmIntStatusClear()
         *          to clear the ALARM interrupt status whenever an ALARM interrupt is  
         *          generated. Otherwise, there is a possibility of the interrupt 
         *          handler being entered again since the previous interrupt's status
         *          was not cleared.   
         */
   bool  alarm_int_status_get() const;
   bool  alarm2_int_status_get() const;

        /*
         * @brief   This function clears the ALARM interrupt's status. 
         *
         */
       void  alarm_int_status_clear();
       void  alarm2_int_status_clear();

        /*
         * @brief   This function determines what registers have been incremented in 
         *          the latest time update. 
         *
         * @return  This function can return one of the following four values: 
         *          1> REGS::RTC::FLG_ONE_SEC_EVENT - when only SECOND register has incremented.  
         *          2> (REGS::RTC::FLG_ONE_SEC_EVENT | REGS::RTC::FLG_ONE_MIN_EVENT) - when both SECOND and 
         *             MINUTE registers have been incremented. 
         *          3> (REGS::RTC::FLG_ONE_SEC_EVENT | REGS::RTC::FLG_ONE_MIN_EVENT | REGS::RTC::FLG_ONE_HR_EVENT) - when 
         *              SECOND, MINUTE and HOUR register have been incremented. 
         *          4> (REGS::RTC::FLG_ONE_SEC_EVENT | REGS::RTC::FLG_ONE_MIN_EVENT | REGS::RTC::FLG_ONE_HR_EVENT | 
         *              REGS::RTC::FLG_ONE_DAY_EVENT) - when SECOND, MINUTE, HOUR and DAY registers 
         *              have been incremented. 
         * 
         */
   REGS::RTC::e_STATUS_EVT_flags  event_update_get();

        /*
         * @brief   This function enables the rounding feature on the current time to 
         *          the nearest minute. 
         *
         */
       void  min_rounding_enable();

        /*
         * @brief  This function disables the rounding feature on the current time
         *         to the nearest minute. 
         *
         */
       void  min_rounding_disable();

        /*
         * @brief   This function enables automatic oscillator compensation mode
         *          for the RTC. 
         */
       void  auto_comp_enable();

        /*
         * @brief   This function disables automatic oscillator compensation mode
         *          for the RTC. 
         */
       void  auto_comp_disable();

        /*
         * @brief   This function configures the representation type for hours for the
         *          RTC as either being 24 hour type or 12 hour type.  
         * 
         * @param   hour_type   Represents the hour mode representation type. This can 
         *                     take one of the two below values:  
         *                     REGS::RTC::MODE_12HR - for 12 hour mode representation. 
         *                     REGS::RTC::MODE_24HR - for 24 hour mode representation.   
         */
       void  hour_mode_set(REGS::RTC::e_12_24_HR_MODE  hour_type);

        /*
         * @brief  This function reads the hour mode representation currently used in RTC. 
         *         The hour mode representation used could either be a 12 hour mode or 
         *         24 hour mode representation.
         *
         * @return This function returns either of the following two macros:
         *         REGS::RTC::MODE_12HR - indicating 12 hour mode of representation.  
         *         REGS::RTC::MODE_24HR - indicating 24 hour mode of representation.  
         */
   REGS::RTC::e_12_24_HR_MODE  hour_mode_get() const;

        /*
         * @brief   This function sets the SET32COUNTER bit in CTRL register.
         *          Setting the SET32COUNTER bit results in the 32KHz counter
         *          getting compensated with the value in the compensation registers.
         *
         * @note    The compensation registers contains the number of 32KHz periods
         *          to be added to the 32KHz counter every hour. This is used to
         *          compensate the oscillator drift.
         */
       void  set_32_counter_enable();

        /*
         * @brief   This function clears the SET32COUNTER bit in CTRL register.
         *          Clearing the SET32COUNTER bit results in the 32KHz counter not
         *          being compensated with the value in the compensation registers.
         *
         * @note    The compensation registers contains the number of 32KHz periods
         *          to be added to the 32KHz counter every hour. This is used to
         *          compensate the oscillator drift.
         */
       void  set_32_counter_disable();

        /*
         * @brief   This function is used to disable the RTC instance. Disabling the
         *          RTC would gate the 32KHz reference clock to the RTC. 
         *
         * @note    This function sets the RTCDISABLE bit in CTRL register. Once this
         *          bit has been set, it should not be cleared again. This function
         *          should only be used when the RTC function is unwanted in the
         *          application. This bit is cleared after a reset and RTC becomes
         *          enabled.  
         */
       void  disable();

        /*
         * @brief  This function enables the RTC. For the RTC IP in AM1808, this
         *         also performs a software reset of the RTC.
         *
         * @note   Registers must not be accessed for three 32-KHz reference
         *         periods after reset is asserted. The application invoking
         *         this API should provide an appropriate delay after this
         *         API's call. 
         */
       void  enable();

        /*
         * @brief   This function indicates whether RTC is disabled or is enabled 
         *          and functional.  
         *
         * @return  This can return one of the two below values:
         *          RTC_ENABLED - indicating that RTC is enabled and is 
         *                        functional.
         *          RTC_DISABLED - indicating that RTC is disabled.
         */
       bool  get_enable_status() const;

        /*
         *  @brief  This function enables the split power feature of RTC and 
         *          in turn enabling the leakage isolation circuitry.
         */
       void  split_pwr_enable();

        /*
         * @brief   This function disables the split power feature of RTC and 
         *          in turn disabling the leakage isolation circuitry.  
         */
       void  split_pwr_disable();

        /*
         * @brief   This function sets the SECOND register with the specified value. 
         *
         * @param   sec_value   The value of 'seconds' to be written to SECOND 
         *                     register. 
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  second_set(uint8_t sec_value);

        /*
         * @brief   This function determines the 'second' value of the current time. 
         *        
         * @return  The value in the SECOND register. 
         */
   uint8_t  second_get() const;

        /*
         * @brief   This function sets the MINUTE register with the specified value. 
         * 
         * @param   min_value  The value of 'minutes' to be written to MINUTE 
         *                    register.   
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */   
       void  minute_set(uint8_t min_value);

        /*
         * @brief   This function determines the minute value of the current time.
         *
         * @return  The value in MINUTE register.
         */       
   uint8_t  minute_get() const;

        /*
         * @brief  This function sets the hour value of the current time. 
         *
         * @param  hour_value  The value of 'hours' to be written into HOURS register. 
         *
         * @note   Programming the HOUR register with the hours value will also modify
         *         the MERIDIEM bit present in the HOUR register. Thus, invoke the  
         *         API \RTCMeridiemSet after invoking this API to set the meridiem 
         *         type.  
         *         If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         */   
       void  hour_set(uint8_t hour_value, REGS::RTC::e_meridiem am_pm);

        /*
         * @brief  This function reads hour value of the current time. 
         *
         * @return The value in the HOUR register. 
         */       
   uint8_t  hour_get() const;

        /*
         * @brief  This function sets the meridiem type for the time that is 
         *         programmed. 
         *
         * @param   meridiem_type  This specifies the meridiem type. This can take one
         *                        of the below two values:  
         *                        REGS::RTC::AM - for ante-meridiem(AM).
         *                        REGS::RTC::PM - for post-meridiem(PM).
         *
         * @note    Programming the type of meridiem is meaningful only when 12-hour
         *          mode of time representation has been opted for. Use RTCHourModeSet()
         *          to do this. 
         *          If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */   
       void  meridiem_set(REGS::RTC::e_meridiem meridiem_type);

        /*
         * @brief   This function determines the meridiem type of the current time. 
         * 
         * @return  The meridiem type of the current time. This will be one of the 
         *          two below values:
         *          REGS::RTC::AM - indicating ante-meridiem(AM).
         *          REGS::RTC::PM - indicating post-meridiem(PM).
         *
         * @note    The meridiem type of the current time should be ignored if the 
         *          time representation is in 24 hour mode format.
         */      
   REGS::RTC::e_meridiem  meridiem_get() const;

        /*
         * @brief  This function sets the day of the month in the relevant register.  
         * 
         * @param  day_value  The 'day_value' value to be written to DAY register. 
         *
         * @note   If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         */   
       void  day_of_month_set(uint8_t day_value);

        /*
         * @brief  This function determines the day of the month currently held by 
         *         relevant RTC register.
         *
         * @return The 'day' value in the DAY register.
         */       
   uint8_t  day_of_month_get() const;

        /*
         * @brief   This function sets the month of the year in the relevant RTC
         *          register. 
         * 
         * @param   month_value  The 'month' value to be written to MONTH regsiter. 
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */   
       void  month_set(uint8_t month_value);

        /*
         * @brief  This function determines the month of the year from the relevant 
         *         RTC register. 
         *
         * @return  The 'month' value in the MONTH register.  
         */
   uint8_t  month_get() const;

        /*
         * @brief   This function sets the year value in the relevant RTC register. 
         *
         * @param   year_value  The 'year' value to be written to YEAR register.   
         *
         * @note    We can program only the last two digits of the four digit year
         *          value. Ex: 87 is programmed for year being 1987.  
         *          If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */   
       void  year_set(uint8_t year_value);

        /*
         * @brief  This function determines the current year value from the relevant
         *         RTC register. 
         * 
         * @return  The 'year' value in the YEAR register. 
         */
   uint8_t  year_get() const;

        /*
         * @brief   This function sets the day of the week in the relevant RTC register. 
         *
         * @param   dotw  The 'day of the week' value to be written to DOTW
         *                     register. This will take one of the following seven
         *                     values:
         *                     REGS::RTC::DOTW_SUN - // indicating Sunday.    // воск 
         *                     REGS::RTC::DOTW_MON - // indicating Monday.    // пн  
         *                     REGS::RTC::DOTW_TUE - // indicating Tuesday.   // вторн  
         *                     REGS::RTC::DOTW_WED - // indicating Wednesday. // ср    
         *                     REGS::RTC::DOTW_THU - // indicating Thursday.  // чтврг  
         *                     REGS::RTC::DOTW_FRI - // indicating Friday.    // пятн 
         *                     REGS::RTC::DOTW_SAT - // indicating Saturday.  // суббота                      
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  day_of_the_week_set(REGS::RTC::e_DOTW dotw);

        /*
         * @brief   This function reads the current day of the week from the relevant
         *          RTC register.
         *
         * @return  The 'day of the week' value in the DOTW register. 
         *          This returns one of the seven values mentioned in the API
         *          \RTCDayOfTheWeekSet.  
         */
   REGS::RTC::e_DOTW  day_of_the_week_get() const;

        /*
         * @brief   This function programs the specified time information in
         *          the Time registers. 
         * 
         * @param   time      The time is specified here and should be in the
         *                    following format: <hours><minutes><seconds><meridiem>. 
         *                    Example - For 12-hour representation mode: 
         *                    If the time is 8 hours, 47 minutes and 31 seconds AM,
         *                    then the 'time' should be
         *                    (0x08473100 | RTC_ANTE_MERIDIEM).  
         *                    For 24-hour representation mode:
         *                    If the time is 19 hours, 53 minutes, 02 seconds, then
         *                    'time' should be (0x19530200).
         *
         * @note    Though this API programs the required time value in the relevant
         *          Time registers of RTC, it does not start the RTC. The API RTCRun()
         *          should be explicitly called later to start the RTC.
         */
       void  time_set(REGS::RTC::TIME_t time);

        /*
         * @brief   This function reads the current time from the registers holding 
         *          time information.   
         *
         * @return  The time in the format: <hours><minutes><seconds><meridiem>.
         */
   REGS::RTC::TIME_t  time_get() const;

        /*
         * @brief  This function sets the specified calendar information in registers 
         *         holding calendar settings.  
         *          
         * @param   calendar  This parameter includes values for day of the month,
         *                    month, year and day of the week. The format is:  
         *                    <day of the month><month><year><day of the week>
         *
         *                    For example, if the date is: 29 November,2010,Monday,then
         *                    the representation would be: 0x29111000 | RTC_DOTW_MON.
         *                   (Nov = 11, 2010 = 10).  
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  calendar_set(REGS::RTC::CALENDAR_t calendar);

        /*
         * @brief   This function reads the calendar information from relevant
         *          registers holding calendar settings.  
         *
         * @return  The calendar information in the format:
         *          <day of the month><month><year><day of the week>.
         */
   REGS::RTC::CALENDAR_t  calendar_get() const;

        /*
         * @brief  This configures the seconds value in the ALARM registers.  
         * 
         * @param  alarm_sec_value  The seconds value to be set in the ALARMSECOND
         *                        registers.   
         *
         * @note   If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         */  
       void  alarm_second_set(uint8_t alarm_sec_value);
       void  alarm2_second_set(uint8_t alarm_sec_value);

        /*
         * @brief  This determines the seconds value being set in the ALARM
         *         registers.  
         *
         * @return The value of seconds being set in the ALARMSECOND register. 
         */
   uint8_t  alarm_second_get() const;
   uint8_t  alarm2_second_get() const;

        /*
         * @brief   This configures the minutes value in the ALARM registers.  
         *
         * @param   alrm_min_value  The minutes value to be written to 
         *                         ALARMMINUTES register.  
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.   
         */
       void  alarm_minute_set(uint8_t alrm_min_value);
       void  alarm2_minute_set(uint8_t alrm_min_value);

        /*
         * @brief   This determines the value of minutes being set in the ALARM
         *          registers.  
         *
         * @return  The value of minutes being set in the ALARMMINUTES register.  
         */
   uint8_t  alarm_minute_get() const;
   uint8_t  alarm2_minute_get() const;

        /*
         * @brief  This sets the value of hours in the ALARM registers.  
         * 
         * @param  alarmhourValue  The value of hours to be written to 
         *                         ALARMHOUR register.  
         * 
         * @note   Programming the ALARMHOUR register with the hours value will also 
         *         modify the MERIDIEM bit present in the ALARMHOUR register.
         *         Thus, invoke the API RTCAlarmHourMeridiemSet() after invoking
         *         the current API to configure the MERIDIEM bit.  
         *         If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         */  
       void  alarm_hour_set(uint8_t alrm_hour_val, REGS::RTC::e_meridiem am_pm);
       void  alarm2_hour_set(uint8_t alrm_hour_val, REGS::RTC::e_meridiem am_pm);

        /*
         * @brief   This determines the value of hours being set in the ALARM
         *          registers.  
         *
         * @return  The value of hours being set in the ALARMHOUR register.  
         */
   uint8_t  alarm_hour_get() const;
   uint8_t  alarm2_hour_get() const;

        /*
         * @brief  This function sets the meridiem type for the ALARM time that is
         *         programmed. 
         *
         * @param   meridiem_type  This specifies the meridiem type. This can take one
         *                        of the below two values:  
         *                        REGS::RTC::AM - for ante-meridiem(AM).
         *                        REGS::RTC::PM - for post-meridiem(PM).
         *
         * @note    Programming the type of meridiem is meaningful only when 12-hour
         *          mode of time representation has been opted for. Use RTCHourModeSet()
         *          to do this.
         *          If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  alarm_hour_meridiem_set(REGS::RTC::e_meridiem meridiem_type);
       void  alarm2_hour_meridiem_set(REGS::RTC::e_meridiem meridiem_type);

        /*
         * @brief   This function determines the meridiem type of the ALARM time.  
         *
         * @return  The meridiem type of the ALARM time. This will be one of the
         *          two below values:
         *          REGS::RTC::AM - indicating ante-meridiem(AM).
         *          REGS::RTC::PM - indicating post-meridiem(PM).
         *
         * @note    The meridiem type of the ALARM time should be ignored if the
         *          time representation is in 24 hour mode format.
         */
   REGS::RTC::e_meridiem  alarm_hour_meridiem_get() const;
   REGS::RTC::e_meridiem  alarm2_hour_meridiem_get() const;

        /*
         * @brief  This function sets the ALARM time regiters with the specified
         *         ALARM time value.  
         *   
         * @param  alarm_time  The time is specified here and should be in the
         *                    following format: <hours><minutes><seconds><meridiem>. 
         *                    Example - For 12-hour mode representation: 
         *                    If the time is 10 hours, 54 minutes and 31 seconds PM,
         *                    then the 'alarm_time' should be
         *                    (0x10543100 | RTC_POST_MERIDIEM).  
         *                    For 24-hour mode representation: 
         *                    If the time is 17 hours, 36 minutes, 41 seconds, then
         *                    'alarm_time' should be (0x17364100). 
         *
         * @note   If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         */
       void  alarm_time_set(REGS::RTC::TIME_t alarm_time);
       void  alarm2_time_set(REGS::RTC::TIME_t alarm_time);

        /*
         * @brief   This function reads the programmed ALARM time from the ALARM
         *          registers.
         *
         * @return  The ALARM time is returned in the format:
         *          <hour><minute><second><meridiem>.
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
   REGS::RTC::TIME_t  alarm_time_get() const;
   REGS::RTC::TIME_t  alarm2_time_get() const;

        /*
         * @brief  This function sets the day of the month in the ALARM registers.  
         * 
         * @param  alarm_day_value The day of the month to be written to ALARMDAY
         *                       register.  
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */   
       void  alarm_day_of_month_set(uint8_t alarm_day_value);
       void  alarm2_day_of_month_set(uint8_t alarm_day_value);

        /*
         * @brief  This function determines the day of the month being set in the
         *         ALARM registers.  
         *
         * @return  The day of the month value set in ALARMDAY register.  
         */
   uint8_t  alarm_day_of_month_get() const;
   uint8_t  alarm2_day_of_month_get() const;

        /*
         * @brief   This function sets the value of the month in the ALARM registers. 
         * 
         * @param   alrm_mnth_val  The value of the month to be written to 
         *                           ALARMMONTH register.  
         *
         * @note    If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         * 
         */  
       void  alarm_month_set(uint8_t alrm_mnth_val);
       void  alarm2_month_set(uint8_t alrm_mnth_val);

        /*
         * @brief  This function determines the value of month being set in the
         *         ALARM registers.   
         * 
         * @return  The value of month being set in the ALARMMONTH register.  
         */
   uint8_t  alarm_month_get() const;
   uint8_t  alarm2_month_get() const;

        /*
         * @brief   This function sets the value of year in the ALARM registers.  
         * 
         * @param   alrm_yr_val  The value of year to be written to ALARMYEAR
         *                          register.  
         *
         * @note    We can program only the last two digits of the four digit year
         *          value. Ex: 87 is programmed for year being 1987.
         *          If the RTC is busy in updating its registers, then this API waits 
         *          until this update is complete.  
         */
       void  alarm_year_set(uint8_t alrm_yr_val);
       void  alarm2_year_set(uint8_t alrm_yr_val);

        /*
         * @brief  This function determines the value of the year being set in the 
         *         ALARM registers.  
         *
         * @return  The value of year being set in the ALARMYEAR register.  
         */      
   uint8_t  alarm_year_get() const;
   uint8_t  alarm2_year_get() const;

        /*
         * @brief  This sets the ALARM calendar registers of the RTC with the specified
         *         ALARM calendar information.  
         * 
         * @param  calendar    This parameter includes values for day of the month,
         *                   month and  year. The format is:  
         *                   <day of the month><month><year>.
         *                   For example, if the ALARM calendar registers are to be
         *                   loaded with a date namely 24 February, 2003, then 
         *                   'calendar' should be 0x24020300(February=0x02, 2003=0x03)  
         * 
         * @note   If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         * 
         */  
       void  alarm_calendar_set(REGS::RTC::CALENDAR_t calendar);
       void  alarm2_calendar_set(REGS::RTC::CALENDAR_t calendar);

        /*
         * @brief   This function reads the ALARM calendar information being set in
         *          the ALARM calendar registers.   
         *
         * @return  The ALARM calendar information read from the ALARM calendar
         *          registers. The format of this information is:
         *          <day of the week><month><year>. 
         */       
   REGS::RTC::CALENDAR_t  alarm_calendar_get() const;
   REGS::RTC::CALENDAR_t  alarm2_calendar_get() const;

        /*
         * @brief  This function sets the compensation registers with the specified
         *         compensation value.  
         * 
         * @param   compensation    The compensation value.
         *
         * @note   Compensation value is subtracted from the 32KHz period. The 
         *         subtraction here is accomplished by two's complement
         *         addititon. Thus the application should pass the two's 
         *         complement value of the value to be subtracted. 
         *         If the RTC is busy in updating its registers, then this API waits 
         *         until this update is complete.  
         * 
         */   
       void  compensation_set(REGS::RTC::COMPENSATION_t compensation);

        /*
         * @brief   This function reads the compensation value being set in the 
         *          compensation registers.  
         *
         * @return  The value in the compensation registers COMPMSB and COMPLSB.
         *
         * @note    This returns the two's complement value of the number to be 
         *          subtracted from 32KHz period. Refer to @note of 
         *          \RTCCompensationSet  API for more details.
         */       
   REGS::RTC::COMPENSATION_t  compensation_get() const;

        /*
         * @brief   This function writes the specified arbitrary value to the specified
         *          scratch register.  
         *  
         * @param   scratch_value  Refers to the value to be written to the scratch 
         *                        registers.  
         *
         */
       void  scratch_pad_set(REGS::RTC::SCRATCH_t scratch_value);

        /*
         * @brief   This function reads the value stored in a specified scratch
         *          register.     
         */       
   REGS::RTC::SCRATCH_t  scratch_pad_get() const;

        /*****************************************************************************
         **  APIs specific to RTC IP of AM1808 and not applicable for that in AM335x.
         *****************************************************************************/
        /*
         * @brief   This function resets the RTC module and registers except
         *          Oscillator(OSC) and KICKnR registers.  
         *
         * @note    1> When the device is initially powered on, the RTC may issue
         *             spurious interrupt signals to the CPU. To avoid issues,
         *             a software reset should be performed on the RTC module before
         *             the CPU interrupt controller is initialized. 
         *
         *          2> Registers must not be accessed for three 32-KHz reference
         *             periods after reset is asserted. The application invoking
         *             this API should provide an appropriate delay after this
         *             API's call. 
         *
         */
       void  software_reset();

        /*****************************************************************************
         **  APIs specific to RTC IP of AM335x and not applicable for that in AM1808.
         *****************************************************************************/
        /*
         * @brief   This API gets the Revision Identity of the RTC Module.
         *
         * @return  The Revision Identity of the RTC Module.
         */
    REGS::RTC::RTC_REVISION_reg_t  revision_ID_get() const;


        /* 
         * @brief This API helps determine the SoC(Platform) in use. 
         */
    uint32_t  version_get(void) const;

        /*
         * @brief   This API configures the Idle Mode for the RTC.
         *
         * @param   mode_flag  This specifies the idle mode that is to be enabled.
         *
         *  'mode_flag' can take one of the following four values:
         * - REGS::RTC::FORCE_IDLE - to enable Force-Idle mode 
         * - REGS::RTC::NO_IDLE - to enable No-Idle mode 
         * - REGS::RTC::SMART_IDLE - to enable Smart-Idle mode 
         * - REGS::RTC::SMART_IDLE_WKUP_CAPABLE - to enable Smart-Idle Wakeup-capable mode 
         */
        void  idle_mode_configure(REGS::RTC::e_RTC_IDLE mode_flag);

        /*
         * @brief  This API is used to control(enable/disable) the feature where
         *         ALARM events can trigger a Wake-up signal to the CPU.
         *
         * @param  control_flag  This specifies whether to enable/disable the feature
         *                       where an Alarm event shall trigger a Wake-Up signal to
         *                       the CPU.
         *
         *  'control_flag' can take one of the following values:
         * - true - to trigger a Wake-Up signal on an Alarm event 
         * - false - to not trigger a Wake-Up signal on an Alarm
         *   event 
         *
         * @note  The ALARM_WAKEEN bit in RTC_IRQWAKEEN register which this API controls,
         *        caters only to ALARM feature and not ALARM2 feature.
         */        
        void  wakeup_alarm_event_control(bool control_flag);

        /*
         * @brief  This API is used to control(enable/disable) the feature where
         *         Timer events can trigger a Wake-Up signal to the CPU.
         * 
         * @param   control_flag  This specifies whether to enable/disable the feature
         *                       where a Timer event shall trigger a Wake-Up signal
         *                       to the CPU.
         *
         *  'control_flag' can take one of the following values:
         * - true - to trigger a Wake-Up signal on a Timer event 
         * - false - to not trigger a Wake-Up signal on a Timer
         *   event 
         */ 
        void  wakeup_timer_event_control(bool control_flag);

        /*
         * @brief   This API controls(enables/disables) the Test mode functionality
         *          of the RTC.
         *
         * @param   control_flag  This specifies whether to enable or disable Test
         *                       Mode functionality
         *
         *  'control_flag' can take one of the following values: 
         * - false - to disable Test Mode and thus enabling
         *   normal functional mode 
         * - true - to enable Test Mode 
         */
        void  test_mode_control(bool control_flag);

        /*
         * @brief  This API selects the clock source for the RTC module.
         *         RTC can be supplied with a 32.768KHz clock either from an
         *         Internal clock source or an External clock source.
         *
         * @param  clk_src_flag  This specifies the RTC Clock source to be selected
         *
         *  'clk_src_flag' can take one of the following two values:
         * - REGS::RTC::CLK32K_INTERNAL - to select the Internal Clock source 
         * - REGS::RTC::CLK32K_EXTERNAL - to select the External Clock source(ceramic oscillator) 
         */        
        void  clk_32k_source_select(REGS::RTC::e_32KCLKSOURCE clk_src_flag);

        /*
         * @brief This API controls(enables/disables) the RTC to receive clocks
         *        from the selected clock source.
         *
         * @param  control_flag  This specifies whether to enable or disable the
         *                      RTC to receive clock inputs from the selected
         *                      clock source.
         *
         *  'control_flag' can take one of the following values:
         * - true - to enable RTC to receive clock inputs 
         * - false - to disable RTC to receive clock inputs 
         *
         * @note  The RTC Clock source(Internal or External) should be selected
         *        using the API RTC32KClkSourceSelect() before invoking this API.
         */        
        void  clk_32k_clock_control(bool control_flag);

        /*
         * @brief This API is used to control(enable/disable) the use of External
         *        Oscillator for RTC.
         *
         * @param  control_flag  This specifies whether to enable or disable the
         *                      use of the External Oscillator for the RTC.
         *
         *  'control_flag' can take one of the following two values:
         * - false - to enable the External Oscillator 
         * - true - to disable the External Oscillator. Disabling
         *   the Oscillator would drive the Oscillator outputs to High Impedance.
         */        
        void  oscillator_state_control(bool control_flag);

        /*
         * @brief  This selects the mode of the Oscillator Feedback resistor.
         *         The Oscillator Feedback resistor could be either external or
         *         internal to the SoC.
         *
         * @param  select_flag   This specifies whether the Oscillator Feedback
         *                      resistor to be used should be either external or
         *                      internal to the SoC.
         *
         *  'select_flag' can take one of the following two values:
         * - false - to select an internal oscillator
         *   feedback resistor for use 
         * - true - to select an external oscillator
         *   feedback resistor for use 
         */        
        void  feedback_resistance_select(bool select_flag);

        /*
         * @brief  This API configures the PMIC power Enable signal
         *
         * @param  select_flag   This specifies whether the PMIC power enable signal has
         *                      to be pulled low or high.
         *
         *  'select_flag' can take one of the following two values:
         * - true - to enable PMIC power 
         * - false - to disable PMIC power 
         */
        void  config_pmic_power_enable(bool select_flag);

        /*
         * @brief  This API configures the Polarity of PMIC External Wakeup pin
         *
         * @param  ext_input     The external Input pin to be configured
         * @param  select_flag   This specifies whether the PMIC External Wakeup Polarity
         *                      to be low or high.
         *
         *  'ext_input' can take values from 0 to 3
         *
         *  'select_flag' can take one of the following two values:
         * - false - to set polarity High 
         * - true  - to set polarity Low 
         */
        void  config_pmic_ext_wake_polarity(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag);

        /*
         * @brief  This API configures the PMIC External Wakeup
         *
         * @param  ext_input     The external Input pin to be configured
         * @param  select_flag   This specifies whether the PMIC External Wakeup
         *                      to be enabled or disabled.
         *
         *  'ext_input' can take values from 0 to 3
         *
         *  'select_flag' can take one of the following two values:
         * - true  - to enable 
         * - false - to disable 
         */

        void  config_pmic_ext_wake(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag);

        /*
         * @brief  This API configures the debounce for PMIC External Wakeup pin
         *
         * @param  ext_input     The external Input pin to be configured
         * @param  select_flag   This specifies whether debounce of External Wakeup pin
         *                      to be enabled or disabled.
         *
         *  'ext_input' can take values from 0 to 3
         *
         *  'select_flag' can take one of the following two values:
         * - true  - to enable 
         * - false - to disable 
         */
        void  config_pmic_ext_wake_debounce(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag);

        /*
         * @brief  This API clears the PMIC External Wakeup Status
         *
         * @param  ext_input     The external Input pin to be configured
         *
         * 'ext_input' can take values from 0 to 3
         */        
        void  pmic_ext_wake_status_clear(REGS::RTC::e_EXT_WAKEUP_IN ext_input);
};

extern am335x_rtc rtc_module;

#endif //_AM335X_RTC_H_
