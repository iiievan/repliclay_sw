#include "DM_Timer.h"

DM_Timer::DM_Timer(DMTIMER::AM335x_DMTIMER_Type *p_tmr_regs)
:m_DMTIMER_regs(*p_tmr_regs)
{

}

void  DM_Timer::enable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.b.ST = HIGH; // Start the timer
    
    m_is_paused = false;
}

void  DM_Timer::disable()
{    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.b.ST = LOW; // Stop the timer
    
    m_is_paused = true;
}
 
void  DM_Timer::mode_configure(DMTIMER::e_DMTIMER_mode mode)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_DMTIMER_regs.TCLR.b.AR = LOW;  // clear autoreload mode
    m_DMTIMER_regs.TCLR.b.CE = LOW;  // clear compare mode

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the timer mode in TCLR register **/
    m_DMTIMER_regs.TCLR.reg |= mode; 
}
 
void  DM_Timer::prescaler_clk_enable(uint8_t ptv)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
   
    m_DMTIMER_regs.TCLR.b.PTV = 0x0;  // Clear the PTV field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the PTV field and enable the pre-scaler clock **/
    m_DMTIMER_regs.TCLR.b.PTV = ptv; 
    m_DMTIMER_regs.TCLR.b.PRE = HIGH;
}
 
void  DM_Timer::prescaler_clk_disable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Disable Pre-scaler clock **/
    m_DMTIMER_regs.TCLR.b.PRE = LOW;
}
 
void  DM_Timer::counter_set(uint32_t counter)
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode

    /** Set the counter value **/
    m_DMTIMER_regs.TCRR.reg = counter;
}
 
uint32_t  DM_Timer::counter_get()
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    return  m_DMTIMER_regs.TCRR.reg;
}

/** Set the reload count value in the timer load register **/
void  DM_Timer::reload_set(uint32_t reload)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode

    /** Load the register with the re-load value **/
    m_DMTIMER_regs.TLDR.reg = reload;
}
 
/** Get the reload count value from the timer load register **/
uint32_t  DM_Timer::reload_get()
{
    /** Return the contents of TLDR **/
    return   m_DMTIMER_regs.TLDR.reg;
}
 
void  DM_Timer::GPO_configure(uint32_t gpo_cfg)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_DMTIMER_regs.TCLR.b.GPO_CFG = LOW; // Clear the GPO_CFG field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Write to the GPO_CFG field of TCLR **/
     m_DMTIMER_regs.TCLR.b.GPO_CFG = HIGH; 
}
 
void  DM_Timer::compare_set(uint32_t compare_val)
{
    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode

    /** Write the compare value to TMAR **/
    m_DMTIMER_regs.TMAR.reg = compare_val; 
}
 
uint32_t  DM_Timer::compare_get()
{
    /** Return the TMAR value **/
    return  m_DMTIMER_regs.TMAR.reg;
}

DMTIMER::e_TIMER_NUM DM_Timer::get_DMTIMER_number()
{
    uint32_t timer_num = (uint32_t)&m_DMTIMER_regs;
     
    switch(timer_num)
    {
        case DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return DMTIMER::TIMER_0;
        case DMTIMER::AM335x_DMTIMER_1_BASE:     // 1ms timer
            return DMTIMER::TIMER_1ms;
        case DMTIMER::AM335x_DMTIMER_2_BASE:
            return DMTIMER::TIMER_2;
        case DMTIMER::AM335x_DMTIMER_3_BASE: 
            return DMTIMER::TIMER_3;
        case DMTIMER::AM335x_DMTIMER_4_BASE:
            return DMTIMER::TIMER_4;
        case DMTIMER::AM335x_DMTIMER_5_BASE:
            return DMTIMER::TIMER_5;
        case DMTIMER::AM335x_DMTIMER_6_BASE:
            return DMTIMER::TIMER_6;
        case DMTIMER::AM335x_DMTIMER_7_BASE:
            return DMTIMER::TIMER_7;
        default:
            break;
    } 
    
    return DMTIMER::TIMER_NA;
}

INTC::e_SYS_INTERRUPT DM_Timer::get_DMTIMER_sys_interrupt()
{
    uint32_t timer_num = (uint32_t)&m_DMTIMER_regs;
     
    switch(timer_num)
    {
        case DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return INTC::TINT0;
        case DMTIMER::AM335x_DMTIMER_1_BASE:     // 1ms timer
            return INTC::TINT1_1MS;
        case DMTIMER::AM335x_DMTIMER_2_BASE:
            return INTC::TINT2;
        case DMTIMER::AM335x_DMTIMER_3_BASE: 
            return INTC::TINT3;
        case DMTIMER::AM335x_DMTIMER_4_BASE:
            return INTC::TINT4;
        case DMTIMER::AM335x_DMTIMER_5_BASE:
            return INTC::TINT5;
        case DMTIMER::AM335x_DMTIMER_6_BASE:
            return INTC::TINT6;
        case DMTIMER::AM335x_DMTIMER_7_BASE:
            return INTC::TINT7;
        default:
            break;
    } 
    
    return INTC::INTERRUPTS_NUM_MAX;
}
 
