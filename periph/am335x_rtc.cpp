#include "am335x_rtc.h"
#include "PRCM.h"
#include "utils.h"

am335x_rtc::am335x_rtc(REGS::RTC::AM335x_RTC_Type *p_rtc_regs)
:m_regs(*p_rtc_regs)
, m_hours_mode(REGS::RTC::MODE_24HR)
{

}

/******************************************************************************
**         APIs common to the RTC IPs of both AM1808 and AM335x.
******************************************************************************/

void  am335x_rtc::setup(REGS::RTC::TIME_t time, REGS::RTC::CALENDAR_t calendar, REGS::RTC::e_32KCLKSOURCE clksource)
{
    REGS::PRCM::run_RTC_clk(); 

    write_protect_disable();
    clk_32k_source_select(clksource); 
    clk_32k_clock_control(true);  // enable recieve clk inputs
    enable();
    
    calendar_set(calendar);
    time_set(time);
    
    run();
    
    //write_protect_enable();
}

void  am335x_rtc::run()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    // BUSY bit in STATUS register should be checked for being low
    // only when RTC is running. The current function is invoked when
    // RTC is stopped. Thus, BUSY status need not be checked.
    
    //HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_RUN | split_power);

    // Setting the RUN bit in CTRL register.
    m_regs.RTC_CTRL.b.STOP_RTC = HIGH;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::stop()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());
     
    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);
    //HWREG(baseAdd + RTC_CTRL) |= split_power;

    // Clearing the RUN bit in CTRL register.    
    m_regs.RTC_CTRL.b.STOP_RTC = LOW;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::write_protect_enable()
{
    //HWREG(baseAdd + RTC_KICK0) = RTC_KICK0_KICK0;
    //HWREG(baseAdd + RTC_KICK1) = RTC_KICK1_KICK1;
    
    // Writing a random value into KICK registers.
    m_regs.KICK0R.reg = REGS::RTC::KICK0_KICK0_KEY_EN;
    m_regs.KICK1R.reg = REGS::RTC::KICK1_KICK1_KEY_EN;
}

void  am335x_rtc::write_protect_disable()
{
    //HWREG(baseAdd + RTC_KICK0) = RTC_KICK0R_KEY;
    //HWREG(baseAdd + RTC_KICK1) = RTC_KICK1R_KEY;

    m_regs.KICK0R.reg = REGS::RTC::KICK0R_KEY_DIS;
    m_regs.KICK1R.reg = REGS::RTC::KICK1R_KEY_DIS;
}

void  am335x_rtc::int_alarm_enable()
{
    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());
        
    //HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_ALARM;
    m_regs.RTC_INTERRUPTS.b.IT_ALARM = HIGH;
}

void  am335x_rtc::int_alarm2_enable()
{
    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());

    //HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_ALARM2;
    m_regs.RTC_INTERRUPTS.b.IT_ALARM2 = HIGH;

}

void  am335x_rtc::int_alarm_disable()
{
    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());
    //HWREG(baseAdd + RTC_INTERRUPT) &= ~(RTC_INTERRUPTS_ALARM);
    m_regs.RTC_INTERRUPTS.b.IT_ALARM = LOW;
}

void  am335x_rtc::int_alarm2_disable()
{
    while(busy_status_get());

    m_regs.RTC_INTERRUPTS.b.IT_ALARM2 = LOW;
}

void  am335x_rtc::int_timer_enable(REGS::RTC::e_ISR_PERIOD timer_period)
{
    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.    
    while(busy_status_get());

    //HWREG(baseAdd + RTC_INTERRUPT) |= RTC_INTERRUPTS_TIMER;
    //HWREG(baseAdd + RTC_INTERRUPT) |= (timer_period & RTC_INTERRUPTS_EVERY);
    m_regs.RTC_INTERRUPTS.b.IT_TIMER = HIGH;
    m_regs.RTC_INTERRUPTS.b.EVERY = timer_period;
}

void  am335x_rtc::int_timer_disable()
{
    // Writing to INTERRUPT register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get()); 
    //HWREG(baseAdd + RTC_INTERRUPT) &= ~(RTC_INTERRUPTS_TIMER);
    m_regs.RTC_INTERRUPTS.b.IT_TIMER = LOW;  
}

bool  am335x_rtc::busy_status_get() const
{
    //return(HWREG(baseAdd + RTC_STATUS) & (RTC_STATUS_BUSY));
    return (bool)(m_regs.RTC_STATUS.b.BUSY); 
}

bool  am335x_rtc::run_status_get() const
{
    //return(HWREG(baseAdd + RTC_STATUS) & RTC_STATUS_RUN);
    return (bool)(m_regs.RTC_STATUS.b.RUN);
}

bool  am335x_rtc::alarm_int_status_get() const
{
    //return(HWREG(baseAdd + RTC_STATUS) & RTC_STATUS_ALARM);
    return (bool)(m_regs.RTC_STATUS.b.ALARM);
}

bool  am335x_rtc::alarm2_int_status_get() const
{
    return (bool)m_regs.RTC_STATUS.b.ALARM2;
}

void  am335x_rtc::alarm_int_status_clear()
{
    //HWREG(baseAdd + RTC_STATUS) |= RTC_STATUS_ALARM;

    // Writing logic 1 to the ALARM bit in STATUS register clears the ALARM
    // interrupt status.
    m_regs.RTC_STATUS.b.ALARM |= HIGH;
}

void  am335x_rtc::alarm2_int_status_clear()
{
    m_regs.RTC_STATUS.b.ALARM2 |= HIGH;;
}

REGS::RTC::e_STATUS_EVT_flags  am335x_rtc::event_update_get()
{
    /*
    return(HWREG(baseAdd + RTC_STATUS) & (RTC_STATUS_DAYEVT |
                                          RTC_STATUS_HREVT |
                                          RTC_STATUS_MINEVT |
                                          RTC_STATUS_SECEVT));
    */
    return (REGS::RTC::e_STATUS_EVT_flags)(m_regs.RTC_STATUS.reg & (REGS::RTC::FLG_ONE_SEC_MIN_HR_DAY_EVENT));
}

void  am335x_rtc::min_rounding_enable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    // Writing to any bit in CTRL register except for SET32COUNTER bit does 
    // not require BUSY bit in STATUS register to be low.
    //HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_ROUNDMIN | split_power);
    m_regs.RTC_CTRL.b.ROUND_30S = HIGH;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::min_rounding_disable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    // Writing to any bit in CTRL register except for SET32COUNTER bit does
    // not require BUSY bit in STATUS register to be low.
    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_ROUNDMIN);
    //HWREG(baseAdd + RTC_CTRL) |= split_power;
    m_regs.RTC_CTRL.b.ROUND_30S = LOW;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::auto_comp_enable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    //HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_AUTOCOMP | split_power);
    
    // Writing to any bit in CTRL register except for SET32COUNTER bit does
    // not require BUSY bit in STATUS register to be low.
    m_regs.RTC_CTRL.b.AUTO_COMP = HIGH;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::auto_comp_disable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_AUTOCOMP);
    //HWREG(baseAdd + RTC_CTRL) |= split_power;

    // Writing to any bit in CTRL register except for SET32COUNTER bit does
    // not require BUSY bit in STATUS register to be low.    
    m_regs.RTC_CTRL.b.AUTO_COMP = LOW;
    m_regs.RTC_CTRL.reg |= split_power;
}

