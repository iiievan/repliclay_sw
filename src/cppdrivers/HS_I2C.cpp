#include "HS_I2C.h"

HS_I2C::HS_I2C(I2C::AM335x_I2C_Type *p_i2c_regs)
:m_I2C_regs(*p_i2c_regs)
{
 
}

/**
 * \brief   Enables the I2C module.This will bring the I2C module out of reset.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
void  HS_I2C::master_enable()
{
    /** Bring the I2C module out of reset **/
    m_I2C_regs.I2C_CON.b.I2C_EN = HIGH;
}

/**
 * \brief   Disables the I2C Module.This will put the I2C module in reset.
 *          Only Tx and Rx are cleared,status bits are set their default
 *          values and all configuration registers are not reset,they keep
 *          their initial values.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  None.
 *
 **/
void  HS_I2C::master_disable()
{
    /** Put I2C module in reset **/
    m_I2C_regs.I2C_CON.b.I2C_EN = LOW;
}

/**
 * \brief   This API enables autoidle mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void  HS_I2C::auto_idle_enable()
{
    m_I2C_regs.I2C_SYSC.b.AUTOIDLE = HIGH;
}

/**
 * \brief   This API disables autoidle mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void  HS_I2C::auto_idle_disable()
{
    m_I2C_regs.I2C_SYSC.b.AUTOIDLE = LOW;
}

/**
 * \brief   This API will divide the system clock fed to I2C module between
 *          12 and 100Mhz.It will also configure the I2C bus clock frequency.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 * \param   sysClk      It is the System clock fed to I2C module.
 * \param   internalClk It is the internal clock used by I2C module.Which is
 *                      obtained by scaling System clock fed to I2C module.
 * \param   outputClk   It is the required I2C bus speed or frequency.
 *
 * \return  None.
 **/ 
void  HS_I2C::master_init_exp_clk(uint32_t sys_clk, uint32_t internal_clk, uint32_t output_clk)
{
    uint32_t prescaler;
    uint32_t divider;

    // Calculate and set prescaler value
    prescaler = (uint8_t)(sys_clk / internal_clk) - 1;
    m_I2C_regs.I2C_PSC.b.PSC = (uint8_t)prescaler;
    
    divider = internal_clk/output_clk;
    divider = divider / 2;

    m_I2C_regs.I2C_SCLL.b.SCLL = (uint8_t)(divider - 7);
    m_I2C_regs.I2C_SCLH.b.SCLH = (uint8_t)(divider - 5);
}

/**
 * \brief   This API sets the address of the slave device with which I2C wants to
 *          communicate.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   slaveAddr  slave address.
 *
 * \return None.
 **/
void  HS_I2C::master_slave_addr_set(uint16_t slave_add)
{
    m_I2C_regs.I2C_SA.b.SA = slave_add;
}

/**
* return number of I2C block in direct memory
**/
I2C::e_I2C_SER_NUM  HS_I2C::get_I2C_ser_number()
{
    uint32_t i2c_num = (uint32_t)&m_I2C_regs;
     
    switch(i2c_num)
    {
        case I2C::AM335x_I2C_0_BASE:     
            return I2C::I2C_NUM_0;
        case I2C::AM335x_I2C_1_BASE:     
            return I2C::I2C_NUM_1;
        case I2C::AM335x_I2C_2_BASE:
            return I2C::I2C_NUM_2;
        default:
            break;
    } 
    
    return I2C::I2C_NUM_NA;  
}

/**
* return interrupt number of I2C for INTC setup
**/
INTC::e_SYS_INTERRUPT  HS_I2C::get_I2C_sys_interrupt()
{  
    uint32_t i2c_num = (uint32_t)&m_I2C_regs;
     
    switch(i2c_num)
    {
        case I2C::AM335x_I2C_0_BASE:     
            return INTC::I2C0INT;
        case I2C::AM335x_I2C_1_BASE:     
            return INTC::I2C1INT;
        case I2C::AM335x_I2C_2_BASE:
            return INTC::I2C2INT;
        default:
            break;
    } 
    
    return INTC::INTERRUPTS_NUM_MAX; 
}

