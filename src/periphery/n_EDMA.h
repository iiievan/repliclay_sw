#ifndef __N_EDMA_H
#define __N_EDMA_H

#include <stdint.h>


namespace n_EDMA
{  
/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_EDMA3CC_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t PID    :16;         // bit: 0..15   (R) .  
            uint32_t        :16;         // bit: 16..31   Reserved.         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access 
    } PIDCC_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t    NUM_DMACH   :3;         // bit: 0..2      (R) .  
            uint32_t                :1;         // bit: 3         (R) . 
            uint32_t    NUM_QDMACH  :3;         // bit: 4..6      (R) . 
            uint32_t                :1;         // bit: 7         (R) . 
            uint32_t    NUM_INTCH   :3;         // bit: 8..10     (R) . 
            uint32_t                :1;         // bit: 11        (R) . 
            uint32_t    NUM_PAENTRY :3;         // bit: 12..14    (R) . 
            uint32_t                :1;         // bit: 15        (R) . 
            uint32_t    NUM_EVQUE   :3;         // bit: 16..18    (R) . 
            uint32_t                :1;         // bit: 19        (R) . 
            uint32_t    NUM_REGN    :2;         // bit: 20,21     (R) . 
            uint32_t                :2;         // bit: 22,23     (R) . 
            uint32_t    CHMAP_EXIST :1;         // bit: 24        (R) . 
            uint32_t    MP_EXIST    :1;         // bit: 25        (R) . 
            uint32_t                :6;         // bit: 26..31   Reserved.         
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } CCCFG_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t                  :2;         // bit: 0,1     Reserved.
            uint32_t    IDLEMODE      :2;         // bit: 2,3     (RW)    
            uint32_t                  :28;        // bit: 4..31   Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } SYSCONFIGCC_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t              :5;         // bit: 0..4        Reserved.
            uint32_t    PAENTRY   :9;         // bit: 5..13       (RW) Bitfield description.  
            uint32_t              :18;        // bit: 14..31      Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } DCHMAP_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t                  :2;         // bit: 0,1     Reserved
            uint32_t    TRWORD        :3;         // bit: 2..4    (RW) .
            uint32_t    PAENTRY       :9;         // bit: 5..13   (RW) .
            uint32_t                  :18;        // bit: 14..31  Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } QCHMAP_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    E0  :3;    // bit: 0..2     (RW) .
            uint32_t        :1;    // bit: 3        Reserved.
            uint32_t    E1  :3;    // bit: 4..6     (RW) .
            uint32_t        :1;    // bit: 7        Reserved
            uint32_t    E2  :3;    // bit: 8..10    (RW) .
            uint32_t        :1;    // bit: 11       Reserved
            uint32_t    E3  :3;    // bit: 12..14   (RW) .
            uint32_t        :1;    // bit: 15       Reserved
            uint32_t    E4  :3;    // bit: 16..18   (RW) .
            uint32_t        :1;    // bit: 19       Reserved
            uint32_t    E5  :3;    // bit: 20..21   (RW) .
            uint32_t        :1;    // bit: 23       Reserved
            uint32_t    E6  :3;    // bit: 24..26   (RW) .
            uint32_t        :1;    // bit: 27       Reserved.
            uint32_t    E7  :3;    // bit: 28..30   (RW) .
            uint32_t        :1;    // bit: 31       Reserved        
        } b;                       // Structure used for bit access 
        uint32_t  reg;             // Type used for register access 
    } DMAQNUM_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
          
            uint32_t    E0  :3;    // bit: 0..2     (RW) .
            uint32_t        :1;    // bit: 3        Reserved.
            uint32_t    E1  :3;    // bit: 4..6     (RW) .
            uint32_t        :1;    // bit: 7        Reserved
            uint32_t    E2  :3;    // bit: 8..10    (RW) .
            uint32_t        :1;    // bit: 11       Reserved
            uint32_t    E3  :3;    // bit: 12..14   (RW) .
            uint32_t        :1;    // bit: 15       Reserved
            uint32_t    E4  :3;    // bit: 16..18   (RW) .
            uint32_t        :1;    // bit: 19       Reserved
            uint32_t    E5  :3;    // bit: 20..21   (RW) .
            uint32_t        :1;    // bit: 23       Reserved
            uint32_t    E6  :3;    // bit: 24..26   (RW) .
            uint32_t        :1;    // bit: 27       Reserved.
            uint32_t    E7  :3;    // bit: 28..30   (RW) .
            uint32_t        :1;    // bit: 31       Reserved           
        } b;                       // Structure used for bit access 
        uint32_t  reg;             // Type used for register access 
    } QDMAQNUM_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    PRIQ0      :3;        // bit: 0..2    (RW) . 
            uint32_t               :1;        // bit: 3        Reserved
            uint32_t    PRIQ1      :3;        // bit: 4..6    (RW) .
            uint32_t               :1;        // bit: 7        Reserved.    
            uint32_t    PRIQ2      :3;        // bit: 8..10   (RW) .
            uint32_t               :21;       // bit: 11..31   Reserved.
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } QUEPRI_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31        (R) .         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31      (R) .        
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;        // bit: 0..31    (W) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;        // bit: 0..31        (W) . 
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } EMCRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :8;         // bit: 0..7        (R) .
            uint32_t            :24;        // bit: 8..31       (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEMR_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   
            /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7        (W) .
            uint32_t            :24;        // bit: 8..31       (R) .        
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEMCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {    /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    QTHRXCD0      :1;         // bit: 0        (R) .
            uint32_t    QTHRXCD1      :1;         // bit: 1        (R) 
            uint32_t    QTHRXCD2      :1;         // bit: 2        (R) 
            uint32_t                  :13;        // bit: 3..15    (R) 
            uint32_t    TCCERR        :1;         // bit: 16       (R)  
            uint32_t                  :15;        // bit: 17..31   (R) .         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } CCERR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    QTHRXCD0      :1;         // bit: 0        (W) .
            uint32_t    QTHRXCD1      :1;         // bit: 1        (W) 
            uint32_t    QTHRXCD2      :1;         // bit: 2        (W) 
            uint32_t                  :13;        // bit: 3..15    (R) 
            uint32_t    TCCERR        :1;         // bit: 16       (W)  
            uint32_t                  :15;        // bit: 17..31   (R) .         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } CCERRCLR_reg_t;
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {                                         /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
             
            uint32_t    EVAL      :1;         // bit: 0       (W).  
            uint32_t              :31;        // bit: 1..31   Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } EEVAL_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/             
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access  
    } DRAEH0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access  
    } DRAE1_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } DRAEH1_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAEH2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE3_reg_t;
    
