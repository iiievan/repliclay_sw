#include "INTC.h"
#include  <cpu_core.h>
#include  <os.h>
#include "cpu.h"
//#include "uC_cpu.h"

Interrupt_controller intc;
INTC::Handler_ptr_t interrupt_vector_table[INTC::INTERRUPTS_NUM_MAX];

static  void  OS_exept_handler (uint8_t  except_type)
{
    switch (except_type) 
    {
        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
             while (true); 
    }
}

/**
 * The Default Interrupt Handler.
 *
 * This is the default interrupt handler for all interrupts. It simply returns
 * without performing any operation.
 **/
static void interrupt_default_handler(void)
{
    /* Go Back. Nothing to be done */
    return;
}

/**
 * \brief   This API is used to initialize the interrupt controller. This API  
 *          shall be called before using the interrupt controller. 
 *
 * \param   None
 * 
 * \return  None.
 *
 **/
void  Interrupt_controller::init (void)
{ 
    /* Reset the ARM interrupt controller */
    //HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG) = INTC_SYSCONFIG_SOFTRESET;
    m_sINTC.SYSCONFIG.b.SoftReset = HIGH;
 
    /* Wait for the reset to complete */
    //while((HWREG(SOC_AINTC_REGS + INTC_SYSSTATUS)& INTC_SYSSTATUS_RESETDONE) != INTC_SYSSTATUS_RESETDONE);    
    while(m_sINTC.SYSSTATUS.b.ResetDone != HIGH);
    
    /* Enable any interrupt generation by setting priority threshold */ 
    //HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = INTC_THRESHOLD_PRIORITYTHRESHOLD;
    m_sINTC.THRESHOLD.b.PriorityThreshold = INTC::PRIORITY_THRESHOLD;
    
    /* Disable all pending interrupts                       */
    //REG_INTCPS_ISR_CLEAR(0) = DEF_BIT_FIELD(32u, 0u);
    //REG_INTCPS_ISR_CLEAR(1) = DEF_BIT_FIELD(32u, 0u);
    //REG_INTCPS_ISR_CLEAR(2) = DEF_BIT_FIELD(32u, 0u);
    //REG_INTCPS_ISR_CLEAR(3) = DEF_BIT_FIELD(32u, 0u);
    m_sINTC.ISR_CLEAR0.reg = 0xFF;
    m_sINTC.ISR_CLEAR1.reg = 0xFF;
    m_sINTC.ISR_CLEAR2.reg = 0xFF;
    m_sINTC.ISR_CLEAR3.reg = 0xFF;

    for (uint32_t int_id = 0; int_id < INTC::INTERRUPTS_NUM_MAX; int_id++) 
    {
        register_handler((INTC::e_SYS_INTERRUPT)int_id,(INTC::Handler_ptr_t)interrupt_default_handler);
    }
    
    //REG_INTCPS_CONTROL = (INTC_CONTROL_NEWFIQAGR | INTC_CONTROL_NEWIRQAGR);
    m_sINTC.CONTROL.b.NewIRQAgr = HIGH; //Reset IRQ output and enable new IRQ generation
    m_sINTC.CONTROL.b.NewFIQAgr = HIGH; //Reset FIQ output and enable new FIQ generation
    
    return;
}

void  Interrupt_controller::OS_CPU_except_handler(uint32_t  src_id)
{
    switch (src_id) 
    {
        case OS_CPU_ARM_EXCEPT_IRQ:
        case OS_CPU_ARM_EXCEPT_FIQ:
             BSP_int_handler((uint32_t)src_id);
             break;

        case OS_CPU_ARM_EXCEPT_RESET:
        case OS_CPU_ARM_EXCEPT_UNDEF_INSTR:
        case OS_CPU_ARM_EXCEPT_SWI:
        case OS_CPU_ARM_EXCEPT_DATA_ABORT:
        case OS_CPU_ARM_EXCEPT_PREFETCH_ABORT:
        case OS_CPU_ARM_EXCEPT_ADDR_ABORT:
        default:
             OS_exept_handler((uint8_t)src_id);
             break;
    }
}
 
