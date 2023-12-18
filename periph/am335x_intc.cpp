#include "am335x_intc.h"
#include "utils.h"
#include "cpu.h"

am335x_intc intc;

isr_handler_t* interrupt_vectors = nullptr;

static void int_def_hndlr(void *p_obj)
{
    ;
}

void  am335x_intc::init (void)
{ 
    interrupt_vectors = &m_interrupt_vectors[0];
    
    // Reset the ARM interrupt controller 
    m_INTC_regs.SYSCONFIG.b.SoftReset = HIGH;
 
    // Wait for the reset to complete  
    while(m_INTC_regs.SYSSTATUS.b.ResetDone != HIGH);
    
    // Enable any interrupt generation by setting priority threshold 0xFF 
    m_INTC_regs.THRESHOLD.b.PriorityThreshold = REGS::INTC::PRIORITY_THRESHOLD;
    
    // Disable all pending interrupts */
    m_INTC_regs.ISR_CLEAR0.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR1.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR2.reg = 0xFF;
    m_INTC_regs.ISR_CLEAR3.reg = 0xFF;

    for (uint32_t int_id = 0; int_id < REGS::INTC::INT_NUM_MAX; int_id++) 
    {
        register_handler((REGS::INTC::e_INT_ID)int_id,(isr_handler_t)int_def_hndlr);
    }
    
    m_INTC_regs.CONTROL.b.NewIRQAgr = HIGH; //Reset IRQ output and enable new IRQ generation    
    m_INTC_regs.CONTROL.b.NewFIQAgr = HIGH; //Reset FIQ output and enable new FIQ generation
} 

void  am335x_intc::register_handler(REGS::INTC::e_INT_ID  int_id, isr_handler_t isr_fnct)
{
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;

    // assign ISR
    m_interrupt_vectors[int_id] = isr_fnct;
}

void  am335x_intc::unregister_handler(REGS::INTC::e_INT_ID int_id)
{   
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;

    m_interrupt_vectors[int_id] = int_def_hndlr;
}

void  am335x_intc::interface_clk_set(bool mode)
{    
    if(mode)
    {
        //Internal OCP clock gating strategy - autoClkGate.
        m_INTC_regs.SYSCONFIG.b.Autoidle = HIGH; 
    }
    else
    {
        //Internal OCP clock gating strategy - clkfree.
        m_INTC_regs.SYSCONFIG.b.Autoidle = LOW; 
    }
}

void  am335x_intc::protection_enable(bool mode)
{
    if(mode)
        m_INTC_regs.PROTECTION.b.Protection = HIGH;
    else
        m_INTC_regs.PROTECTION.b.Protection = LOW;
}

void  am335x_intc::low_power_turbo(bool mode)
{
    if(mode)
    {
        // clock is auto-gated
        m_INTC_regs.IDLE.b.Turbo = HIGH;
    }
    else
    {
        // is free running (default),
        m_INTC_regs.IDLE.b.Turbo = LOW;
    }
}

void  am335x_intc::low_power_funcidle(bool mode)
{
    if(mode)
    {
        //functional clock gating strategy is applied.
        m_INTC_regs.IDLE.b.FuncIdle = HIGH;
    }
    else
    {
        //functional clock is free running
        m_INTC_regs.IDLE.b.FuncIdle = LOW;
    }
}

void  am335x_intc::priority_threshold_set(uint8_t threshold)
{
    m_INTC_regs.THRESHOLD.b.PriorityThreshold = threshold;
}

void  am335x_intc::software_int_set(REGS::INTC::e_INT_ID int_id)
{    
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;
    
    // Enable the software interrupt in the corresponding ISR_SET register
    REGS::INTC::ISR_SET_reg_t *&s_isr_set = REGS::INTC::get_ISR_SET_reference(int_id);           
    s_isr_set->b.IsrSet |= BIT(int_id % 32);
}

void  am335x_intc::software_int_clear(REGS::INTC::e_INT_ID int_id)
{
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;
    
    // Disable the software interrupt in the corresponding ISR_CLEAR register 
    REGS::INTC::ISR_CLEAR_reg_t *&s_isr_clear = REGS::INTC::get_ISR_CLEAR_reference(int_id);   
    s_isr_clear->b.IsrClear |= BIT(int_id % 32);
}

void  am335x_intc::master_IRQ_enable(void)
{
    // Enable IRQ in CPSR
    CPUirqe();
}

void  am335x_intc::master_IRQ_disable(void)
{
    // Disable IRQ in CPSR
    CPUirqd();
}

void  am335x_intc::master_FIQ_enable(void)
{
    // Enable FIQ in CPSR.
    CPUfiqe();
}

void  am335x_intc::master_FIQ_disable(void)
{
    // Disable FIQ in CPSR
    CPUfiqd();
}

