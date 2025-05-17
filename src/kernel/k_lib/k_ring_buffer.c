#include "k_ring_buffer.h"

#include "stdbool.h"

void ring_buffer_put(ring_buffer_t *rb, uint8_t data)
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

uint8_t ring_buffer_get(ring_buffer_t *rb)
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

void ring_buffer_reset(ring_buffer_t *rb)
{
    if (rb)
    {
        rb->head = 0;
        rb->tail = 0;
        rb->full = false;
    }
}