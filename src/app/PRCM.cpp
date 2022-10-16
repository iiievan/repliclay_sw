#include "PRCM.h"

power_reset_clock_control::power_reset_clock_control()
: m_sCM_PER(*PRCM::AM335x_CM_PER),
m_sCM_DPLL(*PRCM::AM335x_CM_DPLL),
m_sCM_WKUP(*PRCM::AM335x_CM_WKUP)
{

}
        
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

void power_reset_clock_control::define_DMTIMER_number(DMTIMER::AM335x_DMTIMER_Type * p_tmr)
{
    uint32_t timer_num = (uint32_t)m_pTIMER;
     
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

void power_reset_clock_control::run_clk_DMTIMER(DMTIMER::AM335x_DMTIMER_Type * p_tmr)
{
    define_DMTIMER_number(p_tmr);

    run_clk_interconnects();

    switch(m_timer_num)
    {
        case TIMER_0:
            break;
        case TIMER_1ms:
            break;
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
                /* Select the clock source for the Timer2 instance. */
                m_sCM_DPLL.TIMER4_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER4_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER4_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
            
                m_sCM_PER.TIMER4_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER4_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER4_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case TIMER_5:
                /* Select the clock source for the Timer5 instance. */
                #warning Need to test, there is a discrepancy with the starterware
                m_sCM_DPLL.TIMER5_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER5_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER5_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_sCM_PER.TIMER5_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER5_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER5_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case TIMER_6:
                /* Select the clock source for the Timer6 instance. */
                #warning Need to test, there is a discrepancy with the starterware
                m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER6_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_sCM_PER.TIMER6_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER6_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_sCM_PER.TIMER6_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
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
        case TIMER_5:
                #warning Need to test, there is a discrepancy with the starterware
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER5_GCLK) == false);
            break;
        case TIMER_6:
                #warning Need to test, there is a discrepancy with the starterware
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false);
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
void power_reset_clock_control::run_clk_DMTIMER_1ms()
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