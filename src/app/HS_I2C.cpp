#include "HS_I2C.h"

HS_I2C::HS_I2C(I2C::AM335x_I2C_Type &s_tmr)
:m_sI2C(s_tmr)
{
 
}

void  HS_I2C::soft_reset()
{
    //HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_SRST;
    m_sI2C.I2C_SYSC.b.SRST = HIGH;
}

void  HS_I2C::master_stop()
{
    //HWREG(baseAdd + I2C_CON) |= I2C_CON_STP;
    m_sI2C.I2C_CON.b.STP = HIGH;
}

void  HS_I2C::master_start()
{
    //HWREG(baseAdd + I2C_CON) |= I2C_CON_STT;
    m_sI2C.I2C_CON.b.STT = HIGH ;
}

void  HS_I2C::master_enable()
{
    /* Bring the I2C module out of reset */
    //HWREG(baseAdd + I2C_CON) |= I2C_CON_I2C_EN;
    m_sI2C.I2C_CON.b.I2C_EN = HIGH;
}

void  HS_I2C::master_disable()
{
    /* Put I2C module in reset */
    //HWREG(baseAdd + I2C_CON) &= ~(I2C_CON_I2C_EN);
    m_sI2C.I2C_CON.b.I2C_EN = LOW;
}

void  HS_I2C::auto_idle_enable()
{
    //HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_AUTOIDLE;
    m_sI2C.I2C_SYSC.b.AUTOIDLE = HIGH;
}

void  HS_I2C::auto_idle_disable()
{
    //HWREG(baseAdd + I2C_SYSC) &= ~I2C_SYSC_AUTOIDLE;
    m_sI2C.I2C_SYSC.b.AUTOIDLE = LOW;
}

void  HS_I2C::DMATx_event_enable()
{
    /*HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_XDMA_EN);
    HWREG(baseAdd + I2C_DMATXENABLE_SET) =  (I2C_DMATXENABLE_SET_DMATX_ENABLE_SET);*/
  
    m_sI2C.I2C_BUF.b.XDMA_EN = HIGH;    
    m_sI2C.I2C_DMATXENABLE_SET.b.DMATX_TRANSMIT_SET = HIGH;
}

void  HS_I2C::DMARx_event_enable()
{
    /*HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_RDMA_EN);
    HWREG(baseAdd + I2C_DMARXENABLE_SET) = (I2C_DMARXENABLE_SET_DMARX_ENABLE_SET); */
  
    m_sI2C.I2C_BUF.b.RDMA_EN = HIGH;    
    m_sI2C.I2C_DMARXENABLE_SET.b.DMARX_ENABLE_SET = HIGH;
}

void  HS_I2C::DMATx_event_disable()
{
    /*HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_XDMA_EN);
    HWREG(baseAdd + I2C_DMATXENABLE_CLR) = (I2C_DMATXENABLE_CLR_DMATX_ENABLE_CLEAR);*/
  
    m_sI2C.I2C_BUF.b.XDMA_EN = LOW;    
    m_sI2C.I2C_DMATXENABLE_CLR.b.DMATX_ENABLE_CLEAR = HIGH;  
}

void  HS_I2C::DMARx_event_disable()
{
    /*HWREG(baseAdd + I2C_BUF) &= ~(I2C_BUF_RDMA_EN);
    HWREG(baseAdd + I2C_DMARXENABLE_CLR) = (I2C_DMARXENABLE_CLR_DMARX_ENABLE_CLEAR);*/
  
    m_sI2C.I2C_BUF.b.RDMA_EN = LOW;    
    m_sI2C.I2C_DMARXENABLE_CLR.b.DMARX_ENABLE_CLEAR = HIGH; 
}

I2C::e_IRQSTATUS_flags  HS_I2C::master_err()
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
    err = m_sI2C.I2C_IRQSTATUS_RAW.reg & (uint32_t)(I2C::F_IRQSTATUS_AL      |  //           0001 b
                                                    I2C::F_IRQSTATUS_AERR    |  //      1000 0000 b
                                                    I2C::F_IRQSTATUS_NACK    |  //           0010 b
                                                    I2C::F_IRQSTATUS_ROVR)   ;  // 1000 0000 0000 b
    return (I2C::e_IRQSTATUS_flags)err;                                         // 1000 0000 1011 mask result
}    

