#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include "stddef.h"
#include "stdint.h"
#include <string.h>         // for memcpy


template <typename T, size_t BUF_SIZE = 16>
class ring_buffer
{
public:
    ring_buffer() : m_Size(BUF_SIZE)
    {
        m_Head = m_Tail = m_Avail = 0;
        memset(m_BUF, 0, sizeof(m_BUF));
    }

    inline size_t get_avail() const { return m_Avail; }            // Return available data in ringbuffer
    inline size_t get_free() const { return (m_Size - m_Avail); }  // Return available space in ringbuffer
    inline size_t get_size() const { return m_Size; }              // Return size of ringbuffer
    inline bool   is_empty() const { return m_Tail == m_Head; }    // Test if the ringbuffer is empty.
    inline bool   is_full() const { return 0 == get_free(); }      // Test if the ringbuffer is full.
    inline void   reset() { m_Head = m_Tail = m_Avail = 0; }       // reset(but not clear) data in buffer
    
    inline void   reset_to_zero()
    {
        // reset to zero data in buffer
        m_Head = m_Tail = m_Avail = 0;
        memset(m_BUF, 0, sizeof(m_BUF));
    }

    // add element to buffer
    bool push(T& data)
    {
        if (is_full()) 
        {
            return false;
        }

        m_BUF[m_Head] = data;
        m_Head++;
        m_Head %= m_Size; // loopback
        m_Avail++; 

        return true;
    }

    // ejects the element from the buffer
    T pop()
    {
        T result;

        if (m_Avail > 0)
        {
            result = m_BUF[m_Tail];
            memset(&m_BUF[m_Tail], 0, sizeof(T));
            m_Tail++;         
            m_Tail %= m_Size; // loopback
            m_Avail--;           
        }

        return result;
    }

    // ejects the element from the buffer by index
    T pop_item(size_t index)
    {
        T result;
        size_t buf_idx;
        size_t buf_idx_p1;
        size_t buf_idx_m1;

        if(index > m_Avail)
            return result;   // null result

        if (m_Avail > 0)
        {
            if((index + 1) == m_Avail) // last element in buffer !!index + 1 - because index started from 0, m_Avail - from 1
            {
                result = *peek_item(m_Avail - 1);
                memset(peek_item(m_Avail - 1), 0, sizeof(T));

                (m_Head) ? (m_Head--) : m_Head = (m_Size - 1); // loopback
                m_Avail--;

                return result;
            }

            if(index == 0) // first element in buffer
            {
                result = m_BUF[m_Tail];
                memset(&m_BUF[m_Tail], 0, sizeof(T));
                m_Tail++;
                m_Tail %= m_Size; // loopback
                m_Avail--;
                return result;
            }

            result = m_BUF[(m_Tail + index) % m_Size];

            if((index + 1) > (m_Avail/2))
            {
                size_t remaining_elements = m_Avail - (index + 1);

                for(size_t i = index; i < (index + remaining_elements); i++)
                {
                    buf_idx = (m_Tail + i) % m_Size;
                    buf_idx_p1 = (m_Tail + (i + 1)) % m_Size;

                    memcpy(&m_BUF[buf_idx],&m_BUF[buf_idx_p1],sizeof(T));
                }

                memset(peek_item(m_Avail - 1), 0, sizeof(T));

                (m_Head) ? (m_Head--) : m_Head = (m_Size - 1); // loopback
                m_Avail--;
            }
            else
            {
                for(size_t i = index; i > 0; i--)
                {
                    buf_idx = (m_Tail + i) % m_Size;
                    buf_idx_m1 = (m_Tail + (i - 1)) % m_Size;

                    memcpy(&m_BUF[buf_idx],&m_BUF[buf_idx_m1],sizeof(T));
                }

                memset(&m_BUF[m_Tail], 0, sizeof(T));
                m_Tail++;
                m_Tail %= m_Size; // loopback
                m_Avail--;
            }
        }

        return result;
    }


    // Look first(tail) element putted in buffer
    T* peek()  
    {
        if(is_empty())
            return nullptr;

        return &(m_BUF[m_Tail]);
    }

    // Look what is putted in buffer by index
    T* peek_item(size_t index)  
    {
        if(is_empty() || index > m_Size)
            return nullptr;

        return &(m_BUF[(m_Tail + index) % m_Size]);
    }

    // overwrite existing element in queue
    void write_item(size_t index, T& data) 
    {                
        if (data > m_Size) { return; }

        m_BUF[(m_Tail + index) % m_Size] = data;
    }

private:
    T            m_BUF[BUF_SIZE];     // ring buffer itself
    const size_t m_Size;              // buffer size
    size_t       m_Avail;             // available elements in buffer
    size_t       m_Head;
    size_t       m_Tail;
};

#endif  //_RINGBUFFER_H