/**
 * \brief   This API configure I2C in different modes of operation.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   cmd       It is the value which configures I2C in different mode's
 *                    of operation.\n
 * 
 *          cmd can take follwing macros.\n
 *
 *          I2C_CFG_MST_TX             - Configure's I2C as Master-Transmitter.\n
 *          I2C_CFG_MST_RX             - Configure's I2C as Master-Receiver.\n
 *          I2C_CFG_STOP               - Configure's I2C to generate stop 
 *                                       condition when DCOUNT counts down to
 *                                       zero.\n
 *          I2C_CFG_N0RMAL_MODE        - Configure's I2C in normal mode.\n
 *          I2C_CFG_SRT_BYTE_MODE      - Configure's I2C in start byte mode.\n
 *          I2C_CFG_7BIT_SLAVE_ADDR    - Configure's I2C to address seven bit
 *                                       addressed slave.\n
 *          I2C_CFG_10BIT_SLAVE_ADDR   - Configure's I2C to address ten bit
 *                                       addressed slave.\n 
 *          I2C_CFG_10BIT_OWN_ADDR_0   - Enable 10bit addressing mode for own
 *                                       address 0.\n
 *          I2C_CFG_10BIT_OWN_ADDR_1   - Enable 10bit addressing mode for own
 *                                       address 1.\n
 *          I2C_CFG_10BIT_OWN_ADDR_2   - Enable 10bit addressing mode for own
 *                                       address 2.\n
 *          I2C_CFG_10BIT_OWN_ADDR_3   - Enable 10bit addressing mode for own
 *                                       address 3.\n
 *          I2C_CFG_7BIT_OWN_ADDR_0   -  Enable 7bit addressing mode for own
 *                                       address 0.\n
 *          I2C_CFG_7BIT_OWN_ADDR_1   -  Enable 7bit addressing mode for own
 *                                       address 1 .\n
 *          I2C_CFG_7BIT_OWN_ADDR_2   -  Enable 7bit addressing mode for own
 *                                       address 2.\n
 *          I2C_CFG_7BIT_OWN_ADDR_3   -  Enable 7bit addressing mode for own
 *                                       address 3.\n
 * \return None.
 *
 **/
void  HS_I2C::master_control(uint32_t cmd) // see I2C::e_CON_flags
{  
    m_I2C_regs.I2C_CON.reg = (uint32_t)(cmd | I2C::F_CON_I2C_EN);
}

/**
 * \brief   This API configure I2C data count register with a value. 
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   count    It is value which is set to I2C data count register.
 *
 * \return None.
 **/
void  HS_I2C::set_data_count(uint16_t count)
{
    m_I2C_regs.I2C_CNT.b.DCOUNT = count;
}

/**
 * \brief   This API configure I2C data count register with a value. 
 *          The value in the I2C data count register indicate how many data
 *          words to transfer when the I2C is configured as a  master-transmitter
 *          and repeat mode is off.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return  number of bytes transfered over the I2C bus.
 **/
uint16_t  HS_I2C::data_count_get()
{
    return m_I2C_regs.I2C_CNT.b.DCOUNT;
}

/**
 * \brief  This function Transmits a byte from the I2C in Master mode.
 * 
 * \param  baseAdd is the Memory address of the I2C instance used.
 * \param  data data to be transmitted from the I2C Master.
 * 
 * \return None.\n
 *
 **/
void  HS_I2C::master_data_put(uint8_t data)
{
    m_I2C_regs.I2C_DATA.reg = data;
}

/**
 *  \brief  This Receives a byte that has been sent to the I2C in Master mode.
 * 
 *  \param  baseAdd is the Memory address of the I2C instance used.
 * 
 *  \return Returns the byte received from by the I2C in Master mode.
 *
 **/
uint8_t  HS_I2C::master_data_get()
{ 
    uint8_t data;
    
    data = (uint8_t)m_I2C_regs.I2C_DATA.b.DATA;
    
    return data;
}

/**
 * \brief   This API determines whether bus is busy or not.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  returns 1 if bus is busy.
 *          returns 0 if bus is free.
 *
 **/
bool  HS_I2C::master_bus_busy()
{    
    if (m_I2C_regs.I2C_IRQSTATUS_RAW.b.BB)
        return true;    
    else
        return false;
}

/**
 * \brief   This API determines nack status.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  returns 1 if nack detetcted.
 *          returns 0 if nack event not found.
 *
 **/
bool  HS_I2C::master_nack_status()
{ 
    if (m_I2C_regs.I2C_IRQSTATUS_RAW.b.NACK)
        return true;    
    else
        return false;
}

/**
 * \brief  This API returns the raw status of interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns Raw status of interrupts.
 **/
uint32_t  HS_I2C::master_int_raw_status()
{
    return m_I2C_regs.I2C_IRQSTATUS_RAW.reg;
}

/**
 * \brief  This API stops a I2C transaction on the bus.
 *         This API must be used in case a deliberate STOP needs to be sent
 *         on the bus.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void  HS_I2C::master_stop()
{
    m_I2C_regs.I2C_CON.b.STP = HIGH;
}

/**
 * \brief   This API start's a I2C transaction on the bus. This API must
 *          be called after all the configuration for the i2c module is 
 *          done and after bringing I2C out of local reset
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void  HS_I2C::master_start()
{
    m_I2C_regs.I2C_CON.b.STT = HIGH ;
}

/**
 * \brief  This API enables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be enabled.\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \return None.
 **/
void  HS_I2C::master_int_enable_ex(uint32_t int_flag) // see e_IRQENABLE_flags
{
    m_I2C_regs.I2C_IRQENABLE_SET.reg = int_flag;
}

/**
 * \brief  This API Clears the status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be cleared\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \returns None
 **/