void  HS_I2C::global_wake_up_enable()
{
    //HWREG(baseAdd + I2C_SYSC) |= I2C_SYSC_ENAWAKEUP;  
    m_sI2C.I2C_SYSC.b.ENAWAKEUP = HIGH;
}

void  HS_I2C::global_wake_up_disable()
{
    //HWREG(baseAdd + I2C_SYSC) &= ~I2C_SYSC_ENAWAKEUP;
    m_sI2C.I2C_SYSC.b.ENAWAKEUP = LOW;
}

uint16_t  HS_I2C::data_count_get()
{
    //return(HWREG(baseAdd + I2C_CNT));
  
    return m_sI2C.I2C_CNT.b.DCOUNT;
}

char   HS_I2C::master_data_get()// char
{
    //unsigned char rData;
    //rData = (unsigned char)HWREG(baseAdd + I2C_DATA);
    //return rData;
  
    char data;
    
    data = (char)m_sI2C.I2C_DATA.b.DATA;
    
    return data;
}

bool  HS_I2C::master_bus_busy()
{
    /*if(HWREG(baseAdd + I2C_IRQSTATUS_RAW) & I2C_IRQSTATUS_RAW_BB)
    {
         status = 1;
    }
    else
    {
         status = 0;
    }

    return status;*/ 
    
    if (m_sI2C.I2C_IRQSTATUS_RAW.b.BB)
        return true;    
    else
        return false;
}

uint32_t  HS_I2C::master_busy()
{
    //(HWREG(baseAdd + I2C_CON) & I2C_CON_MST);
    return m_sI2C.I2C_CON.b.MST; /*I2C::F_CON_MST*/
}

uint32_t  HS_I2C::master_int_status()
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS)));
    return m_sI2C.I2C_IRQSTATUS.reg;
}   

bool  HS_I2C::system_status_get()
{
    //return(HWREG(baseAdd + I2C_SYSS) & I2C_SYSS_RDONE);   
   if (m_sI2C.I2C_SYSS.b.RDONE)
        return true;    
    else
        return false;
}

uint32_t  HS_I2C::master_int_raw_status()
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS_RAW)));
    return m_sI2C.I2C_IRQSTATUS_RAW.reg;
}

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
  
    if(m_sI2C.I2C_ACTOA.b.OA0_ACT)
         return m_sI2C.I2C_OA.reg;
    else 
    if(m_sI2C.I2C_ACTOA.b.OA1_ACT)
         return m_sI2C.I2C_OA1.reg;
    else 
    if(m_sI2C.I2C_ACTOA.b.OA2_ACT)
         return m_sI2C.I2C_OA2.reg;
    else 
    if(m_sI2C.I2C_ACTOA.b.OA3_ACT)
         return m_sI2C.I2C_OA3.reg;

    return 0;
}

void  HS_I2C::FIFO_clear(I2C::e_I2C_MODE flag)
{
    /*if(I2C_TX_MODE == flag)
    {
         HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_TXFIFO_CLR);
    }
    else
    {
         HWREG(baseAdd + I2C_BUF) |= (I2C_BUF_RXFIFO_CLR);
    }*/
  
    if(flag == I2C::I2C_TX_MODE)
    {
        m_sI2C.I2C_BUF.b.TXFIFO_CLR = HIGH;
    }
    else
    {
        m_sI2C.I2C_BUF.b.RXFIFO_CLR = HIGH;
    }
}

void  HS_I2C::master_control(I2C::e_CON_flags cmd)
{
    //HWREG(baseAdd + I2C_CON) = cmd | I2C_CON_I2C_EN;  
    m_sI2C.I2C_CON.reg = cmd | I2C::F_CON_I2C_EN;
}

void  HS_I2C::set_data_count(uint16_t count)
{
    //HWREG(baseAdd + I2C_CNT) = count;
    m_sI2C.I2C_CNT.b.DCOUNT = count;
}

void  HS_I2C::idle_mode_select(I2C::e_SYSC_IDLEMODE flag)
{
    /*HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_IDLEMODE);
    HWREG(baseAdd + I2C_SYSC) |= flag;*/
  
    m_sI2C.I2C_SYSC.b.IDLEMODE = LOW;    
    m_sI2C.I2C_SYSC.b.IDLEMODE = flag;
}

