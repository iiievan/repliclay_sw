#ifndef _CONTROL_MODULE_H_
#define _CONTROL_MODULE_H_

#include <stdint.h>
#include "app_utils.h"

//This control module namespace
namespace CONTROL_MODULE
{ 
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_CTRL_MODULE_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/      
    


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////    ALL CONTROL MODULE REGISTERS BLOCKS   //////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct AM335x_CTRL_MODULE_Type
    {                                                                                      
        __  _reg_t       control_revision;         // (0x00)  
        __  _reg_t       control_hwinfo;          // (0x04) 
        __  uint32_t     RESERVED[1]; 
        __  _reg_t       control_sysconfig;         // (0x0C)   
        __  _reg_t       control_status;            // (0x14)  
        __  _reg_t       control_emif_sdram_config; // (0x18)  
        __  _reg_t       core_sldo_ctrl;            // (0x1C)  
        __  _reg_t       mpu_sldo_ctrl;             // (0x24)  
        __  _reg_t       clk32kdivratio_ctrl;       // (0x28)  
        __  _reg_t       bandgap_ctrl;              // (0x2C)  
        __  _reg_t       bandgap_trim;              // (0x30)  
        __  _reg_t       pll_clkinpulow_ctrl;       // (0x34)  
        __  _reg_t       mosc_ctrl;                 // (0x38)  
        __  _reg_t       deepsleep_ctrl;            // (0x3C)  
        __  _reg_t       dpll_pwr_sw_status;        // (0x150)
        __  _reg_t       device_id;                 // (0x150)
        __  _reg_t       dev_feature;               // (0x150)
        __  _reg_t       init_priority_0;           // (0x150)
        __  _reg_t       init_priority_1;           // (0x150)
        __  _reg_t       tptc_cfg;                  // (0x150)
        __  _reg_t       usb_ctrl0;                 // (0x150)
        __  _reg_t       usb_sts0;                  // (0x150) 
        __  _reg_t       usb_ctrl1;                 // (0x150)
        __  _reg_t       usb_sts1;                  // (0x150)
        __  _reg_t       mac_id0_lo;                // (0x150)
        __  _reg_t       mac_id0_hi;                // (0x150)
        __  _reg_t       mac_id1_lo;                // (0x150)
        __  _reg_t       mac_id1_hi;                // (0x150)
        __  _reg_t       dcan_raminit;              // (0x150)
        __  _reg_t       usb_wkup_ctrl;             // (0x150)
        __  _reg_t       gmii_sel;                  // (0x150)
        __  _reg_t       pwmss_ctrl;                // (0x150)
        __  _reg_t       mreqprio_0;                // (0x150)
        __  _reg_t       mreqprio_1;                // (0x150)
        __  _reg_t       hw_event_sel_grp1;         // (0x150)
        __  _reg_t       hw_event_sel_grp2;         // (0x150)
        __  _reg_t       hw_event_sel_grp3;         // (0x150)
        __  _reg_t       hw_event_sel_grp4;         // (0x150)
        __  _reg_t       smrt_ctrl;                 // (0x150)
        __  _reg_t       mpuss_hw_debug_sel;        // (0x150)
        __  _reg_t       mpuss_hw_dbg_info;         // (0x150)
        __  _reg_t       vdd_mpu_opp_050;           // (0x150)
        __  _reg_t       vdd_mpu_opp_100;           // (0x150)
        __  _reg_t       vdd_mpu_opp_120;           // (0x150)
        __  _reg_t       vdd_mpu_opp_turbo;         // (0x150)
        __  _reg_t       vdd_core_opp_050;          // (0x150)
        __  _reg_t       vdd_core_opp_100;          // (0x150)
        __  _reg_t       bb_scale;                  // (0x150)
        __  _reg_t       usb_vid_pid;               // (0x150)
        __  _reg_t       efuse_sma;                 // (0x150)
        __  _reg_t       conf_gpmc_ad0;             // (0x150)
        __  _reg_t       conf_gpmc_ad1;             // (0x150)
        __  _reg_t       conf_gpmc_ad2;             // (0x150)
        __  _reg_t       conf_gpmc_ad3;             // (0x150)
        __  _reg_t       conf_gpmc_ad4;             // (0x150)
        __  _reg_t       conf_gpmc_ad5;             // (0x150)
        __  _reg_t       conf_gpmc_ad6;             // (0x150)
        __  _reg_t       conf_gpmc_ad7;             // (0x150)
        __  _reg_t       conf_gpmc_ad8;             // (0x150)
        __  _reg_t       conf_gpmc_ad9;             // (0x150)
        __  _reg_t       conf_gpmc_ad10;            // (0x150)
        __  _reg_t       conf_gpmc_ad11;            // (0x150)
        __  _reg_t       conf_gpmc_ad12;            // (0x150)
        __  _reg_t       conf_gpmc_ad13;            // (0x150)
        __  _reg_t       conf_gpmc_ad14;            // (0x150)
        __  _reg_t       conf_gpmc_ad15;            // (0x150)
        __  _reg_t       conf_gpmc_a0;              // (0x150)
        __  _reg_t       conf_gpmc_a1;              // (0x150)
        __  _reg_t       conf_gpmc_a2;              // (0x150)
        __  _reg_t       conf_gpmc_a3;              // (0x150)
        __  _reg_t       conf_gpmc_a4;              // (0x150)
        __  _reg_t       conf_gpmc_a5;              // (0x150)
        __  _reg_t       conf_gpmc_a6;              // (0x150)
        __  _reg_t       conf_gpmc_a7;              // (0x150)
        __  _reg_t       conf_gpmc_a8;              // (0x150)
        __  _reg_t       conf_gpmc_a9;              // (0x150)
        __  _reg_t       conf_gpmc_a10;             // (0x150)
        __  _reg_t       conf_gpmc_a11;             // (0x150)
        __  _reg_t       conf_gpmc_wait0;           // (0x150)
        __  _reg_t       conf_gpmc_wpn;             // (0x150)
        __  _reg_t       conf_gpmc_ben1;            // (0x150)
        __  _reg_t       conf_gpmc_csn0;            // (0x150)
        __  _reg_t       conf_gpmc_csn1;            // (0x150)
        __  _reg_t       conf_gpmc_csn2;            // (0x150)
        __  _reg_t       conf_gpmc_csn3;            // (0x150)
        __  _reg_t       conf_gpmc_clk;             // (0x150)
        __  _reg_t       conf_gpmc_advn_ale;        // (0x150)
        __  _reg_t       conf_gpmc_oen_ren;         // (0x150)
        __  _reg_t       conf_gpmc_wen;             // (0x150)
        __  _reg_t       conf_gpmc_ben0_cle;        // (0x150)
        __  _reg_t       conf_lcd_data0;            // (0x150)
        __  _reg_t       conf_lcd_data1;            // (0x150)
        __  _reg_t       conf_lcd_data2;            // (0x150)
        __  _reg_t       conf_lcd_data3;            // (0x150)
        __  _reg_t       conf_lcd_data4;            // (0x150)
        __  _reg_t       conf_lcd_data5;            // (0x150)
        __  _reg_t       conf_lcd_data6;            // (0x150)
        __  _reg_t       conf_lcd_data7;            // (0x150)
        __  _reg_t       conf_lcd_data8;            // (0x150)
        __  _reg_t       conf_lcd_data9;            // (0x150)
        __  _reg_t       conf_lcd_data10;           // (0x150)
        __  _reg_t       conf_lcd_data11;           // (0x150)
        __  _reg_t       conf_lcd_data12;           // (0x150)
        __  _reg_t       conf_lcd_data13;           // (0x150)
        __  _reg_t       conf_lcd_data14;           // (0x150)
        __  _reg_t       conf_lcd_data15;           // (0x150)
        __  _reg_t       conf_lcd_vsync;            // (0x150)
        __  _reg_t       conf_lcd_hsync;            // (0x150)
        __  _reg_t       conf_lcd_pclk;             // (0x150)
        __  _reg_t       conf_lcd_ac_bias_en;       // (0x150)
        __  _reg_t       conf_mmc0_dat3;            // (0x150)
        __  _reg_t       conf_mmc0_dat2;            // (0x150)
        __  _reg_t       conf_mmc0_dat1;            // (0x150)
        __  _reg_t       conf_mmc0_dat0;            // (0x150)
        __  _reg_t       conf_mmc0_clk;             // (0x150)
        __  _reg_t       conf_mmc0_cmd;             // (0x150)
        __  _reg_t       conf_mii1_col;             // (0x150)
        __  _reg_t       conf_mii1_crs;             // (0x150)
        __  _reg_t       conf_mii1_rx_er;           // (0x150)
        __  _reg_t       conf_mii1_tx_en;           // (0x150)
        __  _reg_t       conf_mii1_rx_dv;           // (0x150)
        __  _reg_t       conf_mii1_txd3;            // (0x150)
        __  _reg_t       conf_mii1_txd2;            // (0x150)
        __  _reg_t       conf_mii1_txd1;            // (0x150)
        __  _reg_t       conf_mii1_txd0;            // (0x150)
        __  _reg_t       conf_mii1_tx_clk;          // (0x150)
        __  _reg_t       conf_mii1_rx_clk;          // (0x150)
        __  _reg_t       conf_mii1_rxd3;            // (0x150)
        __  _reg_t       conf_mii1_rxd2;            // (0x150)
        __  _reg_t       conf_mii1_rxd1;            // (0x150)
        __  _reg_t       conf_mii1_rxd0;            // (0x150)
        __  _reg_t       conf_rmii1_ref_clk;        // (0x150)
        __  _reg_t       conf_mdio;                 // (0x150)
        __  _reg_t       conf_mdc;                  // (0x150)
        __  _reg_t       conf_spi0_sclk;            // (0x150)
        __  _reg_t       conf_spi0_d0;              // (0x150)
        __  _reg_t       conf_spi0_d1;              // (0x150)
        __  _reg_t       conf_spi0_cs0;             // (0x150)
        __  _reg_t       conf_spi0_cs1;             // (0x150)
        __  _reg_t       conf_ecap0_in_pwm0_out;    // (0x150)
        __  _reg_t       conf_uart0_ctsn;           // (0x150)
        __  _reg_t       conf_uart0_rtsn;           // (0x150)
        __  _reg_t       conf_uart0_rxd;            // (0x150)
        __  _reg_t       conf_uart0_txd;            // (0x150)
        __  _reg_t       conf_uart1_ctsn;           // (0x150)
        __  _reg_t       conf_uart1_rtsn;           // (0x150)
        __  _reg_t       conf_uart1_rxd;            // (0x150)
        __  _reg_t       conf_uart1_txd;            // (0x150)
        __  _reg_t       conf_i2c0_sda;             // (0x150)
        __  _reg_t       conf_i2c0_scl;             // (0x150)
        __  _reg_t       conf_mcasp0_aclkx;         // (0x150)
        __  _reg_t       conf_mcasp0_fsx;           // (0x150)
        __  _reg_t       conf_mcasp0_axr0;          // (0x150)
        __  _reg_t       conf_mcasp0_ahclkr;        // (0x150)
        __  _reg_t       conf_mcasp0_aclkr;         // (0x150)
        __  _reg_t       conf_mcasp0_fsr;           // (0x150)
        __  _reg_t       conf_mcasp0_axr1;          // (0x150)
        __  _reg_t       conf_mcasp0_ahclkx;        // (0x150)
        __  _reg_t       conf_xdma_event_intr0;     // (0x150)
        __  _reg_t       conf_xdma_event_intr1;     // (0x150)
        __  _reg_t       conf_warmrstn;             // (0x150)
        __  _reg_t       conf_nnmi;                 // (0x150)
        __  _reg_t       conf_tms;                  // (0x150)
        __  _reg_t       conf_tdi;                  // (0x150)
        __  _reg_t       conf_tdo;                  // (0x150)
        __  _reg_t       conf_tck;                  // (0x150)
        __  _reg_t       conf_trstn;                // (0x150)
        __  _reg_t       conf_emu0;                 // (0x150)
        __  _reg_t       conf_emu1;                 // (0x150)
        __  _reg_t       conf_rtc_pwronrstn;        // (0x150)
        __  _reg_t       conf_pmic_power_en;        // (0x150)
        __  _reg_t       conf_ext_wakeup;           // (0x150)
        __  _reg_t       conf_usb0_drvvbus;         // (0x150)
        __  _reg_t       conf_usb1_drvvbus;         // (0x150)
        __  _reg_t       cqdetect_status;           // (0x150)
        __  _reg_t       ddr_io_ctrl;               // (0x150)
        __  _reg_t       vtp_ctrl;                  // (0x150)
        __  _reg_t       vref_ctrl;                 // (0x150)
        __  _reg_t       tpcc_evt_mux_0_3;          // (0x150)
        __  _reg_t       tpcc_evt_mux_4_7;          // (0x150)
        __  _reg_t       tpcc_evt_mux_8_11;         // (0x150)
        __  _reg_t       tpcc_evt_mux_12_15;        // (0x150)
        __  _reg_t       tpcc_evt_mux_16_19;        // (0x150)
        __  _reg_t       tpcc_evt_mux_20_23;        // (0x150)
        __  _reg_t       tpcc_evt_mux_24_27;        // (0x150)
        __  _reg_t       tpcc_evt_mux_28_31;        // (0x150)
        __  _reg_t       tpcc_evt_mux_32_35;        // (0x150)
        __  _reg_t       tpcc_evt_mux_36_39;        // (0x150)
        __  _reg_t       tpcc_evt_mux_40_43;        // (0x150)
        __  _reg_t       tpcc_evt_mux_44_47;        // (0x150)
        __  _reg_t       tpcc_evt_mux_48_51;        // (0x150)
        __  _reg_t       tpcc_evt_mux_52_55;        // (0x150)
        __  _reg_t       tpcc_evt_mux_56_59;        // (0x150)
        __  _reg_t       tpcc_evt_mux_60_63;        // (0x150)
        __  _reg_t       timer_evt_capt;            // (0x150)
        __  _reg_t       ecap_evt_capt;             // (0x150)
        __  _reg_t       adc_evt_capt;              // (0x150)
        __  _reg_t       reset_iso;                 // (0x150)
        __  _reg_t       dpll_pwr_sw_ctrl;          // (0x150)
        __  _reg_t       ddr_cke_ctrl;              // (0x150)
        __  _reg_t       sma2;                      // (0x150)
        __  _reg_t       m3_txev_eoi;               // (0x150)
        __  _reg_t       ipc_msg_reg0;              // (0x150)
        __  _reg_t       ipc_msg_reg1;              // (0x150)
        __  _reg_t       ipc_msg_reg2;              // (0x150)
        __  _reg_t       ipc_msg_reg3;              // (0x150)
        __  _reg_t       ipc_msg_reg4;              // (0x150)
        __  _reg_t       ipc_msg_reg5;              // (0x150)
        __  _reg_t       ipc_msg_reg6;              // (0x150)
        __  _reg_t       ipc_msg_reg7;              // (0x150)
        __  _reg_t       ddr_cmd0_ioctrl;           // (0x150)
        __  _reg_t       ddr_cmd1_ioctrl;           // (0x150)
        __  _reg_t       ddr_cmd2_ioctrl;           // (0x150)
        __  _reg_t       ddr_data0_ioctrl;          // (0x150)
        __  _reg_t       ddr_data1_ioctrl;          // (0x150)
    };

