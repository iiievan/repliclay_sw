#include "include.h"
#include "NRF_serial.h"

swTimer RX_end_timer(3, sys_tmr, RX_end_callback);

x_NRF_serial::x_NRF_serial(NRF_UARTE_Type *sUART)
: m_sUART(*sUART),
s_RX_end_timer(RX_end_timer) 
{
    m_TX_busy         =  false;
    m_RX_sts          =  RX_IDLE;
        
    m_RX_data.reset();
    m_TX_data.reset();
 }

void x_NRF_serial::init(uint32_t rx_pin, uint32_t tx_pin, uint32_t baudrate)
{    
    m_sUART.CONFIG  = 0;
    m_sUART.CONFIG  = (UARTE_CONFIG_HWFC_Disabled << UARTE_CONFIG_HWFC_Pos);

    m_RX_pin = rx_pin;
    m_TX_pin = tx_pin;

    nrf_gpio_pin_set(m_TX_pin);
    nrf_gpio_cfg_output(m_TX_pin);  //  for NRF this is TX 
    m_sUART.PSEL.TXD = m_TX_pin;   
    
    nrf_gpio_cfg_input(m_RX_pin, NRF_GPIO_PIN_NOPULL);   // For RF this is RX
    m_sUART.PSEL.RXD = m_RX_pin;
  
    m_sUART.PSEL.RTS = PIN_DISCONNECTED;
    m_sUART.PSEL.CTS = PIN_DISCONNECTED;
    
    switch (baudrate) 
    {
        case 1200:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud1200;
            break;
        case 2400:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud2400;
            break;
        case 4800:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud4800;
            break;
        case 9600:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud9600;
            break;
        case 14400:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud14400;
            break;
        case 19200:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud19200;
            break;
        case 28800:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud28800;
            break;
        case 38400:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud38400;
            break;
        case 57600:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud57600;
            break;
        case 76800:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud76800;
            break;
        case 115200:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud115200;
            break;
        case 230400:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud230400;
            break;
        case 250000:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud250000;
            break;
        case 460800:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud460800;
            break;
        case 921600:
            m_sUART.BAUDRATE = UART_BAUDRATE_BAUDRATE_Baud921600;
            break;
        default:
            return;
    }
    
    m_sUART.ENABLE = UARTE_ENABLE_ENABLE_Enabled;
    
    m_sUART.EVENTS_ENDTX  = 0;
    m_sUART.TASKS_STARTTX = 0;
    
    m_sUART.INTENCLR      = 0xFFFFFFFF;
    
    m_sUART.INTENSET      = (UARTE_INTENSET_RXDRDY_Enabled << UARTE_INTENSET_RXDRDY_Pos) |
                            (UARTE_INTENSET_ENDRX_Enabled  << UARTE_INTENSET_ENDRX_Pos) |
                            (UARTE_INTENSET_ENDTX_Enabled  << UARTE_INTENSET_ENDTX_Pos);
    
    m_sUART.ERRORSRC = BIT(2) | BIT(3);
    m_sUART.EVENTS_RXDRDY = 0;
    m_sUART.EVENTS_RXSTARTED = 0;
   
    m_Start_RX(RX_CHUNK_SIZE);
              
    NVIC_SetPriority(UARTE0_UART0_IRQn, UART0_INT_PRIORITY);
    NVIC_ClearPendingIRQ(UARTE0_UART0_IRQn);
    NVIC_EnableIRQ(UARTE0_UART0_IRQn); 
}

void x_NRF_serial::deinit(void)
{                                            
     m_sUART.INTEN = (UARTE_INTEN_RXDRDY_Disabled << UARTE_INTEN_RXDRDY_Pos) | 
                     (UARTE_INTEN_TXDRDY_Disabled << UARTE_INTEN_RXDRDY_Pos) | 
                     (UARTE_INTEN_CTS_Disabled   << UARTE_INTEN_CTS_Pos) | 
                     (UARTE_INTEN_ENDRX_Disabled  << UARTE_INTEN_ENDRX_Pos);
    
    m_sUART.INTENCLR   = 0xFFFFFFFF;
    
    m_sUART.SHORTS = UARTE_SHORTS_ENDRX_STARTRX_Disabled;
    m_sUART.TASKS_STOPRX = 1UL;
    m_sUART.EVENTS_TXSTOPPED = 0UL;
    m_sUART.TASKS_STOPTX = 1UL;

    while (! m_sUART.EVENTS_TXSTOPPED);
    
    m_sUART.PSEL.TXD = PIN_DISCONNECTED;
    m_sUART.PSEL.RXD = PIN_DISCONNECTED;
  
    NVIC_DisableIRQ(UARTE0_UART0_IRQn);

    m_sUART.ENABLE = UARTE_ENABLE_ENABLE_Disabled;
}

uint32_t x_NRF_serial::available(void)
{
    return m_RX_data.get_avail();
}

