#ifndef __OS_TIMER_H
#define __OS_TIMER_H

#include "DM_Timer.h"

//#define TIMER_INITIAL_COUNT             (0xffffa261) // 1ms approximate
#define OS_TIMER_RLD_COUNT                (0xffffa261) // 1ms approximate

void DM_Timer_irqhandler(void *p_obj);

class OS_Timer : public DM_Timer
{
public:
    OS_Timer(DMTIMER::AM335x_DMTIMER_Type *p_tmr_regs) 
    : DM_Timer(p_tmr_regs),
      m_prcm_module(prcm_module),
      m_int_controller(intc)
    { 
        m_DMTIMER_number = DM_Timer::get_DMTIMER_number();
        m_DMTIMER_sys_interrupt = DM_Timer::get_DMTIMER_sys_interrupt();
        m_isr_handler = (INTC::isr_handler_t)DM_Timer_irqhandler;
    }

    /**
    ** Setup the timer for one-shot and compare mode.
    ** Setup the timer to generate the tick interrupts at the required frequency.
    **/
    void setup(uint32_t reload_value)
    {
        // run clock for timer instance
        m_prcm_module.run_clk_DMTIMER(m_DMTIMER_number); 
    
        // setup timer interrupt in INTC
        m_int_controller.register_handler(m_DMTIMER_sys_interrupt, m_isr_handler);            // Registering DMTimer_irqhandler
        m_int_controller.priority_set(m_DMTIMER_sys_interrupt,(INTC::MAX_IRQ_PRIORITIES -1), INTC::HOSTINT_ROUTE_IRQ); // Set the lowest priority
        sys_interrupt_enable(); 
    
        // setup timer itself
        DM_Timer::counter_set(reload_value); //Load the counter with the initial count value
        DM_Timer::reload_set(reload_value);    //Load the load register with the reload count value
        DM_Timer::mode_configure(DMTIMER::MODE_AUTORELOAD); // mode : autoreload and no compare
        DM_Timer::enable();
    }

    void sys_interrupt_enable()  { m_int_controller.system_enable(m_DMTIMER_sys_interrupt);  }
    void sys_interrupt_disable() { m_int_controller.system_disable(m_DMTIMER_sys_interrupt); }

private:
          INTC::isr_handler_t  m_isr_handler;
         DMTIMER::e_TIMER_NUM  m_DMTIMER_number;
        INTC::e_SYS_INTERRUPT  m_DMTIMER_sys_interrupt;

    power_reset_clock_control &m_prcm_module;      // for clock contrlol setup and management
    Interrupt_controller      &m_int_controller;   // for interrupt setup and management
};

extern OS_Timer os_timer;

inline void DM_Timer_irqhandler(void *p_obj)
{  
    os_timer.IRQ_disable(DMTIMER::IRQ_OVF); // Disable the DMTimer interrupts    
    os_timer.IRQ_clear(DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags 

    OSTimeTick();
    
    os_timer.IRQ_enable(DMTIMER::IRQ_OVF);  // Enable the DM_Timer interrupts
    os_timer.sys_interrupt_enable();  
}

#endif //__OS_TIMER_H