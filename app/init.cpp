#include "init.h"
#include "n_EDMA.h"
//#include "cp15.h"
//#include "hal_mmu.h"
//#include "iar_dynamic_init.h" // in case using RTOS


void (*cb_Fxn[EDMA3_NUM_TCC]) (unsigned int tcc);
unsigned int clBackFlag = 0;

void init_board(void)
{ 
      /// Initialize MMU,Cache,Branch prediction etc... ///
    //InitMem();                     // Initiate MMU and ... Invoke Cache  
    //CP15BranchPredictionEnable();  // Enable Branch Prediction Shit */
    
    //__iar_dynamic_initialization();       // in case using RTOS
    
    EDMAModuleClkConfig();  // Configuring the system clocks for EDMA.    
    UART0ModuleClkConfig(); // Configuring the system clocks for UART0 instance.     
    UARTPinMuxSetup(0);     // Performing Pin Multiplexing for UART0 instance.     
    IntMasterIRQEnable();   // Enabling IRQ in CPSR of ARM processor.    
    IntAINTCInit();         // Initializing the ARM Interrupt Controller.     
    EDMA3Initialize();      // Initializing the EDMA.    
    UARTInitialize();       // Initializing the UART0 instance for use. 

    /******************** Configuring the EDMA **************************/
    // Request DMA Channel and TCC for UART Transmit
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_TX_CHA_NUM, EDMA3_UART_TX_CHA_NUM,
                        EVT_QUEUE_NUM);

    // Registering Callback Function for TX
    cb_Fxn[EDMA3_UART_TX_CHA_NUM] = &callback;

    // Request DMA Channel and TCC for UART Receive 
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_RX_CHA_NUM, EDMA3_UART_RX_CHA_NUM,
                        EVT_QUEUE_NUM);

    // Registering Callback Function for RX
    cb_Fxn[EDMA3_UART_RX_CHA_NUM] = &callback;
}
   
// This function configures and sets the EDMA PaRAM set values for
// transferring data to UART TX FIFO.
void UARTTxEDMAPaRAMSetConfig(unsigned char *txBuffer,
                              unsigned int length,
                              unsigned int tccNum,
                              unsigned short linkAddr,
                              unsigned int chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    // Fill the PaRAM Set with transfer specific information 
    paramSet.srcAddr = (unsigned int) txBuffer;
    paramSet.destAddr = (unsigned int)UART_THR_RHR_REG;

    paramSet.aCnt = (unsigned short)1;
    paramSet.bCnt = (unsigned short)txBytesPerEvent;
    paramSet.cCnt = (unsigned short)(length / txBytesPerEvent);
    paramSet.srcBIdx = (short)1;
    paramSet.srcCIdx = (short)txBytesPerEvent;

    // The destination indexes should not increment since it is a h/w register. 
    paramSet.destBIdx = (short)0;
    paramSet.destCIdx = (short)0;

    paramSet.linkAddr = (unsigned short)linkAddr;
    paramSet.bCntReload = (unsigned short)0;

    // OPT PaRAM entries.
    paramSet.opt = (unsigned int)0x0;

    // Source and Destination addressing modes are Incremental.     
    paramSet.opt |= (1 << EDMA3CC_OPT_SYNCDIM_SHIFT); // AB Synchronized Transfer.    
    paramSet.opt |= ((tccNum << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);  // Setting the Transfer Complete Code(TCC).    
    paramSet.opt |= (1 << EDMA3CC_OPT_TCINTEN_SHIFT);   // Enabling the Completion Interrupt.    
    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS, chNum, &paramSet);   // Now write the PaRAM Set 
}

// This function configures and sets the EDMA PaRAM set values for
// receiving data from UART RX FIFO.
void UARTRxEDMAPaRAMSetConfig(unsigned char *rxBuffer,
                              unsigned int length,
                              unsigned int tccNum,
                              unsigned short linkAddr,
                              unsigned int chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    // Fill the PaRAM Set with transfer specific information 
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

    // OPT PaRAM Entries.
    paramSet.opt = (unsigned int)0x0;

    // Source and Destination addressing modes are Incremental.     
    paramSet.opt |= (1 << EDMA3CC_OPT_SYNCDIM_SHIFT);                       // Enable AB Synchronized Transfer.     
    paramSet.opt |= ((tccNum << EDMA3CC_OPT_TCC_SHIFT) & EDMA3CC_OPT_TCC);  // Setting the Transfer Complete Code(TCC).    
    paramSet.opt |= (1 << EDMA3CC_OPT_TCINTEN_SHIFT);                       // Enabling the Completion Interrupt.   
    
    EDMA3SetPaRAM(SOC_EDMA30CC_0_REGS, chNum, &paramSet);                   // Now write the PaRAM Set 
}


