#include "PRCM.h"

power_reset_clock_control prcm_module;

power_reset_clock_control::power_reset_clock_control()
: m_CM_PER_regs(*PRCM::AM335x_CM_PER),
  m_CM_DPLL_regs(*PRCM::AM335x_CM_DPLL),
  m_CM_WKUP_regs(*PRCM::AM335x_CM_WKUP),
  m_CM_MPU_regs(*PRCM::AM335x_CM_MPU),
  m_CM_DEVICE_regs(*PRCM::AM335x_CM_DEVICE),
  m_CM_RTC_regs(*PRCM::AM335x_CM_RTC),
  m_CM_GFX_regs(*PRCM::AM335x_CM_GFX),
  m_CM_CEFUSE_regs(*PRCM::AM335x_CM_CEFUSE),
  m_PRM_IRQ_regs(*PRCM::AM335x_PRM_IRQ),
  m_PRM_PER_regs(*PRCM::AM335x_PRM_PER),
  m_PRM_WKUP_regs(*PRCM::AM335x_PRM_WKUP),
  m_PRM_MPU_regs(*PRCM::AM335x_PRM_MPU),
  m_PRM_DEVICE_regs(*PRCM::AM335x_PRM_DEVICE),
  m_PRM_RTC_regs(*PRCM::AM335x_PRM_RTC),
  m_PRM_GFX_regs(*PRCM::AM335x_PRM_GFX),
  m_PRM_CEFUSE_regs(*PRCM::AM335x_PRM_CEFUSE)
{

}

// run L3S,L3,L4,L4LS interconnects clock
void power_reset_clock_control::run_clk_interconnects()
{
    /* Run interconnects busses clocking */
    m_CM_PER_regs.L3S_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_CM_PER_regs.L3S_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);    

    m_CM_PER_regs.L3_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_CM_PER_regs.L3_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_CM_PER_regs.L3_INSTR_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_CM_PER_regs.L3_INSTR_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);

    m_CM_PER_regs.L3_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_CM_PER_regs.L3_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    

    m_CM_PER_regs.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_CM_PER_regs.OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKTRCTRL = PRCM::SW_WKUP;    
    while(m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKTRCTRL != PRCM::SW_WKUP);

    m_CM_PER_regs.L4LS_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_CM_PER_regs.L4LS_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);
}

void power_reset_clock_control::run_clk_DMTIMER(DMTIMER::e_TIMER_NUM tmr_num)
{
    switch(tmr_num)
    {
       case DMTIMER::TIMER_5:
            run_clk_DMTIMER_5();
            return; // no need to run run_clk_interconnects() and other stuff below
       case DMTIMER::TIMER_6:
            run_clk_DMTIMER_6();
            return; // no need to run run_clk_interconnects() and other stuff below
        case DMTIMER::TIMER_1ms:
        #ifndef beaglebone_black
            run_clk_DMTIMER_1ms(PRCM::MS1_M_OSC); // such a timer has not yet been described in DM_Timer.h
        #endif
            return; // no need to run run_clk_interconnects() and other stuff below
        default:
            break;    
    }
    
    run_clk_interconnects();

    switch(tmr_num)
    {
        case DMTIMER::TIMER_2:
                /* Select the clock source for the Timer2 instance. */
                m_CM_DPLL_regs.TIMER2_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_CM_DPLL_regs.TIMER2_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_CM_DPLL_regs.TIMER2_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
            
                m_CM_PER_regs.TIMER2_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_CM_PER_regs.TIMER2_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_CM_PER_regs.TIMER2_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case DMTIMER::TIMER_3:
                /* Select the clock source for the Timer3 instance. */
                m_CM_DPLL_regs.TIMER3_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_CM_DPLL_regs.TIMER3_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_CM_DPLL_regs.TIMER3_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_CM_PER_regs.TIMER3_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_CM_PER_regs.TIMER3_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_CM_PER_regs.TIMER3_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case DMTIMER::TIMER_4:
                /* Select the clock source for the Timer4 instance. */
                m_CM_DPLL_regs.TIMER4_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_CM_DPLL_regs.TIMER4_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_CM_DPLL_regs.TIMER4_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
            
                m_CM_PER_regs.TIMER4_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_CM_PER_regs.TIMER4_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_CM_PER_regs.TIMER4_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        case DMTIMER::TIMER_7:
                /* Select the clock source for the Timer7 instance. */
                m_CM_DPLL_regs.TIMER7_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_CM_DPLL_regs.TIMER7_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_CM_DPLL_regs.TIMER7_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    

                m_CM_PER_regs.TIMER7_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_CM_PER_regs.TIMER7_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);    
                while(m_CM_PER_regs.TIMER7_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
            break;
        default:
          break;
    }

    while(!m_CM_PER_regs.L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK);
    while(!m_CM_PER_regs.L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK);
        
    while((m_CM_PER_regs.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK | 
           m_CM_PER_regs.OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false);
    
    switch(tmr_num)
    {
        case DMTIMER::TIMER_2:
                while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER2_GCLK) == false);
            break;
        case DMTIMER::TIMER_3:
                while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER3_GCLK) == false);
            break;
        case DMTIMER::TIMER_4:
                while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER4_GCLK) == false);
            break;
        case DMTIMER::TIMER_7:
                while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER7_GCLK) == false);
            break;
        default:
          break;
    }

}

