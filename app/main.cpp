#include <stdint.h>
#include "board.h"
#include "init.h"
#include "sys_timer.h"
#include "pin.h"
#include "am3358zcz_pins.hpp"
#include "ring_buffer.hpp"


typedef union 
{ 
    struct 
    {                                              
        uint32_t    W_PEND_TCLR :4;           
        uint32_t    W_PEND_TCRR :4;           
        uint32_t    W_PEND_TLDR :4;           
        uint32_t    W_PEND_TTGR :4;                      
        uint32_t                :16;          
    } b;                                      
    uint32_t  z;                            
} reg_t;

typedef struct
{
     reg_t  register_a;
     reg_t  register_b;
     reg_t  register_c;
     reg_t  register_m;
      char  name[8];
} test_struct_t;

int main()
{  
    static uint64_t time = 0;
    
    test_struct_t pop_result;
    
    ring_buffer<test_struct_t,8> ringbuffer;
    
    test_struct_t fsm_1 = { .register_a = {.z = 0x3245},
                            .register_b = {.z = 0x3245},
                            .register_c = {.z = 0x3245},
                            .register_m = {.z = 0x3245},
                            .name = "fsm_1"
                          };
    test_struct_t fsm_2 = { .register_a = {.z = 0x1234},
                            .register_b = {.z = 0x1234},
                            .register_c = {.z = 0x1234},
                            .register_m = {.z = 0x1234},
                            .name = "fsm_2"
                          };
    test_struct_t fsm_3 = { .register_a = {.z = 0x8989},
                            .register_b = {.z = 0x8989},
                            .register_c = {.z = 0x8989},
                            .register_m = {.z = 0x8989},
                            .name = "fsm_3"
                          };
    test_struct_t fsm_4 = { .register_a = {.z = 0x6545},
                            .register_b = {.z = 0x6545},
                            .register_c = {.z = 0x6545},
                            .register_m = {.z = 0x6545},
                            .name = "fsm_4"
                          };
   test_struct_t fsm_5 = { .register_a = {.z = 0x1010},
                           .register_b = {.z = 0x1010},
                           .register_c = {.z = 0x1010},
                           .register_m = {.z = 0x1010},
                           .name = "fsm_5"
                          };
   
   test_struct_t fsm_6 = { .register_a = {.z = 0x2828},
                           .register_b = {.z = 0x2828},
                           .register_c = {.z = 0x2828},
                           .register_m = {.z = 0x2828},
                           .name = "fsm_6"
                          };
   
   test_struct_t fsm_7 = { .register_a = {.z = 0x9876},
                           .register_b = {.z = 0x9876},
                           .register_c = {.z = 0x9876},
                           .register_m = {.z = 0x9876},
                           .name = "fsm_7"
                          };
   
   test_struct_t fsm_8 = { .register_a = {.z = 0x5467},
                           .register_b = {.z = 0x5467},
                           .register_c = {.z = 0x5467},
                           .register_m = {.z = 0x5467},
                           .name = "fsm_8"
                          };
    
    init_board(); 
    
    ringbuffer.push(fsm_1);
    ringbuffer.push(fsm_2);
    ringbuffer.push(fsm_3);
    ringbuffer.push(fsm_4);
    ringbuffer.push(fsm_5);
    ringbuffer.push(fsm_6);
    ringbuffer.push(fsm_7);
    ringbuffer.push(fsm_8);
    
    pop_result = ringbuffer.pop_item(2);
                 ringbuffer.push(fsm_4);
    pop_result = ringbuffer.pop_item(1);
    pop_result = ringbuffer.pop_item(0);
    pop_result = ringbuffer.pop_item(1);
                 ringbuffer.push(fsm_1);
                 ringbuffer.push(fsm_2);
                 ringbuffer.push(fsm_3);
                 ringbuffer.push(fsm_1);
    pop_result = ringbuffer.pop_item(2);
    
    ringbuffer.reset_to_zero();
    
    

    while(1)
    {      
        if(sys_time.get_ms() - time > 1000)
        {
            time = sys_time.get_ms();
            
            USR_LED_3.toggle();
            
            if(END_STOP_X_2.read_input())
                USR_LED_0.set();
            else
                USR_LED_0.clear();
        }
    }
} 

/******************************* End of file *********************************/
