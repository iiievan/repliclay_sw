#include "DM_Timer.h"


/*
** Setup the timer for one-shot and compare mode.
** Setup the timer 2 to generate the tick interrupts at the required frequency.
 */

#define DMTIMER2_INITIAL_COUNT             (0xffffa261) // 1ms approximate
#define DMTIMER2_RLD_COUNT                 (0xffffa261) // 1ms approximate

void DM_Timer_setup(void)
{
    uint32_t dmtimer_mode =  DMTIMER::MODE_AUTORELOAD | (!DMTIMER::MODE_COMPARE); //  mode : autoreload and no compare

    OS_TIMER.init(); //This function will enable clocks and interrupt for the DM_Timer instance
    /* Register DMTimer2 interrupts on to AINTC */
    //DMTimerAintcConfigure();
    
    OS_TIMER.counter_set(DMTIMER2_INITIAL_COUNT); //Load the counter with the initial count value
    OS_TIMER.reload_set(DMTIMER2_RLD_COUNT);    //Load the load register with the reload count value
    OS_TIMER.mode_configure((DMTIMER::e_DMTIMER_mode)dmtimer_mode); //Configure the DMTimer for Auto-reload and compare mode
    OS_TIMER.enable();
}

DM_Timer::DM_Timer(DMTIMER::AM335x_DMTIMER_Type &p_tmr)
:m_sTIMER(p_tmr),
m_sPRCM(prcm_module),
m_sINTC(intc)
{

}

void  DM_Timer::enable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_sTIMER.TCLR.b.ST = HIGH; // Start the timer
    
    m_is_paused = false;
}

void  DM_Timer::disable()
{    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_sTIMER.TCLR.b.ST = LOW; // Stop the timer
    
    m_is_paused = true;
}

void DM_Timer::init(void)
{     
    // run clock for timer instance
    m_sPRCM.run_clk_DMTIMER(m_sTIMER); 

    // setup timer interrupt
    m_sINTC.register_handler(OS_TIMER_INTERRUPT,(INTC::Handler_ptr_t)DMTimer_irqhandler);            // Registering DMTimer_irqhandler
    m_sINTC.priority_set(OS_TIMER_INTERRUPT,(INTC::MAX_IRQ_PRIORITIES -1), INTC::HOSTINT_ROUTE_IRQ); // Set the lowest priority
    m_sINTC.system_enable(OS_TIMER_INTERRUPT);                                                       // Enable the system interrupt
}
 
void  DM_Timer::mode_configure(DMTIMER::e_DMTIMER_mode mode)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_sTIMER.TCLR.b.AR = LOW;  // clear autoreload mode
    m_sTIMER.TCLR.b.CE = LOW;  // clear compare mode

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the timer mode in TCLR register **/
    m_sTIMER.TCLR.reg |= mode; 
}
 
void  DM_Timer::prescaler_clk_enable(uint8_t ptv)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
   
    m_sTIMER.TCLR.b.PTV = 0x0;  // Clear the PTV field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Set the PTV field and enable the pre-scaler clock **/
    m_sTIMER.TCLR.b.PTV = ptv; 
    m_sTIMER.TCLR.b.PRE = HIGH;
}
 
void  DM_Timer::prescaler_clk_disable()
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Disable Pre-scaler clock **/
    m_sTIMER.TCLR.b.PRE = LOW;
}
 
void  DM_Timer::counter_set(uint32_t counter)
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode

    /** Set the counter value **/
    m_sTIMER.TCRR.reg = counter;
}
 
uint32_t  DM_Timer::counter_get()
{
    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    return  m_sTIMER.TCRR.reg;
}

/** Set the reload count value in the timer load register **/
void  DM_Timer::reload_set(uint32_t reload)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode

    /** Load the register with the re-load value **/
    m_sTIMER.TLDR.reg = reload;
}
 
/** Get the reload count value from the timer load register **/
uint32_t  DM_Timer::reload_get()
{
    /** Return the contents of TLDR **/
    return   m_sTIMER.TLDR.reg;
}
 
void  DM_Timer::GPO_configure(uint32_t gpo_cfg)
{
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    m_sTIMER.TCLR.b.GPO_CFG = LOW; // Clear the GPO_CFG field of TCLR

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode

    /** Write to the GPO_CFG field of TCLR **/
     m_sTIMER.TCLR.b.GPO_CFG = HIGH; 
}
 
void  DM_Timer::compare_set(uint32_t compare_val)
{
    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode

    /** Write the compare value to TMAR **/
    m_sTIMER.TMAR.reg = compare_val; 
}
 
