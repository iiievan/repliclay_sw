
#include "init.h"
#include "hw_types.h"
#include "soc_AM335x.h"
#include "hw_cm_per.h"
#include "hw_cm_wkup.h"
#include "beaglebone.h"

#include "gpio_v2.h"
#include "consoleUtils.h"
#include "interrupt.h"

#include "dmtimer.h"
#include "edma.h"
#include "edma_event.h"
#include "DM_Timer.h"
#include "OS_Timer.h"
#include "HS_I2C.h"
#include "I2C_EEPROM.h"
#include "n_UART.h"
#include "n_EDMA.h"
#include "error.h"
#include "cp15.h"
#include "hal_mmu.h"
#include "uart_irda_cir.h"
#include "uartStdio.h"
#include "UART_DT_driver.h"
#include "terminal/x_Print.h"

#ifndef beaglebone_black    // such a timer has not yet been described in DM_Timer.h
     OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_1);
#endif
OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_2);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_3);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_4);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_5);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_6);
// OS_Timer os_timer(DMTIMER::AM335X_DMTIMER_7);

extern void  BRDINFO_24LC32A_irqhandler(void *p_obj);
extern void  CAT24C256WI_irqhandler(void *p_obj);



I2C_EEPROM<(32*1024),32> BRDINFO_24LC32A(I2C::AM335X_I2C_0, SLAVE_ADDR_24LC32A, BRDINFO_24LC32A_irqhandler);
I2C_EEPROM<(32*1024),64> CAT24C256WI(I2C::AM335X_I2C_2, SLAVE_ADDR_CAT24C256, CAT24C256WI_irqhandler);

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

static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     unsigned int length,
                                     unsigned int tccNum,
                                     unsigned short linkAddr,
                                     unsigned int chNum);
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     unsigned int length,
                                     unsigned int tccNum,
                                     unsigned short linkAddr,
                                     unsigned int chNum);

#ifdef UART_ENABLE_FIFO
static void UartFIFOConfigure(void);
#endif

static void callback(unsigned int tccNum);
static void TxDummyPaRAMConfEnable(void);
static void EDMA3INTCConfigure(void);
static void Edma3CompletionIsr(void);
static void UartBaudRateSet(void);
static void Edma3CCErrorIsr(void);
static void EDMA3Initialize(void);
static void UARTInitialize(void);

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

static void (*cb_Fxn[EDMA3_NUM_TCC]) (unsigned int tcc);
unsigned char intent[] = "The application echoes the characters that you type on the console.\r\n";
unsigned char welcome[] = "StarterWare AM335X UART DMA application.\r\n";
unsigned char enter[] = "Please Enter 08 bytes from keyboard.\r\n";
volatile unsigned int clBackFlag = 0;

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


void init_board(void)   
{ 
    unsigned int numByteChunks = 0;
    unsigned char *pBuffer = NULL;
    unsigned int remainBytes = 0;
    
    /// Initialize MMU,Cache,Branch prediction etc... ///
    InitMem();                     // Initiate MMU and ... Invoke Cache  
    CP15BranchPredictionEnable();  // Enable Branch Prediction Shit */
    
    /// Initialize Interrupt controller /// 
    intc.master_IRQ_enable();      // Enable IRQ in CPSR
    intc.init();                   // Initializing the ARM Interrupt Controller.
    
    /// Initialize the OS-tick timer console /// 
    os_timer.setup(OS_TIMER_RLD_COUNT);
    
    /// Initialize the UART console /// 
    // If UART interrupts are used, 
    // setup them before the interrupt controller (INTC) is initiated
    uart_driver.probe((void *)&print);  // set read and write methods to "print" obj
    
    //uart_driver.init(); 

  ///************************** UART0_EDMA_INIT **************************
    
    // Configuring the system clocks for EDMA.
    EDMAModuleClkConfig();

    // Configuring the system clocks for UART0 instance.
    UART0ModuleClkConfig();

    // Performing Pin Multiplexing for UART0 instance.
    UARTPinMuxSetup(0);
    
    //IntMasterIRQEnable();     // Enabling IRQ in CPSR of ARM processor.    
    //IntAINTCInit(); // Initializing the ARM Interrupt Controller.
    
    EDMA3Init(SOC_EDMA30CC_0_REGS, EVT_QUEUE_NUM); // Initialization of EDMA3    
    //IntAINTCInit();       // Initializing the ARM Interrupt Controller.
    
    IntRegister(SYS_INT_EDMACOMPINT, Edma3CompletionIsr);   // Registering EDMA3 Channel Controller 0 transfer completion interrupt.
    
    IntPrioritySet(SYS_INT_EDMACOMPINT, 0, AINTC_HOSTINT_ROUTE_IRQ);    // Setting the priority for EDMA3CC0 completion interrupt in AINTC.
    
    IntRegister(SYS_INT_EDMAERRINT, Edma3CCErrorIsr);   // Registering EDMA3 Channel Controller 0 Error Interrupt.
    
    IntPrioritySet(SYS_INT_EDMAERRINT, 0, AINTC_HOSTINT_ROUTE_IRQ); // Setting the priority for EDMA3CC0 Error interrupt in AINTC.
    
    IntSystemEnable(SYS_INT_EDMACOMPINT);   // Enabling the EDMA3CC0 completion interrupt in AINTC.    
    
    IntSystemEnable(SYS_INT_EDMAERRINT);    // Enabling the EDMA3CC0 Error interrupt in AINTC.
    
    UARTModuleReset(UART_INSTANCE_BASE_ADD); // Performing a module reset.

#ifdef UART_ENABLE_FIFO    
    UartFIFOConfigure();    // Performing FIFO configurations.
#else    
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE); // Enabling DMA Mode 1.
#endif