void  am335x_rtc::hour_mode_set(REGS::RTC::e_12_24_HR_MODE hour_type)
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    switch(hour_type)
    {
        case REGS::RTC::MODE_12HR:            
            //HWREG(baseAdd + RTC_CTRL) |= (RTC_12HOUR_MODE | split_power);
            m_regs.RTC_CTRL.b.MODE_12_24 = HIGH;
            m_regs.RTC_CTRL.reg |= split_power;
        break;
   
        case REGS::RTC::MODE_24HR:
        default:    
            //HWREG(baseAdd + RTC_CTRL) |= (RTC_24HOUR_MODE | split_power);
            m_regs.RTC_CTRL.b.MODE_12_24 = LOW;
            m_regs.RTC_CTRL.reg |= split_power;
        break;
    }
}
 
REGS::RTC::e_12_24_HR_MODE  am335x_rtc::hour_mode_get() const
{
    //return(HWREG(baseAdd + RTC_CTRL) & (RTC_12HOUR_MODE));
    return (REGS::RTC::e_12_24_HR_MODE)(m_regs.RTC_CTRL.b.MODE_12_24);
}
 
void  am335x_rtc::set_32_counter_enable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }
    
    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);
    //HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_SET32COUNTER | split_power);
    //HWREG(baseAdd + RTC_CTRL) |= RTC_CTRL_RUN;
 
    // Modifying the SET_32_COUNTER bit in CTRL register requires that RTC
    // is frozen. Clearing the CTRL[0] bit.
    m_regs.RTC_CTRL.b.STOP_RTC = LOW;

    // Setting the SET_32_COUNTER bit in CTRL register.
    m_regs.RTC_CTRL.b.SET_32_COUNTER = HIGH;
    m_regs.RTC_CTRL.reg |= split_power;
    
    // Setting the RTC 32KHz Counter to run i.e. setting CTRL[0] to 1.
    m_regs.RTC_CTRL.b.STOP_RTC = HIGH;
}
 
void  am335x_rtc::set_32_counter_disable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RUN);
    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_SET32COUNTER);
    //HWREG(baseAdd + RTC_CTRL) |= split_power;
    //HWREG(baseAdd + RTC_CTRL) |= RTC_CTRL_RUN;
    
    // Modifying the SET_32_COUNTER bit in CTRL register requires that RTC
    // is frozen. Clearing the CTRL[0] bit.
    m_regs.RTC_CTRL.b.STOP_RTC = LOW;

    // Clearing the SET_32_COUNTER bit in CTRL register.
    m_regs.RTC_CTRL.b.SET_32_COUNTER = LOW;
    m_regs.RTC_CTRL.reg |= split_power;

    // Setting the RTC 32KHz Counter to run i.e. setting CTRL[0] to 1.
    m_regs.RTC_CTRL.b.STOP_RTC = HIGH; 
}
 
void  am335x_rtc::disable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }

    //HWREG(baseAdd + RTC_CTRL) |= (RTC_CTRL_RTCDISABLE | split_power);
    
    // Writing to any bit in CTRL register except for SET32COUNTER bit does
    // not require BUSY bit in STATUS register to be low.
    m_regs.RTC_CTRL.b.RTC_DISABLE = HIGH;
    m_regs.RTC_CTRL.reg |= split_power;
}
 
void  am335x_rtc::enable()
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
        //HWREG(baseAdd + RTC_OSC) |= RTC_OSC_SWRESET;
        m_regs.RTC_OSC.reg |= REGS::RTC::OSC_SWRESET;
    }

    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_RTCDISABLE);
    //HWREG(baseAdd + RTC_CTRL) |= split_power;
    m_regs.RTC_CTRL.b.RTC_DISABLE = LOW;
    m_regs.RTC_CTRL.reg |= split_power;
}
 
bool  am335x_rtc::get_enable_status() const
{
   // return(HWREG(baseAdd + RTC_CTRL) & (RTC_CTRL_RTCDISABLE));
    return (bool)(m_regs.RTC_CTRL.b.RTC_DISABLE);
}
 
void  am335x_rtc::split_pwr_enable()
{
    //HWREG(baseAdd + RTC_CTRL) |= REGS::RTC::AM1808_CTRL_SPLITPOWER;
    m_regs.RTC_CTRL.reg |= REGS::RTC::AM1808_CTRL_SPLITPOWER;
}
 
void  am335x_rtc::split_pwr_disable()
{
    //HWREG(baseAdd + RTC_CTRL) &= ~(REGS::RTC::AM1808_CTRL_SPLITPOWER);
    m_regs.RTC_CTRL.reg &= ~REGS::RTC::AM1808_CTRL_SPLITPOWER;
}
 
void  am335x_rtc::second_set(uint8_t sec_value)
{
    REGS::RTC::SECONDS_reg_t seconds;
    uint8_t sec_raw = ((sec_value > 59) ? 00: sec_value);    
    
    seconds.b.SEC0 = sec_raw%10;
    seconds.b.SEC1  = (sec_raw/10)%10;

    // Writing to SECOND register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get()); 
    
    //HWREG(baseAdd + RTC_SECOND) = (sec_value & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)); 
    
    // Writing least 7 bits of 'sec_value' into SECOND register.
    m_regs.SECONDS.reg = seconds.reg;
}
 
uint8_t  am335x_rtc::second_get() const
{
    //return(HWREG(baseAdd + RTC_SECOND) & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)); 

    uint8_t result  = m_regs.SECONDS.b.SEC0;

    result += m_regs.SECONDS.b.SEC1*10;

    return result;
}
 
void  am335x_rtc::minute_set(uint8_t min_value)
{
    REGS::RTC::MINUTES_reg_t minutes;
    uint8_t min_raw = ((min_value > 59) ? 00: min_value);    
    
    minutes.b.MIN0 = min_raw%10;
    minutes.b.MIN1  = (min_raw/10)%10;

    // Writing to MINUTE register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    //HWREG(baseAdd + RTC_MINUTE) = (min_value & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0));
    
    // Writing least 7 bits of 'min_value' into MINUTE register.
    m_regs.MINUTES.reg = minutes.reg;
}
 
uint8_t  am335x_rtc::minute_get() const
{
    //return(HWREG(baseAdd + RTC_MINUTE) & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0));

    uint8_t result  = m_regs.MINUTES.b.MIN0;

    result += m_regs.MINUTES.b.MIN1*10;

    return result;
}
 