void  HS_I2C::master_int_clear_ex(uint32_t int_flag) // see e_IRQSTATUS_flags
{
    m_I2C_regs.I2C_IRQSTATUS.reg = int_flag;
}

/**
 * \brief  This API disables only specified I2C interrupts in master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag   It specifies the interrupts that are rquired to be disabled\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n   
 *
 * \return None.
 **/
void  HS_I2C::master_int_disable_ex(uint32_t int_flag) // see e_IRQENABLE_flags
{
    m_I2C_regs.I2C_IRQENABLE_CLR.reg = int_flag;
}

/**
 * \brief   This API reset the entire I2C module.On reset,are set to power
 *          up reset values.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void  HS_I2C::soft_reset()
{
    //HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_SRST;
    m_I2C_regs.I2C_SYSC.b.SRST = HIGH;
}

/**
 * \brief   This API Enables generation of Transmit Event,when
 *          I2C_DATA register is empty.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void  HS_I2C::DMATx_event_enable()
{
    /*HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_XDMA_EN);
    HWREG(baseAdd + I2C_DMATXENABLE_SET) = (I2C_DMATXENABLE_SET_DMATX_ENABLE_SET);*/
  
    m_I2C_regs.I2C_BUF.b.XDMA_EN = HIGH;    
    m_I2C_regs.I2C_DMATXENABLE_SET.b.DMATX_TRANSMIT_SET = HIGH;
}

/**
 * \brief   This API Enables generation of Receive DMA Event,when
 *          I2C_DATA register is full.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void  HS_I2C::DMARx_event_enable()
{
    /*HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_RDMA_EN);
    HWREG(baseAdd + I2C_DMARXENABLE_SET) = (I2C_DMARXENABLE_SET_DMARX_ENABLE_SET);*/
  
    m_I2C_regs.I2C_BUF.b.RDMA_EN = HIGH;    
    m_I2C_regs.I2C_DMARXENABLE_SET.b.DMARX_ENABLE_SET = HIGH;
}

/**
 * \brief   This API Disables Transmit event.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 *
 * \return None.
 **/
void  HS_I2C::DMATx_event_disable()
{
    /*HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_XDMA_EN);
    HWREG(baseAdd + I2C_DMATXENABLE_CLR) = (I2C_DMATXENABLE_CLR_DMATX_ENABLE_CLEAR);*/
  
    m_I2C_regs.I2C_BUF.b.XDMA_EN = LOW;    
    m_I2C_regs.I2C_DMATXENABLE_CLR.b.DMATX_ENABLE_CLEAR = HIGH;
  
}

/**
 * \brief   This API Disables Receive event.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 *
 * \return None.
 **/
void  HS_I2C::DMARx_event_disable()
{
    /*HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_RDMA_EN);
    HWREG(baseAdd + I2C_DMARXENABLE_CLR) = (I2C_DMARXENABLE_CLR_DMARX_ENABLE_CLEAR);*/
  
    m_I2C_regs.I2C_BUF.b.RDMA_EN = LOW;    
    m_I2C_regs.I2C_DMARXENABLE_CLR.b.DMARX_ENABLE_CLEAR = HIGH; 
}

/**
 * \brief   This API determines whether error occured or not during
 *          I2C operation.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \returns error status.If error has occured it returns a non zero value.
 *          If no error has occured then return status will be zero.       
 *
 * Error may occur during I2C operation due to arbitration lost,access error,
 * receive overrun and transmit underrun.
 **/
uint32_t  HS_I2C::master_err()
{
    /*uint32_t err;

    err = HWREG(baseAdd + I2C_IRQSTATUS_RAW) & (  I2C_IRQSTATUS_RAW_AL   | //           0001 b
                                                  I2C_IRQSTATUS_RAW_AERR | //           1000 b
                                                  I2C_IRQSTATUS_RAW_NACK | //           0010 b
                                                  I2C_IRQSTATUS_RAW_ROVR); // 1000 0000 0000 b
                                                                           // 1000 0000 1011 mask result
    return err;*/  
    // 
  
    uint32_t err;
    err = m_I2C_regs.I2C_IRQSTATUS_RAW.reg & (uint32_t)(I2C::F_IRQSTATUS_AL      |  //           0001 b
                                                        I2C::F_IRQSTATUS_AERR    |  //      1000 0000 b
                                                        I2C::F_IRQSTATUS_NACK    |  //           0010 b
                                                        I2C::F_IRQSTATUS_ROVR)   ;  // 1000 0000 0000 b
    return err;                                                                     // 1000 0000 1011 mask result
} 

/**
 * \brief   This API enables wakeup mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void  HS_I2C::global_wake_up_enable()
{
    //HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_ENAWAKEUP;
    m_I2C_regs.I2C_SYSC.b.ENAWAKEUP = HIGH;
}

/**
 * \brief   This API disables wakeup mechanism
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns None.
 *          
 **/
