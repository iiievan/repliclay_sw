#include "Device_driver.h"

void Device_driver::set_Client_ops(void *p_owner, Dev_ops *p_ops)
{
    m_Owner = p_owner;
    
    if(m_Of_match_table->compatible.compare("AM335x_UART"))
    {
        UART_dev_ops *p_client = static_cast<UART_dev_ops *>(m_Owner);

        *p_client = static_cast<UART_dev_ops *>(p_ops);
    }
}