void  HS_I2C::master_data_put(uint8_t data)
{
     /*write data to be transmited to Data transmit register */
    //HWREG(baseAdd + I2C_DATA) = data;
  
    m_sI2C.I2C_DATA.b.DATA = data;
}

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
         m_sI2C.I2C_WE.reg |= event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_RECV == flag)
         m_sI2C.I2C_DMARXWAKE_EN.reg |= event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_TRANSMIT == flag)
         m_sI2C.I2C_DMATXWAKE_EN.reg |= event_flag;
}

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
         m_sI2C.I2C_WE.reg &= ~event_flag;
    else
    if(I2C::I2C_WAKE_UP_DMA_RECV == flag)
         m_sI2C.I2C_DMARXWAKE_EN.reg &= ~event_flag;
    else 
    if(I2C::I2C_WAKE_UP_DMA_TRANSMIT == flag)
         m_sI2C.I2C_DMATXWAKE_EN.reg &= ~event_flag;
}

void  HS_I2C::master_init_exp_clk(uint32_t sys_clk, uint32_t internal_clk, uint32_t output_clk)
{
    uint32_t prescaler;
    uint32_t divider;

    /* Calculate prescaler value */
    prescaler = (uint8_t)(sys_clk / internal_clk) - 1;

    //HWREG(baseAdd + I2C_PSC) = prescaler;
    m_sI2C.I2C_PSC.b.PSC = (uint8_t)prescaler;
    
    divider = internal_clk/output_clk;
    divider = divider / 2;

    //HWREG(baseAdd + I2C_SCLL) = divider - 7;
    m_sI2C.I2C_SCLL.b.SCLL = (uint8_t)(divider - 7);
    
    //HWREG(baseAdd + I2C_SCLH) = divider - 5;
    m_sI2C.I2C_SCLH.b.SCLH = (uint8_t)(divider - 5);
}

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
               m_sI2C.I2C_OA.b.OA  = slave_add;

         case I2C::F_OA1 : 
               m_sI2C.I2C_OA1.b.OA1 = slave_add;

         case I2C::F_OA2 : 
               m_sI2C.I2C_OA2.b.OA1 = slave_add;

         case I2C::F_OA3 :
               m_sI2C.I2C_OA3.b.OA1 = slave_add;
     }  
}

void  HS_I2C::clock_activity_select(I2C::e_SYSC_CLKACTIVITY flag)
{
    /*HWREG(baseAdd + I2C_SYSC) &= ~(I2C_SYSC_CLKACTIVITY);
    HWREG(baseAdd + I2C_SYSC) |= flag;*/
  
    m_sI2C.I2C_SYSC.b.CLKACTIVITY = 0;      
    m_sI2C.I2C_SYSC.b.CLKACTIVITY = flag;
  
}

void  HS_I2C::master_int_clear_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //HWREG(baseAdd + I2C_IRQSTATUS) = intFlag; 
    m_sI2C.I2C_IRQSTATUS.reg |= int_flag;
}

void  HS_I2C::master_int_enable_ex(I2C::e_IRQENABLE_flags int_flag)
{
    //HWREG(baseAdd + I2C_IRQENABLE_SET) |= intFlag;
    m_sI2C.I2C_IRQENABLE_SET.reg |= int_flag;
}

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
            status = m_sI2C.I2C_BUFSTAT.b.TXSTAT; // indicates the number of data bytes still left to be written in the TX FIFO
            break;
         case I2C::BUFSTAT_RXSTAT:
            status = m_sI2C.I2C_BUFSTAT.b.RXSTAT;   // indicates the number of bytes to be transferred from the FIFO
            break;
         case I2C::BUFSTAT_FIFODEPTH:
            status = m_sI2C.I2C_BUFSTAT.b.FIFODEPTH; //  indicates the internal FIFO buffer depth. see I2C::e_BUFSTAT_FIFODEPTH
            break;
         default:
            break;
    }

    return status;
}

