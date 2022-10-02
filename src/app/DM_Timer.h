#ifndef __DM_TIMER_H
#define __DM_TIMER_H

#include "AM335x_mem_map.h"

class DM_Timer
{
public:
                    typedef struct dmtimerContext
                    {
                        uint32_t tldr;
                        uint32_t tmar;
                        uint32_t irqenableset;
                        uint32_t tcrr;
                        uint32_t tclr;
                    }DMTIMERCONTEXT;
                    
                    DM_Timer(DMTIMER::AM335x_DMTIMER_Type * p_tmr);
                   ~DM_Timer() {}

		      void  enable();
              void  disable();

              void  mode_configure(DMTIMER::e_DMTIMER_mode mode);              
              void  prescaler_clk_enable(uint8_t ptv);
              void  prescaler_clk_disable();
              void  counter_set(uint32_t counter);
          uint32_t  counter_get();
              void  reload_set(uint32_t reload);    // Set the reload count value in the timer load register.
          uint32_t  reload_get();                   // Get the reload count value from the timer load register
              void  GPO_configure(uint32_t gpo_cfg);
              void  compare_set(uint32_t compare_val);
          uint32_t  compare_get();
              void  set_irq_handler(void(*function)(void *p_obj)) { m_irq_handler = function; }
              
              void  IRQ_raw_set(DMTIMER::e_IRQ_flags int_flags);
          uint32_t  IRQ_raw_get();
          uint32_t  IRQ_get();
              void  IRQ_clear(DMTIMER::e_IRQ_flags int_flags);
              void  IRQ_enable(DMTIMER::e_IRQ_flags int_flags);
              void  IRQ_disable(DMTIMER::e_IRQ_flags int_flags);
              void  trigger_set();
          uint32_t  IRQ_enable_get();

              bool  check_busy()  const  { return m_is_paused; }
              void  reset_configure(bool rst_option);
              void  reset();
              void  set_debug_EMUFREE(bool emufree_val);    //  [0x0 = frozen during debug; 0x1 = debug suspend ignored]
              bool  get_debug_EMUFREE();
              void  posted_mode_config(bool post_mode);
              void  context_save(DMTIMERCONTEXT *p_context);
              void  context_restore(DMTIMERCONTEXT *p_context);
            
private:
                //IRQn_Type   m_IRQn;         // irq module  
                  void  m_wait_for_write(DMTIMER::e_TWPS_flags twps_mask)
                  {
                      /** Wait for previous write to complete if posted mode enabled**/
                      if(m_pTIMER->TSICR.b.POSTED)
                          while(m_pTIMER->TWPS.reg & twps_mask);
                  }
              
DMTIMER::AM335x_DMTIMER_Type *m_pTIMER;              
               void (*m_irq_handler)(void *p_obj) { nullptr };
           uint64_t  m_time {0}; // the timer itself
               bool  m_is_paused { true }; 
}; 
 
extern     void DMTimer_irqhandler(void *p_obj);
extern DM_Timer dm_timer_2;
#endif //__DM_TIMER_H