void  am335x_rtc::hour_set(uint8_t hour_value, REGS::RTC::e_meridiem am_pm)
{
    REGS::RTC::HOURS_reg_t hours;
    uint8_t hr_raw = ((hour_value > 23) ? 00: hour_value);    
    
    hours.b.HOUR0 = hr_raw%10;
    hours.b.HOUR1  = (hr_raw/10)%10;

    if(m_hours_mode == REGS::RTC::MODE_12HR)
    {
        hours.b.PM_nAM = (am_pm == REGS::RTC::AM)? 0x0 : 0x1;
    }

    // Writing to HOUR register requires that BUSY bit in STATUS register
    // is low.    
    while(busy_status_get());

    //HWREG(baseAdd + RTC_HOUR) = (hour_value & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0));
    
    // Writing least 6 bits of 'hourValue' into HOUR register.
    m_regs.HOURS.reg = hours.reg;
}
 
uint8_t  am335x_rtc::hour_get() const
{
    //return(HWREG(baseAdd + RTC_HOUR) & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0));

    uint8_t result  = m_regs.HOURS.b.HOUR0;

    result += m_regs.HOURS.b.HOUR1*10;

    return result;
}
 
void  am335x_rtc::meridiem_set(REGS::RTC::e_meridiem meridiem_type)
{
    // Writing to HOUR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
    
    // Set the MERIDIEM bit in HOUR register.
    //HWREG(baseAdd + RTC_HOUR) |= (meridiem_type & RTC_HOUR_MERIDIEM);
    m_regs.HOURS.b.PM_nAM = meridiem_type;
}
 
REGS::RTC::e_meridiem  am335x_rtc::meridiem_get() const
{
    //return(HWREG(baseAdd + RTC_HOUR) & RTC_HOUR_MERIDIEM);
    return (REGS::RTC::e_meridiem)(m_regs.HOURS.b.PM_nAM);
}
 
void  am335x_rtc::day_of_month_set(uint8_t day_value)
{
    REGS::RTC::DAYS_reg_t days;
    uint8_t day_raw = ((day_value > 31) ? 00: day_value);    
    
    days.b.DAY0 =  day_raw%10;
    days.b.DAY1 = (day_raw/10)%10;

    // Writing to DAY register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    //HWREG(baseAdd + RTC_DAY) = (day_value & (RTC_DAY_DAY1 | RTC_DAY_DAY0)); 
    
    // Writing least 6 bits of 'day_value' to DAY register.
    m_regs.DAYS.reg = days.reg;
}
 
uint8_t  am335x_rtc::day_of_month_get() const
{
    //return(HWREG(baseAdd + RTC_DAY) & (RTC_DAY_DAY1 | RTC_DAY_DAY0));
    uint8_t result  = m_regs.DAYS.b.DAY0;

    result += m_regs.DAYS.b.DAY1*10;

    return result;
}
 
void  am335x_rtc::month_set(uint8_t month_value)
{
    REGS::RTC::MONTHS_reg_t month;
    uint8_t month_raw = ((month_value > 12) ? 00: month_value);    
    
    month.b.MONTH0 =  month_raw%10;
    month.b.MONTH1 = (month_raw/10)%10;

    // Writing to MONTH register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());

    //HWREG(baseAdd + RTC_MONTH) = (month_value & (RTC_MONTH_MONTH1 | RTC_MONTH_MONTH0));
    
    // Writing least 5 bits of 'month_value' into MONTH register.
    m_regs.MONTHS.reg = month.reg;
}
 
uint8_t  am335x_rtc::month_get() const
{
    //return(HWREG(baseAdd + RTC_MONTH) & (RTC_MONTH_MONTH1 | RTC_MONTH_MONTH0));

    uint8_t result  = m_regs.MONTHS.b.MONTH0;

    result += m_regs.MONTHS.b.MONTH1*10;

    return result;    
}
 
