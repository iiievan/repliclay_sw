#ifndef _NRF_SERIAL_H
#define _NRF_SERIAL_H

#include "include.h"
#include "frame_buffer.h"
#include "Paired_buffer.h"
#include "swTimer.h"

#define RX_CHUNK_SIZE          (64UL)
#define TX_CHUNK_SIZE          (64UL)

#ifndef PIN_DISCONNECTED
#define PIN_DISCONNECTED       (0xFFFFFFFFUL)    // Define that pin is disconnected from hardware
#endif

#define UART0_INT_PRIORITY     (3)

enum e_uart_RX_fsm_sts : uint32_t
{
    RX_IDLE             = 0x0,  // nothing to happen, ready to operation
    RX_IN_PROGESS       = 0x1,  // RX transaction started and in progress 
    RX_CHUNK_RECEIVED   = 0x2,  // half of RX paired buffer is full
    RX_TOUT_IS_OUT      = 0x3,  // timeout after the last received byte has expired, the reception is over
    RX_STOPPED          = 0x4   // receiver stopped 
};

class swTimer;
extern void RX_end_callback(void * p_Obj);
extern swTimer RX_end_timer;

class x_NRF_serial 
{                   
           friend void  RX_end_callback(void * p_Obj);
    
public:
                        x_NRF_serial(NRF_UARTE_Type *sUART);
                  void  init(uint32_t rx_pin, uint32_t tx_pin, uint32_t baudrate);
                  void  deinit(void);

                  void  write(char c); 
                  void  write(const char *data, size_t len);
                  void  write(const char *str);    
              uint32_t  available(void);
                  void  read(char* data);
                  void  read(ring_buffer<RX_CHUNK_SIZE*4>* p_Data);
                  bool  is_RX_data_rdy(ring_buffer<RX_CHUNK_SIZE*4>* p_Data); 
                  
                  void  rx_irq(void);                  // need to be placed in UARTE0_UART0_IRQHandler if RX used
                  void  tx_irq(void);                  // need to be placed in UARTE0_UART0_IRQHandler if TX used
                  
              swTimer&  s_RX_end_timer;

private:
                    NRF_UARTE_Type &m_sUART;

Paired_buffer<char, RX_CHUNK_SIZE>  m_RX_data;        // cumulative received data buffer
Paired_buffer<char, TX_CHUNK_SIZE>  m_TX_data;        // storage data buffer for sending

                  void  m_Start_TX(size_t amount);
                  void  m_Start_RX(size_t amount);
                  bool  m_TX_busy;
     e_uart_RX_fsm_sts  m_RX_sts;                   

              uint32_t  m_TX_pin;   // TX pin
              uint32_t  m_RX_pin;   // RX pin                   
};

extern x_NRF_serial dbg_serial;
#endif