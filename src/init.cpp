
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
#include "iar_dynamic_init.h"
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
//#define UART_ENABLE_FIFO

static void UART_TX_eDMA_paRAM_set(uint8_t *tx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num);
static void UART_RX_eDMA_paRAM_set(uint8_t *rx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num);

#ifdef UART_ENABLE_FIFO
static void UartFIFOConfigure(void);
#endif

static void callback(unsigned int tccNum);
static void Tx_dummy_paRAM_config_enable(void);
static void EDMA3_completion_isr(void *p_Obj);
static void EDMA3_error_isr(void *p_Obj);
static void UartBaudRateSet(void);
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

static void (*cb_Fxn[n_EDMA::AM335X_DMACH_MAX]) (unsigned int tcc);
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
    
    __iar_dynamic_initialization();
    
    /// Initialize Interrupt controller /// 
    //intc.master_IRQ_enable();      // Enable IRQ in CPSR
    //intc.init();                   // Initializing the ARM Interrupt Controller.
    
    /// Initialize the OS-tick timer console /// 
    //os_timer.setup(OS_TIMER_RLD_COUNT);
    
    /// Initialize the UART console /// 
    // If UART interrupts are used, 
    // setup them before the interrupt controller (INTC) is initiated
    //uart_driver.probe((void *)&print);  // set read and write methods to "print" obj
    
    //uart_driver.init(); 

  ///************************** UART0_EDMA_INIT **************************    
    
    prcm_module.run_EDMA_clk((void *)&dma);
    prcm_module.run_clk_UART0();
    ctrl_module.UART0_pin_mux_setup();
    
    intc.master_IRQ_enable();      // Enable IRQ in CPSR
    intc.init();                   // Initializing the ARM Interrupt Controller.
    dma.init(n_EDMA::EVENT_Q0);
    
    intc.init();                   // Initializing the ARM Interrupt Controller.    
    intc.register_handler(INTC::EDMACOMPINT, EDMA3_completion_isr);     // Registering EDMA3 Channel Controller 0 transfer completion interrupt.    
    intc.priority_set(INTC::EDMACOMPINT, 0, INTC::HOSTINT_ROUTE_IRQ);   // Setting the priority for EDMA3CC0 completion interrupt in AINTC.    
    intc.register_handler(INTC::EDMAERRINT, EDMA3_error_isr);           // Registering EDMA3 Channel Controller 0 Error Interrupt.    
    intc.priority_set(INTC::EDMAERRINT, 0, INTC::HOSTINT_ROUTE_IRQ);    // Setting the priority for EDMA3CC0 Error interrupt in AINTC.    
    intc.system_enable(INTC::EDMACOMPINT);                              // Enabling the EDMA3CC0 completion interrupt in AINTC.    
    intc.system_enable(INTC::EDMAERRINT);                               // Enabling the EDMA3CC0 Error interrupt in AINTC.   
    
    uart_0.module_reset();
    
#ifdef UART_ENABLE_FIFO    
    uart_0.FIFO_configure_DMA_RxTx(TX_TRIGGER_SPACE_GRAN_1, RX_DMA_THRESHOLD);  // 8, 8

#else    
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);
#endif

#if (defined UART_ENABLE_FIFO) && (defined DIRECT_TX_DMA_THRESH_MODE)
    uart_0.TX_DMA_threshold_control(true);     
    uart_0.TX_DMA_threshold_val_config(TX_DMA_THRESHOLD);
