#ifndef __UART_DT_DRIVER_H_
#define __UART_DT_DRIVER_H_

#include "uart_irda_cir.h"
#include "Device_driver.h"
#include "PRCM.h"
#include "INTC.h"
#include "CONTROL_MODULE.h"
#include "n_UART.h"

extern            Dev_ops_t  UART_ops;
extern const DT_device_id_t  AM335x_UART_ids;

class UART_DT_Driver : public Device_driver
{
    public:
            UART_DT_Driver(AM335x_UART &uart_instance)
            : Device_driver("AM335x_serial_driver", &AM335x_UART_ids),
              m_UART_device(uart_instance),
              m_prcm_module(prcm_module),
              m_int_controller(intc),
              m_pinmux_ctrl(ctrl_module)
             { }

           ~UART_DT_Driver() { }
    
       int  probe(void);
       int  init(void);
      void  sync_state(void* p_dev);
       int  remove(void* p_dev);
      void  shutdown(void* p_dev);
       int  suspend(void* p_dev);
       int  resume(void* p_dev);
       int  exit(void);

    private:

          INTC::isr_handler_t  m_isr_handler;
  n_UART::e_UART_INSTANCE_NUM  m_UART_instance_num;     // UART instance index number
        INTC::e_SYS_INTERRUPT  m_UART_sys_interrupt;

                  AM335x_UART &m_UART_device;      // UART instance pointer.
    power_reset_clock_control &m_prcm_module;      // for clock contrlol setup and management
         Interrupt_controller &m_int_controller;   // for interrupt setup and management
             x_CONTROL_MODULE &m_pinmux_ctrl;      // for PINMUX
};

extern UART_DT_Driver uart_console;

#endif  //__UART_DT_DRIVER_H_