void  am335x_rtc::year_set(uint8_t year_value)
{
    REGS::RTC::YEARS_reg_t year;
    uint8_t year_raw = ((year_value > 99) ? 00: year_value);    
    
    year.b.YEAR0 =  year_raw%10;
    year.b.YEAR1 = (year_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low.  
    while(busy_status_get());

    //HWREG(baseAdd + RTC_YEAR) = (year_value & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0));
    
    // Write least 8 bits of 'year_value' to YEAR register.
    m_regs.YEARS.reg = year.reg;
}
 
uint8_t  am335x_rtc::year_get() const
{
    //return(HWREG(baseAdd + RTC_YEAR) & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0));

    uint8_t result  = m_regs.YEARS.b.YEAR0;

    result += m_regs.YEARS.b.YEAR1*10;

    return result;
}
 
void  am335x_rtc::day_of_the_week_set(REGS::RTC::e_DOTW dotw)
{ 
    // Writing to DOTW register requires that BUSY bit in STATUS register
    // is low.  
    while(busy_status_get());
    
    //HWREG(baseAdd + RTC_DOTW) = (week_value & RTC_DOTW_DOTW);
    
    // Write least 3 bits of 'week_value' to DOTW register.
    m_regs.WEEKS.b.DOTW = dotw;
}
 
REGS::RTC::e_DOTW  am335x_rtc::day_of_the_week_get() const
{
    //return(HWREG(baseAdd + RTC_DOTW) & RTC_DOTW_DOTW);
    return (REGS::RTC::e_DOTW)(m_regs.WEEKS.b.DOTW);
}
 
void  am335x_rtc::time_set(REGS::RTC::TIME_t time)
{
    volatile uint32_t split_power = 0;

    if(REGS::RTC::REV_AM1808 == version_get())
    {
        split_power = REGS::RTC::AM1808_CTRL_SPLITPOWER;
    }
    
    // Stop the RTC.
    m_regs.RTC_CTRL.b.STOP_RTC = LOW;
    
    // Enable split power mode.
    m_regs.RTC_CTRL.reg |= split_power;

    // Writing to SECOND register.
    second_set((uint8_t)time.SEC);
    
    // Writing to MINUTE register.
    minute_set((uint8_t)time.MIN);

    // Writing to HOUR register.
    hour_set((uint8_t)time.HOUR, (REGS::RTC::e_meridiem)time.MERIDIEM);

}
 
REGS::RTC::TIME_t  am335x_rtc::time_get() const
{
    //uint32_t sec = 0, min = 0, hour = 0, mer = 0;
    REGS::RTC::TIME_t result;

    // Reading MERIDIEM bit in HOUR register.
    result.MERIDIEM = meridiem_get();
    // Reading from SECOND register.
    result.SEC      = second_get();
    // Reading from MINUTE register.
    result.MIN      = minute_get();
    // Reading from HOUR register.
    result.HOUR     = hour_get();

/*
    sec = HWREG(baseAdd + RTC_SECOND);
    sec = (sec & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)) << SECOND_SHIFT;
    min = HWREG(baseAdd +  RTC_MINUTE);
    min = (min & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0)) << MINUTE_SHIFT;
    hour = HWREG(baseAdd + RTC_HOUR);
    hour = (hour & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0)) << HOUR_SHIFT;
    mer = (HWREG(baseAdd + RTC_HOUR) & RTC_HOUR_MERIDIEM);
    return ( sec | min | hour | mer);          
*/ 
    return result;
}
 
void  am335x_rtc::calendar_set(REGS::RTC::CALENDAR_t calendar)
{     
    while(busy_status_get());

    //HWREG(baseAdd + RTC_YEAR) = (calendar & YEAR_MASK) >> YEAR_SHIFT;
    //HWREG(baseAdd + RTC_MONTH) = (calendar & MONTH_MASK) >> MONTH_SHIFT;
    //HWREG(baseAdd + RTC_DAY) = (calendar & DAY_MASK) >> DAY_SHIFT;
    //HWREG(baseAdd + RTC_DOTW) = (calendar & DOTW_MASK);

    // Writing to YEAR register.
    year_set(calendar.YEAR);
    // Writing to MONTH register.
    month_set(calendar.MONTH);
    // Writing to DAY register.
    day_of_month_set(calendar.DAY);
    // Writing to DOTW register.
    day_of_the_week_set((REGS::RTC::e_DOTW)calendar.DOTW);

}
 
REGS::RTC::CALENDAR_t  am335x_rtc::calendar_get() const
{
    REGS::RTC::CALENDAR_t result;
    //uint32_t cal_val = 0;
    //cal_val = (HWREG(baseAdd + RTC_DAY) & (RTC_DAY_DAY1 | RTC_DAY_DAY0)) << DAY_SHIFT;
    //cal_val |= (HWREG(baseAdd + RTC_MONTH) & (RTC_MONTH_MONTH1 | RTC_MONTH_MONTH0)) << MONTH_SHIFT;
    //cal_val |= (HWREG(baseAdd + RTC_YEAR) & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0))  << YEAR_SHIFT;
    //cal_val |= (HWREG(baseAdd + RTC_DOTW) & RTC_DOTW_DOTW);
    
    // Reading from the DAY register.
    result.DAY = day_of_month_get();

    // Reading from MONTH register.
    result.MONTH = month_get();

    // Reading from YEAR register.
    result.YEAR = year_get();

    // Reading from DOTW register.
    result.DOTW = day_of_the_week_get();

    //return cal_val;
    return result;
}
 
void  am335x_rtc::alarm_second_set(uint8_t alarm_sec_value)
{
    REGS::RTC::ALARM_SECONDS_reg_t al_sec;
    uint8_t al_sec_raw = ((alarm_sec_value > 59) ? 00: alarm_sec_value);    
    
    al_sec.b.ALARMSEC0 = al_sec_raw%10;
    al_sec.b.ALARMSEC1  = (al_sec_raw/10)%10;

    // Writing to ALARMSECOND register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMSECOND) = (alarmSecValue & (RTC_ALARMSECOND_SEC1 | RTC_ALARMSECOND_SEC0));
    
    // Writing least 7 bits of 'alarmsecValue' to ALARMSECOND register.
    m_regs.ALARM_SECONDS.reg = al_sec.reg;
}

void  am335x_rtc::alarm2_second_set(uint8_t alarm_sec_value)
{
    REGS::RTC::ALARM2_SECONDS_reg_t al_sec;
    uint8_t al_sec_raw = ((alarm_sec_value > 59) ? 00: alarm_sec_value);    
    
    al_sec.b.ALARM2_SEC0 = al_sec_raw%10;
    al_sec.b.ALARM2_SEC1  = (al_sec_raw/10)%10;

    // Writing to ALARMSECOND register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    // Writing least 7 bits of 'alarmsecValue' to ALARMSECOND register.
    m_regs.ALARM2_SECONDS.reg = al_sec.reg;
}
 
uint8_t  am335x_rtc::alarm_second_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMSECOND) & (RTC_ALARMSECOND_SEC1 | RTC_ALARMSECOND_SEC0));

    uint8_t result  = m_regs.ALARM_SECONDS.b.ALARMSEC0;

    result += m_regs.ALARM_SECONDS.b.ALARMSEC1*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_second_get() const
{
    uint8_t result  = m_regs.ALARM2_SECONDS.b.ALARM2_SEC0;

    result += m_regs.ALARM2_SECONDS.b.ALARM2_SEC1*10;

    return result;
}
 
void  am335x_rtc::alarm_minute_set(uint8_t alrm_min_value)
{
    REGS::RTC::ALARM_MINUTES_reg_t al_minutes;
    uint8_t al_min_raw = ((alrm_min_value > 59) ? 00: alrm_min_value);    
    
    al_minutes.b.ALARM_MIN0 = al_min_raw%10;
    al_minutes.b.ALARM_MIN1  = (al_min_raw/10)%10;

    // Writing to ALARMMINUTE register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMMINUTE) = (alrmMinValue & (RTC_ALARMMINUTE_MIN1 | RTC_ALARMMINUTE_MIN0));
    
    // Write least 7 bits to ALARMMINUTE register.
    m_regs.ALARM_MINUTES.reg = al_minutes.reg;
}

void  am335x_rtc::alarm2_minute_set(uint8_t alrm_min_value)
{
    REGS::RTC::ALARM2_MINUTES_reg_t al_minutes;
    uint8_t al_min_raw = ((alrm_min_value > 59) ? 00: alrm_min_value);    
    
    al_minutes.b.ALARM2_MIN0 = al_min_raw%10;
    al_minutes.b.ALARM2_MIN1  = (al_min_raw/10)%10;

    // Writing to ALARMMINUTE register requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());

    // Write least 7 bits to ALARMMINUTE register.
    m_regs.ALARM2_MINUTES.reg = al_minutes.reg;
}
 
uint8_t  am335x_rtc::alarm_minute_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMMINUTE) & (RTC_ALARMMINUTE_MIN1 | RTC_ALARMMINUTE_MIN0));
    uint8_t result  = m_regs.ALARM_MINUTES.b.ALARM_MIN0;

    result += m_regs.ALARM_MINUTES.b.ALARM_MIN1*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_minute_get() const
{
    uint8_t result  = m_regs.ALARM2_MINUTES.b.ALARM2_MIN0;

    result += m_regs.ALARM2_MINUTES.b.ALARM2_MIN1*10;

    return result;
}
 
void  am335x_rtc::alarm_hour_set(uint8_t alrm_hour_val, REGS::RTC::e_meridiem am_pm)
{
    REGS::RTC::ALARM_HOURS_reg_t al_hours;
    uint8_t al_hr_raw = ((alrm_hour_val > 23) ? 00: alrm_hour_val);    
    
    al_hours.b.ALARM_HOUR0 = al_hr_raw%10;
    al_hours.b.ALARM_HOUR1  = (al_hr_raw/10)%10;

    if(m_hours_mode == REGS::RTC::MODE_12HR)
    {
        al_hours.b.ALARM_PM_nAM = (am_pm == REGS::RTC::AM) ? 0x0 : 0x1;
    }

    // Writing to ALARMHOUR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMHOUR) = (alrmHourVal & (RTC_ALARMHOUR_HOUR1 | RTC_ALARMHOUR_HOUR0));
    
    // Writing the least 6 bits of 'alrmHourVal' to the ALARMHOUR 
    // register.
    m_regs.ALARM_HOURS.reg = al_hours.reg;
}

