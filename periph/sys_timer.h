#ifndef __OS_TIMER_H
#define __OS_TIMER_H

#include <cstddef> // for size_t
#include "PRCM.h"
#include "am335x_dmtimer.h"
#include "am335x_intc.h"

#define SYS_TIMER_RLD_COUNT                (0xffffa261) // 1ms approximate

void sys_timer_irqhandler(void *p_obj);
extern am335x_intc intc;

class sys_timer : public am335x_dmtimer
{
public:
    sys_timer(REGS::DMTIMER::AM335x_DMTIMER_Type *p_regs) 
    : am335x_dmtimer(p_regs),
      m_intc(intc)
    { 
        m_DMTIMER_num = am335x_dmtimer::get_DMTIMER_number();
        m_DMTIMER_sys_isr_num = am335x_dmtimer::get_DMTIMER_sys_interrupt();
        m_isr_handler = (isr_handler_t)sys_timer_irqhandler;
    }

    uint64_t  get_ms(void)  { return am335x_dmtimer::m_time; }
    
    inline void  increment(size_t dt = 1)
    {  
        am335x_dmtimer::m_time += dt;
    }

    /**
    ** Setup the timer for one-shot and compare mode.
    ** Setup the timer to generate the tick interrupts at the required frequency.
    **/
    void setup(REGS::DMTIMER::e_DMTIMER_mode mode, uint32_t reload_value, uint32_t priority)
    {
        // run clock for timer instance
        REGS::PRCM::run_clk_DMTIMER(m_DMTIMER_num); 
    
        // setup timer interrupt in INTC
        m_intc.register_handler(m_DMTIMER_sys_isr_num, m_isr_handler);     // Registering dmtimer_irqhandler
        m_intc.priority_set(m_DMTIMER_sys_isr_num, priority);      // Set the lowest priority
        m_intc.unmask_interrupt(m_DMTIMER_sys_isr_num); 
        
        am335x_dmtimer::counter_set(reload_value);                                  //Load the counter with the initial count value
        am335x_dmtimer::reload_set(reload_value);                                   //Load the load register with the reload count value
        am335x_dmtimer::mode_configure(mode);   //Configure the DMTimer for Auto-reload and compare mode 
        
        am335x_dmtimer::IRQ_enable(REGS::DMTIMER::IRQ_OVF);
        
        am335x_dmtimer::enable();
    }

    void sys_interrupt_enable()  { m_intc.unmask_interrupt(m_DMTIMER_sys_isr_num);  }
    void sys_interrupt_disable() { m_intc.mask_interrupt(m_DMTIMER_sys_isr_num); }

private:  
                    isr_handler_t  m_isr_handler;
       REGS::DMTIMER::e_TIMER_NUM  m_DMTIMER_num;
             REGS::INTC::e_INT_ID  m_DMTIMER_sys_isr_num;

                      am335x_intc &m_intc;              // for interrupt setup and management
};

extern sys_timer sys_time;

inline void sys_timer_irqhandler(void *p_obj)
{  
    sys_time.IRQ_disable(REGS::DMTIMER::IRQ_OVF); // Disable the DMTimer interrupts    
    sys_time.IRQ_clear(REGS::DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags 

    sys_time.increment();
    
    sys_time.IRQ_enable(REGS::DMTIMER::IRQ_OVF);  // Enable the DM_Timer interrupts
    sys_time.sys_interrupt_enable(); 
}



#endif //__OS_TIMER_H