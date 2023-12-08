#include "n_UART.h"


AM335x_UART::AM335x_UART(n_UART::AM335x_UART_Type *p_uart_regs)
: m_UART_regs(*p_uart_regs)
{
    m_TX_busy = false;
    m_RX_sts = RX_IDLE;   
    
    m_RX_data.reset();
    m_TX_data.reset();
}


/**
 * \brief  This API performs a module reset of the UART module. It also
 *         waits until the reset process is complete.
 *
 * \param  baseAdd  Memory address of the UART instance being used.
 *
 * \return None.
 *
 * \note   This API accesses the System Configuration Register(SYSC) and 
 *         System Status Register(SYSS) to perform module reset and to 
 *         wait until the same is complete.
 */
void  AM335x_UART::module_reset()
{
    // Performing Software Reset of the module.
    m_UART_regs.SYSC.b.SOFTRESET = HIGH;

    // Wait until the process of Module Reset is complete.
    while(!m_UART_regs.SYSS.b.RESETDONE);
}
                          
void AM335x_UART::FIFO_configure_no_DMA(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl)
{    
    n_UART::SCR_reg_t  cfg_scr         = {.reg = 0x0 };
    n_UART::TLR_reg_t  trigger_lvl_cfg = {.reg = 0x0 };
    n_UART::FCR_reg_t  cfg_fcr         = {.reg = 0x0 }; 
    
    cfg_scr.b.TXTRIGGRANU1 = 0x1;
    cfg_scr.b.RXTRIGGRANU1 = 0x1;
    cfg_scr.b.DMAMODECTL   = 0x1;
    cfg_scr.b.DMAMODE2     = n_UART::SCR_DMA_MODE_0;    // no dma

    tx_trig_lvl &= 0x003F;                                             // 'tx_trig_lvl' now has the 6-bit TX Trigger level value.
    trigger_lvl_cfg.b.TX_FIFO_TRIG_DMA  = (tx_trig_lvl & 0x003C) >> 2; // Collecting the bits tx_trig_lvl[5:2].        
    cfg_fcr.b.TX_FIFO_TRIG |= (tx_trig_lvl & 0x0003);                  // Collecting the bits tx_trig_lvl[1:0] and writing to 'fcr_value'.
    
    rx_trig_lvl &= 0x003F;                                             // 'rx_trig_lvl' now has the 6-bit RX Trigger level value.
    trigger_lvl_cfg.b.RX_FIFO_TRIG_DMA = (rx_trig_lvl & 0x003C) >> 2;  // Collecting the bits rx_trig_lvl[5:2]. 
    cfg_fcr.b.RX_FIFO_TRIG = (rx_trig_lvl & 0x0003);                   // Collecting the bits rx_trig_lvl[1:0] and writing to 'fcr_value'.   
    
    cfg_fcr.b.TX_FIFO_CLEAR = 1;
    cfg_fcr.b.RX_FIFO_CLEAR = 1;
    
    FIFO_config(cfg_scr, trigger_lvl_cfg, cfg_fcr);
}

void  AM335x_UART::FIFO_configure_DMA_RxTx(uint8_t tx_trig_lvl, uint8_t rx_trig_lvl)
{
    n_UART::SCR_reg_t  cfg_scr         = {.reg = 0x0 };
    n_UART::TLR_reg_t  trigger_lvl_cfg = {.reg = 0x0 };
    n_UART::FCR_reg_t  cfg_fcr         = {.reg = 0x0 }; 
    
    cfg_scr.b.TXTRIGGRANU1 = 0x1;
    cfg_scr.b.RXTRIGGRANU1 = 0x1;
    cfg_scr.b.DMAMODECTL   = 0x1;   // control trough SCR
    cfg_scr.b.DMAMODE2     = n_UART::SCR_DMA_MODE_1;   // DMA mode 0 or 1 available for UART0

    tx_trig_lvl &= 0x003F;                                             // 'tx_trig_lvl' now has the 6-bit TX Trigger level value.
    trigger_lvl_cfg.b.TX_FIFO_TRIG_DMA  = (tx_trig_lvl & 0x003C) >> 2; // Collecting the bits tx_trig_lvl[5:2].        
    cfg_fcr.b.TX_FIFO_TRIG |= (tx_trig_lvl & 0x0003);                  // Collecting the bits tx_trig_lvl[1:0] and writing to 'fcr_value'.
    
    rx_trig_lvl &= 0x003F;                                             // 'rx_trig_lvl' now has the 6-bit RX Trigger level value.
    trigger_lvl_cfg.b.RX_FIFO_TRIG_DMA = (rx_trig_lvl & 0x003C) >> 2;  // Collecting the bits rx_trig_lvl[5:2]. 
    cfg_fcr.b.RX_FIFO_TRIG = (rx_trig_lvl & 0x0003);                   // Collecting the bits rx_trig_lvl[1:0] and writing to 'fcr_value'.   
    
    cfg_fcr.b.TX_FIFO_CLEAR = 1;
    cfg_fcr.b.RX_FIFO_CLEAR = 1;
    
    FIFO_config(cfg_scr, trigger_lvl_cfg, cfg_fcr);
}

/**
 * \brief  This API configures the FIFO settings for the UART instance.
 *         Specifically, this does the following configurations:
 *         1> Configures the Transmitter and Receiver FIFO Trigger Level
 *            granularity\n
 *         2> Configures the Transmitter and Receiver FIFO Trigger Level\n
 *         3> Configures the bits which clear/not clear the TX and RX FIFOs\n
 *         4> Configures the DMA mode of operation\n
 * 
 * \param  fifo_config    This specifies the desired FIFO configurations.
 *                       Use the macro UART_FIFO_CONFIG to pass the required
 *                       FIFO settings.
 *
 * The parameters of UART_FIFO_CONFIG can take the following values:\n
 * -- txGra - the Transmitter FIFO trigger level granularity\n
 * -- rxGra - the Receiver FIFO trigger level granularity\n
 *    These can take one of the following two values:\n
 *    - UART_TRIG_LVL_GRANULARITY_1 - for a granularity of 1,\n
 *    - UART_TRIG_LVL_GRANULARITY_4 - for a granularity of 4.\n
 *
 * -- txTrig - the Transmitter FIFO trigger level\n
 *
 *    For 'txGra' being UART_TRIG_LVL_GRANULARITY_4, this can take one of the
 *    values from one of the following two sets:
 *    Set 1> UART_FCR_TX_TRIG_LVL_n, where n = 8,16,32,56.
 *           These are programmed to the FCR[5:4] in FCR register.
 *    Set 2> m , where (1 <= m <= 15).
 *           The trigger level would then be (m * 4).
 *           For example: If m = 9, then trigger level = 36.
 *           The value 'm' is programmed into TLR[3:0] field in TLR register.
 * 
 *    For granularity being UART_TRIG_LVL_GRANULARITY_1, this can take
 *    any decimal value from 1 to 63.
 * 
 * -- rxTrig - the Receiver FIFO Trigger level\n
 *
 *    For granularity being UART_TRIG_LVL_GRANULARITY_4, this can
 *    take one of the macro from one of the following two sets:
 *    Set 1> UART_FCR_RX_TRIG_LVL_n, where n = 8,16,56,60.  
 *           These are programmed into FCR[7:6] field in FCR register.
 *    Set 2> m , where (1 <= m <= 15).
 *           The trigger level would then be (m * 4).
 *           For example: If m = 7, then trigger level = 28.
 *           The value 'm' is programmed to the TLR[7:4] field of TLR.
 * 
 *    For granularity being UART_TRIG_LVL_GRANULARITY_1, this can take
 *    any decimal value from 1 to 63.
 *
 * -- txClr - the Transmitter FIFO clear flag\n
 * -- rxClr - the Receiver FIFO clear flag\n
 *   
 *    These can take the following values:
 *    0 - to not clear the FIFO\n
 *    1 - to clear the FIFO. Clearing the FIFO also results in resetting the
 *        FIFO counter logic to 0.\n
 *
 * -- dmaEnPath - specifies whether DMA Mode settings should be configured
 *    through FCR or SCR. This can take one of the following two values:
 *    UART_DMA_EN_PATH_FCR - to configure DMA through FCR\n
 *    UART_DMA_EN_PATH_SCR - to configure DMA through SCR\n 
 *
 * -- dmaMode - specifies the DMA Mode to be used\n
 *    This can take one of the following four values:
 *    - UART_DMA_MODE_m_ENABLE, where m = 0, 1, 2 or 3.
 *
 * \return  The value that was written to the FIFO Control Register(FCR).
 *
 * \note    1> FIFO Control Register(FCR) is a write-only register and its
 *             contents cannot be read. Hence, it is  not possible for a
 *             read-modify-write operation on this register. Therefore it is
 *             expected that the FIFO configuration is done at once for both
 *             TX and RX directions and always the entire FCR related information is
 *             required during modification of the FIFO settings.
 *             Also the FIFO related settings are valid only when the FIFO is
 *             enabled. This means that FIFO mode of operation should be enabled for
 *             FIFO related settings to take effect.
 */


n_UART::FCR_reg_t AM335x_UART::FIFO_config(n_UART::SCR_reg_t  cfg_scr, 
                                           n_UART::TLR_reg_t  fifo_trigger_lvl, 
                                           n_UART::FCR_reg_t  cfg_fcr)
{
    uint32_t  enhan_fn_bit_val = 0;
    uint32_t  tcr_tlr_bit_val = 0;
        
    // Setting the EFR[4] bit to 1. 
    enhan_fn_bit_val = enhan_func_enable();
     tcr_tlr_bit_val = sub_config_TCRTLR_mode_en();  // enable access to tcr or tlr registers
     
     cfg_fcr.b.FIFO_EN = HIGH;
           
    /// Setting the Receiver FIFO trigger level. ///
    if(n_UART::TRIG_LVL_GRANULARITY_1 != cfg_scr.b.RXTRIGGRANU1)
    {        
        m_UART_regs.SCR.b.RXTRIGGRANU1 = 0;         // Clearing the RXTRIGGRANU1 bit in SCR. 
        m_UART_regs.TLR.b.RX_FIFO_TRIG_DMA = 0;     // Clearing the RX_FIFO_TRIG_DMA field of TLR register

        cfg_fcr.b.RX_FIFO_TRIG = LOW;
        
        // Checking if 'fifo_trigger_lvl' matches with the RX Trigger level values in FCR.
        if((n_UART::FCR_RX_FIFO_TRIG_8CHARS == fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA)  ||
           (n_UART::FCR_RX_FIFO_TRIG_16CHARS == fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA) ||
           (n_UART::FCR_RX_FIFO_TRIG_56CHARS == fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA) ||
           (n_UART::FCR_RX_FIFO_TRIG_60CHARS == fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA))
        {
            cfg_fcr.b.RX_FIFO_TRIG = fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA;
        }
        else
        {
            // RX Trigger level will be a multiple of 4.
            // Programming the RX_FIFO_TRIG_DMA field of TLR register.
            m_UART_regs.TLR.b.RX_FIFO_TRIG_DMA = fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA;
        }
    }
    else
    {   
        m_UART_regs.SCR.b.RXTRIGGRANU1 = HIGH;                                        // Setting the RXTRIGGRANU1 bit of SCR register.
        m_UART_regs.TLR.b.RX_FIFO_TRIG_DMA = fifo_trigger_lvl.b.RX_FIFO_TRIG_DMA;     // Programming the RX_FIFO_TRIG_DMA field of TLR register.
    }

    /// Setting the Transmitter FIFO trigger level. ///
    if(n_UART::TRIG_LVL_GRANULARITY_1 != cfg_scr.b.TXTRIGGRANU1)
    {  
        m_UART_regs.SCR.b.TXTRIGGRANU1 = 0;  
        m_UART_regs.TLR.b.TX_FIFO_TRIG_DMA = 0;
          
        cfg_fcr.b.TX_FIFO_TRIG = LOW;

        // Checking if 'fifo_trigger_lvl' matches with the TX Trigger level values in FCR.//
        if((n_UART::FCR_TX_FIFO_TRIG_8CHARS == (fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA))  ||
           (n_UART::FCR_TX_FIFO_TRIG_16CHARS == (fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA)) ||
           (n_UART::FCR_TX_FIFO_TRIG_32CHARS == (fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA)) ||
           (n_UART::FCR_TX_FIFO_TRIG_56CHARS == (fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA)))
        {
            cfg_fcr.b.TX_FIFO_TRIG = fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA;
        }
        else
        {
            // TX Trigger level will be a multiple of 4.
            // Programming the TX_FIFO_TRIG_DMA field of TLR register.
            m_UART_regs.TLR.b.TX_FIFO_TRIG_DMA = fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA;          
        }
    }
    else
    {        
        m_UART_regs.SCR.b.TXTRIGGRANU1 = HIGH;                                     // Setting the TXTRIGGRANU1 bit of SCR register.
        m_UART_regs.TLR.b.TX_FIFO_TRIG_DMA = fifo_trigger_lvl.b.TX_FIFO_TRIG_DMA;  // Programming the TX_FIFO_TRIG_DMA field of TLR register.
    }

    if(n_UART::DMA_EN_PATH_SCR == cfg_scr.b.DMAMODECTL)
    {              
        m_UART_regs.SCR.b.DMAMODECTL = HIGH;                    // Configuring the UART DMA Mode through SCR register.
        m_UART_regs.SCR.b.DMAMODE2   = 0x0;                     // Clearing the DMAMODE2 field in SCR.
        m_UART_regs.SCR.b.DMAMODE2   = cfg_scr.b.DMAMODE2;      // Programming the DMAMODE2 field in SCR.
    }
    else
    {
        m_UART_regs.SCR.b.DMAMODECTL = LOW;                       // Configuring the UART DMA Mode through FCR register.        
    }
    
    FIFO_register_write(cfg_fcr);                 // Writing 'fcr_value' to the FIFO Control Register(FCR)    
    TCRTLR_bit_val_restore(tcr_tlr_bit_val);        // Restoring the value of TCRTLR bit in MCR    
    enhan_func_bit_val_restore(enhan_fn_bit_val);   // Restoring the value of EFR[4] to the original value

    return cfg_fcr;
}

#define UART_MODULE_INPUT_CLK  (48000000)
// Over-sampling rate for MIR mode used to obtain the Divisor Values.
#define UART_MIR_OVERSAMPLING_RATE_41          (41)
#define UART_MIR_OVERSAMPLING_RATE_42          (42)
void  AM335x_UART::BAUD_set(unsigned int baud_rate)
{
    uint32_t divisor_value = 0;

    // Computing the Divisor Value.
    divisor_value = divisor_val_compute(UART_MODULE_INPUT_CLK,
                                        baud_rate,
                                        n_UART::MODE_UART_16x,
                                        UART_MIR_OVERSAMPLING_RATE_42);


    divisor_latch_write(divisor_value);
}

