#ifndef __DM_TIMER_H
#define __DM_TIMER_H

#include "AM335x_mem_map.h"

class DM_Timer
{
public:
                    DM_Timer(DMTIMER::AM335x_DMTIMER_Type * p_tmr)
                    :m_pTIMER(p_tmr) {}

					uint32_t  enable() { return m_pTIMER->TIDR.b.Y_MINOR; }
              void  disable() { m_pTIMER->TIDR.b.FUNC = 0x7FF; }

              /*
              void  mode_configure(uint32_t mode);
              void  prescaler_clk_enable(uint32_t ptv);
              void  prescaler_clk_disable();
              void  counter_set(uint32_t counter);
          uint32_t  counter_get();
              void  reload_set(uint32_t reload);
          uint32_t  reload_get();
              void  GPO_configure(uint32_t gpo_cfg);
              void  compare_set(uint32_t compare_val);
          uint32_t  compare_get();

              void  IRQ_raw_set(uint32_t int_flags);
          uint32_t  IRQ_raw_get();
          uint32_t  IRQ_get();
              void  IRQ_clear(uint32_t int_flags);
              void  IRQ_enable(uint32_t int_flags);
              void  IRQ_disable(uint32_t int_flags);
              void  trigger_set();
          uint32_t  IRQ_enable_get();
              void  on_IRQ();
              void  on_FIQ(); 

              void  reset_configure(uint32_t rst_option);
              void  reset();
              void  context_save(DMTIMERCONTEXT *p_context);
              void  context_restore(DMTIMERCONTEXT *p_context);
              void  posted_mode_config(uint32_t post_mode);
          uint32_t  write_posted_status_get();

              bool  check_busy()  const  { return m_is_paused; }
              void  emulation_mode_configure(uint32_t emuMode);             
 

              void  set_callback(void(*function)(uint32_t)) { m_irq_callback = function; }
            */
private:
         DMTIMER::AM335x_DMTIMER_Type  * m_pTIMER;
         //IRQn_Type   m_IRQn;         // irq module
void (*m_irq_callback)(uint32_t) { nullptr };

          uint64_t  m_time {0}; // the timer itself
              bool  m_is_paused { true };
}; 

extern DM_Timer dm_timer_0;
#endif //__DM_TIMER_H