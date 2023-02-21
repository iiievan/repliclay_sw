#ifndef _PAIRED_BUFFER_H_
#define _PAIRED_BUFFER_H_

#include <cstring>

template <typename T, size_t BUF_SIZE = 16UL >
class paired_buffer;

template <typename T, size_t BUF_SIZE>
class paired_buffer
{
public:    
                    paired_buffer()
                    :m_Complete_buf(BUFFER[0]), m_Empty_buf(BUFFER[1]) 
                    {     
                       m_Size = BUF_SIZE;    
                       reset();
                    } 
    
inline        void  reset()                { memset(BUFFER, 0, sizeof(T)*m_Size*2); m_Avail = 0; }   // reset whole buffer                         
inline        void  clear_empty()          { memset(m_Empty_buf, 0, sizeof(T)*m_Size);}              // reset only empty buffer
inline        void  clear_complete()       { memset(m_Complete_buf, 0, sizeof(T)*m_Size);}           // reset only complete buffer

inline      size_t  get_avail()      const { return m_Avail; }                 // Return available data in both buffers
inline      size_t  get_free()       const { return (m_Size*2 - m_Avail); }    // Return available space in both buffers     
inline      size_t  get_one_size()   const { return m_Size; }                  // Return size of 1 buffer
inline      size_t  get_both_size()  const { return m_Size*2; }                // Return size of 1 buffer
inline        bool  is_full()        const { return  0 == get_free(); }        // Test if both buffers is full. 
 
                 T* get_complete_buf(void) {  return m_Complete_buf; }         // return pointer on complete buffer
                 T* get_empty_buf(void)    {  return m_Empty_buf; }            // return pointer on empty buffer

                 // swap pointers to buffers
                 // now the one that was for filling - for sending
                 // and what was sent is filled in.
                 // returns a pointer to the playback buffer (i.e. filled buffer).
inline           T* switch_buffers() 
                 {
                     if (m_Complete_buf == BUFFER[0])
                     {
                         m_Empty_buf = BUFFER[0];
                         m_Complete_buf = BUFFER[1];
                     }
                     else
                     {
                         m_Empty_buf = BUFFER[1];
                         m_Complete_buf = BUFFER[0];
                     }
                     
                     return m_Complete_buf;
                 }
            
            paired_buffer &operator=(paired_buffer &right)
            {
                T* ptr;
                
                if(&right != this)
                {
                    // fill the current empty frame of this buffer with a ready (filled) frame
                    // buffer from which we take data.
                    ptr = right.get_complete_buf();
                    
                    for(uint32_t i = 0; i < m_Size; i++)
                    {
                        m_Empty_buf[i] = ptr[i];
                    }      
                }
                
                return *this;   // for the possibility of coupling
            }             
            
            T& operator[](int i)
            {  
                if(i > 2*m_Size)
                    return BUFFER[0][0];
                
                if(i < m_Size)
                    return &m_Empty_buf[i];  
                else
                    return &m_Complete_buf[i - m_Size];                   
            }

inline      bool  increment(uint32_t index = 1)
            { 
                if (is_full())
                    return false;
                else
                { 
                    m_Avail += index; 
                    return true;                      
                }
            } 

inline      bool  decrement(uint32_t index = 1)
            {  
                if(m_Avail >= index)
                {
                    m_Avail -= index;
                    return true;  
                } 
                else
                    return false;                    
            }        
          
protected:
                         
       T BUFFER[2][BUF_SIZE] {0};  //double buffer, while one is filled, the second sends data.

private:
       T* m_Complete_buf;  // pointer to the current frame being sent
       T* m_Empty_buf;     // pointer to the next frame, to fill it before sending.
  size_t  m_Size;
  size_t  m_Avail;
};

#endif // _PAIRED_BUFFER_H_

