#include "UART_DT_driver.h"

sw_Timer RX_end_timer(3, os_timer, RX_end_callback);
ring_buffer<n_UART::RX_FIFO_MAX*4> Terminal_buffer; 

// @brief This Callback is called when charater is receive
static char UART_read(void *p_Obj)
{    
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    char result = s_UART.char_get();
    return result;
}

// @brief This Callback is called to write buffer to UART
static int UART_write(void *p_Obj, const char *buffer, size_t len)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
    int index = -1 ;    

    // Send the characters
    for(index = 0; index < len; index++)
    {
        // If the character to the UART is \n, then add a \r before it so that
        // \n is translated to \n\r in the output.
        if(buffer[index] == '\n')
            s_UART.char_put('\r');
        
        s_UART.char_put(buffer[index]); // Send the character to the UART output
    }

    // Return the number of characters written. */
    return (index);
}

// @brief This Callback is called when charater is receive
static char UART_DMA_read(void *p_Obj)
{    
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    char result = s_UART.char_get();
    return result;
}

// @brief This Callback is called to write buffer to UART
#define DUMMY_CH_NUM              (5)
static int UART_DMA_write(void *p_Obj, const char *buffer, size_t len)
{
    static unsigned int num_byte_chunks = 0;

    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    num_byte_chunks = (len - 1) / TX_BYTES_PER_EVENT;
    
    uart_0.DMA_enable(n_UART::SCR_DMA_MODE_1);

    // Configuring EDMA PaRAM sets to transmit data.
    UART_TX_eDMA_paRAM_set((uint8_t *)buffer,
                              num_byte_chunks * TX_BYTES_PER_EVENT,
                              n_EDMA::CH_UART0_TX,
                              DUMMY_CH_NUM,
                              n_EDMA::CH_UART0_TX);
    
    Tx_dummy_paRAM_config_enable();       // Configuring the PaRAM set for Dummy Transfer.    
    
    uart_driver.m_TX_busy = true;
    eDMA.enable_transfer(n_EDMA::CH_UART0_TX, n_EDMA::TRIG_MODE_EVENT);
                        
    // Wait for return from callback
    while(uart_driver.m_TX_busy);
}

// @brief This Callback is called to write buffer to UART
static int UART_write_isr(void *p_Obj, const char *buffer, size_t len)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
    
    s_UART.write(buffer, len);
}

static void  UART_0_irqhandler(void *p_Obj)
{  
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);
  
    // go to interrupt handlers
    s_UART.rx_irq();
    s_UART.tx_irq();
}

