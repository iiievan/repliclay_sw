#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "stddef.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8_t* mem;           // pointer to buffer memory static array(or allocated in memory)
     size_t  buf_size;      // size of buffer in item_size units
     size_t  item_size;     // size of one item in buffer in uint8_t units   
     size_t  head;          // head index
     size_t  tail;          // tail index
     size_t  avail;         // available elements in buffer
    uint8_t* type_result;   // array of returned result some functions with item_size length
} ring_buffer;

    /**
     * @brief  This api initiates the structure of ring_buffer with the values necessary for its operability
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * @param  memory - pointer to buffer memory static array(or allocated in memory)
     * @param  bufsize - size of buffer in item_size units
     * @param  itemsize - size of one item in buffer in uint8_t units
     * @param  typeres - pointer on array of returned result some functions with item_size length
     *
     *  'typeres' - this array must be allocated statically or dinamically before ring buffer used
     * 
     *  @return  return sucsessfully result of the creation
     *           true - buffer created sucsessfully
     *           false - buffer createin fault
     */
   bool  ring_buffer_create(ring_buffer* buffer, uint8_t* memory, size_t bufsize, size_t itemsize, uint8_t* typeres);
    
    /**
     * @brief  Gets value of available elements in buffer
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  available elements in buffer
     */
 size_t  ring_buffer_get_avail(ring_buffer* buffer);

    /**
     * @brief  Get the number of free cells in the buffer
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  number of empty cells in buffer
     */
 size_t  ring_buffer_get_free(ring_buffer* buffer);

     /**
     * @brief  Get the size of the buffer in it items cells(one item 'itemsize' length )
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  number of whole cells in buffer
     */
 size_t  ring_buffer_get_size(ring_buffer* buffer);  

    /**
     * @brief  Check if buffer no data available
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  status:
     *          true - buffer is empty
     *          false - buffer have data
     */ 
   bool  ring_buffer_is_empty(ring_buffer* buffer);

    /**
     * @brief  Check if buffer no free cells available
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  status:
     *          true - buffer have no empty cells
     *          false - buffer have empty cells
     */ 
   bool  ring_buffer_is_full(ring_buffer* buffer);

    /**
     * @brief  Set buffer head equal it tail. 
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     */ 
   void  ring_buffer_reset(ring_buffer* buffer);            

    /**
     * @brief  Set buffer head equal it tail and zero the entire memory array(all bytes)
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     */
   void  ring_buffer_reset_to_zero(ring_buffer* buffer); 

    /**
     * @brief  puts element in bufffer head
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  status:
     *          true - buffer push data was successful
     *          false - buffer push data was failed
     */
   bool  ring_buffer_push(ring_buffer* buffer, uint8_t* data);

    /**
     * @brief  return element from buffer tail
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  one item from buffer tail, this value is located at 'type_result',
     *          and must be removed from it as soon as possible
     */ 
uint8_t* ring_buffer_pop(ring_buffer* buffer);

    /**
     * @brief return element from buffer by index
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * @param  index - index of available from 0 to ('buf_size' - 1)h
     * 
     * @return  one item from buffer by index, this value is located at 'type_result',
     *          and must be copied from it as soon as possible
     */  
uint8_t* ring_buffer_pop_item(ring_buffer* buffer, size_t index);  

    /**
     * @brief return a pointer on buffer element in his tail
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * 
     * @return  pointer on buffer element  in his tail.
     *          it must be understood that the length of the element is 'item_size' in bytes
     */
uint8_t* ring_buffer_peek(ring_buffer* buffer);

    /**
     * @brief return a pointer on buffer element by index 
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * @param  index - index of available from 0 to ('buf_size' - 1)
     * 
     * @return  pointer on buffer element in by it index
     *          it must be understood that the length of the element is 'item_size' in bytes
     */
uint8_t* ring_buffer_peek_item(ring_buffer* buffer, size_t index);

    /*
     * @brief rewrite element in buffer by index  
     * 
     * @param  buffer - ring_buffer struct ptr to operte with
     * @param  data   - pointer to element data for an 'item_size'-byte write
     * @param  index  - index of available from 0 to ('buf_size' - 1)
     * 
     * @return  pointer on buffer element in by it index
     *          it must be understood that the length of the element is 'item_size' in bytes
     */
uint8_t* ring_buffer_set_item(ring_buffer* buffer, uint8_t* data, size_t index);

#ifdef __cplusplus
}
#endif

#endif  // _RINGBUFFER_H