void  HS_I2C::global_wake_up_disable()
{
    //HWREG(baseAdd + I2C_SYSC) &= ~I2C_SYSC_ENAWAKEUP;
    m_I2C_regs.I2C_SYSC.b.ENAWAKEUP = LOW;
}

/**
 * \brief   This API determines whether Master is busy or not.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 *
 * \return  returns 1 if bus is busy.
 *          returns 0 if bus is free.
 *
 **/
uint32_t  HS_I2C::master_busy()
{
    //(HWREG(baseAdd + I2C_CON) & I2C_CON_MST);
    return m_I2C_regs.I2C_CON.b.MST; /*I2C::F_CON_MST*/
}

/**
 * \brief  This API returns the status of  interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns status of interrupts.
 **/
uint32_t  HS_I2C::master_int_status()
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS)));
    return m_I2C_regs.I2C_IRQSTATUS.reg;
}  

/**
 * \brief   This API indicates the state of the reset in case of
 *          hardware reset,global reset or paratial reset.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns returns "1" if reset is completed. 
 *          returns "0" if internal module reset is ongoing.
 *          
 **/
bool  HS_I2C::system_status_get()
{
    //return(HWREG(baseAdd + I2C_SYSS) & I2C_SYSS_RDONE);   
   if (m_I2C_regs.I2C_SYSS.b.RDONE)
        return true;    // Reset completed 
    else
        return false;   // Internal module reset in ongoing
}

/**
 * \brief   This API returns one of the module's four own addresses,which
 *          external master used when addressing the module.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 *
 * \returns one of the module's four own address the external master used 
 *          when addressing the module.
 **/
uint32_t  HS_I2C::active_own_address_get()
{
    /*if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA0_ACT)))
    {
         return((HWREG(baseAdd + I2C_OA)));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA1_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(0))));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA2_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(1))));
    }
    else if((HWREG(baseAdd + I2C_ACTOA) & (I2C_ACTOA_OA3_ACT)))
    {
         return((HWREG(baseAdd + I2C_OAn(2))));
    }

    return 0;*/
  
    if(m_I2C_regs.I2C_ACTOA.b.OA0_ACT)
         return m_I2C_regs.I2C_OA.reg;
    else 
    if(m_I2C_regs.I2C_ACTOA.b.OA1_ACT)
         return m_I2C_regs.I2C_OA1.reg;
    else 
    if(m_I2C_regs.I2C_ACTOA.b.OA2_ACT)
         return m_I2C_regs.I2C_OA2.reg;
    else 
    if(m_I2C_regs.I2C_ACTOA.b.OA3_ACT)
         return m_I2C_regs.I2C_OA3.reg;

    return 0;
}

/**
 * \brief   This API Clear's Transmit and Receive FIFO.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 * \param   flag        It specifies Transmit FIFO or Receive FIFO.\n
 *     
 *         flag can take following macros.\n
 *
 *         I2C_TX_MODE - .\n
 *         I2C_RX_MODE - .\n
 *
 * \return None.
 **/
void  HS_I2C::FIFO_clear(I2C::e_I2C_MODE flag)
{  
    if(flag == I2C::I2C_TX_MODE)
        m_I2C_regs.I2C_BUF.b.TXFIFO_CLR = HIGH;
    else
        m_I2C_regs.I2C_BUF.b.RXFIFO_CLR = HIGH;
}

/**
 * \brief   This API selects one of the idel mode operation mechanism.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   flag      It is the value which determines the type of idel
 *                    mode operation.\n
 *
 *          flag can take following values.\n
 *
 *          I2C_FORCE_IDLE_MODE          - selects forced idel mode operation.\n
 *          I2C_NO_IDLE_MODE             - selects no idel mode operation.\n
 *          I2C_SMART_IDLE_MODE          - selects smart idel mode operation.\n
 *          I2C_SMART_IDLE_WAKEUP_MODE   - selects smart idel wakeup mode
 *                                         of operation.\n
 *
 * \returns None.
 *          
 **/
void  HS_I2C::idle_mode_select(I2C::e_SYSC_IDLEMODE flag)
{
    /*HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_IDLEMODE);
    HWREG(baseAdd + I2C_SYSC) |= flag;*/
  
    m_I2C_regs.I2C_SYSC.b.IDLEMODE = LOW;    
    m_I2C_regs.I2C_SYSC.b.IDLEMODE = flag;
}

