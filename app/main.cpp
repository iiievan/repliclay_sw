
/**
 * \brief  This application demonstrates UART communication with the Host machine
 *      and using EDMA to transfer data beween memory and UART FIFO.
 *      
 *      Application Configuration:
 *
 *          Modules Used:
 *              UART0
 *              EDMA
 *              Interrupt Controller
 *
 *          Configurable Parameters:
 *              None
 *          
 *          Hard-Coded Configuration of other parameters:
 *              UART:
 *              a) FIFO Mode enabled
 *              b) Baud Rate - 115200 bps
 *              c) Word Length - 8 bits
 *              d) Parity - None
 *              e) Stop Bits - 1 stop bit
 *              f) TX DMA Threshold Programming Mode -
 *                  Direct Method (MDR3[2] = 1; TX_DMA_THRESHOLD Register
 *                  holds threshold value)
 *              g) TX DMA Threshold level - 5
 *              h) TX Trigger Space value - 8
 *              i) RX Threshold level - 8
 *
 *      Application Use Cases:
 *          1) Application demonstrates UART Transmit and Receive
 *             operations with EDMA writing data into and reading data out
 *             of the UART TX and RX FIFOs respectively.
 *          2) Demonstrates EDMA Completion Interrupt Handling and Error
 *             Interrupt Handling.
 *          3) Demonstrates EDMA Channel PaRAM Set linking to a Dummy
 *             PaRAM Set.
 *
 *      Running the Example:
 *          On executing the example:
 *          1) Three strings will be tranmitted by the application and will be
 *             displayed on the serial console of the host. These inform the
 *             user about the application and provides directions.
 *          2) The user is expected to key in 8 characters from the keyboard.
 *             The application echoes these characters at once after all the
 *             8 characters have been received.
 *             
 */

#include "init.h"

/****************************************************************************/
/*                      NOTE TO THE USER                                    */
/****************************************************************************/
/*
** 1) The application can be used with or without Transmit and Receive
**    UART FIFOs being enabled. The macro UART_ENABLE_FIFO should be defined
**    if UART FIFOs have to used.
** 2) The number of bytes transferred by EDMA to the TX FIFO per TX event
**    sent by UART should be equal to the TX Trigger Space setting in TLR
**    and/or FCR.
** 3) This application uses Direct TX DMA Threshold Programming method
**    to program the TX DMA Threshold level. Here the TX DMA Threshold level
**    is programmed in TX_DMA_THRESHOLD register of UART.
** 4) If Direct TX DMA Threshold Programming is used, the TX Trigger Space
**    setting should be greater than TX Threshold Level.
*/

/****************************************************************************/
/*                   LOCAL FUNCTION DEFINITIONS                             */
/****************************************************************************/
extern unsigned int clBackFlag;
unsigned char intent[] = "The application echoes the characters that you type on the console.\r\n";
unsigned char welcome[] = "StarterWare AM335X UART DMA application.\r\n";
unsigned char enter[] = "Please Enter 08 bytes from keyboard.\r\n";

unsigned char rxBuffer[RX_BUFFER_SIZE];
/*
** Transmit Trigger Space value. This is applicable only when UART FIFO mode
** is used. Refer to the comments of the API UARTFIFOConfig() to find the
** possible values of TX Trigger Space.
*/
unsigned int txTrigSpace = TX_TRIGGER_SPACE_GRAN_1;

/*
** Number of bytes transmitted by EDMA per TX event sent by UART.
** In UART FIFO mode, this should be equal to the TX Trigger Space value.
*/
unsigned int txBytesPerEvent = TX_BYTES_PER_EVENT;

/*
** Receive DMA Thresold Level. This applies to both UART FIFO and Non-FIFO
** modes of operation. For FIFO mode, refer to the comments of the API
** UARTFIFOConfig() to find the possible values of RX Trigger Level.
** For Non-FIFO mode, this value is 1.
*/
unsigned int rxTrigLevel = RX_DMA_THRESHOLD;

/* Transmit DMA Threshold Level. This is set in TX_DMA_THRESHOLD register. */
unsigned int txThreshLevel = TX_DMA_THRESHOLD;

UART_Driver UART_0;

int main(void)
{
    init_board();
    
    // Transmit welcone string
    UART_0.send(welcome, sizeof(welcome));
    UART_0.send(intent, sizeof(intent));
    UART_0.send(enter, sizeof(enter));
    
    UART_0.recieve(NUM_RX_BYTES);        // Receiving Data from User    
    UART_0.flush();                      // Echoing received bytes
    

    // Free EDMA3 Channels for TX and RX */
    EDMA3FreeChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_TX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_TX_CHA_NUM, EVT_QUEUE_NUM);

    EDMA3FreeChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                     EDMA3_UART_RX_CHA_NUM, EDMA3_TRIG_MODE_EVENT,
                     EDMA3_UART_RX_CHA_NUM, EVT_QUEUE_NUM);

    while(1);
}

/******************************** End of file *******************************/