void  am335x_rtc::alarm2_hour_set(uint8_t alrm_hour_val, REGS::RTC::e_meridiem am_pm)
{
    REGS::RTC::ALARM2_HOURS_reg_t al_hours;
    uint8_t al_hr_raw = ((alrm_hour_val > 23) ? 00: alrm_hour_val);    
    
    al_hours.b.ALARM2_HOUR0 = al_hr_raw%10;
    al_hours.b.ALARM2_HOUR1  = (al_hr_raw/10)%10;

    if(m_hours_mode == REGS::RTC::MODE_12HR)
    {
        al_hours.b.ALARM2_PM_nAM = (am_pm == REGS::RTC::AM) ? 0x0 : 0x1;
    }

    // Writing to ALARMHOUR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    // Writing the least 6 bits of 'alrmHourVal' to the ALARMHOUR 
    // register.
    m_regs.ALARM2_HOURS.reg = al_hours.reg;
}
 
uint8_t  am335x_rtc::alarm_hour_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMHOUR) & (RTC_ALARMHOUR_HOUR1 | RTC_ALARMHOUR_HOUR0));

    uint8_t result  = m_regs.ALARM_HOURS.b.ALARM_HOUR0;

    result += m_regs.ALARM_HOURS.b.ALARM_HOUR1*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_hour_get() const
{
    uint8_t result  = m_regs.ALARM2_HOURS.b.ALARM2_HOUR0;

    result += m_regs.ALARM2_HOURS.b.ALARM2_HOUR1*10;

    return result;
}
 
void  am335x_rtc::alarm_hour_meridiem_set(REGS::RTC::e_meridiem meridiem_type)
{
    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMHOUR) |= (meridiemType & RTC_ALARMHOUR_MERIDIEM);
    
    // Set the MERIDIEM bit in ALARMHOUR register.
    m_regs.ALARM_HOURS.b.ALARM_PM_nAM = meridiem_type;
}

void  am335x_rtc::alarm2_hour_meridiem_set(REGS::RTC::e_meridiem meridiem_type)
{
    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
    
    // Set the MERIDIEM bit in ALARMHOUR register.
    m_regs.ALARM2_HOURS.b.ALARM2_PM_nAM = meridiem_type;
}
 
REGS::RTC::e_meridiem  am335x_rtc::alarm_hour_meridiem_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMHOUR) & RTC_HOUR_MERIDIEM);
    return (REGS::RTC::e_meridiem)(m_regs.ALARM_HOURS.b.ALARM_PM_nAM);
}

REGS::RTC::e_meridiem  am335x_rtc::alarm2_hour_meridiem_get() const
{
    return (REGS::RTC::e_meridiem)(m_regs.ALARM2_HOURS.b.ALARM2_PM_nAM);
}
 
void  am335x_rtc::alarm_time_set(REGS::RTC::TIME_t alarm_time)
{
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMSECOND) = (alarm_time & SECOND_MASK) >> SECOND_SHIFT;
    //HWREG(baseAdd + RTC_ALARMMINUTE) = (alarm_time & MINUTE_MASK) >> MINUTE_SHIFT;
    //HWREG(baseAdd + RTC_ALARMHOUR) = (((alarm_time & HOUR_MASK) >> HOUR_SHIFT) | (alarm_time & MERIDIEM_MASK));
    
    // Writing to ALARMSECOND register.
    alarm_second_set((uint8_t)alarm_time.SEC);

    // Writing to ALARMMINUTE register.
    alarm_minute_set((uint8_t)alarm_time.MIN);

    // Writing to ALARMHOUR register.
    alarm_hour_set((uint8_t)alarm_time.HOUR, (REGS::RTC::e_meridiem)alarm_time.MERIDIEM);
}

void  am335x_rtc::alarm2_time_set(REGS::RTC::TIME_t alarm_time)
{
    while(busy_status_get());

   // Writing to ALARMSECOND register.
    alarm2_second_set((uint8_t)alarm_time.SEC);

    // Writing to ALARMMINUTE register.
    alarm2_minute_set((uint8_t)alarm_time.MIN);

    // Writing to ALARMHOUR register.
    alarm2_hour_set((uint8_t)alarm_time.HOUR, (REGS::RTC::e_meridiem)alarm_time.MERIDIEM);
}
 
REGS::RTC::TIME_t  am335x_rtc::alarm_time_get() const
{
    //uint32_t alrm_sec = 0, alrm_min = 0, alrm_hour = 0, alrm_mer = 0;
   REGS::RTC::TIME_t result;
    while(busy_status_get());

    //alrm_sec = HWREG(baseAdd + RTC_ALARMSECOND);
    //alrm_sec = (alrm_sec & (RTC_SECOND_SEC1 | RTC_SECOND_SEC0)) << SECOND_SHIFT;
    //alrm_min = HWREG(baseAdd +  RTC_ALARMMINUTE);
    //alrm_min = (alrm_min & (RTC_MINUTE_MIN1 | RTC_MINUTE_MIN0)) << MINUTE_SHIFT;
    //alrm_hour = HWREG(baseAdd + RTC_ALARMHOUR);
    //alrm_hour = (alrm_hour & (RTC_HOUR_HOUR1 | RTC_HOUR_HOUR0)) << HOUR_SHIFT;
    //alrm_mer = (HWREG(baseAdd + RTC_ALARMHOUR) & RTC_HOUR_MERIDIEM);      
    //return ( alrm_sec | alrm_min | alrm_hour | alrm_mer); 
    
    // Reading from ALARMSECOND register.
    result.SEC      = alarm_second_get();

    // Reading from ALARMMINUTE register.
    result.MIN      = alarm_minute_get();

    // Reading from ALARMHOUR register.
    result.HOUR     = alarm_hour_get();

    // Reading MERIDIEM bit in ALARMHOUR register.
    result.MERIDIEM = alarm_hour_meridiem_get();
    
    return result; 
}

REGS::RTC::TIME_t  am335x_rtc::alarm2_time_get() const
{
    //uint32_t alrm_sec = 0, alrm_min = 0, alrm_hour = 0, alrm_mer = 0;
   REGS::RTC::TIME_t result;
    while(busy_status_get());
    
    // Reading from ALARMSECOND register.
    result.SEC      = alarm2_second_get();

    // Reading from ALARMMINUTE register.
    result.MIN      = alarm2_minute_get();

    // Reading from ALARMHOUR register.
    result.HOUR     = alarm2_hour_get();

    // Reading MERIDIEM bit in ALARMHOUR register.
    result.MERIDIEM = alarm_hour_meridiem_get();
    
    return result;
}
 