/**
 * \brief  This API Enables a specific IRQ/DMA request source to generate an
 *         asynchronous wakeup signal.A wakeup is signaled to the local
 *         host if the corresponding event is captured by the core of
 *         the I2C controller.
 *
 * \param  baseAdd    It is the Memory address of the I2C instance used.
 * \param  eventFlag   It specifies for which event wakeup sinal has to 
 *                     Enable.\n
 *
 *         intFlag can take following values.\n
 *         
 *         I2C_WAKE_UP_ARBITRATION_LOST    - Arbitration-lost wakeup signal.\n
 *         I2C_WAKE_UP_NO_ACK              - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_READY_ACCESS   - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_GENERAL_CALL        - General call wakeup signal.\n
 *         I2C_WAKE_UP_START               - Start condition wakeup signal.\n
 *         I2C_WAKE_UP_STOP_CONDITION      - Stop condition wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_SLAVE          - Address-as-slave wakeup signal.\n
 *         I2C_WAKE_UP_TX_UNDER_FLOW       - Transmit under flow wakeup siganl.\n
 *         I2C_WAKE_UP_RECV_OVER_RUN       - Receive overrun wakeup signal.\n
 *         I2C_WAKE_UP_RECV_DRAIN          - Receive drain wakeup signal.\n
 *         I2C_WAKE_UP_TRANSMIT_DRAIN      - Transmit drain wakeup siganl.\n   
 *         I2C_WAKE_UP_DATA_RECV_TX_RDY    - Receive-data-ready
 *                                                  wakeup signal.\n
 *
 * \param  flag        It specifies IRQ or DMA Transmit or DMA receive 
 *                     request source to generate asynchronous wake up
 *                     signal.\n
 *
 *         flag can take following values.\n
 *
 *         I2C_WAKE_UP_IRQ.\n
 *         I2C_WAKE_UP_DMA_RECV.\n
 *         I2C_WAKE_UP_DMA_TRANMIT.\n
 *
 * \returns None.
 **/
void  HS_I2C::wake_up_enable(I2C::e_WE_flags event_flag, I2C::e_I2C_WAKE_UP flag)
{
    /*if(I2C_WAKE_UP_IRQ == flag)
    {
         HWREG(baseAdd + I2C_WE) |= eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_RECV == flag)
    {
         HWREG(baseAdd + I2C_DMARXWAKE_EN) |= eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_TRANSMIT == flag)
    {
         HWREG(baseAdd + I2C_DMATXWAKE_EN) |= eventFlag;
    }*/
     
    if(I2C::I2C_WAKE_UP_IRQ == flag)
         m_I2C_regs.I2C_WE.reg |= event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_RECV == flag)
         m_I2C_regs.I2C_DMARXWAKE_EN.reg |= event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_TRANSMIT == flag)
         m_I2C_regs.I2C_DMATXWAKE_EN.reg |= event_flag;
}

/**
 * \brief  This API Disables a specific IRQ/DMA request source to generate an
 *         asynchronous wakeup signal.A wakeup is signaled to the local
 *         host if the corresponding event is captured by the core of
 *         the I2C controller.
 *
 * \param  baseAdd    It is the Memory address of the I2C instance used.
 * \param  eventflag   It specifies for which event wakeup sinal has to 
 *                     disabled.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_WAKE_UP_ARBITRATION_LOST    - Arbitration-lost wakeup signal.\n
 *         I2C_WAKE_UP_NO_ACK              - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_RDY_ACCESS     - No-acknowledgment wakeup signal.\n
 *         I2C_WAKE_UP_GENERAL_CALL        - General call wakeup signal.\n
 *         I2C_WAKE_UP_START               - Start condition wakeup signal.\n
 *         I2C_WAKE_UP_STOP_CONDITION      - Stop condition wakeup signal.\n
 *         I2C_WAKE_UP_ADRR_SLAVE          - Address-as-slave wakeup signal.\n
 *         I2C_WAKE_UP_TX_UNDER_FLOW       - Transmit under flow wakeup siganl.\n
 *         I2C_WAKE_UP_RECV_OVER_RUN       - Receive overrun wakeup signal.\n
 *         I2C_WAKE_UP_RECV_DRAIN          - Receive drain wakeup signal.\n
 *         I2C_WAKE_UP_TRANSMIT_DRAIN      - Transmit drain wakeup siganl.\n   
 *         I2C_WAKE_UP_DATA_RECV_TX_RDY    - Receive-data-ready
 *                                              wakeup signal.\n
 *
 * \param  flag        It specifies IRQ or DMA Transmit or DMA receive 
 *                     request source to generate asynchronous wake up
 *                     signal.\n
 *
 *         flag can take following values.\n
 *
 *         I2C_WAKE_UP_IRQ.\n
 *         I2C_WAKE_UP_DMA_RECV.\n
 *         I2C_WAKE_UP_DMA_TRANMIT.\n
 *
 * \returns None.
 **/
void  HS_I2C::wake_up_disable(I2C::e_WE_flags event_flag, I2C::e_I2C_WAKE_UP flag)
{
    /*if(I2C_WAKE_UP_IRQ == flag)
    {
         HWREG(baseAdd + I2C_WE) &= ~eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_RECV == flag)
    {
         HWREG(baseAdd + I2C_DMARXWAKE_EN) &= ~eventFlag;
    }
    else if(I2C_WAKE_UP_DMA_TRANSMIT == flag)
    {
         HWREG(baseAdd + I2C_DMATXWAKE_EN) &= ~eventFlag;
    }*/
  
    if(I2C::I2C_WAKE_UP_IRQ == flag)
         m_I2C_regs.I2C_WE.reg &= ~event_flag;
    else
    if(I2C::I2C_WAKE_UP_DMA_RECV == flag)
         m_I2C_regs.I2C_DMARXWAKE_EN.reg &= ~event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_TRANSMIT == flag)
         m_I2C_regs.I2C_DMATXWAKE_EN.reg &= ~event_flag;
}