void  Interrupt_controller::BSP_int_handler(uint32_t  src_nbr)
{
  INTC::e_SYS_INTERRUPT  int_nbr;
    INTC::Handler_ptr_t  isr;

    switch (src_nbr) 
    {
        case OS_CPU_ARM_EXCEPT_IRQ:
             //int_nbr = REG_INTCPS_SIR_IRQ;
             int_nbr = (INTC::e_SYS_INTERRUPT)m_sINTC.SIR_IRQ.b.ActiveIRQ;

             isr = interrupt_vector_table[int_nbr];
             if (isr != nullptr) 
             {
                 isr((void *)int_nbr);
             }
             
			 BSP_int_clr(int_nbr);                               /* Clear interrupt									   	*/

			 //REG_INTCPS_CONTROL = INTC_CONTROL_NEWIRQAGR;
             m_sINTC.CONTROL.b.NewIRQAgr = HIGH; //Reset IRQ output and enable new IRQ generation
             break;

        case OS_CPU_ARM_EXCEPT_FIQ:
             //int_nbr = REG_INTCPS_SIR_FIQ;
             int_nbr =  (INTC::e_SYS_INTERRUPT)m_sINTC.SIR_FIQ.b.ActiveFIQ;

             isr = interrupt_vector_table[int_nbr];
             if (isr != nullptr) 
             {
                 isr((void *)int_nbr);
             }
             
			 BSP_int_clr(int_nbr);                       		/* Clear interrupt									   	*/

			 //REG_INTCPS_CONTROL = INTC_CONTROL_NEWFIQAGR;
             m_sINTC.CONTROL.b.NewFIQAgr = HIGH; //Reset FIQ output and enable new FIQ generation
             break;

        default:
             break;
    }
}

void  Interrupt_controller::BSP_int_clr (INTC::e_SYS_INTERRUPT  int_id)
{    
    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;

    INTC::ISR_CLEAR_reg_t *&s_isr_clear = INTC::get_ISR_CLEAR_reference(int_id);   
        
    //REG_INTCPS_ISR_CLEAR(reg_nbr) = BIT(int_id % 32);
    s_isr_clear->b.IsrClear = BIT(int_id % 32);
}

/**
 * \brief    Registers an interrupt Handler in the interrupt vector table for
 *           system interrupts. 
 * 
 * \param    int_id - Interrupt Number
 * \param    pfn_handler - Function pointer to the ISR
 * 
 * Note: When the interrupt occurs for the sytem interrupt number indicated,
 * the control goes to the ISR given as the parameter.
 * 
 * \return      None.
 **/
void  Interrupt_controller::register_handler(INTC::e_SYS_INTERRUPT  int_id, INTC::Handler_ptr_t isr_fnct)
{
    CPU_SR_ALLOC();

    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;


    if (int_id < INTC::INTERRUPTS_NUM_MAX) 
    {
        CPU_CRITICAL_ENTER();
        interrupt_vector_table[int_id] = isr_fnct;
        CPU_CRITICAL_EXIT();
    }
}

/**
 * \brief   Unregisters an interrupt
 * 
 * \param   int_id - Interrupt Number
 * 
 * Note: Once an interrupt is unregistered it will enter infinite loop once
 * an interrupt occurs
 * 
 * \return      None.
 **/
void  Interrupt_controller::unregister_handler(INTC::e_SYS_INTERRUPT int_id)
{
    CPU_SR_ALLOC();

    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;

    if (int_id < INTC::INTERRUPTS_NUM_MAX) 
    {
        CPU_CRITICAL_ENTER();
        /* Assign default ISR */
        interrupt_vector_table[int_id] = (INTC::Handler_ptr_t)interrupt_default_handler; 
        CPU_CRITICAL_EXIT();
    }
}

/**
 * \brief   Sets the interface clock to be free running
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void  Interrupt_controller::if_clk_free_run_set(void)
{
    //HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG)&= ~INTC_SYSCONFIG_AUTOIDLE;
    m_sINTC.SYSCONFIG.b.Autoidle = LOW; //Internal OCP clock gating strategy - clkfree.
}

/**
 * \brief   When this API is called,  automatic clock gating strategy is applied
 *          based on the interface bus activity. 
 *
 * \param   None.
 *
 * \return  None.
 *
 **/
void  Interrupt_controller::if_clk_auto_gate_set(void)
{
    //HWREG(SOC_AINTC_REGS + INTC_SYSCONFIG)|= INTC_SYSCONFIG_AUTOIDLE; 
    m_sINTC.SYSCONFIG.b.Autoidle = HIGH; //Internal OCP clock gating strategy - autoClkGate.
}

