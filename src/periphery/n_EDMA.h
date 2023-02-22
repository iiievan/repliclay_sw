#ifndef __N_EDMA_H
#define __N_EDMA_H

#include <stdint.h>


namespace n_EDMA
{
    /*! @brief      The transmitter section consists of the transmit holding register and the transmit shift register.  
    *   @details    The transmit holding register is a 64-byte FIFO. The MPU writes data to the THR. The data is placed in the transmit shift
    *               register where it is shifted out serially on the TX output. If the FIFO is disabled, location zero of the FIFO
    *               is used to store the data.
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {
             
            uint32_t    THR        :8;         // bit: 0..7    (W) Transmit holding register.[Value 0 to FFh.]
            uint32_t               :24;        // bit: 8..32   Reserved  
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access 
    } THR_reg_t;

    struct AM335x_EDMA_Type
    {                                                                                      
        __  _reg_t           PID;            // (0x00)  
        __  _reg_t           CCCFG;          // (0x04)  
        __  uint32_t         RESERVED1[2];
        __  _reg_t           SYSCONFIG;      // (0x10)  
        __  _reg_t           DCHMAP_0;       // (0x100)  
        __  _reg_t           DCHMAP_1;       // (0x104) 
        __  _reg_t           DCHMAP_2;       // (0x108) 
        __  _reg_t           DCHMAP_3;       // (0x10C) 
        __  _reg_t           DCHMAP_4;       // (0x110) 
        __  _reg_t           DCHMAP_5;       // (0x114) 
        __  _reg_t           DCHMAP_6;       // (0x118) 
        __  _reg_t           DCHMAP_7;       // (0x11C) 
        __  _reg_t           DCHMAP_8;       // (0x120)  
        __  _reg_t           DCHMAP_9;       // (0x124) 
        __  _reg_t           DCHMAP_10;      // (0x128) 
        __  _reg_t           DCHMAP_11;      // (0x12C) 
        __  _reg_t           DCHMAP_12;      // (0x130) 
        __  _reg_t           DCHMAP_13;      // (0x134) 
        __  _reg_t           DCHMAP_14;      // (0x138) 
        __  _reg_t           DCHMAP_15;      // (0x13C)
        __  _reg_t           DCHMAP_16;      // (0x140)  
        __  _reg_t           DCHMAP_17;      // (0x144) 
        __  _reg_t           DCHMAP_18;      // (0x148) 
        __  _reg_t           DCHMAP_19;      // (0x14C) 
        __  _reg_t           DCHMAP_20;      // (0x150) 
        __  _reg_t           DCHMAP_21;      // (0x154) 
        __  _reg_t           DCHMAP_22;      // (0x158) 
        __  _reg_t           DCHMAP_23;      // (0x15C) 
        __  _reg_t           DCHMAP_24;      // (0x160)  
        __  _reg_t           DCHMAP_25;      // (0x164) 
        __  _reg_t           DCHMAP_26;      // (0x168) 
        __  _reg_t           DCHMAP_27;      // (0x16C) 
        __  _reg_t           DCHMAP_28;      // (0x170) 
        __  _reg_t           DCHMAP_29;      // (0x174) 
        __  _reg_t           DCHMAP_30;      // (0x178) 
        __  _reg_t           DCHMAP_31;      // (0x17C)
        __  _reg_t           DCHMAP_32;      // (0x180)  
        __  _reg_t           DCHMAP_33;      // (0x184) 
        __  _reg_t           DCHMAP_34;      // (0x188) 
        __  _reg_t           DCHMAP_35;      // (0x18C) 
        __  _reg_t           DCHMAP_36;      // (0x190) 
        __  _reg_t           DCHMAP_37;      // (0x194) 
        __  _reg_t           DCHMAP_38;      // (0x198) 
        __  _reg_t           DCHMAP_39;      // (0x19C) 
        __  _reg_t           DCHMAP_40;      // (0x1A0)  
        __  _reg_t           DCHMAP_41;      // (0x1A4) 
        __  _reg_t           DCHMAP_42;      // (0x1A8) 
        __  _reg_t           DCHMAP_43;      // (0x1AC) 
        __  _reg_t           DCHMAP_44;      // (0x1B0) 
        __  _reg_t           DCHMAP_45;      // (0x1B4) 
        __  _reg_t           DCHMAP_46;      // (0x1B8) 
        __  _reg_t           DCHMAP_47;      // (0x1BC)
        __  _reg_t           DCHMAP_48;      // (0x1C0)  
        __  _reg_t           DCHMAP_49;      // (0x1C4) 
        __  _reg_t           DCHMAP_50;      // (0x1C8) 
        __  _reg_t           DCHMAP_51;      // (0x1CC) 
        __  _reg_t           DCHMAP_52;      // (0x1D0) 
        __  _reg_t           DCHMAP_53;      // (0x1D4) 
        __  _reg_t           DCHMAP_54;      // (0x1D8) 
        __  _reg_t           DCHMAP_55;      // (0x1DC) 
        __  _reg_t           DCHMAP_56;      // (0x1E0)  
        __  _reg_t           DCHMAP_57;      // (0x1E4) 
        __  _reg_t           DCHMAP_58;      // (0x1E8) 
        __  _reg_t           DCHMAP_59;      // (0x1EC) 
        __  _reg_t           DCHMAP_60;      // (0x1F0) 
        __  _reg_t           DCHMAP_61;      // (0x1F4) 
        __  _reg_t           DCHMAP_62;      // (0x1F8) 
        __  _reg_t           DCHMAP_63;      // (0x1FC)
        __  _reg_t           QCHMAP_0;       // (0x200) 
        __  _reg_t           QCHMAP_1;       // (0x204) 
        __  _reg_t           QCHMAP_2;       // (0x208) 
        __  _reg_t           QCHMAP_3;       // (0x20C) 
        __  _reg_t           QCHMAP_4;       // (0x210) 
        __  _reg_t           QCHMAP_5;       // (0x214) 
        __  _reg_t           QCHMAP_6;       // (0x218) 
        __  _reg_t           QCHMAP_7;       // (0x21C)  
        __  _reg_t           DMAQNUM_0;      // (0x240) 
        __  _reg_t           DMAQNUM_1;      // (0x244) 
        __  _reg_t           DMAQNUM_2;      // (0x248) 
        __  _reg_t           DMAQNUM_3;      // (0x24C) 
        __  _reg_t           DMAQNUM_4;      // (0x250) 
        __  _reg_t           DMAQNUM_5;      // (0x254) 
        __  _reg_t           DMAQNUM_6;      // (0x258) 
        __  _reg_t           DMAQNUM_7;      // (0x25C) 
        __  _reg_t           QDMAQNUM;       // (0x)  
        __  _reg_t           QUEPRI;         // (0x)  
        __  _reg_t           EMR;            // (0x)  
        __  _reg_t           EMRH;           // (0x)  
        __  _reg_t           EMCR;           // (0x)  
        __  _reg_t           EMCRH;          // (0x)  
        __  _reg_t           QEMR;           // (0x)  
        __  _reg_t           QEMCR;          // (0x)  
        __  _reg_t           CCERR;          // (0x)  
        __  _reg_t           CCERRCLR;       // (0x)  
        __  _reg_t           EEVAL;          // (0x)  
        __  _reg_t           DRAE0;          // (0x)      
        __  _reg_t           DRAEH0;         // (0x)  
        __  _reg_t           DRAE1;          // (0x)  
        __  _reg_t           DRAEH1;         // (0x)  
        __  _reg_t           DRAE2;          // (0x)  
        __  _reg_t           DRAEH2;         // (0x)  
        __  _reg_t           DRAE3;          // (0x)  
        __  _reg_t           DRAEH3;         // (0x)  
        __  _reg_t           DRAE4;          // (0x)  
        __  _reg_t           DRAEH4;         // (0x)  
        __  _reg_t           DRAE5;          // (0x)  
        __  _reg_t           DRAEH5;         // (0x)  
        __  _reg_t           DRAE6;          // (0x)  
        __  _reg_t           DRAEH6;         // (0x)  
        __  _reg_t           DRAE7;          // (0x) 
        __  _reg_t           DRAEH7;         // (0x)  
        __  _reg_t           QRAE_0;         // (0x380)  
        __  _reg_t           QRAE_1;         // (0x384)  
        __  _reg_t           QRAE_2;         // (0x388)  
        __  _reg_t           QRAE_3;         // (0x38�)  
        __  _reg_t           QRAE_4;         // (0x390)  
        __  _reg_t           QRAE_5;         // (0x394)  
        __  _reg_t           QRAE_6;         // (0x398)  
        __  _reg_t           QRAE_7;         // (0x39�)  
        __  _reg_t           Q0E0;           // (0x)  
        __  _reg_t           Q0E1;           // (0x)  
        __  _reg_t           Q0E2;           // (0x)  
        __  _reg_t           Q0E3;           // (0x)  
        __  _reg_t           Q0E4;           // (0x)  
        __  _reg_t           Q0E5;           // (0x)  
        __  _reg_t           Q0E6;           // (0x) 
        __  _reg_t           Q0E7;           // (0x)  
        __  _reg_t           Q0E8;           // (0x)  
        __  _reg_t           Q0E9;           // (0x)  
        __  _reg_t           Q0E10;          // (0x)  
        __  _reg_t           Q0E11;          // (0x)  
        __  _reg_t           Q0E12;          // (0x)  
        __  _reg_t           Q0E13;          // (0x) 
        __  _reg_t           Q0E14;          // (0x)  
        __  _reg_t           Q0E15;          // (0x)  
        __  _reg_t           Q1E0;           // (0x)  
        __  _reg_t           Q1E1;           // (0x)  
        __  _reg_t           Q1E2;           // (0x)  
        __  _reg_t           Q1E3;           // (0x)  
        __  _reg_t           Q1E4;           // (0x) 
        __  _reg_t           Q1E5;           // (0x)  
        __  _reg_t           Q1E6;           // (0x)  
        __  _reg_t           Q1E7;           // (0x)  
        __  _reg_t           Q1E8;           // (0x)  
        __  _reg_t           Q1E9;           // (0x)  
        __  _reg_t           Q1E10;          // (0x)  
        __  _reg_t           Q1E11;          // (0x) 
        __  _reg_t           Q1E12;          // (0x)  
        __  _reg_t           Q1E13;          // (0x)  
        __  _reg_t           Q1E14;          // (0x)  
        __  _reg_t           Q1E15;          // (0x)  
        __  _reg_t           Q2E0;           // (0x)  
        __  _reg_t           Q2E1;           // (0x)  
        __  _reg_t           Q2E2;           // (0x) 
        __  _reg_t           Q2E3;           // (0x)  
        __  _reg_t           Q2E4;           // (0x)  
        __  _reg_t           Q2E5;           // (0x)  
        __  _reg_t           Q2E6;           // (0x)  
        __  _reg_t           Q2E7;           // (0x)  
        __  _reg_t           Q2E8;           // (0x)  
        __  _reg_t           Q2E9;           // (0x) 
        __  _reg_t           Q2E10;          // (0x)  
        __  _reg_t           Q2E11;          // (0x)  
        __  _reg_t           Q2E12;          // (0x) 
        __  _reg_t           Q2E13;          // (0x)  
        __  _reg_t           Q2E14;          // (0x)  
        __  _reg_t           Q2E15;          // (0x)  
        __  _reg_t           QSTAT_0;        // (0x)  
        __  _reg_t           QSTAT_1;        // (0x)  
        __  _reg_t           QSTAT_2;        // (0x)  
        __  _reg_t           QWMTHRA;        // (0x) 
        __  _reg_t           CCSTAT;         // (0x)  
        __  _reg_t           MPFAR;          // (0x)  
        __  _reg_t           MPFSR;          // (0x) 
        __  _reg_t           MPFCR;          // (0x)  
        __  _reg_t           MPPAG;          // (0x)  
        __  _reg_t           MPPA_0;         // (0x)  
        __  _reg_t           MPPA_1;         // (0x)  
        __  _reg_t           MPPA_2;         // (0x)  
        __  _reg_t           MPPA_3;         // (0x)  
        __  _reg_t           MPPA_4;         // (0x) 
        __  _reg_t           MPPA_5;         // (0x)  
        __  _reg_t           MPPA_6;         // (0x)  
        __  _reg_t           MPPA_7;         // (0x) 
        __  _reg_t           ER;             // (0x)  
        __  _reg_t           ERH;            // (0x)  
        __  _reg_t           ECR;            // (0x)  
        __  _reg_t           ECRH;           // (0x)  
        __  _reg_t           ESR;            // (0x)  
        __  _reg_t           ESRH;           // (0x)  
        __  _reg_t           CER;            // (0x)   
        __  _reg_t           CERH;           // (0x)  
        __  _reg_t           EER;            // (0x)  
        __  _reg_t           EERH;           // (0x)  
        __  _reg_t           EECR;           // (0x)  
        __  _reg_t           EECRH;          // (0x)  
        __  _reg_t           EESR;           // (0x)  
        __  _reg_t           EESRH;          // (0x)
        __  _reg_t           SER;            // (0x)  
        __  _reg_t           SERH;           // (0x)  
        __  _reg_t           SECR;           // (0x)  
        __  _reg_t           SECRH;          // (0x)  
        __  _reg_t           IER;            // (0x)  
        __  _reg_t           IERH;           // (0x)  
        __  _reg_t           IECR;           // (0x)
        __  _reg_t           IECRH;          // (0x)  
        __  _reg_t           IESR;           // (0x)  
        __  _reg_t           IESRH;          // (0x)  
        __  _reg_t           IPR;            // (0x)  
        __  _reg_t           IPRH;           // (0x)  
        __  _reg_t           ICR;            // (0x)  
        __  _reg_t           ICRH;           // (0x)
        __  _reg_t           IEVAL;          // (0x)  
        __  _reg_t           QER;            // (0x)  
        __  _reg_t           QEER;           // (0x)  
        __  _reg_t           QEECR;          // (0x)  
        __  _reg_t           QEESR;          // (0x)  
        __  _reg_t           QSER;           // (0x)  
        __  _reg_t           QSECR;          // (0x)
    };
}

#endif //__N_EDMA_H