/**
 * \brief   This API configuers any one of the own address field out of four
 *          present in I2C controller.
 *
 * \param   baseAdd  It is the Memory address of the I2C instance used.
 * \param   slaveAdd  Slave address to be set.
 * \param   flag      It specifies the any one of the own address field
 *                    out of four.\n
 *
 *          flag can take following values.\n
 *      
 *          I2C_OWN_ADDR_0.\n
 *          I2C_OWN_ADDR_1.\n
 *          I2C_OWN_ADDR_2.\n
 *          I2C_OWN_ADDR_3.\n
 *
 * \returns None.
 *          
 **/
void  HS_I2C::own_address_set(uint32_t slave_add, I2C::e_OWN_ADDRESS_flags flag)
{
    /*switch(flag)
    {
         case 0 : 
               HWREG(baseAdd + I2C_OA) = slaveAdd;

         case 1 : 
               HWREG(baseAdd + I2C_OAn(0)) = slaveAdd;

         case 2 : 
               HWREG(baseAdd + I2C_OAn(1)) = slaveAdd;

         case 3 :
               HWREG(baseAdd + I2C_OAn(2)) = slaveAdd;
    }*/
  
    switch(flag)
    {
         case I2C::F_OA0 : 
               m_I2C_regs.I2C_OA.b.OA  = slave_add;

         case I2C::F_OA1 : 
               m_I2C_regs.I2C_OA1.b.OA1 = slave_add;

         case I2C::F_OA2 : 
               m_I2C_regs.I2C_OA2.b.OA1 = slave_add;

         case I2C::F_OA3 :
               m_I2C_regs.I2C_OA3.b.OA1 = slave_add;
     }  
}

/**
 * \brief   This API disable external clock gating mechanism by selecting
 *          approriate type of clock activity.
 *
 * \param   flag      It is the value which determines the type of clock
 *                    activity.\n
 *
 *          flag can take following values.\n
 *
 *          I2C_CUT_OFF_BOTH_CLCK       - Both OCP and SYS Clk are cut off.\n
 *          I2C_CUT_OFF_SYS_CLK         - system clock is cut off;OCP clock
 *                                        is kept alive.\n
 *          I2C_CUT_OFF_OCP_CLK         - OCP clock is cut off;system clock is
 *                                        is kept alive\n
 *          I2C_KEEP_ALIVE_BOTH_CLK     - BOTH OCP and SYS Clk are kept alive.\n
 *
 * \returns None.
 *          
 **/
void  HS_I2C::clock_activity_select(I2C::e_SYSC_CLKACTIVITY flag)
{
    /*HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_CLKACTIVITY);
    HWREG(baseAdd + I2C_SYSC) |= flag;*/
  
    m_I2C_regs.I2C_SYSC.b.CLKACTIVITY = 0;      
    m_I2C_regs.I2C_SYSC.b.CLKACTIVITY = flag;
  
}

/**
 * \brief   This API returns the status of the internal buffers.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used..
 * \param   flag        It specifies required status field.\n
 *     
 *          flag can take following macros.\n
 *
 *          I2C_TX_BUFFER_STATUS - Indicates the number of data bytes still.
 *                                 left to be written in TXFIFO\n
 *          I2C_RX_BUFFER_STATUS - Indicates the number of bytes to be
 *                                 transfered from the fifo at the end
 *                                 of the I2C transfer.\n
 *          I2C_FIFO_DEPTH       - Internal FIFO buffer depth.\n
 *
 * \returns required status of internal buffer.
 **/
uint32_t  HS_I2C::buffer_status(I2C::e_I2C_buffer_status flag)
{
    /*uint32_t status = 0;

    switch(flag)
    {
         case 0:
               status = HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_TXSTAT;
               break;

         case 1:
               status = (HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_RXSTAT) 
                        >> I2C_BUFSTAT_RXSTAT_SHIFT;
               break;

         case 2:
               status = (HWREG(baseAdd + I2C_BUFSTAT) & I2C_BUFSTAT_FIFODEPTH) 
                        >> I2C_BUFSTAT_FIFODEPTH_SHIFT;
               break;

         default:
               break;
    }

    return status;*/
  
    uint32_t status = 0;
  
    switch(flag)
    {
         case I2C::BUFSTAT_TXSTAT:
            status = m_I2C_regs.I2C_BUFSTAT.b.TXSTAT; // indicates the number of data bytes still left to be written in the TX FIFO
            break;
         case I2C::BUFSTAT_RXSTAT:
            status = m_I2C_regs.I2C_BUFSTAT.b.RXSTAT;   // indicates the number of bytes to be transferred from the FIFO
            break;
         case I2C::BUFSTAT_FIFODEPTH:
            status = m_I2C_regs.I2C_BUFSTAT.b.FIFODEPTH; //  indicates the internal FIFO buffer depth. see I2C::e_BUFSTAT_FIFODEPTH
            break;
         default:
            break;
    }

    return status;
}

