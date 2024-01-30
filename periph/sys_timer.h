#ifndef _SYS_TIMER_H
#define _SYS_TIMER_H

#include <cstddef> // for size_t
#include "PRCM.h"
#include "am335x_dmtimer.h"
#include "am335x_intc.h"

#define USE_DMTIMER_1ms
#define SYST_RLD_COUNT                (0xffffa261) // 1ms approximate

#if defined(USE_DMTIMER_1ms)
    #define SYST_t         REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type
    #define SYST_TIMER_ptr REGS::DMTIMER1MS::AM335X_DMTIMER_1MS
#else
    #define SYST_t         REGS::DMTIMER::AM335x_DMTIMER_Type
    #define SYST_TIMER_ptr REGS::DMTIMER::AM335X_DMTIMER_2
#endif

void sys_timer_irqhandler(void *p_obj);
extern am335x_intc intc;

template <typename DMT> 
class sys_timer : public am335x_dmtimer<DMT>
{
public:
    sys_timer(DMT *p_regs) 
    : am335x_dmtimer<DMT>(p_regs),
      m_intc(intc)
    { 
        m_DMTIMER_num = am335x_dmtimer<DMT>::get_DMTIMER_number();
        m_DMTIMER_sys_isr_num = am335x_dmtimer<DMT>::get_DMTIMER_sys_interrupt();
        m_isr_handler = (isr_handler_t)sys_timer_irqhandler;
    }

    float  get_ms(void)  { return am335x_dmtimer<DMT>::m_time; }
    
    inline void  increment(float dt = 1.0)
    {  
        am335x_dmtimer<DMT>::m_time += (float)dt;
    }

    void  init()
    {  
    #if defined(USE_DMTIMER_1ms)
        setup_1ms_precise();
    #else
        setup();
    #endif
    }
    /**
    ** Setup the timer for one-shot and compare mode.
    ** Setup the timer to generate the tick interrupts at the required frequency.
    **/
    void setup(REGS::DMTIMER::e_DMTIMER_mode  mode = REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE, 
                                    uint32_t  reload_value = SYST_RLD_COUNT, 
                                    uint32_t  priority = (REGS::INTC::MAX_IRQ_PRIORITIES - 1))
    {          
        REGS::PRCM::run_clk_DMTIMER(m_DMTIMER_num); 
    
        // setup timer interrupt in INTC
        m_intc.register_handler(m_DMTIMER_sys_isr_num, m_isr_handler);     // Registering dmtimer_irqhandler
        m_intc.priority_set(m_DMTIMER_sys_isr_num, priority);      // Set the lowest priority
        m_intc.unmask_interrupt(m_DMTIMER_sys_isr_num); 
        
        am335x_dmtimer<DMT>::counter_set(reload_value);                                  //Load the counter with the initial count value
        am335x_dmtimer<DMT>::reload_set(reload_value);                                   //Load the load register with the reload count value
        am335x_dmtimer<DMT>::mode_configure(mode);  
        
        am335x_dmtimer<DMT>::IRQ_enable(REGS::DMTIMER::IRQ_OVF);
        
        am335x_dmtimer<DMT>::enable();
    }

    // specific setup for DM_TIMER 1ms precise value, 
    // if using another DMTIMER(0, 2,3,4,5,6,7) - use setup(REGS::DMTIMER::e_DMTIMER_mode mode, uint32_t reload_value, uint32_t priority)
    void setup_1ms_precise(uint32_t priority = (REGS::INTC::MAX_IRQ_PRIORITIES - 1),
      REGS::PRCM::e_TIMER1MS_CLKSEL clocksource = REGS::PRCM::MS1_32KHZ)
    {
        //  wake up configs
        //HWREG(0x44e31010) = 0x214; //TIOCP_CFG  set EnaWakeup,SMART_IDLE,ClockActivity = 0x2

        //  enable overflow int
        //HWREG(0x44e3101c) = 0x2; //TIER

        //  enable overflow wakeup
        //HWREG(0x44e31020) = 0x2;  //TWER

        REGS::PRCM::run_clk_DMTIMER_1ms(clocksource);

        m_intc.register_handler(m_DMTIMER_sys_isr_num, m_isr_handler);     // Registering dmtimer_irqhandler
        m_intc.priority_set(m_DMTIMER_sys_isr_num, priority);      // Set the lowest priority
        m_intc.unmask_interrupt(m_DMTIMER_sys_isr_num); 
        
        am335x_dmtimer<DMT>::prescaler_clk_disable();
        am335x_dmtimer<DMT>::counter_set(0xFFFFFFE0u); 
        am335x_dmtimer<DMT>::reload_set(0xFFFFFFE0u); 
        am335x_dmtimer<DMT>::set_1ms_block(232000,-768000);
        am335x_dmtimer<DMT>::mode_configure(REGS::DMTIMER::MODE_AUTORLD_NOCMP_ENABLE);   //Configure the DMTimer for Auto-reload and compare mode 
        
        am335x_dmtimer<DMT>::IRQ_enable(REGS::DMTIMER::IRQ_OVF);
        
        am335x_dmtimer<DMT>::enable();
    }

    void sys_interrupt_enable()  { m_intc.unmask_interrupt(m_DMTIMER_sys_isr_num);  }
    void sys_interrupt_disable() { m_intc.mask_interrupt(m_DMTIMER_sys_isr_num); }

private:  
                    isr_handler_t  m_isr_handler;
       REGS::DMTIMER::e_TIMER_NUM  m_DMTIMER_num;
             REGS::INTC::e_INT_ID  m_DMTIMER_sys_isr_num;

                      am335x_intc &m_intc;              // for interrupt setup and management
};

extern sys_timer<SYST_t> sys_time;

inline void sys_timer_irqhandler(void *p_obj)
{  
    sys_time.IRQ_disable(REGS::DMTIMER::IRQ_OVF); // Disable the DMTimer interrupts    
    sys_time.IRQ_clear(REGS::DMTIMER::IRQ_OVF);   // Clear the status of the interrupt flags 

    sys_time.increment();
    
    sys_time.IRQ_enable(REGS::DMTIMER::IRQ_OVF);  // Enable the DM_Timer interrupts
    sys_time.sys_interrupt_enable(); 
}



#endif //_SYS_TIMER_H