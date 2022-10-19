#include "PRCM.h"

power_reset_clock_control prcm_module;

power_reset_clock_control::power_reset_clock_control()
: m_sCM_PER(*PRCM::AM335x_CM_PER),
  m_sCM_DPLL(*PRCM::AM335x_CM_DPLL),
  m_sCM_WKUP(*PRCM::AM335x_CM_WKUP),
  m_sCM_MPU(*PRCM::AM335x_CM_MPU),
  m_sCM_DEVICE(*PRCM::AM335x_CM_DEVICE),
  m_sCM_RTC(*PRCM::AM335x_CM_RTC),
  m_sCM_GFX(*PRCM::AM335x_CM_GFX),
  m_sCM_CEFUSE(*PRCM::AM335x_CM_CEFUSE),
  m_sPRM_IRQ(*PRCM::AM335x_PRM_IRQ),
  m_sPRM_PER(*PRCM::AM335x_PRM_PER),
  m_sPRM_WKUP(*PRCM::AM335x_PRM_WKUP),
  m_sPRM_MPU(*PRCM::AM335x_PRM_MPU),
  m_sPRM_DEVICE(*PRCM::AM335x_PRM_DEVICE),
  m_sPRM_RTC(*PRCM::AM335x_PRM_RTC),
  m_sPRM_GFX(*PRCM::AM335x_PRM_GFX),
  m_sPRM_CEFUSE(*PRCM::AM335x_PRM_CEFUSE)
{

}

// run L3S,L3,L4,L4LS interconnects clock
void power_reset_clock_control::run_clk_interconnects()
{
    /* Run interconnects busses clocking */
    m_sCM_PER.L3S_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_sCM_PER.L3S_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);    

    m_sCM_PER.L3_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_sCM_PER.L3_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_sCM_PER.L3_INSTR_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_sCM_PER.L3_INSTR_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);

    m_sCM_PER.L3_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_sCM_PER.L3_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    

    m_sCM_PER.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_sCM_PER.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_sCM_PER.L4LS_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_sCM_PER.L4LS_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_sCM_PER.L4LS_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_sCM_PER.L4LS_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);

}

void power_reset_clock_control::define_DMTIMER_number(DMTIMER::AM335x_DMTIMER_Type &p_tmr)
{
    uint32_t timer_num = (uint32_t)&p_tmr;
     
    switch(timer_num)
    {
        case DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            m_timer_num = TIMER_0;
            break;
        case DMTIMER::AM335x_DMTIMER_1_BASE:     // 1ms timer
            m_timer_num = TIMER_1ms;
            break;
        case DMTIMER::AM335x_DMTIMER_2_BASE:
            m_timer_num = TIMER_2;
            break;
        case DMTIMER::AM335x_DMTIMER_3_BASE: 
            m_timer_num = TIMER_3;
            break;
        case DMTIMER::AM335x_DMTIMER_4_BASE:
            m_timer_num = TIMER_4;
            break;
        case DMTIMER::AM335x_DMTIMER_5_BASE:
            m_timer_num = TIMER_5;
            break;
        case DMTIMER::AM335x_DMTIMER_6_BASE:
            m_timer_num = TIMER_6;
            break;
        case DMTIMER::AM335x_DMTIMER_7_BASE:
            m_timer_num = TIMER_7;
            break;
        default:
            break;
    }   
}

void power_reset_clock_control::run_clk_DMTIMER(DMTIMER::AM335x_DMTIMER_Type &p_tmr)
{
    define_DMTIMER_number(p_tmr);

    switch(m_timer_num)
    {
       case TIMER_5:
            run_clk_DMTIMER_5();
            return; // no need to run run_clk_interconnects() and other stuff below
       case TIMER_6:
            run_clk_DMTIMER_6();
            return; // no need to run run_clk_interconnects() and other stuff below
        case TIMER_1ms:
        #ifndef beaglebone_black
            run_clk_DMTIMER_1ms(PRCM::MS1_M_OSC); // such a timer has not yet been described in DM_Timer.h
        #endif
            return; // no need to run run_clk_interconnects() and other stuff below
        default:
            break;    
    }
    
    run_clk_interconnects();

    switch(m_timer_num)
    {
        case TIMER_2:
                /* Select the clock source for the Timer2 instance. */
                m_sCM_DPLL.TIMER2_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER2_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER2_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
            
                m_sCM_PER.TIMER2_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER2_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER2_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case TIMER_3:
                /* Select the clock source for the Timer3 instance. */
                m_sCM_DPLL.TIMER3_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER3_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER3_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_sCM_PER.TIMER3_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER3_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER3_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case TIMER_4:
                /* Select the clock source for the Timer4 instance. */
                m_sCM_DPLL.TIMER4_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER4_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER4_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
            
                m_sCM_PER.TIMER4_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER4_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER4_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case TIMER_7:
                /* Select the clock source for the Timer7 instance. */
                m_sCM_DPLL.TIMER7_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER7_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER7_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_sCM_PER.TIMER7_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER7_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER7_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        default:
          break;
    }

    while(!m_sCM_PER.L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK);
    while(!m_sCM_PER.L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK);
        
    while((m_sCM_PER.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK | 
           m_sCM_PER.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false);
    
    switch(m_timer_num)
    {
        case TIMER_2:
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER2_GCLK) == false);
            break;
        case TIMER_3:
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER3_GCLK) == false);
            break;
        case TIMER_4:
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER4_GCLK) == false);
            break;
        case TIMER_7:
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER7_GCLK) == false);
            break;
        default:
          break;
    }

}

