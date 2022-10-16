#include "DM_Timer.h"


DM_Timer::DM_Timer(DMTIMER::AM335x_DMTIMER_Type * p_tmr)
:m_pTIMER(p_tmr),
m_sCM_PER(*PRCM::AM335x_CM_PER),
m_sCM_DPLL(*PRCM::AM335x_CM_DPLL),
m_sCM_WKUP(*PRCM::AM335x_CM_WKUP)
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

void  DM_Timer::enable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_pTIMER->TCLR.b.ST = HIGH; // Start the timer
    
    m_is_paused = false;
}

void  DM_Timer::disable()
{    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_pTIMER->TCLR.b.ST = LOW; // Stop the timer
    
    m_is_paused = true;
}

// only for DMTIMER 1
void DM_Timer::timer1ms_clk_config(PRCM::e_TIMER1MS_CLKSEL clk_sel)
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

void DM_Timer::clk_config(void)
{ 
    switch(m_timer_num)
    {
        case TIMER_1ms:
            return;
        case TIMER_6:
                /* Select the clock source for the Timer6 instance. */
                m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = LOW;               // clear bitfield
                m_sCM_DPLL.TIMER6_CLK.b.CLKSEL = PRCM::CLK_M_OSC;   // and then set it to the desired value
                while(m_sCM_DPLL.TIMER6_CLK.b.CLKSEL != PRCM::CLK_M_OSC);    
                
                m_sCM_PER.TIMER6_CLKCTRL.b.MODULEMODE = PRCM::MODULEMODE_ENABLE;    
                while(m_sCM_PER.TIMER2_CLKCTRL.b.MODULEMODE != PRCM::MODULEMODE_ENABLE); 
                
                while((m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                m_sCM_PER.L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false);
            return;
        default:
            break;
    }
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
 
void  DM_Timer::mode_configure(DMTIMER::e_DMTIMER_mode mode)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_pTIMER->TCLR.b.AR = LOW;  // clear autoreload mode
    m_pTIMER->TCLR.b.CE = LOW;  // clear compare mode

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the timer mode in TCLR register **/
    m_pTIMER->TCLR.reg |= mode; 
}
 
void  DM_Timer::prescaler_clk_enable(uint8_t ptv)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
   
    m_pTIMER->TCLR.b.PTV = 0;  // Clear the PTV field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the PTV field and enable the pre-scaler clock **/
    m_pTIMER->TCLR.b.PTV = ptv; 
    m_pTIMER->TCLR.b.PRE = HIGH;
}
 
void  DM_Timer::prescaler_clk_disable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Disable Pre-scaler clock **/
    m_pTIMER->TCLR.b.PRE = LOW;
}
 
void  DM_Timer::counter_set(uint32_t counter)
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode

    /** Set the counter value **/
    m_pTIMER->TCRR.reg = counter;
}
 
uint32_t  DM_Timer::counter_get()
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    return m_pTIMER->TCRR.reg;
}

/** Set the reload count value in the timer load register **/
void  DM_Timer::reload_set(uint32_t reload)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode

    /** Load the register with the re-load value **/
    m_pTIMER->TLDR.reg = reload;
}
 
/** Get the reload count value from the timer load register **/
uint32_t  DM_Timer::reload_get()
{
    /** Return the contents of TLDR **/
    return  m_pTIMER->TLDR.reg;
}
 
void  DM_Timer::GPO_configure(uint32_t gpo_cfg)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_pTIMER->TCLR.b.GPO_CFG = LOW; // Clear the GPO_CFG field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Write to the GPO_CFG field of TCLR **/
    m_pTIMER->TCLR.b.GPO_CFG = HIGH; 
}
 
void  DM_Timer::compare_set(uint32_t compare_val)
{
    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode

    /** Write the compare value to TMAR **/
    m_pTIMER->TMAR.reg = compare_val; 
}
 
