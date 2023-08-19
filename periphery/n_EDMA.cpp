#include"n_EDMA.h"

/**
 *  \brief   EDMA3 Initialization
 *  
 *  This function initializes the EDMA3 Driver
 *  Clears the error specific registers (EMCR/EMCRh, QEMCR, CCERRCLR) &
 *  initialize the Queue Number Registers
 *
 *  \param  queNum                   Event Queue Number to which the channel
 *                                   will be mapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  \return None
 *
 *  \note   The region_id is the shadow region(0 or 1) used and the,
 *          Event Queue used is either (0 or 1). There are only four shadow 
 *          regions and only two event Queues
 */
void AM335x_EDMA::init(n_EDMA::e_DMA_QUEUE que_num)
{
    uint32_t count = 0;

    // Clear the Event miss Registers
    // HWREG(baseAdd + EDMA3CC_EMCR) = EDMA3_SET_ALL_BITS;
    // HWREG(baseAdd + EDMA3CC_EMCRH) = EDMA3_SET_ALL_BITS;
    // HWREG(baseAdd + EDMA3CC_QEMCR) = EDMA3_SET_ALL_BITS;
    m_EDMA3CC_regs.EMCR.reg  = n_EDMA::SET_ALL_BITS;
    m_EDMA3CC_regs.EMCRH.reg = n_EDMA::SET_ALL_BITS;
    m_EDMA3CC_regs.QEMCR.reg = n_EDMA::SET_ALL_BITS;
    
    //HWREG(baseAdd + EDMA3CC_CCERRCLR) = EDMA3_SET_ALL_BITS;   // Clear CCERR register
    m_EDMA3CC_regs.CCERRCLR.reg =  n_EDMA::SET_ALL_BITS;        // Clear CCERR register
    
    // FOR TYPE EDMA 
    // Enable the DMA (0 - 64) channels in the DRAE and DRAEH register 
    //HWREG(baseAdd + EDMA3CC_DRAE(region_id)) = EDMA3_SET_ALL_BITS;
    //HWREG(baseAdd + EDMA3CC_DRAEH(region_id)) = EDMA3_SET_ALL_BITS;
     n_EDMA::get_DRAE_ptr(region_id)->reg = n_EDMA::SET_ALL_BITS;
     n_EDMA::get_DRAEH_ptr(region_id)->reg = n_EDMA::SET_ALL_BITS;
    
    if(n_EDMA::EDMA_REVID == version_get())
    {           
        for(uint32_t i = 0; i < n_EDMA::AM335X_DMACH_MAX; i++)
        {             
            //HWREG(baseAdd + EDMA3CC_DCHMAP(i)) = i << 5;  // All events are one to one mapped with the channels 
            m_EDMA3CC_regs.DCHMAP[i].reg = i << 5;
        }
    }
    
    // Initialize the DMA Queue Number Registers
    //for (uint32_t count = 0; count < SOC_EDMA3_NUM_DMACH; count++)
    for (count = 0; count < n_EDMA::AM335X_DMACH_MAX; count++)
    {
        //HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) &= EDMA3CC_DMAQNUM_CLR(count);
        //HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) |= EDMA3CC_DMAQNUM_SET(count,que_num);
        m_EDMA3CC_regs.DMAQNUM[count >> 3u].reg &= n_EDMA::DMAQNUM_CLR(count);
        m_EDMA3CC_regs.DMAQNUM[count >> 3u].reg |= n_EDMA::DMAQNUM_SET(count, que_num);
    }

    // FOR TYPE QDMA 
    // Enable the DMA (0 - 64) channels in the DRAE register
    //HWREG(baseAdd + EDMA3CC_QRAE(region_id)) = EDMA3_SET_ALL_BITS;
    m_EDMA3CC_regs.QRAE[(uint8_t)region_id].reg = n_EDMA::SET_ALL_BITS;

    // Initialize the QDMA Queue Number Registers
    for (count = 0; count < n_EDMA::AM335X_QDMACH_MAX; count++)
    {
        //HWREG(baseAdd + EDMA3CC_QDMAQNUM) &= EDMA3CC_QDMAQNUM_CLR(count);
        //HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= EDMA3CC_QDMAQNUM_SET(count,que_num);
        m_EDMA3CC_regs.QDMAQNUM.reg &= n_EDMA::QDMAQNUM_CLR(count);
        m_EDMA3CC_regs.QDMAQNUM.reg |= n_EDMA::QDMAQNUM_SET(count, que_num);
    }
}

void  AM335x_EDMA::set_non_idle_mode()
{      
    //m_EDMA3TC0_regs.SYSCONFIG.reg = 0x00000028;
    //m_EDMA3TC1_regs.SYSCONFIG.reg = 0x00000028;
    //m_EDMA3TC2_regs.SYSCONFIG.reg = 0x00000028;
    
    m_EDMA3TC0_regs.SYSCONFIG.b.IDLEMODE    = n_EDMA::SYSC_SMARTIDLE;
    m_EDMA3TC0_regs.SYSCONFIG.b.STANDBYMODE = n_EDMA::SYSC_SMARTSTBY;
    m_EDMA3TC1_regs.SYSCONFIG.b.IDLEMODE    = n_EDMA::SYSC_SMARTIDLE;
    m_EDMA3TC1_regs.SYSCONFIG.b.STANDBYMODE = n_EDMA::SYSC_SMARTSTBY;
    m_EDMA3TC2_regs.SYSCONFIG.b.IDLEMODE    = n_EDMA::SYSC_SMARTIDLE;
    m_EDMA3TC2_regs.SYSCONFIG.b.STANDBYMODE = n_EDMA::SYSC_SMARTSTBY;
}

/**
 * \brief  Enable channel to Shadow region mapping
 *
 * This API allocates DMA/QDMA channels or TCCs, and the same resources are 
 * enabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 *  \param   chtype      (DMA/QDMA) Channel
 *                        For Example: For DMA it is,
 *                        EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param   ch_num       Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void AM335x_EDMA::enable_ch_in_shadow_reg(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num)
{
    // Allocate the DMA/QDMA channel
    if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
    {
         // FOR TYPE EDMA
         if(ch_num < 32)
         {
              // Enable the DMA channel in the DRAE registers
              //HWREG(baseAdd + EDMA3CC_DRAE(region_id)) |= (0x01u << ch_num);
              get_DRAE_ptr(region_id)->reg |= (0x01u << ch_num);
         }
         else
         {
              // Enable the DMA channel in the DRAEH registers 
              //HWREG(baseAdd + EDMA3CC_DRAEH(region_id)) |= (0x01u << (ch_num - 32));
              get_DRAEH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
         }
        
    }
    else 
    if(n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
    {
        // FOR TYPE QDMA
        // Enable the QDMA channel in the DRAE/DRAEH registers 
        //HWREG(baseAdd + EDMA3CC_QRAE(region_id)) |= 0x01u << ch_num;
        m_EDMA3CC_regs.QRAE[region_id].reg |= 0x01u << ch_num;
    }
}

/**
 * \brief  Disable channel to Shadow region mapping
 *
 * This API allocates DMA/QDMA channels or TCCs, and the same resources are 
 * enabled in the shadow region specific register (DRAE/DRAEH/QRAE).
 * Here only one shadow region is used since, there is only one Master.
 *
 * \param   chtype    (DMA/QDMA) Channel
 *                      For Example: For DMA it is,
 *                      EDMA3_CHANNEL_TYPE_DMA.\n
 *
 * \param   ch_num      Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void AM335x_EDMA::disable_ch_in_shadow_reg(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num)
{
    /* Allocate the DMA/QDMA channel */
    if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
    {
         // FOR TYPE EDMA
         if(ch_num < 32)
         { 
              // Enable the DMA channel in the DRAE registers 
              //HWREG(baseAdd + EDMA3CC_DRAE(region_id)) &= ~(0x01u << ch_num);
              get_DRAE_ptr(region_id)->reg &= ~(0x01u << ch_num);
         }
         else
         {
              // Enable the DMA channel in the DRAEH registers
              //HWREG(baseAdd + EDMA3CC_DRAEH(region_id)) &= ~(0x01u << (ch_num - 32));
              get_DRAEH_ptr(region_id)->reg &= ~(0x01u << (ch_num - 32));
         }
    }
    else 
    if (n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
    {
        // FOR TYPE QDMA 
        // Enable the QDMA channel in the DRAE/DRAEH registers 
        //HWREG(baseAdd + EDMA3CC_QRAE(region_id)) &= ((~0x01u) << ch_num);
        m_EDMA3CC_regs.QRAE[region_id].reg &= ((~0x01u) << ch_num);
    }
}