void x_NRF_serial::read(char* data)
{
    uint32_t avail = m_RX_data.get_avail();
          
    if(avail >= RX_CHUNK_SIZE)
    {
        memcpy(data, m_RX_data.get_complete_buf(), m_RX_data.get_one_size());
        m_RX_data.decrement(RX_CHUNK_SIZE);
        avail = m_RX_data.get_avail();
        memcpy(&data[RX_CHUNK_SIZE], m_RX_data.get_empty_buf(), avail);
        m_RX_data.decrement(avail);
    }
    else
    {
        memcpy(data, m_RX_data.get_complete_buf(), avail);
        m_RX_data.decrement(avail);
    } 
    
    m_RX_sts = RX_IN_PROGESS;
}

void x_NRF_serial::read(ring_buffer<RX_CHUNK_SIZE*4>* p_Data)
{
    uint32_t avail = m_RX_data.get_avail();
    char* p_BUF = m_RX_data.get_complete_buf();
    uint32_t i = 0;
    
    if(avail >= RX_CHUNK_SIZE)
    {
        for(; i < RX_CHUNK_SIZE; i++)
        {
            p_Data->push(p_BUF[i]);
        }
        
        m_RX_data.decrement(RX_CHUNK_SIZE);
    }
    else
    {
        for(; i < avail; i++)
        {
            p_Data->push(p_BUF[i]);
        }
        
        m_RX_data.decrement(avail);
    } 
}


bool  x_NRF_serial::is_RX_data_rdy(ring_buffer<RX_CHUNK_SIZE*4>* p_Data)
{ 
    bool result = false;
    
    RX_end_timer.on_delay((void *)this);

    if(m_RX_sts == RX_CHUNK_RECEIVED)
    {  
        read(p_Data);
        m_RX_sts = RX_IN_PROGESS;
    }

    //-----|
    //     |----- - transition mean that RX end with timeout.
    if(m_RX_sts == RX_TOUT_IS_OUT)
    {        
        read(p_Data);
        m_RX_data.reset();
        m_Start_RX(RX_CHUNK_SIZE);
        m_RX_sts = RX_STOPPED;
        result = true;
    }
        
    return result;  
}

void x_NRF_serial::write(char c)
{
    write(&c,1);
}

void x_NRF_serial::write(const char *data, size_t len)
{
    auto already_sent = 0;
    auto left_to_send = 0;
    
    while(m_RX_data.get_avail()); 
    
    do
    {
        left_to_send = len - already_sent;
        left_to_send = (left_to_send > TX_CHUNK_SIZE) ? TX_CHUNK_SIZE : left_to_send;

        __disable_interrupt();

        memcpy(m_TX_data.get_empty_buf(), data + already_sent, left_to_send);
        m_TX_busy = true;
        m_Start_TX(left_to_send);
        
        __enable_interrupt();

        while(m_TX_busy);

        already_sent += left_to_send;
    }
    while (already_sent < len);
}

void  x_NRF_serial::write(const char *str) 
{
    if (str == NULL) 
    return;

    volatile uint32_t len = strlen(str);

    write(str, len);
}

void x_NRF_serial::m_Start_TX(size_t amount)
{
    m_sUART.TXD.PTR    = (uint32_t)m_TX_data.switch_frames();
    m_sUART.TXD.MAXCNT = amount;
    
    /* start transmit*/
    m_sUART.EVENTS_ENDTX = 0;
    m_sUART.TASKS_STARTTX = 1;
}

void x_NRF_serial::m_Start_RX(size_t amount)
{
    m_RX_data.switch_frames();
    
    m_sUART.RXD.MAXCNT = amount;
    m_sUART.RXD.PTR    = (uint32_t)m_RX_data.get_empty_buf();
    
    /* start receive */
    m_sUART.TASKS_STARTRX = 1;
    while( m_sUART.EVENTS_RXSTARTED == 0);
}

void x_NRF_serial::rx_irq(void)
{
    if (m_sUART.EVENTS_RXDRDY)
    {
        m_sUART.EVENTS_RXDRDY = 0;        
        m_RX_data.increment();
        
        if(m_RX_sts != RX_CHUNK_RECEIVED &&
           m_RX_sts != RX_IN_PROGESS)
            m_RX_sts = RX_IN_PROGESS;
        
        if(RX_end_timer.is_working())
            RX_end_timer.update();            
        else
            RX_end_timer.start();  
    }
            
    if (m_sUART.EVENTS_ENDRX)
    { 
        m_sUART.EVENTS_ENDRX  = 0;        
        m_Start_RX(RX_CHUNK_SIZE); 
        m_RX_sts = RX_CHUNK_RECEIVED;
    }
}

void RX_end_callback(void * p_Obj)
{
    x_NRF_serial * p_Serial = (x_NRF_serial *) p_Obj;
    
    p_Serial->m_RX_data.switch_frames();
    p_Serial->m_RX_sts = RX_TOUT_IS_OUT;
}

void x_NRF_serial::tx_irq(void)
{    
    if (m_sUART.EVENTS_ENDTX)
    { 
        m_sUART.EVENTS_ENDTX = 0;
        m_TX_busy = false; 
    }  
}

x_NRF_serial dbg_serial(NRF_UARTE0);

void UARTE0_UART0_IRQHandler()
{      
    dbg_serial.rx_irq();
    dbg_serial.tx_irq();  
}