/**
 * \brief  This API configures the specified Register Configuration mode for
 *         the UART.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 * \param  mode_flag  This specifies the register configuration mode to be
 *                   enabled.
 *
 * 'mode_flag' can take one of the following values:
 * - UART_REG_CONFIG_MODE_A - to enable Register Configuration Mode A\n
 * - UART_REG_CONFIG_MODE_B - to enable Register Configuration Mode B\n
 * - UART_REG_OPERATIONAL_MODE - to enable Register Operational Mode\n
 *
 * \return The contents of the Line Control Register(LCR) before it was
 *         modified.
 *
 * \note   Since the UART module registers that can be accessed at any time
 *         depends on the value in the Line Control Register(LCR), three
 *         register configuration modes have been defined, each corresponding
 *         to a specific state of the LCR. The three register configuration
 *         modes are:\n
 *         - Configuration Mode A: LCR[7] = 1 and LCR[7:0] != 0xBF.\n
 *         - Configuration Mode B: LCR[7:0] = 0xBF.\n
 *         - Operational Mode    : LCR[7] = 0.\n
 *
 *         Refer to the Register Listing in the UART/IrDA/CIR peripheral
 *         document for more information.\n
 *
 */
uint32_t  AM335x_UART::reg_config_mode_enable(n_UART::e_UART_CONFIG_MODE mode_flag)
{
    volatile uint32_t LCR_reg_value = 0;
    
    LCR_reg_value = m_UART_regs.LCR.reg;        // Preserving the current value of LCR.
    
    switch(mode_flag)
    {
        case n_UART::CONFIG_MODE_A:
        case n_UART::CONFIG_MODE_B:
             m_UART_regs.LCR.reg = (mode_flag & 0xFF);
        break;
        case n_UART::OPERATIONAL_MODE:
            m_UART_regs.LCR.reg &= 0x7F;
        break;

        default:
        break;
    }

    return LCR_reg_value;
}

/**
 * \brief  This API configures the Line Characteristics for the
 *         UART instance. The Line Characteristics include:
 *         - Word length per frame\n
 *         - Number of Stop Bits per frame\n
 *         - Parity feature configuration\n
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 * \param   wlen_stb_flag Bit mask value of the bits pertaining to word
 *                      length selection and stop bits selection in LCR.
 * \param   parity_flag  Bit mask value of the bits pertaining to parity
 *                      feature selection in LCR.
 *
 * 'wlen_stb_flag' can take one of the following macros:
 *  - (UART_FRAME_WORD_LENGTH_n | UART_FRAME_NUM_STB_1), where
 *    n = 5,6,7 or 8. -- This signifies that 1 stop bit and
 *    one among 5,6,7 and 8 bits are chosen as the word length
 *    per frame.
 *  - (UART_FRAME_WORD_LENGTH_n | UART_FRAME_NUM_STB_1_5_2), where
 *    n = 5,6,7 or 8. -- This signifies that the word length and
 *    number of stop bits per frame could be one among the below
 *    four choices:
 *    --- WL = 5          NUM_STB = 1.5
 *    --- WL = 6,7 or 8   NUM_STB = 2
 *
 * 'parity_flag' can take one of the following macros:
 *  - (UART_ODD_PARITY) - signifying that odd parity be enabled and the
 *     parity bit be represented in a default manner.\n
 *  - (UART_EVEN_PARITY) - signifying that even parity be enabled and the
 *     parity bit be represented in a default manner.\n
 *  - (UART_PARITY_REPR_1) - signifying that the parity bit be represented
 *     by a logic 1 in the transmitted and received data.\n
 *  - (UART_PARITY_REPR_0) - signifying that the parity bit be represented
 *     by a logic 0 in the transmitted and received data.\n
 *  - (UART_PARITY_NONE) - signifying that no parity be enabled.\n
 *
 * \return  None.
 */ 
/*
void  AM335x_UART::line_char_config(uint32_t wlen_stb_flag, uint32_t parity_flag)
{   
    // Clearing the CHAR_LENGTH and NB_STOP fields in LCR.
    m_UART_regs.LCR.b.CHAR_LENGTH = 0;  
    m_UART_regs.LCR.b.NB_STOP = 0;
    // Programming the CHAR_LENGTH and NB_STOP fields in LCR.
    m_UART_regs.LCR.reg |= (wlen_stb_flag & 
                            (n_UART::LCR_CHAR_LENGTH | 
                             n_UART::LCR_NB_STOP));
    
    // Clearing the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR.
    m_UART_regs.LCR.b.PARITY_EN = 0;
    m_UART_regs.LCR.b.PARITY_TYPE1 = 0;
    m_UART_regs.LCR.b.PARITY_TYPE2 = 0;
    
    // Programming the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR.
    m_UART_regs.LCR.reg |= (parity_flag & 
                           (n_UART::LCR_PARITY_EN | 
                            n_UART::LCR_PARITY_TYPE1 |
                            n_UART::LCR_PARITY_TYPE2));
}
*/
   
void  AM335x_UART::char_len_config(n_UART::e_CHAR_LENGHT len)
{   
    // Clearing the CHAR_LENGTH  fields in LCR.
    m_UART_regs.LCR.b.CHAR_LENGTH = 0;  
    m_UART_regs.LCR.b.CHAR_LENGTH = len;    // then write
    
}

void  AM335x_UART::stop_bit_config(n_UART::e_STOP_BIT stop_bit)
{   
    // Clearing the NB_STOP fields in LCR.
    m_UART_regs.LCR.b.NB_STOP = 0;
    m_UART_regs.LCR.b.NB_STOP = stop_bit;  // then write
}

void  AM335x_UART::parity_config(n_UART::e_LCR_PARITY parity)
{   
    // Clearing the PARITY_EN, PARITY_TYPE1 and PARITY_TYPE2 fields in LCR.
    m_UART_regs.LCR.b.PARITY_EN = 0;
    m_UART_regs.LCR.b.PARITY_TYPE1 = 0;
    m_UART_regs.LCR.b.PARITY_TYPE2 = 0;
    
    m_UART_regs.LCR.reg |= (parity & n_UART::LCR_Parity_mask);
}

/**
 * \brief  This API configures the operating mode for the UART instance.
 *         The different operating modes are:
 *         - UART(16x, 13x, 16x Auto-Baud)\n
 *         - IrDA(SIR, MIR, FIR)\n
 *         - CIR\n
 *         - Disabled state(default state)\n
 *
 * \param   baseAdd   Memory address of the UART instance being used.
 * \param   mode_flag  A value which holds the mode number. This mode  
 *                    number is referred from the MODESELECT field in MDR1.
 *
 * 'mode_flag' can take one of the following values:
 * - UART16x_OPER_MODE - to switch to UART 16x operating mode\n
 * - UART_SIR_OPER_MODE - to swith to IrDA SIR operating mode\n
 * - UART16x_AUTO_BAUD_OPER_MODE - to switch to UART 16x Auto Baud operating
 *   mode\n
 * - UART13x_OPER_MODE - to switch to UART 13x operating mode\n
 * - UART_MIR_OPER_MODE - to switch to IrDA MIR operating mode\n 
 * - UART_FIR_OPER_MODE - to switch to IrDA FIR operating mode\n
 * - UART_CIR_OPER_MODE - to switch to CIR operating mode\n
 * - UART_DISABLED_MODE - to switch to Disabled state\n
 *
 * \return  The mode number in the MODESELECT field of MDR1 before it
 *          was  modified.
 */
n_UART::e_MODESELECT  AM335x_UART::operating_mode_select(n_UART::e_MODESELECT mode_flag)
{
    n_UART::e_MODESELECT op_mode = (n_UART::e_MODESELECT)0;
    
    op_mode = (n_UART::e_MODESELECT)m_UART_regs.MDR1.b.MODESELECT;
    m_UART_regs.MDR1.b.MODESELECT = 0;                              // Clearing the MODESELECT field in MDR1.
    m_UART_regs.MDR1.b.MODESELECT = mode_flag;                      // Programming the MODESELECT field in MDR1.
    
    return op_mode;
}

/**
 * \brief   This API computes the divisor value for the specified operating
 *          mode. Not part of this API, the divisor value returned is written
 *          to the Divisor Latches to configure the Baud Rate.
 *
 * \param   module_clk        The frequency of the input clock to the UART module
 * \param   mode_flag         A value which represents the current operating mode
 * \param   baud_rate         The required baud rate of communication in bits
 *                           per second(bps)
 * \param   mirOverSampRate  Over-sampling rate for MIR mode.This is applicable
 *                           only when MIR mode of operation is chosen.
 *                           Otherwise, this value is not considered.
 *
 * 'mode_flag' can take one of the following values:\n
 * - UART16x_OPER_MODE - indicating 16x operating mode\n
 * - UART13x_OPER_MODE - indicating 13x operating mode\n 
 * - UART_SIR_OPER_MODE - indicating SIR operating mode\n
 * - UART_MIR_OPER_MODE - indicating MIR operating mode\n
 * - UART_FIR_OPER_MODE - indicating FIR operating mode\n
 *
 * 'mirOverSampRate' can take one of the following values:
 * - UART_MIR_OVERSAMPLING_RATE_41 - for an over-sampling rate of 41\n
 * - UART_MIR_OVERSAMPLING_RATE_42 - for an over-smapling rate of 42\n
 *
 * \return The divisor value computed for the specified mode.
 *
 * \note   Refer to the section in the user guide that specifies the baud rate
 *         computation method to find the supported values of baud rates.
 */
uint32_t  AM335x_UART::divisor_val_compute(uint32_t module_clk,
                                           uint32_t baud_rate,
                                           n_UART::e_MODESELECT  mode_flag,
                                           uint32_t mir_over_samp_rate)
{
    uint32_t divisor_value = 0;
        
    switch(mode_flag)
    {
        case n_UART::MODE_UART_16x:
        case n_UART::MODE_SIR:
            divisor_value = (module_clk)/(16 * baud_rate);
            break;
        case n_UART::MODE_UART_13x:
            divisor_value = (module_clk)/(13 * baud_rate);
            break;        
        case n_UART::MODE_MIR:
            divisor_value = (module_clk)/(mir_over_samp_rate * baud_rate);
            break;
        case n_UART::MODE_FIR:
            divisor_value = 0;
            break;
        default:
            break;
    }
  
    return divisor_value;
}

/**
 * \brief  This API is used to write the specified divisor value to Divisor
 *         Latch registers DLL and DLH.
 *
 * \param  baseAdd       Memory address of the UART instance being used.
 * \param  divisorValue  The 14-bit value whose least 8 bits go to DLL
 *                       and highest 6 bits go to DLH.
 * 
 * \return A concatenated value of DLH and DLL registers(DLH:DLL, a 14-bit 
 *         value) before they are modified in the current API.
 */
uint32_t  AM335x_UART::divisor_latch_write(uint32_t divisor_value)
{
    volatile             uint32_t  enhan_fn_bit_val = 0;
    volatile             uint32_t  sleep_md_bit_val = 0;
    volatile             uint32_t  LCR_reg_value    = 0;
    volatile n_UART::e_MODESELECT  op_mode          = (n_UART::e_MODESELECT)0;
                         uint32_t  div_reg_val      = 0;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);      // Switching to Register Configuration Mode B.    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;                    // Collecting the current value of EFR[4] and later setting it.    
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;    
    reg_config_mode_enable(n_UART::OPERATIONAL_MODE);                   // Switching to Register Operational Mode.

    /// Collecting the current value of IER[4](SLEEPMODE bit) and later clearing it.///
    sleep_md_bit_val = m_UART_regs.IER_UART.b.SLEEPMODE;
    m_UART_regs.IER_UART.b.SLEEPMODE = 0;        
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_B);             // Switching to Register Configuration Mode B.

    /// Collecting the current value of Divisor Latch Registers. ///
    div_reg_val = m_UART_regs.DLL.reg & 0xFF;
    div_reg_val |= ((m_UART_regs.DLH.reg & 0x3F) << 8);
    
    op_mode = operating_mode_select(n_UART::MODE_DISABLE);     // Switch the UART instance to Disabled state.
    
    m_UART_regs.DLL.reg = (divisor_value & 0x00FF);            // Writing to Divisor Latch Low(DLL) register.    
    m_UART_regs.DLH.reg = ((divisor_value & 0x3F00) >> 8);     // Writing to Divisor Latch High(DLH) register.    
    
    operating_mode_select(op_mode);                           // Restoring the Operating Mode of UART.
    
    reg_config_mode_enable(n_UART::OPERATIONAL_MODE);         // Switching to Register Operational Mode.    
    m_UART_regs.IER_UART.b.SLEEPMODE = sleep_md_bit_val;      // Restoring the value of IER[4] to its original value.    
    reg_config_mode_enable(n_UART::CONFIG_MODE_B);            // Switching to Register Configuration Mode B.

    /// Restoring the value of EFR[4] to its original value. ///
    m_UART_regs.EFR.b.ENHANCEDEN = LOW;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;
    m_UART_regs.LCR.reg = LCR_reg_value;                     // Restoring the value of LCR Register.  
    
    return div_reg_val;
}

/**
 * \brief  This API enables write access to Divisor Latch registers DLL and
 *         DLH.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return None.
 */
void  AM335x_UART::divisor_latch_enable()
{
    /* Enable access to Divisor Latch registers by setting LCR[7] bit. */
    // HWREG(baseAdd + UART_LCR) |= (UART_LCR_DIV_EN);
    m_UART_regs.LCR.b.DIV_EN = HIGH;
}

/**
 * \brief  This API disables write access to Divisor Latch registers DLL and
 *         DLH.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return None.
 *
 * \note   Disabling write access to Divisor Latch Registers enables access to
 *         MCR, FCR, IER, BLR, EBLR, RHR registers.
 */
void  AM335x_UART::divisor_latch_disable()
{
    /// Disabling access to Divisor Latch registers by clearing LCR[7] bit. ///
    m_UART_regs.LCR.b.DIV_EN = LOW;
}


/**
 * \brief  This API is used to restore the UART to the specified Register
 *         Configuration Mode. 
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  lcr_reg_value  The value to be loaded to the Line Control Register(LCR).
 *
 * \return None
 *
 * \note   The API UARTRegConfigModeEnable() and the current API are used
 *         hand-in-hand. While UARTRegConfigModeEnable() switches the UART to
 *         the requested operating mode, the current API restores the UART to
 *         that register configuration mode prevalent before
 *         UARTRegConfigModeEnable() was called.
 */
void  AM335x_UART::reg_conf_mode_restore(uint32_t lcr_reg_value)
{
    /* Programming the Line Control Register(LCR). */
    //HWREG(baseAdd + UART_LCR) = lcr_reg_value;
    m_UART_regs.LCR.reg = lcr_reg_value;
}

/**
 * \brief  This API is used to introduce or to remove a Break condition.
 * 
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  break_state  This specifies whether the break condition should be
 *                     introduced or removed.
 *
 * 'break_state' can take one of the following two values:
 * - UART_BREAK_COND_DISABLE - to disable the Break condition if it has
 *   already been enabled\n
 * - UART_BREAK_COND_ENABLE - to enable the Break condition\n
 *
 * \return None
 *
 * \note  When the Break Condition is imposed, the Transmitter output line TX
 *        goes low to alert the communication terminal.
 */
