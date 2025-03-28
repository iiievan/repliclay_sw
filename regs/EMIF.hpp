#ifndef _EMIF_H_
#define _EMIF_H_

#include <stdint.h>

namespace REGS
{
    //This is EMIF namespace
    namespace EMIF
    { 
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_DDR23mPHY_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      
        
        /* [reset state = 0x80] [offset = 0x01C, 0x050, 0x084]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    CMD_SLAVE_RATIO  :10;     // bit: 0..9   (W) Ratio value for address/command launch timing in DDR PHY macro. This is the fraction of a
                                                      //                 clock cycle represented by the shift to be applied to the read DQS in units of 256ths. In other
                                                      //                 words, the full-cycle tap value from the master DLL will be scaled by this number over 256 to
                                                      //                 get the delay value for the slave delay line.
                                                      //                 [values 0-100h]
                uint32_t                     :22;     // bit: 10..31 (R)  Reserved             
            } b;                                      // Structure used for bit access 
            uint32_t  reg;                            // Type used for register access 
        } CSR0_reg_t;

        /* [reset state = 0x4] [offset = 0x028, 0x05C, 0x090]*/
        typedef union 
        {                                 /* This register should
                                           * be left at its default value and should not be altered for proper operation.
                                           */
            struct 
            {                                         
                uint32_t    DLL_LOCK_DIFF  :4;      // bit: 0..3  (W) The max number of delay line taps variation allowed while maintaining the master DLL lock.This is
                                                    //                calculated as total jitter/ delay line tap size, where total jitter is half of (incoming clock jitter (pp) +
                                                    //                delay line jitter (pp)). 
                                                    //                [values 0-4h]
                uint32_t                   :28;     // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DLD0_reg_t;

        /* [reset state = 0x0] [offset = 0x0x02C, 0x060, 0x094]*/
        typedef union 
        {                                           /* 
                                                     */
            struct 
            {                                         
                uint32_t    INVERT_CLK_SEL  :1;      // bit: 0     (W) Inverts the polarity of DRAM clock.
                                                     //                [0x0 = Core clock is passed on to DRAM, 
                                                     //                 0x1 = inverted core clock is passed on to DRAM]
                uint32_t                    :31;     // bit: 1..31 (R)  Reserved             
            } b;                                     // Structure used for bit access 
            uint32_t  reg;                           // Type used for register access 
        } ICLK0_reg_t;

        /* [reset state = 0x04010040] [offset = 0x0C8, 0x16C]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    RD_DQS_SLAVE_RATIO_CS0  :10;    // bit: 0..9   (W) Ratio value for Read DQS slave DLL for CS0.
                                                            //                 40h This is the fraction of a clock cycle represented by the shift to be applied to the read DQS in units of
                                                            //                 256ths. In other words, the full-cycle tap value from the master DLL will be scaled by this number
                                                            //                 over 256 to get the delay value for the slave delay line. 
                                                            //                 [values 0-40h]
                uint32_t                            :22;    // bit: 10..31 (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } RDQSSR0_reg_t;

        /* [reset state = 0x0] [offset = 0x0DC, 0x180]*/
        typedef union 
        {                                            /* 
                                                      */
            struct 
            {                                         
                uint32_t    WR_DQS_SLAVE_RATIO_CS0  :10;      // bit: 0..9   (W) Ratio value for Write DQS slave DLL for CS0.
                                                              //                 This is the fraction of a clock cycle represented by the shift to be applied to the write DQS in
                                                              //                 units of 256ths. In other words, the full-cycle tap value from the master DLL will be scaled by
                                                              //                 this number over 256 to get the delay value for the slave delay line. [values 0-40h]
                uint32_t                            :22;      // bit: 10..31 (R)  Reserved             
            } b;                                              // Structure used for bit access 
            uint32_t  reg;                                    // Type used for register access 
        } WDQSSR0_reg_t;

        /* [reset state = 0x0] [offset = 0x0F0, 0x194]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WRLVL_INIT_RATIO_CS0  :10;      // bit: 0..9   (W)  The user programmable init ratio used by Write Leveling FSM when
                                                            //                  DATA0/1_REG_PHY_WRLVL_INIT_MODE_0 register value set to 1

                uint32_t                          :22;      // bit: 10..31 (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } MWRLVLINI_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x0F8, 0x19C]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WRLVL_INIT_MODE_SEL  :1;        // bit: 0       (W) The user programmable init ratio selection mode for Write Leveling FSM.
                                                            //                  [0x0 = Selects a starting ratio value based on Write Leveling of previous data slice;
                                                            //                   0x1 = Selects a starting ratio value based in register DATA0/1_REG_PHY_WRLVL_INIT_RATIO_0 value programmed by the user.]                
                uint32_t                         :31;       // bit: 1..31   (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } MWRLVLINI_MODE_reg_t;

        /* [reset state = 0x0] [offset = 0x0FC, 0x1A0]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    GATELVL_INIT_RATIO_CS0  :10;    // bit: 0..9    (W) The user programmable init ratio used by DQS Gate Training FSM when
                                                            //                  DATA0/1/_REG_PHY_GATELVL_INIT_MODE_0 register value set to 1.
                uint32_t                            :22;    // bit: 10..31  (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } DQSGTI_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x104, 0x1A8]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    GATELVL_INIT_MODE_SEL  :1;      // bit: 0       (W)  User programmable init ratio selection mode for DQS Gate Training FSM.
                                                            //                  [0x0 Selects a starting ratio value based on Write Leveling of the same data slice;
                                                            //                   0x1 selects a starting ratio value based on DATA0/1_REG_PHY_GATELVL_INIT_RATIO_0 value programmed by the user]
                uint32_t                           :31;     // bit: 1..31   (R)  Reserved             
            } b;                                            // Structure used for bit access 
            uint32_t  reg;                                  // Type used for register access 
        } DQS_GTI_MODE_reg_t;

        /* [reset state = 0x0] [offset = 0x108, 0x1AC]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    FIFO_WE_SLAVE_RATIO_CS0     :10;    // bit: 0..9    (W) Ratio value for fifo we for CS0.
                uint32_t                                :22;    // bit: 10..31  (R) Reserved             
            } b;                                                // Structure used for bit access 
            uint32_t  reg;                                      // Type used for register access 
        } DQS_GS_RATIO_reg_t;

        /* [reset state = 0x4] [offset = 0x11C, 0x1C0]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    OFFSET  :7;     // bit: 0..6   (RW) Default value 40 equates to a 90 degree shift.
                uint32_t            :25;    // bit: 7..31 (R)  Reserved             
            } b;                            // Structure used for bit access 
            uint32_t  reg;                  // Type used for register access 
        } DQS_T_DQ_OFFSET_reg_t;

        /* [reset state = 0x04010040] [offset = 0x120, 0x1C4] */
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    WR_DATA_SLAVE_RATIO_CS0     :10;    // bit: 0..9    (W) Ratio value for write data slave DLL for CS0.
                                                                //                  This is the fraction of a clock cycle represented by the shift to be applied to
                                                                //                  the write DQ muxes in units of 256ths. In other words, the full-cycle tap
                                                                //                  value from the master DLL will be scaled by this number over 256 to get the
                                                                //                  delay value for the slave delay line.
                                                                //                  [values 0-40h]
                uint32_t                                :22;    // bit: 10..31  (R) Reserved             
            } b;                                                // Structure used for bit access 
            uint32_t  reg;                                      // Type used for register access 
        } WDS_RATIO_reg_t;

        /* [reset state = 0x0] [offset = 0x134, 0x1D8]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    RANK0_DELAY    :1;      // bit: 0       (W) Delay Selection
                                                    //                  [0x0 = Each Rank uses its own delay. (Recommended). This is applicable only in case of DDR3;
                                                    //                   0x1 = Rank 0 delays are used for all ranks. This must be set to 1 for DDR2 and mDDR.]

                uint32_t                    :31;    // bit: 1..31   (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DELAY_SEL_reg_t;

        /* [reset state = 0x4] [offset = 0x138, 0x1DC]*/
        typedef union 
        {                                 /* 
                                           */
            struct 
            {                                         
                uint32_t    DLL_LOCK_DIFF   :4;     // bit: 0..3  (W) The max number of delay line taps variation allowed while maintaining the master DLL lock.This is
                                                    //               calculated as total jitter/ delay line tap size, where total jitter is half of (incoming clock jitter (pp) +
                                                    //               delay line jitter (pp)).
                                                    //               [values 0-4h]
                uint32_t                    :28;    // bit: 4..31 (R)  Reserved             
            } b;                                    // Structure used for bit access 
            uint32_t  reg;                          // Type used for register access 
        } DLL_LOCK_DIFF_reg_t; 

    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_EMIF4D_Type Registers **********************************************************************/ 
    
    /*******************************************************************************************************************************************************************************/      