/**
 *  \brief  Map channel to Event Queue
 *
 *  This API maps DMA/QDMA channels to the Event Queue
 *
 *  \param  chtype     (DMA/QDMA) Channel
 *                     For Example: For QDMA it is
 *                     EDMA3_CHANNEL_TYPE_QDMA.\n
 *
 *  \param  ch_num      Allocated channel number.\n
 *
 *  \param  evtQNum    Event Queue Number to which the channel
 *                     will be mapped (valid only for the
 *                     Master Channel (DMA/QDMA) request).\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void AM335x_EDMA::map_ch_to_evtQ(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, n_EDMA::e_DMA_QUEUE evt_Qnum)
{
    if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
    {
        // Associate DMA Channel to Event Queue 
        //HWREG(baseAdd + EDMA3CC_DMAQNUM((ch_num) >> 3u)) &=  EDMA3CC_DMAQNUM_CLR(ch_num);
        //HWREG(baseAdd + EDMA3CC_DMAQNUM((ch_num) >> 3u)) |= EDMA3CC_DMAQNUM_SET((ch_num), evt_Qnum);
        m_EDMA3CC_regs.DMAQNUM[ch_num >> 3u].reg &= n_EDMA::DMAQNUM_CLR(ch_num);
        m_EDMA3CC_regs.DMAQNUM[ch_num >> 3u].reg |= n_EDMA::DMAQNUM_SET(ch_num, evt_Qnum);
    }
    else 
    if (n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
    {
        // Associate QDMA Channel to Event Queue 
        //HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= EDMA3CC_QDMAQNUM_SET(ch_num, evt_Qnum);
        m_EDMA3CC_regs.QDMAQNUM.reg |= n_EDMA::QDMAQNUM_SET(ch_num, evt_Qnum);
    }
}

/**
 *  \brief  Remove Mapping of channel to Event Queue
 *
 *  This API Unmaps DMA/QDMA channels to the Event Queue allocated
 *
 *  \param  chtype     (DMA/QDMA) Channel
 *                     For Example: For DMA it is
 *                     EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param  ch_num      Allocated channel number.\n
 *
 *  chtype can have values
 *        EDMA3_CHANNEL_TYPE_DMA\n
 *        EDMA3_CHANNEL_TYPE_QDMA
 *
 *  \return  None
 */
