#include "k_ring_buffer.h"

#include "stdbool.h"

// Function to add an element to the ring buffer
void ring_buffer_put(RingBuffer *rb, uint8_t data)
{
    rb->buffer[rb->head] = data;

    if (rb->full)
    {
        rb->tail = (rb->tail + 1) % rb->max; // Overwrite the oldest data
        // or implement callback to handle error
    }

    rb->head = (rb->head + 1) % rb->max;
    rb->full = (rb->head == rb->tail);
}

// Function to get an element from the ring buffer
uint8_t ring_buffer_get(RingBuffer *rb)
{
    if (ring_buffer_empty(rb))
    {
        // implement callback to handle error
    }

    uint8_t data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->max;
    rb->full = false;

    return data;
}

// Function to reset the ring buffer
void ring_buffer_reset(RingBuffer *rb)
{
    if (rb)
    {
        rb->head = 0;
        rb->tail = 0;
        rb->full = false;
    }
}