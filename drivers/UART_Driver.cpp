#include "UART_Driver.h"
#include <cstring>


UART_Driver::UART_Driver()
{

}

UART_Driver::~UART_Driver()
{

}

void  UART_Driver::setup()
{
    m_TX_busy = false;
    
    m_tx_trig_space = TX_TRIGGER_SPACE_GRAN_1;
    m_tx_bytes_per_event = TX_BYTES_PER_EVENT;
    m_rx_trig_level = RX_DMA_THRESHOLD;
    m_tx_thresh_level = TX_DMA_THRESHOLD;

    memset(m_rxBuffer,'\0', sizeof(m_rxBuffer));

    EDMAModuleClkConfig();  // Configuring the system clocks for EDMA.    
    UART0ModuleClkConfig(); // Configuring the system clocks for UART0 instance.     
    UARTPinMuxSetup(0);     // Performing Pin Multiplexing for UART0 instance.     
    IntMasterIRQEnable();   // Enabling IRQ in CPSR of ARM processor.    
    IntAINTCInit();         // Initializing the ARM Interrupt Controller.

    EDMA3Init(SOC_EDMA30CC_0_REGS, EVT_QUEUE_NUM);  // Initialization of EDMA3  
    IntRegister(SYS_INT_EDMACOMPINT, EDMA_Completion_Isr);                   // Registering EDMA3 Channel Controller 0 transfer completion interrupt.    
    IntPrioritySet(SYS_INT_EDMACOMPINT, 0, AINTC_HOSTINT_ROUTE_IRQ);        // Setting the priority for EDMA3CC0 completion interrupt in AINTC.    
    IntRegister(SYS_INT_EDMAERRINT, EDMA_CC_error_isr);       // Registering EDMA3 Channel Controller 0 Error Interrupt.    
    IntPrioritySet(SYS_INT_EDMAERRINT, 0, AINTC_HOSTINT_ROUTE_IRQ);     // Setting the priority for EDMA3CC0 Error interrupt in AINTC.    
    IntSystemEnable(SYS_INT_EDMACOMPINT);           // Enabling the EDMA3CC0 completion interrupt in AINTC. 
    IntSystemEnable(SYS_INT_EDMAERRINT);            // Enabling the EDMA3CC0 Error interrupt in AINTC.  

    UARTModuleReset(UART_INSTANCE_BASE_ADD);    // Performing a module reset.

#ifdef UART_ENABLE_FIFO     
    FIFO_configure();    // Performing FIFO configurations.
#else    
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);  // Enabling DMA Mode 1. 
#endif

#if (defined UART_ENABLE_FIFO) && (defined DIRECT_TX_DMA_THRESH_MODE)    
    UARTTxDMAThresholdControl(UART_INSTANCE_BASE_ADD, UART_TX_DMA_THRESHOLD_REG);   // Selecting the method of setting the Transmit DMA Threshold value.    
    UARTTxDMAThresholdValConfig(UART_INSTANCE_BASE_ADD, m_tx_thresh_level); // Configuring the Transmit DMA Threshold value.
#endif
    
    Baud_set();  // Performing Baud Rate settings.    
    UARTRegConfigModeEnable(UART_INSTANCE_BASE_ADD, UART_REG_CONFIG_MODE_B);    // Switching to Configuration Mode B.

    // Programming the Line Characteristics.
    UARTLineCharacConfig(UART_INSTANCE_BASE_ADD,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1), 
                         UART_PARITY_NONE);
    
    UARTDivisorLatchDisable(UART_INSTANCE_BASE_ADD);    // Disabling write access to Divisor Latches.     
    UARTBreakCtl(UART_INSTANCE_BASE_ADD, UART_BREAK_COND_DISABLE);  // Disabling Break Control.    
    UARTOperatingModeSelect(UART_INSTANCE_BASE_ADD, UART16x_OPER_MODE); // Switching to UART16x operating mode.

    /******************** Configuring the EDMA **************************/
    // Request DMA Channel and TCC for UART Transmit
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_TX_CHA_NUM, EDMA3_UART_TX_CHA_NUM,
                        EVT_QUEUE_NUM);

    // Registering Callback Function for TX
    m_cb_Fxn[EDMA3_UART_TX_CHA_NUM] = &RXTX_end_clbck;

    // Request DMA Channel and TCC for UART Receive 
    EDMA3RequestChannel(SOC_EDMA30CC_0_REGS, EDMA3_CHANNEL_TYPE_DMA,
                        EDMA3_UART_RX_CHA_NUM, EDMA3_UART_RX_CHA_NUM,
                        EVT_QUEUE_NUM);

    // Registering Callback Function for RX
    m_cb_Fxn[EDMA3_UART_RX_CHA_NUM] = &RXTX_end_clbck;

}