/**
 * \brief   This API configure's the threshold value for FIFO buffer.
 *
 * \param   baseAdd     It is the Memory address of the I2C instance used.
 * \param   thresholdVal It is the threshold value for FIFO buffer.Which is 
 *                       used to specify the trigger level for data transfer or
 *                       data receive transfers.
 * \param   flag         It specifies FIFO buffer in TX mode or RX mode.\n
 *     
 *          flag can take following macros.\n
 *
 *          I2C_TX_MODE.\n
 *          I2C_RX_MODE.\n
 *
 * \return None.
 **/
void  HS_I2C::FIFO_threshold_config(I2C::e_BUF_TRSH_flags threshlod_val, I2C::e_I2C_MODE  flag)
{
    /*if(I2C_TX_MODE == flag)
    {
         HWREG(baseAdd + I2C_BUF) &= ~I2C_BUF_TXTRSH;

         HWREG(baseAdd + I2C_BUF) |= threshlodVal;
    }
    else
    {
         HWREG(baseAdd + I2C_BUF) &= ~I2C_BUF_RXTRSH;

         HWREG(baseAdd + I2C_BUF) |= threshlodVal <<  I2C_BUF_RXTRSH_SHIFT;
    }*/
  
    if(I2C::I2C_TX_MODE == flag)
    {
        m_I2C_regs.I2C_BUF.b.TXTRSH = LOW;        
        m_I2C_regs.I2C_BUF.b.TXTRSH |= threshlod_val;       
    }    
    else
    {
        m_I2C_regs.I2C_BUF.b.RXTRSH = LOW;        
        m_I2C_regs.I2C_BUF.b.RXTRSH |= threshlod_val;  
    }
}

/**
 * \brief  This API Clears the raw status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be cleared\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *
 * \returns None
 **/
void  HS_I2C::master_int_raw_status_clear_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //HWREG(baseAdd + I2C_IRQSTATUS_RAW) = intFlag;
    m_I2C_regs.I2C_IRQSTATUS_RAW.reg = int_flag; 
}

/**
 * \brief  This API returns the status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose status needs to be
 *                  returned.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C register ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_BUS_BUSY             - Bus busy.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \returns status of specified interrupts.
 **/
uint32_t  HS_I2C::master_int_status_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS)) & (intFlag));
    return ((m_I2C_regs.I2C_IRQSTATUS.reg) & (int_flag));
}

/**
 * \brief   This API returns the address of the slave device with which I2C wants to
 *          communicate.
 *
 * \param   baseAdd   It is the Memory address of the I2C instance used.
 * \param   slaveAddr slave address.
 *
 * \return  slave address.
 **/
uint16_t  HS_I2C::master_slave_addr_get(uint32_t slave_add)
{
    /* Returns the address of the slave with which the master will communicate.*/
    //return (HWREG(baseAdd + I2C_SA) & I2C_SA_SA);
    return m_I2C_regs.I2C_SA.b.SA;
}

/**
 * \brief  This API returns the raw status of specified interrupts in
 *         master mode.
 *
 * \param  baseAdd  It is the Memory address of the I2C instance used.
 * \param  intFlag  It specifies the interrupts whose raw status needs to be
 *                  returned.\n
 *
 *         intFlag can take following macros.\n
 *         
 *         I2C_INT_ARBITRATION_LOST     - Arbitration-lost interrupt.\n
 *         I2C_INT_NO_ACK               - No-acknowledgment interrupt.\n
 *         I2C_INT_ADRR_READY_ACESS     - I2C registers are ready to access.\n
 *         I2C_INT_RECV_READY           - Receive-data-ready interrupt.\n
 *         I2C_INT_TRANSMIT_READY       - Transmit-data-ready interrupt.\n
 *         I2C_INT_GENERAL_CALL         - General call interrupt.\n
 *         I2C_INT_START                - Start condition interrupt.\n
 *         I2C_INT_ACCESS_ERROR         - Access error interrupt.\n
 *         I2C_INT_STOP_CONDITION       - Stop condition interrupt.\n
 *         I2C_INT_ADRR_SLAVE           - Address-as-slave interrupt.\n
 *         I2C_INT_TRANSMIT_UNDER_FLOW  - Transmit under flow interrupt.\n
 *         I2C_INT_RECV_OVER_RUN        - Receive overrun interrupt.\n
 *         I2C_INT_BUS_BUSY             - Bus busy.\n
 *         I2C_INT_RECV_DRAIN           - Receive drain interrupt.\n
 *         I2C_INT_TRANSMIT_DRAIN       - Transmit drain interrupt.\n
 *
 * \returns status of specified interrupts.
 **/