/*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } DRAEH3_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE4_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAEH4_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE5_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register accesss 
    } DRAEH5_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE6_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAEH6_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } DRAE7_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :32;         // bit: 0..31       (RW) .          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } DRAEH7_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    En      :8;         // bit: 0..7       (RW) .  
            uint32_t            :24;        // bit: 8..31      Reserved.
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } QRAE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    ENUM      :6;         // bit: 0..5      (R) .  
            uint32_t    ETYPE     :2;         // bit: 6,7       (R) .
            uint32_t              :24;        // bit: 8..31     Reserved.
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } QE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t    STRTPTR     :4;         // bit: 0..3      (R) .  
            uint32_t                :4;         // bit: 4..7      Reserved.
            uint32_t    NUMVAL      :5;         // bit: 8..12     (R) .  
            uint32_t                :3;         // bit: 13..15    Reserved.
            uint32_t    WM          :5;         // bit: 16..20    (R) .  
            uint32_t                :3;         // bit: 21..23    Reserved.
            uint32_t    THRXCD      :1;         // bit: 24        (R) .
            uint32_t                :7;         // bit: 25..31     Reserved.
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access  
    } QSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    Q0      :5;         // bit: 0..4      (RW) .  
            uint32_t            :3;         // bit: 5..7      Reserved.
            uint32_t    Q1      :5;         // bit: 8..12     (RW) .  
            uint32_t            :3;         // bit: 13..15    Reserved.
            uint32_t    Q2      :5;         // bit: 16..20    (RW) .  
            uint32_t            :11;        // bit: 21..31    Reserved.       
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QWMTHRA_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVTACTV      :1;         // bit: 0        (R) . 
            uint32_t    QEVTACTV     :1;         // bit: 1        (R) .
            uint32_t    TRACTV       :1;         // bit: 2        (R) .
            uint32_t                 :1;         // bit: 3        Reserved.
            uint32_t    ACTV         :1;         // bit: 4        (R) . 
            uint32_t                 :3;         // bit: 5..7     Reserved.
            uint32_t    COMPACTV     :6;         // bit: 8..13    (R) .
            uint32_t                 :2;         // bit: 14,15    Reserved. 
            uint32_t    QUEACTV0     :1;         // bit: 16       (R) . 
            uint32_t    QUEACTV1     :1;         // bit: 17       (R) .
            uint32_t    QUEACTV2     :1;         // bit: 18       (R) .
            uint32_t                 :13;        // bit: 19..31   Reserved.        
        } b;                                     // Structure used for bit access 
        uint32_t  reg;                           // Type used for register access 
    } CCSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    FADDR      :32;         // bit: 0..31       (R) .          
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } MPFAR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UXE      :1;         // bit: 0        (R) .
            uint32_t    UWE      :1;         // bit: 1        (R) .
            uint32_t    URE      :1;         // bit: 2        (R) .
            uint32_t    SXE      :1;         // bit: 3        (R) .
            uint32_t    SWE      :1;         // bit: 4        (R) .
            uint32_t    SRE      :1;         // bit: 5        (R) .
            uint32_t             :1;         // bit: 6..8     Reserved. 
            uint32_t    FID      :4;         // bit: 9..12    (R) . 
            uint32_t             :19;        // bit: 13..31   Reserved.         
        } b;                                      // Structure used for bit access 
        uint32_t  reg;                            // Type used for register access 
    } MPFSR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    MPFCLR      :1;         // bit: 0       (W) .  
            uint32_t                :31;        // bit: 1..31   Reserved.         
        } b;                                    // Structure used for bit access 
        uint32_t  reg;                          // Type used for register access 
    } MPFCR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x676] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UX      :1;         // bit: 0        (RW) Bitfield description. 
            uint32_t    UW      :1;         // bit: 1        (RW) Bitfield description.
            uint32_t    UR      :1;         // bit: 2        (RW) Bitfield description.
            uint32_t    SX      :1;         // bit: 3        (RW) Bitfield description. 
            uint32_t    SW      :1;         // bit: 4        (RW) Bitfield description. 
            uint32_t    SR      :1;         // bit: 5        (RW) Bitfield description.
            uint32_t            :3;         // bit: 6..8     Reserved.
            uint32_t    EXT     :1;         // bit: 9        (RW) Bitfield description. 
            uint32_t    AIDm    :6;         // bit: 10..15   (RW) Bitfield description.
            uint32_t            :16;        // bit: 16..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } MPPAG_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x676] */ 
    typedef union 
    { 
        struct
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    UX      :1;         // bit: 0        (RW) Bitfield description. 
            uint32_t    UW      :1;         // bit: 1        (RW) Bitfield description.
            uint32_t    UR      :1;         // bit: 2        (RW) Bitfield description.
            uint32_t    SX      :1;         // bit: 3        (RW) Bitfield description. 
            uint32_t    SW      :1;         // bit: 4        (RW) Bitfield description. 
            uint32_t    SR      :1;         // bit: 5        (RW) Bitfield description.
            uint32_t            :3;         // bit: 6..8     Reserved.
            uint32_t    EXT     :1;         // bit: 9        (RW) Bitfield description. 
            uint32_t    AIDm    :6;         // bit: 10..15   (RW) Bitfield description.
            uint32_t            :16;        // bit: 16..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } MPPA_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ER_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ERH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } ESR_reg_t;
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ESRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (RW) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } CER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } CERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EER_reg_t;
    
        /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } EECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EESR_reg_t;
    
/*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31       (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } EESRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } SER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } SERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } SECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } SECRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In_      :32;        // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } IERH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IECR_reg_t;
  
/*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IECRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IESR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IESRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } IPR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (R) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } IPRH_reg_t;
    
     /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ICR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    In      :32;         // bit: 0..31        (W) .           
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access 
    } ICRH_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVAL      :1;         // bit: 0       (W) .  
            uint32_t              :31;        // bit: 1..31   Reserved.         
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access 
    } IEVAL_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEECR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QEESR_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (R) . 
            uint32_t            :24;        // bit: 8..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access 
    } QSER_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    En      :8;         // bit: 0..7     (W) . 
            uint32_t            :24;        // bit: 8..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } QSECR_reg_t;

/*******************************************************************************************************************************************************************************/  

/*************************************************************************** AM335x_EDMA3TC_Type Registers **********************************************************************/ 