// only for DMTIMER 1
void power_reset_clock_control::run_clk_DMTIMER_1ms(PRCM::e_TIMER1MS_CLKSEL clk_sel)
{
    /* Select the clock source for the Timer1ms instance. */
    m_sCM_DPLL.TIMER1MS_CLK.b.CLKSEL = LOW;         // clear bitfield
    while(m_sCM_DPLL.TIMER1MS_CLK.b.CLKSEL != LOW);    
    
    m_sCM_DPLL.TIMER1MS_CLK.b.CLKSEL = clk_sel;    // select clock source
    while(m_sCM_DPLL.TIMER1MS_CLK.b.CLKSEL != clk_sel); 
    
    m_sCM_WKUP.TIMER1_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;
    while(m_sCM_WKUP.TIMER1_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    while(m_sCM_WKUP.TIMER1_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
}

void power_reset_clock_control::run_clk_DMTIMER_5()
{
    /* Select the clock source for the Timer5 instance. */
    m_sCM_DPLL.TIMER5_CLK.b.CLKSEL = LOW;               // clear bitfield
    m_sCM_DPLL.TIMER5_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
    while(m_sCM_DPLL.TIMER5_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
    
    m_sCM_PER.TIMER5_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_sCM_PER.TIMER5_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    
    while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
    m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER5_GCLK) == false);
}

void power_reset_clock_control::run_clk_DMTIMER_6()
{
    /* Select the clock source for the Timer6 instance. */
    m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = LOW;               // clear bitfield
    m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
    while(m_sCM_DPLL.TIMER6_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
    
    m_sCM_PER.TIMER6_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_sCM_PER.TIMER2_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    
    while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
    m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false);
}

void power_reset_clock_control::run_clk_GPIO0()
{
    /* Writing to MODULEMODE field of CM_WKUP_GPIO0_CLKCTRL register. */
    m_sCM_WKUP.GPIO0_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE; 
    /* Waiting for MODULEMODE field to reflect the written value. */
    while(m_sCM_WKUP.GPIO0_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);
    /* Writing to OPTFCLKEN_GPIO0_GDBCLK field of CM_WKUP_GPIO0_CLKCTRL register. */ 
    m_sCM_WKUP.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK = HIGH; 
    /* Waiting for OPTFCLKEN_GPIO0_GDBCLK field to reflect the written value. */
    while(m_sCM_WKUP.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK != HIGH);
    
    /* Verifying if the other bits are set to required settings. */
    /* Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain desired value. */
    while(m_sCM_WKUP.CONTROL_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL register to attain desired value. */
    while(m_sCM_WKUP.L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != HIGH);
    /* Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain desired value. */
    while(m_sCM_WKUP.L4WKUP_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register to attain desired value. */
    while(m_sCM_WKUP.CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != PRCM::CLK_ACT);
    /* Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL register to attain desired value. */
    while(m_sCM_WKUP.L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != HIGH);
    /* Writing to IDLEST field in CM_WKUP_GPIO0_CLKCTRL register. */
    while(m_sCM_WKUP.GPIO0_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_GPIO0_GDBCLK field in CM_WKUP_GPIO0_CLKCTRL register to attain desired value. */
    while(m_sCM_WKUP.CLKSTCTRL.b.CLKACTIVITY_GPIO0_GDBCLK != PRCM::CLK_ACT);
}

void power_reset_clock_control::run_clk_GPIO1()
{
    /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
    m_sCM_PER.GPIO1_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    /* Waiting for MODULEMODE field to reflect the written value. */
    while(m_sCM_PER.GPIO1_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);
    /* Writing to OPTFCLKEN_GPIO_1_GDBCLK bit in CM_PER_GPIO1_CLKCTRL register. */
    m_sCM_PER.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK = HIGH;
    /* Waiting for OPTFCLKEN_GPIO_1_GDBCLK bit to reflect the desired value. */
    while(m_sCM_PER.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK != HIGH);
    
    /* Waiting for IDLEST field in CM_PER_GPIO1_CLKCTRL register to attain the desired value. */
    while(m_sCM_PER.GPIO1_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_GPIO_1_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL register to attain desired value.  */
    while(m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_1_GDBCLK != PRCM::CLK_ACT);
}