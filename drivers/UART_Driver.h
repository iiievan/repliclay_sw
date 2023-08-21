#ifndef __UART_DRIVER_H
#define __UART_DRIVER_H

#include "init.h"
#include "soc_AM335x.h"
#include "edma_event.h"
#include "uartStdio.h"
#include "interrupt.h"
#include "edma.h"
#include "n_EDMA.h"
#include "n_UART.h"
#include "paired_buffer.h"

#define UART_ENABLE_FIFO    // Enable FIFO mode of operation.

#define UART_THR_RHR_REG          (SOC_UART_0_REGS)     // Address of THR and RHR registers of UART.
#define UART_MODULE_INPUT_CLK     (48000000)    // UART Module Input Frequency. 

// Baud Rate of UART for communication.
#define BAUD_RATE_115200          (115200)
#define BAUD_RATE_128000          (128000)
#define BAUD_RATE_230400          (230400)
#define BAUD_RATE_460800          (460800)
#define BAUD_RATE_921600          (921600)

#define EVT_QUEUE_NUM             (0)   // EDMA3 Event queue number.
#define DUMMY_CH_NUM              (5)   // PaRAM Set number for Dummy Transfer.

// Wrapper Definitions. 
#define UART_INSTANCE_BASE_ADD    (SOC_UART_0_REGS)
#define EDMA3_UART_TX_CHA_NUM     (EDMA3_CHA_UART0_TX)
#define EDMA3_UART_RX_CHA_NUM     (EDMA3_CHA_UART0_RX)
#define UART_INT_NUM              (SYS_INT_UART0INT)

// Use this macro if TX_DMA_THRESHOLD register is used to configure TX
// Threshold value.
#define DIRECT_TX_DMA_THRESH_MODE

// Transmit DMA Threshold Value. This is set in TX_DMA_THRESHOLD register.
#define TX_DMA_THRESHOLD          (5)

//Transmit Trigger Space value. Use this if TX Trigger Level granularity
//is selected to be 1.
#define TX_TRIGGER_SPACE_GRAN_1   (8)

// Number of bytes transmitted by EDMA per TX event sent by UART.
#ifdef UART_ENABLE_FIFO
    #define TX_BYTES_PER_EVENT    (8)
#else
    #define TX_BYTES_PER_EVENT    (1)
#endif

#define RX_BUFFER_SIZE            (64)      // Receiver Buffer Size.

// Receive DMA Threshold Value.
#ifdef UART_ENABLE_FIFO
    #define RX_DMA_THRESHOLD      (8)
#else
    #define RX_DMA_THRESHOLD      (1)
#endif

#define NUM_RX_BYTES              (8)   // Number of bytes to be received from the user.

#define RX_CHUNK_SIZE          (64UL)
#define TX_CHUNK_SIZE          (8UL)

// ISR and other callbacks
extern void  EDMA_Completion_Isr(void);
extern void  RXTX_end_clbck(unsigned int tccNum);
extern void  EDMA_CC_error_isr(void);

class UART_Driver
{
    friend void  EDMA_Completion_Isr(void);
    friend void  RXTX_end_clbck(unsigned int tccNum);

public:
         UART_Driver();
        ~UART_Driver();

   void  setup();
   void  FIFO_configure(void);
   void  Baud_set(void);

   void  TX_EDMA_paRAM_set_config(unsigned char *tx_buffer,
                                   unsigned int  len,
                                   unsigned int  tcc_num,
                                 unsigned short  linkaddr,
                                   unsigned int  ch_num);

   void RX_EDMA_paRAM_set_config( unsigned int  len,
                                  unsigned int  tcc_num,
                                unsigned short  linkaddr,
                                  unsigned int  ch_num);
   void TX_dummy_paRAM_conf_enable(void);

   void send(unsigned char * s, size_t len);
   void write(const uint8_t *string, size_t len);
   void recieve( size_t len);
   void flush();      // flush rx buffer to tx

private:
          bool  m_TX_busy {false};

          void  (*m_cb_Fxn[EDMA3_NUM_TCC]) (unsigned int tcc);

 unsigned char  m_rxBuffer[RX_BUFFER_SIZE];
 paired_buffer<uint8_t, TX_CHUNK_SIZE>  m_TX_data;        // storage data buffer for sending
  unsigned int  m_tx_trig_space;
  unsigned int  m_tx_bytes_per_event;
  unsigned int  m_rx_trig_level;
  unsigned int  m_tx_thresh_level;
};

extern UART_Driver UART_0;

#endif //__UART_DRIVER_H