#ifndef _AM335X_INTC_H_
#define _AM335X_INTC_H_

#include <stdint.h>
#include "INTC.h"

typedef void (*isr_handler_t)(void *p_obj);

class am335x_intc  
{
public:
    am335x_intc()
    :m_INTC_regs(*REGS::INTC::AM335x_INTC) {}
    ~am335x_intc() {}

    /**
      * @brief   This API is used to initialize the interrupt controller. This API  
      *          shall be called before using the interrupt controller. 
    **/
    void  init (void);

    /**
     * @brief    Registers an interrupt Handler in the interrupt vector table for
     *           system interrupts. 
     * @param    int_id - Interrupt Number
     * @param    pfn_handler - Function pointer to the ISR
     * 
     *           Note: When the interrupt occurs for the sytem interrupt number indicated,
     *           the control goes to the ISR given as the parameter.
     **/
    void  register_handler(REGS::INTC::e_INT_ID  int_id,  isr_handler_t isr_fnct);
    
    /**
    * @brief   Unregisters an interrupt
    * @param   int_id - Interrupt Number
    * 
    *          Note: Once an interrupt is unregistered it will enter infinite loop once
    *          an interrupt occurs
    **/
    void  unregister_handler(REGS::INTC::e_INT_ID int_id);
    
    /**
    * @brief   Sets the interface clock to be free running
    * @param   true - automatic clock gating strategy is applied
    *          based on the interface bus activity.
    *          false - clk freerun set
    **/
    void  interface_clk_set(bool mode);

    /**
    * @brief   Enables protection mode for the interrupt controller register access.
    * @param   true - When the protection is enabled, the registers will be accessible only
    *          in privileged mode of the CPU.
    *          false - When the protection is disabled, the registers will be accessible 
    *          in both unprivileged and privileged mode of the CPU.
    **/       
    void  protection_enable(bool mode);

    /**
     * @brief   Enables input synchronizer clock
     * @param   true - Input synchronizer clock is auto-gated
     *          false - Input synchronizer clock is free run
    **/        
    void  low_power_turbo(bool mode); 

    /**
     * @brief   Enables of functional clock
     * @param   false - functional clock is free running.
     *          true - functional clock gating strategy is applied.
    **/        
    void  low_power_funcidle(bool mode);

    /**
     * @brief   Sets the given priority threshold value. 
     * @param   threshold - Priority threshold value
     *          'threshold' can take any value from 0x00 to 0x7F. To disable
     *          priority threshold, write 0xFF.
    **/
    void  priority_threshold_set(uint8_t threshold);

    /**
     * @brief   Sets software interrupt for the given interrupt number.
     * @param   int_id - the system interrupt number, for which software interrupt
     *                    to be generated
    **/       
    void  software_int_set(REGS::INTC::e_INT_ID int_id);

    /**
     * @brief   Clears the software interrupt for the given interrupt number.
     * @param   int_id - the system interrupt number, for which software interrupt
     *                    to be cleared.
    **/       
    void  software_int_clear(REGS::INTC::e_INT_ID int_id);

    /**
     * @brief  Enables the processor IRQ only in CPSR. Makes the processor to 
     *         respond to IRQs.  This does not affect the set of interrupts 
     *         enabled/disabled in the AINTC.
     * 
     *         Note: This function call shall be done only in previleged mode of ARM
    **/       
    void  master_IRQ_enable(void);

    /**
     * @brief  Disables the processor IRQ only in CPSR.Prevents the processor to 
     *         respond to IRQs.  This does not affect the set of interrupts 
     *         enabled/disabled in the AINTC.
     * 
     *         Note: This function call shall be done only in previleged mode of ARM
    **/        
    void  master_IRQ_disable(void);

    /**
     * @brief  Enables the processor FIQ only in CPSR. Makes the processor to 
     *         respond to FIQs.  This does not affect the set of interrupts 
     *         enabled/disabled in the AINTC.
     * 
     *         Note: This function call shall be done only in previleged mode of ARM
    **/        
    void  master_FIQ_enable(void);

    /**
     * @brief  Disables the processor FIQ only in CPSR.Prevents the processor to 
     *         respond to FIQs.  This does not affect the set of interrupts 
     *         enabled/disabled in the AINTC.
     * 
     *         Note: This function call shall be done only in previleged mode of ARM
    **/       
    void  master_FIQ_disable(void);

