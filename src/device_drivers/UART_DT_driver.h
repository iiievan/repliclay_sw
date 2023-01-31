#ifndef __UART_DT_DRIVER_H_
#define __UART_DT_DRIVER_H_

#include "Device_driver.h"
#include "PRCM.h"
#include "INTC.h"
#include "CONTROL_MODULE.h"
#include "n_UART.h"

static struct UART_device_ops UART_ops = 
{
    .receive_buf = UART_receive,
}

// @brief This Callback is called when charater is receive
static int UART_receive(UART_Driver *p_Drv, const uint8_t *buffer, size_t size)
{
    print.f("Received %ld bytes with \"%s\"\n", size, buffer);

    return device_write_buf(pdev, buffer, size);
}

static DT_device_id_t  UART_DT_driver_ids =
{
    .compatible = "AM335x_UART"
};

class UART_Driver : public Device_driver
{
    public:
            UART_Driver()
            : Device_driver("UART_driver", &UART_DT_driver_ids),
              m_UART_device(uart_0),
              m_prcm_module(prcm_module),
              m_int_controller(intc),
              m_pinmux_ctrl(ctrl_module)
             { }

           ~UART_Driver() { }
    
       int  probe(void* dev);
       int  init(void);
      void  sync_state(void* dev);
       int  remove(void* dev);
      void  shutdown(void* dev);
       int  suspend(void* dev);
       int  resume(void* dev);
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

#endif  //__UART_DT_DRIVER_H_