uint32_t  DM_Timer::compare_get()
{
    /** Return the TMAR value **/
    return  m_sTIMER.TMAR.reg;
}
 
void  DM_Timer::IRQ_raw_set(DMTIMER::e_IRQ_flags int_flags)
{
    /** Trigger the events in IRQSTATUS_RAW register **/
    m_sTIMER.IRQSTATUS_RAW.reg = int_flags;
}
 
uint32_t  DM_Timer::IRQ_raw_get()
{
    /** Return the status of IRQSTATUS_RAW register **/
    return  m_sTIMER.IRQSTATUS_RAW.reg;
}
 
uint32_t  DM_Timer::IRQ_get()
{
    /** Return the status of IRQSTATUS register **/
    return  m_sTIMER.IRQSTATUS.reg;
}
 
void  DM_Timer::IRQ_clear(DMTIMER::e_IRQ_flags int_flags)
{
    /** Clear the interrupt status from IRQSTATUS register **/
    m_sTIMER.IRQSTATUS.reg = int_flags; 
}
 
void  DM_Timer::IRQ_enable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Enable the DMTimer interrupts represented by int_flags **/
    m_sTIMER.IRQENABLE_SET.reg = int_flags; 
}
 
void  DM_Timer::IRQ_disable(DMTIMER::e_IRQ_flags int_flags)
{
    /** Disable the DMTimer interrupts represented by int_flags **/
    m_sTIMER.IRQENABLE_CLR.reg = int_flags; 
}
 
void  DM_Timer::trigger_set()
{
    m_wait_for_write(DMTIMER::F_PEND_TTGR); // wait in posted mode

    /** Write a value to the register **/
    m_sTIMER.TTGR.reg = DMTIMER::TTGR_DEF_VALUE; 
}
 
uint32_t  DM_Timer::IRQ_enable_get()
{
    /** Return the status of register IRQENABLE_SET **/
    return  m_sTIMER.IRQENABLE_SET.reg;
}
  
void  DM_Timer::reset_configure(bool rst_option)
{
    /** Clear the SFT field of TSICR **/
    m_sTIMER.TSICR.b.SFT = LOW;

    /** Write the option sent by user to SFT field of TSICR **/
    m_sTIMER.TSICR.b.SFT = rst_option; 
}
 
void  DM_Timer::reset()
{
    /** Reset the DMTimer module **/
    m_sTIMER.TIOCP_CFG.b.SOFTRESET = HIGH;

    while( m_sTIMER.TIOCP_CFG.b.SOFTRESET);  
}

void  DM_Timer::set_debug_EMUFREE(bool emufree_val)
{
    /** Set debug suspend ignored(0x1) or frozen during debug (0x0 default)in DMTimer module **/
    m_sTIMER.TIOCP_CFG.b.EMUFREE = emufree_val;
}

bool  DM_Timer::get_debug_EMUFREE()
{
  return (bool)( m_sTIMER.TIOCP_CFG.b.EMUFREE);
}
 
void  DM_Timer::context_save(DMTIMERCONTEXT *p_context)
{
    p_context->tldr =  m_sTIMER.TLDR.reg;
    p_context->tmar =  m_sTIMER.TMAR.reg;
    p_context->irqenableset =  m_sTIMER.IRQENABLE_SET.reg;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    p_context->tcrr =  m_sTIMER.TCRR.reg;
    
    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    p_context->tclr =  m_sTIMER.TCLR.reg; 
}
 
void  DM_Timer::context_restore(DMTIMERCONTEXT *p_context)
{
    m_wait_for_write(DMTIMER::F_PEND_TLDR); // wait in posted mode
    m_sTIMER.TLDR.reg = p_context->tldr;

    m_wait_for_write(DMTIMER::F_PEND_TMAR); // wait in posted mode
    m_sTIMER.TMAR.reg = p_context->tmar;
    m_sTIMER.IRQENABLE_SET.reg = p_context->irqenableset;

    m_wait_for_write(DMTIMER::F_PEND_TCRR); // wait in posted mode
    m_sTIMER.TCRR.reg = p_context->tcrr;

    m_wait_for_write(DMTIMER::F_PEND_TCLR); // wait in posted mode
    m_sTIMER.TCLR.reg = p_context->tclr;  
}
 
void  DM_Timer::posted_mode_config(bool post_mode)
{ 
    /** Clear the POSTED field of TSICR **/
    m_sTIMER.TSICR.b.POSTED = LOW;

    /** Write to the POSTED field of TSICR **/
    m_sTIMER.TSICR.b.POSTED = post_mode;  
}  