void  am335x_rtc::alarm_day_of_month_set(uint8_t alarm_day_value)
{
    REGS::RTC::ALARM_DAYS_reg_t al_day;
    uint8_t al_day_raw = ((alarm_day_value > 31) ? 00: alarm_day_value);    
    
    al_day.b.ALARM_DAY0 =  al_day_raw%10;
    al_day.b.ALARM_DAY1 = (al_day_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low.    
    while(busy_status_get());
 
    //HWREG(baseAdd + RTC_ALARMDAY) = (alarmDayValue & (RTC_ALARMDAY_DAY1 | RTC_ALARMDAY_DAY0));
    
    // Writing the least 6 bits of 'alarm_day_value' to ALARMHOUR register.
    m_regs.ALARM_DAYS.reg = al_day.reg;
}

void  am335x_rtc::alarm2_day_of_month_set(uint8_t alarm_day_value)
{
    REGS::RTC::ALARM2_DAYS_reg_t al_day;
    uint8_t al_day_raw = ((alarm_day_value > 31) ? 00: alarm_day_value);    
    
    al_day.b.ALARM2_DAY0 =  al_day_raw%10;
    al_day.b.ALARM2_DAY1 = (al_day_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low.    
    while(busy_status_get());
 
    // Writing the least 6 bits of 'alarm_day_value' to ALARMHOUR register.
    m_regs.ALARM2_DAYS.reg = al_day.reg;
}
 
uint8_t  am335x_rtc::alarm_day_of_month_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMDAY) & (RTC_ALARMDAY_DAY1 | RTC_ALARMDAY_DAY0));
    uint8_t result  = m_regs.ALARM_DAYS.b.ALARM_DAY0;

    result += m_regs.ALARM_DAYS.b.ALARM_DAY0*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_day_of_month_get() const
{
    uint8_t result  = m_regs.ALARM2_DAYS.b.ALARM2_DAY0;

    result += m_regs.ALARM2_DAYS.b.ALARM2_DAY0*10;

    return result;
}
 
void  am335x_rtc::alarm_month_set(uint8_t alrm_mnth_val)
{
    REGS::RTC::ALARM_MONTHS_reg_t al_month;
    uint8_t al_month_raw = ((alrm_mnth_val > 12) ? 00: alrm_mnth_val);    
    
    al_month.b.ALARM_MONTH0 =  al_month_raw%10;
    al_month.b.ALARM_MONTH1 = (al_month_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
   
    //HWREG(baseAdd + RTC_ALARMMONTH) = (alrmMnthVal & (RTC_ALARMMONTH_MONTH1 | RTC_ALARMMONTH_MONTH0));
    
    // Writing the least 6 bits of 'alrmMnthVal' to ALARMHOUR register.
    m_regs.ALARM_MONTHS.reg = al_month.reg;
}

void  am335x_rtc::alarm2_month_set(uint8_t alrm_mnth_val)
{
    REGS::RTC::ALARM2_MONTHS_reg_t al_month;
    uint8_t al_month_raw = ((alrm_mnth_val > 12) ? 00: alrm_mnth_val);    
    
    al_month.b.ALARM2_MONTH0 =  al_month_raw%10;
    al_month.b.ALARM2_MONTH1 = (al_month_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
   
    // Writing the least 6 bits of 'alrmMnthVal' to ALARMHOUR register.
    m_regs.ALARM2_MONTHS.reg = al_month.reg;
}
 
uint8_t  am335x_rtc::alarm_month_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMMONTH) & (RTC_ALARMMONTH_MONTH1 | RTC_ALARMMONTH_MONTH0));
    uint8_t result  = m_regs.ALARM_MONTHS.b.ALARM_MONTH0;

    result += m_regs.ALARM_MONTHS.b.ALARM_MONTH1*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_month_get() const
{
    uint8_t result  = m_regs.ALARM2_MONTHS.b.ALARM2_MONTH0;

    result += m_regs.ALARM2_MONTHS.b.ALARM2_MONTH1*10;

    return result;
}
 