void  AM335x_UART::break_ctl(bool break_state)
{
    /// Clearing the BREAK_EN bit in LCR. ///
    m_UART_regs.LCR.b.BREAK_EN = 0;

    /// Programming the BREAK_EN bit in LCR. ///
    m_UART_regs.LCR.b.BREAK_EN = break_state;
}

/**
 * \brief  This API configures the Parity feature for the UART.
 *
 * \param  baseAdd     Memory address of the UART instance being used
 * \param  parity_flag  This specifies the parity configuration to be
 *                     programmed to the Line Control Register(LCR)
 *
 * 'parity_flag' can take one of the following values:
 *  - (UART_ODD_PARITY) - signifying that odd parity be enabled and the parity
 *     bit be represented in a default manner\n
 *  - (UART_EVEN_PARITY) - signifying that even parity be enabled and the
 *     parity bit be represented in a default manner\n
 *  - (UART_ODD_PARITY_REPR_1) - signifying that odd parity be enabled and the
 *     parity bit be represented by a logic 1\n
 *  - (UART_EVEN_PARITY_REPR_0)- signifying that even parity be enabled and the
 *     parity bit be represented by a logic 0\n
 *  - (UART_PARITY_NONE) - signifying that no parity be enabled\n
 *
 * \return None
 */
void  AM335x_UART::parity_mode_set(uint32_t parity_flag)
{
    //HWREG(baseAdd + UART_LCR) &= ~((UART_LCR_PARITY_TYPE2 |
    //                                UART_LCR_PARITY_TYPE1 |
    //                                UART_LCR_PARITY_EN));
    m_UART_regs.LCR.b.PARITY_EN = 0;
    m_UART_regs.LCR.b.PARITY_TYPE1 = 0;
    m_UART_regs.LCR.b.PARITY_TYPE2 = 0;

    // Programming the PARITY_TYPE2, PARITY_TYPE1 and PARITY_EN fields of LCR.
    //HWREG(baseAdd + UART_LCR) |= (parity_flag & (UART_LCR_PARITY_TYPE2 |
    //                                            UART_LCR_PARITY_TYPE1 |
    //                                            UART_LCR_PARITY_EN));
    m_UART_regs.LCR.reg = (parity_flag & 
                           (n_UART::LCR_PARITY_EN | 
                            n_UART::LCR_PARITY_TYPE1 |
                            n_UART::LCR_PARITY_TYPE2));
}

/**
 * \brief  This API reads the Parity configuration being set in the UART.
 *
 * \param  baseAdd     Memory address of the UART instance being used
 *
 * \return This returs one of the following values:
 *  - (UART_ODD_PARITY) - signifying that odd parity is enabled and the parity
 *     bit is represented in a default manner\n
 *  - (UART_EVEN_PARITY) - signifying that even parity is enabled and the
 *     parity bit is represented in a default manner\n
 *  - (UART_ODD_PARITY_REPR_1) - signifying that odd parity is enabled and the
 *     parity bit is represented by a logic 1\n
 *  - (UART_EVEN_PARITY_REPR_0)- signifying that even parity is enabled and the
 *     parity bit is represented by a logic 0\n
 *  - (UART_PARITY_NONE) - signifying that no parity is enabled\n
 *
 */
uint32_t  AM335x_UART::parity_mode_get()
{
    //return (HWREG(baseAdd + UART_LCR) & (UART_LCR_PARITY_TYPE2 |
    //                                     UART_LCR_PARITY_TYPE1 |
    //                                     UART_LCR_PARITY_EN));
    return (m_UART_regs.LCR.reg & (n_UART::LCR_PARITY_EN | 
                                   n_UART::LCR_PARITY_TYPE1 |
                                   n_UART::LCR_PARITY_TYPE2));
}

n_UART::e_UART_INSTANCE_NUM  AM335x_UART::get_UART_inst_number()
{
    uint32_t UART_inst = (uint32_t)&m_UART_regs;
     
    switch(UART_inst)
    {
        case n_UART::AM335x_UART_0_BASE:     
            return n_UART::UART_INSTANCE_0;
        case n_UART::AM335x_UART_1_BASE:     
            return n_UART::UART_INSTANCE_1;
        case n_UART::AM335x_UART_2_BASE:     
            return n_UART::UART_INSTANCE_2;
        case n_UART::AM335x_UART_3_BASE:     
            return n_UART::UART_INSTANCE_3;
        case n_UART::AM335x_UART_4_BASE:     
            return n_UART::UART_INSTANCE_4;
        case n_UART::AM335x_UART_5_BASE:     
            return n_UART::UART_INSTANCE_5;
        default:
            break;
    } 
    
    return n_UART::UART_INSTANCE_NA;
}
 
 INTC::e_SYS_INTERRUPT  AM335x_UART::get_UART_sys_interrupt()
{
   uint32_t UART_inst = (uint32_t)&m_UART_regs;
     
    switch(UART_inst)
    {
        case n_UART::AM335x_UART_0_BASE:     
            return INTC::UART0INT;
        case n_UART::AM335x_UART_1_BASE:     
            return INTC::UART1INT;
        case n_UART::AM335x_UART_2_BASE:     
            return INTC::UART2INT;
        case n_UART::AM335x_UART_3_BASE:     
            return INTC::UART3INT;
        case n_UART::AM335x_UART_4_BASE:     
            return INTC::UART4INT;
        case n_UART::AM335x_UART_5_BASE:     
            return INTC::UART5INT;
        default:
            break;
    } 
    
    return INTC::INTERRUPTS_NUM_MAX;
}

/**
 * \brief  This API enables the DMA mode of operation for the UART instance.
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  dma_mode_flag  This specifies the DMA mode to be enabled for the
 *                       UART instance.
 *
 * 'dma_mode_flag' can take one of the following four values:
 * - UART_DMA_MODE_0_ENABLE - to enable DMA Mode 0(No DMA)\n
 * - UART_DMA_MODE_1_ENABLE - to enable DMA Mode 1(DMA for both TX and RX)\n
 * - UART_DMA_MODE_2_ENABLE - to enable DMA Mode 2(DMA only for RX)\n
 * - UART_DMA_MODE_3_ENABLE - to enable DMA Mode 3(DMA only for TX)\n
 *
 * \return  None
 *
 * \note   This API enables the specified DMA modes always in SCR and FCR is
 *         not used. This is because SCR[2:1] allows the program to enable any
 *         of the four available DMA modes while FCR[3] allows the program to
 *         use either DMA Mode 0 or DMA Mode 1.\n
 */
void  AM335x_UART::DMA_enable(n_UART::e_SCR_DMA_MODE dma_mode_flag)
{
    //HWREG(baseAdd + UART_SCR) |= (UART_SCR_DMA_MODE_CTL);   // Setting the DMAMODECTL bit in SCR to 1.    
    //HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_DMA_MODE_2);    // Clearing the DMAMODE2 field in SCR.    
    //HWREG(baseAdd + UART_SCR) |= ((dma_mode_flag << UART_SCR_DMA_MODE_2_SHIFT) & UART_SCR_DMA_MODE_2);  // Programming the DMAMODE2 field in SCR.
    m_UART_regs.SCR.b.DMAMODECTL = HIGH;            // Setting the DMAMODECTL bit in SCR to 1.
    m_UART_regs.SCR.b.DMAMODE2 = 0x0;               // Clearing the DMAMODE2 field in SCR.
    m_UART_regs.SCR.b.DMAMODE2 = dma_mode_flag;     // Programming the DMAMODE2 field in SCR.
}

/**
 * \brief  This API disables the DMA mode of operation.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return None
 */
void  AM335x_UART::DMA_disable()
{
    // HWREG(baseAdd + UART_SCR) |= (UART_SCR_DMA_MODE_CTL);    
    // HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_DMA_MODE_2);    // Programming DMAMODE2 field of SCR to DMA mode 0.
    m_UART_regs.SCR.b.DMAMODECTL = HIGH;
    m_UART_regs.SCR.b.DMAMODE2 = 0x0;
}

/**
 * \brief  This API is used to write a specified value to the FIFO Control
 *         Register(FCR).
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  fcrValue    This specifies the value to be written to the
 *                     FCR.
 *
 * 'fcrValue' can be determined using a parameterized macro named
 * 'UART_FCR_PROGRAM'.
 * The parameters of 'UART_FCR_PROGRAM' are described below:
 * - rxFIFOTrig - specifies the Receiver FIFO Trigger Level\n
 * - txFIFOTrig - specifies the Transmitter FIFO Trigger Level\n
 * - dmaMode - specifies the DMA Mode of operation to be selected:\n
 *   Write 0 - for DMA Mode 0\n
 *         1 - for DMA Mode 1\n
 * - txClr - specifies whether or not to clear the Transmitter FIFO
 *   and resetting the counter logic to 0.\n
 * - rxClr - specifies whether or not to clear the Receiver FIFO and resetting
 *   the counter logic to 0.
 * - fifoEn - specifies whether to enable the FIFO mode for the UART or not\n
 *   0 - to enable Non-FIFO mode of operation\n
 *   1 - to enable FIFO mode of operation\n
 *
 * \return  None
 *
 * \note  1> The FIFO_EN and DMA_MODE bits of FCR can be written to only when
 *           the Baud Clock is not running(DLL and DLH register are cleared
 *           to 0). Modifying DLL and DLH registers in turn requires that the
 *           UART be operated in Disabled Mode(MDR1[2:0] = 0x7).\n
 *        2> Writing to 'TX_FIFO_TRIG' field in FCR requires that the
 *           ENHANCEDEN bit in EFR(EFR[4]) be set to 1.\n
 *        Prior to writing to the FCR, this API does the above two operations.
 *        It also restores the respective bit values after FCR has been
 *        written to.\n
 */
void  AM335x_UART::FIFO_register_write(n_UART::FCR_reg_t  cfg_fcr)
{
    uint32_t div_latch_reg_val = 0;
    uint32_t enhan_fn_bit_val = 0;
    uint32_t LCR_reg_value = 0;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_A);      // Switching to Register Configuration Mode A of operation.
    div_latch_reg_val = divisor_latch_write(0x0000);                    // Clearing the contents of Divisor Latch Registers.
    
    enhan_fn_bit_val = enhan_func_enable();                             // Set the EFR[4] bit to 1.
    
    m_UART_regs.FCR.reg = cfg_fcr.reg;                                  // Writing the 'cfg_fcr' to the FCR register.
    
    enhan_func_bit_val_restore(enhan_fn_bit_val);                       // Restoring the value of EFR[4] to its original value.    
    divisor_latch_write(div_latch_reg_val);                             // Programming the Divisor Latch Registers with the collected value.
    
    m_UART_regs.LCR.reg = LCR_reg_value;                                // Reinstating LCR with its original value.
}

/**
 * \brief  This API sets a certain bit in Enhanced Feature Register(EFR) which
 *         shall avail the UART to use some Enhanced Features.
 *
 * \param  baseAdd    Memory address of the UART instance being used.
 * 
 * \return The value of ENHANCEDEN bit in EFR before it is modified in this API.
 *
 * \note   This API switches UART to Configuration Mode B, sets the ENHANCEDEN
 *         bit in EFR and reverts the UART back to the original mode of
 *         operation.
 *
 */
uint32_t  AM335x_UART::enhan_func_enable()
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t LCR_reg_value = 0;

    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);      // Enabling Configuration Mode B of operation.
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN; 
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;
    m_UART_regs.LCR.reg = LCR_reg_value;                    // Programming LCR with the collected value.

    return enhan_fn_bit_val;
}

/**
 * \brief  This API restores the ENHANCEDEN bit value of EFR register(EFR[4])
 *         to the corresponding bit value in 'enhan_fn_bit_val' passed as a
 *         parameter to this API.
 *
 * \param  baseAdd        Memory address of the UART instance being used.
 * \param  enhan_fn_bit_val  The 4th bit of this 32-bit value shall hold a value
 *                        to which the ENHANCEDEN bit of EFR (EFR[4]) has to
 *                        be restored to.
 * 
 * \return None.
 *
 * \note   The APIs UARTEnhanFuncEnable() and the current one are used
 *         hand-in-hand. While UARTEnhanFuncEnable() collects the EFR[4] bit
 *         value before modifying it, UARTEnhanFuncBitValRestore() can be used
 *         to restore EFR[4] bit value after the necessary operation is complete.
 *         This API switches the UART to Configuration Mode B, does the needful
 *         and reverts it back to original mode of operation.
 *
 */
void  AM335x_UART::enhan_func_bit_val_restore(bool enhan_fn_bit_val)
{
    uint32_t LCR_reg_value = 0;

    // Enabling Configuration Mode B of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);

    // Restoring the value of EFR[4].
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;
    
    m_UART_regs.LCR.reg = LCR_reg_value;  // Programming LCR with the collected value.
}


/**
 * \brief  This API enables the MSR_SPR Sub-Configuration Mode of operation.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return The value of the TCRTLR bit in MCR (MCR[6]) before it is modified
 *         in this API.
 *
 * \note   1> Each Register configuration mode(A, B and operational) has
 *            further sub-configuration modes corresponding to accesses to
 *            offset addresses 0x18 and 0x1C. They are:\n
 *            For Register Configuration Mode A:\n
 *            1> MSR_SPR:  EFR[4] = 0  or MCR[6] = 0\n
 *            2> TCR_TLR:  EFR[4] = 1 and MCR[6] = 1\n
 *            For Register Configuration Mode B:\n
 *            1> TCR_TLR - EFR[4] = 1 and MCR[6] = 1\n
 *            2> XOFF    - EFR[4] = 0 or  MCR[6] = 0\n
 *
 *            For Register Operational Mode:\n
 *            1> MSR_SPR - EFR[4] = 0 or  MCR[6] = 0\n
 *            2> TCR_TLR - EFR[4] = 1 and MCR[6] = 1\n
 *
 *            In any configuration mode, enabling one of the sub-configuration
 *            mode would disable access to the registers of the other
 *            sub-configuration mode.\n
 *
 *         2> The current API enables access to Modem Status Register(MSR) and
 *            Scratch Pad Register(SPR). This is applicable for Register
 *            Configuration Mode A and Operational mode of operation.\n
 */
uint32_t  AM335x_UART::sub_config_MSRSPR_mode_en()
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t TCR_TLR_value = 0;
    uint32_t LCR_reg_value = 0;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Configuration Mode B of operation. 

    // Collecting the current value of EFR[4] and later setting it. 
    //enhan_fn_bit_val = HWREG(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN;
    // HWREG(baseAdd + UART_EFR) |= UART_EFR_ENHANCED_EN;
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;    
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_A);                  // Switching to Configuration Mode A of operation.    
    //TCR_TLR_value = (HWREG(baseAdd + UART_MCR) & UART_MCR_TCR_TLR);   // Collecting the bit value of MCR[6].
    TCR_TLR_value = m_UART_regs.MCR.b.TCRTLR;   // Collecting the bit value of MCR[6].
    
    // HWREG(baseAdd + UART_MCR) &= ~(UART_MCR_TCR_TLR);    // Clearing the TCRTLR bit in MCR register.
    m_UART_regs.MCR.b.TCRTLR = 0x0;                         // Clearing the TCRTLR bit in MCR register.
    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Configuration Mode B of operation.

    // Restoring the value of EFR[4]. 
    // HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_ENHANCED_EN);
    // HWREG(baseAdd + UART_EFR) |= enhan_fn_bit_val;
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;
    
    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR.
    m_UART_regs.LCR.reg = LCR_reg_value;    // Restoring the value of LCR.

    return TCR_TLR_value;
}

