#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

template <size_t BUF_SIZE = 16>
class ring_buffer
{
public:    
                      ring_buffer() : m_Size(BUF_SIZE) { reset(); }

                char  get_tail() 
                {
                    volatile char result = -1; 
                
                    result = *curr_data();
                
                    pop();
                
                    return result;
                }
 
                size_t  add(char* data, size_t len)
                {
                        __disable_interrupt();
                        
                        uint32_t i;                      
                    
                        for (i = 0; i < len; i++) 
                        {
                            if (is_full())
                                break;
                    
                            push(data[i]);
                        }
                    
                        __enable_interrupt();
                    
                        return i;
                }

                size_t  get(char* data, size_t len)
                {
                      __disable_interrupt();

                      volatile uint32_t bytes_avail = get_avail();
                      
                      if (len > bytes_avail) { len = bytes_avail; }
                  
                      if (len > 0) 
                      {       
                          for (int idx = 0; idx < len; idx++ ) 
                          { data[idx] = get_tail(); }
                      }
                  
                      __enable_interrupt();
                  
                      return len;                  
                }

                char  add_one(char& c)
                {
                    __disable_interrupt();
                
                    char result = -1;
                
                    // if the buffer is full, then spit out one character
                    if (is_full()) { result = get_tail(); }

                    push(c); 
                
                    __enable_interrupt();  
                
                    return result;
                }

                char  get_one()
                {
                      __disable_interrupt();

                      char result = -1;

                      if (!is_empty()) { result = get_tail(); }

                      __enable_interrupt();

                      return result;
                }

                char  peek_one() // Look what is putted in buffer, without take element
                {
                      __disable_interrupt();

                      char result = *curr_data();
                  
                      __enable_interrupt();
                      
                      return result;                  
                }                           

    inline      size_t  get_avail() const { return m_Avail; }                  // Return available data in ringbuffer 
    inline      size_t  get_free()  const { return (m_Size - m_Avail); }       // Return available space in ringbuffer     
    inline      size_t  get_size()  const { return m_Size; }                   // Return size of ringbuffer  
    inline        bool  is_empty()  const { return  m_Tail == m_Head; }        // Test if the ringbuffer is empty.
    inline        bool  is_full()   const { return  0 == get_free(); }         // Test if the ringbuffer is full.
    inline        void  reset()           { m_Head = m_Tail = m_Avail = 0; }   // reset(but not clear) data in buffer
    inline        void  reset_to_zero()              
                  { 
                      // reset to zero data in buffer
                      m_Head = m_Tail = m_Avail = 0;
                      memset(m_BUF, 0, sizeof(m_BUF)); 
                  }    
    inline        void  set_head(size_t value) { m_Head = m_Avail = value; }    // this method may uses in ISR buffer fill.

    inline const char* curr_data() const { return &(m_BUF[m_Tail]); }
    inline       char* curr_data()       { return &(m_BUF[m_Tail]); }

    // ejects the element from the buffer
    inline        void  pop()
                  {
                      if (get_avail() == 0) return;
                      if (get_avail() == 1) reset();
                      else
                      {
                         m_Tail = (m_Tail + 1) % m_Size;
                         m_Avail--;
                      }
                  }

    // add element to buffer
    inline        void  push(char& data)
                  {
                        m_BUF[m_Head] = data;
                        m_Head = (m_Head + 1) % m_Size;
                        
                        // move tail with data loss if buffer is full
                        // while the number of available elements remains equal to m_Size
                        if (is_full())
                            m_Tail = (m_Tail + 1) % m_Size;
                        else
                            m_Avail++;
                  }
				  
	inline        bool  push_for_dma()
                  {
                        m_Head = (m_Head + 1) % m_Size;
                        
                        // move tail with data loss if buffer is full
                        // while the number of available elements remains equal to m_Size
                        if (is_full())
                        { return false; }
                        else
                        { 
						  m_Avail++; 
						  return true;						
					   }
                  }

                  char* get_buf_pointer(void) {  return &m_BUF[0];  }  

private:
                  char  m_BUF[BUF_SIZE] {0};  // ring buffer itself    
    const       size_t  m_Size;               // buffer size
                size_t  m_Avail;              // available elements in buffer
                size_t  m_Head;               
                size_t  m_Tail;              
};

#endif  // _RINGBUFFER_H