void  DM_Timer::IRQ_raw_set(DMTIMER::e_IRQ_flags int_flags)
{
    /** Trigger the events in IRQSTATUS_RAW register **/
    m_DMTIMER_regs.IRQSTATUS_RAW.reg = int_flags;
}
 
uint32_t  DM_Timer::IRQ_raw_get()
{
    /** Return the status of IRQSTATUS_RAW register **/
    return  m_DMTIMER_regs.IRQSTATUS_RAW.reg;
}
 
uint32_t  DM_Timer::IRQ_get()
{
    /** Return the status of IRQSTATUS register **/
    return  m_DMTIMER_regs.IRQSTATUS.reg;
}
 
void  DM_Timer::IRQ_clear(DMTIMER::e_IRQ_flags int_flags)
{
    /** Clear the interrupt status from IRQSTATUS register **/
    m_DMTIMER_regs.IRQSTATUS.reg = int_flags; 
}
 
void  DM_Timer::IRQ_enable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Enable the DMTimer interrupts represented by int_flags **/
    m_DMTIMER_regs.IRQENABLE_SET.reg = int_flags; 
}
 
void  DM_Timer::IRQ_disable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Disable the DMTimer interrupts represented by int_flags **/
    m_DMTIMER_regs.IRQENABLE_CLR.reg = int_flags; 
}
 
void  DM_Timer::trigger_set()
{
    m_wait_for_write(DMTIMER::F_PEND_TTGR); // wait in posted mode

    /** Write a value to the register **/
    m_DMTIMER_regs.TTGR.reg = DMTIMER::TTGR_DEF_VALUE; 
}
 
uint32_t  DM_Timer::IRQ_enable_get()
{
    /** Return the status of register IRQENABLE_SET **/
    return  m_DMTIMER_regs.IRQENABLE_SET.reg;
}
  
void  DM_Timer::reset_configure(bool rst_option)
{
    /** Clear the SFT field of TSICR **/
    m_DMTIMER_regs.TSICR.b.SFT = LOW;

    /** Write the option sent by user to SFT field of TSICR **/
    m_DMTIMER_regs.TSICR.b.SFT = rst_option; 
}
 
void  DM_Timer::reset()
{
    /** Reset the DMTimer module **/
    m_DMTIMER_regs.TIOCP_CFG.b.SOFTRESET = HIGH;

    while( m_DMTIMER_regs.TIOCP_CFG.b.SOFTRESET);  
}

void  DM_Timer::set_debug_EMUFREE(bool emufree_val)
{
    /** Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_DMTIMER_regs.TIOCP_CFG.b.EMUFREE = emufree_val;
}

bool  DM_Timer::get_debug_EMUFREE()
{
  return (bool)( m_DMTIMER_regs.TIOCP_CFG.b.EMUFREE);
}
 
void  DM_Timer::context_save(DMTIMERCONTEXT *p_context)
{
    p_context->tldr =  m_DMTIMER_regs.TLDR.reg;
    p_context->tmar =  m_DMTIMER_regs.TMAR.reg;
    p_context->irqenableset =  m_DMTIMER_regs.IRQENABLE_SET.reg;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    p_context->tcrr =  m_DMTIMER_regs.TCRR.reg;
    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    p_context->tclr =  m_DMTIMER_regs.TCLR.reg; 
}
 
void  DM_Timer::context_restore(DMTIMERCONTEXT *p_context)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_DMTIMER_regs.TLDR.reg = p_context->tldr;

    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_DMTIMER_regs.TMAR.reg = p_context->tmar;
    m_DMTIMER_regs.IRQENABLE_SET.reg = p_context->irqenableset;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_DMTIMER_regs.TCRR.reg = p_context->tcrr;

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.reg = p_context->tclr;  
}
 
void  DM_Timer::posted_mode_config(bool post_mode)
{ 
    /** Clear the POSTED field of TSICR **/
    m_DMTIMER_regs.TSICR.b.POSTED = LOW;

    /** Write to the POSTED field of TSICR **/
    m_DMTIMER_regs.TSICR.b.POSTED = post_mode;  
}  