    constexpr uint32_t AM335x_PRCM_BASE         = 0x44E00000; 

    /************************************************************************ ALL POINTERS ON PRCM MODULE BLOCKS ***********************************************************************************************/

    constexpr AM335x_CM_PER_Type        *AM335x_CM_PER      = ((AM335x_CM_PER_Type *) AM335x_CM_PER_BASE); 
    
    uint32_t debug_dump_CM_PER(AM335x_CM_PER_Type &sCM_PER = *AM335x_CM_PER);
    /* for testing purpose */
    inline uint32_t debug_dump_CM_PER(AM335x_CM_PER_Type &sCM_PER)
    {
          constexpr uint32_t COUNTOF_CM_PER = sizeof(AM335x_CM_PER_Type)/sizeof(uint32_t);
          volatile uint32_t TSTREG[COUNTOF_CM_PER] = {0};          
          uint32_t *pAM335x_CM_PER = (uint32_t *)&sCM_PER;
          
          //volatile uint32_t TSTREG1 = (uint32_t)m_sCM_PER.GPIO1_CLKCTRL.reg;
          //volatile uint32_t TSTREG2 = (uint32_t)m_sCM_PER.GPIO2_CLKCTRL.reg;
          //volatile uint32_t TSTREG3 = (uint32_t)sCM_PER.GPIO3_CLKCTRL.reg;
          //volatile uint32_t TSTREG4 = (uint32_t)sCM_PER.EPWMSS1_CLKCTRL.reg;
          volatile uint32_t SIZEOF_CM_PER = sizeof(AM335x_CM_PER_Type); 
          
          for(uint32_t i = 0 ; i < COUNTOF_CM_PER; i++)
          {   
                TSTREG[i] = pAM335x_CM_PER[i];
          }
          
          return SIZEOF_CM_PER;
    }
}

namespace DMTIMER
{
    struct AM335x_DMTIMER_Type;
    enum e_TIMER_NUM : uint8_t;
}

extern power_reset_clock_control prcm_module;


#endif //_PRCM_H_