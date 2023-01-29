#ifndef _UTILS_H
#define _UTILS_H

#ifdef _cplusplus
extern "C" {
#endif
  
#include <stdlib.h>
 
// forward declaraton
enum stereoChnl_e : uint8_t;
enum      frame_e : uint8_t;
template <typename T, size_t buf_size>
class frame_buffer;

struct i2s_sample_t;

#define MY_RAND_MAX        (32767)
#define MY_RAND_MIN        (-32768)
  
#define M_PI 			   (3.141592653589f)
  
#define ASSERT(expr)                                                          \
if (expr)                                                                     \
{                                                                             \
}                                                                             \
else                                                                          \
{                                                                             \
    while (1);                                                                \
}

#define countof(a)              (sizeof(a) / sizeof(*(a)))

#define hi_z(pin)															\
nrf_gpio_cfg(pin,															\
             NRF_GPIO_PIN_DIR_INPUT,										\
             NRF_GPIO_PIN_INPUT_DISCONNECT,									\
             NRF_GPIO_PIN_NOPULL,											\
             NRF_GPIO_PIN_S0S1,												\
             NRF_GPIO_PIN_NOSENSE);											\
               
#define undefine_gpiote(x)                                                              \
NRF_GPIOTE->CONFIG[x] = (GPIOTE_CONFIG_MODE_Disabled   << GPIOTE_CONFIG_MODE_Pos) |     \
                        (31UL                          << GPIOTE_CONFIG_PSEL_Pos) |     \
                        (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos);  \
                        __NOP();    \
                        __NOP();    \
                        __NOP();    \

#define conf_gpiote_hilo(x, y)                                                          \
NRF_GPIOTE->CONFIG[x] = (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos) |          \
                        (y << GPIOTE_CONFIG_PSEL_Pos) |                                 \
                        (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos);  \
                        __NOP();    \
                        __NOP();    \
                        __NOP();    \
                          
#define conf_gpiote_lohi(x, y)                                                          \
NRF_GPIOTE->CONFIG[x] = (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos) |          \
                        (y << GPIOTE_CONFIG_PSEL_Pos) |                                 \
                        (GPIOTE_CONFIG_POLARITY_LoToHi << GPIOTE_CONFIG_POLARITY_Pos);  \
                        __NOP();    \
                        __NOP();    \
                        __NOP();    \
               
#define SLEEPFORAWHILE()                        \
NRF_POWER->DCDCEN = 0;                          \
NRF_CLOCK->TASKS_HFCLKSTOP = 1;                 \
__WFI();                                        \
__WFI();
               
#define WATCHDOGRESET                           \
    NRF_WDT->RR[0] = 0x6E524635;               \
    WDT_aux_cntr = 0;
     
extern "C" {
extern  int random(void); // RAND_MAX assumed to be 32767
}
extern  int rnd_max(int max);
extern void seed_random(unsigned int seed);
extern uint16_t crc16_fill(const uint8_t *pBuf, uint32_t uiLength, uint16_t fill);
extern uint16_t crc16(const uint8_t *pBuf, uint32_t uiLength);
extern volatile uint32_t* pincfg_reg(uint32_t pin);

#ifdef FRAMES_DBG

#ifndef RAW_FRAMESIZE
  #define RAW_FRAMESIZE (80)
#endif  //RAW_FRAMESIZE

extern uint32_t   frame_dbg_buf[2][RAW_FRAMESIZE];
extern  int16_t   chnl_dbg_buf[RAW_FRAMESIZE];
extern void   show_frame_data(frame_buffer<i2s_sample_t,RAW_FRAMESIZE> &rfbuf, frame_e frm, stereoChnl_e chnl); 

#endif //FRAMES_DBG

#ifdef _cplusplus
}
#endif

#endif // _UTILS_H