#if (defined UART_ENABLE_FIFO) && (defined DIRECT_TX_DMA_THRESH_MODE)
    // Selecting the method of setting the Transmit DMA Threshold value.
    UARTTxDMAThresholdControl(UART_INSTANCE_BASE_ADD, UART_TX_DMA_THRESHOLD_REG);

    // Configuring the Transmit DMA Threshold value. 
    UARTTxDMAThresholdValConfig(UART_INSTANCE_BASE_ADD, txThreshLevel);
#endif
    // Performing Baud Rate settings.
    UartBaudRateSet();
    
    // Switching to Configuration Mode B.
    UARTRegConfigModeEnable(UART_INSTANCE_BASE_ADD, UART_REG_CONFIG_MODE_B);

    // Programming the Line Characteristics.
    UARTLineCharacConfig(UART_INSTANCE_BASE_ADD, (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1), 
                         UART_PARITY_NONE);
    
    UARTDivisorLatchDisable(UART_INSTANCE_BASE_ADD); // Disabling write access to Divisor Latches.
    
    UARTBreakCtl(UART_INSTANCE_BASE_ADD, UART_BREAK_COND_DISABLE); // Disabling Break Control.
    
    UARTOperatingModeSelect(UART_INSTANCE_BASE_ADD, UART16x_OPER_MODE); // Switching to UART16x operating mode.

    // Configuring the EDMA.

    // Request DMA Channel and TCC for UART Transmit
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_TX_CHA_NUM, EDMA3_UART_TX_CHA_NUM,
                        EVT_QUEUE_NUM);    
    cb_Fxn[EDMA3_UART_TX_CHA_NUM] = &callback; // Registering Callback Function for TX

    // Request DMA Channel and TCC for UART Receive 
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_RX_CHA_NUM, EDMA3_UART_RX_CHA_NUM,
                        EVT_QUEUE_NUM);    
    cb_Fxn[EDMA3_UART_RX_CHA_NUM] = &callback;  // Registering Callback Function for RX
    
  ///************************* UART0_EDMA_INIT *************************** ///
  ///******************** Transmission of a string **************************///

    numByteChunks = (sizeof(intent) - 1) / txBytesPerEvent;
    remainBytes = (sizeof(intent) - 1) % txBytesPerEvent;
    
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);  // Enabling DMA Mode 1.

    // Configuring EDMA PaRAM sets to transmit data.
    UARTTxEDMAPaRAMSetConfig(intent,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA3CC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);
    
    TxDummyPaRAMConfEnable();       // Configuring the PaRAM set for Dummy Transfer.    
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_TX_CHA_NUM, EDMA3_TRIG_MODE_EVENT);  // Enable EDMA Transfer

    // Wait for return from callback
    while(0 == clBackFlag);
    clBackFlag = 0;

    // Remaining bytes are transferred through polling method.
    if(0 != remainBytes)
    {
        pBuffer = intent + (sizeof(intent) - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    }
    
    ///******************** Transmission of a string **************************///

    print.ln("AM335x UART Driver started!");
    
    /// Initialize GPIO's ///
    GPIOModuleClkConfig(1);             // Enabling functional clocks for GPIO1 instance.
    GPIOModuleEnable(SOC_GPIO_1_REGS);  // Enabling the GPIO module.
    GPIOModuleReset(SOC_GPIO_1_REGS);   // Resetting the GPIO module. */
    
    //board_info_check((uint8_t *)BBB_A3_VERSION);
}