/**
 * \brief   Enables protection mode for the interrupt controller register access.
 *          When the protection is enabled, the registers will be accessible only
 *          in privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::protection_enable(void)
{
   // HWREG(SOC_AINTC_REGS + INTC_PROTECTION) = INTC_PROTECTION_PROTECTION;
   m_sINTC.PROTECTION.b.Protection = HIGH;
}

/**
 * \brief   Disables protection mode for the interrupt controller register access.
 *          When the protection is disabled, the registers will be accessible 
 *          in both unprivileged and privileged mode of the CPU.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::protection_disable(void)
{
    // HWREG(SOC_AINTC_REGS + INTC_PROTECTION) &= ~INTC_PROTECTION_PROTECTION;
    m_sINTC.PROTECTION.b.Protection = LOW;
}


/**
 * \brief   Enables the free running of input synchronizer clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::sync_clk_free_run_set(void)
{
    // HWREG(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_TURBO;
    m_sINTC.IDLE.b.Turbo = LOW;
}

/**
 * \brief   When this API is called, Input synchronizer clock is auto-gated 
 *          based on interrupt input activity
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::sync_clk_auto_gate_set(void)
{
    // HWREG(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_TURBO;
    m_sINTC.IDLE.b.Turbo = HIGH;
}

/**
 * \brief   Enables the free running of functional clock
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::func_clk_free_run_set(void)
{
    // HWREG(SOC_AINTC_REGS + INTC_IDLE) |= INTC_IDLE_FUNCIDLE;
    m_sINTC.IDLE.b.FuncIdle = HIGH;
}


/**
 * \brief   When this API is called, functional clock gating strategy
 *          is applied.
 *
 * \param   None
 *
 * \return  None
 *
 **/
void  Interrupt_controller::func_clk_auto_gate_set(void)
{
    // HWREG(SOC_AINTC_REGS + INTC_IDLE) &= ~INTC_IDLE_FUNCIDLE;
    m_sINTC.IDLE.b.FuncIdle = LOW;
}

/**
 * \brief   Sets the given priority threshold value. 
 *
 * \param   threshold - Priority threshold value
 *
 *      'threshold' can take any value from 0x00 to 0x7F. To disable
 *      priority threshold, write 0xFF.
 *             
 * \return  None.
 *
 **/
void  Interrupt_controller::priority_threshold_set(uint8_t threshold)
{
    // HWREG(SOC_AINTC_REGS + INTC_THRESHOLD) = threshold & INTC_THRESHOLD_PRIORITYTHRESHOLD;
    m_sINTC.THRESHOLD.b.PriorityThreshold = threshold;
}

/**
 * \brief   Sets software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be generated
 *
 * \return  None
 *
 **/
void  Interrupt_controller::software_int_set(INTC::e_SYS_INTERRUPT int_id)
{    
    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;
    
    /* Enable the software interrupt in the corresponding ISR_SET register */
    //HWREG(SOC_AINTC_REGS + INTC_ISR_SET(intrNum >> REG_IDX_SHIFT)) = (0x01 << (intrNum & REG_BIT_MASK));

    INTC::ISR_SET_reg_t *&s_isr_set = INTC::get_ISR_SET_reference(int_id);           
    s_isr_set->b.IsrSet = BIT(int_id % 32);
}

/**
 * \brief   Clears the software interrupt for the given interrupt number.
 *
 * \param   intrNum - the system interrupt number, for which software interrupt
 *                    to be cleared.
 *
 * \return  None
 *
 **/
void  Interrupt_controller::software_int_clear(INTC::e_SYS_INTERRUPT int_id)
{
    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;
    
    /* Disable the software interrupt in the corresponding ISR_CLEAR register */
    //HWREG(SOC_AINTC_REGS + INTC_ISR_CLEAR(intrNum >> REG_IDX_SHIFT)) = (0x01 << (intrNum & REG_BIT_MASK));   
   
    INTC::ISR_CLEAR_reg_t *&s_isr_clear = INTC::get_ISR_CLEAR_reference(int_id);   
        
    //REG_INTCPS_ISR_CLEAR(reg_nbr) = BIT(int_id % 32);
    s_isr_clear->b.IsrClear = BIT(int_id % 32);
}

/**
 * \brief  Enables the processor IRQ only in CPSR. Makes the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void  Interrupt_controller::master_IRQ_enable(void)
{
    /* Enable IRQ in CPSR.*/
    CPUirqe();
}


/**
 * \brief  Disables the processor IRQ only in CPSR.Prevents the processor to 
 *         respond to IRQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void  Interrupt_controller::master_IRQ_disable(void)
{
    /* Disable IRQ in CPSR.*/
    CPUirqd();
}

/**
 * \brief  Enables the processor FIQ only in CPSR. Makes the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void  Interrupt_controller::master_FIQ_enable(void)
{
    /* Enable FIQ in CPSR.*/
    CPUfiqe();
}

