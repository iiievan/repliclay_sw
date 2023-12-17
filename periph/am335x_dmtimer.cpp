#include "am335x_dmtimer.h"
#include "utils.h"

am335x_dmtimer::am335x_dmtimer(REGS::DMTIMER::AM335x_DMTIMER_Type *p_tmr_regs)
:m_DMTIMER_regs(*p_tmr_regs)
{

}

void  am335x_dmtimer::enable()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.b.ST = HIGH; // Start the timer
    
    m_is_paused = false;
}

void  am335x_dmtimer::disable()
{    
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.b.ST = LOW; // Stop the timer
    
    m_is_paused = true;
}
 
void  am335x_dmtimer::mode_configure(REGS::DMTIMER::e_DMTIMER_mode mode)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_DMTIMER_regs.TCLR.b.AR = LOW;  // clear autoreload mode
    m_DMTIMER_regs.TCLR.b.CE = LOW;  // clear compare mode

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Set the timer mode in TCLR register
    m_DMTIMER_regs.TCLR.reg |= mode; 
}
 
void  am335x_dmtimer::prescaler_clk_enable(uint8_t ptv)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
   
    m_DMTIMER_regs.TCLR.b.PTV = 0x0;  // Clear the PTV field of TCLR

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Set the PTV field and enable the pre-scaler clock
    m_DMTIMER_regs.TCLR.b.PTV = ptv; 
    m_DMTIMER_regs.TCLR.b.PRE = HIGH;
}
 
void  am335x_dmtimer::prescaler_clk_disable()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Disable Pre-scaler clock 
    m_DMTIMER_regs.TCLR.b.PRE = LOW;
}
 
void  am335x_dmtimer::counter_set(uint32_t counter)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode

    // Set the counter value
    m_DMTIMER_regs.TCRR.reg = counter;
}
 
uint32_t  am335x_dmtimer::counter_get()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    return  m_DMTIMER_regs.TCRR.reg;
}

// Set the reload count value in the timer load register
void  am335x_dmtimer::reload_set(uint32_t reload)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TLDR); // wait in posted mode

    // Load the register with the re-load value
    m_DMTIMER_regs.TLDR.reg = reload;
}
 
// Get the reload count value from the timer load register
uint32_t  am335x_dmtimer::reload_get()
{
    return   m_DMTIMER_regs.TLDR.reg;
}
 
void  am335x_dmtimer::GPO_configure(bool gpo_cfg)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_DMTIMER_regs.TCLR.b.GPO_CFG = LOW; // Clear the GPO_CFG field of TCLR

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

     // Write to the GPO_CFG field of TCLR
     m_DMTIMER_regs.TCLR.b.GPO_CFG = gpo_cfg; 
}
 
void  am335x_dmtimer::compare_set(uint32_t compare_val)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TMAR); // wait in posted mode

    // Write the compare value to TMAR
    m_DMTIMER_regs.TMAR.reg = compare_val; 
}
 
uint32_t  am335x_dmtimer::compare_get()
{
    return  m_DMTIMER_regs.TMAR.reg;
}
 
void  am335x_dmtimer::IRQ_raw_set(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Trigger the events in IRQSTATUS_RAW register
    m_DMTIMER_regs.IRQSTATUS_RAW.reg = int_flags;
}
 
uint32_t  am335x_dmtimer::IRQ_raw_get()
{
    // Return the status of IRQSTATUS_RAW register
    return  m_DMTIMER_regs.IRQSTATUS_RAW.reg;
}
 
uint32_t  am335x_dmtimer::IRQ_get()
{
    // Return the status of IRQSTATUS register
    return  m_DMTIMER_regs.IRQSTATUS.reg;
}
 
void  am335x_dmtimer::IRQ_clear(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Clear the interrupt status from IRQSTATUS register
    m_DMTIMER_regs.IRQSTATUS.reg = int_flags; 
}
 
void  am335x_dmtimer::IRQ_enable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Enable the DMTimer interrupts represented by int_flags
    m_DMTIMER_regs.IRQENABLE_SET.reg = int_flags; 
}
 
void  am335x_dmtimer::IRQ_disable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Disable the DMTimer interrupts represented by int_flags
    m_DMTIMER_regs.IRQENABLE_CLR.reg = int_flags; 
}
 
void  am335x_dmtimer::trigger_set()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TTGR); // wait in posted mode

    m_DMTIMER_regs.TTGR.reg = REGS::DMTIMER::TTGR_DEF_VALUE; 
}
 
uint32_t  am335x_dmtimer::IRQ_enable_get()
{
    // Return the status of register IRQENABLE_SET
    return  m_DMTIMER_regs.IRQENABLE_SET.reg;
}
  
void  am335x_dmtimer::reset_configure(bool rst_option)
{
    // Clear the SFT field of TSICR
    m_DMTIMER_regs.TSICR.b.SFT = LOW;

    // Write the option sent by user to SFT field of TSICR
    m_DMTIMER_regs.TSICR.b.SFT = rst_option; 
}
 
