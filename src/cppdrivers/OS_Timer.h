#ifndef __OSTIMER_H
#define __OSTIMER_H

#include "DM_Timer.h"

#define TIMER_INITIAL_COUNT             (0xffffa261) // 1ms approximate
#define TIMER_RLD_COUNT                 (0xffffa261) // 1ms approximate
#define OS_TIMER_INTERRUPT              INTC::TINT5

extern     void DMTimer_irqhandler(void *p_obj);

class OS_Timer : public DM_Timer
{
public:
    OS_Timer(DMTIMER::AM335x_DMTIMER_Type *p_tmr_regs) 
    : DM_Timer(p_tmr_regs),
      m_prcm_module(prcm_module),
      m_int_controller(intc)
    { }

    /**
    ** Setup the timer for one-shot and compare mode.
    ** Setup the timer to generate the tick interrupts at the required frequency.
    **/
    void setup()
    {
        uint32_t dmtimer_mode =  DMTIMER::MODE_AUTORELOAD | (!DMTIMER::MODE_COMPARE); //  mode : autoreload and no compare

        // run clock for timer instance
        m_prcm_module.run_clk_DMTIMER(get_DMTIMER_number()); 
    
        // setup timer interrupt in INTC
        m_int_controller.register_handler(OS_TIMER_INTERRUPT,(INTC::Handler_ptr_t)DMTimer_irqhandler);            // Registering DMTimer_irqhandler
        m_int_controller.priority_set(OS_TIMER_INTERRUPT,(INTC::MAX_IRQ_PRIORITIES -1), INTC::HOSTINT_ROUTE_IRQ); // Set the lowest priority
        m_int_controller.system_enable(OS_TIMER_INTERRUPT); 
    
        counter_set(TIMER_INITIAL_COUNT); //Load the counter with the initial count value
        reload_set(TIMER_RLD_COUNT);    //Load the load register with the reload count value
        mode_configure((DMTIMER::e_DMTIMER_mode)dmtimer_mode); //Configure the DMTimer for Auto-reload and compare mode
        enable();
    }

    void  set_irq_handler(void(*function)(void *p_obj)) { m_irq_handler = function; }

private:
                                void (*m_irq_handler)(void *p_obj) { nullptr };
    power_reset_clock_control  &m_prcm_module;      // for clock contrlol setup and management
    Interrupt_controller       &m_int_controller;   // for interrupt setup and management



};

extern OS_Timer os_timer;

#endif //__OSTIMER_H