/**
 * \brief  This API enables the TCR_TLR Sub_Configuration Mode of operation.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return The value of the TCRTLR bit in MCR (MCR[6]) before it is modified
 *         in this API.
 *
 * \note   The current API enables access to Transmission Control Register(TCR)
 *         and Trigger Level Register(TLR). This is applicable for all the
 *         three register configuration modes.
 *         Refer to the comments of UARTSubConfigMSRSPRModeEn() API for more
 *         details.
 */
uint32_t  AM335x_UART::sub_config_TCRTLR_mode_en()
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t TCR_TLR_value = 0;
    uint32_t LCR_reg_value = 0;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the current value of EFR[4] and later setting it.    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Register Configuration Mode A.
    
    TCR_TLR_value = m_UART_regs.MCR.b.TCRTLR;       // Collecting the bit value of MCR[6].
    
    m_UART_regs.MCR.b.TCRTLR = HIGH;                // Setting the TCRTLR bit in Modem Control Register(MCR).
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Restoring the value of EFR[4] to its original value.
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;
     
    m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return TCR_TLR_value;
}

/**
 * \brief  This API enables the XOFF Sub-Configuration Mode of operation.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return The value of the TCRTLR bit in MCR (MCR[6]) before it is modified
 *         in this API.
 *
 * \note   The current API enables access to the XOFF (XOFF1 and XOFF2)
 *         registers. The XOFF registers can be accessed in Register
 *         Configuration Mode B of operation.
 *         Refer to the comments of UARTSubConfigMSRSPRModeEn() API for more
 *         details.
 */
uint32_t  AM335x_UART::sub_config_XOFF_mode_en()
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t TCR_TLR_value = 0;
    uint32_t LCR_reg_value = 0;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the current value of EFR[4] and later setting it.
    //enhan_fn_bit_val = HWREG(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN;
    //HWREG(baseAdd + UART_EFR) |= UART_EFR_ENHANCED_EN;    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Configuration Mode A of operation.
    
    // TCR_TLR_value = (HWREG(baseAdd + UART_MCR) & UART_MCR_TCR_TLR); // Collecting the bit value of TCRTLR(MCR[6]).
    TCR_TLR_value = m_UART_regs.MCR.b.TCRTLR;       // Collecting the bit value of TCRTLR(MCR[6]).
    
    // HWREG(baseAdd + UART_MCR) &= ~(UART_MCR_TCR_TLR);   // Clearing the TCRTLR bit in MCR register.
    m_UART_regs.MCR.b.TCRTLR = 0;   // Clearing the TCRTLR bit in MCR register.
    
    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.
    
    // Restoring the value of EFR[4] to its original value.
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_ENHANCED_EN);
    //HWREG(baseAdd + UART_EFR) |= enhan_fn_bit_val;
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return TCR_TLR_value;
}

/**
 * \brief  This API restores the TCRTLR bit(MCR[6]) value in Modem Control
 *         Register(MCR) to the corresponding bit value in 'tcr_tlr_bit_val' 
 *         passed as a parameter to this API.
 *
 * \param  baseAdd       Memory address of the UART instance being used.
 * \param  tcr_tlr_bit_val  The 6th bit in this 32-bit value shall hold a value
 *                       to which the TCRTLR bit(MCR[6]) of MCR has to be
 *                       restored to.
 *
 * \return None.
 */
void  AM335x_UART::TCRTLR_bit_val_restore(uint32_t tcr_tlr_bit_val)
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t LCR_reg_value = 0;

    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the current value of EFR[4] and later setting it.    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;

    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Configuration Mode A of operation.

    // Programming MCR[6] with the corresponding bit value in 'tcr_tlr_bit_val'.
    m_UART_regs.MCR.b.TCRTLR = 0;
    m_UART_regs.MCR.b.TCRTLR = tcr_tlr_bit_val;    

    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Restoring the value of EFR[4] to its original value.
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief   This API enables the specified interrupts in the UART mode of
 *          operation.
 *
 * \param   baseAdd   Memory address of the UART instance being used.
 * \param   int_flag   Bit mask value of the bits corresponding to Interrupt
 *                    Enable Register(IER). This specifies the UART interrupts
 *                    to be enabled.
 *
 *  'int_flag' can take one or a combination of the following macros:
 *  - UART_INT_CTS - to enable Clear-To-Send interrupt,
 *  - UART_INT_RTS - to enable Request-To-Send interrupt,
 *  - UART_INT_XOFF - to enable XOFF interrupt,
 *  - UART_INT_SLEEPMODE - to enable Sleep Mode,
 *  - UART_INT_MODEM_STAT - to enable Modem Status interrupt,
 *  - UART_INT_LINE_STAT - to enable Line Status interrupt,
 *  - UART_INT_THR - to enable Transmitter Holding Register Empty interrupt,
 *  - UART_INT_RHR_CTI - to enable Receiver Data available interrupt and
 *                       Character timeout indication interrupt.
 * 
 * \return  None.
 *
 * \note    This API modifies the contents of UART Interrupt Enable Register
 *          (IER). Modifying the bits IER[7:4] requires that EFR[4] be set.
 *          This API does the needful before it accesses IER.
 *          Moreover, this API should be called when UART is operating in
 *          UART 16x Mode, UART 13x Mode or UART 16x Auto-baud mode.\n
 *
 */
void  AM335x_UART::int_enable(uint32_t int_flag)
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t LCR_reg_value = 0;

    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the current value of EFR[4] and later setting it.
    //enhan_fn_bit_val = HWREG(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN;
    //HWREG(baseAdd + UART_EFR) |= UART_EFR_ENHANCED_EN;    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;

    /* Switching to Register Operational Mode of operation. */
    reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    /*
    ** It is suggested that the System Interrupts for UART in the
    ** Interrupt Controller are enabled after enabling the peripheral
    ** interrupts of the UART using this API. If done otherwise, there
    ** is a risk of LCR value not getting restored and illicit characters
    ** transmitted or received from/to the UART. The situation is explained
    ** below.
    ** The scene is that the system interrupt for UART is already enabled and
    ** the current API is invoked. On enabling the interrupts corresponding
    ** to IER[7:4] bits below, if any of those interrupt conditions
    ** already existed, there is a possibility that the control goes to
    ** Interrupt Service Routine (ISR) without executing the remaining
    ** statements in this API. Executing the remaining statements is
    ** critical in that the LCR value is restored in them.
    ** However, there seems to be no risk in this API for enabling interrupts
    ** corresponding to IER[3:0] because it is done at the end and no
    ** statements follow that.
    */

    /************* ATOMIC STATEMENTS START *************************/
    
    //HWREG(baseAdd + UART_IER) |= (int_flag & 0xF0); // Programming the bits IER[7:4].
    m_UART_regs.IER_UART.reg |= (int_flag & 0xF0);

    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Restoring the value of EFR[4] to its original value.
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_ENHANCED_EN);
    //HWREG(baseAdd + UART_EFR) |= enhan_fn_bit_val;
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    /************** ATOMIC STATEMENTS END *************************/    
    //HWREG(baseAdd + UART_IER) |= (int_flag & 0x0F); // Programming the bits IER[3:0].
     m_UART_regs.IER_UART.reg |= (int_flag & 0x0F);
}

/**
 * \brief   This API disables the specified interrupts in the UART mode of
 *          operation.
 *
 * \param   baseAdd   Memory address of the UART instance being used.
 * \param   int_flag   Bit mask value of the bits corresponding to Interrupt
 *                    Enable Register(IER). This specifies the UART interrupts
 *                    to be disabled.
 *
 *  'int_flag' can take one or a combination of the following macros:
 *  - UART_INT_CTS - to disable Clear-To-Send interrupt,
 *  - UART_INT_RTS - to disable Request-To-Send interrupt,
 *  - UART_INT_XOFF - to disable XOFF interrupt,
 *  - UART_INT_SLEEPMODE - to disable Sleep Mode,
 *  - UART_INT_MODEM_STAT - to disable Modem Status interrupt,
 *  - UART_INT_LINE_STAT - to disable Line Status interrupt,
 *  - UART_INT_THR - to disable Transmitter Holding Register Empty interrupt,
 *  - UART_INT_RHR_CTI - to disable Receiver Data available interrupt and
 *                       Character timeout indication interrupt.
 *
 * \return  None
 *
 * \note  The note section of UARTIntEnable() also applies to this API.
 */
void  AM335x_UART::int_disable(uint32_t int_flag)
{
    uint32_t enhan_fn_bit_val = 0;
    uint32_t LCR_reg_value = 0;

    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the current value of EFR[4] and later setting it.
    //enhan_fn_bit_val = HWREG(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN;
    //HWREG(baseAdd + UART_EFR) |= UART_EFR_ENHANCED_EN;    
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;

    /* Switching to Register Operational Mode of operation. */
    reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    //HWREG(baseAdd + UART_IER) &= ~(int_flag & 0xFF);
    m_UART_regs.IER_UART.reg &= ~(int_flag & 0xFF);

    reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Restoring the value of EFR[4] to its original value.
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_ENHANCED_EN);
    //HWREG(baseAdd + UART_EFR) |= enhan_fn_bit_val;
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief  This API checks whether the TX FIFO (or THR in non-FIFO mode)
 *         is empty or not.
 *
 * \param  baseAdd    Memory address of the UART instance being used.
 *
 * \return HIGH - if the Transmitter FIFO(or THR in non-FIFO mode) is empty.
 *         LOW - if the Transmitter FIFO(or THR in non-FIFO mode) is
 *         not empty.\n
 */
uint32_t  AM335x_UART::space_avail()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = LOW;

    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    /*
    ** Checking if either TXFIFOE or TXSRE bits of Line Status Register(LSR)
    ** are set. TXFIFOE bit is set if TX FIFO(or THR in non-FIFO mode) is
    ** empty. TXSRE is set if both the TX FIFO(or THR in non-FIFO mode) and
    ** the transmitter shift register are empty.
    */

    //if(HWREG(baseAdd + UART_LSR) & (UART_LSR_TX_SR_E | UART_LSR_TX_FIFO_E))
    if(m_UART_regs.LSR_UART.b.TXSRE | m_UART_regs.LSR_UART.b.TXFIFOE)
        ret_val = HIGH;


    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API checks if the RX FIFO (or RHR in non-FIFO mode) has atleast
 *         one byte of data to be read.
 * 
 * \param  baseAdd    Memory address of the UART instance being used.
 *
 * \return  HIGH - if there is atleast one data byte present in the RX FIFO
 *          (or RHR in non-FIFO mode)\n
 *          LOW - if there are no data bytes present in the RX FIFO(or RHR
 *           in non-FIFO mode)\n
 */
uint32_t  AM335x_UART::chars_avail()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = LOW;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);   // Switching to Register Operational Mode of operation.
    
    //if(HWREG(baseAdd + UART_LSR) & UART_LSR_RX_FIFO_E) // Checking if the RHR(or RX FIFO) has atleast one byte to be read.
    if(m_UART_regs.LSR_UART.b.RXFIFOE)  // Checking if the RHR(or RX FIFO) has atleast one byte to be read.
        ret_val = HIGH;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief    This API attempts to write a byte into Transmitter Holding
 *           Register (THR). It checks only once if the transmitter is empty.
 *
 * \param    baseAdd     Memory address of the UART instance being used.
 * \param    byte_write   Byte to be written into the THR register.
 *
 * \return   HIGH if the transmitter FIFO(or THR register in non-FIFO mode)
 *           was empty and the character was written. Else it returns LOW.
 */
uint32_t  AM335x_UART::char_put_non_blocking(uint8_t byte_write)
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = LOW;
    
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);   // Switching to Register Operational Mode of operation.

    // Checking if either THR alone or both THR and Transmitter Shift Register are empty.
    //if(HWREG(baseAdd + UART_LSR) & (UART_LSR_TX_SR_E | UART_LSR_TX_FIFO_E))
    if(m_UART_regs.LSR_UART.b.TXSRE | m_UART_regs.LSR_UART.b.TXFIFOE)
    {
        //HWREG(baseAdd + UART_THR) = byte_write;
        m_UART_regs.THR.b.THR = byte_write;
        ret_val = HIGH;
    }

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;         // Restoring the value of LCR.
    
    return ret_val;
}


/**
 * \brief    This API reads a byte from the Receiver Buffer Register
 *           (RBR). It checks once if any character is ready to be read.
 *
 * \param    baseAdd     Memory address of the UART instance being used.
 *
 * \return   If the RX FIFO(or RHR) was found to have atleast one byte of
 *           data, then this API reads and returns that byte. Else it
 *           returns -1.
 */
char  AM335x_UART::char_get_non_blocking()
{
    uint32_t  LCR_reg_value = 0;
        char  ret_val = -1;

    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    // Checking if the RX FIFO(or RHR) has atleast one byte of data.
    //if(HWREG(baseAdd + UART_LSR) & UART_LSR_RX_FIFO_E)
    if(m_UART_regs.LSR_UART.b.RXFIFOE)
    {
        //ret_val = (char)HWREG(baseAdd + UART_RHR);
        ret_val = (char)m_UART_regs.RHR.b.RHR;
    }

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief    This API waits indefinitely for the arrival of a byte in
 *           the receiver FIFO. Once a byte has arrived, it returns that
 *           byte.
 *
 * \param    baseAdd     Memory address of the UART instance being used.
 *
 * \return   This returns the read byte.
 */
char  AM335x_UART::char_get()
{
    uint32_t  LCR_reg_value = 0;
        char  ret_val = 0;
    
    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    // Waits indefinitely until a byte arrives in the RX FIFO(or RHR).
    //while(0 == (HWREG(baseAdd + UART_LSR) & UART_LSR_RX_FIFO_E));
    while(m_UART_regs.LSR_UART.b.RXFIFOE == 0)

    //ret_val = ((char)HWREG(baseAdd + UART_RHR));
      ret_val = (char)m_UART_regs.RHR.b.RHR;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR.    
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief   This API waits for the arrival of atleast one byte into the
 *          Receiver FIFO or until a specified timeout value gets decremented
 *          to zero, whichever happens first.
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 * \param   time_out_val  The timeout value that is to be used. This timeout
 *                      value gets decremented once per iteration of the
 *                      wait loop.
 *
 * \return  This returns either of the below two values:\n
 *          1) If a character was keyed in before the timeout value gets
 *             decremented to zero, this API returns the entered byte.\n
 *          2) If no character was input within the timeout value getting
 *             decremented to zero, this API returns -1.\n
 */