void  am335x_intc::unmask_interrupt(REGS::INTC::e_INT_ID int_id)
{
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;
    
    __asm(" dsb");
    // Disable the system interrupt in the corresponding MIR_CLEAR register
    REGS::INTC::MIR_CLEAR_reg_t *&s_mir_clear = REGS::INTC::get_MIR_CLEAR_reference(int_id);          
    s_mir_clear->b.MirClear = BIT(int_id % 32);
}

void  am335x_intc::mask_interrupt(REGS::INTC::e_INT_ID int_id)
{
    if (int_id > REGS::INTC::INT_NUM_MAX) 
        return;
    
    __asm(" dsb");
    // Enable the system interrupt in the corresponding MIR_SET register
    REGS::INTC::MIR_SET_reg_t *&s_mir_set = REGS::INTC::get_MIR_SET_reference(int_id);          
    s_mir_set->b.MirSet = BIT(int_id % 32);   
}

void  am335x_intc::sys_enable(uint8_t  status)
{
    if((status & 0x80) == 0) 
        master_IRQ_enable();
}

uint8_t  am335x_intc::sys_disable(void)
{
    // Reads the current status.
    uint8_t status = (master_status_get() & 0xFF);

    // Disable the Interrupts.
    master_IRQ_disable();

    return status;
}

#if defined(am335x) 
void  am335x_intc::priority_set(REGS::INTC::e_INT_ID int_id, uint32_t priority)
{
    REGS::INTC::INTC_ILR_reg_t *&sILR = REGS::INTC::get_ILR_reference(int_id);
    sILR->b.Priority = priority;

    // by defualt to IRQ - 0x0 ,for am335x SoCs
    sILR->b.FIQnIRQ  = REGS::INTC::HOSTINT_ROUTE_IRQ;

}
#else
void  am335x_intc::priority_set(REGS::INTC::e_INT_ID int_id, uint32_t priority, uint32_t host_int_route)
{
    REGS::INTC::INTC_ILR_reg_t *&sILR = REGS::INTC::get_ILR_reference(int_id);
    sILR->b.Priority = priority;    

    sILR->b.FIQnIRQ  = host_int_route;
}
#endif

uint32_t  am335x_intc::master_status_get(void)
{
    return CPUIntStatus();
}

uint32_t  am335x_intc::active_IRQ_num_get(void)
{
    return   m_INTC_regs.SIR_IRQ.b.ActiveIRQ;
}

#if !defined(am335x)
uint32_t  am335x_intc::active_FIQ_num_get(void)
{
    return   m_INTC_regs.SIR_FIQ.b.ActiveFIQ;
}
#endif

uint32_t  am335x_intc::spur_IRQ_flag_get(void)
{
             // return sputious(masked) interrupt
    return   m_INTC_regs.SIR_IRQ.b.SpuriousIRQ;
}

#if !defined(am335x)
uint32_t  am335x_intc::spur_FIQ_flag_get(void)
{
    return   m_INTC_regs.SIR_FIQ.b.SpuriousFIQ;
}
#endif

uint32_t  am335x_intc::curr_IRQ_priorigty_get(void)
{
    return m_INTC_regs.IRQ_PRIORITY.b.IRQPriority;
}

#if !defined(am335x)
uint32_t  am335x_intc::curr_FIQ_priority_get(void)
{
    return m_INTC_regs.FIQ_PRIORITY.b.FIQPriority;
}
#endif

uint8_t  am335x_intc::priority_threshold_get(void)
{
    return m_INTC_regs.THRESHOLD.b.PriorityThreshold;
}

bool  am335x_intc::raw_status_get(REGS::INTC::e_INT_ID int_id)
{
    REGS::INTC::ITR_reg_t *&s_raw_sts = REGS::INTC::get_ITR_reference(int_id);
    
    if(s_raw_sts->b.Itr & BIT(int_id % 32))
        return true;
    else
        return false;
}

bool  am335x_intc::pending_IRQ_masked_status_get(REGS::INTC::e_INT_ID int_id)
{
    REGS::INTC::PENDING_IRQ_reg_t *&s_pending = REGS::INTC::get_pending_IRQ_reference(int_id);
    
    if(s_pending->b.PendingIRQ & BIT(int_id % 32))
        return true;
    else
        return false;
}

#if !defined(am335x)
bool  am335x_intc::pending_FIQ_masked_status_get(REGS::INTC::e_INT_ID int_id)
{
    REGS::INTC::PENDING_FIQ_reg_t *&s_pending = REGS::INTC::get_pending_FIQ_reference(int_id);
    
    if(s_pending->b.PendingFIQ & BIT(int_id % 32))
        return true;
    else
        return false;
} 
#endif