/*******************************************************************************************************************************************************************************/
 
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PID      :16;   // bit: 0..15     (R) . 
            uint32_t             :16;   // bit: 16..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } PIDTC_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    FIFOSIZE       :3;   // bit: 0..2     (R) . 
            uint32_t                   :1;   // bit: 3        Reserved 
            uint32_t    BUSWIDTH       :2;   // bit: 4,5      (R) .
            uint32_t                   :2;   // bit: 6,7      Reserved 
            uint32_t    DREGDEPTH      :2;   // bit: 8,9      (R) .
            uint32_t                   :22;  // bit: 10..31   Reserved.          
        } b;                                 // Structure used for bit access 
        uint32_t  reg;                       // Type used for register access
    } TCCFG_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t                  :2;   // bit: 0,1      Reserved.   
            uint32_t    IDLEMODE      :2;   // bit: 2,3      (RW) .
            uint32_t    STANDBYMODE   :2;   // bit: 4,5      (RW) .
            uint32_t                  :26;  // bit: 6..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SYSCONFIGTC_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PROGBUSY      :1;   // bit: 0        (R) . 
            uint32_t    SRCACTV       :1;   // bit: 1        (R) .
            uint32_t    WSACTV        :1;   // bit: 2        (R) .
            uint32_t                  :1;   // bit: 3        Reserved.
            uint32_t    DSTACTV       :3;   // bit: 4..6     (R) .
            uint32_t                  :1;   // bit: 7..11    Reserved.
            uint32_t    DFSTRTPTR     :1;   // bit: 12,13    (R) .
            uint32_t                  :18;  // bit: 14..31   Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } TCSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (R) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (R) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (R) .
            uint32_t                :28;  // bit: 4..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } ERRSTAT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (RW) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (RW) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (RW) .
            uint32_t                :28;  // bit: 4..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } ERREN_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    BUSERR      :1;   // bit: 0        (W) .
            uint32_t                :1;   // bit: 1        Reserved. 
            uint32_t    TRERR       :1;   // bit: 2        (W) . 
            uint32_t    MMRAERR     :1;   // bit: 3        (W) . 
            uint32_t                :28;  // bit: 4..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } ERRCLR_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    STAT      :4;   // bit: 0..3      (R) .
            uint32_t              :4;   // bit: 4..7      Reserved.
            uint32_t    TCC       :6;   // bit: 8..13     (R) .
            uint32_t              :2;   // bit: 14,15     Reserved.
            uint32_t    TCINTEN   :1;   // bit: 16        (R) .
            uint32_t    TCCHEN    :1;   // bit: 17        (R) .
            uint32_t              :14;  // bit: 18..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } ERRDET_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    EVAL      :1;   // bit: 0        (W) . 
            uint32_t              :31;  // bit: 1..31    Reserved.          
        } b;                            // Structure used for bit access 
        uint32_t  reg;                  // Type used for register access
    } ERRCMD_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    RDRATE      :3;   // bit: 0..2        (W) . 
            uint32_t                :29;  // bit: 3..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } RDRATE_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SAOPT_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SADDR      :32;   // bit: 0..31       (R) .         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SASRC_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15       (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31      (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } SACNT_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t  R_BITFIELD       :32;  // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SADST_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } SABIDX_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SAMPPRXY_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNTRLD      :16;   // bit: 0        (R) . 
            uint32_t                 :16;   // bit: 1..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SACNTRLD_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SADDRBREF      :32;   // bit: 0..31        (R) .           
        } b;                                  // Structure used for bit access 
        uint32_t  reg;                        // Type used for register access
    } SASRCBREF_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t   R_BITFIELD      :32;  // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } SADSTBREF_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNTRLD      :16;   // bit: 0..15     (R) .
            uint32_t                 :16;   // bit: 16..31    Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFCNTRLD_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/ 
            uint32_t   R_BITFIELD    :32;    // bit: 0..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRCBREF_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t   DADDRBREF  :32;   // bit: 0..31        (R) .           
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFDSTBREF_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFOPT0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD    :32;  // bit: 0..32       (R) .         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;   // bit: 0..31        (W) .           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFDST0_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;  // bit: 0..15     (R) . 
            uint32_t    DBIDX      :16;  // bit: 16..31    (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFBIDX0_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY0_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFOPT1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD      :32;   // bit: 0..31        Reserved.           
        } b;                                   // Structure used for bit access 
        uint32_t  reg;                         // Type used for register access
    } DFSRC1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFCNT1_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;   // bit: 0..31       (R) .        
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFDST1_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .         
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFBIDX1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {   /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY1_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.           
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFOPT2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD   :32;   // bit: 0..31       Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC2_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT2_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;  // bit: 0..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFDST2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFBIDX2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFMPPRXY2_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SAM         :1;   // bit: 0        (R) . 
            uint32_t    DAM         :1;   // bit: 1        (R) .
            uint32_t                :2;   // bit: 2,3      Reserved.
            uint32_t    PRI         :3;   // bit: 4..6     (R) .
            uint32_t                :1;   // bit: 7        Reserved.
            uint32_t    FWID        :3;   // bit: 8..10    (R) .
            uint32_t                :1;   // bit: 11       Reserved.
            uint32_t    TCC         :6;   // bit: 12..17   (R) .
            uint32_t                :2;   // bit: 18,19    Reserved.
            uint32_t    TCINTEN     :1;   // bit: 20       (R) .
            uint32_t                :1;   // bit: 21       Reserved.
            uint32_t    TCCHEN      :1;   // bit: 22       (R) .
            uint32_t                :9;   // bit: 23..31   Reserved.         
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFOPT3_reg_t; 

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    R_BITFIELD   :32;   // bit: 0..31       Reserved.          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFSRC3_reg_t;

    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    ACNT      :16;   // bit: 0..15        (R) . 
            uint32_t    BCNT      :16;   // bit: 16..31       (R) .          
        } b;                             // Structure used for bit access 
        uint32_t  reg;                   // Type used for register access
    } DFCNT3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    DADDR      :32;     // bit: 0        (R) .          
        } b;                                // Structure used for bit access 
        uint32_t  reg;                      // Type used for register access
    } DFDST3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    SBIDX      :16;   // bit: 0..15       (R) . 
            uint32_t    DBIDX      :16;   // bit: 16..31      (R) .         
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFBIDX3_reg_t;
    
    /*! @brief      __XXX__  
    *   @details    __XXX__
    *               __XXX__
    *               __XXX__
    [reset state = 0x0] */ 
    typedef union 
    { 
        struct 
        {  /**  Register not described!!! Describe yoursef using am335x_reference_manual **/
            uint32_t    PRIVID      :4;   // bit: 0..3     (R) . 
            uint32_t                :4;   // bit: 4..7     Reserved.
            uint32_t    PRIV        :1;   // bit: 8        (R) .
            uint32_t                :23;  // bit: 9..31    Reserved.          
        } b;                              // Structure used for bit access 
        uint32_t  reg;                    // Type used for register access
    } DFMPPRXY3_reg_t;
    
    struct AM335x_EDMA3CC_Type
    {                                                                                      
        __R   PIDCC_reg_t       PID;            // (0x00)  Peripheral Identification Register
        __R   CCCFG_reg_t       CCCFG;          // (0x04)  EDMA3CC Configuration Register
        __R   uint32_t          RESERVED1[2];
        __RW  SYSCONFIGCC_reg_t   SYSCONFIG;    // (0x10)  EDMA3CC System Configuration Register
        __R   uint32_t          RESERVED2[59]; 
        __RW  DCHMAP_reg_t      DCHMAP_0;       // (0x100) DMA Channel Mapping Register 0
        __RW  DCHMAP_reg_t      DCHMAP_1;       // (0x104) DMA Channel Mapping Register 1
        __RW  DCHMAP_reg_t      DCHMAP_2;       // (0x108) DMA Channel Mapping Register 2
        __RW  DCHMAP_reg_t      DCHMAP_3;       // (0x10C) DMA Channel Mapping Register 3
        __RW  DCHMAP_reg_t      DCHMAP_4;       // (0x110) DMA Channel Mapping Register 4
        __RW  DCHMAP_reg_t      DCHMAP_5;       // (0x114) DMA Channel Mapping Register 5
        __RW  DCHMAP_reg_t      DCHMAP_6;       // (0x118) DMA Channel Mapping Register 6
        __RW  DCHMAP_reg_t      DCHMAP_7;       // (0x11C) DMA Channel Mapping Register 7
        __RW  DCHMAP_reg_t      DCHMAP_8;       // (0x120) DMA Channel Mapping Register 8 
        __RW  DCHMAP_reg_t      DCHMAP_9;       // (0x124) DMA Channel Mapping Register 9
        __RW  DCHMAP_reg_t      DCHMAP_10;      // (0x128) DMA Channel Mapping Register 10
        __RW  DCHMAP_reg_t      DCHMAP_11;      // (0x12C) DMA Channel Mapping Register 11
        __RW  DCHMAP_reg_t      DCHMAP_12;      // (0x130) DMA Channel Mapping Register 12
        __RW  DCHMAP_reg_t      DCHMAP_13;      // (0x134) DMA Channel Mapping Register 13
        __RW  DCHMAP_reg_t      DCHMAP_14;      // (0x138) DMA Channel Mapping Register 14
        __RW  DCHMAP_reg_t      DCHMAP_15;      // (0x13C) DMA Channel Mapping Register 15
        __RW  DCHMAP_reg_t      DCHMAP_16;      // (0x140) DMA Channel Mapping Register 16 
        __RW  DCHMAP_reg_t      DCHMAP_17;      // (0x144) DMA Channel Mapping Register 17
        __RW  DCHMAP_reg_t      DCHMAP_18;      // (0x148) DMA Channel Mapping Register 18
        __RW  DCHMAP_reg_t      DCHMAP_19;      // (0x14C) DMA Channel Mapping Register 19
        __RW  DCHMAP_reg_t      DCHMAP_20;      // (0x150) DMA Channel Mapping Register 20
        __RW  DCHMAP_reg_t      DCHMAP_21;      // (0x154) DMA Channel Mapping Register 21
        __RW  DCHMAP_reg_t      DCHMAP_22;      // (0x158) DMA Channel Mapping Register 22
        __RW  DCHMAP_reg_t      DCHMAP_23;      // (0x15C) DMA Channel Mapping Register 23
        __RW  DCHMAP_reg_t      DCHMAP_24;      // (0x160) DMA Channel Mapping Register 24
        __RW  DCHMAP_reg_t      DCHMAP_25;      // (0x164) DMA Channel Mapping Register 25
        __RW  DCHMAP_reg_t      DCHMAP_26;      // (0x168) DMA Channel Mapping Register 26
        __RW  DCHMAP_reg_t      DCHMAP_27;      // (0x16C) DMA Channel Mapping Register 27
        __RW  DCHMAP_reg_t      DCHMAP_28;      // (0x170) DMA Channel Mapping Register 28
        __RW  DCHMAP_reg_t      DCHMAP_29;      // (0x174) DMA Channel Mapping Register 29
        __RW  DCHMAP_reg_t      DCHMAP_30;      // (0x178) DMA Channel Mapping Register 30
        __RW  DCHMAP_reg_t      DCHMAP_31;      // (0x17C) DMA Channel Mapping Register 31
        __RW  DCHMAP_reg_t      DCHMAP_32;      // (0x180) DMA Channel Mapping Register 32
        __RW  DCHMAP_reg_t      DCHMAP_33;      // (0x184) DMA Channel Mapping Register 33
        __RW  DCHMAP_reg_t      DCHMAP_34;      // (0x188) DMA Channel Mapping Register 34
        __RW  DCHMAP_reg_t      DCHMAP_35;      // (0x18C) DMA Channel Mapping Register 35
        __RW  DCHMAP_reg_t      DCHMAP_36;      // (0x190) DMA Channel Mapping Register 36
        __RW  DCHMAP_reg_t      DCHMAP_37;      // (0x194) DMA Channel Mapping Register 37
        __RW  DCHMAP_reg_t      DCHMAP_38;      // (0x198) DMA Channel Mapping Register 38
        __RW  DCHMAP_reg_t      DCHMAP_39;      // (0x19C) DMA Channel Mapping Register 39
        __RW  DCHMAP_reg_t      DCHMAP_40;      // (0x1A0) DMA Channel Mapping Register 40 
        __RW  DCHMAP_reg_t      DCHMAP_41;      // (0x1A4) DMA Channel Mapping Register 41
        __RW  DCHMAP_reg_t      DCHMAP_42;      // (0x1A8) DMA Channel Mapping Register 42
        __RW  DCHMAP_reg_t      DCHMAP_43;      // (0x1AC) DMA Channel Mapping Register 43
        __RW  DCHMAP_reg_t      DCHMAP_44;      // (0x1B0) DMA Channel Mapping Register 44
        __RW  DCHMAP_reg_t      DCHMAP_45;      // (0x1B4) DMA Channel Mapping Register 45
        __RW  DCHMAP_reg_t      DCHMAP_46;      // (0x1B8) DMA Channel Mapping Register 46
        __RW  DCHMAP_reg_t      DCHMAP_47;      // (0x1BC) DMA Channel Mapping Register 47
        __RW  DCHMAP_reg_t      DCHMAP_48;      // (0x1C0) DMA Channel Mapping Register 48 
        __RW  DCHMAP_reg_t      DCHMAP_49;      // (0x1C4) DMA Channel Mapping Register 49
        __RW  DCHMAP_reg_t      DCHMAP_50;      // (0x1C8) DMA Channel Mapping Register 50
        __RW  DCHMAP_reg_t      DCHMAP_51;      // (0x1CC) DMA Channel Mapping Register 51
        __RW  DCHMAP_reg_t      DCHMAP_52;      // (0x1D0) DMA Channel Mapping Register 52
        __RW  DCHMAP_reg_t      DCHMAP_53;      // (0x1D4) DMA Channel Mapping Register 53
        __RW  DCHMAP_reg_t      DCHMAP_54;      // (0x1D8) DMA Channel Mapping Register 54
        __RW  DCHMAP_reg_t      DCHMAP_55;      // (0x1DC) DMA Channel Mapping Register 55
        __RW  DCHMAP_reg_t      DCHMAP_56;      // (0x1E0) DMA Channel Mapping Register 56
        __RW  DCHMAP_reg_t      DCHMAP_57;      // (0x1E4) DMA Channel Mapping Register 57
        __RW  DCHMAP_reg_t      DCHMAP_58;      // (0x1E8) DMA Channel Mapping Register 58
        __RW  DCHMAP_reg_t      DCHMAP_59;      // (0x1EC) DMA Channel Mapping Register 59
        __RW  DCHMAP_reg_t      DCHMAP_60;      // (0x1F0) DMA Channel Mapping Register 60
        __RW  DCHMAP_reg_t      DCHMAP_61;      // (0x1F4) DMA Channel Mapping Register 61
        __RW  DCHMAP_reg_t      DCHMAP_62;      // (0x1F8) DMA Channel Mapping Register 62
        __RW  DCHMAP_reg_t      DCHMAP_63;      // (0x1FC) DMA Channel Mapping Register 63
        __RW  QCHMAP_reg_t      QCHMAP_0;       // (0x200) QDMA Channel Mapping Register 0
        __RW  QCHMAP_reg_t      QCHMAP_1;       // (0x204) QDMA Channel Mapping Register 1
        __RW  QCHMAP_reg_t      QCHMAP_2;       // (0x208) QDMA Channel Mapping Register 2
        __RW  QCHMAP_reg_t      QCHMAP_3;       // (0x20C) QDMA Channel Mapping Register 3
        __RW  QCHMAP_reg_t      QCHMAP_4;       // (0x210) QDMA Channel Mapping Register 4
        __RW  QCHMAP_reg_t      QCHMAP_5;       // (0x214) QDMA Channel Mapping Register 5
        __RW  QCHMAP_reg_t      QCHMAP_6;       // (0x218) QDMA Channel Mapping Register 6
        __RW  QCHMAP_reg_t      QCHMAP_7;       // (0x21C) QDMA Channel Mapping Register 7
        __R   uint32_t          RESERVED3[8]; 
        __RW  DMAQNUM_reg_t     DMAQNUM_0;      // (0x240) DMA Queue Number Register 0
        __RW  DMAQNUM_reg_t     DMAQNUM_1;      // (0x244) DMA Queue Number Register 1
        __RW  DMAQNUM_reg_t     DMAQNUM_2;      // (0x248) DMA Queue Number Register 2
        __RW  DMAQNUM_reg_t     DMAQNUM_3;      // (0x24C) DMA Queue Number Register 3
        __RW  DMAQNUM_reg_t     DMAQNUM_4;      // (0x250) DMA Queue Number Register 4
        __RW  DMAQNUM_reg_t     DMAQNUM_5;      // (0x254) DMA Queue Number Register 5
        __RW  DMAQNUM_reg_t     DMAQNUM_6;      // (0x258) DMA Queue Number Register 6
        __RW  DMAQNUM_reg_t     DMAQNUM_7;      // (0x25C) DMA Queue Number Register 7
        __RW  QDMAQNUM_reg_t    QDMAQNUM;       // (0x260) QDMA Queue Number Register
        __R   uint32_t          RESERVED4[8];  
        __RW  QUEPRI_reg_t      QUEPRI;         // (0x284) Queue Priority Register
        __R   uint32_t          RESERVED5[30]; 
        __R   EMR_reg_t         EMR;            // (0x300) Event Missed Register
        __R   EMRH_reg_t        EMRH;           // (0x304) Event Missed Register High 
        __W   EMCR_reg_t        EMCR;           // (0x308) Event Missed Clear Register
        __W   EMCRH_reg_t       EMCRH;          // (0x30C) Event Missed Clear Register High 
        __R   QEMR_reg_t        QEMR;           // (0x310) QDMA Event Missed Register 
        __W   QEMCR_reg_t       QEMCR;          // (0x314) QDMA Event Missed Clear Register 
        __R   CCERR_reg_t       CCERR;          // (0x318) EDMA3CC Error Register 
        __W   CCERRCLR_reg_t    CCERRCLR;       // (0x31C) EDMA3CC Error Clear Register 
        __R   EEVAL_reg_t       EEVAL;          // (0x320) Error Evaluate Register
        __R   uint32_t          RESERVED6[7]; 
        __RW  DRAE0_reg_t       DRAE0;          // (0x340) DMA Region Access Enable Register for Region 0    
        __RW  DRAEH0_reg_t      DRAEH0;         // (0x344) DMA Region Access Enable Register High for Region 0 
        __RW  DRAE1_reg_t       DRAE1;          // (0x348) DMA Region Access Enable Register for Region 1 
        __RW  DRAEH1_reg_t      DRAEH1;         // (0x34C) DMA Region Access Enable Register High for Region 1
        __RW  DRAE2_reg_t       DRAE2;          // (0x350) DMA Region Access Enable Register for Region 2
        __RW  DRAEH2_reg_t      DRAEH2;         // (0x354) DMA Region Access Enable Register High for Region 2  
        __RW  DRAE3_reg_t       DRAE3;          // (0x358) DMA Region Access Enable Register for Region 3
        __RW  DRAEH3_reg_t      DRAEH3;         // (0x35C) DMA Region Access Enable Register High for Region 3
        __RW  DRAE4_reg_t       DRAE4;          // (0x360) DMA Region Access Enable Register for Region 4 
        __RW  DRAEH4_reg_t      DRAEH4;         // (0x364) DMA Region Access Enable Register High for Region 4
        __RW  DRAE5_reg_t       DRAE5;          // (0x368) DMA Region Access Enable Register for Region 5 
        __RW  DRAEH5_reg_t      DRAEH5;         // (0x36C) DMA Region Access Enable Register High for Region 5 
        __RW  DRAE6_reg_t       DRAE6;          // (0x370) DMA Region Access Enable Register for Region 6
        __RW  DRAEH6_reg_t      DRAEH6;         // (0x374) DMA Region Access Enable Register High for Region 6
        __RW  DRAE7_reg_t       DRAE7;          // (0x378) DMA Region Access Enable Register for Region 7
        __RW  DRAEH7_reg_t      DRAEH7;         // (0x37C) DMA Region Access Enable Register High for Region 7
        __RW  QRAE_reg_t        QRAE_0;         // (0x380) QDMA Region Access Enable Registers for Region 0
        __RW  QRAE_reg_t        QRAE_1;         // (0x384) QDMA Region Access Enable Registers for Region 1 
        __RW  QRAE_reg_t        QRAE_2;         // (0x388) QDMA Region Access Enable Registers for Region 2
        __RW  QRAE_reg_t        QRAE_3;         // (0x38Ñ) QDMA Region Access Enable Registers for Region 3  
        __RW  QRAE_reg_t        QRAE_4;         // (0x390) QDMA Region Access Enable Registers for Region 4
        __RW  QRAE_reg_t        QRAE_5;         // (0x394) QDMA Region Access Enable Registers for Region 5
        __RW  QRAE_reg_t        QRAE_6;         // (0x398) QDMA Region Access Enable Registers for Region 6
        __RW  QRAE_reg_t        QRAE_7;         // (0x39Ñ) QDMA Region Access Enable Registers for Region 7
        __R   uint32_t          RESERVED7[24];  
        __R   QE_reg_t          Q0E0;           // (0x400) Event Queue 0 Entry 0 Register 
        __R   QE_reg_t          Q0E1;           // (0x404) Event Queue 0 Entry 1 Register 
        __R   QE_reg_t          Q0E2;           // (0x408) Event Queue 0 Entry 2 Register 
        __R   QE_reg_t          Q0E3;           // (0x40C) Event Queue 0 Entry 3 Register 
        __R   QE_reg_t          Q0E4;           // (0x410) Event Queue 0 Entry 4 Register 
        __R   QE_reg_t          Q0E5;           // (0x414) Event Queue 0 Entry 5 Register 
        __R   QE_reg_t          Q0E6;           // (0x418) Event Queue 0 Entry 6 Register
        __R   QE_reg_t          Q0E7;           // (0x41C) Event Queue 0 Entry 7 Register 
        __R   QE_reg_t          Q0E8;           // (0x420) Event Queue 0 Entry 8 Register 
        __R   QE_reg_t          Q0E9;           // (0x424) Event Queue 0 Entry 9 Register 
        __R   QE_reg_t          Q0E10;          // (0x428) Event Queue 0 Entry 10 Register 
        __R   QE_reg_t          Q0E11;          // (0x42C) Event Queue 0 Entry 11 Register
        __R   QE_reg_t          Q0E12;          // (0x430) Event Queue 0 Entry 12 Register 
        __R   QE_reg_t          Q0E13;          // (0x434) Event Queue 0 Entry 13 Register
        __R   QE_reg_t          Q0E14;          // (0x438) Event Queue 0 Entry 14 Register 
        __R   QE_reg_t          Q0E15;          // (0x43C) Event Queue 0 Entry 15 Register 
        __R   QE_reg_t          Q1E0;           // (0x440) Event Queue 1 Entry 0 Register   
        __R   QE_reg_t          Q1E1;           // (0x444) Event Queue 1 Entry 1 Register   
        __R   QE_reg_t          Q1E2;           // (0x448) Event Queue 1 Entry 2 Register   
        __R   QE_reg_t          Q1E3;           // (0x44C) Event Queue 1 Entry 3 Register   
        __R   QE_reg_t          Q1E4;           // (0x450) Event Queue 1 Entry 4 Register  
        __R   QE_reg_t          Q1E5;           // (0x454) Event Queue 1 Entry 5 Register   
        __R   QE_reg_t          Q1E6;           // (0x458) Event Queue 1 Entry 6 Register  
        __R   QE_reg_t          Q1E7;           // (0x45C) Event Queue 1 Entry 7 Register   
        __R   QE_reg_t          Q1E8;           // (0x460) Event Queue 1 Entry 8 Register   
        __R   QE_reg_t          Q1E9;           // (0x464) Event Queue 1 Entry 9 Register   
        __R   QE_reg_t          Q1E10;          // (0x468) Event Queue 1 Entry 10 Register  
        __R   QE_reg_t          Q1E11;          // (0x46C) Event Queue 1 Entry 11 Register 
        __R   QE_reg_t          Q1E12;          // (0x470) Event Queue 1 Entry 12 Register  
        __R   QE_reg_t          Q1E13;          // (0x474) Event Queue 1 Entry 13 Register  
        __R   QE_reg_t          Q1E14;          // (0x478) Event Queue 1 Entry 14 Register  
        __R   QE_reg_t          Q1E15;          // (0x47C) Event Queue 1 Entry 15 Register  
        __R   QE_reg_t          Q2E0;           // (0x480) Event Queue 2 Entry 0 Register   
        __R   QE_reg_t          Q2E1;           // (0x484) Event Queue 2 Entry 1 Register   
        __R   QE_reg_t          Q2E2;           // (0x488) Event Queue 2 Entry 2 Register  
        __R   QE_reg_t          Q2E3;           // (0x48C) Event Queue 2 Entry 3 Register   
        __R   QE_reg_t          Q2E4;           // (0x490) Event Queue 2 Entry 4 Register   
        __R   QE_reg_t          Q2E5;           // (0x494) Event Queue 2 Entry 5 Register   
        __R   QE_reg_t          Q2E6;           // (0x498) Event Queue 2 Entry 6 Register  
        __R   QE_reg_t          Q2E7;           // (0x49C) Event Queue 2 Entry 7 Register   
        __R   QE_reg_t          Q2E8;           // (0x4A0) Event Queue 2 Entry 8 Register   
        __R   QE_reg_t          Q2E9;           // (0x4A4) Event Queue 2 Entry 9 Register  
        __R   QE_reg_t          Q2E10;          // (0x4A8) Event Queue 2 Entry 10 Register  
        __R   QE_reg_t          Q2E11;          // (0x4AC) Event Queue 2 Entry 11 Register  
        __R   QE_reg_t          Q2E12;          // (0x4B0) Event Queue 2 Entry 12 Register 
        __R   QE_reg_t          Q2E13;          // (0x4B4) Event Queue 2 Entry 13 Register  
        __R   QE_reg_t          Q2E14;          // (0x4B8) Event Queue 2 Entry 14 Register  
        __R   QE_reg_t          Q2E15;          // (0x4BC) Event Queue 2 Entry 15 Register 
        __R   uint32_t          RESERVED8[80]; 
        __R   QSTAT_reg_t       QSTAT_0;        // (0x600) Queue Status Registers 0
        __R   QSTAT_reg_t       QSTAT_1;        // (0x604) Queue Status Registers 1 
        __R   QSTAT_reg_t       QSTAT_2;        // (0x608) Queue Status Registers 2
        __R   uint32_t          RESERVED9[5]; 
        __RW  QWMTHRA_reg_t     QWMTHRA;        // (0x620) Queue Watermark Threshold A Register
        __R   uint32_t          RESERVED10[7]; 
        __R   CCSTAT_reg_t      CCSTAT;         // (0x640) EDMA3CC Status Register
        __R   uint32_t          RESERVED11[111]; 
        __R   MPFAR_reg_t       MPFAR;          // (0x800) Memory Protection Fault Address Register
        __R   MPFSR_reg_t       MPFSR;          // (0x804) Memory Protection Fault Status Register
        __W   MPFCR_reg_t       MPFCR;          // (0x808) Memory Protection Fault Command Register 
        __RW  MPPAG_reg_t       MPPAG;          // (0x80C) Memory Protection Page Attribute Register Global 
        __RW  MPPA_reg_t        MPPA_0;         // (0x810) Memory Protection Page Attribute Register 0
        __RW  MPPA_reg_t        MPPA_1;         // (0x814) Memory Protection Page Attribute Register 1
        __RW  MPPA_reg_t        MPPA_2;         // (0x818) Memory Protection Page Attribute Register 2 
        __RW  MPPA_reg_t        MPPA_3;         // (0x81C) Memory Protection Page Attribute Register 3 
        __RW  MPPA_reg_t        MPPA_4;         // (0x820) Memory Protection Page Attribute Register 4
        __RW  MPPA_reg_t        MPPA_5;         // (0x824) Memory Protection Page Attribute Register 5 
        __RW  MPPA_reg_t        MPPA_6;         // (0x828) Memory Protection Page Attribute Register 6
        __RW  MPPA_reg_t        MPPA_7;         // (0x82C) Memory Protection Page Attribute Register 7
        __R   uint32_t          RESERVED12[500]; 
        __R   ER_reg_t          ER;             // (0x1000) Event Register  
        __R   ERH_reg_t         ERH;            // (0x1004) Event Register High 
        __W   ECR_reg_t         ECR;            // (0x1008) Event Clear Register 
        __W   ECRH_reg_t        ECRH;           // (0x100C) Event Clear Register High 
        __RW  ESR_reg_t         ESR;            // (0x1010) Event Set Register 
        __RW  ESRH_reg_t        ESRH;           // (0x1014) Event Set Register High 
        __R   CER_reg_t         CER;            // (0x1018) Chained Event Register  
        __R   CERH_reg_t        CERH;           // (0x101C) Chained Event Register High 
        __R   EER_reg_t         EER;            // (0x1020) Event Enable Register
        __R   EERH_reg_t        EERH;           // (0x1024) Event Enable Register High 
        __W   EECR_reg_t        EECR;           // (0x1028) Event Enable Clear Register  
        __W   EECRH_reg_t       EECRH;          // (0x102C) Event Enable Clear Register High 
        __W   EESR_reg_t        EESR;           // (0x1030) Event Enable Set Register 
        __W   EESRH_reg_t       EESRH;          // (0x1034) Event Enable Set Register High
        __R   SER_reg_t         SER;            // (0x1038) Secondary Event Register 
        __R   SERH_reg_t        SERH;           // (0x103C) Secondary Event Register High 
        __W   SECR_reg_t        SECR;           // (0x1040) Secondary Event Clear Register 
        __W   SECRH_reg_t       SECRH;          // (0x1044) Secondary Event Clear Register High
        __R   uint32_t          RESERVED13[2]; 
        __R   IER_reg_t         IER;            // (0x1050) Interrupt Enable Register
        __R   IERH_reg_t        IERH;           // (0x1054) Interrupt Enable Register High 
        __W   IECR_reg_t        IECR;           // (0x1058) Interrupt Enable Clear Register
        __W   IECRH_reg_t       IECRH;          // (0x105C) Interrupt Enable Clear Register High  
        __W   IESR_reg_t        IESR;           // (0x1060) Interrupt Enable Set Register 
        __W   IESRH_reg_t       IESRH;          // (0x1064) Interrupt Enable Set Register High 
        __R   IPR_reg_t         IPR;            // (0x1068) Interrupt Pending Register 
        __R   IPRH_reg_t        IPRH;           // (0x106C) Interrupt Pending Register High 
        __W   ICR_reg_t         ICR;            // (0x1070) Interrupt Clear Register 
        __W   ICRH_reg_t        ICRH;           // (0x1074) Interrupt Clear Register High
        __W   IEVAL_reg_t       IEVAL;          // (0x1078) Interrupt Evaluate Register
        __R   uint32_t          RESERVED14[1]; 
        __R   QER_reg_t         QER;            // (0x1080) QDMA Event Register 
        __R   QEER_reg_t        QEER;           // (0x1084) QDMA Event Enable Register
        __W   QEECR_reg_t       QEECR;          // (0x1088) QDMA Event Enable Clear Register 
        __W   QEESR_reg_t       QEESR;          // (0x108C) QDMA Event Enable Set Register  
        __R   QSER_reg_t        QSER;           // (0x1090) QDMA Secondary Event Register 
        __W   QSECR_reg_t       QSECR;          // (0x1094) QDMA Secondary Event Clear Register
    };

    struct AM335x_EDMA3TC_Type
    {                                                                                      
        __R   PIDTC_reg_t         PID;                // (0x00)   Peripheral Identification Register
        __R   TCCFG_reg_t         TCCFG;              // (0x04)   EDMA3TC Configuration Register
        __R   uint32_t            RESERVED1[2];
        __RW  SYSCONFIGTC_reg_t   SYSCONFIG;          // (0x10)   EDMA3TC System Configuration Register  
        __R   uint32_t            RESERVED2[59];
        __R   TCSTAT_reg_t        TCSTAT;             // (0x100)  EDMA3TC Channel Status Register
        __R   uint32_t            RESERVED3[7];  
        __R   ERRSTAT_reg_t       ERRSTAT;            // (0x120)  Error Register 
        __RW  ERREN_reg_t         ERREN;              // (0x124)  Error Enable Register 
        __W   ERRCLR_reg_t        ERRCLR;             // (0x128)  Error Clear Register 
        __R   ERRDET_reg_t        ERRDET;             // (0x12C)  Error Details Register 
        __W   ERRCMD_reg_t        ERRCMD;             // (0x130)  Error Interrupt Command Register 
        __R   uint32_t            RESERVED4[3]; 
        __RW  RDRATE_reg_t        RDRATE;             // (0x140)  Read Rate Register
        __R   uint32_t            RESERVED5[63];
        __R   SAOPT_reg_t         SAOPT;              // (0x240)  Source Active Options Register 
        __R   SASRC_reg_t         SASRC;              // (0x244)  Source Active Source Address Register
        __R   SACNT_reg_t         SACNT;              // (0x248)  Source Active Count Register  
        __R   SADST_reg_t         SADST;              // (0x24C)  Source Active Destination Address Register 
        __R   SABIDX_reg_t        SABIDX;             // (0x250)  Source Active Source B-Index Register
        __R   SAMPPRXY_reg_t      SAMPPRXY;           // (0x254)  Source Active Memory Protection Proxy Register  
        __R   SACNTRLD_reg_t      SACNTRLD;           // (0x258)  Source Active Count Reload Register
        __R   SASRCBREF_reg_t     SASRCBREF;          // (0x25C)  Source Active Source Address B-Reference Register 
        __R   SADSTBREF_reg_t     SADSTBREF;          // (0x260)  Source Active Destination Address B-Reference Register
        __R   uint32_t            RESERVED6[7];
        __R   DFCNTRLD_reg_t      DFCNTRLD;           // (0x280)  Destination FIFO Set Count Reload
        __R   DFSRCBREF_reg_t     DFSRCBREF;          // (0x284)  Destination FIFO Set Destination Address B Reference Register
        __R   DFDSTBREF_reg_t     DFDSTBREF;          // (0x288)  Destination FIFO Set Destination Address B Reference Register
        __R   uint32_t            RESERVED7[29];
        __R   DFOPT0_reg_t        DFOPT0;             // (0x300)  Destination FIFO Options Register 0
        __R   DFSRC0_reg_t        DFSRC0;             // (0x304)  Destination FIFO Source Address Register 0
        __R   DFCNT0_reg_t        DFCNT0;             // (0x308)  Destination FIFO Count Register 0
        __R   DFDST0_reg_t        DFDST0;             // (0x30C)  Destination FIFO Destination Address Register 0
        __R   DFBIDX0_reg_t       DFBIDX0;            // (0x310)  Destination FIFO BIDX Register 0
        __R   DFMPPRXY0_reg_t     DFMPPRXY0;          // (0x314)  Destination FIFO Memory Protection Proxy Register 0
        __R   uint32_t            RESERVED8[10];
        __R   DFOPT1_reg_t        DFOPT1;             // (0x340)  Destination FIFO Options Register 1
        __R   DFSRC1_reg_t        DFSRC1;             // (0x344)  Destination FIFO Source Address Register 1
        __R   DFCNT1_reg_t        DFCNT1;             // (0x348)  Destination FIFO Count Register 1
        __R   DFDST1_reg_t        DFDST1;             // (0x34C)  Destination FIFO Destination Address Register 1
        __R   DFBIDX1_reg_t       DFBIDX1;            // (0x350)  Destination FIFO BIDX Register 1
        __R   DFMPPRXY1_reg_t     DFMPPRXY1;          // (0x354)  Destination FIFO Memory Protection Proxy Register 1
        __R   uint32_t            RESERVED9[10];
        __R   DFOPT2_reg_t        DFOPT2;             // (0x380)  Destination FIFO Options Register 2
        __R   DFSRC2_reg_t        DFSRC2;             // (0x384)  Destination FIFO Source Address Register 2
        __R   DFCNT2_reg_t        DFCNT2;             // (0x388)  Destination FIFO Count Register 2
        __R   DFDST2_reg_t        DFDST2;             // (0x38C)  Destination FIFO Destination Address Register 2
        __R   DFBIDX2_reg_t       DFBIDX2;            // (0x390)  Destination FIFO BIDX Register 2
        __R   DFMPPRXY2_reg_t     DFMPPRXY2;          // (0x394)  Destination FIFO Memory Protection Proxy Register 2
        __R   uint32_t            RESERVED10[10];
        __R   DFOPT3_reg_t        DFOPT3;             // (0x3C0)  Destination FIFO Options Register 3
        __R   DFSRC3_reg_t        DFSRC3;             // (0x3C4)  Destination FIFO Source Address Register 3
        __R   DFCNT3_reg_t        DFCNT3;             // (0x3C8)  Destination FIFO Count Register 3
        __R   DFDST3_reg_t        DFDST3;             // (0x3CC)  Destination FIFO Destination Address Register 3
        __R   DFBIDX3_reg_t       DFBIDX3;            // (0x3D0)  Destination FIFO BIDX Register 3
        __R   DFMPPRXY3_reg_t     DFMPPRXY3;          // (0x3D4)  Destination FIFO Memory Protection Proxy Register 3 
    };

    constexpr uint32_t AM335x_EDMA3CC_BASE     = 0x49000000;   
    constexpr uint32_t AM335x_EDMA3TC0_BASE    = 0x49800000;
    constexpr uint32_t AM335x_EDMA3TC1_BASE    = 0x49900000;
    constexpr uint32_t AM335x_EDMA3TC2_BASE    = 0x49A00000;

    constexpr AM335x_EDMA3CC_Type * AM335X_EDMA3CC_regs  = reinterpret_cast<AM335x_EDMA3CC_Type *>(AM335x_EDMA3CC_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC0_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC0_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC1_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC1_BASE);
    constexpr AM335x_EDMA3TC_Type * AM335X_EDMA3TC2_regs = reinterpret_cast<AM335x_EDMA3TC_Type *>(AM335x_EDMA3TC2_BASE);
}