// This configures the PaRAM set for the Dummy Transfer.
void TxDummyPaRAMConfEnable(void)
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


// EDMA Completion Interrupt Service Routine(ISR).
void Edma3CompletionIsr(void)
{
    volatile unsigned int pendingIrqs;
    unsigned int index = 1;
    unsigned int count = 0;

    if(EDMA3GetIntrStatus(SOC_EDMA30CC_0_REGS))
    {
        // Wait for a finite time to monitor the EDMA Completion Interrupt
        // status.
        while ((count < EDMA3CC_COMPL_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0;
            
            pendingIrqs = EDMA3GetIntrStatus(SOC_EDMA30CC_0_REGS);  // Get the Interrupt status. 
            
            while(pendingIrqs)
            {
                if((pendingIrqs & 1u) == TRUE)
                {                    
                    EDMA3ClrIntr(SOC_EDMA30CC_0_REGS, index);   // Clear the interrupt status. 

                    (*cb_Fxn[index])(index);
                }
                ++index;
                pendingIrqs >>= 1u;
            }
            count++;
        }
    }
}


// This function is used as a callback from EDMA3 Completion Handler.
void callback(unsigned int tccNum)
{
     
    UARTDMADisable(UART_INSTANCE_BASE_ADD); // Disabling DMA Mode of operation in UART.     
    EDMA3DisableTransfer(SOC_EDMA30CC_0_REGS, tccNum, EDMA3_TRIG_MODE_EVENT);   // Disabling DMA transfer on the specified channel.

    clBackFlag = 1;
}

// EDMA Error Interrupt Service Routine(ISR).
void Edma3CCErrorIsr(void)
{
    volatile unsigned int pendingIrqs = 0;
    unsigned int evtqueNum = 0;
    unsigned int index = 1;
    unsigned int Cnt = 0;

    if((0 != EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS)) ||
       (0 != (EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS))))
    {
        // Loop for EDMA3CC_ERR_HANDLER_RETRY_COUNT number of time, breaks
        // when no pending interrupt is found 
        while ((Cnt < EDMA3CC_ERR_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0u;
            pendingIrqs = EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS);

            while (pendingIrqs)
            {
                // Process all the pending interrupts
                if((pendingIrqs & 1u)==TRUE)
                {
                    // Writing to EMCR to clear the corresponding EMR bits.
                    // Also clearing any Secondary events in SER. 
                    EDMA3ClrMissEvt(SOC_EDMA30CC_0_REGS, index);
                }
                ++index;
                pendingIrqs >>= 1u;
            }
            
            index = 0u;

            pendingIrqs = EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS);
            if (pendingIrqs != 0u)
            {
                // Process all the pending CC error interrupts. 
                // Queue threshold error for different event queues. 
                for (evtqueNum = 0u; evtqueNum < EDMA3_0_NUM_EVTQUE; evtqueNum++)
                {
                    if((pendingIrqs & (1u << evtqueNum)) != 0u)
                    {
                        // Clear the error interrupt. 
                        EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS, (1u << evtqueNum));
                    }
                }

                // Transfer completion code error. 
                if ((pendingIrqs & (1 << EDMA3CC_CCERR_TCCERR_SHIFT)) != 0u)
                {
                    EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS, (0x01u << EDMA3CC_CCERR_TCCERR_SHIFT));
                }
                
                ++index;
            }

            Cnt++;
        }
        
        EDMA3CCErrorEvaluate(SOC_EDMA30CC_0_REGS);  // Enable error to be evaluated again 
    }
}

 
// Powering up, initializing and registering interrupts for EDMA.
void EDMA3Initialize(void)
{    
    EDMA3Init(SOC_EDMA30CC_0_REGS, EVT_QUEUE_NUM);  // Initialization of EDMA3      
    EDMA3INTCConfigure();   // Configuring the AINTC to receive EDMA3 interrupts.
}


// This function initializes the UART instance for use.
void UARTInitialize(void)
{     
    UARTModuleReset(UART_INSTANCE_BASE_ADD);    // Performing a module reset.

#ifdef UART_ENABLE_FIFO     
    UartFIFOConfigure();    // Performing FIFO configurations.
#else    
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);  // Enabling DMA Mode 1. 
#endif