    /**
     * @brief   This API enables the system interrupt in AINTC. However, for 
     *          the interrupt generation, make sure that the interrupt is 
     *          enabled at the peripheral level also. 
     * @param   int_id  - Interrupt number
    **/        
    void  unmask_interrupt(REGS::INTC::e_INT_ID int_id);

    /**
     * @brief   This API disables the system interrupt in INTC.
     * @param   int_id  - Interrupt number
    **/        
    void  mask_interrupt(REGS::INTC::e_INT_ID int_id);

    /**
     * @brief   Restore the processor IRQ only status. This does not affect 
     *          the set of interrupts enabled/disabled in the INTC.
     * @param   The status returned by the IntDisable fundtion.
     * 
     *          Note: This function call shall be done only in previleged mode of ARM
    **/
    void  sys_enable(uint8_t  status);

    /**
     * @brief    Read and save the stasus and Disables the processor IRQ .
     *           Prevents the processor to respond to IRQs.  
     * @return   Current status of IRQ
     * 
     *           Note: This function call shall be done only in previleged mode of ARM
    **/     
    uint8_t  sys_disable(void);

    /**
     * @brief   This API assigns a priority to an interrupt and routes it to
     *          either IRQ or to FIQ. Priority 0 is the highest priority level
     *          Among the host interrupts, FIQ has more priority than IRQ.
     * @param   int_id   - Interrupt number
     * @param   priority - Interrupt priority level
     * @param   host_int_route - The host interrupt IRQ/FIQ to which the interrupt
     *          is to be routed.
     * 
     *          'priority' can take any value from 0 to 127, 0 being the highest and
     *          127(0x7F) being the lowest priority.              
     *
     *          'host_int_route' can take one of the following values \n
     *          REGS::INTC::HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
     *          REGS::INTC::HOSTINT_ROUTE_FIQQ - To route the interrupt to FIQ
    **/  
    #if defined(am335x)     
        void  priority_set(REGS::INTC::e_INT_ID int_id, uint32_t priority);
    #else
        // not for am335x SoCs
        void  priority_set(REGS::INTC::e_INT_ID int_id, uint32_t priority, uint32_t host_int_route); 
    #endif
    /**
     * @brief    Returns the status of the interrupts FIQ and IRQ.
     * @return   Status of interrupt as in CPSR.
     * 
     *           Note: This function call shall be done only in previleged mode of ARM
    **/    
    uint32_t  master_status_get(void);
    
    /**
     * @brief   Reads the active IRQ number.
     * @return  Active IRQ number.
    **/    
    uint32_t  active_IRQ_num_get(void); 

    #if !defined(am335x)  
        // not for am335x SoCs
        uint32_t  active_FIQ_num_get(void);  
    #endif

    /**
     * @brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
     *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
     * @return  Spurious(masked) IRQ Flag.
    **/    
    uint32_t  spur_IRQ_flag_get(void); 

    #if !defined(am335x)  
        // not for am335x SoCs
        uint32_t  spur_FIQ_flag_get(void);  
    #endif

    /**
     * @brief   Returns the currently active IRQ priority level.
     * @return  Current IRQ priority 
    **/    
    uint32_t  curr_IRQ_priorigty_get(void); 
    #if !defined(am335x)   
        // not for am335x SoCs
        uint32_t  curr_FIQ_priority_get(void);  
    #endif

    /**
     * @brief   Returns the priority threshold.
     * @return  Priority threshold value.
    **/     
    uint8_t  priority_threshold_get(void);

    /**
     * @brief   Returns the raw interrupt status before masking.
     * @param   int_id - the system interrupt number.
     * @return  true - if the raw status is set \n
     *          false - if the raw status is not set.   
    **/       
    bool  raw_status_get(REGS::INTC::e_INT_ID int_id);

    /**
     * @brief   Returns the IRQ status after masking.
     * @param   int_id - the system interrupt number
     * @return  true - if interrupt is pending \n
     *          false - in no interrupt is pending
    **/        
    bool  pending_IRQ_masked_status_get(REGS::INTC::e_INT_ID int_id); 
    
    #if !defined(am335x)
        // not for am335x SoCs      
        bool  pending_FIQ_masked_status_get(REGS::INTC::e_INT_ID int_id);  
    #endif

private:
    REGS::INTC::AM335x_INTC_Type &m_INTC_regs;
    
    isr_handler_t m_interrupt_vectors[REGS::INTC::INT_NUM_MAX];
};

extern am335x_intc intc;

#endif //_AM335X_INTC_H_