void AM335x_EDMA::unmap_ch_to_evtQ(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num)
{
    if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
    {
        // Unmap DMA Channel to Event Queue
        //HWREG(baseAdd + EDMA3CC_DMAQNUM((ch_num) >> 3u)) |= EDMA3CC_DMAQNUM_CLR(ch_num);
        m_EDMA3CC_regs.DMAQNUM[ch_num >> 3u].reg |= n_EDMA::DMAQNUM_CLR(ch_num);
    }
    else 
    if (n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
    {
        // Unmap QDMA Channel to Event Queue
        //HWREG(baseAdd + EDMA3CC_QDMAQNUM) |= EDMA3CC_QDMAQNUM_CLR(ch_num);
        m_EDMA3CC_regs.QDMAQNUM.reg |= n_EDMA::QDMAQNUM_CLR(ch_num);
    }
}

/**
 *  \brief  Enables the user to map a QDMA channel to PaRAM set
 *          This API Needs to be called before programming the paRAM sets for
 *          the QDMA Channels.Application needs to maitain the paRAMId 
 *          provided by this API.This paRAMId is used to set paRAM and get
 *          paRAM. Refer corresponding API's for more details.
 *
 *  \param  ch_num                    Allocated QDMA channel number.\n
 *
 *  \param  paRaMID                  PaRAM Id to which the QDMA channel will be
 *                                   mapped to.
 *
 *  \return None
 *
 *  Note : The PaRAMId requested must be greater than 32(SOC_EDMA3_NUM_DMACH). 
 *         and lesser than SOC_EDMA3_NUM_DMACH + ch_num  Because, the first 
 *         32 PaRAM's are directly mapped to first 32 DMA channels and (32 - 38)
 *         for QDMA Channels. (32 - 38) is assigned by driver in this API. 
 *
 */
void AM335x_EDMA::map_QDMA_ch_to_paRAM(uint32_t ch_num, uint32_t *paRAM_id)
{
    /* First 32 channels are for DMA only                                   */
    /* if (((*paRAMId) > SOC_EDMA3_NUM_DMACH) &&
            ((*paRAMId) < SOC_EDMA3_NUM_DMACH+SOC_EDMA3_NUM_QDMACH))  */ 
    if ((n_EDMA::AM335X_DMACH_MAX + ch_num) == (*paRAM_id))
    {
        // Map Parameter RAM Set Number for specified channelId 
        //HWREG(baseAdd + EDMA3CC_QCHMAP(ch_num)) &= EDMA3CC_QCHMAP_PAENTRY_CLR;
        //HWREG(baseAdd + EDMA3CC_QCHMAP(ch_num)) |= EDMA3CC_QCHMAP_PAENTRY_SET(*paRAM_id);
        m_EDMA3CC_regs.QCHMAP[ch_num].b.PAENTRY = 0; 
        m_EDMA3CC_regs.QCHMAP[ch_num].b.PAENTRY = (*paRAM_id); 
    }
    else
    {
        (*paRAM_id) = (n_EDMA::AM335X_DMACH_MAX + ch_num);
        // Map Parameter RAM Set Number for specified channelId 
        //HWREG(baseAdd + EDMA3CC_QCHMAP(ch_num)) &= EDMA3CC_QCHMAP_PAENTRY_CLR;
        //HWREG(baseAdd + EDMA3CC_QCHMAP(ch_num)) |= EDMA3CC_QCHMAP_PAENTRY_SET(*paRAM_id);
        m_EDMA3CC_regs.QCHMAP[ch_num].b.PAENTRY = 0; 
        m_EDMA3CC_regs.QCHMAP[ch_num].b.PAENTRY = (*paRAM_id);
    }
}

/**
 * \brief  Assign a Trigger Word to the specified QDMA channel
 *
 * This API sets the Trigger word for the specific QDMA channel in the QCHMAP
 * Register. Default QDMA trigger word is CCNT.
 *
 * \param  ch_num               QDMA Channel which needs to be assigned
 *                             the Trigger Word
 *
 * \param  trigWord            The Trigger Word for the QDMA channel.
 *                             Trigger Word is the word in the PaRAM
 *                             Register Set which, when written to by CPU,
 *                             will start the QDMA transfer automatically.
 *
 * \return  None
 */
void AM335x_EDMA::set_QDMA_trig_word(uint32_t ch_num, uint8_t trig_word)
{
     // Set the Trigger Word
     //HWREG(baseAdd + EDMA3CC_QCHMAP(ch_num)) |= EDMA3CC_QCHMAP_TRWORD_SET(trigWord);
     m_EDMA3CC_regs.QCHMAP[ch_num].b.TRWORD = trig_word;
}

/**
 *  \brief   Enables the user to Clear any missed event
 *
 *  \param   ch_num                  Allocated channel number.\n
 * 
 *  \return  None
 */
void AM335x_EDMA::clr_miss_evt(uint32_t ch_num)
{
    if(ch_num < 32)
    {         
         //HWREG(baseAdd + EDMA3CC_S_SECR(region_id)) = (0x01u << ch_num);    // clear SECR to clean any previous NULL request         
         //HWREG(baseAdd + EDMA3CC_EMCR) |= (0x01u <<  ch_num);               //clear EMCR to clean any previous NULL request
         n_EDMA::get_S_SECR_ptr(region_id)->reg = (0x01u << ch_num);    // clear SECR to clean any previous NULL request         
         m_EDMA3CC_regs.EMCR.reg |= (0x01u <<  ch_num);               //clear EMCR to clean any previous NULL request
    }
    else
    { 
         //HWREG(baseAdd + EDMA3CC_S_SECRH(region_id)) = (0x01u << (ch_num - 32));         
         //HWREG(baseAdd + EDMA3CC_EMCRH) |= (0x01u <<  (ch_num - 32));         //clear EMCRH to clean any previous NULL request
         n_EDMA::get_S_SECR_ptr(region_id)->reg = (0x01u << (ch_num - 32));         
         m_EDMA3CC_regs.EMCRH.reg |= (0x01u <<  (ch_num - 32));               //clear EMCRH to clean any previous NULL request
    }
}

/**
 *  \brief   Enables the user to Clear any QDMA missed event
 *
 *  \param   ch_num                  Allocated channel number.\n
 * 
 *  \return  None
 */
void AM335x_EDMA::QDMA_clr_miss_evt(uint32_t ch_num)
{
    // clear SECR to clean any previous NULL request                        
    //HWREG(baseAdd + EDMA3CC_S_QSECR(region_id)) = (0x01u << ch_num);
    n_EDMA::get_S_QSECR_ptr(region_id)->reg = (0x01u << ch_num);
    
    // clear EMCR to clean any previous NULL request                       
    //HWREG(baseAdd + EDMA3CC_QEMCR) |= (0x01u <<  ch_num);
    m_EDMA3CC_regs.QEMCR.reg |= (0x01u <<  ch_num);
}

/**
 *  \brief   Enables the user to Clear any Channel controller Errors
 *
 *  \param   Flags                Masks to be passed.\n
 *
 *  Flags can have values:
 *
 *  EDMA3CC_CLR_TCCERR            Clears the TCCERR bit in the EDMA3CC 
 *                                ERR Reg\n
 *  EDMA3CC_CLR_QTHRQ0            Queue threshold error clear for queue 0.\n
 *  EDMA3CC_CLR_QTHRQ1            Queue threshold error clear for queue 1.
 *
 *  \return  None
 */
void AM335x_EDMA::clr_CCERR(uint32_t flags)
{
    // (CCERRCLR) - clear channel controller error register
    //HWREG(baseAdd + EDMA3CC_CCERRCLR) = Flags;
    m_EDMA3CC_regs.CCERRCLR.reg = flags;
}

/**
 *  \brief   Enables the user to Set an event. This API helps user to manually 
 *           set events to initiate DMA transfer requests.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void AM335x_EDMA::set_evt(uint32_t ch_num)
{
    if(ch_num < 32)
    { 
         // (ESR) - set corresponding bit to set a event
         //HWREG(baseAdd + EDMA3CC_S_ESR(region_id)) |= (0x01u <<  ch_num);
         n_EDMA::get_S_ESR_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
    else
    {
         // (ESRH) - set corresponding bit to set a event  
         //HWREG(baseAdd + EDMA3CC_S_ESRH(region_id)) |= (0x01u << (ch_num - 32));
         n_EDMA::get_S_ESRH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
    }
}

/**
 *  \brief   Enables the user to Clear an event.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   This API is generally used during Manual transfers.\n
 */
void AM335x_EDMA::clr_evt(uint32_t ch_num)
{
    if(ch_num < 32)
    {
         // (ECR) - set corresponding bit to clear a event 
         //HWREG(baseAdd + EDMA3CC_S_ECR(region_id)) |= (0x01u <<  ch_num);
         n_EDMA::get_S_ECR_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
    else
    {
         // (ECRH) - set corresponding bit to clear a event 
         //HWREG(baseAdd + EDMA3CC_S_ECRH(region_id)) |= (0x01u << (ch_num - 32));
         n_EDMA::get_S_ECRH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
    }
}

/**
 *  \brief   Enables the user to enable an DMA event.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in EESR sets the corresponding event 
 *           bits in EER. This is generally used for Event Based transfers.\n
 */
void AM335x_EDMA::enable_DMA_evt(uint32_t ch_num)
{
    if(ch_num < 32)
    { 
         // (EESR) - set corresponding bit to enable DMA event
         //HWREG(baseAdd + EDMA3CC_S_EESR(region_id)) |= (0x01u <<  ch_num);
        n_EDMA::get_S_EESR_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
    else
    { 
         // (EESRH) - set corresponding bit to enable DMA event
         //HWREG(baseAdd + EDMA3CC_S_EESRH(region_id)) |= (0x01u << (ch_num - 32));
        n_EDMA::get_S_EESRH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
    }
}

/**
 *  \brief   Enables the user to Disable an DMA event.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in EECR clear the corresponding event bits 
 *           in EER; writes of 0 have no effect.. This is generally used for 
 *           Event Based transfers.\n
 */
void AM335x_EDMA::disable_DMA_evt(uint32_t ch_num)
{
    if(ch_num < 32)
    {
         // (EECR) - set corresponding bit to disable event
         //HWREG(baseAdd + EDMA3CC_S_EECR(region_id)) |= (0x01u <<  ch_num);
        n_EDMA::get_S_EECR_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
    else
    {
         // (EECRH) - set corresponding bit to disable event
         //HWREG(baseAdd + EDMA3CC_S_EECRH(region_id)) |= (0x01u <<  ch_num);
        n_EDMA::get_S_EECRH_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
}

/**
 *  \brief   Enables the user to enable an QDMA event.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in QEESR sets the corresponding event 
              bits in QEER.\n
 */
void AM335x_EDMA::enable_QDMA_evt(uint32_t ch_num)
{
    // (QEESR) - set corresponding bit to enable QDMA event 
    //HWREG(baseAdd + EDMA3CC_S_QEESR(region_id)) = (0x01u << ch_num);
    n_EDMA::get_S_QEESR_ptr(region_id)->reg = (0x01u << ch_num);
}

/**
 *  \brief   Enables the user to disable an QDMA event.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in QEECR clears the corresponding event 
              bits in QEER.\n
 */
void AM335x_EDMA::disable_QDMA_evt(uint32_t ch_num)
{
    // (QEESR) - set corresponding bit to enable QDMA event
    //HWREG(baseAdd + EDMA3CC_S_QEECR(region_id)) = (0x01u << ch_num);
    n_EDMA::get_S_QEECR_ptr(region_id)->reg = (0x01u << ch_num);
}

/**
 *  \brief   This function returns interrupts status of those events
 *           which is less than 32.
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
uint32_t AM335x_EDMA::get_intr_status()
{
    uint32_t intr_sts = 0;

    //intr_sts = (uint32_t)HWREG(baseAdd + EDMA3CC_S_IPR(region_id));
    intr_sts = (uint32_t)n_EDMA::get_S_IPR_ptr(region_id)->reg;

    return intr_sts;
}


/**
 *  \brief   Enables the user to enable the transfer completion interrupt 
 *           generation by the EDMA3CC for all DMA/QDMA channels.
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   To set any interrupt bit in IER, a 1 must be written to the 
 *           corresponding interrupt bit in the interrupt enable set register.
 */
void AM335x_EDMA::enable_evt_intr(uint32_t ch_num)
{    
    if(ch_num < 32)
    {
         //  Interrupt Enable Set Register (IESR)
         // HWREG(baseAdd + EDMA3CC_S_IESR(region_id)) |= (0x01u <<  ch_num);
         n_EDMA::get_S_IESR_ptr(region_id)->reg |= (0x01u <<  ch_num);;
    }
    else
    {
         //  Interrupt Enable Set Register (IESRH)
         // HWREG(baseAdd + EDMA3CC_S_IESRH(region_id)) |= (0x01u << (ch_num - 32));
         n_EDMA::get_S_IESRH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
    }
}

/**
 *  \brief   Enables the user to clear CC interrupts
 *
 *  \param   ch_num                  Allocated channel number.\n
 *
 *  \return  None
 *
 *  Note :   Writes of 1 to the bits in IECR clear the corresponding interrupt 
 *           bits in the interrupt enable registers (IER); writes of 0 have 
 *           no effect.\n
 */
void AM335x_EDMA::disable_evt_intr(uint32_t ch_num)
{
    if(ch_num < 32)
    {
         // Interrupt Enable Clear Register (IECR)
         // HWREG(baseAdd + EDMA3CC_S_IECR(region_id)) |= (0x01u <<  ch_num);
        n_EDMA::get_S_IECR_ptr(region_id)->reg |= (0x01u <<  ch_num);
    }
    else
    {
         // Interrupt Enable Clear Register (IECRH)
         // HWREG(baseAdd + EDMA3CC_S_IECRH(region_id)) |= (0x01u << (ch_num - 32));
        n_EDMA::get_S_IECRH_ptr(region_id)->reg |= (0x01u << (ch_num - 32));
    }
}

/**
 *  \brief   Enables the user to Clear an Interrupt.
 *
 *  \param   value                  Value to be set to clear the Interrupt Status.
 *
 *  \return  None
 *
 */
void AM335x_EDMA::clr_intr(uint32_t value)
{
    if(value < 32)
    {
         //HWREG(baseAdd + EDMA3CC_S_ICR(region_id)) = (1u << value);
        n_EDMA::get_S_ICR_ptr(region_id)->reg = (1u << value);
    }
    else
    {
         //HWREG(baseAdd + EDMA3CC_S_ICRH(region_id)) = (1u << (value - 32));
         n_EDMA::get_S_ICRH_ptr(region_id)->reg = (1u << (value - 32));
    }
}


/**
 *  \brief   Retrieve existing PaRAM set associated with specified logical
 *           channel (DMA/Link).
 *  
 *  \param   ch_num                  Logical Channel whose PaRAM set is
 *                                  requested.\n
 *  
 *  \param   currPaRAM              User gets the existing PaRAM here.\n
 *  
 *  \return  None
 */
n_EDMA::paRAM_entry_t* AM335x_EDMA::get_paRAM(uint32_t paRAM_id)
{
    uint32_t *sr = n_EDMA::get_paRAM_ptr(paRAM_id);
    
    return reinterpret_cast<n_EDMA::paRAM_entry_t*>(sr);    
}

/**
 * \brief   Retrieve existing PaRAM set associated with specified logical
 *          channel (QDMA).
 * 
 * \param   ch_num                  Logical Channel whose PaRAM set is
 *                                 requested.\n
 * 
 * \param   currPaRAM              User gets the existing PaRAM here.\n
 * 
 * \return  None
 */
n_EDMA::paRAM_entry_t* AM335x_EDMA::QDMA_get_paRAM(uint32_t paRAM_id)
{
    uint32_t *sr = n_EDMA::get_paRAM_ptr(paRAM_id);
    
    return reinterpret_cast<n_EDMA::paRAM_entry_t*>(sr); 
}

/**
 * \brief   Copy the user specified PaRAM Set onto the PaRAM Set associated 
 *          with the logical channel (DMA/Link).
 *
 * This API takes a PaRAM Set as input and copies it onto the actual PaRAM Set
 * associated with the logical channel. OPT field of the PaRAM Set is written
 * first and the CCNT field is written last.
 *
 *
 * \param   ch_num                  Logical Channel whose PaRAM set is
 *                                 requested.\n
 *
 * \param   newPaRAM               Parameter RAM set to be copied onto existing
 *                                 PaRAM.\n
 *
 * \return  None
 */
void AM335x_EDMA::set_paRAM(uint32_t ch_num, n_EDMA::paRAM_entry_t* new_paRAM)
{  
    n_EDMA::paRAM_entry_t *dist = get_paRAM(ch_num);
 
    *dist = *new_paRAM;
}

/**
 * \brief   Copy the user specified PaRAM Set onto the PaRAM Set associated 
 *          with the logical channel (QDMA only).
 *
 * This API takes a PaRAM Set as input and copies it onto the actual PaRAM Set
 * associated with the logical channel. OPT field of the PaRAM Set is written
 * first and the CCNT field is written last.
 *
 *
 * \param   ch_num                 Logical Channel whose PaRAM set is
 *                                 requested.\n
 *
 * \param  paRaMID                 PaRAM Id to which the QDMA channel is
 *                                 mapped to. 
 *
 * \param   newPaRAM               Parameter RAM set to be copied onto existing
 *                                 PaRAM.\n
 *
 * \return  None
 */
void AM335x_EDMA::QDMA_set_paRAM(uint32_t paRAM_id, n_EDMA::paRAM_entry_t* new_paRAM)
{
    n_EDMA::paRAM_entry_t *dist = get_paRAM(paRAM_id);
 
    *dist = *new_paRAM;
}

/**
 * \brief   Set a particular PaRAM set entry of the specified PaRAM set
 *
 * \param   paRaMID           PaRAM Id to which the QDMA channel is
 *                            mapped to.
 *
 * \param   paRAMEntry        Specify the PaRAM set entry which needs
 *                            to be set.
 *
 * \param   newPaRAMEntryVal  The new field setting. Make sure this field is 
 *                            packed for setting certain fields in paRAM.
 *
 *  paRAMEntry can have values:
 *
 *  EDMA3CC_PARAM_ENTRY_OPT
 *  EDMA3CC_PARAM_ENTRY_SRC
 *  EDMA3CC_PARAM_ENTRY_ACNT_BCNT
 *  EDMA3CC_PARAM_ENTRY_DST
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX
 *  EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX
 *  EDMA3CC_PARAM_ENTRY_CCNT
 * 
 * \return  None
 *
 * \note    This API should be used while setting the PaRAM set entry
 *          for QDMA channels. If EDMA3QdmaSetPaRAMEntry() used,
 *          it will trigger the QDMA channel before complete
 *          PaRAM set entry is written.
 */
void AM335x_EDMA::QDMA_set_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry, uint32_t new_paRAM_entry_val)
{
    uint32_t *dist = reinterpret_cast<uint32_t *>(get_paRAM(paRAM_id));
    
    if((paRAM_entry > n_EDMA::PARAM_ENTRY_OPT) || 
       (paRAM_entry < n_EDMA::PARAM_ENTRY_CCNT))
    {
        dist += (uint32_t)(paRAM_entry * 0x04); 
       *dist = new_paRAM_entry_val;
    }
}

/**
 * \brief   Get a particular PaRAM entry of the specified PaRAM set
 *
 * \param   paRaMID           PaRAM Id to which the QDMA channel is
 *                            mapped to.
 *
 * \param   paRAMEntry        Specify the PaRAM set entry which needs
 *                            to be read.
 *
 *  paRAMEntry can have values:
 *
 *  EDMA3CC_PARAM_ENTRY_OPT
 *  EDMA3CC_PARAM_ENTRY_SRC
 *  EDMA3CC_PARAM_ENTRY_ACNT_BCNT
 *  EDMA3CC_PARAM_ENTRY_DST
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_BIDX
 *  EDMA3CC_PARAM_ENTRY_LINK_BCNTRLD
 *  EDMA3CC_PARAM_ENTRY_SRC_DST_CIDX
 *  EDMA3CC_PARAM_ENTRY_CCNT
 *
 * \return  paRAMEntryVal     The value of the paRAM field pointed by the  
 *                            paRAMEntry.
 *
 * \note    This API should be used while reading the PaRAM set entry
 *          for QDMA channels. And the paRAMEntryVal is a packed value for
 *          certain fields of paRAMEntry.The user has to make sure the value 
 *          is unpacked appropriately.
 *          For example, the third field is A_B_CNT. Hence he will have to
 *          unpack it to two 16 bit fields to get ACNT and BCNT.
 */
uint32_t AM335x_EDMA::QDMA_get_paRAM_entry(uint32_t paRAM_id, uint32_t paRAM_entry)
{
    uint32_t *src = reinterpret_cast<uint32_t *>(get_paRAM(paRAM_id));
    
    if((paRAM_entry > n_EDMA::PARAM_ENTRY_OPT) ||
       (paRAM_entry < n_EDMA::PARAM_ENTRY_CCNT))
    {
        src += (uint32_t)(paRAM_entry * 0x04);
    }
    
    return (*src);
}

/**
 *  \brief Request a DMA/QDMA/Link channel.
 *
 *  Each channel (DMA/QDMA/Link) must be requested  before initiating a DMA
 *  transfer on that channel.
 *
 *  This API is used to allocate a logical channel (DMA/QDMA/Link) along with
 *  the associated resources. For DMA and QDMA channels, TCC and PaRAM Set are
 *  also allocated along with the requested channel.
 *  
 *  User can request a specific logical channel by passing the channel number
 *  in 'ch_num'.
 *  
 *  For DMA/QDMA channels, after allocating all the EDMA3 resources, this API
 *  sets the TCC field of the OPT PaRAM Word with the allocated TCC. It also sets
 *  the event queue for the channel allocated. The event queue needs to be
 *  specified by the user.
 *  
 *  For DMA channel, it also sets the DCHMAP register.
 *  
 *  For QDMA channel, it sets the QCHMAP register and CCNT as trigger word and
 *  enables the QDMA channel by writing to the QEESR register.
 *
 *  \param  chtype                   (DMA/QDMA) Channel
 *                                    For Example: For DMA it is
 *                                    EDMA3_CHANNEL_TYPE_DMA.\n
 *
 *  \param  ch_num                    This is the channel number requested for a
 *                                   particular event.\n
 *
 *  \param  tccNum                   The channel number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be mapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  \return  TRUE if parameters are valid, else FALSE
 */
bool  AM335x_EDMA::request_channel(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t tcc_num, n_EDMA::e_DMA_QUEUE evt_Qnum)
{
    bool ret_val = false;
    
    if (ch_num < n_EDMA::AM335X_DMACH_MAX)
    {
        //Enable the DMA channel in the enabled in the shadow region
        //specific register
        enable_ch_in_shadow_reg(ch_type, ch_num);
        map_ch_to_evtQ(ch_type, ch_num, evt_Qnum);
        
        if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
        {
            // Interrupt channel nums are < 32 
            if (tcc_num < n_EDMA::AM335X_DMACH_MAX)
            {
                // Enable the Event Interrupt
                enable_evt_intr(ch_num);
                ret_val = true;
            }
            //HWREG(baseAdd + EDMA3CC_OPT(ch_num)) &= EDMA3CC_OPT_TCC_CLR;
            //HWREG(baseAdd + EDMA3CC_OPT(ch_num)) |= EDMA3CC_OPT_TCC_SET(tcc_num);
            get_paRAM(ch_num)->OPT.b.TCC = LOW;
            get_paRAM(ch_num)->OPT.b.TCC = tcc_num;
        }
        else 
        if (n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
        {
            // Interrupt channel nums are < 8 
            if (tcc_num < n_EDMA::AM335X_QDMACH_MAX)
            {
                // Enable the Event Interrupt
                enable_evt_intr(ch_num);
                ret_val = true;
            } 
            //HWREG(baseAdd + EDMA3CC_OPT(ch_num)) &= EDMA3CC_OPT_TCC_CLR;
            //HWREG(baseAdd + EDMA3CC_OPT(ch_num)) |= EDMA3CC_OPT_TCC_SET(tcc_num);
            get_paRAM(ch_num)->OPT.b.TCC = LOW;
            get_paRAM(ch_num)->OPT.b.TCC = tcc_num;
        }
    }
    return ret_val;
}

/**
 *  \brief    Free the specified channel (DMA/QDMA/Link) and its associated
 *            resources (PaRAM Set, TCC etc) and removes various mappings.
 *  
 *  For Link channels, this API only frees the associated PaRAM Set.
 *  
 *  For DMA/QDMA channels, it does the following operations:
 *  1) Disable any ongoing transfer on the channel,\n
 *  2) Remove the channel to Event Queue mapping,\n
 *  3) For DMA channels, clear the DCHMAP register, if available\n
 *  4) For QDMA channels, clear the QCHMAP register,\n
 *  5) Frees the DMA/QDMA channel in the end.\n
 *
 *  \param  chtype              (DMA/QDMA) Channel
 *                     For Example: For QDMA it is,
 *                     EDMA3_CHANNEL_TYPE_QDMA.\n
 *
 *  \param  ch_num                    This is the channel number requested for a
 *                      particular event.\n
 *
 *  \param  trigMode                 Mode of triggering start of transfer.\n
 *
 *  \param  tccNum                   The channel number on which the
 *                                   completion/error interrupt is generated.
 *                                   Not used if user requested for a Link
 *                                   channel.\n
 *
 *  \param  evtQNum                  Event Queue Number to which the channel
 *                                   will be unmapped (valid only for the
 *                                   Master Channel (DMA/QDMA) request).\n
 *
 *  trigMode can have values:
 *        EDMA3_TRIG_MODE_MANUAL\n
 *        EDMA3_TRIG_MODE_QDMA\n
 *        EDMA3_TRIG_MODE_EVENT
 *
 *  \return  TRUE if parameters are valid else return FALSE
 */
bool  AM335x_EDMA::free_channel(n_EDMA::e_EDMA3_CH_TYPE ch_type, uint32_t ch_num, uint32_t trig_mode, uint32_t tcc_num, n_EDMA::e_DMA_QUEUE evt_Qnum)
{
    bool ret_val = false;
    
    if (ch_num < n_EDMA::AM335X_DMACH_MAX)
    {
        disable_transfer(ch_num, trig_mode);
        
        // Disable the DMA channel in the shadow region specific register 
        disable_ch_in_shadow_reg(ch_type, ch_num);

        unmap_ch_to_evtQ(ch_type, ch_num);
        
        if (n_EDMA::CHANNEL_TYPE_DMA == ch_type)
        {
            // Interrupt channel nums are < 32
            if (tcc_num < n_EDMA::AM335X_DMACH_MAX)
            {
                // Disable the DMA Event Interrupt                            */
                disable_evt_intr(ch_num);
                ret_val = true;
            }
        }
        else if (n_EDMA::CHANNEL_TYPE_QDMA == ch_type)
        {
            // Interrupt channel nums are < 8 
            if (tcc_num < n_EDMA::AM335X_QDMACH_MAX)
            {
                // Disable the QDMA Event Interrupt                           */
                disable_evt_intr(ch_num);
                ret_val = true;
            }
        }
    }
    
    return ret_val;
}

/**
 *  \brief    Start EDMA transfer on the specified channel.
 *
 *  There are multiple ways to trigger an EDMA3 transfer. The triggering mode
 *  option allows choosing from the available triggering modes: Event,
 *  Manual or QDMA.
 *  
 *  In event triggered, a peripheral or an externally generated event triggers
 *  the transfer. This API clears the Event and Event Miss Register and then
 *  enables the DMA channel by writing to the EESR.
 *  
 *  In manual triggered mode, CPU manually triggers a transfer by writing a 1
 *  in the Event Set Register ESR. This API writes to the ESR to start the 
 *  transfer.
 *  
 *  In QDMA triggered mode, a QDMA transfer is triggered when a CPU (or other
 *  EDMA3 programmer) writes to the trigger word of the QDMA channel PaRAM set
 *  (auto-triggered) or when the EDMA3CC performs a link update on a PaRAM set
 *  that has been mapped to a QDMA channel (link triggered). This API enables
 *  the QDMA channel by writing to the QEESR register.
 *
 *  \param  ch_num           Channel being used to enable transfer.\n
 *
 *  \param  trig_mode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *
 *  trig_mode can have values:
 *        EDMA3_TRIG_MODE_MANUAL\n
 *        EDMA3_TRIG_MODE_QDMA\n
 *        EDMA3_TRIG_MODE_EVENT\n
 *
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
bool  AM335x_EDMA::enable_transfer(uint32_t ch_num, uint32_t trig_mode)
{
    bool ret_val = false;
    
    switch (trig_mode)
    {
        case n_EDMA::TRIG_MODE_MANUAL :
            if (ch_num < n_EDMA::AM335X_DMACH_MAX)
            {
                set_evt(ch_num);
                ret_val = true;
            }
           break;
    
        case n_EDMA::TRIG_MODE_QDMA :
            if (ch_num < n_EDMA::AM335X_QDMACH_MAX)
            {
                enable_QDMA_evt(ch_num);
                ret_val = true;
            }
        break;
    
        case n_EDMA::TRIG_MODE_EVENT :
            if (ch_num < n_EDMA::AM335X_DMACH_MAX)
            {
                //clear SECR & EMCR to clean any previous NULL request
                clr_miss_evt(ch_num);

                // Set EESR to enable event
                enable_DMA_evt(ch_num);
                ret_val = true;
            }
        break;
    
        default :
            ret_val = false;
        break;
    }
    
    return ret_val;
}

/**
 *  \brief   Disable DMA transfer on the specified channel
 *  
 *  There are multiple ways by which an EDMA3 transfer could be triggered.
 *  The triggering mode option allows choosing from the available triggering
 *  modes.
 *  
 *  To disable a channel which was previously triggered in manual mode,
 *  this API clears the Secondary Event Register and Event Miss Register,
 *  if set, for the specific DMA channel.
 *  
 *  To disable a channel which was previously triggered in QDMA mode, this
 *  API clears the QDMA Event Enable Register, for the specific QDMA channel.
 *  
 *  To disable a channel which was previously triggered in event mode, this API
 *  clears the Event Enable Register, Event Register, Secondary Event Register
 *  and Event Miss Register, if set, for the specific DMA channel.
 *
 *
 *  \param  ch_num           Channel being used to enable transfer.\n
 *
 *  \param  trigMode        Mode of triggering start of transfer (Manual,
 *                          QDMA or Event).\n
 *
 *  trigMode can have values:
 *        EDMA3_TRIG_MODE_MANUAL
 *        EDMA3_TRIG_MODE_QDMA
 *        EDMA3_TRIG_MODE_EVENT
 *
 *  \return  retVal         TRUE or FALSE depending on the param passed.\n
 *
 */
bool  AM335x_EDMA::disable_transfer(uint32_t ch_num, uint32_t trig_mode)
{
    bool ret_val = false;
    
    switch (trig_mode)
    {
        case n_EDMA::TRIG_MODE_MANUAL :
            if (ch_num < n_EDMA::AM335X_DMACH_MAX)
            {
                clr_evt(ch_num);
                ret_val = true;
            }
        break;
    
        case n_EDMA::TRIG_MODE_QDMA :
            if (ch_num < n_EDMA::AM335X_QDMACH_MAX)
            {
                disable_QDMA_evt(ch_num);
                ret_val = true;
            }
        break;
    
        case n_EDMA::TRIG_MODE_EVENT :
            if (ch_num < n_EDMA::AM335X_DMACH_MAX)
            {
                // clear SECR & EMCR to clean any previous NULL request
                clr_miss_evt(ch_num);

                // Set EESR to enable event
                disable_DMA_evt(ch_num);
                ret_val = true;
            }
        break;
    
        default :
            ret_val = false;
        break;
    }
    
    return ret_val;
}


/**
 *  \brief  Clears Event Register and Error Register for a specific
 *          DMA channel and brings back EDMA3 to its initial state.
 *
 *  This API clears the Event register, Event Miss register, Event Enable
 *  register for a specific DMA channel. It also clears the CC Error register.
 *
 *  \param  ch_num           This is the channel number requested for a
 *                          particular event.\n
 *
 *  \param  evtQNum         Event Queue Number to which the channel
 *                          will be unmapped (valid only for the
 *                          Master Channel (DMA/QDMA) request).\n
 *
 *  \return none.\n
 */
void AM335x_EDMA::clear_error_bits(uint32_t ch_num, n_EDMA::e_DMA_QUEUE evt_Qnum)
{
    if(ch_num < n_EDMA::AM335X_DMACH_MAX)
    {
         if(ch_num < 32)
         {
              //HWREG(baseAdd + EDMA3CC_S_EECR(region_id)) = (0x01u << ch_num);              
              //HWREG(baseAdd + EDMA3CC_EMCR) = (0x01u << ch_num);                // Write to EMCR to clear the corresponding EMR bit              
              //HWREG(baseAdd + EDMA3CC_S_SECR(region_id)) = (0x01u << ch_num);   // Clears the SER               
              get_S_EECR_ptr(region_id)->reg = (0x01u << ch_num);
              m_EDMA3CC_regs.EMCR.reg = (0x01u << ch_num);                  // Write to EMCR to clear the corresponding EMR bit                 
              get_S_SECR_ptr(region_id)->reg = (0x01u << ch_num);     // Clears the SER 

         }
         else
         {
              //HWREG(baseAdd + EDMA3CC_S_EECRH(region_id)) = (0x01u << (ch_num - 32));              
              //HWREG(baseAdd + EDMA3CC_EMCRH) = (0x01u << (ch_num - 32));        // Write to EMCR to clear the corresponding EMR bi              
              //HWREG(baseAdd + EDMA3CC_S_SECRH(region_id)) = (0x01u << (ch_num - 32));   // Clears the SER              
              get_S_EECRH_ptr(region_id)->reg = (0x01u << (ch_num - 32));             
              m_EDMA3CC_regs.EMCRH.reg = (0x01u << (ch_num - 32));                // Write to EMCRH to clear the corresponding EMR bi              
              get_S_SECRH_ptr(region_id)->reg = (0x01u << (ch_num - 32));   // Clears the SER
         }

    }

    // Clear the global CC Error Register
    /*
    if (0 == evt_Qnum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD0 | EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(1 == evt_Qnum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD1 | EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(2 == evt_Qnum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD2 | EDMA3CC_CCERRCLR_TCCERR);
    }
    else if(3 == evt_Qnum)
    {
         HWREG(baseAdd + EDMA3CC_CCERRCLR) &= (EDMA3CC_CCERRCLR_QTHRXCD2 | EDMA3CC_CCERRCLR_TCCERR);
    }
    */
    
    switch(evt_Qnum)
    {
        case n_EDMA::EVENT_Q0:
          m_EDMA3CC_regs.CCERRCLR.b.QTHRXCD0 = LOW;
          m_EDMA3CC_regs.CCERRCLR.b.TCCERR = LOW;
          break;
        case n_EDMA::EVENT_Q1:
          m_EDMA3CC_regs.CCERRCLR.b.QTHRXCD1 = LOW;
          m_EDMA3CC_regs.CCERRCLR.b.TCCERR = LOW;
          break;
        case n_EDMA::EVENT_Q2:
          m_EDMA3CC_regs.CCERRCLR.b.QTHRXCD2 = LOW;
          m_EDMA3CC_regs.CCERRCLR.b.TCCERR = LOW;
          break;
        default:
          break;
    }
}

/**
 *  \brief   This returns EDMA3 CC error status.
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
uint32_t AM335x_EDMA::get_CCERR_status()
{
    uint32_t intr_status_val = 0;
  
    //intr_status_val = (uint32_t)HWREG(baseAdd + EDMA3CC_CCERR);
    intr_status_val = m_EDMA3CC_regs.CCERR.reg;

    return intr_status_val;
}

/**
 *  \brief   This returns error interrupt status for those events whose
 *           event number is less than 32.
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
uint32_t AM335x_EDMA::get_ERR_intr_status()
{
    uint32_t intr_status_val = 0;

    //intr_status_val = (uint32_t)HWREG(baseAdd + EDMA3CC_EMR);
    intr_status_val = m_EDMA3CC_regs.EMR.reg;

    return intr_status_val;
}

/**
 *  \brief   This returns QDMA error interrupt status.
 *
 *  \return  value              Status of the QDMA Interrupt Pending Register
 *
 */
n_EDMA::QEMR_reg_t AM335x_EDMA::QDMA_get_ERR_intr_status()
{
    n_EDMA::QEMR_reg_t intr_status_val = {.reg = 0};

    //intr_status_val = (uint32_t)HWREG(baseAdd + EDMA3CC_QEMR);
    intr_status_val.reg = m_EDMA3CC_regs.QEMR.reg;

    return intr_status_val;
}

/**
 *  \brief   This API enables to evaluate the subsequent errors. On writing 
 *           to the EEVAL register EDMA3CC error interrupt will be reasserted, 
 *           if there are any outstanding error bits set due to subsequent 
 *           error conditions.
 *
 *  \param  baseAddr         Memory address of the EDMA instance used.
 *
 *  \return  None
 */
void AM335x_EDMA::CCERR_evaluate()
{
    //HWREG(baseAddr + EDMA3CC_EEVAL) = EDMA3CC_EEVAL_EVAL << EDMA3CC_EEVAL_EVAL_SHIFT;
    m_EDMA3CC_regs.EEVAL.b.EVAL = HIGH;
}

/**
 *  \brief   EDMA3 Deinitialization
 *  
 *  This function deinitializes the EDMA3 Driver
 *  Clears the error specific registers (EMCR/EMCRh, QEMCR, CCERRCLR) &
 *  deinitialize the Queue Number Registers
 *  
 *  \param  queNum          Event Queue used 
 *  
 *  \return  None
 *  
 *  \note     The region_id is the shadow region(0 or 1) used and the,
 *            Event Queue used is either (0 or 1). There are only two shadow regions
 *            and only two event Queues
 */
void AM335x_EDMA::deinit(uint32_t que_num)
{
    uint32_t count = 0;
    n_EDMA::CCERRCLR_reg_t ccerr = { .reg = 0 };
    
    ccerr.b.TCCERR = HIGH;
    
    // Disable the DMA (0 - 62) channels in the DRAE register
    //HWREG(baseAdd + EDMA3CC_DRAE(region_id)) = EDMA3_CLR_ALL_BITS;
    //HWREG(baseAdd + EDMA3CC_DRAEH(region_id)) = EDMA3_CLR_ALL_BITS;
    get_DRAE_ptr(region_id)->reg = n_EDMA::CLR_ALL_BITS;
    get_DRAEH_ptr(region_id)->reg = n_EDMA::CLR_ALL_BITS;
    
    clr_CCERR(ccerr.reg);
    
    // Clear the Event miss Registers
    //HWREG(baseAdd + EDMA3CC_EMCR)  = EDMA3_SET_ALL_BITS;
    //HWREG(baseAdd + EDMA3CC_EMCRH) = EDMA3_SET_ALL_BITS;
    m_EDMA3CC_regs.EMCR.reg = n_EDMA::CLR_ALL_BITS;
    m_EDMA3CC_regs.EMCRH.reg = n_EDMA::CLR_ALL_BITS;
    // Clear CCERR register
    //HWREG(baseAdd + EDMA3CC_CCERRCLR) = EDMA3_SET_ALL_BITS;
    m_EDMA3CC_regs.CCERRCLR.reg = n_EDMA::SET_ALL_BITS;
      
    // Deinitialize the Queue Number Registers
    for (count = 0;count < n_EDMA::AM335X_DMACH_MAX; count++)
    {
        //HWREG(baseAdd + EDMA3CC_DMAQNUM(count >> 3u)) &= EDMA3CC_DMAQNUM_CLR(count);
        m_EDMA3CC_regs.DMAQNUM[count >> 3u].reg &= n_EDMA::DMAQNUM_CLR(count);
    }

    for (count = 0;count < n_EDMA::AM335X_QDMACH_MAX; count++)
    {
        m_EDMA3CC_regs.QDMAQNUM.reg &= n_EDMA::QDMAQNUM_CLR(count);
    }
}

/**
 * \brief   This API return the revision Id of the peripheral.
 *
 *  \return  None
 */
uint32_t AM335x_EDMA::peripheral_id_get()
{
    //return (HWREG(baseAdd + EDMA3CC_REVID));
    return m_EDMA3CC_regs.PID.reg;
}

/**
 *  \brief   This function returns interrupts status of those events
 *           which is greater than 32.
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
uint32_t AM335x_EDMA::intr_status_high_get()
{
    uint32_t intr_sts_val = 0;

    //intr_sts_val = (uint32_t)HWREG(baseAdd + EDMA3CC_S_IPRH(region_id));
    intr_sts_val = get_S_IPRH_ptr(region_id)->reg;

    return intr_sts_val;
}


/**
 *  \brief   This returns error interrupt status for those events whose
 *           event number is greater than 32.
 *
 *  \return  value                  Status of the Interrupt Pending Register
 *
 */
uint32_t AM335x_EDMA::ERR_intr_high_status_get()
{
    uint32_t intr_sts_val = 0;

    //intr_sts_val = (uint32_t)HWREG(baseAdd + EDMA3CC_EMRH);
    intr_sts_val = m_EDMA3CC_regs.EMRH.reg;

    return intr_sts_val;
}


/**
 *  \brief   This function maps DMA channel to any of the PaRAM sets
 *           in the PaRAM memory map.
 *
 *  \param   channel   The DMA channel number required to be mapped.
 *
 *  \param   paramSet  It specifies the paramSet to which DMA channel
 *                     required to be mapped.
 *
 *  \return  None
 */
void AM335x_EDMA::channel_to_param_map(uint32_t channel, uint32_t param_set)
{
    //HWREG(baseAdd + EDMA3CC_DCHMAP(channel)) = paramSet << 5;
    m_EDMA3CC_regs.DCHMAP[channel].b.PAENTRY = param_set;
} 
/**
 *  \brief   This API can be used to save the register context for EDMA
 *
 *  \param  edmaCntxPtr     Pointer to the structure where the context
 *                          needs to be saved.
 *
 *  \return  None
 */
void AM335x_EDMA::context_save(n_EDMA::EDMACONTEXT_t *p_edma_cntx)
{
    uint32_t i;
    uint32_t max_par = 128;

    // Get the Channel mapping reg Val    
    for(i = 0; i < n_EDMA::AM335X_DMACH_MAX; i++)
    {
         // All events are one to one mapped with the channels         
         //p_edma_cntx->dch_map[i] = HWREG(baseAddr + EDMA3CC_DCHMAP(i));
         p_edma_cntx->dch_map[i] = m_EDMA3CC_regs.DCHMAP[i].b.PAENTRY;
    }
      
    // Get DMA Queue Number Register Val
    for(i = 0; i < n_EDMA::AM335X_QDMACH_MAX; i++)
    {    
        //p_edma_cntx->dma_Qnum[i] = HWREG(baseAddr + EDMA3CC_DMAQNUM((i)));
        p_edma_cntx->dma_Qnum[i] = m_EDMA3CC_regs.DMAQNUM[i].reg;    
    }         

    // Get the DMA Region Access Enable Register val               
    //p_edma_cntx->reg_acc_enable_low = HWREG(baseAddr + EDMA3CC_DRAE(0));            
    //p_edma_cntx->reg_acc_enable_high = HWREG(baseAddr + EDMA3CC_DRAEH(0));            
    p_edma_cntx->reg_acc_enable_low = n_EDMA::get_DRAE_ptr(region_id)->reg;            
    p_edma_cntx->reg_acc_enable_high = n_EDMA::get_DRAEH_ptr(region_id)->reg;
    
    // Get Event Set Register value        
    //p_edma_cntx->event_set_reg_low  = HWREG(baseAddr + EDMA3CC_S_ESR(0));                
    //p_edma_cntx->event_set_reg_high = HWREG(baseAddr + EDMA3CC_S_ESRH(0));                    
    p_edma_cntx->event_set_reg_low  = n_EDMA::get_S_ESR_ptr(region_id)->reg;                
    p_edma_cntx->event_set_reg_high = n_EDMA::get_S_ESRH_ptr(region_id)->reg;
    
    // Get Event Enable Set Register value      
    //p_edma_cntx->enable_evt_set_reg_low = HWREG(baseAddr + EDMA3CC_S_EER(0));                   
    //p_edma_cntx->enable_evt_set_reg_high = HWREG(baseAddr + EDMA3CC_S_EERH(0)); 
    p_edma_cntx->enable_evt_set_reg_low =  n_EDMA::get_S_EER_ptr(region_id)->reg;                   
    p_edma_cntx->enable_evt_set_reg_high = n_EDMA::get_S_EERH_ptr(region_id)->reg;   
          
    // Get Interrupt Enable Set Register value           
    p_edma_cntx->int_enable_set_reg_low  =  n_EDMA::get_S_IER_ptr(region_id)->reg;                     
    p_edma_cntx->int_enable_set_reg_high =  n_EDMA::get_S_IERH_ptr(region_id)->reg;                        


    if(n_EDMA::EDMA_REVID == version_get())
    {
        max_par = 256;
    }

    for(i = 0; i < max_par; i++)
    {
        // Get the  PaRAM  values           
        p_edma_cntx->dma_par_entry[i] = *get_paRAM(i);
    }                         
}

/**
 *  \brief   This API can be used to restore the register context for EDMA
 *
 *  \param  edmaCntxPtr     Pointer to the structure where the context
 *                          needs to be restored from.
 *
 *  \return  None
 */
void AM335x_EDMA::context_restore(n_EDMA::EDMACONTEXT_t *p_edma_cntx)
{
    uint32_t i;
    uint32_t max_par = 128;
  
    // set the Channel mapping reg Val
    for(i = 0; i < n_EDMA::AM335X_DMACH_MAX; i++)
    {
         // All events are one to one mapped with the channels       
         //HWREG(baseAddr + EDMA3CC_DCHMAP(i)) = p_edma_cntx->dch_map[i];
         m_EDMA3CC_regs.DCHMAP[i].b.PAENTRY = p_edma_cntx->dch_map[i];
    }
      
    // set DMA Queue Number Register Val
    for(i  =0; i < n_EDMA::AM335X_QDMACH_MAX; i++)
    {    
        //HWREG(baseAddr + EDMA3CC_DMAQNUM((i))) = p_edma_cntx->dma_Qnum[i];
        m_EDMA3CC_regs.DMAQNUM[i].reg = p_edma_cntx->dma_Qnum[i]; 
    }         

    // set the DMA Region Access Enable Register val               
    //HWREG(baseAddr + EDMA3CC_DRAE(0)) = p_edma_cntx->reg_acc_enable_low;
    //HWREG(baseAddr + EDMA3CC_DRAEH(0)) = p_edma_cntx->reg_acc_enable_high; 
    n_EDMA::get_DRAE_ptr(region_id)->reg = p_edma_cntx->reg_acc_enable_low;
    n_EDMA::get_DRAEH_ptr(region_id)->reg = p_edma_cntx->reg_acc_enable_high;
    
    // set Event Set Register value 
    //HWREG(baseAddr + EDMA3CC_S_ESR(0)) = p_edma_cntx->event_set_reg_low;                
    //HWREG(baseAddr + EDMA3CC_S_ESRH(0)) = p_edma_cntx->event_set_reg_high;
    n_EDMA::get_S_ESR_ptr(region_id)->reg = p_edma_cntx->event_set_reg_low;                
    n_EDMA::get_S_ESRH_ptr(region_id)->reg = p_edma_cntx->event_set_reg_high;
                  
    // set Event Enable Set Register value
    //HWREG(baseAddr + EDMA3CC_S_EESR(0)) = p_edma_cntx->enable_evt_set_reg_low;                   
    //HWREG(baseAddr + EDMA3CC_S_EESRH(0)) = p_edma_cntx->enable_evt_set_reg_high; 
    n_EDMA::get_S_EER_ptr(region_id)->reg = p_edma_cntx->enable_evt_set_reg_low;                   
    n_EDMA::get_S_EERH_ptr(region_id)->reg = p_edma_cntx->enable_evt_set_reg_high;
          
    // set Interrupt Enable Set Register value
    //HWREG(baseAddr + EDMA3CC_S_IESR(0)) = p_edma_cntx->int_enable_set_reg_low;                    
    //HWREG(baseAddr + EDMA3CC_S_IESRH(0)) = p_edma_cntx->int_enable_set_reg_high;  
    n_EDMA::get_S_IER_ptr(region_id)->reg = p_edma_cntx->int_enable_set_reg_low;                    
    n_EDMA::get_S_IERH_ptr(region_id)->reg = p_edma_cntx->int_enable_set_reg_high;  

    if(n_EDMA::EDMA_REVID == version_get())
    {
        max_par = 256;
    }

    for(i = 0; i < max_par; i++)
    {
        // Set the  PaRAM  values          
        set_paRAM(i,(n_EDMA::paRAM_entry_t*)(&(p_edma_cntx->dma_par_entry[i])));
    }                      
}

AM335x_EDMA eDMA;