// @brief This Callback is called to write buffer to UART
static void EDMA3_completion_isr(void *p_Obj)
{
    AM335x_EDMA &s_EDMA = *reinterpret_cast<AM335x_EDMA *>(p_Obj);
    
    volatile unsigned int pending_IRQs;
    unsigned int index = 1;
    unsigned int count = 0;

    if(s_EDMA.get_intr_status())
    {       
       //Wait for a finite time to monitor the EDMA Completion Interruptstatus.
       while ((count < n_EDMA::COMPL_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0;

            // Get the Interrupt status.
            pending_IRQs = s_EDMA.get_intr_status();
            
            while(pending_IRQs)
            {
                if((pending_IRQs & 1u) == true)
                {
                    // Clear the interrupt status.
                    s_EDMA.clr_intr(index);

                    (*s_EDMA.cb_fx[index])(index);
                }
                
                ++index;
                pending_IRQs >>= 1u;
            }
            count++;
        }
    }    
}

static void EDMA3_error_isr(void *p_Obj)
{
    AM335x_EDMA &s_EDMA = *reinterpret_cast<AM335x_EDMA *>(p_Obj);

    volatile unsigned int pending_IRQs = 0;
    unsigned int evtque_num = 0;
    unsigned int index = 1;
    unsigned int count = 0;

    //if((0 != EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS)) ||
    //   (0 != (EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS))))
    if((0 != s_EDMA.get_ERR_intr_status()) ||
       (0 != s_EDMA.get_CCERR_status()))
    {
        // Loop for EDMA3CC_ERR_HANDLER_RETRY_COUNT number of time, breaks
        // when no pending interrupt is found 
        while ((count < n_EDMA::ERR_HANDLER_RETRY_COUNT) && (index != 0u))
        {
            index = 0u;
            //pending_IRQs = EDMA3GetErrIntrStatus(SOC_EDMA30CC_0_REGS);
            pending_IRQs = s_EDMA.get_ERR_intr_status();

            while (pending_IRQs)
            {
                // Process all the pending interrupts
                if((pending_IRQs & 1u) == true)
                {
                    // Writing to EMCR to clear the corresponding EMR bits.
                    // Also clearing any Secondary events in SER.
                    //EDMA3ClrMissEvt(SOC_EDMA30CC_0_REGS, index);
                    s_EDMA.clr_miss_evt(index);
                }
                ++index;
                pending_IRQs >>= 1u;
            }
            index = 0u;

            //pending_IRQs = EDMA3GetCCErrStatus(SOC_EDMA30CC_0_REGS);
            pending_IRQs = s_EDMA.get_CCERR_status();
            
            if (pending_IRQs != 0u)
            {
                // Process all the pending CC error interrupts.
                // Queue threshold error for different event queues.
                for (evtque_num = 0u; evtque_num < n_EDMA::EVTQUE_AVAIL; evtque_num++)
                {
                    if((pending_IRQs & (1u << evtque_num)) != 0u)
                    {
                        // Clear the error interrupt.
                        //EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS, (1u << evtqueNum));
                       s_EDMA.clr_CCERR(1u << evtque_num);
                    }
                }

                // Transfer completion code error.
                if ((pending_IRQs & (1 << n_EDMA::F_TCCERR)) != 0u)
                {
                    //EDMA3ClrCCErr(SOC_EDMA30CC_0_REGS, (0x01u << EDMA3CC_CCERR_TCCERR_SHIFT));
                    s_EDMA.clr_CCERR(0x01u << n_EDMA::F_TCCERR);
                }
                ++index;
            }

            count++;
        }

        // Enable error to be evaluated again
        //EDMA3CCErrorEvaluate(SOC_EDMA30CC_0_REGS);
        s_EDMA.CCERR_evaluate();
    }   
}

// callback for end of dma transfer
static void RXTX_end_callback(uint32_t tcc_num)
{
    // Disabling DMA Mode of operation in UART.
    uart_0.DMA_disable();

    // Disabling DMA transfer on the specified channel.
    eDMA.disable_transfer(tcc_num, n_EDMA::TRIG_MODE_EVENT);

    uart_driver.m_TX_busy = 0;
}

    
static int console_pollrx(void *p_Obj)
{
    AM335x_UART &s_UART = *reinterpret_cast<AM335x_UART *>(p_Obj);

    int ret = -1;
    
    /* как можно быстрее переводим данные в буфер долгого хранения*/
    s_UART.is_RX_data_rdy(&Terminal_buffer);
    
    if(Terminal_buffer.get_avail() > 0)
    {
        ret = (int)Terminal_buffer.get_one();
    }
    
    return ret;
}

// @brief  UART device opertaion functions callbacks
// @detail
UART_client_ops UART_ops;

// @brief  device tree property
// @details
const DT_device_id_t  AM335x_UART_ids =
{
   .compatible = "AM335x_UART",
};

int  UART_DT_Driver::probe(void *p_owner)
{   
    UART_ops.write = UART_DMA_write;
    UART_ops.read = UART_read;
    UART_ops.isr = nullptr;
    UART_ops.pollrx = nullptr;
    set_Client_ops(p_owner,dynamic_cast<Client_ops*>(&UART_ops));
    
    return 0;
}

void UART_DT_Driver::set_Client_ops(void *p_owner, Client_ops *p_ops)
{
    Device_driver::m_Owner = p_owner;
    Device_driver::mp_Ops  = p_ops;
    
    UART_client_ops *p_client = static_cast<UART_client_ops *>(Device_driver::m_Owner);  //static because p_owner is (void *)
    std::string compat(m_Of_match_table->compatible);
    
    if(p_client->compatible.compare(compat) == 0)
    {  
        UART_client_ops *input_ops = dynamic_cast<UART_client_ops*>(mp_Ops);
        
        p_client->write = input_ops->write;
        p_client->read = input_ops->read;
        p_client->p_UART_instance = input_ops->p_UART_instance;
        p_client->pollrx = input_ops->pollrx;
        p_client->p_UART_instance = get_instance(); 
    } 
}
 
/*
int  UART_DT_Driver::init(void)
{     
    m_int_controller.master_IRQ_disable();   // Disable IRQ in CPSR   
    
    /// Initialize the UART console ///
    m_prcm_module.run_EDMA_clk((void *)&m_EDMA);  
    m_prcm_module.run_clk_UART0();              // Configuring the system clocks for UART0 instance.
    m_pinmux_ctrl.UART0_pin_mux_setup();        // Performing the Pin Multiplexing for UART0 instance. 
    
    m_int_controller.master_IRQ_enable();       // Enable IRQ in CPSR    
         
    m_EDMA.init(n_EDMA::EVENT_Q0);
    EDMA_INTC_configure();
    
    m_UART_device.module_reset();                                   // Performing a module reset.        
    m_UART_device.FIFO_configure_no_DMA(1, 1);                      // Performing FIFO configurations.
       
    m_UART_device.TX_DMA_threshold_control(true);
    m_UART_device.TX_DMA_threshold_val_config(TX_DMA_THRESHOLD);
    
    m_UART_device.BAUD_set(115200);                                // Performing Baud Rate settings.
    m_UART_device.reg_config_mode_enable(n_UART::CONFIG_MODE_B);   // Switching to Configuration Mode B. 
    
    // Programming the Line Characteristics. 
    m_UART_device.char_len_config(n_UART::CHL_8_BITS);
    m_UART_device.stop_bit_config(n_UART::STOP_1);
    m_UART_device.parity_config(n_UART::PARITY_NONE);
             
    m_UART_device.divisor_latch_disable();                         // Disabling write access to Divisor Latches.        
    m_UART_device.break_ctl(false);                                // Disabling Break Control.
    m_UART_device.operating_mode_select(n_UART::MODE_UART_16x);    // Switching to UART16x operating mode.     

    ///Configuring the EDMA.///
    m_EDMA.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_TX, n_EDMA::CH_UART0_TX, n_EDMA::EVENT_Q0);   // Registering Callback Function for TX    
    cb_fx[n_EDMA::CH_UART0_TX] = &EDMA3_end_transaction_clb;            // Registering Callback Function for TX
    m_EDMA.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_RX, n_EDMA::CH_UART0_RX, n_EDMA::EVENT_Q0);   // Registering Callback Function for RX     
    cb_fx[n_EDMA::CH_UART0_RX] = &EDMA3_end_transaction_clb;            // Registering Callback Function for RX
    
    return 0;
}
*/

#define UART_ENABLE_FIFO            // Enable FIFO mode of operation.
#define DIRECT_TX_DMA_THRESH_MODE   // Use this macro if TX_DMA_THRESHOLD register is used to configure TX
                                    // Threshold value.
#define TX_DMA_THRESHOLD          (5)


#define TX_TRIGGER_SPACE_GRAN_1   (8)

// Number of bytes transmitted by EDMA per TX event sent by UART.
#ifdef UART_ENABLE_FIFO
    #define TX_BYTES_PER_EVENT        (8)
#else
    #define TX_BYTES_PER_EVENT        (1)
#endif

#ifdef UART_ENABLE_FIFO
    #define RX_DMA_THRESHOLD          (8)
#else
    #define RX_DMA_THRESHOLD          (1)
#endif

int  UART_DT_Driver::init(void)
{   
    m_TX_busy = false;
    
    m_prcm_module.run_EDMA_clk((void *)&eDMA);
    m_prcm_module.run_clk_UART0();
    m_pinmux_ctrl.UART0_pin_mux_setup();

    m_int_controller.master_IRQ_enable();      // Enable IRQ in CPSR
    m_int_controller.init();                   // Initializing the ARM Interrupt Controller.
    eDMA.init(n_EDMA::EVENT_Q0);

    EDMA_INTC_configure();
    
    m_UART_device.module_reset();                                   // Performing a module reset. 

#ifdef UART_ENABLE_FIFO    
    m_UART_device.FIFO_configure_DMA_RxTx(TX_TRIGGER_SPACE_GRAN_1, RX_DMA_THRESHOLD);  // 8, 8
#else    
    m_UART_device.DMA_enable(n_UART::SCR_DMA_MODE_1);
#endif
       
#if (defined UART_ENABLE_FIFO) && (defined DIRECT_TX_DMA_THRESH_MODE)
    m_UART_device.TX_DMA_threshold_control(true);     
    m_UART_device.TX_DMA_threshold_val_config(TX_DMA_THRESHOLD);
#endif
   
    m_UART_device.BAUD_set(115200);                                // Performing Baud Rate settings.
    m_UART_device.reg_config_mode_enable(n_UART::CONFIG_MODE_B);   // Switching to Configuration Mode B. 
    
    // Programming the Line Characteristics. 
    m_UART_device.char_len_config(n_UART::CHL_8_BITS);
    m_UART_device.stop_bit_config(n_UART::STOP_1);
    m_UART_device.parity_config(n_UART::PARITY_NONE);
             
    m_UART_device.divisor_latch_disable();                         // Disabling write access to Divisor Latches.        
    m_UART_device.break_ctl(false);                                // Disabling Break Control.
    m_UART_device.operating_mode_select(n_UART::MODE_UART_16x);    // Switching to UART16x operating mode.     

    // Configuring the EDMA.
    // Request DMA Channel and TCC for UART Transmit
    m_EDMA.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_TX, n_EDMA::CH_UART0_TX, n_EDMA::EVENT_Q0);    
    m_EDMA.cb_fx[n_EDMA::CH_UART0_TX] = &RXTX_end_callback; // Registering Callback Function for TX

    // Request DMA Channel and TCC for UART Receive   
    m_EDMA.request_channel(n_EDMA::CHANNEL_TYPE_DMA, n_EDMA::CH_UART0_RX, n_EDMA::CH_UART0_RX, n_EDMA::EVENT_Q0);
    m_EDMA.cb_fx[n_EDMA::CH_UART0_RX] = &RXTX_end_callback;  // Registering Callback Function for RX
    
    return 0;
}

 
void  UART_DT_Driver::sync_state(void* dev)
{
  
}
 