uint32_t  HS_I2C::master_int_raw_status_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS_RAW)) & (intFlag));
    return ((m_I2C_regs.I2C_IRQSTATUS_RAW.reg) & (int_flag));
}

void  HS_I2C::clock_blocking_control(bool ownAdd0, bool ownAdd1, bool ownAdd2, bool ownAdd3)
{
    /*HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA0_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd0 << I2C_SBLOCK_OA0_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA1_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd1 << I2C_SBLOCK_OA1_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA2_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd2 << I2C_SBLOCK_OA2_EN_SHIFT;

    HWREG(baseAdd + I2C_SBLOCK) &= ~(I2C_SBLOCK_OA3_EN);
    HWREG(baseAdd + I2C_SBLOCK) |=  ownAdd3 << I2C_SBLOCK_OA3_EN_SHIFT;*/
  
    m_I2C_regs.I2C_SBLOCK.b.OA0_EN = LOW;
    m_I2C_regs.I2C_SBLOCK.b.OA0_EN = ownAdd0;
    
    m_I2C_regs.I2C_SBLOCK.b.OA1_EN = LOW;
    m_I2C_regs.I2C_SBLOCK.b.OA1_EN = ownAdd1;
    
    m_I2C_regs.I2C_SBLOCK.b.OA2_EN = LOW;
    m_I2C_regs.I2C_SBLOCK.b.OA2_EN = ownAdd2;
    
    m_I2C_regs.I2C_SBLOCK.b.OA3_EN = LOW;
    m_I2C_regs.I2C_SBLOCK.b.OA3_EN = ownAdd3;
}

/**
 * \brief   This API can be used to save the register context of I2C
 *
 * \param   i2cBase       Base address of I2C instance
 * \param   contextPtr    Pointer to the structure where I2C register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void  HS_I2C::context_save(I2CCONTEXT *contextPtr)
{
    //contextPtr->prescalar	= HWREG(i2cBase + I2C_PSC);
    //contextPtr->lowdivider 	= HWREG(i2cBase + I2C_SCLL);
    //contextPtr->highdivider = HWREG(i2cBase + I2C_SCLH);
    //contextPtr->ownaddr 	= HWREG(i2cBase + I2C_OA);
    
    contextPtr->prescalar	    = m_I2C_regs.I2C_PSC.reg ;
    contextPtr->lowdivider   	= m_I2C_regs.I2C_SCLL.reg;
    contextPtr->highdivider     = m_I2C_regs.I2C_SCLH.reg;
    contextPtr->ownaddr 	    = m_I2C_regs.I2C_OA.reg;
}

/**
 * \brief   This API can be used to restore the register context of I2C
 *
 * \param   i2cBase       Base address of I2C instance
 * \param   contextPtr    Pointer to the structure where I2C register
 *                        context need to be saved
 *
 * \return  None
 *
 **/
void  HS_I2C::context_restore(I2CCONTEXT *contextPtr)
{
    /*HWREG(i2cBase + I2C_CON) &= ~(I2C_CON_I2C_EN);	// Disable
	   HWREG(i2cBase + I2C_SYSC) |= I2C_SYSC_SRST;		// reset
	   HWREG(i2cBase + I2C_SYSC) &= ~I2C_SYSC_AUTOIDLE;// Autoidle disable

    HWREG(i2cBase + I2C_PSC)	=	contextPtr->prescalar;
    HWREG(i2cBase + I2C_SCLL)	=	contextPtr->lowdivider;
    HWREG(i2cBase + I2C_SCLH)	=	contextPtr->highdivider;
    HWREG(i2cBase + I2C_OA)		=	contextPtr->ownaddr;
	
	HWREG(i2cBase + I2C_CON) |= I2C_CON_I2C_EN; 	// Enable 
	while((!HWREG(i2cBase + I2C_SYSS) & I2C_SYSS_RDONE)); 	// reset complete...?*/
    
    m_I2C_regs.I2C_CON.b.I2C_EN = LOW;      // Disable
    m_I2C_regs.I2C_SYSC.b.SRST = HIGH;      // Reset
    m_I2C_regs.I2C_SYSC.b.AUTOIDLE = LOW;   // Autoidle disable

    m_I2C_regs.I2C_PSC.reg  = contextPtr->prescalar;
    m_I2C_regs.I2C_SCLL.reg = contextPtr->lowdivider;
    m_I2C_regs.I2C_SCLH.reg = contextPtr->highdivider;
    m_I2C_regs.I2C_OA.reg   = contextPtr->ownaddr;
    
    m_I2C_regs.I2C_CON.b.I2C_EN = HIGH;                           // Enable 
    while (!m_I2C_regs.I2C_SYSS.b.RDONE); // Reset complete...?
}