        /* (offset = 0x0) [reset = 0x40443403] */
        typedef union 
        {
                                                  /* EMIF_MOD_ID_REV
                                                   */
            struct 
            {                                      
                uint32_t    MINOR_REV    : 6;      // bits 0..5   (R) Minor Revision
                uint32_t                 : 2;      // bits 6..7   (R) Reserved 
                uint32_t    MAJOR_REV    : 3;      // bits 8..10  (R) Major Revision
                uint32_t    RTL_VERSION  : 5;      // bits 11..15 (R) RTL Version
                uint32_t    MODULE_ID    :12;      // bits 16..27 (R) EMIF module ID
                uint32_t                 : 2;      // bits 28..29 (R) Reserved
                uint32_t    SCHEME       : 2;      // bits 30..31 (R) Scheme indicator [0x1 = old scheme; 0x2 = current scheme]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } EMIF_MOD_ID_REV_reg_t;
        
        /* (offset = 0x4) [reset = 0x40000000] */
        typedef union 
        {
                                                      /* STATUS
                                                       */
            struct 
            {                                      
                uint32_t                    : 2;      // bits 0..1   (R) Reserved
                uint32_t    PHY_DLL_READY   : 1;      // bit  2      (R) DDR PHY Ready [0x0 = ready; 0x1 = not ready]
                uint32_t                    :26;      // bits 3..28  (R) Reserved
                uint32_t    FAST_INIT       : 1;      // bit  29     (R) Fast Init enabled [0x0 = disabled; 0x1 = enabled]
                uint32_t    DUAL_CLK_MODE   : 1;      // bit  30     (R) Dual Clock mode [0x0 = synchronous; 0x1 = asynchronous]
                uint32_t    BE              : 1;      // bit  31     (R) Big Endian mode [0x0 = little endian; 0x1 = big endian]
            } b;                                      // bit access
            uint32_t reg;                             // raw register
        } STATUS_reg_t;
        
        /* (offset = 0x8) [reset = 0x4104BAB2] */
        typedef union 
        {
                                                  /* SDRAM_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    PAGESIZE        : 3;      // bits 0..2   (RW) Page Size [see e_PAGESIZE]
                uint32_t    EBANK           : 1;      // bit  3      (RW) External chip select [0x0 = CS0 only; 0x1 = CS0 and CS1]
                uint32_t    IBANK           : 3;      // bits 4..6   (RW) Internal Bank setup [see e_IBANK]
                uint32_t    ROWSIZE         : 3;      // bits 7..9   (RW) Row Size [see e_ROWSIZE]
                uint32_t    CL              : 4;      // bits 10..13 (RW) CAS Latency [see e_CL]
                uint32_t    NARROW_MODE     : 2;      // bits 14..15 (RW) Data bus width [0x0 = 32-bit; 0x1 = 16-bit]
                uint32_t    CWL             : 2;      // bits 16..17 (RW) DDR3 CAS Write latency [see e_CWL]
                uint32_t    SDRAM_DRIVE     : 2;      // bits 18..19 (RW) Drive strength [see e_SDRAM_DRIVE]
                uint32_t    DDR_DISABLE_DLL : 1;      // bit  20     (RW) Disable DLL select [0x0 = enabled; 0x1 = disabled]
                uint32_t    DYN_ODT         : 2;      // bits 21..22 (RW) DDR3 Dynamic ODT [see e_DYN_ODT]
                uint32_t    DDR2_DDQS       : 1;      // bit  23     (RW) DDR2 diff DQS enable [0x0 = single ended; 0x1 = differential]
                uint32_t    DDR_TERM        : 3;      // bits 24..26 (RW) Termination resistor [see e_DDR_TERM]
                uint32_t    IBANK_POS       : 2;      // bits 27..28 (RW) Internal bank position [see e_IBANK_POS]
                uint32_t    SDRAM_TYPE      : 3;      // bits 29..31 (RW) SDRAM Type selection [see e_SDRAM_TYPE]
            } b;                                      // bit access
            uint32_t reg;                             // raw register
        } SDRAM_CONFIG_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PAGESIZE : uint32_t 
        {
            PAGE_256_WORDS  = 0x0,  // 8 column bits
            PAGE_512_WORDS  = 0x1,  // 9 column bits
            PAGE_1024_WORDS = 0x2,  // 10 column bits
            PAGE_2048_WORDS = 0x3   // 11 column bits
        };
        
        enum e_IBANK : uint32_t 
        {
            BANK_1 = 0x0,       // one bank
            BANK_2 = 0x1,       // two bank
            BANK_4 = 0x2,       // four banks
            BANK_8 = 0x3        // eight banks
        };
        
        enum e_ROWSIZE : uint32_t 
        {
            // This field is only used when reg_ibank_pos field in SDRAM Config
            // register is set to 1, 2, or 3, or reg_ebank_pos field in SDRAM
            // Config_2 register is set to 1.
            ROW_9_BITS  = 0x0,
            ROW_10_BITS = 0x1,
            ROW_11_BITS = 0x2,
            ROW_12_BITS = 0x3,
            ROW_13_BITS = 0x4,
            ROW_14_BITS = 0x5,
            ROW_15_BITS = 0x6,
            ROW_16_BITS = 0x7
        };
        
        enum e_CL : uint32_t 
        {
            /*  The value of this field defines the CAS latency to be used when
             *  accessing connected SDRAM devices.
             *  Value of 2, 3, 5, and 6 (CAS latency of 2, 3, 1.5, and 2.5) are supported for DDR1.
             *  Value of 2, 3, 4, and 5 (CAS latency of 2, 3, 4, and 5) are supported for DDR2.
             *  Value of 2, 4, 6, 8, 10, 12, and 14 (CAS latency of 5, 6, 7, 8, 9, 10, and 11) are supported for DDR3.
             *  Value of 2 and 3 (CAS latency of 2 and 3) are supported for LPDDR1.
             *  All other values are reserved.
             */
            CL_2 = 0x2,
            CL_3 = 0x3,
            CL_4 = 0x4,
            CL_5 = 0x5,
            CL_6 = 0x6,
            CL_8 = 0x8,
            CL_10 = 0xA,
            CL_12 = 0xC,
            CL_14 = 0xE
        };
        
        enum e_CWL : uint32_t 
        {
            /* 
             * Value of 0, 1, 2, and 3 (CAS write latency of 5, 6, 7, and 8) are supported.
             * Use the lowest value supported for best performance.
             * All other values are reserved.
             */
            CWL_5 = 0x0,
            CWL_6 = 0x1,
            CWL_7 = 0x2,
            CWL_8 = 0x3
        };
        
        enum e_SDRAM_DRIVE : uint32_t 
        {
            DRIVE_NORMAL  = 0x0,    // DDR1/DDR2
            DRIVE_WEAK    = 0x1,    // DDR1/DDR2
            DRIVE_RZQ6    = 0x0,    // DDR3
            DRIVE_RZQ7    = 0x1,    // DDR3
            DRIVE_FULL    = 0x0,    // LPDDR1
            DRIVE_HALF    = 0x1,    // LPDDR1
            DRIVE_QUARTER = 0x2,    // LPDDR1
            DRIVE_EIGHTH  = 0x3     // LPDDR1
        };
        
        enum e_DYN_ODT : uint32_t 
        {
            DYN_ODT_OFF  = 0x0,
            DYN_ODT_RZQ4 = 0x1,
            DYN_ODT_RZQ2 = 0x2
        };
        
        enum e_DDR_TERM : uint32_t 
        {
            TERM_DISABLED = 0x0,    // DDR2
            TERM_75_OHM   = 0x1,    // DDR2
            TERM_150_OHM  = 0x2,    // DDR2
            TERM_50_OHM   = 0x3,    // DDR2
            TERM_RZQ4     = 0x1,    // DDR3
            TERM_RZQ2     = 0x2,    // DDR3
            TERM_RZQ6     = 0x3,    // DDR3
            TERM_RZQ12    = 0x4,    // DDR3
            TERM_RZQ8     = 0x5     // DDR3
        };
        
        enum e_IBANK_POS : uint32_t 
        {

            /*
             * Set to 0 to assign internal bank address bits from lower OCP
             * address bits, as shown in the tables for OCP Address to
             * DDR2/3/mDDR Address Mapping.
             * Set to 1, 2, or 3 to assign internal bank address bits from higher
             * OCP address, as shown in the tables for OCP Address to
             * DDR2/3/mDDR Address Mapping.
             */
            IBANK_LOWER   = 0x0,
            IBANK_HIGHER1 = 0x1,
            IBANK_HIGHER2 = 0x2,
            IBANK_HIGHER3 = 0x3
        };
        
        enum e_SDRAM_TYPE : uint32_t 
        {
            DDR1   = 0x0,
            LPDDR1 = 0x1,
            DDR2   = 0x2,
            DDR3   = 0x3
        };
        
        /* (offset = 0xC) [reset = 0x0] */
        typedef union 
        {
                                                  /* SDRAM_CONFIG_2
                                                   */
            struct 
            {
                uint32_t                 :27;      // bits 0..26  (R)  Reserved
                uint32_t    EBANK_POS    : 1;      // bit  27     (RW) External bank position [0x0 = lower OCP address; 0x1 = higher OCP address]
                uint32_t                 : 4;      // bits 28..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_CONFIG_2_reg_t;
        
        /* (offset = 0x10) [reset = 0x80001388] */ 
        typedef union 
        { 
                                                  /* SDRAM_REF_CTRL
                                                   */
            struct 
            {                                      
                uint32_t    REFRESH_RATE :16;      // bits 0..15  (RW) Refresh Rate
                                                   //                  Value defines rate at which connected SDRAM devices will be refreshed
                                                   //                  SDRAM refresh rate = EMIF rate / reg_refresh_rate where EMIF rate
                                                   //                  is equal to DDR clock rate
                                                   //                  If reg_refresh_rate < (8*reg_t_rfc)+reg_t_rp+reg_t_rcd+20 then it will
                                                   //                  be loaded with (8*reg_t_rfc)+reg_t_rp+reg_t_rcd+20.
                                                   //                  This is done to avoid lock-up situations when illegal values are
                                                   //                  programmed.
                uint32_t                 : 8;      // bits 16..23 (R)  Reserved
                uint32_t    PASR         : 3;      // bits 24..26 (RW) Partial Array Self Refresh [see e_PASR]
                uint32_t                 : 1;      // bit  27     (R)  Reserved
                uint32_t    ASR          : 1;      // bit  28     (RW) Auto Self Refresh enable
                                                   //                  A write to this field will cause the EMIF to start the SDRAM
                                                   //                  initialization sequence.
                                                   //                  [ 0x0 = manual Self Refresh;
                                                   //                    0x1 = auto Self Refresh ]
                uint32_t    SRT          : 1;      // bit  29     (RW) Self-refresh temperature range
                                                   //                  For DDR3, this bit must be set to 0 if the ASR field is set to 1.
                                                   //                  A write to this field will cause the EMIF to start the SDRAM
                                                   //                  initialization sequence.
                                                   //                  [ 0x0 = normal operating temperature range;
                                                   //                    0x1 = extended operating temperature range ]
                uint32_t                 : 1;      // bit  30     (R)  Reserved
                uint32_t    INITREF_DIS  : 1;      // bit  31     (RW) Initialization and Refresh disable
                                                   //                  [ 0x0 = enabled;
                                                   //                    0x1 = disabled ]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_REF_CTRL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PASR : uint32_t 
        {
            /* Partial Array Self Refresh configuration for LPDDR1/DDR3
             * For LPDDR1: 0 = full array, 1 = 1/2 array, 2 = 1/4 array, 5 = 1/8 array, 6 = 1/16 array
             * For DDR3: 0 = full array, 1 or 5 = 1/2 array, 2 or 6 = 1/4 array, 3 or 7 = 1/8 array, 4 = 3/4 array
             */
            PASR_FULL       = 0x0,
            PASR_HALF       = 0x1,
            PASR_QUARTER    = 0x2,
            PASR_EIGHTH     = 0x5,
            PASR_SIXTEENTH  = 0x6,
            PASR_3QUARTERS  = 0x4
        };
        
        /* (offset = 0x14) [reset = 0x00001388] */ 
        typedef union 
        { 
                                                  /* SDRAM_REF_CTRL_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    REFRESH_RATE_SHADOW :16;    // bits 0..15  (RW) Shadow field for reg_refresh_rate
                                                        //              Loaded into reg_refresh_rate when SlideAck is asserted
                                                        //              This register is not auto corrected when the value is invalid.
                uint32_t                        :16;    // bits 16..31 (R) Reserved
            } b;                                        // bit access
            uint32_t reg;                               // raw register
        } SDRAM_REF_CTRL_SHDW_reg_t;
        
        /* (offset = 0x18) [reset = 0x08891599] */ 
        typedef union 
        { 
                                                  /* SDRAM_TIM_1
                                                   */
            struct 
            {                                      
                uint32_t    WTR          : 3;      // bits 0..2   (RW) Write to Read delay
                                                   //                  Minimum DDR clock cycles from last Write to Read, minus one
                uint32_t    RRD          : 3;      // bits 3..5   (RW) Activate to Activate delay for different bank
                                                   //                  Minimum DDR clock cycles between activates to different banks, minus one
                                                   //                  For an 8-bank DDR2 or DDR3, this field must be equal to
                                                   //                  ((tFAW/(4*tCK))-1). For 4-bank DDR2 or LPDDR1, the field must be
                                                   //                  equal to (tRRD/tCK)-1. 
                uint32_t    RC           : 6;      // bits 6..11  (RW) Activate to Activate
                                                   //                  Minimum DDR clock cycles between activate commands, minus one
                uint32_t    RAS          : 5;      // bits 12..16 (RW) Activate to Pre-charge
                                                   //                  Minimum DDR clock cycles from Activate to Pre-charge, minus one
                                                   //                  reg_t_ras >= reg_t_rcd.
                uint32_t    WR           : 4;      // bits 17..20 (RW) Write to Pre-charge
                                                   //                  Minimum DDR clock cycles from last Write to Pre-charge, minus one
                                                   //                  The SDRAM initialization sequence will be started when the value of
                                                   //                  this field is changed from the previous value and the EMIF is in
                                                   //                  DDR2 mode.
                uint32_t    RCD          : 4;      // bits 21..24 (RW) Activate to Read/Write
                                                   //                  Minimum DDR clock cycles from Activate to Read/Write, minus one
                uint32_t    RP           : 4;      // bits 25..28 (RW) Precharge to Activate
                                                   //                  Minimum DDR clock cycles from Precharge to Activate, minus one
                uint32_t                 : 3;      // bits 29..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_1_reg_t;
        
        /* (offset = 0x1C) [reset = 0x08891599] */ 
        typedef union 
        { 
                                                  /* SDRAM_TIM_1_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    WTR_SHADOW   : 3;      // bits 0..2   (RW) Shadow field for WTR
                                                   //                  Loaded into WTR SDRAM_TIM_1_reg_t when SlideAck is asserted
                uint32_t    RRD_SHADOW   : 3;      // bits 3..5   (RW) Shadow field for RRD
                                                   //                  Loaded into RRD SDRAM_TIM_1_reg_t when SlideAck is asserted
                uint32_t    RC_SHADOW    : 6;      // bits 6..11  (RW) Shadow field for RC
                                                   //                  Loaded into RC SDRAM_TIM_1_reg_t when SlideAck is asserted
                uint32_t    RAS_SHADOW   : 5;      // bits 12..16 (RW) Shadow field for RAS
                                                   //                  Loaded into RAS SDRAM_TIM_1_reg_t when SlideAck is asserted
                uint32_t    WR_SHADOW    : 4;      // bits 17..20 (RW) Shadow field for WR
                                                   //                  Loaded into WR SDRAM_TIM_1_reg_t when SlideAck is asserted
                                                   //                  initialization sequence will be started when the value of this field is
                                                   //                  changed from the previous value and the EMIF is in DDR2 mode.
                uint32_t    RCD_SHADOW   : 4;      // bits 21..24 (RW) Shadow field for RCD
                                                   //                  Loaded into RCD SDRAM_TIM_1_reg_t when SlideAck is asserted
                uint32_t    RP_SHADOW    : 4;      // bits 25..28 (RW) Shadow field for RP
                                                   //                  Loaded into RP SDRAM_TIM_1_reg_ts when SlideAck is asserted
                uint32_t                 : 3;      // bits 29..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_1_SHDW_reg_t;
        
        /* (offset = 0x20) [reset = 0x148B31CA] */ 
        typedef union 
        { 
                                                  /* SDRAM_TIM_2
                                                   */
            struct 
            {                                      
                uint32_t    CKE          : 3;      // bits 0..2   (RW) CKE changes delay
                                                   //                  Minimum DDR clock cycles between pad_cke_o changes, minus one
                uint32_t    RTP          : 3;      // bits 3..5   (RW) Read to Precharge
                                                   //                  Minimum DDR clock cycles from last Read to Precharge for DDR2 and DDR3, minus one
                uint32_t    XSRD         :10;      // bits 6..15  (RW) Self-Refresh exit to Read
                                                   //                  Minimum DDR clock cycles from Self-Refresh exit to Read, minus one
                uint32_t    XSNR         : 9;      // bits 16..24 (RW) Self-Refresh exit delay
                                                   //                  Minimum DDR clock cycles from Self-Refresh exit to any command, minus one
                uint32_t                 : 3;      // bits 25..27 (RW) Reserved
                uint32_t    XP           : 3;      // bits 28..30 (RW) Powerdown exit delay
                                                   //                  Minimum DDR clock cycles from Powerdown exit to any command, minus one
                                                   //                  For DDR2 and LPDDR1, this field must satisfy greater of tXP or tCKE.
                uint32_t                 : 1;      // bit  31     (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_2_reg_t;
        
        /* (offset = 0x24) [reset = 0x148B31CA] */ 
        typedef union 
        { 
                                                  /* SDRAM_TIM_2_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    CKE_SHADOW   : 3;      // bits 0..2   (RW) Shadow field for CKE
                                                   //                  Loaded into CKE for SDRAM_TIM_2_reg_t when SlideAck is asserted
                uint32_t    RTP_SHADOW   : 3;      // bits 3..5   (RW) Shadow field for RTP
                                                   //                  Loaded into RTP for SDRAM_TIM_2_reg_t when SlideAck is asserted
                uint32_t    XSRD_SHADOW  :10;      // bits 6..15  (RW) Shadow field for XSRD
                                                   //                  Loaded into XSRD for SDRAM_TIM_2_reg_t when SlideAck is asserted
                uint32_t    XSNR_SHADOW  : 9;      // bits 16..24 (RW) Shadow field for XSNR
                                                   //                  Loaded into XSNR for SDRAM_TIM_2_reg_t when SlideAck is asserted
                uint32_t                 : 3;      // bits 25..27 (RW) Reserved
                uint32_t    XP_SHADOW    : 3;      // bits 28..30 (RW) Shadow field for XP
                                                   //                  Loaded into XP for SDRAM_TIM_2_reg_t when SlideAck is asserted
                uint32_t                 : 1;      // bit  31     (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_2_SHDW_reg_t;
        
        /* (offset = 0x28) [reset = 0x00FFE82F] */ 
        typedef union 
        { 
                                                  /* SDRAM_TIM_3
                                                   */
            struct 
            {                                      
                uint32_t    RAS_MAX      : 4;      // bits 0..3   (RW) Max Activate to Precharge
                                                   //                  Maximum number of refresh_rate intervals from Activate to Precharge
                                                   //                  This field must be equal to ((tRASmax / tREFI)-1) rounded down to
                                                   //                  the next lower integer.
                                                   //                  This field is only applicable for mDDR.
                                                   //                  This field must be programmed to 0xF for other SDRAM types.
                uint32_t    RFC          : 9;      // bits 4..12  (RW) Refresh/Activate delay
                                                   //                  Minimum DDR clock cycles from Refresh/Activate to Refresh/Activate, minus one
                uint32_t                 : 2;      // bits 13..14 (RW) Reserved
                uint32_t    ZQ_ZQCS      : 6;      // bits 15..20 (RW) ZQCS command cycles
                                                   //                  Number of DDR clock cycles for ZQCS command, minus one
                uint32_t                 : 7;      // bits 24..27 (R)  Reserved
                uint32_t    PDLL_UL      : 4;      // bits 28..31 (RW) PHY DLL unlock cycles
                                                   //                  Minimum DDR clock cycles for PHY DLL to unlock 
                                                   //                  A value of N will be equal to N x 128 clocks.
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } SDRAM_TIM_3_reg_t;
        
        /* (offset = 0x2C) [reset = 0x00FFE82F 00000000 00000000] */ 
        typedef union 
        { 
                                                     /* SDRAM_TIM_3_SHDW
                                                      */
            struct 
            {                                      
                uint32_t    RAS_MAX_SHADOW  : 4;     // bits 0..3   (RW) Shadow field for RAS_MAX
                                                     //                  Loaded into RAS_MAX of SDRAM_TIM_3_reg_t when SlideAck is asserted
                uint32_t    RFC_SHADOW      : 9;     // bits 4..12  (RW) Shadow field for RFC
                                                     //                  Loaded into RFC of SDRAM_TIM_3_reg_t when SlideAck is asserted
                uint32_t                    : 2;     // bits 13..14 (RW) Reserved
                uint32_t    ZQ_ZQCS_SHADOW  : 6;     // bits 15..20 (RW) Shadow field for ZQ_ZQCS
                                                     //                  Loaded into ZQ_ZQCS of SDRAM_TIM_3_reg_t when SlideAck is asserted
                uint32_t                    : 7;     // bits 24..27 (R)  Reserved
                uint32_t    PDLL_UL_SHADOW  : 4;     // bits 28..31 (RW) Shadow field for PDLL_UL
                                                     //                  Loaded into PDLL_UL of SDRAM_TIM_3_reg_t when SlideAck is asserted
            } b;                                     // bit access
            uint32_t reg;                            // raw register
        } SDRAM_TIM_3_SHDW_reg_t;
        
        /* (offset = 0x38) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* PWR_MGMT_CTRL
                                                   */
            struct 
            {                                      
                uint32_t    CS_TIM       : 4;      // bits 0..3   (RW) Clock Stop timer [see e_PWR_TIMER]
                uint32_t    SR_TIM       : 4;      // bits 4..7   (RW) Self Refresh timer [see e_PWR_TIMER]
                uint32_t    LP_MODE      : 3;      // bits 8..10  (RW) Power Management mode [see e_LP_MODE]
                uint32_t    DPD_EN       : 1;      // bit  11     (RW) Deep Power Down enable
                                                   //                  This mode will override the reg_lp_mode field setting.
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t    PD_TIM       : 4;      // bits 12..15 (RW) Power-Down timer [see e_PWR_TIMER]
                uint32_t                 :16;      // bits 16..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PWR_MGMT_CTRL_reg_t;
        
        /* Enums for multi-value fields */
        enum e_PWR_TIMER : uint32_t 
        {
            /* Power management timer values in DDR clock cycles
             *
             * The EMIF will put the external SDRAM in Clock Stop mode after the
             * EMIF is idle for these number of DDR clock cycles and if
             * reg_lp_mode field is set to 1.
             * Set to 0 to immediately enter Clock Stop mode.
             *
             * The EMIF will put the external SDRAM in Self Refresh mode after
             * the EMIF is idle for these number of DDR clock cycles and if
             * reg_lp_mode field is set to 2.
             * Set to 0 to immediately enter Self
             *
             * The EMIF will put the external SDRAM in Power-Down mode after
             * the EMIF is idle for these number of DDR clock cycles and if
             * reg_lp_mode field is set to 4.
             * Set to 0 to immediately enter Power-Down mode.
             *
             * Note: After updating this field, at least one dummy read access to
             * SDRAM is required for the new value to take affect.
             */
            PWR_TIMER_IMMEDIATE = 0x0,
            PWR_TIMER_16 = 0x1,
            PWR_TIMER_32 = 0x2,
            PWR_TIMER_64 = 0x3,
            PWR_TIMER_128 = 0x4,
            PWR_TIMER_256 = 0x5,
            PWR_TIMER_512 = 0x6,
            PWR_TIMER_1024 = 0x7,
            PWR_TIMER_2048 = 0x8,
            PWR_TIMER_4096 = 0x9,
            PWR_TIMER_8192 = 0xA,
            PWR_TIMER_16384 = 0xB,
            PWR_TIMER_32768 = 0xC,
            PWR_TIMER_65536 = 0xD,
            PWR_TIMER_131072 = 0xE,
            PWR_TIMER_262144 = 0xF
        };
        
        enum e_LP_MODE : uint32_t 
        {
            /* Automatic Power Management enable.
             * Set to 1 for Clock Stop, set to 2 for Self Refresh, and set to 4 for Power-Down.
             * All other values will disable automatic power management
             */
            LP_DISABLED     = 0x0,
            LP_CLOCK_STOP   = 0x1,
            LP_SELF_REFRESH = 0x2,
            LP_POWER_DOWN   = 0x4
        };
        
        /* (offset = 0x3C) [reset = 0x0] */ 
        typedef union 
        { 
                                                      /* PWR_MGMT_CTRL_SHDW
                                                       */
            struct 
            {                                      
                uint32_t    CS_TIM_SHADOW   : 4;       // bits 0..3   (RW) Shadow field for CS_TIM
                                                       //                  Loaded into CS_TIM in PWR_MGMT_CTRL_reg_t when SlideAck is asserted
                uint32_t    SR_TIM_SHADOW   : 4;       // bits 4..7   (RW) Shadow field for SR_TIM
                                                       //                  Loaded into SR_TIM in PWR_MGMT_CTRL_reg_t when SlideAck is asserted
                uint32_t    PD_TIM_SHADOW   : 4;       // bits 8..11  (RW) Shadow field for PD_TIM
                                                       //                  Loaded into PD_TIM in PWR_MGMT_CTRL_reg_t when SlideAck is asserted
                uint32_t                    :20;       // bits 12..31 (R)  Reserved
            } b;                                       // bit access
            uint32_t reg;                              // raw register
        } PWR_MGMT_CTRL_SHDW_reg_t;
        
        /* (offset = 0x54) [reset = 0x00FFFFFF] */ 
        typedef union 
        { 
                                                  /* OCP_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    PR_OLD_COUNT : 8;      // bits 0..7   (RW) Priority Raise Old Counter
                                                   //                  Number of m_clk cycles after which EMIF raises priority of oldest command in the OCP Command FIFO.
                                                   //                  A value of N will be equal to N x 16 clocks. 
                uint32_t    COS_COUNT_2  : 8;      // bits 8..15  (RW) Priority Counter COS 2
                                                   //                  Number of m_clk cycles after which EMIF raises priority of COS 2 commands in the OCP Command FIFO.
                                                   //                  A value of N will be equal to N x 16 clocks.
                uint32_t    COS_COUNT_1  : 8;      // bits 16..23 (RW) Priority Counter COS 1
                                                   //                  Number of m_clk cycles after which EMIF raises priority of COS 1 commands in the OCP Command FIFO.
                                                   //                  A value of N will be equal to N x 16 clocks.
                uint32_t                 : 8;      // bits 24..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } OCP_CONFIG_reg_t;
        
        /* (offset = 0x58) [reset = 0x8000140A] */ 
        typedef union 
        { 
                                                    /* OCP_CFG_VAL_1
                                                     */
            struct 
            {                                      
                uint32_t    CMD_FIFO_DEPTH  : 8;      // bits 0..7   (R) Command FIFO depth
                                                      //                 Depth of Command FIFO for this configuration
                uint32_t    WR_FIFO_DEPTH   : 8;      // bits 8..15  (R) Write Data FIFO depth
                                                      //                 Depth of Write Data FIFO for this configuration
                uint32_t                    :14;      // bits 16..29 (R) Reserved
                uint32_t    SYS_BUS_WIDTH   : 2;      // bits 30..31 (R) L3 OCP data bus width [see e_SYS_BUS_WIDTH]
            } b;                                      // bit access
            uint32_t reg;                             // raw register
        } OCP_CFG_VAL_1_reg_t;
        
        /* Enums for multi-value fields */
        enum e_SYS_BUS_WIDTH : uint32_t 
        {
            /* System bus width configuration
             * Determines the width of the L3 OCP data bus
             */
            BUS_WIDTH_32 = 0x0,
            BUS_WIDTH_64 = 0x1,
            BUS_WIDTH_128 = 0x2,
            BUS_WIDTH_256 = 0x3
        };
        
        /* (offset = 0x5C) [reset = 0x00021616 00002011 00000000 00000000 00000000] */ 
        typedef union 
        { 
                                                  /* OCP_CFG_VAL_2
                                                   */
            struct 
            {                                      
                uint32_t    RCMD_FIFO_DEPTH     : 8;    // bits 0..7   (R) Read Command FIFO depth
                                                        //                 Depth of Read Command FIFO for this configuration
                uint32_t    RSD_FIFO_DEPTH      : 8;    // bits 8..15  (R) SDRAM Read Data FIFO depth
                                                        //                 Depth of SDRAM Read Data FIFO for this configuration
                uint32_t    RREG_FIFO_DEPTH     : 8;    // bits 16..23 (R) Register Read FIFO depth
                                                        //                 Depth of Register Read FIFO for this configuration
                uint32_t                        : 8;    // bits 24..31 (R) Reserved
            } b;                                        // bit access
            uint32_t reg;                               // raw register
        } OCP_CFG_VAL_2_reg_t;
        
        /* (offset = 0x80) [reset = 0x00592A49] */ 
        typedef union 
        { 
                                                  /* PERF_CNT_1
                                                   */
            struct 
            {                                      
                uint32_t    COUNTER1     :32;      // bits 0..31  (R) Performance counter 1
                                                   //              32-bit counter configurable via PERF_CNT_CFG register
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_1_reg_t;
        
        /* (offset = 0x84) [reset = 0x1FEB9] */ 
        typedef union 
        { 
                                                  /* PERF_CNT_2
                                                   */
            struct 
            {                                      
                uint32_t    COUNTER2     :32;      // bits 0..31  (R) Performance counter 2
                                                   //              32-bit counter configurable via PERF_CNT_CFG register
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_2_reg_t;
        
        /* (offset = 0x88) [reset = 0x10000] */ 
        typedef union 
        { 
                                                  /* PERF_CNT_CFG
                                                   */
            struct 
            {                                      
                uint32_t    CNTR1_CFG        : 4;   // bits 0..3   (RW) Counter 1 config
                                                    //                  Filter configuration for Performance Counter 1
                uint32_t                     :10;   // bits 4..13  (R)  Reserved
                uint32_t    CNTR1_REGION_EN  : 1;   // bit  14     (RW) Counter 1 region enable
                                                    //                  [ 0x0 = disabled;
                                                    //                    0x1 = enabled ]
                uint32_t    CNTR1_MCONNID_EN : 1;   // bit  15     (RW) Counter 1 MConnID enable
                                                    //                  [ 0x0 = disabled;
                                                    //                    0x1 = enabled ]
                uint32_t    CNTR2_CFG        : 4;   // bits 16..19 (RW) Counter 2 config
                                                    //                  Filter configuration for Performance Counter 2
                uint32_t                     : 10;  // bits 20..29 (R)  Reserved
                uint32_t    CNTR2_REGION_EN  : 1;   // bit  30     (RW) Counter 2 region enable
                                                    //                  [ 0x0 = disabled;
                                                    //                    0x1 = enabled ]
                uint32_t    CNTR2_MCONNID_EN : 1;   // bit  31     (RW) Counter 2 MConnID enable
                                                    //                  [ 0x0 = disabled;
                                                    //                    0x1 = enabled ]
            } b;                                    // bit access
            uint32_t reg;                           // raw register
        } PERF_CNT_CFG_reg_t;
        
        /* (offset = 0x8C) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* PERF_CNT_SEL
                                                   */
            struct 
            {                                      
                uint32_t    REGION_SEL1  : 2;      // bits 0..1   (RW) MMddrSpace for Counter 1
                                                   //                  Memory region selection for Performance Counter 1
                uint32_t                 : 6;      // bits 2..7   (R)  Reserved
                uint32_t    MCONNID1     : 8;      // bits 8..15  (RW) MConnID for Counter 1
                                                   //                  Connection ID filter for Performance Counter 1
                uint32_t    REGION_SEL2  : 2;      // bits 16..17 (RW) MMddrSpace for Counter 2
                                                   //                  Memory region selection for Performance Counter 2
                uint32_t                 : 6;      // bits 18..23 (R)  Reserved
                uint32_t    MCONNID2     : 8;      // bits 24..31 (RW) MConnID for Counter 2
                                                   //                  Connection ID filter for Performance Counter 2
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_SEL_reg_t;
        
        /* (offset = 0x90) [reset = 0xA484D432 00000000] */ 
        typedef union 
        { 
                                                   /* PERF_CNT_TIM
                                                    */
            struct 
            {                                      
                uint32_t    TOTAL_TIME   :32;      // bits 0..31  (R) Total m_clk cycles counter
                                                   //              32-bit counter of m_clk cycles since EMIF reset
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } PERF_CNT_TIM_reg_t;
        
        /* (offset = 0x98) [reset = 0x50000] */ 
        typedef union 
        { 
                                                         /* READ_IDLE_CTRL
                                                          */
            struct 
            {                                      
                uint32_t    READ_IDLE_INTERVAL  :9;      // bits 0..8   (RW) Read idle interval
                                                         //                  Maximum interval between read idle detections ((reg_read_idle_interval-1)*64 clock cycles)
                                                         //                  A value of zero disables the read idle function.
                uint32_t                        :7;      // bits 9..15  (R)  Reserved
                uint32_t    READ_IDLE_LEN       :4;      // bits 16..19 (RW) Read idle length
                                                         //                  Minimum size of read idle window (reg_read_idle_len-1 clock cycles)
                uint32_t                        :12;     // bits 20..31 (R)  Reserved
            } b;                                         // bit access
            uint32_t reg;                                // raw register
        } READ_IDLE_CTRL_reg_t;
        
        /* (offset = 0x9C) [reset = 0x0050000 00000000] */ 
        typedef union 
        { 
                                                                  /* READ_IDLE_CTRL_SHDW
                                                                   */
            struct 
            {                                      
                uint32_t    READ_IDLE_INTERVAL_SHADOW   : 9;        // bits 0..8   (RW) Shadow field for read idle interval
                                                                    //                  Loaded into read idle interval in READ_IDLE_CTRL_reg_t when SlideAck is asserted
                uint32_t                                : 7;        // bits 9..15  (R)  Reserved
                uint32_t    READ_IDLE_LEN_SHADOW        : 4;        // bits 16..19 (RW) Shadow field for read idle length
                                                                    //                  Loaded into read idle length in READ_IDLE_CTRL_reg_t when SlideAck is asserted
                uint32_t                                :12;        // bits 20..31 (R)  Reserved
            } b;                                                    // bit access
            uint32_t reg;                                           // raw register
        } READ_IDLE_CTRL_SHDW_reg_t;
        
        /* (offset = 0xA4) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* IRQSTATUS_RAW_SYS
                                                   */
            struct 
            {                                      
                uint32_t    ERR_SYS      : 1;      // bit  0      (RW) Raw status of system OCP interrupt.
                                                   //                  [ 0x0 = no error;
                                                   //                    0x1 = error ]
                uint32_t    TA_SYS       : 1;      // bit  1      (RW) Raw status of system OCP interrupt.
                                                   //                  [ 0x0 = no error;
                                                   //                    0x1 = error ]
                uint32_t                 :30;      // bits 2..31  (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQSTATUS_RAW_SYS_reg_t;
        
        /* (offset = 0xAC) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* IRQSTATUS_SYS
                                                   */
            struct 
            {                                      
                uint32_t    ERR_SYS      : 1;      // bit  0      (RW) Enabled status of system OCP interrupt.
                                                   //                  Write 1 to clear the status after interrupt has been serviced (raw
                                                   //                  status gets cleared, i.e.
                                                   //                  even if not enabled).
                                                   //                  Writing a 0 has no effect. 
                                                   //                  [ 0x0 = no error;
                                                   //                    0x1 = error ]
                uint32_t    TA_SYS       : 1;      // bit  1      (RW) Enabled status of system OCP interrupt.
                                                   //                  Write 1 to clear the status after interrupt has been serviced (raw
                                                   //                  status gets cleared, i.e.
                                                   //                  even if not enabled).
                                                   //                  Writing a 0 has no effect.
                                                   //                  [ 0x0 = no error;
                                                   //                    0x1 = error ]
                uint32_t                 :30;      // bits 2..31  (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQSTATUS_SYS_reg_t;
        
        /* (offset = 0xB4) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* IRQENABLE_SET_SYS
                                                   */
            struct 
            {                                      
                uint32_t    EN_ERR_SYS   : 1;      // bit  0      (RW) Enable set for system OCP interrupt.
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t    EN_TA_SYS    : 1;      // bit  1      (RW) Enable set for system OCP interrupt.
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t                 :30;      // bits 2..31  (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQENABLE_SET_SYS_reg_t;
        
        /* (offset = 0xBC) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* IRQENABLE_CLR_SYS
                                                   */
            struct 
            {                                      
                uint32_t    EN_ERR_SYS   : 1;      // bit  0      (RW) Enable clear for system OCP interrupt.r
                                                   //                  [ 0x0 = no effect;
                                                   //                    0x1 = disable ]
                uint32_t    EN_TA_SYS    : 1;      // bit  1      (RW) Enable clear for system OCP interrupt.
                                                   //                  [ 0x0 = no effect;
                                                   //                    0x1 = disable ]
                uint32_t                 :30;      // bits 2..31  (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } IRQENABLE_CLR_SYS_reg_t;
        
        /* (offset = 0xC8) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* ZQ_CONFIG
                                                   */
            struct 
            {                                      
                uint32_t    REFINTERVAL  :16;      // bits 0..15  (RW) Refresh periods between ZQCS
                                                   //                  This field supports between one refresh period to 256 ms between
                                                   //                  ZQCS calibration commands.
                                                   //                  Refresh period is defined by reg_refresh_rate in SDRAM Refresh
                                                   //                  Control register
                uint32_t    ZQCL_MULT    : 2;      // bits 16..17 (RW) Determines number of ZQCS intervals that make up ZQCL/ZQINIT intervals
                                                   //                  interval, minus one.
                                                   //                  ZQCS interval is defined by reg_zq_zqcs in SDRAM_TIM_3_reg_t.
                uint32_t    ZQINIT_MULT  : 2;      // bits 18..19 (RW) Indicates the number of ZQCL intervals that make up a ZQINIT
                                                   //                  interval, minus one.
                uint32_t                 : 8;      // bits 20..27 (R)  Reserved
                uint32_t    SFEXITEN     : 1;      // bit  28     (RW) ZQCL on power-down exit
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t    DUALCALEN    : 1;      // bit  29     (RW) Dual Calibration enable
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t    CS0EN        : 1;      // bit  30     (RW) ZQ cal for CS0 enable
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
                uint32_t    CS1EN        : 1;      // bit  31     (RW) ZQ cal for CS1 enable
                                                   //                  [ 0x0 = disabled;
                                                   //                    0x1 = enabled ]
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } ZQ_CONFIG_reg_t;        


        /* (offset = 0xD4) [reset = 0x0] */ 
        typedef union 
        {                                             /* ReadWriteLevelingRampWindow
                                                       */
            struct 
            {                                      
                uint32_t RDWRLVLINC_RMP_WIN :13;    // bits 0..12  (R)  Incremental leveling ramp window
                                                    //                  Number of refresh periods for ramp window (value = programmed -1)
                                                    //                  Refresh period is defined by reg_refresh_rate in SDRAM_REF_CTRL_reg_t
                uint32_t                    :19;    // bits 13..31 (R)  Reserved 
            } b;                                    // bit access
            uint32_t reg;                           // raw register
        } RDWRLVL_RAMP_WIN_reg_t;
        
        /*  (offset = 0xD8) [reset = 0x0] */ 
        typedef union 
        {                                             /* ReadWriteLevelingRampControl
                                                       */
            struct 
            {                                      
                uint32_t WRLVLINC_RMP_INT       : 8;     // bits 0..7   (RW) Incremental write leveling interval
                                                         //                  Number of pre-scalar intervals between write leveling
                                                         //                  A value of 0 will disable incremental write leveling during ramp window.
                uint32_t RDLVLGATEINC_RMP_INT   : 8;     // bits 8..15  (RW) Incremental read DQS gate training interval
                                                         //                  Number of pre-scalar intervals between DQS gate training
                                                         //                  A value of 0 will disable incremental read DQS gate training during ramp window.
                uint32_t RDLVLINC_RMP_INT       : 8;     // bits 16..23 (RW) Incremental read data eye training interval
                                                         //                  Number of pre-scalar intervals between data eye training
                                                         //                  A value of 0 will disable incremental read data eye training during ramp window
                uint32_t RDWRLVLINC_RMP_PRE     : 7;     // bits 24..30 (RW) Incremental leveling pre-scalar
                                                         //                  Number of refresh periods per interval (value = programmed -1)
                                                         //                  Refresh period is defined by reg_refresh_rate in SDRAM_REF_CTRL_reg_t
                uint32_t RDWRLVL_EN             : 1;     // bit  31     (RW) Read-Write Leveling enable
                                                         //                  [ 0x0 = disabled;
                                                         //                    0x1 = enabled ]
            } b;                                         // bit access
            uint32_t reg;                                // raw register
        } RDWRLVL_RAMP_CTRL_reg_t;

        /* (offset = 0xDC) [reset = 0x0] */ 
        typedef union 
        {                                             /* ReadWriteLevelingControl
                                                       */
            struct 
            {                                      
                uint32_t WRLVLINC_INT      : 8;        // bits 0..7   (RW) Incremental write leveling interval
                                                       //                  Number of pre-scalar intervals between write leveling
                                                       //                  A value of 0 will disable incremental write leveling.
                uint32_t RDLVLGATEINC_INT  : 8;        // bits 8..15  (RW) Incremental read DQS gate training interval
                                                       //                  Number of pre-scalar intervals between DQS gate training
                                                       //                  A value of 0 will disable incremental read DQS gate training.
                uint32_t RDLVLINC_INT      : 8;        // bits 16..23 (RW) Incremental read data eye training interval
                                                       //                  Number of pre-scalar intervals between data eye training
                                                       //                  A value of 0 will disable incremental read data eye training.
                uint32_t RDWRLVLINC_PRE    : 7;        // bits 24..30 (RW) Incremental leveling pre-scalar
                                                       //                  Number of refresh periods per interval (value = programmed -1)
                                                       //                  Refresh period is defined by reg_refresh_rate in SDRAM_REF_CTRL_reg_t 
                uint32_t RDWRLVLFULL_START : 1;        // bit  31     (RW) Full leveling trigger
                                                       //                  [ 0x1 = trigger (self-clearing to 0) ]
            } b;                                       // bit access
            uint32_t reg;                              // raw register
        } RDWRLVL_CTRL_reg_t;
        
        /* (offset = 0xE4) [reset = 0x0] */ 
        typedef union 
        { 
                                                             /* DDR_PHY_CTRL_1
                                                              */
            struct 
            {                                      
                uint32_t    READ_LATENCY            : 5;      // bits 0..4   (RW) This field defines the latency for read data from DDR SDRAM in
                                                              //                  number of DDR clock cycles.
                                                              //                  The value applied should be equal to the required value minus one.
                                                              //                  The maximum read latency supported by the DDR PHY is equal to
                                                              //                  CAS latency plus 7 clock cycles.
                                                              //                  The minimum read latency must be equal to CAS latency plus 2
                                                              //                  clock cycle.
                uint32_t                            : 3;      // bits 5..7   (R)  Reserved
                uint32_t    RD_LOCAL_ODT            : 2;      // bits 8..9   (RW) Read local ODT value [see e_LOCAL_ODT]
                uint32_t    WR_LOCAL_ODT            : 2;      // bits 10..11 (RW) This bit controls the value assigned to the reg_phy_wr_local_odt
                                                              //                  input on the data macros.
                                                              //                  Always set to 00.
                uint32_t    IDLE_LOCAL_ODT          : 2;      // bits 12..13 (RW) Value to drive on the
                                                              //                  2-bit local_odt (On-Die Termination) PHY outputs when
                                                              //                  reg_phy_dynamic_pwrdn_enable is asserted and a read is not in
                                                              //                  progress and reg_phy_dynamic_pwrdn_enable.
                                                              //                  Typically this is the value required to disable termination (00) to save
                                                              //                  power when idle.
                uint32_t                            : 1;      // bit  14     (R)  Reserved
                uint32_t    PHY_RST_N               : 1;      // bit  15     (RW) PHY reset control
                                                              //                  [ 0x0 = reset;
                                                              //                    0x1 = normal ]
                uint32_t                            : 4;      // bits 16..19 (R)  Reserved
                uint32_t    ENABLE_DYNAMIC_PWRDN    : 1;      // bit  20     (RW) Dynamic IO power down
                                                              //                  [ 0x0 = always on;
                                                              //                    0x1 = dynamic ]
                uint32_t                            :11;      // bits 21..31 (R)  Reserved
            } b;                                              // bit access
            uint32_t reg;                                     // raw register
        } DDR_PHY_CTRL_1_reg_t;
        
        /* Enums for multi-value fields */
        enum e_LOCAL_ODT : uint32_t 
        {
            /* Value to drive on the
             * 2-bit local_odt (On-Die Termination) PHY outputs when output
             * enable is not asserted and a read is in progress (where in progress
             * is defined as after a read command is issued and until all read data
             * has been returned all the way to the controller.) Typically this is set
             * to the value required to enable termination at the desired strength for
             * read usage.
             */
            LOCAL_ODT_OFF  = 0x0,
            LOCAL_ODT_FULL = 0x2,
            LOCAL_ODT_HALF = 0x3
        };
        
        /* (offset = 0xE8) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* DDR_PHY_CTRL_1_SHDW
                                                   */
            struct 
            {                                      
                uint32_t    READ_LATENCY_SHADOW         : 5;    // bits 0..4   (RW) This field defines the latency for read data from DDR SDRAM in
                                                                //                  number of DDR clock cycles.
                                                                //                  The value applied should be equal to the required value minus one.
                                                                //                  The maximum read latency supported by the DDR PHY is equal to
                                                                //                  CAS latency plus 7 clock cycles.
                                                                //                  The minimum read latency must be equal to CAS latency plus 2
                                                                //                  clock cycle.
                uint32_t                                : 3;    // bits 5..7   (R)  Reserved
                uint32_t    RD_LOCAL_ODT_SHADOW         : 2;    // bits 8..9   (RW) Value to drive on the
                                                                //                  2-bit local_odt PHY outputs when output enable is not asserted and
                                                                //                  a read is in progress (where in progress is defined as after a read
                                                                //                  command is issued and until all read data has been returned all the
                                                                //                  way to the controller.) Typically this is set to the value required to
                                                                //                  enable termination at the desired strength for read usage. [see e_LOCAL_ODT]
                                                                //                  
                uint32_t    WR_LOCAL_ODT_SHADOW         : 2;    // bits 10..11 (RW) This bit controls the value assigned to the reg_phy_wr_local_odt
                                                                //                  input on the data macros.Always set to 00.
                uint32_t    IDLE_LOCAL_ODT_SHADOW       : 2;    // bits 12..13 (RW) Value to drive on the
                                                                //                  2-bit local_odt PHY outputs when reg_phy_dynamic_pwrdn_enable
                                                                //                  is asserted and a read is not in progress and
                                                                //                  reg_phy_dynamic_pwrdn_enable.
                                                                //                  Typically this is the value required to disable termination (00) to save
                                                                //                  power when idle.
                uint32_t                                : 1;    // bit  14     (R)  Reserved
                uint32_t    PHY_RST_N_SHADOW            : 1;    // bit  15     (RW) Writing a 1 to this bit will hold the PHY macros in reset.
                                                                //                  Writing a 0 will bring PHY macros out of reset.
                uint32_t                                : 4;    // bits 16..19 (R)  Reserved
                uint32_t    ENABLE_DYNAMIC_PWRDN_SHADOW : 1;    // bit  20     (RW) Dynamically enables powering down the IO receiver when not
                                                                //                  performing a read.
                                                                //                  0 = IO receivers always powered up.
                                                                //                  1 = IO receives only powered up during a read.
                uint32_t                                :11;    // bits 16..31 (R)  Reserved
            } b;                                                // bit access
            uint32_t reg;                                       // raw register
        } DDR_PHY_CTRL_1_SHDW_reg_t;
        
        /* (offset = 0x100) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* PRIORITY_TO_COS_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    PRI_0_COS       : 2;      // bits 0..1   (RW) Priority 0 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_1_COS       : 2;      // bits 2..3   (RW) Priority 1 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_2_COS       : 2;      // bits 4..5   (RW) Priority 2 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_3_COS       : 2;      // bits 6..7   (RW) Priority 3 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_4_COS       : 2;      // bits 8..9   (RW) Priority 4 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_5_COS       : 2;      // bits 10..11 (RW) Priority 5 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_6_COS       : 2;      // bits 12..13 (RW) Priority 6 COS mapping [see e_COS_MAPPING]
                uint32_t    PRI_7_COS       : 2;      // bits 14..15 (RW) Priority 7 COS mapping [see e_COS_MAPPING]
                uint32_t                    :15;      // bits 16..30 (R)  Reserved
                uint32_t    PRI_COS_MAP_EN  : 1;      // bit  31     (RW) Priority mapping enable
                                                      //                  [ 0x0 = disabled;
                                                      //                    0x1 = enabled ]
            } b;                                      // bit access
            uint32_t reg;                             // raw register
        } PRIORITY_TO_COS_MAPPING_reg_t;
        
        /* Enums for multi-value fields */
        enum e_COS_MAPPING : uint32_t 
        {
            /* Value can be 1 or 2.
             * Setting a value of 0 or 3 will not assign any class of service.
             */
            COS_NONE    = 0x0,
            COS_1       = 0x1,
            COS_2       = 0x2,
            COS_INVALID = 0x3
        };
        
        /* (offset = 0x104) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* CONNID_TO_COS_1_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    MSK_3_COS_1         : 2;      // bits 0..1   (RW) Mask for ConnID 3 COS 1 [see e_CONNID_MASK]
                uint32_t    CONNID_3_COS_1      : 8;      // bits 2..9   (RW) ConnID value 3 COS 1
                uint32_t    MSK_2_COS_1         : 2;      // bits 10..11 (RW) Mask for ConnID 2 COS 1 [see e_CONNID_MASK]
                uint32_t    CONNID_2_COS_1      : 8;      // bits 12..19 (RW) ConnID value 2 COS 1
                uint32_t    MSK_1_COS_1         : 3;      // bits 20..22 (RW) Mask for ConnID 1 COS 1 [see e_CONNID_MASK_EXT]
                uint32_t    CONNID_1_COS_1      : 8;      // bits 23..30 (RW) ConnID value 1 COS 1
                uint32_t    CONNID_COS_1_MAP_EN : 1;      // bit  31     (RW) ConnID mapping enable
                                                          //                  [ 0x0 = disabled;
                                                          //                    0x1 = enabled ]
            } b;                                          // bit access
            uint32_t reg;                                 // raw register
        } CONNID_TO_COS_1_MAPPING_reg_t;
        
        /* Enums for multi-value fields */
        enum e_CONNID_MASK : uint32_t 
        {
            /* Connection ID mask configuration
             * Determines which bits of the connection ID are masked
             */
            MASK_NONE    = 0x0,
            MASK_BIT0    = 0x1,
            MASK_BITS1_0 = 0x2,
            MASK_BITS2_0 = 0x3
        };
        
        enum e_CONNID_MASK_EXT : uint32_t 
        {
            /* Extended connection ID mask configuration
             * Determines which bits of the connection ID are masked
             */
            MASK_EXT_DISABLE = 0x0,
            MASK_EXT_BIT0    = 0x1,
            MASK_EXT_BITS1_0 = 0x2,
            MASK_EXT_BITS2_0 = 0x3,
            MASK_EXT_BITS3_0 = 0x4,
            MASK_EXT_BITS4_0 = 0x5,
            MASK_EXT_BITS5_0 = 0x6,
            MASK_EXT_BITS6_0 = 0x7
        };
        
        /* (offset = 0x108) [reset = 0x0] */ 
        typedef union 
        { 
                                                  /* CONNID_TO_COS_2_MAPPING
                                                   */
            struct 
            {                                      
                uint32_t    MSK_3_COS_2         : 2;      // bits 0..1   (RW) Mask for ConnID 3 COS 2 [see e_CONNID_MASK]
                uint32_t    CONNID_3_COS_2      : 8;      // bits 2..9   (RW) ConnID value 3 COS 2
                uint32_t    MSK_2_COS_2         : 2;      // bits 10..11 (RW) Mask for ConnID 2 COS 2 [see e_CONNID_MASK]
                uint32_t    CONNID_2_COS_2      : 8;      // bits 12..19 (RW) ConnID value 2 COS 2
                uint32_t    MSK_1_COS_2         : 3;      // bits 20..22 (RW) Mask for ConnID 1 COS 2 [see e_CONNID_MASK_EXT]
                uint32_t    CONNID_1_COS_2      : 8;      // bits 23..30 (RW) ConnID value 1 COS 2
                uint32_t    CONNID_COS_2_MAP_EN : 1;      // bit  31     (RW) ConnID mapping enable
                                                          //                  [ 0x0 = disabled;
                                                          //                    0x1 = enabled ]
            } b;                                          // bit access
            uint32_t reg;                                 // raw register
        } CONNID_TO_COS_2_MAPPING_reg_t;

        /* (offset = 0x120) [reset = 0x00000305] */ 
        typedef union 
        { 
                                                  /* READ_WRITE_EXEC_THRESHOLD
                                                   */
            struct 
            {                                      
                uint32_t    RD_THRSH     : 5;      // bits 0..4   (RW) Read threshold
                                                   //                  Number of read bursts before switching to writes (value = programmed -1)
                uint32_t                 : 3;      // bits 5..7   (R)  Reserved
                uint32_t    WR_THRSH     : 5;      // bits 8..12  (RW) Write threshold
                                                   //                  Number of write bursts before switching to reads (value = programmed -1)
                uint32_t                 :19;      // bits 13..31 (R)  Reserved
            } b;                                   // bit access
            uint32_t reg;                          // raw register
        } READ_WRITE_EXEC_THRESHOLD_reg_t;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////         ALL EMIF MODULE MEMORY MAP    //////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct AM335x_EMIF4D_Type
        {                                                                                      
            __R    EMIF_MOD_ID_REV_reg_t              EMIF_MOD_ID_REV;            // (0x0) 
            __R    STATUS_reg_t                       STATUS;                     // (0x4)
            __RW   SDRAM_CONFIG_reg_t                 SDRAM_CONFIG;               // (0x8)
            __RW   SDRAM_CONFIG_2_reg_t               SDRAM_CONFIG_2;             // (0xC)
            __RW   SDRAM_REF_CTRL_reg_t               SDRAM_REF_CTRL;             // (0x10)
            __RW   SDRAM_REF_CTRL_SHDW_reg_t          SDRAM_REF_CTRL_SHDW;        // (0x14)
            __RW   SDRAM_TIM_1_reg_t                  SDRAM_TIM_1;                // (0x18)
            __RW   SDRAM_TIM_1_SHDW_reg_t             SDRAM_TIM_1_SHDW;           // (0x1C)
            __RW   SDRAM_TIM_2_reg_t                  SDRAM_TIM_2;                // (0x20)
            __RW   SDRAM_TIM_2_SHDW_reg_t             SDRAM_TIM_2_SHDW;           // (0x24)  
            __RW   SDRAM_TIM_3_reg_t                  SDRAM_TIM_3;                // (0x28) 
            __RW   SDRAM_TIM_3_SHDW_reg_t             SDRAM_TIM_3_SHDW;           // (0x2C)
            __R    uint32_t                           RESERVED1[2];
            __RW   PWR_MGMT_CTRL_reg_t                PWR_MGMT_CTRL;              // (0x38)
            __RW   PWR_MGMT_CTRL_SHDW_reg_t           PWR_MGMT_CTRL_SHDW;         // (0x3C)
            __R    uint32_t                           RESERVED2[5];
            __RW   OCP_CONFIG_reg_t                   OCP_CONFIG;                 // (0x54)
            __R    OCP_CFG_VAL_1_reg_t                OCP_CFG_VAL_1;              // (0x58)
            __R    OCP_CFG_VAL_2_reg_t                OCP_CFG_VAL_2;              // (0x5C)
            __R    uint32_t                           RESERVED3[8];
            __R    PERF_CNT_1_reg_t                   PERF_CNT_1;                 // (0x80)
            __R    PERF_CNT_2_reg_t                   PERF_CNT_2;                 // (0x84)
            __RW   PERF_CNT_CFG_reg_t                 PERF_CNT_CFG;               // (0x88)
            __RW   PERF_CNT_SEL_reg_t                 PERF_CNT_SEL;               // (0x8C) 
            __R    PERF_CNT_TIM_reg_t                 PERF_CNT_TIM;               // (0x90)
            __R    uint32_t                           RESERVED4[1];
            __RW   READ_IDLE_CTRL_reg_t               READ_IDLE_CTRL;             // (0x98)
            __RW   READ_IDLE_CTRL_SHDW_reg_t          READ_IDLE_CTRL_SHDW;        // (0x9C)
            __R    uint32_t                           RESERVED5[1];
            __RW   IRQSTATUS_RAW_SYS_reg_t            IRQSTATUS_RAW_SYS;          // (0xA4)
            __R    uint32_t                           RESERVED6[1];
            __RW   IRQSTATUS_SYS_reg_t                IRQSTATUS_SYS;              // (0xAC)
            __R    uint32_t                           RESERVED7[1];
            __RW   IRQENABLE_SET_SYS_reg_t            IRQENABLE_SET_SYS;          // (0xB4)
            __R    uint32_t                           RESERVED8[1];
            __RW   IRQENABLE_CLR_SYS_reg_t            IRQENABLE_CLR_SYS;          // (0xBC)
            __R    uint32_t                           RESERVED9[2];
            __RW   ZQ_CONFIG_reg_t                    ZQ_CONFIG;                  // (0xC8)
            __R    uint32_t                           RESERVED10[2];
            __R    RDWRLVL_RAMP_WIN_reg_t             RDWRLVL_RAMP_WIN;           // (0xD4) 
            __RW   RDWRLVL_RAMP_CTRL_reg_t            RDWRLVL_RAMP_CTRL;          // (0xD8) 
            __RW   RDWRLVL_CTRL_reg_t                 RDWRLVL_CTRL;               // (0xDC)
            __R    uint32_t                           RESERVED11[1];
            __RW   DDR_PHY_CTRL_1_reg_t               DDR_PHY_CTRL_1;             // (0xE4)
            __RW   DDR_PHY_CTRL_1_SHDW_reg_t          DDR_PHY_CTRL_1_SHDW;        // (0xE8)
            __R    uint32_t                           RESERVED12[5];
            __RW   PRIORITY_TO_COS_MAPPING_reg_t      PRIORITY_TO_COS_MAPPING;    // (0x100)
            __RW   CONNID_TO_COS_1_MAPPING_reg_t      CONNID_TO_COS_1_MAPPING;    // (0x104)
            __RW   CONNID_TO_COS_2_MAPPING_reg_t      CONNID_TO_COS_2_MAPPING;    // (0x108)
            __R    uint32_t                           RESERVED13[5]; 
            __RW   READ_WRITE_EXEC_THRESHOLD_reg_t    READ_WRITE_EXEC_THRESHOL;   // (0x120)  
        };

        struct AM335x_DDR23mPHY_Type
        {     
            __R   uint32_t              RESERVED[7];                                                                                 
            __W   CSR0_reg_t            CMD0_CTRL_SLAVE_RATIO_0;          // (0x01C)  DDR PHY Command 0 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED1[2];
            __W   DLD0_reg_t            CMD0_DLL_LOCK_DIFF_0;             // (0x028)  DDR PHY Command 0 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD0_INVERT_CLKOUT_0;             // (0x02C)  DDR PHY Command 0 Invert Clockout Selection Register
            __R   uint32_t              RESERVED2[8];
            __W   CSR0_reg_t            CMD1_CTRL_SLAVE_RATIO_0;          // (0x050)  DDR PHY Command 1 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED3[2];
            __W   DLD0_reg_t            CMD1_DLL_LOCK_DIFF_0;             // (0x05C)  DDR PHY Command 1 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD1_INVERT_CLKOUT_0;             // (0x060)  DDR PHY Command 1 Invert Clockout Selection Register
            __R   uint32_t              RESERVED4[8];
            __W   CSR0_reg_t            CMD2_CTRL_SLAVE_RATIO_0;          // (0x084)  DDR PHY Command 2 Address/Command Slave Ratio Register
            __R   uint32_t              RESERVED5[2];
            __W   DLD0_reg_t            CMD2_DLL_LOCK_DIFF_0;             // (0x090)  DDR PHY Command 2 Address/Command DLL Lock Difference Register
            __W   ICLK0_reg_t           CMD2_INVERT_CLKOUT_0;             // (0x094)  DDR PHY Command 2 Invert Clockout Selection Register
            __R   uint32_t              RESERVED6[12];
            __W   RDQSSR0_reg_t         DATA0_RD_DQS_SLAVE_RATIO_0;       // (0x0C8)  DDR PHY Data Macro 0 Read DQS Slave Ratio Register
            __R   uint32_t              RESERVED7[4];
            __W   WDQSSR0_reg_t         DATA0_WR_DQS_SLAVE_RATIO_0;       // (0x0DC)  DDR PHY Data Macro 0 Write DQS Slave Ratio Register
            __R   uint32_t              RESERVED8[4];
            __W   MWRLVLINI_RATIO_reg_t DATA0_WRLVL_INIT_RATIO_0;         // (0x0F0)  DDR PHY Data Macro 0 Write Leveling Init Ratio Register
            __R   uint32_t              RESERVED9[1];
            __W   MWRLVLINI_MODE_reg_t  DATA0_WRLVL_INIT_MODE_0;          // (0x0F8)  DDR PHY Data Macro 0 Write Leveling Init Mode Ratio Selection Register
            __W   DQSGTI_RATIO_reg_t    DATA0_GATELVL_INIT_RATIO_0;       // (0x0FC)  DDR PHY Data Macro 0 DQS Gate Training Init Ratio Register
            __R   uint32_t              RESERVED10[1];
            __W   DQS_GTI_MODE_reg_t    DATA0_GATELVL_INIT_MODE_0;        // (0x104)  DDR PHY Data Macro 0 DQS Gate Training Init Mode Ratio Selection Register
            __W   DQS_GS_RATIO_reg_t    DATA0_FIFO_WE_SLAVE_RATIO_0;      // (0x108)  DDR PHY Data Macro 0 DQS Gate Slave Ratio Register
            __R   uint32_t              RESERVED11[4];
            __RW  DQS_T_DQ_OFFSET_reg_t DATA0_DQ_OFFSET_0;                // (0x11C)  Offset value from DQS to DQ for Data Macro 0
            __W   WDS_RATIO_reg_t       DATA0_WR_DATA_SLAVE_RATIO_0;      // (0x120)  DDR PHY Data Macro 0 Write Data Slave Ratio Register 
            __R   uint32_t              RESERVED12[4];
            __W   DELAY_SEL_reg_t       DATA0_USE_RANK0_DELAYS;           // (0x134)  DDR PHY Data Macro 0 Delay Selection Register
            __W   DLL_LOCK_DIFF_reg_t   DATA0_DLL_LOCK_DIFF_0;            // (0x138)  DDR PHY Data Macro 0 DLL Lock Difference Register
            __R   uint32_t              RESERVED13[12];
            __W   RDQSSR0_reg_t         DATA1_RD_DQS_SLAVE_RATIO_0;       // (0x16C)  DDR PHY Data Macro 1 Read DQS Slave Ratio Register
            __R   uint32_t              RESERVED14[4];
            __W   WDQSSR0_reg_t         DATA1_WR_DQS_SLAVE_RATIO_0;       // (0x180)  DDR PHY Data Macro 1 Write DQS Slave Ratio Register
            __R   uint32_t              RESERVED15[4];
            __W   MWRLVLINI_RATIO_reg_t DATA1_WRLVL_INIT_RATIO_0;         // (0x194)  DDR PHY Data Macro 1 Write Leveling Init Ratio Register 
            __R   uint32_t              RESERVED16[1];
            __W   MWRLVLINI_MODE_reg_t  DATA1_WRLVL_INIT_MODE_0;          // (0x19C)  DDR PHY Data Macro 1 Write Leveling Init Mode Ratio Selection Register
            __W   DQSGTI_RATIO_reg_t    DATA1_GATELVL_INIT_RATIO_0;       // (0x1A0)  DDR PHY Data Macro 1 DQS Gate Training Init Ratio Register
            __R   uint32_t              RESERVED17[1];
            __W   DQS_GTI_MODE_reg_t    DATA1_GATELVL_INIT_MODE_0;        // (0x1A8)  DDR PHY Data Macro 1 DQS Gate Training Init Mode Ratio Selection Register
            __W   DQS_GS_RATIO_reg_t    DATA1_FIFO_WE_SLAVE_RATIO_0;      // (0x1AC)  DDR PHY Data Macro 1 DQS Gate Slave Ratio Register
            __R   uint32_t              RESERVED18[4];
            __RW  DQS_T_DQ_OFFSET_reg_t DATA1_DQ_OFFSET_0;                // (0x1C0)  Offset value from DQS to DQ for Data Macro 1
            __W   WDS_RATIO_reg_t       DATA1_WR_DATA_SLAVE_RATIO_0;      // (0x1C4)  DDR PHY Data Macro 1 Write Data Slave Ratio Register
            __R   uint32_t              RESERVED19[4];
            __W   DELAY_SEL_reg_t       DATA1_USE_RANK0_DELAYS;           // (0x1D8)  DDR PHY Data Macro 1 Delay Selection Register
            __W   DLL_LOCK_DIFF_reg_t   DATA1_DLL_LOCK_DIFF_0;            // (0x1DC)  DDR PHY Data Macro 1 DLL Lock Difference Register
        };

        constexpr uint32_t AM335x_DDR23mPHY_BASE = 0x44E12000; 
        constexpr uint32_t AM335x_EMIF0_BASE     = 0x4C000000;

        constexpr AM335x_DDR23mPHY_Type  *AM335x_DDR23mPHY = reinterpret_cast<AM335x_DDR23mPHY_Type *>(AM335x_DDR23mPHY_BASE); 
        constexpr AM335x_EMIF4D_Type     *AM335x_EMIF0     = reinterpret_cast<AM335x_EMIF4D_Type *>(AM335x_EMIF0_BASE); 
        

    } // namespace EMIF
} // namespace REGS

#endif //_EMIF_H_