void  am335x_dmtimer::reset()
{
    // Reset the DMTimer module
    m_DMTIMER_regs.TIOCP_CFG.b.SOFTRESET = HIGH;

    while( m_DMTIMER_regs.TIOCP_CFG.b.SOFTRESET);  
}
 
void  am335x_dmtimer::context_save()
{
    m_context.tldr =  m_DMTIMER_regs.TLDR.reg;
    m_context.tmar =  m_DMTIMER_regs.TMAR.reg;
    m_context.irqenableset =  m_DMTIMER_regs.IRQENABLE_SET.reg;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_context.tcrr =  m_DMTIMER_regs.TCRR.reg;
    
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_context.tclr =  m_DMTIMER_regs.TCLR.reg; 
}
 
void  am335x_dmtimer::context_restore()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_DMTIMER_regs.TLDR.reg = m_context.tldr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_DMTIMER_regs.TMAR.reg = m_context.tmar;
    m_DMTIMER_regs.IRQENABLE_SET.reg = m_context.irqenableset;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_DMTIMER_regs.TCRR.reg = m_context.tcrr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_DMTIMER_regs.TCLR.reg = m_context.tclr;  
}
 
void  am335x_dmtimer::posted_mode_config(bool post_mode)
{ 
    m_DMTIMER_regs.TSICR.b.POSTED = LOW;

    m_DMTIMER_regs.TSICR.b.POSTED = post_mode;  
} 

bool  am335x_dmtimer::posted_status_get()
{ 
    return (bool)m_DMTIMER_regs.TSICR.b.POSTED;  
} 

REGS::DMTIMER::e_TIMER_NUM am335x_dmtimer::get_DMTIMER_number()
{
    uint32_t timer_num = (uint32_t)&m_DMTIMER_regs;
     
    switch(timer_num)
    {
        case REGS::DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return REGS::DMTIMER::TIMER_0;
        case REGS::DMTIMER::AM335x_DMTIMER_1_BASE:     // 1ms timer
            return REGS::DMTIMER::TIMER_1ms;
        case REGS::DMTIMER::AM335x_DMTIMER_2_BASE:
            return REGS::DMTIMER::TIMER_2;
        case REGS::DMTIMER::AM335x_DMTIMER_3_BASE: 
            return REGS::DMTIMER::TIMER_3;
        case REGS::DMTIMER::AM335x_DMTIMER_4_BASE:
            return REGS::DMTIMER::TIMER_4;
        case REGS::DMTIMER::AM335x_DMTIMER_5_BASE:
            return REGS::DMTIMER::TIMER_5;
        case REGS::DMTIMER::AM335x_DMTIMER_6_BASE:
            return REGS::DMTIMER::TIMER_6;
        case REGS::DMTIMER::AM335x_DMTIMER_7_BASE:
            return REGS::DMTIMER::TIMER_7;
        default:
            break;
    } 
    
    return REGS::DMTIMER::TIMER_NA;
}

REGS::INTC::e_INT_ID am335x_dmtimer::get_DMTIMER_sys_interrupt()
{
    uint32_t timer_num = (uint32_t)&m_DMTIMER_regs;
     
    switch(timer_num)
    {
        case REGS::DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return REGS::INTC::TINT0;
        case REGS::DMTIMER::AM335x_DMTIMER_1_BASE:     // 1ms timer
            return REGS::INTC::TINT1_1MS;
        case REGS::DMTIMER::AM335x_DMTIMER_2_BASE:
            return REGS::INTC::TINT2;
        case REGS::DMTIMER::AM335x_DMTIMER_3_BASE: 
            return REGS::INTC::TINT3;
        case REGS::DMTIMER::AM335x_DMTIMER_4_BASE:
            return REGS::INTC::TINT4;
        case REGS::DMTIMER::AM335x_DMTIMER_5_BASE:
            return REGS::INTC::TINT5;
        case REGS::DMTIMER::AM335x_DMTIMER_6_BASE:
            return REGS::INTC::TINT6;
        case REGS::DMTIMER::AM335x_DMTIMER_7_BASE:
            return REGS::INTC::TINT7;
        default:
            break;
    } 
    
    return REGS::INTC::INT_NUM_MAX;
}

void  am335x_dmtimer::set_debug_EMUFREE(bool emufree_val)
{
    // Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_DMTIMER_regs.TIOCP_CFG.b.EMUFREE = emufree_val;
}

bool  am335x_dmtimer::get_debug_EMUFREE()
{
    return (bool)( m_DMTIMER_regs.TIOCP_CFG.b.EMUFREE);
}

void  am335x_dmtimer::m_wait_for_write(REGS::DMTIMER::e_TWPS_flags twps_mask)
{
    // Wait for previous write to complete if posted mode enabled
    if(m_DMTIMER_regs.TSICR.b.POSTED)
        while(m_DMTIMER_regs.TWPS.reg & twps_mask);
}   
