#ifndef _EMIF_H_
#define _EMIF_H_

#include <stdint.h>

namespace REGS
{
    //This is EMIF namespace
    namespace EMIF
    { 
    /*******************************************************************************************************************************************************************************/  
    
    /*************************************************************************** AM335x_EMIF_Type Registers **********************************************************************/ 
    
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

        struct AM335x_EMIF_Type
        {     
            __R   uint32_t              RESERVED[6];                                                                                 
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
            __R   uint32_t              RESERVED8[];
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

        constexpr uint32_t AM335x_EMIF_BASE = 0x44E1_2000; 

        constexpr AM335x_EMIF_Type  *AM335x_EMIF = ((AM335x_EMIF_Type *) AM335x_EMIF_BASE); 
        

    } // namespace EMIF
} // namespace REGS

#endif //_EMIF_H_
