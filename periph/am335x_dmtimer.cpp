#include "am335x_dmtimer.h"
#include "utils.h"

template <typename DMT>
am335x_dmtimer<DMT>::am335x_dmtimer(DMT *p_tmr_regs)
:m_regs(*p_tmr_regs)
{

}

template <typename DMT>
void  am335x_dmtimer<DMT>::enable()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_regs.TCLR.b.ST = HIGH; // Start the timer
    
    m_is_paused = false;

    m_time = 0UL;
}

template <typename DMT>
void  am335x_dmtimer<DMT>::disable()
{    
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_regs.TCLR.b.ST = LOW; // Stop the timer
    
    m_is_paused = true;
}

template <typename DMT>
void  am335x_dmtimer<DMT>::mode_configure(REGS::DMTIMER::e_DMTIMER_mode mode)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_regs.TCLR.b.AR = LOW;  // clear autoreload mode
    m_regs.TCLR.b.CE = LOW;  // clear compare mode

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Set the timer mode in TCLR register
    m_regs.TCLR.reg |= mode; 
}

template <typename DMT>
void  am335x_dmtimer<DMT>::prescaler_clk_enable(REGS::DMTIMER::e_PRSC ptv)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
   
    m_regs.TCLR.b.PTV = 0x0;  // Clear the PTV field of TCLR

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Set the PTV field and enable the pre-scaler clock
    m_regs.TCLR.b.PTV = ptv; 
    m_regs.TCLR.b.PRE = HIGH;
}

template <typename DMT>
void  am335x_dmtimer<DMT>::prescaler_clk_disable()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    // Disable Pre-scaler clock 
    m_regs.TCLR.b.PRE = LOW;
}

template<>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::set_1ms_block(int32_t pos, int32_t neg)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_regs.TPIR.b.POSITIVE_INC_VALUE = pos;

    m_regs.TNIR.b.NEGATIVE_INC_VALUE = neg;
}

template <typename DMT>
void  am335x_dmtimer<DMT>::counter_set(uint32_t counter)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode

    // Set the counter value
    m_regs.TCRR.reg = counter;

}

template <typename DMT>
uint32_t  am335x_dmtimer<DMT>::counter_get()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    return  m_regs.TCRR.reg;
}

// Set the reload count value in the timer load register
template <typename DMT>
void  am335x_dmtimer<DMT>::reload_set(uint32_t reload)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TLDR); // wait in posted mode

    // Load the register with the re-load value
    m_regs.TLDR.reg = reload;
}
 
// Get the reload count value from the timer load register
template <typename DMT>
uint32_t  am335x_dmtimer<DMT>::reload_get()
{
    return   m_regs.TLDR.reg;
}

template <typename DMT>
void  am335x_dmtimer<DMT>::GPO_configure(bool gpo_cfg)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_regs.TCLR.b.GPO_CFG = LOW; // Clear the GPO_CFG field of TCLR

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode

     // Write to the GPO_CFG field of TCLR
     m_regs.TCLR.b.GPO_CFG = gpo_cfg; 
}

template <typename DMT>
void  am335x_dmtimer<DMT>::compare_set(uint32_t compare_val)
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TMAR); // wait in posted mode

    // Write the compare value to TMAR
    m_regs.TMAR.reg = compare_val; 
}

template <typename DMT>
uint32_t  am335x_dmtimer<DMT>::compare_get()
{
    return  m_regs.TMAR.reg;
}

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_raw_set(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Trigger the events in IRQSTATUS_RAW register
    m_regs.IRQSTATUS_RAW.reg = int_flags;
}