void  HS_I2C::master_int_disable_ex(I2C::e_IRQENABLE_flags int_flag)
{
    //HWREG(baseAdd + I2C_IRQENABLE_CLR) = intFlag;
    m_sI2C.I2C_IRQENABLE_CLR.reg |= int_flag;
}
void  HS_I2C::master_slave_addr_set(uint16_t slave_add)
{
    /*Set the address of the slave with which the master will communicate.*/
    //HWREG(baseAdd + I2C_SA) = slaveAdd;
        m_sI2C.I2C_SA.b.SA = slave_add;
}
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
        m_sI2C.I2C_BUF.b.TXTRSH = LOW;        
        m_sI2C.I2C_BUF.b.TXTRSH |= threshlod_val;       
    }    
    else
    {
        m_sI2C.I2C_BUF.b.RXTRSH = LOW;        
        m_sI2C.I2C_BUF.b.RXTRSH |= threshlod_val;  
    }
}

void  HS_I2C::master_int_raw_status_clear_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //HWREG(baseAdd + I2C_IRQSTATUS_RAW) = intFlag;
    m_sI2C.I2C_IRQSTATUS_RAW.reg = int_flag; 
}

uint32_t  HS_I2C::master_int_status_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS)) & (intFlag));
    return ((m_sI2C.I2C_IRQSTATUS.reg) & (int_flag));
}

uint16_t  HS_I2C::master_slave_addr_get(uint32_t slave_add)
{
    /* Returns the address of the slave with which the master will communicate.*/
    //return (HWREG(baseAdd + I2C_SA) & I2C_SA_SA);
    return m_sI2C.I2C_SA.b.SA;
}

uint32_t  HS_I2C::master_int_raw_status_ex(I2C::e_IRQSTATUS_flags int_flag)
{
    //return ((HWREG(baseAdd + I2C_IRQSTATUS_RAW)) & (intFlag));
    return ((m_sI2C.I2C_IRQSTATUS_RAW.reg) & (int_flag));
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
  
    m_sI2C.I2C_SBLOCK.b.OA0_EN = LOW;
    m_sI2C.I2C_SBLOCK.b.OA0_EN = ownAdd0;
    
    m_sI2C.I2C_SBLOCK.b.OA1_EN = LOW;
    m_sI2C.I2C_SBLOCK.b.OA1_EN = ownAdd1;
    
    m_sI2C.I2C_SBLOCK.b.OA2_EN = LOW;
    m_sI2C.I2C_SBLOCK.b.OA2_EN = ownAdd2;
    
    m_sI2C.I2C_SBLOCK.b.OA3_EN = LOW;
    m_sI2C.I2C_SBLOCK.b.OA3_EN = ownAdd3;
}

void  HS_I2C::context_save(I2CCONTEXT *contextPtr)
{
    //contextPtr->prescalar	= HWREG(i2cBase + I2C_PSC);
    //contextPtr->lowdivider 	= HWREG(i2cBase + I2C_SCLL);
    //contextPtr->highdivider = HWREG(i2cBase + I2C_SCLH);
    //contextPtr->ownaddr 	= HWREG(i2cBase + I2C_OA);
    
    contextPtr->prescalar	    = m_sI2C.I2C_PSC.reg ;
    contextPtr->lowdivider   	= m_sI2C.I2C_SCLL.reg;
    contextPtr->highdivider     = m_sI2C.I2C_SCLH.reg;
    contextPtr->ownaddr 	    = m_sI2C.I2C_OA.reg;
}
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
    
    m_sI2C.I2C_CON.b.I2C_EN = LOW;      // Disable
    m_sI2C.I2C_SYSC.b.SRST  = HIGH;     // Reset
    m_sI2C.I2C_SYSC.b.AUTOIDLE = LOW;   // Autoidle disable

    m_sI2C.I2C_PSC.reg  = contextPtr->prescalar;
    m_sI2C.I2C_SCLL.reg = contextPtr->lowdivider;
    m_sI2C.I2C_SCLH.reg = contextPtr->highdivider;
    m_sI2C.I2C_OA.reg   = contextPtr->ownaddr;
    
    m_sI2C.I2C_CON.b.I2C_EN = HIGH;                           // Enable 
    while (!m_sI2C.I2C_SYSS.b.RDONE); // Reset complete...?
}