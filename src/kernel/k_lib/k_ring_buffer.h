#ifndef _K_RINGBUFFER_H_
#define _K_RINGBUFFER_H_

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

// Ring buffer structure
typedef struct
{
    uint8_t *buffer; // Pointer to the buffer array (external)
    size_t head;     // Index of the head
    size_t tail;     // Index of the tail
    size_t max;      // Maximum size of the buffer
    bool full;       // Flag to indicate if the buffer is full
} RingBuffer;

// Function to initialize the ring buffer with a specified size and external buffer
inline void ring_buffer_init(RingBuffer *rb, uint8_t *buffer, size_t size)
{
    rb->buffer = buffer;
    rb->max = size;
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

// Function to check if the ring buffer is empty
inline bool ring_buffer_empty(RingBuffer *rb)
{
    if (!rb->full && (rb->head == rb->tail))
        return 1;
    else
        return 0;
}

// Function to check if the ring buffer is full
inline bool ring_buffer_full(RingBuffer *rb)
{
    return rb->full;
}

void ring_buffer_put(RingBuffer *rb, uint8_t data);
uint8_t ring_buffer_get(RingBuffer *rb);
void ring_buffer_reset(RingBuffer *rb);

#endif // _K_RINGBUFFER_H_