void  UART_Driver::FIFO_configure(void)
{
    unsigned int fifoConfig = 0;

    /*
    ** Transmitter Trigger Level Granularity is 1.
    ** Receiver Trigger Level Granularity is 1.
    ** Transmit Trigger Space set using 'm_tx_trig_space'.
    ** Receive Trigger level set using 'm_rx_trig_level'.
    ** Clear the Trasnmit FIFO.
    ** Clear the Receive FIFO.
    ** DMA Mode enabling shall happen through SCR register.
    ** DMA Mode 1 is enabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_1,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  m_tx_trig_space,
                                  m_rx_trig_level,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_1_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(UART_INSTANCE_BASE_ADD, fifoConfig);
}

void  UART_Driver::Baud_set(void)
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

void  UART_Driver::TX_EDMA_paRAM_set_config(unsigned char *txBuffer,
                                             unsigned int  length,
                                             unsigned int  tccNum,
                                           unsigned short  linkAddr,
                                             unsigned int  chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    // Fill the PaRAM Set with transfer specific information 
    paramSet.srcAddr = (unsigned int) txBuffer;
    paramSet.destAddr = (unsigned int)UART_THR_RHR_REG;

    paramSet.aCnt = (unsigned short)1;
    paramSet.bCnt = (unsigned short)m_tx_bytes_per_event;
    paramSet.cCnt = (unsigned short)(length / m_tx_bytes_per_event);
    paramSet.srcBIdx = (short)1;
    paramSet.srcCIdx = (short)m_tx_bytes_per_event;

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

void UART_Driver::RX_EDMA_paRAM_set_config(unsigned char *rxBuffer,
                                  unsigned int  length,
                                  unsigned int  tccNum,
                                unsigned short  linkAddr,
                                  unsigned int  chNum)
{
    EDMA3CCPaRAMEntry paramSet;

    // Fill the PaRAM Set with transfer specific information 
    paramSet.srcAddr = (unsigned int)UART_THR_RHR_REG;
    paramSet.destAddr = (unsigned int)rxBuffer;

    paramSet.aCnt = (unsigned short)1;
    paramSet.bCnt = (unsigned short)(m_rx_trig_level);
    paramSet.cCnt = (unsigned short)(length / m_rx_trig_level);
    paramSet.destBIdx = (short)1;
    paramSet.destCIdx = (short)m_rx_trig_level;

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

void UART_Driver::TX_dummy_paRAM_conf_enable(void)
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

void UART_Driver::send(unsigned char * s, size_t len)
{
    unsigned int numByteChunks = 0;
    unsigned char *pBuffer = nullptr;
    unsigned int remainBytes = 0;

    numByteChunks = (len - 1) / m_tx_bytes_per_event;
    remainBytes = (len - 1) % m_tx_bytes_per_event;    
     
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE); // Enabling DMA Mode 1.

    // Configuring EDMA PaRAM sets to transmit  message. 
    TX_EDMA_paRAM_set_config(s,
                             numByteChunks * m_tx_bytes_per_event,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA3CC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    // Configuring the PaRAM set for Dummy Transfer.
    TX_dummy_paRAM_conf_enable();

    // Enable EDMA Transfer
    m_TX_busy = true;
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    // Wait for return from callback 
    while(m_TX_busy);

    // Remaining bytes are transferred through polling method. 
    if(0 != remainBytes)
    {
        pBuffer = s + (len - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    } 
}

void UART_Driver::recieve(size_t len)
{
    // Enabling DMA Mode 1.
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE);

    // Configuring the PaRAM set for reception. */
    RX_EDMA_paRAM_set_config(m_rxBuffer,
                             len,
                             EDMA3_UART_RX_CHA_NUM,
                             0xFFFF,
                             EDMA3_UART_RX_CHA_NUM);

    // Enable EDMA Transfe
    m_TX_busy = true;
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_RX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    // Wait for return from callback 
    while(m_TX_busy);
}