template <>
uint32_t  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_raw_get()
{
    // Return the status of IRQSTATUS_RAW register
    return  m_regs.IRQSTATUS_RAW.reg;
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
uint32_t  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_get()
{
    // Return the status of IRQSTATUS register
    return  m_regs.TISR.reg;
}

template <>
uint32_t  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_get()
{
    // Return the status of IRQSTATUS register
    return  m_regs.IRQSTATUS.reg;
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_clear(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Clear the interrupt status from TISR register
    m_regs.TISR.reg = int_flags; 
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_clear(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Clear the interrupt status from IRQSTATUS register
    m_regs.IRQSTATUS.reg = int_flags; 
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_enable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Enable the DMTimer interrupts represented by int_flags
    m_regs.TIER.reg |= int_flags; 
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_enable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Enable the DMTimer interrupts represented by int_flags
    m_regs.IRQENABLE_SET.reg = int_flags; 
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_disable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Disable the DMTimer interrupts represented by int_flags
    m_regs.TIER.reg &= ~int_flags; 
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_disable(REGS::DMTIMER::e_IRQ_flags int_flags)
{
    // Disable the DMTimer interrupts represented by int_flags
    m_regs.IRQENABLE_CLR.reg = int_flags; 
}
// <--------------------------------------------------------------*

template <typename DMT>
void  am335x_dmtimer<DMT>::trigger_set()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TTGR); // wait in posted mode

    m_regs.TTGR.reg = REGS::DMTIMER::TTGR_DEF_VALUE; 
}

// *-------------------------------------------------------------->
template <>
uint32_t  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::IRQ_enable_get()
{
    // Return the status of register TIER
    return  m_regs.TIER.reg;
}

template <>
uint32_t  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::IRQ_enable_get()
{
    // Return the status of register IRQENABLE_SET
    return  m_regs.IRQENABLE_SET.reg;
}
// <--------------------------------------------------------------*

template <typename DMT> 
void  am335x_dmtimer<DMT>::reset_configure(bool rst_option)
{
    // Clear the SFT field of TSICR
    m_regs.TSICR.b.SFT = LOW;

    // Write the option sent by user to SFT field of TSICR
    m_regs.TSICR.b.SFT = rst_option; 
}

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::reset()
{
    // Reset the DMTimer module
    m_regs.TIOCP_CFG.b.SoftReset = HIGH;

    while( m_regs.TIOCP_CFG.b.SoftReset);  
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::reset()
{
    // Reset the DMTimer module
    m_regs.TIOCP_CFG.b.SOFTRESET = HIGH;

    while( m_regs.TIOCP_CFG.b.SOFTRESET);  
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::context_save()
{
    m_context.tldr =  m_regs.TLDR.reg;
    m_context.tmar =  m_regs.TMAR.reg;
    m_context.irqenableset =  m_regs.TIER.reg;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_context.tcrr =  m_regs.TCRR.reg;
    
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_context.tclr =  m_regs.TCLR.reg; 
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::context_save()
{
    m_context.tldr =  m_regs.TLDR.reg;
    m_context.tmar =  m_regs.TMAR.reg;
    m_context.irqenableset =  m_regs.IRQENABLE_SET.reg;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_context.tcrr =  m_regs.TCRR.reg;
    
    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_context.tclr =  m_regs.TCLR.reg; 
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <> 
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::context_restore()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_regs.TLDR.reg = m_context.tldr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_regs.TMAR.reg = m_context.tmar;
    m_regs.TIER.reg = m_context.irqenableset;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_regs.TCRR.reg = m_context.tcrr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_regs.TCLR.reg = m_context.tclr;  
}

template <> 
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::context_restore()
{
    m_wait_for_write(REGS::DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_regs.TLDR.reg = m_context.tldr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_regs.TMAR.reg = m_context.tmar;
    m_regs.IRQENABLE_SET.reg = m_context.irqenableset;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_regs.TCRR.reg = m_context.tcrr;

    m_wait_for_write(REGS::DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_regs.TCLR.reg = m_context.tclr;  
}
// <--------------------------------------------------------------*

template <typename DMT> 
void  am335x_dmtimer<DMT>::posted_mode_config(bool post_mode)
{ 
    m_regs.TSICR.b.POSTED = LOW;

    m_regs.TSICR.b.POSTED = post_mode;  
} 

template <typename DMT>
bool  am335x_dmtimer<DMT>::posted_status_get()
{ 
    return (bool)m_regs.TSICR.b.POSTED;  
} 

template <typename DMT>
REGS::DMTIMER::e_TIMER_NUM am335x_dmtimer<DMT>::get_DMTIMER_number()
{
    uint32_t timer_num = (uint32_t)&m_regs;
     
    switch(timer_num)
    {
        case REGS::DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return REGS::DMTIMER::TIMER_0;
        case REGS::DMTIMER1MS::AM335x_DMTIMER_1MS_BASE:
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

template <typename DMT>
REGS::INTC::e_INT_ID am335x_dmtimer<DMT>::get_DMTIMER_sys_interrupt()
{
    uint32_t timer_num = (uint32_t)&m_regs;
     
    switch(timer_num)
    {
        case REGS::DMTIMER::AM335x_DMTIMER_0_BASE:     // only 32KHz RC Clock
            return REGS::INTC::TINT0;
        case REGS::DMTIMER1MS::AM335x_DMTIMER_1MS_BASE:
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

// *-------------------------------------------------------------->
template <>
void  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::set_debug_EMUFREE(bool emufree_val)
{
    // Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_regs.TIOCP_CFG.b.EmuFree = emufree_val;
}

template <>
void  am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::set_debug_EMUFREE(bool emufree_val)
{
    // Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_regs.TIOCP_CFG.b.EMUFREE = emufree_val;
}
// <--------------------------------------------------------------*

// *-------------------------------------------------------------->
template <>
bool  am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>::get_debug_EMUFREE()
{
    return (bool)( m_regs.TIOCP_CFG.b.EmuFree);
}

template <> 
bool am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>::get_debug_EMUFREE()   
{ 
    return (bool)( m_regs.TIOCP_CFG.b.EMUFREE);
}
// <--------------------------------------------------------------*

template <typename DMT>
void  am335x_dmtimer<DMT>::m_wait_for_write(REGS::DMTIMER::e_TWPS_flags twps_mask)
{
    // Wait for previous write to complete if posted mode enabled
    if(m_regs.TSICR.b.POSTED)
        while(m_regs.TWPS.reg & twps_mask);
} 



// dmtimer template instantiating
template class am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type>;              // for DMTimer 0,2,3,4,5,6,7
template class am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type>;        // for DMTimer_1ms

      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_0(REGS::DMTIMER::AM335X_DMTIMER_0);
am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type> dm_timer_1ms(REGS::DMTIMER1MS::AM335X_DMTIMER_1MS);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_2(REGS::DMTIMER::AM335X_DMTIMER_2);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_3(REGS::DMTIMER::AM335X_DMTIMER_3);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_4(REGS::DMTIMER::AM335X_DMTIMER_4);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_5(REGS::DMTIMER::AM335X_DMTIMER_5);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_6(REGS::DMTIMER::AM335X_DMTIMER_6);
//      am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_7(REGS::DMTIMER::AM335X_DMTIMER_7);