/**
 * \brief EDMA3 Parameter RAM Set in User Configurable format
 *
 * This is a mapping of the EDMA3 PaRAM set provided to the user
 * for ease of modification of the individual fields
 */
typedef struct EDMA3CCPaRAMEntry {
        /** OPT field of PaRAM Set */
        unsigned int opt;

        /**
         * \brief Starting byte address of Source
         * For FIFO mode, srcAddr must be a 256-bit aligned address.
         */
        unsigned int srcAddr;

        /**
         * \brief Number of bytes in each Array (ACNT)
         */
        unsigned short aCnt;

        /**
         * \brief Number of Arrays in each Frame (BCNT)
         */
        unsigned short bCnt;

        /**
         * \brief Starting byte address of destination
         * For FIFO mode, destAddr must be a 256-bit aligned address.
         * i.e. 5 LSBs should be 0.
         */
        unsigned int destAddr;

        /**
         * \brief Index between consec. arrays of a Source Frame (SRCBIDX)
         */
        short  srcBIdx;

        /**
         * \brief Index between consec. arrays of a Destination Frame (DSTBIDX)
         */
        short  destBIdx;

        /**
         * \brief Address for linking (AutoReloading of a PaRAM Set)
         * This must point to a valid aligned 32-byte PaRAM set
         * A value of 0xFFFF means no linking
         */
        unsigned short linkAddr;

        /**
         * \brief Reload value of the numArrInFrame (BCNT)
         * Relevant only for A-sync transfers
         */
        unsigned short bCntReload;

        /**
         * \brief Index between consecutive frames of a Source Block (SRCCIDX)
         */
        short  srcCIdx;

        /**
         * \brief Index between consecutive frames of a Dest Block (DSTCIDX)
         */
        short  destCIdx;

        /**
         * \brief Number of Frames in a block (CCNT)
         */
        unsigned short cCnt;

        /**
         * \brief  This field is Reserved. Write zero to this field.
         */
        unsigned short rsvd;

}EDMA3CCPaRAMEntry;