int  AM335x_UART::char_get_timeout(uint32_t time_out_val)
{
    uint32_t LCR_reg_value = 0;
    int ret_val = -1;
    
    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    // Wait until either data is not received or the time out value is greater 
    //while((0 == (HWREG(baseAdd + UART_LSR) & UART_LSR_RX_FIFO_E)) && time_out_val)
    while((0 == m_UART_regs.LSR_UART.b.RXFIFOE) &&
          time_out_val)
    {
        time_out_val--;
    }

    if(time_out_val)
    {
        //ret_val = (HWREG(baseAdd + UART_RHR)) & 0x0FF;
        ret_val = m_UART_regs.RHR.b.RHR & 0x0FF;
    }

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;         // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief   This API waits indefinitely until the Transmitter FIFO
 *          (THR register in non-FIFO mode) and Transmitter Shift
 *          Register are empty. On empty, it writes a byte to the THR.
 *
 * \param   baseAdd     Memory address of the UART instance being used
 * \param   byte_tx      The byte to be transmitted by the UART.
 *
 * \return  None
 */
void  AM335x_UART::char_put(uint8_t byte_tx)
{
    uint32_t LCR_reg_value = 0;

    // Switching to Register Operational Mode of operation. 
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    // Waits indefinitely until the THR and Transmitter Shift Registers are empty.
    //while((UART_LSR_TX_SR_E | UART_LSR_TX_FIFO_E) !=
    //      (HWREG(baseAdd + UART_LSR) & (UART_LSR_TX_SR_E | UART_LSR_TX_FIFO_E)));

    //HWREG(baseAdd + UART_THR) = byte_tx;
    
    while(!m_UART_regs.LSR_UART.b.TXSRE  ||
          !m_UART_regs.LSR_UART.b.TXFIFOE);
    
    m_UART_regs.THR.b.THR = byte_tx;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief   This API writes a byte to the Transmitter FIFO without checking for
 *          the emptiness of the Transmitter FIFO or the Transmitter Shift
 *          Register(TSR).
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 * \param   byte_tx      The byte to be transmitted by the UART.
 *
 * \return  None
 *
 * \note    Unlike the APIs UARTCharPut() or UARTCharPutNonBlocking(), this
 *          API does not check for the emptiness of the TX FIFO or TSR. This
 *          API is ideal for use in FIFO mode of operation where the 64-byte
 *          TX FIFO has to be written with successive bytes. If transmit
 *          interrupt is enabled, it provides a mechanism to control the
 *          writes to the TX FIFO.
 */
void  AM335x_UART::FIFO_char_put(uint8_t byte_tx)
{
    //HWREG(baseAdd + UART_THR) = byte_tx;  // Write the byte to the Transmit Holding Register(or TX FIFO).
    m_UART_regs.THR.b.THR = byte_tx;        // Write the byte to the Transmit Holding Register(or TX FIFO).
}

/**
 * \brief   This API reads the data present at the top of the RX FIFO, that
 *          is, the data in the Receive Holding Register(RHR). However
 *          before reading the data from RHR, it does not check whether
 *          RHR has fresh data or not.
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 *
 * \return  The data read from the RHR.
 *
 * \note    1) Since this API does not check whether RX FIFO(RHR) has fresh
 *             data before reading the same, the application should ensure
 *             that RX FIFO has data before calling this API. The API
 *             UARTCharsAvail() can be used to check if the RX FIFO has
 *             atleast one byte of data.\n
 *          2) If the RX FIFO did not have any fresh data and this API is
 *             called, this API would return an unknown value.\n
 */
char  AM335x_UART::FIFO_char_get()
{
    //return (HWREG(baseAdd + UART_RHR));
  return  (char)m_UART_regs.RHR.b.RHR;
}

/**
 * \brief  This API copies the requested amount of data from the
 *         pointed data block to the UART Transmit FIFO.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  pBuffer     The starting address of the data block.
 * \param  num_tx_bytes  The number of data bytes to be transmitted.
 *
 * \return The number of data bytes that were written to the TX FIFO.
 *
 * \note   This API does not check for the emptiness of the TX FIFO or for
 *         its space availability before writing to it. The application
 *         calling this API has the responsibility of checking the TX
 *         FIFO status before using this API.\n
 */
uint32_t  AM335x_UART::FIFO_write(uint8_t *p_Buf, uint32_t num_tx_bytes)
{
    uint32_t l_index = 0;

    // Writing data to the TX FIFO.
    for(l_index = 0; l_index < num_tx_bytes; l_index++)
    {        
        //HWREG(baseAdd + UART_THR) = *p_Buf++;
        m_UART_regs.THR.b.THR = *p_Buf++;
    }

    return l_index;
}

/**
 * \brief  This API reads the receiver data error status. 
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 *
 * \return This returns the error status. This can be one or a combination 
 *         of the below values:
 *         - UART_OVERRUN_ERROR - indicating Overrun error occured\n
 *         - UART_PARITY_ERROR - indicating Parity error occured\n
 *         - UART_FRAMING_ERROR - indicating Framing error occured\n
 *         - UART_BREAK_DETECTED_ERROR - indicating a Break condition was
 *           detected\n
 *         - UART_FIFO_PE_FE_BI_DETECTED - indicating that atleast one parity
 *           error, framing error or a break indication is present in the
 *           RX FIFO\n
 */
uint32_t  AM335x_UART::RX_error_get()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = 0;
    
    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    //ret_val = (HWREG(baseAdd + UART_LSR) & (UART_LSR_RX_FIFO_STS |
    //                                        UART_LSR_RX_BI |
    //                                        UART_LSR_RX_FE |
    //                                        UART_LSR_RX_PE |
    //                                        UART_LSR_RX_OE));
    ret_val = (m_UART_regs.LSR_UART.reg & (n_UART::ERR_RX_OVERRUN |
                                          n_UART::ERR_RX_PARITY |
                                          n_UART::ERR_RX_FRAMING |
                                          n_UART::ERR_RX_BRAK_COND |
                                          n_UART::ERR_RX_FIFO));
 

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API determines the UART Interrupt Status.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 * 
 * \return This returns one or a combination of the following macros:
 *         - UART_INTID_MODEM_STAT - indicating the occurence of a Modem Status
 *           interrupt\n
 *         - UART_INTID_TX_THRES_REACH - indicating that the TX FIFO Threshold
 *           number of bytes can be written to the TX FIFO.
 *         - UART_INTID_RX_THRES_REACH - indicating that the RX FIFO has
 *           reached its programmed Trigger Level\n
 *         - UART_INTID_RX_LINE_STAT_ERROR - indicating the occurence of a
 *           receiver Line Status error\n
 *         - UART_INTID_CHAR_TIMEOUT - indicating the occurence of a Receiver
 *           Timeout\n
 *         - UART_INTID_XOFF_SPEC_CHAR_DETECT - indicating the detection of XOFF
 *           or a Special character\n
 *         - UART_INTID_MODEM_SIG_STATE_CHANGE - indicating that atleast one of
 *           the Modem signals among CTSn, RTSn and DSRn have changed states
 *           from active(low) to inactive(high)\n
 */
uint32_t  AM335x_UART::int_identity_get()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = 0;
    
    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    //ret_val = (HWREG(baseAdd + UART_IIR) & UART_IIR_IT_TYPE);
    ret_val = m_UART_regs.IIR_UART.b.IT_TYPE;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API determines whether any UART interrupt condition is
 *         still alive and is pending to be serviced.
 * 
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return UART_INT_PENDING - if servicing an interrupt is still pending\n
 *         UART_N0_INT_PENDING - if there are no interrupts to be serviced\n
 */
bool  AM335x_UART::int_pending_status_get()
{
    bool ret_val = true;
    uint32_t LCR_reg_value = 0;

    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    // Checking if an Interrupt is pending.
    //if(!(HWREG(baseAdd + UART_IIR) & UART_IIR_IT_PENDING))
    if(!m_UART_regs.IIR_UART.b.IT_PENDING)
        ret_val = false;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API determines whether FIFO mode of operation is enabled
 *         for the UART instance or not.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 *
 * \return HIGH - if FIFO mode of operation is enabled\n
 *         LOW - if FIFO mode of operation is disabled\n
 */
bool  AM335x_UART::FIFO_enable_status_get()
{
    uint32_t LCR_reg_value = 0;
        bool ret_val = false;

    // Switching to Register Operational Mode of operation.
    LCR_reg_value = reg_config_mode_enable(n_UART::OPERATIONAL_MODE);

    //if(HWREG(baseAdd + UART_IIR) & UART_IIR_FCR_MIRROR)
    if(m_UART_regs.IIR_UART.b.FCR_MIRROR)
        ret_val = true;
    
    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API controls the use of Auto-RTS and Auto-CTS features which
 *         are used in Hardware Flow Control Mode of operation. The
 *         Auto-RTS and Auto-CTS functions can be individually enabled or
 *         disabled.
 *     
 * \param  baseAdd         Memory address of the UART instance being used.
 * \param  auto_cts_control  This specifies whether to enable or disable
 *                         Auto-CTS functionality
 * \param  auto_rts_control  This specifies whether to enable or disable
 *                         Auto-RTS functionality
 *
 * 'autoCtsControl' can take one of the following values:
 * - UART_AUTO_CTS_DISABLE - to disable Auto-CTS functionality\n
 * - UART_AUTO_CTS_ENABLE - to enable Auto-CTS functionality\n
 *
 * 'auto_rts_control' can take either of the following values:
 * - UART_AUTO_RTS_DISABLE - to disable Auto-RTS functionality\n
 * - UART_AUTO_RTS_ENABLE - to enable Auto-RTS functionality\n
 *
 * \return None.
 *
 * \note   This API switches UART to Configuration Mode B, programs
 *         AUTOCTSEN and AUTORTSEN bits in EFR and reverts the UART back
 *         to the original mode of operation.
 */
void  AM335x_UART::auto_RTS_auto_CTS_control(uint32_t auto_cts_control, uint32_t auto_rts_control)
{
    uint32_t LCR_reg_value = 0;     
 
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.
    
    // Clearing AUTOCTSEN and AUTORTSEN bits in EFR
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_AUTO_CTS_EN |
    //                               UART_EFR_AUTO_RTS_EN);
    m_UART_regs.EFR.b.AUTOCTSEN = 0;
    m_UART_regs.EFR.b.AUTORTSEN = 0;
    
    // Programming AUTOCTSEN and AUTORTSEN bits in EFR.
    //HWREG(baseAdd + UART_EFR) |= (auto_cts_control & UART_EFR_AUTO_CTS_EN);
    //HWREG(baseAdd + UART_EFR) |= (auto_rts_control & UART_EFR_AUTO_RTS_EN);
    m_UART_regs.EFR.b.AUTOCTSEN = auto_cts_control;
    m_UART_regs.EFR.b.AUTORTSEN = auto_rts_control;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief  This API controls the feature of detecting a Special Character
 *         arriving in the receiver.
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 * \param   control_flag This specifies whether to enable or disable detection
 *                      of Special Character.
 *
 * 'control_flag' can take either of the following two values:\n
 * - UART_SPECIAL_CHAR_DETECT_DISABLE - to disable detection of Special
 *   Character\n
 * - UART_SPECIAL_CHAR_DETECT_ENABLE - to enable detection of Special
 *   Character\n
 *
 * \return  None.
 *
 * \note   This API switches the UART to Configuration Mode B, programs
 *         SPECIALCHARDETECT field in EFR and reverts the UART back to
 *         the original mode of operation.  
 *
 */
void  AM335x_UART::special_char_detect_control(uint32_t control_flag)
{
    uint32_t LCR_reg_value = 0;     
 
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_SPECIAL_CHAR_DETECT);
    m_UART_regs.EFR.b.SPECIALCHARDETECT = 0;

    // Programming the SPECIALCHARDETECT bit in EFR. 
    //HWREG(baseAdd + UART_EFR) |= (control_flag & UART_EFR_SPECIAL_CHAR_DETECT);
    m_UART_regs.EFR.b.SPECIALCHARDETECT = control_flag;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief  This API configures the options for Software Flow Control.
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  sw_flow_ctrl   This specifies one of the options available for
 *                      software flow control.
 *
 * 'sw_flow_ctrl' can take one of the following values:
 * - UART_NO_SOFTWARE_FLOW_CONTROL - To disable Software Flow control\n
 * - UART_TX_RX_XON1_XOFF1 - Transmitter transmits XON1, XOFF1;
 *                           Receiver expects XON1, XOFF1\n
 * - UART_TX_RX_XON2_XOFF2 - Transmitter transmits XON2, XOFF2;
 *                           Receiver expects XON2, XOFF2\n
 * - UART_TX_RX_XON1_XOFF1_XON2_XOFF2 - Transmitter transmits XON1,XON2,
 *                           XOFF1 and XOFF2; Receiver expects XON1,XON2,
 *                           XOFF1, XOFF2\n
 *
 * \return None.
 * 
 * \note   This API switches the UART to Configuration Mode B, programs
 *         SWFLOWCONTROL field in EFR and reverts the UART back to the
 *         original mode of operation.
 */
void  AM335x_UART::software_flow_ctrl_opt_set(uint32_t sw_flow_ctrl)
{
    uint32_t LCR_reg_value = 0;
 
    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Clearing the SWFLOWCONTROL field in EFR.
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_SW_FLOW_CONTROL);
    m_UART_regs.EFR.b.SWFLOWCONTROL = 0;

    // Configuring the SWFLOWCONTROL field in EFR.
    //HWREG(baseAdd + UART_EFR) |= (sw_flow_ctrl & UART_EFR_SW_FLOW_CONTROL);
    m_UART_regs.EFR.b.SWFLOWCONTROL = sw_flow_ctrl;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}


/**
 * \brief  Used only in UART mode, this API is used to control the pulse
 *         shaping feature. Pulse shaping feature could either be enabled
 *         or disabled in UART mode.
 *
 * \param  baseAdd       Memory address of the UART instance being used.
 * \param  shape_control  This specifies whether to enable or disable Pulse
 *                       shaping feature in UART mode
 *
 * 'shape_control' can take either of the two following values:\n
 * - UART_PULSE_NORMAL - to disable Pulse Shaping feature which is the Normal
 *   and default configuration\n
 * - UART_PULSE_SHAPING - to enable Pulse Shaping feature\n
 *
 * \return None
 */
void  AM335x_UART::pulse_shaping_control(uint32_t shape_control)
{
    // Clearing the UARTPULSE bit in MDR2.
    //HWREG(baseAdd + UART_MDR2) &= ~(UART_MDR2_UART_PULSE);
    m_UART_regs.MDR2.b.UARTPULSE = 0;

    // Programming the UARTPULSE bit in MDR2.
    //HWREG(baseAdd + UART_MDR2) |= (shape_control & UART_MDR2_UART_PULSE);
    m_UART_regs.MDR2.b.UARTPULSE = shape_control;
}

/**
 * \brief  This API can be used to control the Power Management
 *         request/acknowledgement process.
 *
 * \param  baseAdd   Memory address of the UART instance being used.
 * \param  mode_flag  This specifies the Power Management
 *                   request/acknowledgement process to be followed
 *
 * 'mode_flag' can take one of the following values:
 * - UART_IDLEMODE_FORCE_IDLE - to enable Force Idle mode\n
 * - UART_IDLEMODE_NO_IDLE - to enable No-Idle mode\n
 * - UART_IDLEMODE_SMART_IDLE - to enable Smart Idle mode\n
 * - UART_IDLEMODE_SMART_IDLE_WAKEUP - to enable Smart Idle Wakeup mode\n
 *
 * \return None
 */
void  AM335x_UART::idle_mode_configure(n_UART::e_IDLEMODE mode_flag)
{
    // Clearing the IDLEMODE field in SYSC.
    //HWREG(baseAdd + UART_SYSC) &= ~(UART_SYSC_IDLEMODE);
    m_UART_regs.SYSC.b.IDLEMODE = 0x0;

    // Programming the IDLEMODE field in SYSC.
    //HWREG(baseAdd + UART_SYSC) |= (mode_flag & UART_SYSC_IDLEMODE);
    m_UART_regs.SYSC.b.IDLEMODE = mode_flag;
}

/**
 * \brief  This API is used to control(enable/disable) the Wake-Up feature
 *         of the UART.
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  control_flag  This specifies whether the Wake Up feature should
 *                      be enabled or disabled for the UART instance
 *
 * 'control_flag' can take one of the following two values:
 * - UART_WAKEUP_ENABLE - to enable Wake-Up feature\n
 * - UART_WAKEUP_DISABLE - to disable Wake-Up feature\n
 *
 * \return None
 */
void  AM335x_UART::wakeup_control(uint32_t control_flag)
{
    // Clearing the ENAWAKEUP bit in SYSC register.
    //HWREG(baseAdd + UART_SYSC) &= ~(UART_SYSC_ENAWAKEUP);
    m_UART_regs.SYSC.b.ENAWAKEUP = 0;

    // Programming the ENAWAKEUP feature in SYSC register.
    //HWREG(baseAdd + UART_SYSC) |= (control_flag & UART_SYSC_ENAWAKEUP);
    m_UART_regs.SYSC.b.ENAWAKEUP = 0;
}

/**
 * \brief  This API is used to control(enable/disable) the Auto-Idle mode
 *         of operation of the UART.
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  mode_flag     This specifies whether to enable or disable the
 *                      Auto-Idle mode of the UART
 *
 * 'mode_flag' can take one of the following two values:
 * - UART_AUTO_IDLE_MODE_DISABLE - to disable Auto-Idle mode\n
 * - UART_AUTO_IDLE_MODE_ENABLE - to enable Auto-Idle mode\n
 *
 * \return None
 */
void  AM335x_UART::auto_idle_mode_control(uint32_t mode_flag)
{
    // Clearing the AUTOIDLE bit in SYSC register.
    //HWREG(baseAdd + UART_SYSC) &= ~(UART_SYSC_AUTOIDLE);
    m_UART_regs.SYSC.b.AUTOIDLE = 0;

    // Programming the AUTOIDLE bit in SYSC register.
    //HWREG(baseAdd + UART_SYSC) |= (mode_flag & UART_SYSC_AUTOIDLE);
    m_UART_regs.SYSC.b.AUTOIDLE = mode_flag;
}


/**
 * \brief  This API configures the Receiver FIFO threshold level to
 *         start/stop transmission during Hardware Flow Control. 
 *
 * \param  baseAdd        Memory address of the UART instance being used.
 * \param  rts_halt_flag    The receiver FIFO threshold level on attaining
 *                        which the RTS line is deasserted signalling the
 *                        transmitter of its counterpart to stop trasmitting.
 * \param  rts_start_flag   The receiver FIFO threshold level on attaining
 *                        which the RTS line is asserted signalling the
 *                        transmitter of its counterpart to start transmitting.
 *
 * 'rts_halt_flag' can take one among the following values:\n
 *  - m, where (0 <= m <= 15).\n
 *  The HALT trigger level would then be (m *  4).\n
 * 'rts_start_flag' can take one among the following values:\n
 *  - n, where (0 <= n <= 15).\n
 *  The RESTORE trigger level would then be (n * 4).\n
 *
 * For Example: If m = 8 and n = 5, then the receiver trigger levels would be:\n
 * HALT = (8 * 4) = 32, RESTORE = (5 * 4) = 20.\n
 *
 * \return None.
 *
 * \note     Here two things should be taken care of:\n
 *        1> RX FIFO Threshold Level to Halt Transmission should be greater
 *           than the Threshold level to Start transmission
 *           i.e. TCR[3:0] > TCR[7:4].\n
 *        2> In FIFO Interrupt mode with Flow Control, the RX FIFO threshold
 *           level to Halt Transmission (TCR[3:0]) should be greater than or
 *           equal to the Receiver FIFO trigger level(TLR[7:4] or FCR[7:6]).\n
 */
void  AM335x_UART::flow_ctrl_trig_lvl_config(uint32_t rts_halt_flag, uint32_t rts_start_flag)
{
    //uint32_t tcr_value = 0;

    //tcr_value = rts_halt_flag & n_UART::TCR_RX_FIFO_TRIG_HALT;
    //tcr_value |= (rts_start_flag <<
    //              n_UART::TCR_RX_FIFO_TRIG_START_SHIFT) &
    //              n_UART::TCR_RX_FIFO_TRIG_START;

    // Writing to TCR register.
    //HWREG(baseAdd + UART_TCR) = tcr_value;
    m_UART_regs.TCR.b.RXFIFOTRIGHALT = rts_halt_flag;
    m_UART_regs.TCR.b.RXFIFOTRIGSTART = rts_start_flag;
}

/**
 * \brief  This API programs the XON1/ADDR1 and XOFF1 registers.
 *
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  xon1_value    The XON1 character.
 * \param  xoff1_value   The XOFF1 character.
 *
 * \return None.
 *
 * \note   In UART mode, the character in XON1/ADDR1 register is the XON1
 *         character. In IrDA mode, this is the address ADDR1. 
 */
void  AM335x_UART::XON1XOFF1_val_program(uint8_t xon1_value, uint8_t xoff1_value)
{
    // Programming the XON1 register
    //HWREG(baseAdd + UART_XON1_ADDR1) = xon1_value;
    m_UART_regs.XON1_ADDR1.b.XONWORD1 = xon1_value;
        
    // Programming the XOFF1 register. 
    //HWREG(baseAdd + UART_XOFF1) = xoff1_value;
    m_UART_regs.XOFF1.b.XOFFWORD1 = xoff1_value;
}

/**
 * \brief  This API programs the XON2/ADDR2 and XOFF2 registers.
 * 
 * \param  baseAdd      Memory address of the UART instance being used.
 * \param  xon2_value    The XON2 character.
 * \param  xoff2_value   The XOFF2 character.
 *
 * \return None.
 *  
 * \note   In UART mode, the character in XON2/ADDR2 register is the XON2
 *         character. In IrDA mode, this is the address ADDR2.
 *
 */
void  AM335x_UART::XON2XOFF2_val_program(uint8_t xon2_value, uint8_t xoff2_value)
{
    // Programming the XON2 register.
    //HWREG(baseAdd + UART_XON2_ADDR2) = xon2_value;
    m_UART_regs.XON2_ADDR2.b.XONWORD2 = xon2_value;

    // Programming the XOFF2 register. */
    //HWREG(baseAdd + UART_XOFF2) = xoff2_value;
    m_UART_regs.XOFF2.b.XOFFWORD2 = xoff2_value;
}


/**
 * \brief  This API controls(enables/disables) the XON-any feature in Modem
 *         Control Register(MCR).
 *
 * \param  baseAdd        Memory address of the UART instance being used.
 * \param  control_flag    This specifies whether to enable or disable XON any
 *                        feature
 *
 * 'xonAnyControl' can take one of the following values:
 * - UART_XON_ANY_ENABLE - to enable XON any functionality\n
 * - UART_XON_ANY_DISABLE - to disable XON any functionality\n
 *
 * \return None.
 *
 * \note   When XON-any feature is enabled, the transmission will resume after
 *         receiving any character after recognizing the XOFF character. The 
 *         XON-any character is written into the RX FIFO even if it is a
 *         software flow character.\n
 */
void  AM335x_UART::XON_any_feature_control(uint32_t control_flag)
{
    uint32_t LCR_reg_value = 0;
    uint32_t enhan_fn_bit_val = 0;

    LCR_reg_value = reg_config_mode_enable(n_UART::CONFIG_MODE_B);  // Switching to Register Configuration Mode B.

    // Collecting the value of EFR[4] and later setting the same to 1.
    //enhan_fn_bit_val = (HWREG(baseAdd + UART_EFR) & UART_EFR_ENHANCED_EN);
    //HWREG(baseAdd + UART_EFR) |= UART_EFR_ENHANCED_EN;
    enhan_fn_bit_val = m_UART_regs.EFR.b.ENHANCEDEN;
    m_UART_regs.EFR.b.ENHANCEDEN = HIGH;

    // Clearing the XONEN bit in MCR.
    //HWREG(baseAdd + UART_MCR) &= ~(UART_MCR_XON_EN);
    m_UART_regs.MCR.b.XONEN = 0;

    // Programming the XONEN bit in MCR.
    //HWREG(baseAdd + UART_MCR) |= (control_flag & UART_MCR_XON_EN);
    m_UART_regs.MCR.b.XONEN = control_flag;

    // Restoring the value of EFR[4] to its original value.
    //HWREG(baseAdd + UART_EFR) &= ~(UART_EFR_ENHANCED_EN);
    //HWREG(baseAdd + UART_EFR) |= enhan_fn_bit_val;
    m_UART_regs.EFR.b.ENHANCEDEN = 0;
    m_UART_regs.EFR.b.ENHANCEDEN = enhan_fn_bit_val;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.
}

/**
 * \brief  This API controls(enables/disables) the Loopback mode of operation
 *         for the UART instance.
 *
 * \param  baseAdd      Memory address of the UART instance being used
 * \param  control_flag  This specifies whether to enable or disable Loopback
 *                      mode of operation
 *
 * 'control_flag' can take one of the following values:
 * - UART_LOOPBACK_MODE_ENABLE - to enable Loopback mode of operation\n
 * - UART_LOOPBACK_MODE_DISABLE - to disable Loopback mode and thus resulting
 *                                in switching to Normal operating mode\n
 *
 * \return None
 */
void  AM335x_UART::loopback_mode_control(uint32_t control_flag)
{
    // Clearing the LOOPBACKEN bit in MCR.
    //HWREG(baseAdd + UART_MCR) &= ~(UART_MCR_LOOPBACK_EN);
    m_UART_regs.MCR.b.LOOPBACKEN = 0;

    // Programming the LOOPBACKEN bit in MCR.
    //HWREG(baseAdd + UART_MCR) |= (control_flag & UART_MCR_LOOPBACK_EN);
    m_UART_regs.MCR.b.LOOPBACKEN = control_flag;
}

/**
 * \brief  This API switches the specified Modem Control Signals to active
 *         state. The Modem Control signals in context are DCD, RI, RTS and
 *         DTR.
 * 
 * \param  baseAdd    Memory address of the UART instance being used. 
 * \param  mode_flag   This specifies the signals that are required to be
 *                    switched to active state. Bits MCR[3:0] hold control
 *                    for switching Modem Control Signals to active/inactive
 *                    state.
 *
 * 'mode_flag' can take one or a combination of the following values:\n
 * - UART_DCD_CONTROL - specifying to force DCDn input to active state(low)\n
 * - UART_RI_CONTROL - specifying to force RIn input to active state(low)\n
 * - UART_RTS_CONTROL - specifying to force RTSn output to active state (low)\n
 * - UART_DTR_CONTROL - specifying to force DTRn output to active state (low)\n
 *
 * \return None.
 */
void  AM335x_UART::modem_control_set(uint32_t mode_flag)
{
    // Programming the specified bits of MCR.
    //HWREG(baseAdd + UART_MCR) |= (mode_flag & (UART_MCR_CD_STS_CH |
    //                                         UART_MCR_RI_STS_CH |
    //                                         UART_MCR_RTS |
    //                                         UART_MCR_DTR));
  
    m_UART_regs.MCR.reg |= (mode_flag & (n_UART::MODEM_DTR |
                                         n_UART::MODEM_RTS |
                                         n_UART::MODEM_RISTSCH |
                                         n_UART::MODEM_CDSTSCH));    
 
}

/**
 * \brief  This API switches the specified Modem Control signals to inactive
 *         state. The Modem Control signals in context are DCD, RI, RTS and
 *         DTR.
 *
 * \param  baseAdd    Memory address of the UART instance being used.
 * \param  mode_flag   This specifies the signals that are required to be
 *                    switched to inactive state. Bits MCR[3:0] hold control
 *                    for switching Modem Control Signals to active/inactive
 *                    state.

 *
 * 'mode_flag' can take one or a combination of the following values:\n
 * - UART_DCD_CONTROL - specifying to force DCDn input to inactive state(high)\n
 * - UART_RI_CONTROL - specifying to force RIn input to inactive state (high)\n
 * - UART_RTS_CONTROL - specifying to force RTSn output to inactive state(high)\n
 * - UART_DTR_CONTROL - specifying to force DTRn output to inactive state(high)\n
 * 
 * \return None
 */
void  AM335x_UART::modem_control_clear(uint32_t mode_flag)
{
    // Clearing the specified bits in MCR.
    //HWREG(baseAdd + UART_MCR) &= ~(mode_flag & (UART_MCR_CD_STS_CH |
    //                                           UART_MCR_RI_STS_CH |
    //                                           UART_MCR_RTS |
    //                                           UART_MCR_DTR));
    m_UART_regs.MCR.reg &= ~(mode_flag & (n_UART::MODEM_DTR |
                                          n_UART::MODEM_RTS |
                                          n_UART::MODEM_RISTSCH |
                                          n_UART::MODEM_CDSTSCH));
}

/**
 * \brief  This API reads the values on Modem Signal Lines. The Modem Signals
 *         in context are:
 *         1> Data Carrier Detect(DCD)\n
 *         2> Ring Indicator(RI)\n
 *         3> Data Set Ready(DSR)\n
 *         4> Clear To Send(CTS)\n
 *
 * \param  baseAdd    Memory address of the UART instance being used.
 *
 * \return The value returned could be one of the following macros, a
 *         combination or all of it.\n
 *         - UART_DCD_VALUE - indicating DCDn line is active(low)\n
 *         - UART_RI_VALUE - indicating RIn line is active(low)\n
 *         - UART_DSR_VALUE - indicating DSRn line is active(low)\n
 *         - UART_CTS_VALUE - indicating CTSn line is active(low)\n
 */
uint32_t  AM335x_UART::modem_ctatus_get()
{    
    // Reading MSR[7:4] bits. These values indicate the complement of the
    // signal levels on the Modem input lines.
    //return(HWREG(baseAdd + UART_MSR) & (UART_MSR_NCD_STS |
    //                                    UART_MSR_NRI_STS |
    //                                    UART_MSR_NDSR_STS |
    //                                    UART_MSR_NCTS_STS));
    return(m_UART_regs.MSR.reg & (n_UART::BIT_NCD_STS |
                                  n_UART::BIT_NRI_STS |
                                  n_UART::BIT_NDSR_STS |
                                  n_UART::BIT_NCTS_STS));
}

/**
 * \brief  This API determines if the values on Modem Signal Lines have
 *         changed since the last read of Modem Status Register(MSR).
 *         The Modem Signals in context are DCD, RI, DSR, CTS.
 *
 * \param  baseAdd    Memory address of the UART instance being used.
 *
 * \return The value returned could be one of the following macros, a
 *         combination or all of it.
 *         - UART_DCD_STS_CHANGED - indicating that DCDn input changed state
 *           since the last read of MSR\n
 *         - UART_RI_STS_CHANGED - indicating that RIn input changed state
 *           since the last read of MSR\n
 *         - UART_DSR_STS_CHANGED - indicating that DSRn input changed state
 *           since the last read of MSR\n
 *         - UART_CTS_STS_CHANGED - indicating that CTSn input changed state
 *           since the last read of MSR\n
 */
uint32_t  AM335x_UART::modem_ctatus_change_check()
{

    // Reading MSR[3:0] bits that indicate the change of state of Modem signal
    // lines.
    //return(HWREG(baseAdd + UART_MSR) & (UART_MSR_DCD_STS |
    //                                    UART_MSR_RI_STS |
    //                                    UART_MSR_DSR_STS |
    //                                    UART_MSR_CTS_STS));
    return(m_UART_regs.MSR.reg & (n_UART::BIT_DCD_STS |
                                  n_UART::BIT_RI_STS |
                                  n_UART::BIT_DSR_STS |
                                  n_UART::BIT_CTS_STS));
}

/**
 * \brief  This API reads the RESUME register which clears the internal flags.
 * 
 * \param  baseAdd    Memory address of the UART instance being used
 *
 * \return None
 *   
 * \note   When conditions like TX Underrun/RX Overrun errors occur, the
 *         transmission/reception gets halted and some internal flags are set.
 *         Clearing these flags would resume the halted operation.
 */
void  AM335x_UART::resume_operation()
{   
    // Dummy read of RESUME register.
    //HWREG(baseAdd + UART_RESUME);
    uint8_t resume_read = m_UART_regs.RESUME.b.RESUME;
}


/**
 * \brief  This API enables the Wake-Up capability for the specified events.
 *         On enabling Wake-Up capability for them, the occurence of the
 *         corresponding event shall wake up the system.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  wakeUpFlag  This specifies the event(s) for which Wake-Up
 *                     capability needs to be enabled.
 *
 * 'wakeUpFlag' can take one or a combination of the following values:
 * - UART_WAKEUP_TX_INTERRUPT - enabling THR, TXDMA and TXSTATUS
 *   interrupts to wake up the system\n
 * - UART_WAKEUP_RLS_INTERRUPT - enabling the Receiver Line Status
 *   interrupt to wake up the system\n
 * - UART_WAKEUP_RHR_INTERRUPT - enabling the RHR interrupt(RX FIFO
 *   threshold level reached) to wake up the system\n
 * - UART_WAKEUP_RX_ACTIVITY - enabling any activity on the Receiver line
 *   (RX) to wake up the system\n
 * - UART_WAKEUP_DCD_ACTIVITY - enabling any activity on DCD line to wake
 *   up the system\n
 * - UART_WAKEUP_RI_ACTIVITY - enabling any activity on RI line to wake up
 *   the system\n
 * - UART_WAKEUP_DSR_ACTIVITY - enabling any acivity on DSR line to wake up
 *   the system\n
 * - UART_WAKEUP_CTS_ACTIVITY - enabling any activity on CTS line to wake up
 *   the system\n
 *
 * \return  None
 */
void  AM335x_UART::wakeup_events_enable(uint32_t wakeup_flag)
{
    // Programming the Wake-Up configuration fields in WER.
    //HWREG(baseAdd + UART_WER) |= (wakeup_flag &
    //                              (UART_WER_EVENT_7_TX_WAKEUP_EN |
    //                               UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT |
    //                               UART_WER_EVENT_5_RHR_INTERRUPT |
    //                               UART_WER_EVENT_4_RX_ACTIVITY |
    //                               UART_WER_EVENT_3_DCD_CD_ACTIVITY |
    //                               UART_WER_EVENT_2_RI_ACTIVITY |
    //                               UART_WER_EVENT_1_DSR_ACTIVITY |
    //                               UART_WER_EVENT_0_CTS_ACTIVITY));
    m_UART_regs.WER.reg |= (wakeup_flag &
                            (n_UART::EVENT_7_TX_WAKEUP_EN |
                             n_UART::EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT |
                             n_UART::EVENT_5_RHR_INTERRUPT |
                             n_UART::EVENT_4_RX_ACTIVITY |
                             n_UART::EVENT_3_DCD_CD_ACTIVITY |
                             n_UART::EVENT_2_RI_ACTIVITY |
                             n_UART::EVENT_1_DSR_ACTIVITY |
                             n_UART::EVENT_0_CTS_ACTIVITY));
  
}

/**
 * \brief  This API disables the Wake-Up capability for the specified events.
 *         On disabling Wake-Up capability for them, the occurence of the
 *         corresponding event shall not wake up the system.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  wakeup_flag  This specifies the event(s) for which Wake-Up
 *                     capability needs to be disabled.
 *
 * 'wakeup_flag' can take one or a combination of the following values:
 * - UART_WAKEUP_TX_INTERRUPT - disabling THR, TXDMA and TXSTATUS
 *   interrupts to wake up the system\n
 * - UART_WAKEUP_RLS_INTERRUPT - disabling the Receiver Line Status
 *   interrupt to wake up the system\n
 * - UART_WAKEUP_RHR_INTERRUPT - disabling the RHR interrupt(RX FIFO
 *   threshold level reached) to wake up the system\n
 * - UART_WAKEUP_RX_ACTIVITY - disabling any activity on the Receiver line
 *   (RX) to wake up the system\n
 * - UART_WAKEUP_DCD_ACTIVITY - disabling any activity on DCD line to wake
 *   up the system\n
 * - UART_WAKEUP_RI_ACTIVITY - disabling any activity on RI line to wake up
 *   the system\n
 * - UART_WAKEUP_DSR_ACTIVITY - disabling any acivity on DSR line to wake up
 *   the system\n
 * - UART_WAKEUP_CTS_ACTIVITY - disabling any activity on CTS line to wake up
 *   the system\n
 *
 * \return  None
 */
void  AM335x_UART::wakeup_events_disable(uint32_t wakeup_flag)
{
    // Programming the Wake-Up configuration fields in WER.
    //HWREG(baseAdd + UART_WER) &= ~(wakeup_flag &
    //                               (UART_WER_EVENT_7_TX_WAKEUP_EN |
    //                                UART_WER_EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT |
    //                                UART_WER_EVENT_5_RHR_INTERRUPT |
    //                                UART_WER_EVENT_4_RX_ACTIVITY |
    //                                UART_WER_EVENT_3_DCD_CD_ACTIVITY |
    //                                UART_WER_EVENT_2_RI_ACTIVITY |
    //                                UART_WER_EVENT_1_DSR_ACTIVITY |
    //                                UART_WER_EVENT_0_CTS_ACTIVITY));
     m_UART_regs.WER.reg &= ~(wakeup_flag &
                              (n_UART::EVENT_7_TX_WAKEUP_EN |
                               n_UART::EVENT_6_RECEIVER_LINE_STATUS_INTERRUPT |
                               n_UART::EVENT_5_RHR_INTERRUPT |
                               n_UART::EVENT_4_RX_ACTIVITY |
                               n_UART::EVENT_3_DCD_CD_ACTIVITY |
                               n_UART::EVENT_2_RI_ACTIVITY |
                               n_UART::EVENT_1_DSR_ACTIVITY |
                               n_UART::EVENT_0_CTS_ACTIVITY));
}


/**
 * \brief  This API controls the feature of setting the Trigger Level
 *         granularity as 1 for Transmitter and Receiver FIFOs.
 *
 * \param  baseAdd          Memory address of the UART instance being used.
 * \param  rx_FIFO_gran_ctrl   This specifies whether the trigger level
 *                          granularity for the RX FIFO is to be 1 or not
 * \param  tx_FIFO_gran_ctrl   This specifies whether the trigger level
 *                          granularity for the TX FIFO is to be 1 or not
 *
 * 'rx_FIFO_gran_ctrl' can take either of the following values:
 * - UART_RX_TRIG_LVL_GRAN_1_DISABLE - to disable usage of a granularity of 1
 *   for RX FIFO Trigger level\n
 * - UART_RX_TRIG_LVL_GRAN_1_ENABLE - to set a granularity of 1 for RX FIFO
 *   Trigger level\n
 *
 * 'tx_FIFO_gran_ctrl' can take either of the following values:
 * - UART_TX_TRIG_LVL_GRAN_1_DISABLE - to disable usage of a granularity of 1
 *   for TX FIFO Trigger level\n
 * - UART_TX_FIFO_LVL_GRAN_1_ENABLE - to set a granularity of 1 for TX FIFO
 *   Trigger level\n
 *
 * \return None
 */
 void  AM335x_UART::FIFO_trig_lvl_gran_control(uint32_t rx_FIFO_gran_ctrl, uint32_t tx_FIFO_gran_ctrl)
{
    // Clearing the RXTRIGGRANU1 and TXTRIGGRANU1 bits in SCR.
    //HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_RX_TRIG_GRANU1 |
    //                               UART_SCR_TX_TRIG_GRANU1);
    m_UART_regs.SCR.b.RXTRIGGRANU1 = 0;
    m_UART_regs.SCR.b.TXTRIGGRANU1 = 0;
    
    // Programming the RXTRIGGRANU1 bit in SCR.
    //HWREG(baseAdd + UART_SCR) |= (rx_FIFO_gran_ctrl & UART_SCR_RX_TRIG_GRANU1);
    m_UART_regs.SCR.b.RXTRIGGRANU1 = rx_FIFO_gran_ctrl;

    // Programming the TXTRIGGRANU1 bit in SCR.
    //HWREG(baseAdd + UART_SCR) |= (tx_FIFO_gran_ctrl & UART_SCR_TX_TRIG_GRANU1);
    m_UART_regs.SCR.b.TXTRIGGRANU1 = tx_FIFO_gran_ctrl;
}

/**
 * \brief  This API controls the interrupt enable and disable feature for
 *         Data Set Ready(DSRn) interrupt.
 *
 * \param  baseAdd     Memory address of the UART instance being used
 * \param  control_flag This specifies whether to enable or disable DSRn
 *                     interrupt
 *
 * 'control_flag' can take one of the following values:
 * - UART_DSRn_INT_DISABLE - to disable DSRn interrupt\n
 * - UART_DSRn_INT_ENABLE - to enable DSRn interrupt\n
 *
 * \return None
 */
void  AM335x_UART::DSR_interrupt_control(uint32_t control_flag)
{
    //HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_DSR_IT);
    m_UART_regs.SCR.b.DSRIT = 0;
    
    // Programming the DSRIT bit in SCR.
    //HWREG(baseAdd + UART_SCR) |= (control_flag & UART_SCR_DSR_IT);
    m_UART_regs.SCR.b.DSRIT = control_flag;
}

/**
 * \brief  This API is used to choose a condition under which a  
 *         Transmit Holding Register(THR) Interrupt should occur.
 *         A THR interrupt can be configured to occur either when:\n
 *         1> TX FIFO becoming empty OR\n
 *         2> TX FIFO and TX Shift register becoming empty.
 *
 * \param  baseAdd      Memory address of the UART instance being used
 * \param  control_flag  This specifies the condition under which a Transmitter
 *                      Holding Register Interrupt should occur.
 *
 * 'control_flag' can take either of the following two values:
 * - UART_THR_INT_NORMAL - for THR Interrupt to be raised under normal
 *   conditions(guided by the TX FIFO Threshold value)\n
 * - UART_THR_INT_FIFO_TSR_EMPTY - for THR Interrupt to be raised when both
 *   Transmitter FIFO and Transmitter Shift Register are empty\n
 *
 * \return None
 */
void  AM335x_UART::TX_empty_int_control(uint32_t control_flag)
{
    // Clearing the TXEMPTYCTLIT bit in SCR.
    //HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_TX_EMPTY_CTL_IT);
    m_UART_regs.SCR.b.TXEMPTYCTLIT = 0;

    // Programming the TXEMPTYCTLIT bit in SCR.
    //HWREG(baseAdd + UART_SCR) |= (control_flag & UART_SCR_TX_EMPTY_CTL_IT);
    m_UART_regs.SCR.b.TXEMPTYCTLIT = control_flag;
}


/**
 * \brief  This API controls (enables/disables) a feature where a falling
 *         edge on the RX, CTSn or DSRs could send a wake-up interrupt to
 *         the CPU.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 * \param  wake_up_flag  This specifies whether or not a wake-up interrupt
 *                     should be sent to the CPU when a falling edge occurs on
 *                     RX, CTSn or DSRn lines.
 *
 * 'wake_up_flag' can take one of the following values:
 * - UART_RX_CTS_DSR_WAKEUP_DISABLE - to disable generation of a Wake-Up
 *   interrupt due to occurence of a falling edge on RX, CTSn or DSRn lines.
 * - UART_RX_CTS_DSR_WAKEUP_ENABLE - to enable generation of a Wake-Up
 *   interrupt due to occurence of a falling edge on RX, CTSn, DSRn lines.
 *
 * \return None
 */
void  AM335x_UART::RXCTSDSR_wakeup_configure(uint32_t wake_up_flag)
{
    // Clearing the RXCTSDSRWAKEUPENABLE bit in SCR.
    //HWREG(baseAdd + UART_SCR) &= ~(UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE);
    m_UART_regs.SCR.b.RXCTSDSRWAKEUPENABLE = 0;

    // Programming the RXCTSDSRWAKEUPENABLE bit in SCR.
    //HWREG(baseAdd + UART_SCR) |= (wake_up_flag & UART_SCR_RX_CTS_DSR_WAKE_UP_ENABLE);
    m_UART_regs.SCR.b.RXCTSDSRWAKEUPENABLE = wake_up_flag;
}

/**
 * \brief  This API determines whether a falling edge occured on RX, CTSn or
 *         DSRn lines.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 *
 * \return This returns one of the following values:
 *         - UART_RX_CTS_DSR_NO_FALL_EDGE - indicating that no falling edge
 *           occured on RX, CTSn and DSRn lines\n
 *         - UART_RX_CTS_DSR_FALL_EDGE - indicating that a falling edge
 *           occured on RX, CTSn and DSRn lines\n
 */
uint32_t  AM335x_UART::RXCTSDSR_transition_status_get()
{
    //return(HWREG(baseAdd + UART_SSR) & UART_SSR_RX_CTS_DSR_WAKE_UP_STS);
    return (uint32_t)m_UART_regs.SSR.b.RXCTSDSRWAKEUPSTS;
}

/**
 * \brief  This API controls the DMA Counter Reset options.
 *
 * \param  baseAdd      Memory address of the UART instance being used
 * \param  control_flag  This specifies the DMA Counter Reset options
 *
 * 'control_flag' can take either of the following values:
 * - UART_DMA_CNTR_NO_RESET_FIFO_RESET - indicating that the DMA counter
 *   shall not be reset if the corresponding FIFO is reset\n
 * - UART_DMA_CNTR_RESET_FIFO_RESET - indicating that the DMA counter shall
 *   be reset if the corresponding FIFO is reset\n
 *
 * \return None
 */
void  AM335x_UART::DMA_counter_reset_control(uint32_t control_flag)
{
    // Clearing the DMACOUNTERRST bit in SSR.
    //HWREG(baseAdd + UART_SSR) &= ~(UART_SSR_DMA_COUNTER_RST);
    m_UART_regs.SSR.b.DMACOUNTERRST = 0;

    // Programming the DMACOUNTERRST bit in SSR.
    //HWREG(baseAdd + UART_SSR) |= (control_flag &  UART_SSR_DMA_COUNTER_RST);
    m_UART_regs.SSR.b.DMACOUNTERRST = control_flag;
}

/**
 * \brief  This API determines whether the Transmitter FIFO is full or not.
 *
 * \param  baseAdd      Memory address of the UART instance being used
 *
 * \return This returns either of the following values:
 *         - UART_TX_FIFO_NOT_FULL - indicating that the TX FIFO is not full\n
 *         - UART_TX_FIFO_FULL - indicating that the TX FIFO is full\n
 */
bool  AM335x_UART::TX_FIFO_full_status_get()
{
    bool  result = false;
    
    if(m_UART_regs.SSR.b.TXFIFOFULL)
        result = true;

    return result;
}

/**
 * \brief   This API determines the current level of the Transmitter FIFO.
 *
 * \param   baseAdd      Memory address of the UART instance being used.
 *
 * \return  The current level of the Transmitter FIFO.
 */
uint32_t  AM335x_UART::TX_FIFO_level_get()
{
    //return(HWREG(baseAdd + UART_TXFIFO_LVL));
    return (uint32_t)m_UART_regs.TXFIFO_LVL.reg;
}

/**
 * \brief   This API determines the current level of the Receiver FIFO.
 *
 * \param   baseAdd      Memory address of the UART instance being used.
 *
 * \return  The current level of the Receiver FIFO.
 */
uint32_t  AM335x_UART::RX_FIFO_level_get()
{
    //return(HWREG(baseAdd + UART_RXFIFO_LVL));
    return (uint32_t)m_UART_regs.RXFIFO_LVL.reg;
}

/**
 * \brief  This API determines the Parity mode being configured by the system
 *         in the UART Autobauding mode.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 *
 * \return This returns one of the following values:
 *         - UART_AUTOBAUD_NO_PARITY - indicating that no parity was
 *           identified\n
 *         - UART_AUTOBAUD_PARITY_SPACE - indicating that space parity has
 *           been configured\n
 *         - UART_AUTOBAUD_EVEN_PARITY - indicating that even parity has been
 *           configured\n
 *         - UART_AUTOBAUD_ODD_PARITY - indicating that odd parity has been
 *           configured\n
 *
 * \note   UASR register used in this API can be accessed only when the UART
 *         is in Configuration Mode A or Configuration Mode B of operation.
 */
uint32_t  AM335x_UART::autobaud_parity_get()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = 0;

    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Configuration Mode A of operation.

    //ret_val = (HWREG(baseAdd + UART_UASR) & UART_UASR_PARITY_TYPE);
      ret_val = m_UART_regs.UASR.b.PARITYTYPE;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API determines the word length per frame(character length)
 *         being configured by the system in UART Autobauding mode.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 *
 * \return This returns one of the following two values:
 *         - UART_AUTOBAUD_CHAR_LENGTH_7 - indicating word length of 7 bits\n
 *         - UART_AUTOBAUD_CHAR_LENGTH_8 - indicating word length of 8 bits\n
 *
 * \note   UASR register used in this API can be accessed only when the UART
 *         is in Configuration Mode A or Configuration Mode B of operation.
 */
uint32_t  AM335x_UART::autobaud_word_len_get()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = 0;

    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Configuration Mode A of operation.

    //ret_val = (HWREG(baseAdd + UART_UASR) & UART_UASR_BIT_BY_CHAR);
      ret_val = m_UART_regs.UASR.b.BITBYCHAR;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
      m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API determines the baud rate being configured by the system
 *         in UART Autobauding mode.
 *
 * \param  baseAdd     Memory address of the UART instance being used.
 *
 * \return This returns one of the following values:
 *         - UART_AUTOBAUD_SPEED_115200 - for baud rate of 115200 bps\n
 *         - UART_AUTOBAUD_SPEED_57600 - for baud rate of 57600 bps\n
 *         - UART_AUTOBAUD_SPEED_38400 - for baud rate of 38400 bps\n
 *         - UART_AUTOBAUD_SPEED_28800 - for baud rate of 28800 bps\n
 *         - UART_AUTOBAUD_SPEED_19200 - for baud rate of 19200 bps\n
 *         - UART_AUTOBAUD_SPEED_14400 - for baud rate of 14400 bps\n
 *         - UART_AUTOBAUD_SPEED_9600 - for baud rate of 9600 bps\n
 *         - UART_AUTOBAUD_SPEED_4800 - for baud rate of 4800 bps\n
 *         - UART_AUTOBAUD_SPEED_2400 - for baud rate of 2400 bps\n
 *         - UART_AUTOBAUD_SPEED_1200 - for baud rate of 1200 bps\n
 *         - UART_AUTOBAUD_NO_SPEED_IDEN - for no speed identified\n
 *
 * \note   UASR register used in this API can be accessed only when the UART
 *         is in Configuration Mode A or Configuration Mode B of operation.
 */
uint32_t  AM335x_UART::autobaud_speed_get()
{
    uint32_t LCR_reg_value = 0;
    uint32_t ret_val = 0;

    reg_config_mode_enable(n_UART::CONFIG_MODE_A);  // Switching to Configuration Mode A of operation.

    //ret_val = (HWREG(baseAdd + UART_UASR) & UART_UASR_SPEED);
      ret_val = m_UART_regs.UASR.b.SPEED;

    //HWREG(baseAdd + UART_LCR) = LCR_reg_value;  // Restoring the value of LCR. 
     m_UART_regs.LCR.reg = LCR_reg_value;   // Restoring the value of LCR.

    return ret_val;
}

/**
 * \brief  This API programs the Scratchpad Register with the specified
 *         value.
 *
 * \param  baseAdd      Memory address of the UART instance being used
 * \param  scratch_value This is the scratch value(temporary data) to be loaded
 *                      to the Scratchpad Register
 * 
 * \return None
 */
void  AM335x_UART::scratchpad_reg_write(uint32_t scratch_value)
{
    //HWREG(baseAdd + UART_SPR) &= ~(UART_SPR_SPR_WORD);
    m_UART_regs.SPR.b.SPR_WORD = 0;
    
    // Programming the SPR_WORD field of SPR
    m_UART_regs.SPR.b.SPR_WORD = scratch_value;
}

/**
 * \brief  This API reads the value in Scratchpad Register.
 * 
 * \param  baseAdd      Memory address of the UART instance being used
 *
 * \return The value in Scratchpad Register
 */
uint32_t  AM335x_UART::scratchpad_reg_read()
{
    //return (HWREG(baseAdd + UART_SPR) & UART_SPR_SPR_WORD);
    return (uint32_t)m_UART_regs.SPR.b.SPR_WORD;
}

/**
 * \brief  This API reads the Revision Number of the module from the Module
 *         Version Register(MVR).
 *
 * \param  baseAdd    Memory address of the UART instance being used
 *
 * \return This returns the Major Revision Number(MVR[7:4] and Minor Revision
 *         Number(MVR[3:0])) of the module.
 */
uint32_t  AM335x_UART::module_version_number_get()
{
    //return (HWREG(baseAdd + UART_MVR) & 0x00FF);
    return (m_UART_regs.MVR.reg & 0x00FF);
}


/**
 * \brief   This function controls the method of setting the Transmit DMA
 *          Threshold Value. The Transmit DMA Threshold Value can be set to
 *          a default value of 64 characters or can take the value in
 *          TX_DMA_THRESHOLD register.
 *
 * \param   baseAdd      Memory address of the UART instance being used.
 * \param   thrs_ctrl_flag A value which signifies the method of setting the
 *                       Transmit DMA Threshold Value.
 *
 * 'thrs_ctrl_flag' can take one of the following values:\n
 * - UART_TX_DMA_THRESHOLD_64 - for 64 characters TX DMA Threshold value\n
 * - UART_TX_DMA_THRESHOLD_REG - for Transmit DMA Threshold value to be
 *   the value in TX_DMA_THRESHOLD register.\n
 *
 * \return  None
 *
 */
void  AM335x_UART::TX_DMA_threshold_control(bool thrs_ctrl_flag)
{
    // Clearing the SET_TX_DMA_THRESHOLD bit in MDR3 register.
    //HWREG(baseAdd + UART_MDR3) &= ~(UART_MDR3_SET_DMA_TX_THRESHOLD);
    m_UART_regs.MDR3.b.SET_DMA_TX_THRESHOLD = 0;

    // Programming the SET_TX_DMA_THRESHOLD bit in MDR3 register. */
    //HWREG(baseAdd + UART_MDR3) |= (thrs_ctrl_flag & UART_MDR3_SET_DMA_TX_THRESHOLD );
    m_UART_regs.MDR3.b.SET_DMA_TX_THRESHOLD = thrs_ctrl_flag;
}


/**
 * \brief   This function programs the TX_DMA_THRESHOLD register which holds
 *          Transmit DMA Threshold value to be used. When a TX DMA Threshold
 *          value other than 64 characters is required, this function can be
 *          used to program the same.
 *
 * \param   baseAdd     Memory address of the UART instance being used.
 * \param   thrs_value   The Transmit DMA Threshold Value.
 *
 * 'thrs_value' can take one of the following value - (0 <= thrs_value <= 63).\n
 *
 * \return  None
 *
 */
void  AM335x_UART::TX_DMA_threshold_val_config(uint32_t thrs_value)
{
    // Clearing the TX_DMA_THRESHOLD field of TX DMA Threshold register.
    //HWREG(baseAdd + UART_TX_DMA_THRESHOLD) &= ~(UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD);
    m_UART_regs.TX_DMA_THRESHOLD.b.TX_DMA_THRESHOLD = 0;

    // Programming the TX_DMA_THRESHOLD field of TX DMA Threshold register.
    //HWREG(baseAdd + UART_TX_DMA_THRESHOLD) |=  (thrs_value & UART_TX_DMA_THRESHOLD_TX_DMA_THRESHOLD);
     m_UART_regs.TX_DMA_THRESHOLD.b.TX_DMA_THRESHOLD = thrs_value;
}

bool  AM335x_UART::is_RX_data_rdy(ring_buffer<n_UART::RX_FIFO_MAX*4>*  )
{
    bool result = false;
    
    RX_end_timer.on_delay((void *)this);

    if(m_RX_sts == RX_CHUNK_RECEIVED)
    {  
        //read(p_Data);
        m_RX_sts = RX_IN_PROGESS;
    }

    //-----|
    //     |----- - transition mean that RX end with timeout.
    if(m_RX_sts == RX_TOUT_IS_OUT)
    {        
        //read(p_Data);
        m_RX_data.reset();
        m_RX_sts = RX_STOPPED;
        result = true;
    }
        
    return result; 
}

void AM335x_UART::m_Start_TX(size_t amount)
{
    //n_UART::IER_UART_reg_t  interrupt = { .reg = 0x0 };
    
    m_TX_data.increment(amount);
    m_TX_data.switch_buffers();
   
    //interrupt.b.THRIT = HIGH;      // enable TX interrupt.
    //int_enable(interrupt.reg);
    m_UART_regs.IER_UART.b.THRIT = HIGH;
}

void AM335x_UART::m_Start_RX(size_t amount)
{
    n_UART::IER_UART_reg_t  interrupt = { .reg = 0x0 };
    
    m_RX_data.switch_buffers();
    
    interrupt.b.RHRIT = HIGH;      // enable RX interrupt and RX timout interrupt.
    int_enable(interrupt.reg);
}

// need to be placed in IRQ_Handler if RX used
void  AM335x_UART::rx_irq(void)
{
    uint32_t status = int_identity_get(); 
    
    if(status & n_UART::RHR_IT)
    {
        m_TX_busy = false;
        
        // TODO: rx FIFO buffer get to m_RX_data
        
        m_RX_data.increment();
        
        if(m_RX_sts != RX_CHUNK_RECEIVED &&
           m_RX_sts != RX_IN_PROGESS)
            m_RX_sts = RX_IN_PROGESS;
        
        if(RX_end_timer.is_working())
            RX_end_timer.update();            
        else
            RX_end_timer.start(); 
    } 
    
    if(status & n_UART::RX_TOUT_IT)
    {
        m_RX_sts = RX_CHUNK_RECEIVED;
        
        // TODO: rx FIFO buffer get to m_RX_data
    }
}

void RX_end_callback(void * p_Obj)
{
    AM335x_UART *p_Serial = static_cast<AM335x_UART *>(p_Obj);
    
    p_Serial->m_RX_data.switch_buffers();
    p_Serial->m_RX_sts = p_Serial->RX_TOUT_IS_OUT;
}

// need to be placed in IRQ_Handler if TX used
void  AM335x_UART::tx_irq(void)
{
    uint32_t status = int_identity_get(); 
    uint32_t avail;
    char *data = nullptr;
    //n_UART::IER_UART_reg_t  interrupt = { .reg = 0x0 };
    
    if(status & n_UART::THR_IT)
    {  
        avail = m_TX_data.get_avail();
         data = m_TX_data.get_complete_buf();
        
        for(uint32_t index = 0; index < avail; index++)
        {
           m_UART_regs.THR.b.THR = *data;  // Write the byte to the Transmit Holding Register(or TX FIFO).
            
           data++;
            
           m_TX_data.decrement(1);
        }
    
        // turn off TX interrupt
        //interrupt.b.THRIT = HIGH;   
        //int_disable(interrupt.reg);
        m_UART_regs.IER_UART.b.THRIT = LOW;
        m_TX_busy = false;
    }    
}

void  AM335x_UART::write(const char *data, size_t len)
{
     uint32_t already_sent = 0;
     uint32_t left_to_send = 0;
     
     while(m_RX_data.get_avail()); 
     
     do
     {
         left_to_send = len - already_sent;
         left_to_send = (left_to_send > n_UART::TX_FIFO_MAX) ? n_UART::TX_FIFO_MAX : left_to_send;                
         
         memcpy(m_TX_data.get_empty_buf(), data + already_sent, left_to_send);
         m_TX_busy = true;
         m_Start_TX(left_to_send);  
 
         while(m_TX_busy);
 
         already_sent += left_to_send;
     }
     while (already_sent < len);            
}

AM335x_UART uart_0(n_UART::AM335X_UART_0_regs);