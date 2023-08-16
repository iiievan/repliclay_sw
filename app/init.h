#ifndef __INIT_H
#define __INIT_H

#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "edma_event.h"
#include "beaglebone.h"
#include "interrupt.h"
#include "edma.h"

/****************************************************************************/
/*                      INTERNAL MACROS                                     */
/****************************************************************************/
/* Address of THR and RHR registers of UART. */
#define UART_THR_RHR_REG          (SOC_UART_0_REGS)

/* UART Module Input Frequency. */
#define UART_MODULE_INPUT_CLK     (48000000)

/* Baud Rate of UART for communication. */
#define BAUD_RATE_115200          (115200)
#define BAUD_RATE_128000          (128000)
#define BAUD_RATE_230400          (230400)
#define BAUD_RATE_460800          (460800)
#define BAUD_RATE_921600          (921600)

/* EDMA3 Event queue number. */
#define EVT_QUEUE_NUM             (0)

/* PaRAM Set number for Dummy Transfer. */
#define DUMMY_CH_NUM              (5)

/* Wrapper Definitions. */
#define UART_INSTANCE_BASE_ADD    (SOC_UART_0_REGS)
#define EDMA3_UART_TX_CHA_NUM     (EDMA3_CHA_UART0_TX)
#define EDMA3_UART_RX_CHA_NUM     (EDMA3_CHA_UART0_RX)
#define UART_INT_NUM              (SYS_INT_UART0INT)

/* Enable FIFO mode of operation. */
#define UART_ENABLE_FIFO

/******************* Transmit related definitions  **************************/

/*
** Use this macro if TX_DMA_THRESHOLD register is used to configure TX
** Threshold value.
*/
#define DIRECT_TX_DMA_THRESH_MODE

/*
** Transmit DMA Threshold Value. This is set in TX_DMA_THRESHOLD register.
*/
#define TX_DMA_THRESHOLD          (5)

/*
** Transmit Trigger Space value. Use this if TX Trigger Level granularity
** is selected to be 1.
*/
#define TX_TRIGGER_SPACE_GRAN_1   (8)

/* Number of bytes transmitted by EDMA per TX event sent by UART. */
#ifdef UART_ENABLE_FIFO
#define TX_BYTES_PER_EVENT        (8)
#else
#define TX_BYTES_PER_EVENT        (1)
#endif

/******************* Receive related definitions  ***************************/

/* Receiver Buffer Size. */
#define RX_BUFFER_SIZE            (50)

/* Receive DMA Threshold Value. */
#ifdef UART_ENABLE_FIFO
#define RX_DMA_THRESHOLD          (8)
#else
#define RX_DMA_THRESHOLD          (1)
#endif

/* Number of bytes to be received from the user. */
#define NUM_RX_BYTES              (8)

void init_board(void);

#endif

