#ifndef __UART_DT_DRIVER_H_
#define __UART_DT_DRIVER_H_

#include "Device_driver.h"
#include "PRCM.h"
#include "INTC.h"
#include "CONTROL_MODULE.h"
#include "n_UART.h"

static char UART_read(void *p_Obj);
static int UART_write(void *p_Obj, const char *buffer, size_t len);

// @brief  UART device opertaion functions callbacks
// @detail
static Dev_ops_t UART_ops = 
{
    .write = UART_write,
    .read = UART_read,
    .isr_handler = nullptr
};

// @brief  device tree property
// @details
static const DT_device_id_t  AM335x_UART_ids =
{
    .compatible = "AM335x_UART"
};

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

extern UART_DT_Driver uart_console;

#endif  //__UART_DT_DRIVER_H_