uint32_t  DM_Timer::compare_get()
{
    /** Return the TMAR value **/
    return m_pTIMER->TMAR.reg;
}
 
void  DM_Timer::IRQ_raw_set(DMTIMER::e_IRQ_flags int_flags)
{
    /** Trigger the events in IRQSTATUS_RAW register **/
    m_pTIMER->IRQSTATUS_RAW.reg = int_flags;
}
 
uint32_t  DM_Timer::IRQ_raw_get()
{
    /** Return the status of IRQSTATUS_RAW register **/
    return m_pTIMER->IRQSTATUS_RAW.reg;
}
 
uint32_t  DM_Timer::IRQ_get()
{
    /** Return the status of IRQSTATUS register **/
    return m_pTIMER->IRQSTATUS.reg;
}
 
void  DM_Timer::IRQ_clear(DMTIMER::e_IRQ_flags int_flags)
{
    /** Clear the interrupt status from IRQSTATUS register **/
    m_pTIMER->IRQSTATUS.reg = int_flags; 
}
 
void  DM_Timer::IRQ_enable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Enable the DMTimer interrupts represented by int_flags **/
    m_pTIMER->IRQENABLE_SET.reg = int_flags; 
}
 
void  DM_Timer::IRQ_disable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Disable the DMTimer interrupts represented by int_flags **/
    m_pTIMER->IRQENABLE_CLR.reg = int_flags; 
}
 
void  DM_Timer::trigger_set()
{
    m_wait_for_write(DMTIMER::F_PEND_TTGR); // wait in posted mode

    /** Write a value to the register **/
    m_pTIMER->TTGR.reg = DMTIMER::TTGR_DEF_VALUE; 
}
 
uint32_t  DM_Timer::IRQ_enable_get()
{
    /** Return the status of register IRQENABLE_SET **/
    return m_pTIMER->IRQENABLE_SET.reg;
}
  
void  DM_Timer::reset_configure(bool rst_option)
{
    /** Clear the SFT field of TSICR **/
    m_pTIMER->TSICR.b.SFT = LOW;

    /** Write the option sent by user to SFT field of TSICR **/
    m_pTIMER->TSICR.b.SFT = rst_option; 
}
 
void  DM_Timer::reset()
{
    /** Reset the DMTimer module **/
    m_pTIMER->TIOCP_CFG.b.SOFTRESET = HIGH;

    while(m_pTIMER->TIOCP_CFG.b.SOFTRESET);  
}

void  DM_Timer::set_debug_EMUFREE(bool emufree_val)
{
    /** Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_pTIMER->TIOCP_CFG.b.EMUFREE = emufree_val;
}

bool  DM_Timer::get_debug_EMUFREE()
{
  return (bool)(m_pTIMER->TIOCP_CFG.b.EMUFREE);
}
 
void  DM_Timer::context_save(DMTIMERCONTEXT *p_context)
{
    p_context->tldr = m_pTIMER->TLDR.reg;
    p_context->tmar = m_pTIMER->TMAR.reg;
    p_context->irqenableset = m_pTIMER->IRQENABLE_SET.reg;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    p_context->tcrr = m_pTIMER->TCRR.reg;
    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    p_context->tclr = m_pTIMER->TCLR.reg; 
}
 
void  DM_Timer::context_restore(DMTIMERCONTEXT *p_context)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_pTIMER->TLDR.reg = p_context->tldr;

    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_pTIMER->TMAR.reg = p_context->tmar;
    m_pTIMER->IRQENABLE_SET.reg = p_context->irqenableset;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_pTIMER->TCRR.reg = p_context->tcrr;

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_pTIMER->TCLR.reg = p_context->tclr;  
}
 
void  DM_Timer::posted_mode_config(bool post_mode)
{ 
    /** Clear the POSTED field of TSICR **/
    m_pTIMER->TSICR.b.POSTED = LOW;

    /** Write to the POSTED field of TSICR **/
     m_pTIMER->TSICR.b.POSTED = post_mode;  
}  