void  am335x_rtc::alarm_year_set(uint8_t alrm_yr_val)
{
    REGS::RTC::ALARM_YEARS_reg_t al_year;
    uint8_t al_year_raw = ((alrm_yr_val > 99) ? 00: alrm_yr_val);    
    
    al_year.b.ALARM_YEAR0 =  al_year_raw%10;
    al_year.b.ALARM_YEAR1 = (al_year_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
    
    //HWREG(baseAdd + RTC_ALARMYEAR) = (alrm_yr_val & (RTC_ALARMYEAR_YEAR1 | RTC_ALARMYEAR_YEAR0));
    
    // Writing the least 8 bits of 'alrm_yr_val' to ALARMYEAR register.
    m_regs.ALARM_YEARS.reg = al_year.reg;
}

void  am335x_rtc::alarm2_year_set(uint8_t alrm_yr_val)
{
    REGS::RTC::ALARM2_YEARS_reg_t al_year;
    uint8_t al_year_raw = ((alrm_yr_val > 99) ? 00: alrm_yr_val);    
    
    al_year.b.ALARM2_YEAR0 =  al_year_raw%10;
    al_year.b.ALARM2_YEAR1 = (al_year_raw/10)%10;

    // Writing to YEAR register requires that BUSY bit in STATUS register
    // is low. 
    while(busy_status_get());
     
    // Writing the least 8 bits of 'alrm_yr_val' to ALARMYEAR register.
    m_regs.ALARM2_YEARS.reg = al_year.reg;
}
 
uint8_t  am335x_rtc::alarm_year_get() const
{
    //return(HWREG(baseAdd + RTC_ALARMYEAR) & (RTC_ALARMYEAR_YEAR1 | RTC_ALARMYEAR_YEAR0));

    uint8_t result  = m_regs.ALARM_YEARS.b.ALARM_YEAR0;

    result += m_regs.ALARM_YEARS.b.ALARM_YEAR1*10;

    return result;
}

uint8_t  am335x_rtc::alarm2_year_get() const
{
    uint8_t result  = m_regs.ALARM2_YEARS.b.ALARM2_YEAR0;

    result += m_regs.ALARM2_YEARS.b.ALARM2_YEAR1*10;

    return result;
}
 
void  am335x_rtc::alarm_calendar_set(REGS::RTC::CALENDAR_t calendar)
{
    while(busy_status_get());

    //HWREG(baseAdd + RTC_ALARMYEAR) = (cal_val & YEAR_MASK) >> YEAR_SHIFT;
    //HWREG(baseAdd + RTC_ALARMMONTH) = (cal_val & MONTH_MASK) >> MONTH_SHIFT;
    //HWREG(baseAdd + RTC_ALARMDAY) = (cal_val & DAY_MASK) >> DAY_SHIFT;
    
    // Writing to ALARMYEAR register.
    alarm_year_set(calendar.YEAR);

    // Writing to ALARMMONTH register.
    alarm_month_set(calendar.MONTH);

    // Writing to ALARMDAY register.
    alarm_day_of_month_set(calendar.DAY);
}

void  am335x_rtc::alarm2_calendar_set(REGS::RTC::CALENDAR_t calendar)
{
    while(busy_status_get());
    
    // Writing to ALARMYEAR register.
    alarm2_year_set(calendar.YEAR);

    // Writing to ALARMMONTH register.
    alarm2_month_set(calendar.MONTH);

    // Writing to ALARMDAY register.
    alarm2_day_of_month_set(calendar.DAY);
}
 
REGS::RTC::CALENDAR_t  am335x_rtc::alarm_calendar_get() const
{
    //uint32_t cal_val = 0;
    REGS::RTC::CALENDAR_t result;
    
    //cal_val = (HWREG(baseAdd + RTC_ALARMDAY) & (RTC_DAY_DAY1 | RTC_DAY_DAY0)) << DAY_SHIFT;
    //cal_val |= (HWREG(baseAdd + RTC_ALARMMONTH) & (RTC_MONTH_MONTH1 | RTC_MONTH_MONTH0)) << MONTH_SHIFT;
    //cal_val |= (HWREG(baseAdd + RTC_ALARMYEAR) & (RTC_YEAR_YEAR1 | RTC_YEAR_YEAR0)) << YEAR_SHIFT;
    
    // Reading from the ALARMDAY register.
    result.DAY = alarm_day_of_month_get();

    // Reading from ALARMMONTH register.
    result.MONTH = alarm_month_get();

    // Reading from ALARMYEAR register.
    result.YEAR = alarm_year_get();

    //return cal_val;
    return result;
}

REGS::RTC::CALENDAR_t  am335x_rtc::alarm2_calendar_get() const
{
    //uint32_t cal_val = 0;
    REGS::RTC::CALENDAR_t result;
        
    // Reading from the ALARMDAY register.
    result.DAY = alarm2_day_of_month_get();

    // Reading from ALARMMONTH register.
    result.MONTH = alarm2_month_get();

    // Reading from ALARMYEAR register.
    result.YEAR = alarm2_year_get();

    //return cal_val;
    return result;
}
 
void  am335x_rtc::compensation_set(REGS::RTC::COMPENSATION_t compensation)
{
    // Writing to COMPENSATION registers requires that BUSY bit in STATUS register
    // is low.
    while(busy_status_get());  

    //HWREG(baseAdd + RTC_COMPLSB) = (comp_val & COMP_LOW_MASK);
    //HWREG(baseAdd + RTC_COMPMSB) = (comp_val & COMP_HIGH_MASK);
    
    // Writing the lower 8 bits of 'comp_val' to COMPLSB register.
    m_regs.RTC_COMP_LSB.b.LSB = compensation.m.LSB;

    // Writing the higher 8 bits of 'comp_val' to COMPMSB register.
    m_regs.RTC_COMP_MSB.b.MSB = compensation.m.MSB;
}
 
REGS::RTC::COMPENSATION_t  am335x_rtc::compensation_get() const
{
    //uint32_t comp_val = 0;
    //comp_val = (HWREG(baseAdd + RTC_COMPLSB) & COMP_LOW_MASK);
    //comp_val |= ((HWREG(baseAdd + RTC_COMPMSB) & 0xFF) << COMP_SHIFT);
    //return comp_val;

    REGS::RTC::COMPENSATION_t result;

    // Reading from the COMPLSB register.
    result.m.LSB = m_regs.RTC_COMP_LSB.b.LSB;

    // Reading from the COMPMSB register.
    result.m.MSB = m_regs.RTC_COMP_MSB.b.MSB;

    return result;
}
 
void  am335x_rtc::scratch_pad_set(REGS::RTC::SCRATCH_t scratch_value)
{
    //HWREG(baseAdd + RTC_SCRATCH0 + offset) = scratch_value;
    m_regs.RTC_SCRATCH0.b.RTCSCRATCH0 = scratch_value.SCRATCH0; 
    m_regs.RTC_SCRATCH1.b.RTCSCRATCH1 = scratch_value.SCRATCH1; 
    m_regs.RTC_SCRATCH2.b.RTCSCRATCH2 = scratch_value.SCRATCH2; 
}
 
REGS::RTC::SCRATCH_t  am335x_rtc::scratch_pad_get() const
{
    REGS::RTC::SCRATCH_t result;

    result.SCRATCH0 = m_regs.RTC_SCRATCH0.b.RTCSCRATCH0;
    result.SCRATCH1 = m_regs.RTC_SCRATCH1.b.RTCSCRATCH1;
    result.SCRATCH2 = m_regs.RTC_SCRATCH2.b.RTCSCRATCH2;

    //return(HWREG(baseAdd + RTC_SCRATCH0 + offset));
    return result;
}
 

/*****************************************************************************
 **  APIs specific to RTC IP of AM1808 and not applicable for that in AM335x.
 *****************************************************************************/
void  am335x_rtc::software_reset()
{
    //HWREG(baseAdd + RTC_OSC) |= RTC_OSC_SWRESET;
    m_regs.RTC_OSC.reg |= REGS::RTC::AM1808__OSC_SWRESET;
}
 

/*****************************************************************************
 **  APIs specific to RTC IP of AM335x and not applicable for that in AM1808.
 *****************************************************************************/
REGS::RTC::RTC_REVISION_reg_t  am335x_rtc::revision_ID_get() const
{
    //return(HWREG(baseAdd + RTC_REVISION));
    REGS::RTC::RTC_REVISION_reg_t result; 
    result.reg = m_regs.RTC_REVISION.reg;     

    return result;
}
 
// Function which helps determine the SoC(Platform) in use. 
uint32_t  am335x_rtc::version_get(void) const
{
#if defined(am335x)
    return 2;
#elif defined(am1808)
    return 1;
#else
    return 0;
#endif
}
 
void  am335x_rtc::idle_mode_configure(REGS::RTC::e_RTC_IDLE mode_flag)
{
    //HWREG(baseAdd + RTC_SYSCONFIG) &= ~(RTC_SYSCONFIG_IDLEMODE);
    //HWREG(baseAdd + RTC_SYSCONFIG) |= (mode_flag & RTC_SYSCONFIG_IDLEMODE);
    
    // Clearing the IDLEMODE field in RTC_SYSCONFIG register.
    m_regs.RTC_SYSCONFIG.b.IDLEMODE = LOW; 

    // Programming the IDLEMODE field in RTC_SYSCONFIG register.
    m_regs.RTC_SYSCONFIG.b.IDLEMODE = mode_flag;
}
 
void  am335x_rtc::wakeup_alarm_event_control(bool control_flag)
{
    //HWREG(baseAdd + RTC_IRQWAKEEN) &= ~(RTC_IRQ_WAKEEN_ALARM_WAKEEN);
    //HWREG(baseAdd + RTC_IRQWAKEEN) |= (control_flag & RTC_IRQ_WAKEEN_ALARM_WAKEEN);
    
    // Clearing the ALARM_WAKEEN field of RTC_IRQWAKEEN register. 
    m_regs.RTC_IRQWAKEEN.b.ALARM_WAKEEN = LOW;
    // Programming the ALARM_WAKEEN field of RTC_WAKEEN register. 
    m_regs.RTC_IRQWAKEEN.b.ALARM_WAKEEN = control_flag;
}
 
void  am335x_rtc::wakeup_timer_event_control(bool control_flag)
{
    //HWREG(baseAdd + RTC_IRQWAKEEN) &= ~(RTC_IRQ_WAKEEN_TIMER_WAKEEN);
    //HWREG(baseAdd + RTC_IRQWAKEEN) |= (control_flag & RTC_IRQ_WAKEEN_TIMER_WAKEEN);
    
    // Clearing the TIMER_WAKEEN field of RTC_WAKEEN register. 
    m_regs.RTC_IRQWAKEEN.b.TIMER_WAKEEN = LOW;

    // Programming the TIMER_WAKEEN field of RTC_WAKEEN register.
    m_regs.RTC_IRQWAKEEN.b.TIMER_WAKEEN = control_flag;
}
 
void  am335x_rtc::test_mode_control(bool control_flag)
{
    //HWREG(baseAdd + RTC_CTRL) &= ~(RTC_CTRL_TEST_MODE);
    //HWREG(baseAdd + RTC_CTRL) |= (control_flag & RTC_CTRL_TEST_MODE);

    // Clearing the TEST_MODE field in RTC_CTRL register.
    m_regs.RTC_CTRL.b.TEST_MODE = LOW;

    // Setting the TEST_MODE bit of RT Control Register. 
    m_regs.RTC_CTRL.b.TEST_MODE = control_flag;
}
 
void  am335x_rtc::clk_32k_source_select(REGS::RTC::e_32KCLKSOURCE clk_src_flag)
{    
    // Clearing the 32KCLK_SEL bit in Oscilltor register.
    m_regs.RTC_OSC.b.SEL_32KCLK_SRC = LOW;

    // Programming the 32KCLK_SEL bit in Oscillator register.
    m_regs.RTC_OSC.b.SEL_32KCLK_SRC = clk_src_flag; 

    if(clk_src_flag == REGS::RTC::CLK32K_EXTERNAL)
    {        
        // Clearing the OSC32K_GZ field in RTC_OSC register.
        m_regs.RTC_OSC.reg &= ~REGS::RTC::OSC_OSC32K_GZ_MSK;
        m_regs.RTC_OSC.b.OSC32K_GZ = LOW;
    }
}
 
void  am335x_rtc::clk_32k_clock_control(bool control_flag)
{    
    // Clearing the 32KCLK_EN bit in RTC_OSC register. 
    m_regs.RTC_OSC.b.EN_32KCLK = LOW;

    // Programming the 32KCLK_EN bit in RTC_OSC register.
    m_regs.RTC_OSC.b.EN_32KCLK = control_flag; 
}
 
void  am335x_rtc::oscillator_state_control(bool control_flag)
{
    //HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_OSC32K_GZ);
    //HWREG(baseAdd + RTC_OSC) |= (controlFlag & RTC_OSC_OSC32K_GZ);
    
    // Clearing the OSC32K_GZ bit in Oscillator register.
    m_regs.RTC_OSC.b.OSC32K_GZ = LOW; 

    // Programming the OSC32K_GZ bit in Oscillator register.
    m_regs.RTC_OSC.b.OSC32K_GZ = control_flag;  
}
 
void  am335x_rtc::feedback_resistance_select(bool select_flag)
{
    //HWREG(baseAdd + RTC_OSC) &= ~(RTC_OSC_RES_SELECT);
    //HWREG(baseAdd + RTC_OSC) |= (select_flag & RTC_OSC_RES_SELECT);
    
    // Clearing the RES_SELECT bit in Oscillator register.
    m_regs.RTC_OSC.b.RES_SELECT = LOW;

    // Programming the RES_SELECT bit in Oscillator register.
    m_regs.RTC_OSC.b.RES_SELECT = select_flag;
}
 
void  am335x_rtc::config_pmic_power_enable(bool select_flag)
{
    // Clear the PMIC enable flag. 
    //HWREG(baseAdd + RTC_PMIC) &= ~(RTC_PMIC_PWR_ENABLE_EN);
    m_regs.RTC_PMIC.b.PWR_ENABLE_EN = LOW;

    // Write the value passed by the user. 
    //HWREG(baseAdd + RTC_PMIC) |= (select_flag & RTC_PMIC_PWR_ENABLE_EN);
    m_regs.RTC_PMIC.b.PWR_ENABLE_EN = select_flag;
}
 
void  am335x_rtc::config_pmic_ext_wake_polarity(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag)
{
    //HWREG(baseAdd + RTC_PMIC) &= ~((1 << ext_input) << RTC_PMIC_EXT_WAKEUP_POL_SHIFT);
    //HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_POL &
    //               ((select_flag << ext_input) << RTC_PMIC_EXT_WAKEUP_POL_SHIFT));
    
    // Clear the PMIC External Wakeup pin Polarity flag. 
    m_regs.RTC_PMIC.b.EXT_WAKEUP_POL &= ~ext_input;

    // Write the value passed by the user.
    m_regs.RTC_PMIC.b.EXT_WAKEUP_POL |= (select_flag << ext_input); 
}
 
void  am335x_rtc::config_pmic_ext_wake(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag)
{
    //HWREG(baseAdd + RTC_PMIC) &= ~((1 << ext_input) << RTC_PMIC_EXT_WAKEUP_EN_SHIFT);
    //HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_EN &
    //                ((select_flag << ext_input) << RTC_PMIC_EXT_WAKEUP_EN_SHIFT));
    
    // Clear the PMIC External Wakeup flag.
    m_regs.RTC_PMIC.b.EXT_WAKEUP_EN &= ~ext_input; 

    // Write the value passed by the user.
    m_regs.RTC_PMIC.b.EXT_WAKEUP_EN |= (select_flag << ext_input); 
}
 
void  am335x_rtc::config_pmic_ext_wake_debounce(REGS::RTC::e_EXT_WAKEUP_IN ext_input, bool select_flag)
{
    //HWREG(baseAdd + RTC_PMIC) &= ~((1 << ext_input) << RTC_PMIC_EXT_WAKEUP_DB_EN_SHIFT);
    //HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_DB_EN &
    //             ((select_flag << ext_input) << RTC_PMIC_EXT_WAKEUP_DB_EN_SHIFT));
    
    // Clear the PMIC External Wakeup pin Debounce flag. 
    m_regs.RTC_PMIC.b.EXT_WAKEUP_DB_EN &= ~ext_input;

    // Write the value passed by the user.
    m_regs.RTC_PMIC.b.EXT_WAKEUP_DB_EN |= (select_flag << ext_input); 
}
 
void  am335x_rtc::pmic_ext_wake_status_clear(REGS::RTC::e_EXT_WAKEUP_IN ext_input)
{
    //HWREG(baseAdd + RTC_PMIC) |= (RTC_PMIC_EXT_WAKEUP_STATUS &
    //                     ((1 << ext_input) << RTC_PMIC_EXT_WAKEUP_STATUS_SHIFT));
    m_regs.RTC_PMIC.b.EXT_WAKEUP_STATUS |= (1 << ext_input);
}

am335x_rtc rtc_module(REGS::RTC::AM335X_RTC);
 