int  UART_DT_Driver::remove(void* dev)
{
    return 0;
}
 
void  UART_DT_Driver::shutdown(void* dev)
{
}
 
int  UART_DT_Driver::suspend(void* dev)
{
    return 0;
}
 
int  UART_DT_Driver::resume(void* dev)
{
    return 0;
}

int  UART_DT_Driver::exit(void)
{
    return 0;
}

void  UART_DT_Driver::AINTC_configure(void)
{
    m_int_controller.register_handler(m_UART_sys_interrupt, UART_ops.isr);             // Registering I2C_irqhandler         
    m_int_controller.priority_set(m_UART_sys_interrupt,5, INTC::HOSTINT_ROUTE_IRQ);    // Set the highest priority
    sys_interrupt_enable();
}

void  UART_DT_Driver::EDMA_INTC_configure(void)
{      
    //IntAINTCInit();                                                     // Initializing the ARM Interrupt Controller.   
    //IntRegister(SYS_INT_EDMACOMPINT, Edma3CompletionIsr);               // Registering EDMA3 Channel Controller 0 transfer completion interrupt.    
    //IntPrioritySet(SYS_INT_EDMACOMPINT, 0, AINTC_HOSTINT_ROUTE_IRQ);    // Setting the priority for EDMA3CC0 completion interrupt in AINTC.    
    //IntRegister(SYS_INT_EDMAERRINT, Edma3CCErrorIsr);                   // Registering EDMA3 Channel Controller 0 Error Interrupt.    
    //IntPrioritySet(SYS_INT_EDMAERRINT, 0, AINTC_HOSTINT_ROUTE_IRQ);     // Setting the priority for EDMA3CC0 Error interrupt in AINTC.    
    //IntSystemEnable(SYS_INT_EDMACOMPINT);                               // Enabling the EDMA3CC0 completion interrupt in AINTC.    
    //IntSystemEnable(SYS_INT_EDMAERRINT);                                // Enabling the EDMA3CC0 Error interrupt in AINTC.
  
    m_int_controller.register_handler(INTC::EDMACOMPINT, EDMA3_completion_isr);     // Registering EDMA3 Channel Controller 0 transfer completion interrupt.    
    m_int_controller.priority_set(INTC::EDMACOMPINT, 0, INTC::HOSTINT_ROUTE_IRQ);   // Setting the priority for EDMA3CC0 completion interrupt in AINTC.    
    m_int_controller.register_handler(INTC::EDMAERRINT, EDMA3_error_isr);           // Registering EDMA3 Channel Controller 0 Error Interrupt.    
    m_int_controller.priority_set(INTC::EDMAERRINT, 0, INTC::HOSTINT_ROUTE_IRQ);    // Setting the priority for EDMA3CC0 Error interrupt in AINTC.    
    m_int_controller.system_enable(INTC::EDMACOMPINT);                              // Enabling the EDMA3CC0 completion interrupt in AINTC.    
    m_int_controller.system_enable(INTC::EDMAERRINT);                               // Enabling the EDMA3CC0 Error interrupt in AINTC.
}