// flush rx buffer to tx
void UART_Driver::flush()
{
    unsigned int numByteChunks = 0;
    unsigned char *pBuffer = nullptr;
    unsigned int remainBytes = 0;

    unsigned int len = 0;
    for(; len < sizeof(m_rxBuffer); len++)
    {
        if(m_rxBuffer[len] == '\0')
        {   
            len++;
            break;
        }
    }

    numByteChunks = (len - 1) / m_tx_bytes_per_event;
    remainBytes = (len - 1) % m_tx_bytes_per_event;    
     
    UARTDMAEnable(UART_INSTANCE_BASE_ADD, UART_DMA_MODE_1_ENABLE); // Enabling DMA Mode 1.

    // Configuring EDMA PaRAM sets to transmit  message. 
    TX_EDMA_paRAM_set_config(m_rxBuffer,
                             numByteChunks * m_tx_bytes_per_event,
                             EDMA3_UART_TX_CHA_NUM,
                             EDMA3CC_OPT(DUMMY_CH_NUM),
                             EDMA3_UART_TX_CHA_NUM);

    // Configuring the PaRAM set for Dummy Transfer.
    TX_dummy_paRAM_conf_enable();

    // Enable EDMA Transfer
    m_TX_busy = true;
    EDMA3EnableTransfer(SOC_EDMA30CC_0_REGS, EDMA3_UART_TX_CHA_NUM,
                        EDMA3_TRIG_MODE_EVENT);

    // Wait for return from callback 
    while(m_TX_busy);

    // Remaining bytes are transferred through polling method. 
    if(0 != remainBytes)
    {
        pBuffer = m_rxBuffer + (len - 1) - remainBytes;
        UARTPuts((char*)pBuffer, remainBytes);
    } 

    memset(m_rxBuffer,'\0', sizeof(m_rxBuffer));
}

// ISR and other callbacks
void  EDMA_Completion_Isr(void)
{
    UART_Driver *s_UART = &UART_0;

    volatile unsigned int pendingIrqs = 0;
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
            
            // calculate event number in EDMA interrupt complition
            if(pendingIrqs)
            {
                do
                {                    
                    pendingIrqs >>= 1u;
                    if(pendingIrqs)
                      ++index;
                }
                while(pendingIrqs);
                
                // tx complition status
                if(index == EDMA3_CHA_UART0_TX)
                    s_UART->m_TX_busy = false;
            }
            
            index = 0;
            pendingIrqs = EDMA3GetIntrStatus(SOC_EDMA30CC_0_REGS);  // Get the Interrupt status.
            
            while(pendingIrqs)
            {
                if((pendingIrqs & 1u) == TRUE)
                {                    
                    EDMA3ClrIntr(SOC_EDMA30CC_0_REGS, index);   // Clear the interrupt status. 

                    (*s_UART->m_cb_Fxn[index])(index);
                }
                ++index;
                pendingIrqs >>= 1u;
            }
            count++;
        }
    }
}

void  RXTX_end_clbck(unsigned int tccNum)
{
    UART_Driver *s_UART = &UART_0;

    UARTDMADisable(UART_INSTANCE_BASE_ADD); // Disabling DMA Mode of operation in UART.     
    EDMA3DisableTransfer(SOC_EDMA30CC_0_REGS, tccNum, EDMA3_TRIG_MODE_EVENT);   // Disabling DMA transfer on the specified channel.

    s_UART->m_TX_busy = false;
}

void  EDMA_CC_error_isr(void)
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