/*
** Structure to store the EDMA context
*/
typedef struct edmaContext {
    /* Channel mapping reg Val */
    unsigned int dchMap[64];
    /* DMA Queue Number Register Val */    
    unsigned int dmaQNum[8];    
    
    /* DMA Region Access Enable Register val */    
    unsigned int regAccEnableLow;    
    unsigned int regAccEnableHigh;        

    /* Event Set Register value */    
    unsigned int eventSetRegLow;
    unsigned int eventSetRegHigh;    
    
    /* Enable Event Set Register value */    
    unsigned int enableEvtSetRegLow;
    unsigned int enableEvtSetRegHigh;
    
    /* Interrupt Enable Set Register value */            
    unsigned int intEnableSetRegLow;        
    unsigned int intEnableSetRegHigh;    
    
    struct EDMA3CCPaRAMEntry dmaParEntry[512];    
    
} EDMACONTEXT;

class AM335x_EDMA
{
public:
              AM335x_EDMA()
                : m_EDMA3CC_regs(*(n_EDMA::AM335X_EDMA3CC_regs)),
                m_EDMA3TC0_regs(*(n_EDMA::AM335X_EDMA3TC0_regs)),
                m_EDMA3TC1_regs(*(n_EDMA::AM335X_EDMA3TC1_regs)),
                m_EDMA3TC2_regs(*(n_EDMA::AM335X_EDMA3TC2_regs)) 
              { }
             ~AM335x_EDMA() { }