#endif
   
    uart_0.BAUD_set(BAUD_RATE_115200);                                // Performing Baud Rate settings.
    uart_0.reg_config_mode_enable(n_UART::CONFIG_MODE_B);   // Switching to Configuration Mode B. 
    
    // Programming the Line Characteristics. 
    uart_0.char_len_config(n_UART::CHL_8_BITS);
    uart_0.stop_bit_config(n_UART::STOP_1);
    uart_0.parity_config(n_UART::PARITY_NONE);
             
    uart_0.divisor_latch_disable();                         // Disabling write access to Divisor Latches.        
    uart_0.break_ctl(false);                                // Disabling Break Control.
    uart_0.operating_mode_select(n_UART::MODE_UART_16x);    // Switching to UART16x operating mode. 

    // Configuring the EDMA.
    // Request DMA Channel and TCC for UART Transmit
    dma.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_TX, n_EDMA::CH_UART0_TX, n_EDMA::EVENT_Q0);    
    cb_Fxn[n_EDMA::CH_UART0_TX] = &callback; // Registering Callback Function for TX

    // Request DMA Channel and TCC for UART Receive   
    dma.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_RX, n_EDMA::CH_UART0_RX, n_EDMA::EVENT_Q0);
    cb_Fxn[n_EDMA::CH_UART0_RX] = &callback;  // Registering Callback Function for RX
    
  ///************************* UART0_EDMA_INIT *************************** ///
  ///******************** Transmission of a string **************************///

    numByteChunks = (sizeof(intent) - 1) / txBytesPerEvent;
    remainBytes = (sizeof(intent) - 1) % txBytesPerEvent;
    
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);

    // Configuring EDMA PaRAM sets to transmit data.
     UART_TX_eDMA_paRAM_set((uint8_t *)welcome,
                             numByteChunks * txBytesPerEvent,
                             n_EDMA::CH_UART0_TX,
                             DUMMY_CH_NUM,
                             n_EDMA::CH_UART0_TX);
    
    Tx_dummy_paRAM_config_enable();       // Configuring the PaRAM set for Dummy Transfer.    
    

    dma.enable_transfer(n_EDMA::CH_UART0_TX, n_EDMA::TRIG_MODE_EVENT);
                        
    // Wait for return from callback
    while(0 == clBackFlag);
    clBackFlag = 0;

    // Remaining bytes are transferred through polling method.
    if(0 != remainBytes)
    {
        pBuffer = welcome + (sizeof(welcome) - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    }
    
/******************** Transmission of a string **************************/

    numByteChunks = (sizeof(intent) - 1) / txBytesPerEvent;
    remainBytes = (sizeof(intent) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);

    /* Configuring EDMA PaRAM sets to transmit data. */
      UART_TX_eDMA_paRAM_set((uint8_t *)intent,
                             numByteChunks * txBytesPerEvent,
                             n_EDMA::CH_UART0_TX,
                             DUMMY_CH_NUM,
                             n_EDMA::CH_UART0_TX);
      
    /* Configuring the PaRAM set for Dummy Transfer. */
    Tx_dummy_paRAM_config_enable();

    /* Enable EDMA Transfer */
    dma.enable_transfer(n_EDMA::CH_UART0_TX, n_EDMA::TRIG_MODE_EVENT);

    /* Wait for return from callback */
    while(0 == clBackFlag);
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if(0 != remainBytes)
    {
        pBuffer = intent + (sizeof(intent) - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    }

    /******************** Transmission of a string **************************/

    numByteChunks = (sizeof(enter) - 1) / txBytesPerEvent;
    remainBytes = (sizeof(enter) - 1) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    //UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);

    /* Configuring EDMA PaRAM sets to transmit 'enter' message. */
    UART_TX_eDMA_paRAM_set((uint8_t *)enter,
                             numByteChunks * txBytesPerEvent,
                             n_EDMA::CH_UART0_TX,
                             DUMMY_CH_NUM,
                             n_EDMA::CH_UART0_TX);
    /* Configuring the PaRAM set for Dummy Transfer. */
    Tx_dummy_paRAM_config_enable();

    /* Enable EDMA Transfer */
    dma.enable_transfer(n_EDMA::CH_UART0_TX, n_EDMA::TRIG_MODE_EVENT);
    
    /* Wait for return from callback */
    while(0 == clBackFlag);
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if(0 != remainBytes)
    {
        pBuffer = enter + (sizeof(enter) - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    }

    /********************* Receiving Data from User *************************/

    /* Enabling DMA Mode 1. */
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);
    
    /* Configuring the PaRAM set for reception. */
    UART_RX_eDMA_paRAM_set((uint8_t *)rxBuffer,
                           NUM_RX_BYTES,
                           n_EDMA::CH_UART0_RX,
                             0xFFFF,
                           n_EDMA::CH_UART0_RX);
                           
    /* Enable EDMA Transfer */
    dma.enable_transfer(n_EDMA::CH_UART0_RX, n_EDMA::TRIG_MODE_EVENT);
    
    /* Wait for return from callback */
    while(0 == clBackFlag);
    clBackFlag = 0;

    /******************* Echoing received bytes *****************************/

    numByteChunks = (NUM_RX_BYTES) / txBytesPerEvent;
    remainBytes = (NUM_RX_BYTES) % txBytesPerEvent;

    /* Enabling DMA Mode 1. */
    //UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);
    
    /* Configuring the PaRAM set to transmit the bytes that were received. */
    /*
    UARTTxEDMAPaRAMSetConfig(rxBuffer,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA3CC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);
*/
    UART_TX_eDMA_paRAM_set((uint8_t *)rxBuffer,
                             numByteChunks * txBytesPerEvent,
                             n_EDMA::CH_UART0_TX,
                             DUMMY_CH_NUM,
                             n_EDMA::CH_UART0_TX);

    /* Configuring the PaRAM set for Dummy Transfer. */
    Tx_dummy_paRAM_config_enable();

    /* Enable EDMA Transfer */
    //EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_TX_CHA_NUM, EDMA3_TRIG_MODE_EVENT);
    dma.enable_transfer(n_EDMA::CH_UART0_TX, n_EDMA::TRIG_MODE_EVENT);
    
    /* Wait for return from callback */
    while(0 == clBackFlag);
    clBackFlag = 0;

    /* Remaining bytes are transferred through polling method. */
    if(0 != remainBytes)
    {
        pBuffer = rxBuffer + NUM_RX_BYTES - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    }

    /******************* Freeing of allocated channels **********************/
    /* Free EDMA3 Channels for TX and RX */    
    dma.free_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_TX, 
                     n_EDMA::TRIG_MODE_EVENT, n_EDMA::CH_UART0_TX, n_EDMA::EVENT_Q0);
    
    dma.free_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_RX, 
                     n_EDMA::TRIG_MODE_EVENT, n_EDMA::CH_UART0_RX, n_EDMA::EVENT_Q0);

    while(1);

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
static void EDMA3_completion_isr(void *p_Obj)
{
    AM335x_EDMA &s_EDMA = *reinterpret_cast<AM335x_EDMA *>(p_Obj);
    
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
static void EDMA3_error_isr(void *p_Obj)
{
    AM335x_EDMA &s_EDMA = *reinterpret_cast<AM335x_EDMA *>(p_Obj);

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
static void UART_TX_eDMA_paRAM_set(uint8_t *tx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num)
{
    n_EDMA::paRAM_entry_t param_set;

    /// Fill the PaRAM Set with transfer specific information ///
    param_set.SRC = (uint32_t)tx_buffer;
    param_set.DST = (uint32_t)UART_THR_RHR_REG;

    param_set.ACNT = (uint16_t)1;
    param_set.BCNT = (uint16_t)txBytesPerEvent;
    param_set.CCNT = (uint16_t)(len / txBytesPerEvent);
    param_set.SRCBIDX = (int16_t)1;
    param_set.SRCCIDX = (int16_t)txBytesPerEvent;

    /// The destination indexes should not increment since it is a h/w register. ///
    param_set.DSTBIDX = (int16_t)0;
    param_set.DSTCIDX = (int16_t)0;

    param_set.LINK = (uint16_t)*n_EDMA::get_paRAM_ptr(param_num);
    param_set.BCNTRLD = (uint16_t)0;

    /// OPT PaRAM Entries. ///
    ///Source and Destination addressing modes are Incremental.//
    param_set.OPT.b.SYNCDIM = HIGH;     // AB_sync
    param_set.OPT.b.TCC = tcc_num;      // Setting the Transfer Complete Code(TCC).
    param_set.OPT.b.TCINTEN = HIGH;     // Enabling the Completion Interrupt.
    
    dma.set_paRAM(ch_num, &param_set);  //Now write the PaRAM set
}


static void UART_RX_eDMA_paRAM_set(uint8_t *rx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num)
{
    n_EDMA::paRAM_entry_t param_set;

    /// Fill the PaRAM Set with transfer specific information ///
    param_set.SRC = (uint32_t)UART_THR_RHR_REG;
    param_set.DST = (uint32_t)rx_buffer;

    param_set.ACNT = (uint16_t)1;
    param_set.BCNT = (uint16_t)(rxTrigLevel);
    param_set.CCNT = (uint16_t)(len / rxTrigLevel);
    param_set.DSTBIDX = (int16_t)1;
    param_set.DSTCIDX = (int16_t)rxTrigLevel;

    param_set.SRCBIDX = (int16_t)0;
    param_set.SRCCIDX = (int16_t)0;

    if(param_num == 0xFFFF)
        param_set.LINK = 0xFFFF;
    else
        param_set.LINK = (uint16_t)*n_EDMA::get_paRAM_ptr(param_num);
    
    param_set.BCNTRLD = (uint16_t)0;

    /// OPT PaRAM Entries. ///
    ///Source and Destination addressing modes are Incremental.//
    param_set.OPT.b.SYNCDIM = HIGH;     // AB_sync
    param_set.OPT.b.TCC = tcc_num;      // Setting the Transfer Complete Code(TCC).
    param_set.OPT.b.TCINTEN = HIGH;     // Enabling the Completion Interrupt.
    
    dma.set_paRAM(ch_num, &param_set);  //Now write the PaRAM set
}


//This configures the PaRAM set for the Dummy Transfer.
static void Tx_dummy_paRAM_config_enable(void)
{
    n_EDMA::paRAM_entry_t dummy_param_set;

    dummy_param_set.ACNT = 1;
    dummy_param_set.BCNT = 0;
    dummy_param_set.CCNT = 0;
    dummy_param_set.SRC = 0;
    dummy_param_set.DST = 0;
    dummy_param_set.SRCBIDX = 0;
    dummy_param_set.DSTBIDX = 0;
    dummy_param_set.SRCCIDX = 0;
    dummy_param_set.DSTCIDX = 0; 
    dummy_param_set.LINK = 0xFFFF;
    dummy_param_set.BCNTRLD = 0;

    dma.set_paRAM(DUMMY_CH_NUM, &dummy_param_set);
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