/*
** This function configures and sets the EDMA PaRAM set values for
** transferring data to UART TX FIFO.
*/
void UART_TX_eDMA_paRAM_set(uint8_t *tx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num)
{
    n_EDMA::paRAM_entry_t param_set;

    /// Fill the PaRAM Set with transfer specific information ///
    param_set.SRC = (uint32_t)tx_buffer;
    param_set.DST = n_UART::AM335x_UART_0_BASE;

    param_set.ACNT = (uint16_t)1;
    param_set.BCNT = (uint16_t)TX_BYTES_PER_EVENT;
    param_set.CCNT = (uint16_t)(len / TX_BYTES_PER_EVENT);
    param_set.SRCBIDX = (int16_t)1;
    param_set.SRCCIDX = (int16_t)TX_BYTES_PER_EVENT;

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
    
    eDMA.set_paRAM(ch_num, &param_set);  //Now write the PaRAM set
}

void UART_RX_eDMA_paRAM_set(uint8_t *rx_buffer, size_t len, uint32_t tcc_num, uint16_t param_num, uint32_t ch_num)
{
    n_EDMA::paRAM_entry_t param_set;

    /// Fill the PaRAM Set with transfer specific information ///
    param_set.SRC = (uint32_t)n_UART::AM335x_UART_0_BASE;
    param_set.DST = (uint32_t)rx_buffer;

    param_set.ACNT = (uint16_t)1;
    param_set.BCNT = (uint16_t)(RX_TRIG_LEVEL);
    param_set.CCNT = (uint16_t)(len / RX_TRIG_LEVEL);
    param_set.DSTBIDX = (int16_t)1;
    param_set.DSTCIDX = (int16_t)RX_TRIG_LEVEL;

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
    
    eDMA.set_paRAM(ch_num, &param_set);  //Now write the PaRAM set
}


//This configures the PaRAM set for the Dummy Transfer.
void Tx_dummy_paRAM_config_enable(void)
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

    eDMA.set_paRAM(DUMMY_CH_NUM, &dummy_param_set);
}

UART_DT_Driver uart_driver(uart_0);
