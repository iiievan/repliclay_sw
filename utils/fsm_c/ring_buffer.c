#include "ring_buffer.h"
#include "string.h"

#define  BUF_ITEM_RETURN (&buffer->type_result[0])

bool ring_buffer_create(ring_buffer* buffer, uint8_t* memory, size_t bufsize, size_t itemsize, uint8_t* typeres)
{
    if (buffer == NULL || memory == NULL || bufsize == 0 || itemsize == 0)
        return false;

    buffer->mem = memory;
    buffer->head = buffer->tail = buffer->avail = 0;
    buffer->buf_size = bufsize;
    buffer->item_size = itemsize;
    buffer->type_result = typeres;

    return true;
}

size_t ring_buffer_get_avail(ring_buffer* buffer)
{
    if (buffer == NULL)
        return 0;
    else
        return buffer->avail;
}

size_t ring_buffer_get_free(ring_buffer* buffer)
{
    if (buffer == NULL)
        return 0;
    else
        return buffer->buf_size - buffer->avail;
}

size_t ring_buffer_get_size(ring_buffer* buffer)
{
    if (buffer == NULL)
        return 0;
    else
        return buffer->buf_size;
}

bool ring_buffer_is_empty(ring_buffer* buffer)
{
    if (buffer == NULL)
        return false;
    else
        return buffer->tail == buffer->head;
}

bool ring_buffer_is_full(ring_buffer* buffer)
{
    if (buffer == NULL)
        return false;
    else
        return 0 == (buffer->buf_size - buffer->avail);
}

void ring_buffer_reset(ring_buffer* buffer)
{
    buffer->head = buffer->tail = buffer->avail = 0;
}

void ring_buffer_reset_to_zero(ring_buffer* buffer)
{
    buffer->head = buffer->tail = buffer->avail = 0;
    memset(buffer->mem, 0, (buffer->buf_size*buffer->item_size));  
}

bool ring_buffer_push(ring_buffer* buffer, uint8_t* data)
{
    if (buffer == NULL || data == NULL)
        return false;

    if (ring_buffer_is_full(buffer))
    {
        return false;
    }

    ring_buffer_set_item(buffer,data,buffer->head);

    buffer->head++;
    buffer->head %= buffer->buf_size;
    buffer->avail++;
    return true;
}

uint8_t* ring_buffer_pop(ring_buffer* buffer)
{
    if (buffer == NULL)
        return NULL;

    if (buffer->avail > 0)
    {
        memcpy(BUF_ITEM_RETURN,ring_buffer_peek(buffer),buffer->item_size);
        memset(ring_buffer_peek(buffer), 0, buffer->item_size);
        buffer->tail++;
        buffer->tail %= buffer->buf_size; // loopback
        buffer->avail++;
    }
    else
        return NULL;

    return BUF_ITEM_RETURN;
}

uint8_t* ring_buffer_pop_item(ring_buffer* buffer,size_t index)
{
    size_t buf_idx;
    size_t buf_idx_p1;
    size_t buf_idx_m1;

    if(index > buffer->avail)
        return NULL;   // null result

    if (buffer->avail > 0)
    {
        if((index + 1) == buffer->avail) // last element in buffer !!index + 1 - because index started from 0, buffer->avail - from 1
        {
            memcpy(BUF_ITEM_RETURN, ring_buffer_peek_item(buffer, (buffer->avail - 1)), buffer->item_size);
            memset(ring_buffer_peek_item(buffer, (buffer->avail - 1)), 0, buffer->item_size);

            buffer->head = (buffer->head) ? (buffer->head - 1) : (buffer->buf_size - 1); // loopback
            buffer->avail--;

            return BUF_ITEM_RETURN;
        }

        if(index == 0) // first element in buffer
        {
            memcpy(BUF_ITEM_RETURN, ring_buffer_peek(buffer), buffer->item_size);
            memset(ring_buffer_peek(buffer), 0, buffer->item_size);
            buffer->tail++;
            buffer->tail %= buffer->buf_size; // loopback
            buffer->avail--;
            return BUF_ITEM_RETURN;
        }

        memcpy(BUF_ITEM_RETURN, 
               ring_buffer_peek_item(buffer, index), 
               buffer->item_size);

        if((index + 1) > (buffer->avail/2))
        {
            size_t remaining_elements = buffer->avail - (index + 1);

            for(size_t i = index; i < (index + remaining_elements); i++)
            {
                buf_idx = (buffer->tail + i) % buffer->buf_size;
                buf_idx_p1 = (buffer->tail + (i + 1)) % buffer->buf_size;

                memcpy(&buffer->mem[buf_idx*buffer->item_size],
                       &buffer->mem[buf_idx_p1*buffer->item_size],
                       buffer->item_size);
            }

            memset(ring_buffer_peek_item(buffer, (buffer->avail - 1)), 0, buffer->item_size);

            buffer->head = (buffer->head ) ? (buffer->head - 1) : (buffer->buf_size - 1); // loopback
            buffer->avail--;
        }
        else
        {
            for(size_t i = index; i > 0; i--)
            {
                buf_idx = (buffer->tail + i) % buffer->buf_size;
                buf_idx_m1 = (buffer->tail + (i - 1)) % buffer->buf_size;

                memcpy(&buffer->mem[buf_idx*buffer->item_size],
                       &buffer->mem[buf_idx_m1*buffer->item_size],
                       buffer->item_size);
            }

            memset(ring_buffer_peek(buffer), 0, buffer->item_size);
            buffer->tail++;
            buffer->tail %= buffer->buf_size; // loopback
            buffer->avail--;
        }
    }

    return BUF_ITEM_RETURN;
}

uint8_t* ring_buffer_peek(ring_buffer* buffer)
{
    if(buffer == NULL || 
       (buffer->tail == buffer->head))  // if is empty
    {
        return NULL;
    }

    return &buffer->mem[buffer->tail*buffer->item_size];
}

uint8_t* ring_buffer_peek_item(ring_buffer* buffer, size_t index)
{
    if(buffer == NULL || 
       (buffer->tail == buffer->head) ||    // if is empty
       (index > buffer->buf_size))          // if index out of range
    {
        return NULL;
    }

    return &buffer->mem[((buffer->tail + index) % buffer->buf_size)*buffer->item_size];
}

uint8_t* ring_buffer_set_item(ring_buffer* buffer, uint8_t* data, size_t index)
{
    if(index > buffer->avail)
        return NULL;   // null result

    memcpy(&buffer->mem[index*buffer->item_size],data,buffer->item_size);
    return BUF_ITEM_RETURN; 
}