/**
 * \brief  Disables the processor FIQ only in CPSR.Prevents the processor to 
 *         respond to FIQs.  This does not affect the set of interrupts 
 *         enabled/disabled in the AINTC.
 *
 * \param    None
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void  Interrupt_controller::master_FIQ_disable(void)
{
    /* Disable FIQ in CPSR.*/
    CPUfiqd();
}

/**
 * \brief   This API enables the system interrupt in AINTC. However, for 
 *          the interrupt generation, make sure that the interrupt is 
 *          enabled at the peripheral level also. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void  Interrupt_controller::system_enable(INTC::e_SYS_INTERRUPT int_id)
{
    volatile uint32_t mir_clear = BIT(int_id % 32);
    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;
    
    __asm(" dsb");
    /* Disable the system interrupt in the corresponding MIR_CLEAR register */
    //HWREG(SOC_AINTC_REGS + INTC_MIR_CLEAR(intrNum >> REG_IDX_SHIFT)) = (0x01 << (intrNum & REG_BIT_MASK));

    INTC::MIR_CLEAR_reg_t *&s_mir_clear = INTC::get_MIR_CLEAR_reference(int_id);          
    //s_mir_clear->b.MirClear = BIT(int_id % 32);
    s_mir_clear->b.MirClear = mir_clear;
}

/**
 * \brief   This API disables the system interrupt in AINTC. 
 *
 * \param   intrNum  - Interrupt number
 *
 * \return  None.
 *
 **/
void  Interrupt_controller::system_disable(INTC::e_SYS_INTERRUPT int_id)
{
    if (int_id > INTC::INTERRUPTS_NUM_MAX) 
        return;
    
    __asm(" dsb");
    /* Enable the system interrupt in the corresponding MIR_SET register */
   // HWREG(SOC_AINTC_REGS + INTC_MIR_SET(intrNum >> REG_IDX_SHIFT)) = (0x01 << (intrNum & REG_BIT_MASK));

    INTC::MIR_SET_reg_t *&s_mir_set = INTC::get_MIR_SET_reference(int_id);          
    s_mir_set->b.MirSet = BIT(int_id % 32);   
}


/**
 * \brief  Restore the processor IRQ only status. This does not affect 
 *          the set of interrupts enabled/disabled in the AINTC.
 *
 * \param    The status returned by the IntDisable fundtion.
 *
 * \return   None
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
void  Interrupt_controller::enable(uint8_t  status)
{
    if((status & 0x80) == 0) 
        master_IRQ_enable();
}

/**
 * \brief  Read and save the stasus and Disables the processor IRQ .
 *         Prevents the processor to respond to IRQs.  
 *
 * \param    None
 *
 * \return   Current status of IRQ
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint8_t  Interrupt_controller::disable(void)
{
    uint8_t status;

    /* Reads the current status.*/
    status = (master_status_get() & 0xFF);

    /* Disable the Interrupts.*/
    master_IRQ_disable();

    return status;
}

/**
 * \brief   This API assigns a priority to an interrupt and routes it to
 *          either IRQ or to FIQ. Priority 0 is the highest priority level
 *          Among the host interrupts, FIQ has more priority than IRQ.
 *
 * \param   int_id   - Interrupt number
 * \param   priority - Interrupt priority level
 * \param   host_int_route - The host interrupt IRQ/FIQ to which the interrupt
 *                         is to be routed.
 *     'priority' can take any value from 0 to 127, 0 being the highest and
 *     127 being the lowest priority.              
 *
 *     'host_int_route' can take one of the following values \n
 *             AINTC_HOSTINT_ROUTE_IRQ - To route the interrupt to IRQ \n
 *             AINTC_HOSTINT_ROUTE_FIQ - To route the interrupt to FIQ
 *
 * \return  None.
 *
 **/
void  Interrupt_controller::priority_set(INTC::e_SYS_INTERRUPT int_id, uint32_t priority, uint32_t host_int_route)
{
    //HWREG(SOC_AINTC_REGS + INTC_ILR(intrNum)) = ((priority << INTC_ILR_PRIORITY_SHIFT)& INTC_ILR_PRIORITY) | hostIntRoute ;
    INTC::INTC_ILR_reg_t *&sILR = INTC::get_ILR_reference(int_id);
    sILR->b.Priority = priority;
    sILR->b.FIQnIRQ  = host_int_route;
}

/**
 * \brief   Returns the status of the interrupts FIQ and IRQ.
 *
 * \param    None
 *
 * \return   Status of interrupt as in CPSR.
 *
 *  Note: This function call shall be done only in previleged mode of ARM
 **/
uint32_t  Interrupt_controller::master_status_get(void)
{
    return CPUIntStatus();
}

