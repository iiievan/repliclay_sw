#ifndef _FRAME_BUFER_H_
#define _FRAME_BUFER_H_

#include "paired_buffer.h"
#include <cstring>
#include <math.h>

#define FRAMES_DEBUG

#ifndef RECEIVER_SUB_FRAME_MAX
    #define RECEIVER_SUB_FRAME_MAX        (5)                                         //количество подкадров у приемника
    #define RAW_FRAMESIZE                 (80)                                        //размер при передаче или приеме в кодек
    #define RECEIVER_SUB_FRAME_SIZE       (RAW_FRAMESIZE/RECEIVER_SUB_FRAME_MAX)      //размер подкадра для приемника 
#endif

#ifdef FRAMES_DEBUG
    #define DEMODULATE_SAMPLES_MAX     (64)
    #define DEBUG_FRAMESIZE  DEMODULATE_SAMPLES_MAX
#endif

enum stereoChnl_e : uint8_t;
enum      e_Frame : uint8_t;

enum stereoChnl_e : uint8_t
{
  LEFT = 0,
  RIGHT,
  STEREO,
};

enum e_Frame : uint8_t
{
    NONE = 0,
    COMPLETE,
    EMPTY,
};

template <size_t BUF_SIZE = 16UL >
class frame_buffer;

struct i2s_sample_t;

struct i2s_sample_t 
{
  union {
    struct {
      union {
        int16_t r;
        int16_t right_chnl; //LSB - младший
      };
      union {
        int16_t l;
        int16_t left_chnl;  //MSB - старший
      };
    };
    
    uint32_t stereo;
  };
};

#ifdef FRAMES_DEBUG
    extern int16_t   chnl_dbg_buf[DEBUG_FRAMESIZE];
    extern uint32_t  frame_dbg_buf[2][DEBUG_FRAMESIZE];
#endif  //FRAMES_DEBUG

template <size_t BUF_SIZE>
class frame_buffer : public paired_buffer<i2s_sample_t, BUF_SIZE>
{
public:    
                frame_buffer()
                : paired_buffer<i2s_sample_t, BUF_SIZE>{}
                { m_Frame_size = BUF_SIZE; }  

                uint32_t* get_chnl(e_Frame frm, stereoChnl_e chnl)      
                {   
                      int16_t *pCh; 
                
                      switch(frm)
                      {
                          case EMPTY:
                              pCh = (int16_t*)paired_buffer<i2s_sample_t, BUF_SIZE>::get_empty_buf();
                              break;
                          case COMPLETE:
                              pCh = (int16_t*)paired_buffer<i2s_sample_t, BUF_SIZE>::get_complete_buf();
                          break;
                          default:
                          return nullptr;
                      }
                      
                      // left is MSB
                      if(chnl == LEFT)
                          pCh++;           
                
                    return (uint32_t*)pCh; 
                }
          
                // amplitude: 0..20000, period in radians.
                // Example:
                // output_frame.fill_frame_with_sin(18000,20.0);
                // show_frame_data(output_frame, EMPTY, RIGHT);    
                // output_frame.switch_buffers();    
                // output_frame.fill_frame_with_sin(18000,20.0);
                // show_frame_data(output_frame, EMPTY, RIGHT);    
                // memset(chnl_dbg_buf, 0, sizeof(int16_t)*RAW_FRAMESIZE)
                void fill_frame_with_sin(int amplitude , float period) 
                {          
                    const  float pi = 3.14159265359;
                           float angle = 0.0;
                    static float phase = 0.0;
                    i2s_sample_t* p_Empty_frame = paired_buffer<i2s_sample_t, BUF_SIZE>::get_empty_buf();
                    
                    int sin_value;
                  
                    //fill the buffer with sinusoid
                    for (uint32_t i = 0; i < m_Frame_size; i++)
                    {       
                        sin_value = (int)((float)amplitude * sin (angle + phase)) ;
                        p_Empty_frame[i].right_chnl = sin_value;
                        p_Empty_frame[i].l = p_Empty_frame[i].r;
                                   
                        angle += (float)(2 * pi) / period;
                
                        //remember the angle at the end of the frame
                        //to "glue" the next with this 
                        if (i == (m_Frame_size - 1))
                            phase += angle;
                    }
                }          

                // partially fills the buffer
                void fill_partially(frame_buffer &rSource)
                {
                    i2s_sample_t* playing_frame = rSource.get_complete_buf();
                    volatile uint8_t type_size = sizeof(i2s_sample_t);
        
                    if(++rSource.subframe_counter >= RECEIVER_SUB_FRAME_MAX)
                    {
                        rSource.subframe_counter = 0;
        
                        playing_frame = rSource.switch_buffers();
                    } 
        
                    memcpy(paired_buffer<i2s_sample_t, BUF_SIZE>::get_complete_buf(), 
                           &playing_frame[RECEIVER_SUB_FRAME_SIZE*(rSource.subframe_counter)], 
                           type_size*RECEIVER_SUB_FRAME_SIZE);              
                    memset(&playing_frame[RECEIVER_SUB_FRAME_SIZE*(rSource.subframe_counter)], 
                           0,
                           type_size*RECEIVER_SUB_FRAME_SIZE);        // zeroing what is reproduced
                    
                    //show_frame_data(rSource, COMPLETE, RIGHT); 
                }
          