#ifdef UART_ENABLE_FIFO
/*
** A wrapper function performing FIFO configurations.
*/
static void UartFIFOConfigure(void)
{
    unsigned int fifoConfig = 0;

    /*
    ** Transmitter Trigger Level Granularity is 1.
    ** Receiver Trigger Level Granularity is 1.
    ** Transmit Trigger Space set using 'txTrigSpace'.
    ** Receive Trigger level set using 'rxTrigLevel'.
    ** Clear the Trasnmit FIFO.
    ** Clear the Receive FIFO.
    ** DMA Mode enabling shall happen through SCR register.
    ** DMA Mode 1 is enabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  txTrigSpace,
                                  rxTrigLevel,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_1_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(UART_INSTANCE_BASE_ADD, fifoConfig);
}
#endif

static void UartBaudRateSet(void)
{
    unsigned int divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_115200,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(UART_INSTANCE_BASE_ADD, divisorValue);

}

/*
** EDMA Completion Interrupt Service Routine(ISR).
*/
static void Edma3CompletionIsr(void)
{
    volatile unsigned int pendingIrqs;
    unsigned int index = 1;
    unsigned int count = 0;

    if(EDMA3GetIntrStatus(SOC_EDMA30CC_0_REGS))
    {
        /*
        ** Wait for a finite time to monitor the EDMA Completion Interrupt
        ** status.
        */
        while ((count < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0;

            /* Get the Interrupt status. */
            pendingIrqs = EDMA3GetIntrStatus(SOC_EDMA30CC_0_REGS);
            while(pendingIrqs)
            {
                if((pendingIrqs & 1u) == TRUE)
                {
                    /* Clear the interrupt status. */
                    EDMA3ClrIntr(SOC_EDMA30CC_0_REGS, index);

                    (*cb_Fxn[index])(index);
                }
                ++index;
                pendingIrqs >>= 1u;
            }
            count++;
        }
    }
}

/*
** This function is used as a callback from EDMA3 Completion Handler.
*/
static void callback(unsigned int tccNum)
{
    /* Disabling DMA Mode of operation in UART. */
    UARTDMADisable(UART_INSTANCE_BASE_ADD);

    /* Disabling DMA transfer on the specified channel. */
    EDMA3DisableTransfer(SOC_EDMA30CC_0_REGS, tccNum, EDMA3_TRIG_MODE_EVENT);

    clBackFlag = 1;
}

/*
** EDMA Error Interrupt Service Routine(ISR).
*/

static void Edma3CCErrorIsr(void)
{
    volatile unsigned int pendingIrqs = 0;
    unsigned int evtqueNum = 0;
    unsigned int index = 1;
    unsigned int Cnt = 0;

    if((0 != EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS)) ||
       (0 != (EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS))))
    {
        /* Loop for EDMA3CC_ERR_HANDLER_RETRY_COUNT number of time, breaks
           when no pending interrupt is found */
        while ((Cnt < EDMA3CC_ERR_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0u;
            pendingIrqs = EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS);

            while (pendingIrqs)
            {
                /*Process all the pending interrupts*/
                if((pendingIrqs & 1u)==TRUE)
                {
                    /* Writing to EMCR to clear the corresponding EMR bits.
                       Also clearing any Secondary events in SER. */
                    EDMA3ClrMissEvt(SOC_EDMA30CC_0_REGS, index);
                }
                ++index;
                pendingIrqs >>= 1u;
            }
            index = 0u;

            pendingIrqs = EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS);
            if (pendingIrqs != 0u)
            {
                /* Process all the pending CC error interrupts. */
                /* Queue threshold error for different event queues. */
                for (evtqueNum = 0u; evtqueNum < EDMA3_0_NUM_EVTQUE; evtqueNum++)
                {
                    if((pendingIrqs & (1u << evtqueNum)) != 0u)
                    {
                        /* Clear the error interrupt. */
                        EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS, (1u << evtqueNum));
                    }
                }

                /* Transfer completion code error. */
                if ((pendingIrqs & (1 << EDMA3CC_CCERR_TCCERR_SHIFT)) != 0u)
                {
                    EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS,
                                  (0x01u << EDMA3CC_CCERR_TCCERR_SHIFT));
                }
                ++index;
            }

            Cnt++;
        }

        /* Enable error to be evaluated again */
        EDMA3CCErrorEvaluate(SOC_EDMA30CC_0_REGS);
    }
}

