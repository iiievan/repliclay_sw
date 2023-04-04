#ifndef __UART_DT_DRIVER_H_
#define __UART_DT_DRIVER_H_

#include "uart_irda_cir.h"
#include "Device_driver.h"
#include "PRCM.h"
#include "INTC.h"
#include "CONTROL_MODULE.h"
#include "n_UART.h"
#include "n_EDMA.h"

#define RX_CHUNK_SIZE          (64UL)
#define TX_CHUNK_SIZE          (64UL)
constexpr uint32_t  TX_BYTES_PER_EVENT = 8u;
constexpr uint32_t  RX_TRIG_LEVEL = 8u;

struct UART_client_ops : public Client_ops
{
    std::string  compatible;
    AM335x_UART *p_UART_instance { nullptr };
            int  (*pollrx)(void *p_Obj);
            
    UART_client_ops() 
    :compatible("AM335x_UART")
    { }
    
    void operator=(Client_ops &right)
    {
        write = right.write;
        read = right.read;
    }
    
    void operator=(UART_client_ops &right)
    {
        write = right.write;
        read = right.read;
        p_UART_instance = right.p_UART_instance;
        pollrx = right.pollrx;
    }
};

extern      UART_client_ops  UART_ops;
extern const DT_device_id_t  AM335x_UART_ids;
static void  RXTX_end_callback(uint32_t tcc_num);
static  int  UART_DMA_write(void *p_Obj, const char *buffer, size_t len);

class UART_DT_Driver : public Device_driver
{        
    friend void  RXTX_end_callback(uint32_t tcc_num);
    friend  int  UART_DMA_write(void *p_Obj, const char *buffer, size_t len);
    
    public:
            UART_DT_Driver(AM335x_UART &uart_instance)
            : Device_driver("AM335x_serial_driver", &AM335x_UART_ids),
              m_UART_device(uart_instance),
              m_prcm_module(prcm_module),
              m_int_controller(intc),
              m_pinmux_ctrl(ctrl_module),
              m_EDMA(eDMA)
             { 
                 m_UART_instance_num  = m_UART_device.get_UART_inst_number();
                 m_UART_sys_interrupt = m_UART_device.get_UART_sys_interrupt();
             }

            ~UART_DT_Driver() { }
    
        int  probe(void *p_owner);
        int  init(void);
       void  sync_state(void* p_dev);
        int  remove(void* p_dev);
       void  shutdown(void* p_dev);
        int  suspend(void* p_dev);
        int  resume(void* p_dev);
        int  exit(void);
       
AM335x_UART* get_instance(void) { return &m_UART_device; }

       void  AINTC_configure(void);
       void  EDMA_INTC_configure(void);
       void  sys_interrupt_enable()  { m_int_controller.system_enable(m_UART_sys_interrupt);  }
       void  sys_interrupt_disable() { m_int_controller.system_disable(m_UART_sys_interrupt); }
       
          bool  m_TX_busy { false };

private:
                         void  set_Client_ops(void *p_owner, Client_ops *p_ops);

          INTC::isr_handler_t  m_isr_handler;
  n_UART::e_UART_INSTANCE_NUM  m_UART_instance_num;     // UART instance index number
        INTC::e_SYS_INTERRUPT  m_UART_sys_interrupt;
        
                         

                  AM335x_UART &m_UART_device;           // UART instance reference.
    power_reset_clock_control &m_prcm_module;           // for clock contrlol setup and management
         Interrupt_controller &m_int_controller;        // for interrupt setup and management
             x_CONTROL_MODULE &m_pinmux_ctrl;           // for PINMUX
                  AM335x_EDMA &m_EDMA;                  // for EDMA transfer
};

void  UART_TX_eDMA_paRAM_set(uint8_t *tx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num);
void  UART_RX_eDMA_paRAM_set(uint8_t *rx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num);
void  Tx_dummy_paRAM_config_enable(void);

extern UART_DT_Driver uart_driver;

#endif  //__UART_DT_DRIVER_H_