// only for DMTIMER 1
void power_reset_clock_control::run_clk_DMTIMER_1ms(PRCM::e_TIMER1MS_CLKSEL clk_sel)
{
    /* Select the clock source for the Timer1ms instance. */
    m_CM_DPLL_regs.TIMER1MS_CLK.b.CLKSEL = LOW;         // clear bitfield
    while(m_CM_DPLL_regs.TIMER1MS_CLK.b.CLKSEL != LOW);    
    
    m_CM_DPLL_regs.TIMER1MS_CLK.b.CLKSEL = clk_sel;    // select clock source
    while(m_CM_DPLL_regs.TIMER1MS_CLK.b.CLKSEL != clk_sel); 
    
    m_CM_WKUP_regs.TIMER1_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;
    while(m_CM_WKUP_regs.TIMER1_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    while(m_CM_WKUP_regs.TIMER1_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
}

void power_reset_clock_control::run_clk_DMTIMER_5()
{
    /* Select the clock source for the Timer5 instance. */
    m_CM_DPLL_regs.TIMER5_CLK.b.CLKSEL = LOW;               // clear bitfield
    m_CM_DPLL_regs.TIMER5_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
    while(m_CM_DPLL_regs.TIMER5_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
    
    m_CM_PER_regs.TIMER5_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_CM_PER_regs.TIMER5_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    
    while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
    m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER5_GCLK) == false);
}

void power_reset_clock_control::run_clk_DMTIMER_6()
{
    /* Select the clock source for the Timer6 instance. */
    m_CM_DPLL_regs.TIMER6_CLK.b.CLKSEL = LOW;               // clear bitfield
    m_CM_DPLL_regs.TIMER6_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
    while(m_CM_DPLL_regs.TIMER6_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
    
    m_CM_PER_regs.TIMER6_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    while(m_CM_PER_regs.TIMER2_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
    
    while((m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
    m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false);
}

void power_reset_clock_control::run_clk_GPIO0()
{
    /* Writing to MODULEMODE field of CM_WKUP_GPIO0_CLKCTRL register. */
    m_CM_WKUP_regs.GPIO0_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE; 
    /* Waiting for MODULEMODE field to reflect the written value. */
    while(m_CM_WKUP_regs.GPIO0_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);
    /* Writing to OPTFCLKEN_GPIO0_GDBCLK field of CM_WKUP_GPIO0_CLKCTRL register. */ 
    m_CM_WKUP_regs.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK = HIGH; 
    /* Waiting for OPTFCLKEN_GPIO0_GDBCLK field to reflect the written value. */
    while(m_CM_WKUP_regs.GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK != HIGH);
    
    /* Verifying if the other bits are set to required settings. */
    /* Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.CONTROL_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != HIGH);
    /* Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.L4WKUP_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != PRCM::CLK_ACT);
    /* Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != HIGH);
    /* Writing to IDLEST field in CM_WKUP_GPIO0_CLKCTRL register. */
    while(m_CM_WKUP_regs.GPIO0_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_GPIO0_GDBCLK field in CM_WKUP_GPIO0_CLKCTRL register to attain desired value. */
    while(m_CM_WKUP_regs.CLKSTCTRL.b.CLKACTIVITY_GPIO0_GDBCLK != PRCM::CLK_ACT);
}

void power_reset_clock_control::run_clk_GPIO1()
{
    /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
    m_CM_PER_regs.GPIO1_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
    /* Waiting for MODULEMODE field to reflect the written value. */
    while(m_CM_PER_regs.GPIO1_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE);
    /* Writing to OPTFCLKEN_GPIO_1_GDBCLK bit in CM_PER_GPIO1_CLKCTRL register. */
    m_CM_PER_regs.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK = HIGH;
    /* Waiting for OPTFCLKEN_GPIO_1_GDBCLK bit to reflect the desired value. */
    while(m_CM_PER_regs.GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK != HIGH);
    
    /* Waiting for IDLEST field in CM_PER_GPIO1_CLKCTRL register to attain the desired value. */
    while(m_CM_PER_regs.GPIO1_CLKCTRL.b.IDLEST != PRCM::IDLEST_FUNC);
    /* Waiting for CLKACTIVITY_GPIO_1_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL register to attain desired value.  */
    while(m_CM_PER_regs.L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_1_GDBCLK != PRCM::CLK_ACT);
}