#ifndef _AM3358ZCZ_PINS_H
#define _AM3358ZCZ_PINS_H

namespace PINS
{
    template <typename T, uint32_t pinnum, uint32_t ctrlm_reg> 
    class pin;

    enum class e_GPMC_A5 : uint8_t
    {    
        gpmc_a5         = 0, // O 
        gmii2_txd0      = 1, // O
        rgmii2_td0      = 2, // O
        rmii2_txd0      = 3, // O
        gpmc_a21        = 4, // O
        pr1_mii1_rxd3   = 5, // I
        eQEP1B_in       = 6, // I
        gpio1_21        = 7, // I/O
    
    };
    extern pin<e_GPMC_A5, 21U, 0x854>  gpmc_a5;

    enum class e_GPMC_A6 : uint8_t
    {    
        gpmc_a6         = 0, // O 
        gmii2_txclk     = 1, // I
        rgmii2_tclk     = 2, // O
        mmc2_dat4       = 3, // I/O
        gpmc_a22        = 4, // O
        pr1_mii1_rxd2   = 5, // I
        eQEP1_index     = 6, // I/O
        gpio1_22        = 7, // I/O
    
    };
    extern pin<e_GPMC_A6, 22U, 0x858>  gpmc_a6;

    enum class e_GPMC_A7 : uint8_t
    {    
        gpmc_a7         = 0, // O 
        gmii2_rxclk     = 1, // I
        rgmii2_rclk     = 2, // I
        mmc2_dat5       = 3, // I/O
        gpmc_a23        = 4, // O
        pr1_mii1_rxd1   = 5, // I
        eQEP1_strobe    = 6, // I/O
        gpio1_23        = 7, // I/O
    
    };
    extern pin<e_GPMC_A7, 23U, 0x85C>  gpmc_a7;

    enum class e_GPMC_A8 : uint8_t
    {    
        gpmc_a8         = 0, // O
        gmii2_rxd3      = 1, // I
        rgmii2_rd3      = 2, // I
        mmc2_dat6       = 3, // I/O
        gpmc_a24        = 4, // O
        pr1_mii1_rxd0   = 5, // I
        mcasp0_aclkx    = 6, // I/O
        gpio1_24        = 7, // I/O
    
    };
    extern  pin<e_GPMC_A8, 24U, 0x860>  gpmc_a8;

    enum class e_GPMC_WAIT0 : uint8_t
    { 
        gpmc_wait0      = 0, // I 
        gmii2_crs       = 1, // I
        gpmc_csn4       = 2, // O
        rmii2_crs_dv    = 3, // I
        mmc1_sdcd       = 4, // I
        pr1_mii1_col    = 5, // I
        uart4_rxd       = 6, // I
        gpio0_30        = 7, // I/O
    };
    extern       pin<e_GPMC_WAIT0, 30U, 0x870>  gpmc_wait0;

    enum class e_UART1_RTSn : uint8_t
    { 
        uart1_rtsn          = 0, // O 
        timer5              = 1, // I/O
        dcan0_rx            = 2, // I
        I2C2_SCL            = 3, // I/OD
        spi1_cs1            = 4, // I/O
        pr1_uart0_rts_n     = 5, // O
        pr1_edc_latch1_in   = 6, // I
        gpio0_13            = 7  // I/O
    };
    extern  pin<e_UART1_RTSn, 13U, 0x97C>  uart1_rtsn;

    enum class e_UART1_CTSn : uint8_t
    { 
        uart1_ctsn          = 0, // I 
        timer6              = 1, // I/O
        dcan0_tx            = 2, // O
        I2C2_SDA            = 3, // I/OD
        spi1_cs0            = 4, // I/O
        pr1_uart0_cts_n     = 5, // I
        pr1_edc_latch0_in   = 6, // I
        gpio0_12            = 7  // I/O
    };
    extern       pin<e_UART1_CTSn, 12U, 0x978>  uart1_ctsn;

    enum class e_XDMA_EVENT_INTR1 : uint8_t
    { 
        xdma_event_intr1    = 0, // I 
        tclkin              = 2, // I
        clkout2             = 3, // O
        timer7              = 4, // I/O
        pr1_pru0_pru_r31_16 = 5, // I
        EMU3                = 6, // I/O
        gpio0_20            = 7, // I/O
    };
    extern pin<e_XDMA_EVENT_INTR1, 20U, 0x9B4>  xdma_event_intr1; 

} // namespace PINS

#endif // _AM3358ZCZ_PINS_H