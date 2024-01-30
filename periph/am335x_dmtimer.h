#ifndef __AM335x_DMTIMER_H
#define __AM335x_DMTIMER_H

#include <stdint.h>
#include "DMTIMER.h"
#include "DMTIMER1MS.h"
#include "PRCM.h"
#include "INTC.h"

template <typename DMT = REGS::DMTIMER::AM335x_DMTIMER_Type> // and REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type
class am335x_dmtimer
{
public:
                typedef struct
                {
                    uint32_t tldr;
                    uint32_t tmar;
                    uint32_t irqenableset;
                    uint32_t tcrr;
                    uint32_t tclr;
                } dmtimer_context_t;
public:                      
                 am335x_dmtimer(DMT *p_tmr_regs);
                
                ~am335x_dmtimer() {}

                /**
                 * @brief   This API will start the timer. 
                 * @note    The timer must be configured before it is started/enabled.
                 **/
		        void  enable();

                /**
                 * @brief   This API will stop the timer. 
                 **/
                void  disable();

                /**
                 * @brief   This API will configure the timer in combinations of 
                 *          'One Shot timer' and 'Compare' Mode or 'Auto-reload timer' 
                 *          and 'Compare' Mode.  
                 * @param   mode    Mode for enabling the timer.
                 *
                 *    'mode' can take the following values \n
                 *    MODE_ONESHOT_CMP_ENABLE   - One shot and compare mode enabled \n
                 *    MODE_ONESHOT_NOCMP_ENABLE - One shot enabled, compare mode disabled \n
                 *    MODE_AUTORLD_CMP_ENABLE   - Auto-reload and compare mode enabled \n
                 *    MODE_AUTORLD_NOCMP_ENABLE - Auto-reload enabled, compare mode 
                 *                                disabled \n
                 **/
                void  mode_configure(REGS::DMTIMER::e_DMTIMER_mode mode);              
                
                /**
                 * @brief   This API will configure and enable the pre-scaler clock.
                 * @param   ptv          Pre-scale clock Timer value.
                 *    'ptv' can take the following values \n
                 *    REGS::DMTIMER::CLK_DIV_BY_2 - Timer clock divide by 2 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_4 - Timer clock divide by 4 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_8 - Timer clock divide by 8 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_16 - Timer clock divide by 16 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_32 - Timer clock divide by 32 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_64 - Timer clock divide by 64 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_128 - Timer clock divide by 128 \n
                 *    REGS::DMTIMER::CLK_DIV_BY_256 - Timer clock divide by 256 \n
                 **/               
                void  prescaler_clk_enable(REGS::DMTIMER::e_PRSC ptv);
                
                /**
                 * @brief   This API will disable the pre-scaler clock.
                 **/
                void  prescaler_clk_disable();

                /**
                 * @brief   This API will set 1ms block values for precision 1ms only for DMTIMER_1MS
                 **/
                void  set_1ms_block(int32_t pos = 232000, int32_t neg = (-768000));
                
                /**
                 * @brief   Set/Write the Counter register with the counter value.
                 * @param   counter       Count value for the timer.
                 * @note    Value can be loaded into the counter register when the counter is 
                 *          stopped or when it is running.
                 **/
                void  counter_set(uint32_t counter);
                
                /**
                 * @brief   Get/Read the counter value from the counter register.
                 * @return  This API returns the count value present in the DMTimer Counter
                 *          register.
                 * @note:   Value can be read from the counter register when the counter is
                 *          stopped or when it is running.
                 **/
                uint32_t  counter_get();
                
                /**
                 * @brief   Set the reload count value in the timer load register.
                 * @param   reload        The reload count value of the timer.
                 * @note:   It is recommended to not use reload value as 0xFFFFFFFF as it can 
                 *          lead to undesired results.
                 **/
                void  reload_set(uint32_t reload);
                
                /**
                 * @brief   Get the reload count value from the timer load register.
                 * @return  This API returns the value present in DMTimer Load Register.
                 **/            
                uint32_t  reload_get();
                
                /**
                 * @brief   Configure general purpose output pin.
                 * @param   gpo_cfg        General purpose output.
                 *  
                 *    'gpo_cfg' can take the following values \n
                 *    true  - PORGPOCFG drives 0 \n
                 *    false - PORGPOCFG drives 1 \n  
                 **/                
                void  GPO_configure(bool gpo_cfg);
                
                /**
                * @brief   Set the match register with the compare value.
                * @param   compare_val    Compare value.
                **/               
                void  compare_set(uint32_t compare_val);
                
                /**
                * @brief   Get the match register contents.
                * @return  This API returns the match register contents.
                **/           
                uint32_t  compare_get();

                /**
                 * @brief   Trigger IRQ event by software.
                 * @param   int_flags      Variable used to trigger the events.
                 * 
                 *    'int_flags' can take the following values \n
                 *    IRQ_NONE = Trigger IRQ none \n,
                 *    IRQ_TCAR - Trigger IRQ status for capture \n
                 *    IRQ_OVF  - Trigger IRQ status for overflow \n
                 *    IRQ_MAT  - Trigger IRQ status for match \n
                 * @note !this function is not in the registers AM335x_DMTIMER1MS_Type! 
                 **/             
                void  IRQ_raw_set(REGS::DMTIMER::e_IRQ_flags int_flags);
                
