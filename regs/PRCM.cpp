#include "PRCM.h"
#include "RTC.hpp"
//#include "EDMA.h"

namespace REGS
{  
    namespace PRCM
    { 

        void run_clk_interconnects()
        {
            /* Run interconnects busses clocking */
            AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);    
        
            AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
        
            AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    
        
            AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            AM335x_CM_PER->L4LS_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->L4LS_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
        }
        
        void run_clk_DMTIMER(DMTIMER::e_TIMER_NUM tmr_num)
        {
            switch(tmr_num)
            {
               case DMTIMER::TIMER_5:
                    run_clk_DMTIMER_5();
                    return; // no need to run run_clk_interconnects() and other stuff below
               case DMTIMER::TIMER_6:
                    run_clk_DMTIMER_6();
                    return; // no need to run run_clk_interconnects() and other stuff below
                default:
                    break;    
            }
            
            run_clk_interconnects();
        
            switch(tmr_num)
            {
                case DMTIMER::TIMER_2:
                        /* Select the clock source for the Timer2 instance. */
                        AM335x_CM_DPLL->TIMER2_CLK.b.CLKSEL = LOW;               // clear bitfield
                        AM335x_CM_DPLL->TIMER2_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(AM335x_CM_DPLL->TIMER2_CLK.b.CLKSEL != CLK_M_OSC);    
                    
                        AM335x_CM_PER->TIMER2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
                        while(AM335x_CM_PER->TIMER2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    
                        while(AM335x_CM_PER->TIMER2_CLKCTRL.b.IDLEST != IDLEST_FUNC);
                    break;
                case DMTIMER::TIMER_3:
                        /* Select the clock source for the Timer3 instance. */
                        AM335x_CM_DPLL->TIMER3_CLK.b.CLKSEL = LOW;               // clear bitfield
                        AM335x_CM_DPLL->TIMER3_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(AM335x_CM_DPLL->TIMER3_CLK.b.CLKSEL != CLK_M_OSC);    
        
                        AM335x_CM_PER->TIMER3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
                        while(AM335x_CM_PER->TIMER3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    
                        while(AM335x_CM_PER->TIMER3_CLKCTRL.b.IDLEST != IDLEST_FUNC);
                    break;
                case DMTIMER::TIMER_4:
                        /* Select the clock source for the Timer4 instance. */
                        AM335x_CM_DPLL->TIMER4_CLK.b.CLKSEL = LOW;               // clear bitfield
                        AM335x_CM_DPLL->TIMER4_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(AM335x_CM_DPLL->TIMER4_CLK.b.CLKSEL != CLK_M_OSC);    
                    
                        AM335x_CM_PER->TIMER4_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
                        while(AM335x_CM_PER->TIMER4_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    
                        while(AM335x_CM_PER->TIMER4_CLKCTRL.b.IDLEST != IDLEST_FUNC);
                    break;
                case DMTIMER::TIMER_7:
                        /* Select the clock source for the Timer7 instance. */
                        AM335x_CM_DPLL->TIMER7_CLK.b.CLKSEL = LOW;               // clear bitfield
                        AM335x_CM_DPLL->TIMER7_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
                        while(AM335x_CM_DPLL->TIMER7_CLK.b.CLKSEL != CLK_M_OSC);    
        
                        AM335x_CM_PER->TIMER7_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
                        while(AM335x_CM_PER->TIMER7_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    
                        while(AM335x_CM_PER->TIMER7_CLKCTRL.b.IDLEST != IDLEST_FUNC);
                    break;
                default:
                  break;
            }
        
            while(!AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK);
            while(!AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK);
                
            while((AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK | 
                   AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false);
            
            switch(tmr_num)
            {
                case DMTIMER::TIMER_2:
                        while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                        AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER2_GCLK) == false);
                    break;
                case DMTIMER::TIMER_3:
                        while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                        AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER3_GCLK) == false);
                    break;
                case DMTIMER::TIMER_4:
                        while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                        AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER4_GCLK) == false);
                    break;
                case DMTIMER::TIMER_7:
                        while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                        AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER7_GCLK) == false);
                    break;
                default:
                  break;
            }
        
        }
        
        void run_clk_DMTIMER_1ms(e_TIMER1MS_CLKSEL clk_sel)
        {
            #define RTC_regs (REGS::RTC::AM335X_RTC) 

            e_TIMER1MS_CLKSEL clksel_copy = clk_sel;

            // disable write protect RTC registers
            RTC_regs->KICK0R.reg = REGS::RTC::KICK0R_KEY_DIS;
            RTC_regs->KICK1R.reg = REGS::RTC::KICK1R_KEY_DIS;

            switch(clksel_copy)
            {
                /// it is also necessary to allow use of external or internal oscillator 32768 in RTC module ///
                case MS1_32768HZ:
                    // if RTC running 
                    if(RTC_regs->RTC_CTRL.b.STOP_RTC && 
                       !RTC_regs->RTC_CTRL.b.RTC_DISABLE)
                    {
                        // if RTC running and clock source is internal, we cannot supply an external source
                        if(!RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC)
                        {
                            // external source used, just activate the remaining clocks
                            clksel_copy = MS1_32KHZ;
                            break;
                        }
    
                    }
                    // use external source
                    RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC = LOW;
                    RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC = HIGH;
                    RTC_regs->RTC_OSC.reg &= ~REGS::RTC::OSC_OSC32K_GZ_MSK;
                    RTC_regs->RTC_OSC.b.OSC32K_GZ = LOW;
                    break;
                case MS1_32KHZ:
                    // if RTC running
                    if(RTC_regs->RTC_CTRL.b.STOP_RTC && 
                       !RTC_regs->RTC_CTRL.b.RTC_DISABLE)
                    {
                        // if RTC running and clock source is external, we cannot supply an internal source
                        if(RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC)
                        {
                            // external source used, just activate the remaining clocks
                            clksel_copy = MS1_32768HZ;                            
                            break;
                        }
                    }
                    
                    //  just use internal source
                    RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC = LOW;
                    RTC_regs->RTC_OSC.b.SEL_32KCLK_SRC = LOW;
                    break;
                default:
                    break;
            }

            // enable write protect RTC registers
            RTC_regs->KICK0R.reg = REGS::RTC::KICK0_KICK0_KEY_EN;
            RTC_regs->KICK1R.reg = REGS::RTC::KICK1_KICK1_KEY_EN;

            #undef RTC_regs

            // Select the clock source for the Timer1ms instance.
            AM335x_CM_DPLL->TIMER1MS_CLK.b.CLKSEL = LOW;        
            while(AM335x_CM_DPLL->TIMER1MS_CLK.b.CLKSEL != LOW);    
            
            AM335x_CM_DPLL->TIMER1MS_CLK.b.CLKSEL = clksel_copy;    // select clock source
            while(AM335x_CM_DPLL->TIMER1MS_CLK.b.CLKSEL != clksel_copy); 
            
            // Configuring registers related to Wake-Up region.    
            AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;           // Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register.   
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);   // Waiting for MODULEMODE field to reflect the written value.    
            
            AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL = NO_SLEEP;                           // Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register.
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL != NO_SLEEP);                   // Waiting for CLKTRCTRL field to reflect the written value.             
 
            AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;                     // Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register.    
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);             // Waiting for CLKTRCTRL field to reflect the written value. 

            AM335x_CM_WKUP->TIMER1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_WKUP->TIMER1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); 
            while(AM335x_CM_WKUP->TIMER1_CLKCTRL.b.IDLEST != IDLEST_FUNC);
        }
        
        void run_clk_DMTIMER_5()
        {
            /* Select the clock source for the Timer5 instance. */
            AM335x_CM_DPLL->TIMER5_CLK.b.CLKSEL = LOW;               // clear bitfield
            AM335x_CM_DPLL->TIMER5_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
            while(AM335x_CM_DPLL->TIMER5_CLK.b.CLKSEL != CLK_M_OSC);    
            
            AM335x_CM_PER->TIMER5_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->TIMER5_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); 
            
            while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
            AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER5_GCLK) == false);
        }
        
        void run_clk_DMTIMER_6()
        {
            /* Select the clock source for the Timer6 instance. */
            AM335x_CM_DPLL->TIMER6_CLK.b.CLKSEL = LOW;               // clear bitfield
            AM335x_CM_DPLL->TIMER6_CLK.b.CLKSEL = CLK_M_OSC;   // and then set it to the desired value
            while(AM335x_CM_DPLL->TIMER6_CLK.b.CLKSEL != CLK_M_OSC);    
            
            AM335x_CM_PER->TIMER6_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->TIMER2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); 
            
            while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
            AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_TIMER6_GCLK) == false);
        }
        
        void run_clk_GPIO0()
        {
            /* Writing to MODULEMODE field of CM_WKUP_GPIO0_CLKCTRL register. */
            AM335x_CM_WKUP->GPIO0_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE; 
            /* Waiting for MODULEMODE field to reflect the written value. */
            while(AM335x_CM_WKUP->GPIO0_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            /* Writing to OPTFCLKEN_GPIO0_GDBCLK field of CM_WKUP_GPIO0_CLKCTRL register. */ 
            AM335x_CM_WKUP->GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK = HIGH; 
            /* Waiting for OPTFCLKEN_GPIO0_GDBCLK field to reflect the written value. */
            while(AM335x_CM_WKUP->GPIO0_CLKCTRL.b.OPTFCLKEN_GPIO0_GDBCLK != HIGH);
            
            /* Verifying if the other bits are set to required settings. */
            /* Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != HIGH);
            /* Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->L4WKUP_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != CLK_ACT);
            /* Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != HIGH);
            /* Writing to IDLEST field in CM_WKUP_GPIO0_CLKCTRL register. */
            while(AM335x_CM_WKUP->GPIO0_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_GPIO0_GDBCLK field in CM_WKUP_GPIO0_CLKCTRL register to attain desired value. */
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_GPIO0_GDBCLK != CLK_ACT);
        }
        
        void run_clk_GPIO1()
        {
            /* Writing to MODULEMODE field of CM_PER_GPIO1_CLKCTRL register. */
            AM335x_CM_PER->GPIO1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            /* Waiting for MODULEMODE field to reflect the written value. */
            while(AM335x_CM_PER->GPIO1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            /* Writing to OPTFCLKEN_GPIO_1_GDBCLK bit in CM_PER_GPIO1_CLKCTRL register. */
            AM335x_CM_PER->GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK = HIGH;
            /* Waiting for OPTFCLKEN_GPIO_1_GDBCLK bit to reflect the desired value. */
            while(AM335x_CM_PER->GPIO1_CLKCTRL.b.OPTFCLKEN_GPIO_1_GDBCLK != HIGH);
            
            /* Waiting for IDLEST field in CM_PER_GPIO1_CLKCTRL register to attain the desired value. */
            while(AM335x_CM_PER->GPIO1_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_GPIO_1_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL register to attain desired value.  */
            while(AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_1_GDBCLK != CLK_ACT);
        }
        
        void run_clk_GPIO2()
        {
            /* Writing to MODULEMODE field of CM_PER_GPIO2_CLKCTRL register. */
            AM335x_CM_PER->GPIO2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            /* Waiting for MODULEMODE field to reflect the written value. */
            while(AM335x_CM_PER->GPIO2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            /* Writing to OPTFCLKEN_GPIO_2_GDBCLK bit in CM_PER_GPIO1_CLKCTRL register. */
            AM335x_CM_PER->GPIO2_CLKCTRL.b.OPTFCLKEN_GPIO_2_GDBCLK = HIGH;
            /* Waiting for OPTFCLKEN_GPIO_2_GDBCLK bit to reflect the desired value. */
            while(AM335x_CM_PER->GPIO2_CLKCTRL.b.OPTFCLKEN_GPIO_2_GDBCLK != HIGH);
            
            /* Waiting for IDLEST field in CM_PER_GPIO2_CLKCTRL register to attain the desired value. */
            while(AM335x_CM_PER->GPIO2_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_GPIO_2_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL register to attain desired value.  */
            while(AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_2_GDBCLK != CLK_ACT);
        }
        
        void run_clk_GPIO3()
        {
            /* Writing to MODULEMODE field of CM_PER_GPIO3_CLKCTRL register. */
            AM335x_CM_PER->GPIO3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            /* Waiting for MODULEMODE field to reflect the written value. */
            while(AM335x_CM_PER->GPIO3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            /* Writing to OPTFCLKEN_GPIO_3_GDBCLK bit in CM_PER_GPIO1_CLKCTRL register. */
            AM335x_CM_PER->GPIO3_CLKCTRL.b.OPTFCLKEN_GPIO_3_GDBCLK = HIGH;
            /* Waiting for OPTFCLKEN_GPIO_3_GDBCLK bit to reflect the desired value. */
            while(AM335x_CM_PER->GPIO3_CLKCTRL.b.OPTFCLKEN_GPIO_3_GDBCLK != HIGH);
            
            /* Waiting for IDLEST field in CM_PER_GPIO3_CLKCTRL register to attain the desired value. */
            while(AM335x_CM_PER->GPIO3_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            /* Waiting for CLKACTIVITY_GPIO_3_GDBCLK bit in CM_PER_L4LS_CLKSTCTRL register to attain desired value.  */
            while(AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_GPIO_3_GDBCLK != CLK_ACT);
        }
        
        void run_I2C0_clk()
        {
            /** Configuring L3 Interface Clocks. **/
            /** Writing to MODULEMODE field of CM_PER_L3_CLKCTRL register. **/
            //HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) |=  CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_L3_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) & CM_PER_L3_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
        
            /** Writing to MODULEMODE field of CM_PER_L3_INSTR_CLKCTRL register. **/
            //HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) |= CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_L3_INSTR_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) & CM_PER_L3_INSTR_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;    
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
        
            /** Writing to CLKTRCTRL field of CM_PER_L3_CLKSTCTRL register. **/
            //HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) |= CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            //while(CM_PER_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP != (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKTRCTRL));
            AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
            
            /** Writing to CLKTRCTRL field of CM_PER_OCPWP_L3_CLKSTCTRL register. **/
            //HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) |= CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            //while(CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL_SW_WKUP != (HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & CM_PER_OCPWP_L3_CLKSTCTRL_CLKTRCTRL));
            AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
            
            /** Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register. **/
            //HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) |= CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            //while(CM_PER_L3S_CLKSTCTRL_CLKTRCTRL_SW_WKUP != (HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKTRCTRL));
            AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);  
        
            /** Checking fields for necessary values.  **/
            /** Waiting for IDLEST field in CM_PER_L3_CLKCTRL register to be set to 0x0. **/
            //while((CM_PER_L3_CLKCTRL_IDLEST_FUNC << CM_PER_L3_CLKCTRL_IDLEST_SHIFT)!= (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKCTRL) & CM_PER_L3_CLKCTRL_IDLEST));
            while(AM335x_CM_PER->L3_CLKCTRL.b.IDLEST != IDLEST_FUNC); 
            
            /** Waiting for IDLEST field in CM_PER_L3_INSTR_CLKCTRL register to attain the desired value. **/
            //while((CM_PER_L3_INSTR_CLKCTRL_IDLEST_FUNC << CM_PER_L3_INSTR_CLKCTRL_IDLEST_SHIFT)!=
            //      (HWREG(SOC_CM_PER_REGS + CM_PER_L3_INSTR_CLKCTRL) & CM_PER_L3_INSTR_CLKCTRL_IDLEST));
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            /** Waiting for CLKACTIVITY_L3_GCLK field in CM_PER_L3_CLKSTCTRL register to attain the desired value. **/
            //while(CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK != (HWREG(SOC_CM_PER_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK != CLK_ACT);
            
            /** Waiting for CLKACTIVITY_OCPWP_L3_GCLK field in CM_PER_OCPWP_L3_CLKSTCTRL register to attain the desired value. **/
            //while(CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK !=
            //      (HWREG(SOC_CM_PER_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK));
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK != CLK_ACT);
            
            /** Waiting for CLKACTIVITY_L3S_GCLK field in CM_PER_L3S_CLKSTCTRL register to attain the desired value. **/
            //while(CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK !=
            //     (HWREG(SOC_CM_PER_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK != CLK_ACT);
        
            /** Configuring registers related to Wake-Up region. **/
            /** Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register. **/
            //HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) |= CM_WKUP_CONTROL_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_WKUP_CONTROL_CLKCTRL_MODULEMODE_ENABLE !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) & CM_WKUP_CONTROL_CLKCTRL_MODULEMODE));
            AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            
            /** Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register. **/
            //HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) |= CM_WKUP_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            //while(CM_WKUP_CLKSTCTRL_CLKTRCTRL_SW_WKUP != (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) & CM_WKUP_CLKSTCTRL_CLKTRCTRL));
            AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
              
            /** Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register. **/
            //HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) |= CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL_SW_WKUP;
            //while(CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL_SW_WKUP != 
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) & CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKTRCTRL));
            AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
            
            /** Writing to MODULEMODE field of CM_WKUP_I2C0_CLKCTRL register. **/
            //HWREG(SOC_CM_WKUP_REGS + CM_WKUP_I2C0_CLKCTRL) |= CM_WKUP_I2C0_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_WKUP_I2C0_CLKCTRL_MODULEMODE_ENABLE !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_I2C0_CLKCTRL) & CM_WKUP_I2C0_CLKCTRL_MODULEMODE));
            AM335x_CM_WKUP->I2C0_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_WKUP->I2C0_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            
            /** Verifying if the other bits are set to required settings. **/
            /** Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain desired value **/
            //while((CM_WKUP_CONTROL_CLKCTRL_IDLEST_FUNC <<  CM_WKUP_CONTROL_CLKCTRL_IDLEST_SHIFT) !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CONTROL_CLKCTRL) & CM_WKUP_CONTROL_CLKCTRL_IDLEST));
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            /** Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL register to attain desired value. **/
            //while(CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKACTIVITY_L3_AON_GCLK !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L3_AON_CLKSTCTRL) & CM_WKUP_CM_L3_AON_CLKSTCTRL_CLKACTIVITY_L3_AON_GCLK));
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != HIGH);
            
            /** Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain desired value.**/
            //while((CM_WKUP_L4WKUP_CLKCTRL_IDLEST_FUNC << CM_WKUP_L4WKUP_CLKCTRL_IDLEST_SHIFT) !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_L4WKUP_CLKCTRL) & CM_WKUP_L4WKUP_CLKCTRL_IDLEST));
            while(AM335x_CM_WKUP->L4WKUP_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            /** Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register to attain desired value. **/
           // while(CM_WKUP_CLKSTCTRL_CLKACTIVITY_L4_WKUP_GCLK !=
           //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) & CM_WKUP_CLKSTCTRL_CLKACTIVITY_L4_WKUP_GCLK));
           while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != CLK_ACT);
            
            /** Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL register to attain desired value. **/
            //while(CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL_CLKACTIVITY_L4_WKUP_AON_GCLK !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL) & CM_WKUP_CM_L4_WKUP_AON_CLKSTCTRL_CLKACTIVITY_L4_WKUP_AON_GCLK));
            while(AM335x_CM_WKUP->L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != HIGH);
        
            /** Waiting for CLKACTIVITY_I2C0_GFCLK field in CM_WKUP_CLKSTCTRL register to attain desired value. **/
            //while(CM_WKUP_CLKSTCTRL_CLKACTIVITY_I2C0_GFCLK !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_CLKSTCTRL) & CM_WKUP_CLKSTCTRL_CLKACTIVITY_I2C0_GFCLK));
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_I2C0_GFCLK != CLK_ACT);
            
            /** Waiting for IDLEST field in CM_WKUP_I2C0_CLKCTRL register to attain desired value. **/
            //while((CM_WKUP_I2C0_CLKCTRL_IDLEST_FUNC << CM_WKUP_I2C0_CLKCTRL_IDLEST_SHIFT) !=
            //      (HWREG(SOC_CM_WKUP_REGS + CM_WKUP_I2C0_CLKCTRL) & CM_WKUP_I2C0_CLKCTRL_IDLEST));
            while(AM335x_CM_WKUP->I2C0_CLKCTRL.b.IDLEST != IDLEST_FUNC);
        }
        
        void run_I2C1_clk()
        {
            run_clk_interconnects();
        
            //HWREG(SOC_PRCM_REGS + CM_PER_I2C1_CLKCTRL) |= CM_PER_I2C1_CLKCTRL_MODULEMODE_ENABLE;
            //while((HWREG(SOC_PRCM_REGS + CM_PER_I2C1_CLKCTRL) & 
            //       CM_PER_I2C1_CLKCTRL_MODULEMODE) != CM_PER_I2C1_CLKCTRL_MODULEMODE_ENABLE);
            AM335x_CM_PER->I2C1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_PER->I2C1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
            //      (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK | CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));
            while(!AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK);
            while(!AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK);
                
            while((AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK | 
                   AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false);
        
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
            //       (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK | CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK)));
                while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                       AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_I2C_FCLK) == false);
        }
        
        void run_I2C2_clk()
        {
            run_clk_interconnects();
        
            //HWREG(SOC_PRCM_REGS + CM_PER_I2C1_CLKCTRL) |= CM_PER_I2C1_CLKCTRL_MODULEMODE_ENABLE;
            //while((HWREG(SOC_PRCM_REGS + CM_PER_I2C1_CLKCTRL) & 
            //       CM_PER_I2C1_CLKCTRL_MODULEMODE) != CM_PER_I2C1_CLKCTRL_MODULEMODE_ENABLE);
            AM335x_CM_PER->I2C2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_PER->I2C2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
            
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3S_CLKSTCTRL) & CM_PER_L3S_CLKSTCTRL_CLKACTIVITY_L3S_GCLK));
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L3_CLKSTCTRL) & CM_PER_L3_CLKSTCTRL_CLKACTIVITY_L3_GCLK));
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_OCPWP_L3_CLKSTCTRL) & 
            //      (CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L3_GCLK | CM_PER_OCPWP_L3_CLKSTCTRL_CLKACTIVITY_OCPWP_L4_GCLK)));
            while(!AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK);
            while(!AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK);
                
            while((AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK | 
                   AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L4_GCLK) == false);
        
            //while(!(HWREG(SOC_PRCM_REGS + CM_PER_L4LS_CLKSTCTRL) & 
            //       (CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_L4LS_GCLK | CM_PER_L4LS_CLKSTCTRL_CLKACTIVITY_I2C_FCLK)));
                while((AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_L4LS_GCLK | 
                       AM335x_CM_PER->L4LS_CLKSTCTRL.b.CLKACTIVITY_I2C_FCLK) == false);
        }
        
        void run_clk_UART0()
        {
              /** Configuring L3 Interface Clocks. **/    
            AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;            // Writing to MODULEMODE field of CM_PER_L3_CLKCTRL register.    
            while(AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);    // Waiting for MODULEMODE field to reflect the written value. 
            
            AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;          // Writing to MODULEMODE field of CM_PER_L3_INSTR_CLKCTRL register    
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);  // Waiting for MODULEMODE field to reflect the written value.
            
            AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;         // Writing to CLKTRCTRL field of CM_PER_L3_CLKSTCTRL register.    
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP); // Waiting for CLKTRCTRL field to reflect the written value.    
            
            AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;           // Writing to CLKTRCTRL field of CM_PER_OCPWP_L3_CLKSTCTRL register.    
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL!= SW_WKUP);    // Waiting for CLKTRCTRL field to reflect the written value.    
            
            AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;            // Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register.
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);    // Waiting for CLKTRCTRL field to reflect the written value.
            
            /** Checking fields for necessary values.**/    
            while(AM335x_CM_PER->L3_CLKCTRL.b.IDLEST != IDLEST_FUNC);  // Waiting for IDLEST field in CM_PER_L3_CLKCTRL register to be set to 0x0. 
            
            // Waiting for IDLEST field in CM_PER_L3_INSTR_CLKCTR reach the desired value
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            // Waiting for CLKACTIVITY_L3_GCLK field in CM_PER_L3_CLKSTCTRL reach the desired value
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK != CLK_ACT);
            
            // Waiting for CLKACTIVITY_OCPWP_L3_GCLK field in CM_PER_OCPWP_L3_CLKSTCTRL reach the desired value
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK != CLK_ACT);
            
            //Waiting for CLKACTIVITY_L3S_GCLK field in CM_PER_L3S_CLKSTCTRL reach the desired value
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK != CLK_ACT);
            
            /** Configuring registers related to Wake-Up region. **/    
            AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;          // Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register.   
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);  // Waiting for MODULEMODE field to reflect the written value.    
            
            AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;           // Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register.
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);   // Waiting for CLKTRCTRL field to reflect the written value.    
            
            AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;            // Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register.    
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);    // Waiting for CLKTRCTRL field to reflect the written value. 
            
            AM335x_CM_WKUP->UART0_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;         // Writing to MODULEMODE field of CM_WKUP_UART0_CLKCTRL register.    
            while(AM335x_CM_WKUP->UART0_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); // Waiting for MODULEMODE field to reflect the written value.
            
            /** Verifying if the other bits are set to required settings. **/
            // Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL reach the desired value
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            // Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL reach the desired value
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != HIGH);
            
            // Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL reach the desired value
            while(AM335x_CM_WKUP->L4WKUP_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            // Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL reach the desired value
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != CLK_ACT);
        
            // Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL reach the desired value
            while(AM335x_CM_WKUP->L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != HIGH);
            
            // Waiting for CLKACTIVITY_UART0_GFCLK field in CM_WKUP_CLKSTCTRL reach the desired value
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_UART0_GFCLK != CLK_ACT);
            
            // Waiting for IDLEST field in CM_WKUP_UART0_CLKCTRL reach the desired value
            while(AM335x_CM_WKUP->UART0_CLKCTRL.b.IDLEST != IDLEST_FUNC);
        }

        void run_RTC_clk()
        {
            /// Configuring L3 Interface Clocks. ///
        
            // Writing to MODULEMODE field of CM_PER_L3_CLKCTRL register.
            // Waiting for MODULEMODE field to reflect the written value. 
            AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_PER->L3_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
                   
            // Writing to MODULEMODE field of CM_PER_L3_INSTR_CLKCTRL register.
            // Waiting for MODULEMODE field to reflect the written value.
            AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);        
                    
            // Writing to CLKTRCTRL field of CM_PER_L3_CLKSTCTRL register.
            // Waiting for CLKTRCTRL field to reflect the written value.
            AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP; 
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
                   
            // Writing to CLKTRCTRL field of CM_PER_OCPWP_L3_CLKSTCTRL register.
            // Waiting for CLKTRCTRL field to reflect the written value.
            AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
                   
            // Writing to CLKTRCTRL field of CM_PER_L3S_CLKSTCTRL register. 
            // Waiting for CLKTRCTRL field to reflect the written value.
            AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;    
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            /// Checking fields for necessary values.  ///
            
            // Waiting for IDLEST field in CM_PER_L3_CLKCTRL register to be set to 0x0.
            while(AM335x_CM_PER->L3_CLKCTRL.b.IDLEST != IDLEST_FUNC);
            
            // Waiting for IDLEST field in CM_PER_L3_INSTR_CLKCTRL register to attain the
            // desired value.
            while(AM335x_CM_PER->L3_INSTR_CLKCTRL.b.IDLEST != IDLEST_FUNC);

            // Waiting for CLKACTIVITY_L3_GCLK field in CM_PER_L3_CLKSTCTRL register to
            // attain the desired value.
            while(AM335x_CM_PER->L3_CLKSTCTRL.b.CLKACTIVITY_L3_GCLK != CLK_ACT);

            // Waiting for CLKACTIVITY_OCPWP_L3_GCLK field in CM_PER_OCPWP_L3_CLKSTCTRL
            // register to attain the desired value.
            while(AM335x_CM_PER->OCPWP_L3_CLKSTCTRL.b.CLKACTIVITY_OCPWP_L3_GCLK != CLK_ACT);

            // Waiting for CLKACTIVITY_L3S_GCLK field in CM_PER_L3S_CLKSTCTRL register
            // to attain the desired value.
            while(AM335x_CM_PER->L3S_CLKSTCTRL.b.CLKACTIVITY_L3S_GCLK != CLK_ACT);
        
        
            // Configuring registers related to Wake-Up region. 
        
            // Writing to MODULEMODE field of CM_WKUP_CONTROL_CLKCTRL register.        
            // Waiting for MODULEMODE field to reflect the written value.
            AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); 
        
            // Writing to CLKTRCTRL field of CM_WKUP_CLKSTCTRL register.
            // Waiting for CLKTRCTRL field to reflect the written value.
            AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            // Writing to CLKTRCTRL field of CM_L3_AON_CLKSTCTRL register.
            // Waiting for CLKTRCTRL field to reflect the written value.
            AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;     
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
        
            /// Verifying if the other bits are set to required settings. ///        
            // Waiting for IDLEST field in CM_WKUP_CONTROL_CLKCTRL register to attain
            // desired value.
            while(AM335x_CM_WKUP->CONTROL_CLKCTRL.b.IDLEST != IDLEST_FUNC);

            // Waiting for CLKACTIVITY_L3_AON_GCLK field in CM_L3_AON_CLKSTCTRL
            // register to attain desired value.
            while(AM335x_CM_WKUP->L3_AON_CLKSTCTRL.b.CLKACTIVITY_L3_AON_GCLK != CLK_ACT);

            // Waiting for IDLEST field in CM_WKUP_L4WKUP_CLKCTRL register to attain
            // desired value.
            while(AM335x_CM_WKUP->L4WKUP_CLKCTRL.b.IDLEST != IDLEST_FUNC);

            // Waiting for CLKACTIVITY_L4_WKUP_GCLK field in CM_WKUP_CLKSTCTRL register
            // to attain desired value.
            while(AM335x_CM_WKUP->CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_GCLK != CLK_ACT);

            // Waiting for CLKACTIVITY_L4_WKUP_AON_GCLK field in CM_L4_WKUP_AON_CLKSTCTRL
            // register to attain desired value.
            while(AM335x_CM_WKUP->L4_WKUP_AON_CLKSTCTRL.b.CLKACTIVITY_L4_WKUP_AON_GCLK != CLK_ACT);
            /// Performing Clock configurations of RTC. ///
        
            // Writing to MODULEMODE field of CM_RTC_RTC_CLKCTRL register.        
            // Waiting for MODULEMODE field to reflect the written value.
            AM335x_CM_RTC->RTC_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;
            while(AM335x_CM_RTC->RTC_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);
        
            // Writing to CLKTRCTRL field of CM_RTC_CLKSTCTRL register. 
            // Waiting for CLKTRCTRL field to reflect the written value. 
            AM335x_CM_RTC->CLKSTCTRL.b.CLKTRCTRL = SW_WKUP;
            while(AM335x_CM_RTC->CLKSTCTRL.b.CLKTRCTRL != SW_WKUP);
        
            /// Checking the RTC registers for desired values being set. ///
        
            // Waiting for IDLEST field in CM_RTC_RTC_CLKCTRL register to attain the
            // desired value.
            while(AM335x_CM_RTC->RTC_CLKCTRL.b.IDLEST != IDLEST_FUNC);

            // Waiting for CLKACTIVITY_L4_RTC_GCLK field in CM_RTC_CLKSTCTRL register
            // to attain the desired value.
            while(AM335x_CM_RTC->CLKSTCTRL.b.CLKACTIVITY_L4_RTC_GCLK != CLK_ACT);        

            // Waiting for CLKACTIVITY_RTC_32KCLK field in CM_RTC_CLKSTCTRL register
            // to attain the desired value.
            while(AM335x_CM_RTC->CLKSTCTRL.b.CLKACTIVITY_RTC_32KCLK != CLK_ACT);
        }
        
        /*
        void  run_EDMA_clk(void* p_Obj)
        {
            AM335x_EDMA &s_EDMA = *reinterpret_cast<AM335x_EDMA *>(p_Obj);
          
            /// Configuring clocks for EDMA3 TPCC and TPTCs. ///    
            //HWREG(SOC_CM_PER_REGS + CM_PER_TPCC_CLKCTRL) |= CM_PER_TPCC_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_TPCC_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_TPCC_CLKCTRL) & CM_PER_TPCC_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->TPCC_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;          // Writing to MODULEMODE field of CM_PER_TPCC_CLKCTRL register. 
            while(AM335x_CM_PER->TPCC_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);  // Waiting for MODULEMODE field to reflect the written value.    
            
            //HWREG(SOC_CM_PER_REGS + CM_PER_TPTC0_CLKCTRL) |= CM_PER_TPTC0_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_TPTC0_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC0_CLKCTRL) & CM_PER_TPTC0_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->TPTC0_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;             // Writing to MODULEMODE field of CM_PER_TPTC0_CLKCTRL register.
            while(AM335x_CM_PER->TPTC0_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE);     // Waiting for MODULEMODE field to reflect the written value.
            
            //HWREG(SOC_CM_PER_REGS + CM_PER_TPTC1_CLKCTRL) |= CM_PER_TPTC1_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_TPTC1_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC1_CLKCTRL) & CM_PER_TPTC1_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->TPTC1_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;         // Writing to MODULEMODE field of CM_PER_TPTC1_CLKCTRL register.
            while(AM335x_CM_PER->TPTC1_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); // Waiting for MODULEMODE field to reflect the written value.    
        
            // Writing to MODULEMODE field of CM_PER_TPTC2_CLKCTRL register.
            //HWREG(SOC_CM_PER_REGS + CM_PER_TPTC2_CLKCTRL) |= CM_PER_TPTC2_CLKCTRL_MODULEMODE_ENABLE;
            //while(CM_PER_TPTC2_CLKCTRL_MODULEMODE_ENABLE != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC2_CLKCTRL) & CM_PER_TPTC2_CLKCTRL_MODULEMODE));
            AM335x_CM_PER->TPTC2_CLKCTRL.b.MODULEMODE = MODULEMODE_ENABLE;         // Writing to MODULEMODE field of CM_PER_TPTC1_CLKCTRL register.
            while(AM335x_CM_PER->TPTC2_CLKCTRL.b.MODULEMODE != MODULEMODE_ENABLE); // Waiting for MODULEMODE field to reflect the written value.
        
        	//	DMA in non-idle mode
        	//HWREG(0x49800010) = 0x00000028;
        	//HWREG(0x49900010) = 0x00000028;
        	//HWREG(0x49a00010) = 0x00000028;
            s_EDMA.set_non_idle_mode();
            
            //while((CM_PER_TPCC_CLKCTRL_IDLEST_FUNC << CM_PER_TPCC_CLKCTRL_IDLEST_SHIFT)   != (HWREG(SOC_CM_PER_REGS + CM_PER_TPCC_CLKCTRL) & CM_PER_TPCC_CLKCTRL_IDLEST));
            //while((CM_PER_TPTC0_CLKCTRL_IDLEST_FUNC << CM_PER_TPTC0_CLKCTRL_IDLEST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC0_CLKCTRL) & CM_PER_TPTC0_CLKCTRL_IDLEST));    
            //while((CM_PER_TPTC0_CLKCTRL_STBYST_FUNC << CM_PER_TPTC0_CLKCTRL_STBYST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC0_CLKCTRL) & CM_PER_TPTC0_CLKCTRL_STBYST));
            //while((CM_PER_TPTC1_CLKCTRL_IDLEST_FUNC << CM_PER_TPTC1_CLKCTRL_IDLEST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC1_CLKCTRL) & CM_PER_TPTC1_CLKCTRL_IDLEST)); 
            //while((CM_PER_TPTC1_CLKCTRL_STBYST_FUNC << CM_PER_TPTC1_CLKCTRL_STBYST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC1_CLKCTRL) & CM_PER_TPTC1_CLKCTRL_STBYST));   
            //while((CM_PER_TPTC2_CLKCTRL_IDLEST_FUNC << CM_PER_TPTC2_CLKCTRL_IDLEST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC2_CLKCTRL) & CM_PER_TPTC2_CLKCTRL_IDLEST));    
            //while((CM_PER_TPTC2_CLKCTRL_STBYST_FUNC << CM_PER_TPTC2_CLKCTRL_STBYST_SHIFT) != (HWREG(SOC_CM_PER_REGS + CM_PER_TPTC2_CLKCTRL) & CM_PER_TPTC2_CLKCTRL_STBYST)); 
            
            while(AM335x_CM_PER->TPCC_CLKCTRL.b.IDLEST != IDLEST_FUNC);            // Waiting for IDLEST field in CM_PER_TPCC_CLKCTRL register to attain the desired value.
            
            while(AM335x_CM_PER->TPTC0_CLKCTRL.b.IDLEST != IDLEST_FUNC);           // Waiting for IDLEST field in CM_PER_TPTC0_CLKCTRL register to attain the desired value.
            while(AM335x_CM_PER->TPTC0_CLKCTRL.b.STBYST != STBYST_FUNC);         // Waiting for STBYST field in CM_PER_TPTC0_CLKCTRL register to attain the desired value.
            
            while(AM335x_CM_PER->TPTC1_CLKCTRL.b.IDLEST != IDLEST_FUNC);           // Waiting for IDLEST field in CM_PER_TPTC1_CLKCTRL register to attain the desired value.
            while(AM335x_CM_PER->TPTC1_CLKCTRL.b.STBYST != STBYST_FUNC);         // Waiting for STBYST field in CM_PER_TPTC1_CLKCTRL register to attain the desired value.
            
            while(AM335x_CM_PER->TPTC2_CLKCTRL.b.IDLEST != IDLEST_FUNC);           // Waiting for IDLEST field in CM_PER_TPTC2_CLKCTRL register to attain the desired value..
            while(AM335x_CM_PER->TPTC2_CLKCTRL.b.STBYST != STBYST_FUNC);         // Waiting for STBYST field in CM_PER_TPTC2_CLKCTRL register to attain the desired value..    
        }
        */

    }   //namespace PRCM

}   // namespace REGS

    