        void  init(uint32_t queNum);
        void  enable_ch_in_shadow_reg(uint32_t chType, uint32_t chNum);
        void  disable_ch_in_shadow_reg(uint32_t chType, uint32_t chNum);
        void  map_ch_to_evtQ(uint32_t chType, uint32_t chNum, uint32_t evtQNum);
        void  unmap_ch_to_evtQ(uint32_t chType, uint32_t chNum);
        void  map_QDMA_ch_to_paRAM(uint32_t chNum, uint32_t *paRAMId);
        void  set_QDMA_trig_word(uint32_t chNum, uint32_t trigWord);
        void  clr_miss_evt(uint32_t chNum);
        void  QDMA_clr_miss_evt(uint32_t chNum);
        void  clr_CCERR(uint32_t Flags);
        void  set_evt(uint32_t chNum);
        void  clr_evt(uint32_t chNum);
        void  enable_DMA_evt(uint32_t chNum);
        void  disable_DMA_evt(uint32_t chNum);
        void  enable_QDMA_evt(uint32_t chNum);
        void  disable_QDMA_evt(uint32_t chNum);
    uint32_t  get_intr_status();
        void  enable_evt_intr(uint32_t chNum);
        void  disable_evt_intr(uint32_t chNum);
        void  clr_intr(uint32_t value);
        void  get_paRAM(uint32_t chNum, EDMA3CCPaRAMEntry* currPaRAM);
        void  QDMA_get_paRAM(uint32_t chNum, uint32_t paRAMId, EDMA3CCPaRAMEntry* currPaRAM);
        void  set_paRAM(uint32_t chNum, EDMA3CCPaRAMEntry* newPaRAM);
        void  QDMA_set_paRAM(uint32_t chNum, uint32_t paRAMId, EDMA3CCPaRAMEntry* newPaRAM);
        void  QDMA_set_paRAM_entry(uint32_t paRAMId, uint32_t paRAMEntry, uint32_t newPaRAMEntryVal);
    uint32_t  QDMA_get_paRAM_entry(uint32_t paRAMId, uint32_t paRAMEntry);
    uint32_t  request_channel(uint32_t chType, uint32_t chNum, uint32_t tccNum, uint32_t evtQNum);
    uint32_t  free_channel(uint32_t chType, uint32_t chNum, uint32_t trigMode, uint32_t tccNum, uint32_t evtQNum);
    uint32_t  enable_transfer(uint32_t chNum, uint32_t trigMode);
    uint32_t  disable_transfer(uint32_t chNum, uint32_t trigMode);
        void  clear_error_bits(uint32_t chNum, uint32_t evtQNum);
    uint32_t  get_CCERR_status();
    uint32_t  get_ERR_intr_status();
    uint32_t  QDMA_get_ERR_intr_status();
        void  CCERR_evaluate();
        void  deinit(uint32_t queNum);
    uint32_t  version_get(void);
    uint32_t  peripheral_id_get();
    uint32_t  intr_status_high_get();
    uint32_t  ERR_intr_high_status_get();
        void  channel_to_param_map(uint32_t channel, uint32_t paramSet);
        void  context_save(EDMACONTEXT *edmaCntxPtr);
        void  context_restore(EDMACONTEXT *edmaCntxPtr);
private:
    n_EDMA::AM335x_EDMA3CC_Type &m_EDMA3CC_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC0_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC1_regs;
    n_EDMA::AM335x_EDMA3TC_Type &m_EDMA3TC2_regs;
};

#endif //__N_EDMA_H