                /**
                 * @brief   Read the status of IRQSTATUS_RAW register.
                 * @return  This API returns the contents of IRQSTATUS_RAW register.
                 * @note    !this function is not in the registers AM335x_DMTIMER1MS_Type!
                 **/            
                uint32_t  IRQ_raw_get();

                /**
                 * @brief   Read the status of IRQ_STATUS register.
                 * @return  This API returns the status of IRQSTATUS register.
                 **/
                uint32_t  IRQ_get();
                
                /**
                 * @brief   Clear the status of interrupt events.
                 * @param   int_flags      Variable used to clear the events.
                 *
                 *   'int_flags' can take the following values \n
                 *    IRQ_TCAR - Clear IRQ status for capture \n
                 *    IRQ_OVF  - Clear IRQ status for overflow \n
                 *    IRQ_MAT  - Clear IRQ status for match \n
                 **/
                void  IRQ_clear(REGS::DMTIMER::e_IRQ_flags int_flags);
                
                /**
                * @brief   Enable the DMTimer interrupts.
                * @param   int_flags      Variable used to enable the interrupts.
                *
                *    'int_flags' can take the following values \n
                *    IRQ_TCAR - IRQ enable for capture \n
                *    IRQ_OVF - IRQ enable for overflow \n
                *    IRQ_MAT - IRQ enable for match \n
                **/               
                void  IRQ_enable(REGS::DMTIMER::e_IRQ_flags int_flags);
                
                /**
                * @brief   Disable the DMTimer interrupts.
                * @param   int_flags      Variable used to disable the interrupts.
                *
                *    'int_flags' can take the following values \n
                *    IRQ_TCAR - IRQ disable for capture \n
                *    IRQ_OVF - IRQ disable for overflow \n
                *    IRQ_MAT - IRQ disable for match \n
                **/               
                void  IRQ_disable(REGS::DMTIMER::e_IRQ_flags int_flags);
                
                /**
                 * @brief   Set/enable the trigger write access.
                 * @note    When we have enabled the timer in Auto-reload mode, the value from 
                 *          TLDR is reloaded into TCRR when a overflow condition occurs. But if 
                 *          we want to load the contents from TLDR to TCRR before overflow 
                 *          occurs then call this API.
                 **/               
                void  trigger_set();
                
                /**
                 * @brief   Read the status of IRQENABLE_SET register.
                 * @return  This API returns the status of IRQENABLE_SET register.
                 **/
                uint32_t  IRQ_enable_get();

                /**
                 * @brief   Enable/Disable software reset for DMTimer module.
                 * @param   rst_option     Enable/Disable reset option for DMTimer.
                 *          
                 *    'rst_option' can take the following values \n
                 *    false  - Software reset is enabled \n
                 *    ture - Software reset is disabled \n   
                 **/                
                void  reset_configure(bool rst_option);
                
                /**
                 * @brief   Reset the DMTimer module.
                 **/
                void  reset();

                /**
                 * @brief   Configure the posted mode of DMTimer.
                 * @param   post_mode      Posted mode configuration.
                 *
                 *    'post_mode' can take the following values \n
                 *    false - Posted mode not used \n
                 *    true - Posted mode used \n
                 **/               
                void  posted_mode_config(bool post_mode);

                /**
                 * @brief   Check posted mode  is enbled
                 * @return  true -  Posted mode active
                 *          false -  Posted mode inactive
                 **/
                bool  posted_status_get();
                
                /**
                 * @brief   This API stores the context of the DMTimer
                 **/               
                void  context_save();
                
                /**
                 * @brief   This API restores the context of the DMTimer
                 **/                
                void  context_restore();

                /**
                 * @brief   Get hardware timer number
                 * @return  sequence number of the timer involved
                 **/
REGS::DMTIMER::e_TIMER_NUM  get_DMTIMER_number();

                /**
                 * @brief   Get hardware timer number interrupt
                 * @return  sequence number of timer interrupt
                 **/
REGS::INTC::e_INT_ID get_DMTIMER_sys_interrupt();

                /**
                 * @brief   Check if timer is enbled
                 * @return  true - timer is enabled
                 *          false - timer is disabled
                 **/
                bool  check_busy()  const  { return m_is_paused; }

                /**
                 * @brief   Froze timer during debug
                 * @param   true -debug suspend ignored
                 *          false - frozen during debug;
                 **/
                void  set_debug_EMUFREE(bool emufree_val);    //  [0x0 = frozen during debug; 0x1 = debug suspend ignored]
                
                /**
                 * @brief   Gets frozen state during debug
                 * @return  true - debug suspend ignored
                 *          false - frozen during debug;
                 **/                
                bool  get_debug_EMUFREE();

protected:
     volatile    float  m_time; // the timer time     
                  bool  m_is_paused { true }; 
private:
     dmtimer_context_t  m_context;  // dmtimer context for rebooting
                  void  m_wait_for_write(REGS::DMTIMER::e_TWPS_flags twps_mask);

                  DMT  &m_regs;     // am335x_dmtimer registers
};

extern     void dmtimer_irqhandler(void *p_obj);

extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_0;
extern am335x_dmtimer<REGS::DMTIMER1MS::AM335x_DMTIMER1MS_Type> dm_timer_1ms;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_2;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_3;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_4;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_5;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_6;
extern am335x_dmtimer<REGS::DMTIMER::AM335x_DMTIMER_Type> dm_timer_7;

#endif //__DM_TIMER_H