/**
 * \brief   Reads the active IRQ number.
 *
 * \param   None
 *
 * \return  Active IRQ number.
 *
 **/
uint32_t  Interrupt_controller::active_IRQ_num_get(void)
{
    //return (HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ) &  INTC_SIR_IRQ_ACTIVEIRQ);
    return   m_sINTC.SIR_IRQ.b.ActiveIRQ;
}


uint32_t  Interrupt_controller::active_FIQ_num_get(void)
{
    return   m_sINTC.SIR_FIQ.b.ActiveFIQ;
}

/**
 * \brief   Reads the spurious IRQ Flag. Spurious IRQ flag is reflected in both
 *          SIR_IRQ and IRQ_PRIORITY registers of the interrupt controller.
 *
 * \param   None
 *
 * \return  Spurious IRQ Flag.
 *
 **/
uint32_t  Interrupt_controller::spur_IRQ_flag_get(void)
{
    // return ((HWREG(SOC_AINTC_REGS + INTC_SIR_IRQ)& INTC_SIR_IRQ_SPURIOUSIRQ) >> INTC_SIR_IRQ_SPURIOUSIRQ_SHIFT);
    return   m_sINTC.SIR_IRQ.b.SpuriousIRQ;
}

uint32_t  Interrupt_controller::spur_FIQ_flag_get(void)
{
    return   m_sINTC.SIR_FIQ.b.SpuriousFIQ;
}

/**
 * \brief   Returns the currently active IRQ priority level.
 *
 * \param   None
 *
 * \return  Current IRQ priority 
 *
 **/
uint32_t  Interrupt_controller::curr_IRQ_priorigty_get(void)
{
    //return (HWREG(SOC_AINTC_REGS + INTC_IRQ_PRIORITY) & INTC_IRQ_PRIORITY_IRQPRIORITY);
    return m_sINTC.IRQ_PRIORITY.b.IRQPriority;
}

uint32_t  Interrupt_controller::curr_FIQ_priority_get(void)
{
    return m_sINTC.FIQ_PRIORITY.b.FIQPriority;
}

/**
 * \brief   Returns the priority threshold.
 *
 * \param   None
 *
 * \return  Priority threshold value.
 *
 **/
uint8_t  Interrupt_controller::priority_threshold_get(void)
{
    // return (HWREG(SOC_AINTC_REGS + INTC_THRESHOLD)& INTC_THRESHOLD_PRIORITYTHRESHOLD);
    return m_sINTC.THRESHOLD.b.PriorityThreshold;
}

/**
 * \brief   Returns the raw interrupt status before masking.
 *
 * \param   intrNum - the system interrupt number.
 *
 * \return  TRUE - if the raw status is set \n
 *          FALSE - if the raw status is not set.   
 *
 **/
bool  Interrupt_controller::raw_status_get(INTC::e_SYS_INTERRUPT int_id)
{
    // return ((0 == ((HWREG(SOC_AINTC_REGS + INTC_ITR(intrNum >> REG_IDX_SHIFT)) >> (intrNum & REG_BIT_MASK))& 0x01)) ? FALSE : TRUE);
    INTC::ITR_reg_t *&s_raw_sts = INTC::get_ITR_reference(int_id);
    
    if(s_raw_sts->b.Itr & BIT(int_id))
        return true;
    else
        return false;
}

/**
 * \brief   Returns the IRQ status after masking.
 *
 * \param   intrNum - the system interrupt number
 *
 * \return  TRUE - if interrupt is pending \n
 *          FALSE - in no interrupt is pending
 *
 **/
bool  Interrupt_controller::pending_IRQ_masked_status_get(INTC::e_SYS_INTERRUPT int_id)
{
    // return ((0 ==(HWREG(SOC_AINTC_REGS + INTC_PENDING_IRQ(intrNum >> REG_IDX_SHIFT)) >> (((intrNum & REG_BIT_MASK)) & 0x01))) ? FALSE : TRUE); 
    INTC::PENDING_IRQ_reg_t *&s_pending = INTC::get_pending_IRQ_reference(int_id);
    
    if(s_pending->b.PendingIRQ & BIT(int_id))
        return true;
    else
        return false;
}

bool  Interrupt_controller::pending_FIQ_masked_status_get(INTC::e_SYS_INTERRUPT int_id)
{
    INTC::PENDING_FIQ_reg_t *&s_pending = INTC::get_pending_FIQ_reference(int_id);
    
    if(s_pending->b.PendingFIQ & BIT(int_id))
        return true;
    else
        return false;
} 