#if (defined UART_ENABLE_FIFO) && (defined DIRECT_TX_DMA_THRESH_MODE)    
    UARTTxDMAThresholdControl(UART_INSTANCE_BASE_ADD, UART_TX_DMA_THRESHOLD_REG);   // Selecting the method of setting the Transmit DMA Threshold value.    
    UARTTxDMAThresholdValConfig(UART_INSTANCE_BASE_ADD, txThreshLevel); // Configuring the Transmit DMA Threshold value.
#endif
    
    UartBaudRateSet();  // Performing Baud Rate settings.    
    UARTRegConfigModeEnable(UART_INSTANCE_BASE_ADD, UART_REG_CONFIG_MODE_B);    // Switching to Configuration Mode B.

    // Programming the Line Characteristics.
    UARTLineCharacConfig(UART_INSTANCE_BASE_ADD,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1), 
                         UART_PARITY_NONE);
    
    UARTDivisorLatchDisable(UART_INSTANCE_BASE_ADD);    // Disabling write access to Divisor Latches.     
    UARTBreakCtl(UART_INSTANCE_BASE_ADD, UART_BREAK_COND_DISABLE);  // Disabling Break Control.    
    UARTOperatingModeSelect(UART_INSTANCE_BASE_ADD, UART16x_OPER_MODE); // Switching to UART16x operating mode. 
}


#ifdef UART_ENABLE_FIFO
// A wrapper function performing FIFO configurations.
void UartFIFOConfigure(void)
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
#endif  //UART_ENABLE_FIFO


// A wrapper function performing Baud Rate settings.
void UartBaudRateSet(void)
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


// This function configures the AINTC to receive EDMA3 interrupts.
void EDMA3INTCConfigure(void)
{    
    //IntAINTCInit();       // Initializing the ARM Interrupt Controller.    
    IntRegister(SYS_INT_EDMACOMPINT, Edma3CompletionIsr);                   // Registering EDMA3 Channel Controller 0 transfer completion interrupt.    
    IntPrioritySet(SYS_INT_EDMACOMPINT, 0, AINTC_HOSTINT_ROUTE_IRQ);        // Setting the priority for EDMA3CC0 completion interrupt in AINTC.    
    IntRegister(SYS_INT_EDMAERRINT, Edma3CCErrorIsr);       // Registering EDMA3 Channel Controller 0 Error Interrupt.    
    IntPrioritySet(SYS_INT_EDMAERRINT, 0, AINTC_HOSTINT_ROUTE_IRQ);     // Setting the priority for EDMA3CC0 Error interrupt in AINTC.    
    IntSystemEnable(SYS_INT_EDMACOMPINT);           // Enabling the EDMA3CC0 completion interrupt in AINTC. 
    IntSystemEnable(SYS_INT_EDMAERRINT);            // Enabling the EDMA3CC0 Error interrupt in AINTC.
}

void UART_send(unsigned char * s, size_t len)
{
    unsigned int numByteChunks = 0;
    unsigned char *pBuffer = nullptr;
    unsigned int remainBytes = 0;

    numByteChunks = (len - 1) / txBytesPerEvent;
    remainBytes = (len - 1) % txBytesPerEvent;    
     
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE); // Enabling DMA Mode 1.

    // Configuring EDMA PaRAM sets to transmit  message. 
    UARTTxEDMAPaRAMSetConfig(s,
                             numByteChunks * txBytesPerEvent,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA3CC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    // Configuring the PaRAM set for Dummy Transfer.
    TxDummyPaRAMConfEnable();

    // Enable EDMA Transfer
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    // Wait for return from callback 
    while(0 == clBackFlag);
    clBackFlag = 0;

    // Remaining bytes are transferred through polling method. 
    if(0 != remainBytes)
    {
        pBuffer = s + (len - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    } 
}

void UART_rcv(unsigned char * buff, size_t len)
{
    // Enabling DMA Mode 1.
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);

    // Configuring the PaRAM set for reception. */
    UARTRxEDMAPaRAMSetConfig(buff,
                             len,
                             EDMA3_UART_RX_CHA_NUM,
                             0xFFFF,
                             EDMA3_UART_RX_CHA_NUM);

    // Enable EDMA Transfer
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_RX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    // Wait for return from callback 
    while(0 == clBackFlag);
    clBackFlag = 0; 
}

/******************************** End of file *******************************/

