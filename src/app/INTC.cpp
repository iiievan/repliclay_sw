#include "INTC.h"

static void interrupt_default_handler(void);
static void interrupt_default_handler(void)
{
    return;
}

void  Interrupt_controller::init (void)
{
    return;
}

void  Interrupt_controller::OS_CPU_except_handler(int32_t  src_id)
{
    return;
}
 
void  Interrupt_controller::BSP_int_handler(int32_t  src_nbr)
{
    return;
}

void  Interrupt_controller::BSP_int_clr (int8_t  int_id)
{
    return;
}

void  Interrupt_controller::BSP_int_vect_reg (int8_t  int_id, CPU_FNCT_PTR    isr_fnct)
{
    return;
}

void  Interrupt_controller::if_clk_free_run_set(void)
{
    return;
}

void  Interrupt_controller::if_clk_auto_gate_set(void)
{
    return;
}

void  Interrupt_controller::protection_enable(void)
{
    return;
}

void  Interrupt_controller::protection_disable(void)
{
    return;
}

void  Interrupt_controller::sync_clk_free_run_set(void)
{
    return;
}

void  Interrupt_controller::sync_clk_auto_gate_set(void)
{
    return;
}

void  Interrupt_controller::func_clk_free_run_set(void)
{
    return;
}

void  Interrupt_controller::func_clk_auto_gate_set(void)
{
    return;
}

void  Interrupt_controller::priority_threshold_set(uint32_t threshold)
{
    return;
}

void  Interrupt_controller::software_int_set(uint32_t intr_num)
{
    return;
}

void  Interrupt_controller::software_int_clear(uint32_t intr_num)
{
    return;
}

void  Interrupt_controller::master_IRQ_enable(void)
{
    return;
}

void  Interrupt_controller::master_IRQ_disable(void)
{
    return;
}

void  Interrupt_controller::master_FIQ_enable(void)
{
    return;
}

void  Interrupt_controller::master_FIQ_disable(void)
{
    return;
}

void  Interrupt_controller::system_enable(uint32_t intr_num)
{
    return;
}

void  Interrupt_controller::system_disable(uint32_t intr_num)
{
    return;
}

void  Interrupt_controller::unregister_handler(uint32_t intr_num)
{
    return;
}

void  Interrupt_controller::enable(uint8_t  status)
{
    return;
}

void  Interrupt_controller::register_handler(uint32_t intr_num, void (*pfn_handler)(void))
{
    return;
}

void  Interrupt_controller::priority_set(uint32_t intr_num, uint32_t priority, uint32_t host_int_route)
{
    return;
}

uint8_t  Interrupt_controller::disable(void)
{
    return;
}

uint32_t  Interrupt_controller::master_status_get(void)
{
    return;
}

uint32_t  Interrupt_controller::active_IRQ_num_get(void)
{
    return;
}

uint32_t  Interrupt_controller::active_FIQ_num_get(void)
{
    return;
}

uint32_t  Interrupt_controller::spur_IRQ_flag_get(void)
{
    return;
}

uint32_t  Interrupt_controller::spur_FIQ_flag_get(void)
{
    return;
}

uint32_t  Interrupt_controller::curr_IRQ_priorigty_get(void)
{
    return;
}

uint32_t  Interrupt_controller::curr_FIQ_priority_get(void)
{
    return;
}

uint32_t  Interrupt_controller::priority_threshold_get(void)
{
    return;
}

uint32_t  Interrupt_controller::raw_status_get(unsigned int intr_num)
{
    return;
}

uint32_t  Interrupt_controller::pending_IRQ_masked_status_get(unsigned int intr_num)
{
    return;
}

uint32_t  Interrupt_controller::pending_FIQ_masked_status_get(unsigned int intr_num)
{
    return;
} 