                // complements left or right channel to stereo
                // specify an empty channel to supplement
                void complement_to_stereo(stereoChnl_e channel)
                {
                      switch(channel)
                      {
                          case RIGHT:
                              for (auto i = 0; i < m_Frame_size; i++)  
                                paired_buffer<i2s_sample_t, BUF_SIZE>::m_Empty_buf[i].r = paired_buffer<i2s_sample_t, BUF_SIZE>::m_Empty_buf[i].l; 
                              break;
        
                          case LEFT:
                              for (auto i = 0; i < m_Frame_size; i++)  
                                paired_buffer<i2s_sample_t, BUF_SIZE>::m_Empty_buf[i].l = paired_buffer<i2s_sample_t, BUF_SIZE>::m_Empty_buf[i].r; 
                              break;
        
                          case STEREO:
                          default:
                          return;
                      }
                }

                // Synchronization is always performed in the decode cycle of received data
                // over radio data, if at the time of decoding termination a subframe is sent over i2s, for example 2
                // then it is shifted to the 3rd in this way one subframe is cut out (not reproduced)
                // for hearing it is not heard, but the sound is smooth.
                void sync(void)
                {
                    ISRDISABLE;

                    if (subframe_counter < RECEIVER_SUB_FRAME_MAX - 2) 
                    {
                        m_Sync_cnt[1]++;
                        subframe_counter = RECEIVER_SUB_FRAME_MAX - 2;
                    }
                    else
                        m_Sync_cnt[0]++; 
		      	
                    ISRENABLE;
                }      
          
                void upsample(i2s_sample_t *out_buf, uint16_t len)
                {
                    // len must be higher than buf_size
                    if(len <= m_Frame_size)
                        return;
                
                }
          
                void downsample(i2s_sample_t *out_buf, uint16_t len)
                {
                    // len must be lower than buf_size
                    if(len >= m_Frame_size)
                        return;
                
                    float downstep = (float)m_Frame_size/(float)len;
                    float curr_step = 0;
                    float k;
                    uint16_t i,n;
                      
                    for (i = 0; i < len; curr_step += downstep, i++)
                    {
                        n = (uint16_t)curr_step;
                        k = curr_step - (float)n;
                        n *= 2;
                        
                        //*out_buf++ = (int16_t)(in[n] + k*(in[n + 2] - in[n]));
                        //правый
                        n++;
                        //*out_buf++ = (int16_t)(in[n] + k*(in[n + 2] - in[n]));
                    }
                    
                    UNUSED(k);
                }
          
                float calculate_dBi(uint32_t* pChannel)
                {
                    double sum = 0;
                    double sample = 0;
                    double rms = 0;
                    
                    // incrementing uint32_t but working with int16_t(left or right channel)
                    for(int i = 0; i < m_Frame_size; i++, pChannel++)
                    {
                        // for int16_t samples we take half of 65535;
                        sample = (double)(*((int16_t*)pChannel));
                        sample /= 32767.0;
                        sample = abs(sample);
                        sum += (sample * sample);
                    }
                    
                    rms = sqrt(sum/m_Frame_size);
                    return (float)(20*log10(rms));
                }

#ifdef FRAMES_DEBUG
                void   show_frame_data(e_Frame frm, stereoChnl_e chnl)   
                { 
                    // to see what is there in the left and right channels on debugging.
                    uint32_t *pCh = get_chnl(frm, chnl); 
                    
                    for(int i = 0; i < paired_buffer<i2s_sample_t, BUF_SIZE>::get_one_size(); i++, pCh++)
                        chnl_dbg_buf[i] = *(reinterpret_cast<int16_t*>(pCh)); 
                
                    memcpy(&frame_dbg_buf[0],(uint32_t*)paired_buffer<i2s_sample_t, BUF_SIZE>::get_complete_buf(),sizeof(uint32_t)*paired_buffer<i2s_sample_t, BUF_SIZE>::get_one_size());
                    memcpy(&frame_dbg_buf[1],(uint32_t*)paired_buffer<i2s_sample_t, BUF_SIZE>::get_empty_buf(),sizeof(uint32_t)*paired_buffer<i2s_sample_t, BUF_SIZE>::get_one_size());
                } 
#endif  //FRAMES_DEBUG
                
         uint8_t   subframe_counter {0};    // counter of subframes into which the buffer is divided

private: 

          size_t  m_Frame_size;
        uint32_t  m_Sync_cnt[2] {0,0};
};

#endif // _FRAME_BUFER_H_