/*
** This function configures and sets the EDMA PaRAM set values for
** transferring data to UART TX FIFO.
*/
static void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                                     unsigned int length,
                                     unsigned int tccNum,
                                     unsigned short linkAddr,
                                     unsigned int chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr = (unsigned int) txBuffer;
    paramSet.destAddr = (unsigned int)UART_THR_RHR_REG;

    paramSet.aCnt = (unsigned short)1;
    paramSet.bCnt = (unsigned short)txBytesPerEvent;
    paramSet.cCnt = (unsigned short)(length / txBytesPerEvent);
    paramSet.srcBIdx = (short)1;
    paramSet.srcCIdx = (short)txBytesPerEvent;

    /* The destination indexes should not increment since it is a h/w register. */
    paramSet.destBIdx = (short)0;
    paramSet.destCIdx = (short)0;

    paramSet.linkAddr = (unsigned short)linkAddr;
    paramSet.bCntReload = (unsigned short)0;

    /* OPT PaRAM entries. */
    paramSet.opt = (unsigned int)0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA3CC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |= ((tccNum << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA3CC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS, chNum, &paramSet);
}

/*
** This function configures and sets the EDMA PaRAM set values for
** receiving data from UART RX FIFO.
*/
static void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                                     unsigned int length,
                                     unsigned int tccNum,
                                     unsigned short linkAddr,
                                     unsigned int chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    /* Fill the PaRAM Set with transfer specific information */
    paramSet.srcAddr = (unsigned int)UART_THR_RHR_REG;
    paramSet.destAddr = (unsigned int)rxBuffer;

    paramSet.aCnt = (unsigned short)1;
    paramSet.bCnt = (unsigned short)(rxTrigLevel);
    paramSet.cCnt = (unsigned short)(length / rxTrigLevel);
    paramSet.destBIdx = (short)1;
    paramSet.destCIdx = (short)rxTrigLevel;

    paramSet.srcBIdx = (short)0;
    paramSet.srcCIdx = (short)0;

    paramSet.linkAddr = (unsigned short)linkAddr;
    paramSet.bCntReload = (unsigned short)0;

    /* OPT PaRAM Entries. */
    paramSet.opt = (unsigned int)0x0;

    /* Source and Destination addressing modes are Incremental. */

    /* Enable AB Synchronized Transfer. */
    paramSet.opt |= (1 << EDMA3CC_OPT_SYNCDIM_SHIFT);

    /* Setting the Transfer Complete Code(TCC). */
    paramSet.opt |= ((tccNum << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);

    /* Enabling the Completion Interrupt. */
    paramSet.opt |= (1 << EDMA3CC_OPT_TCINTEN_SHIFT);

    /* Now write the PaRAM Set */
    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS, chNum, &paramSet);
}

/*
** This configures the PaRAM set for the Dummy Transfer.
*/

static void TxDummyPaRAMConfEnable(void)
{
    EDMA3CCPaRAMEntry dummyPaRAMSet;

    dummyPaRAMSet.aCnt = 1;
    dummyPaRAMSet.bCnt = 0;
    dummyPaRAMSet.cCnt = 0;
    dummyPaRAMSet.srcAddr = 0;
    dummyPaRAMSet.destAddr = 0;
    dummyPaRAMSet.srcBIdx = 0;
    dummyPaRAMSet.destBIdx = 0;
    dummyPaRAMSet.srcCIdx = 0;
    dummyPaRAMSet.destCIdx = 0; 
    dummyPaRAMSet.linkAddr = 0xFFFF;
    dummyPaRAMSet.bCntReload = 0;
    dummyPaRAMSet.opt = 0;

    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS, DUMMY_CH_NUM, &dummyPaRAMSet);
}

void GPIOModuleClkConfig(CPU_INT32U x)
{
    switch(x)
    {
        case 0:
            GPIO0ModuleClkConfig();
        break;
        case 1:
            GPIO1ModuleClkConfig();
        break;
    }
}

uint32_t board_info_check(uint8_t *board_ver)
{
    uint8_t  board_id[30];
    uint8_t *p_Read = BRDINFO_24LC32A.read({.addr = 0x0000},30);
    
    std::memcpy(&board_id[0],p_Read, sizeof(board_id));
    
    if(!(strcmp(BBB_BOARD_NAME, (char *)board_id)))
    {
        if(!(strcmp(BBB_A1_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A1;
        }
        else if(!(strcmp(BBB_A2_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A2;
        }
        else if(!(strcmp(BBB_A3_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A3;
        }
        else if(!(strcmp(BBB_A5_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A5;
        }
        else if(!(strcmp(BBB_A6_VERSION, (char *)board_ver)))
        {
            return BOARD_ID_BBB_A6;
        }
        else
        {
            return BOARD_VER_UNKNOWN;
        }
    }
    else
    {
        return BOARD_UNKNOWN;
    }
}

