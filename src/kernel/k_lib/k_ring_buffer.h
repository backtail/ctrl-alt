#ifndef _K_RINGBUFFER_H_
#define _K_RINGBUFFER_H_

#include "stdint.h"
#include "stddef.h"
#include "stdbool.h"

/// @brief Defines a ring buffer structure
typedef struct
{
    uint8_t *buffer; ///< Pointer to the buffer array (external)
    size_t head;     ///< Index of the head
    size_t tail;     ///< Index of the tail
    size_t max;      ///< Maximum size of the buffer
    bool full;       ///< Flag to indicate if the buffer is full
} ring_buffer_t;

/// @brief Function to initialize the ring buffer with a specified size and external buffer
/// @param rb Pointer to the ring buffer structure
/// @param buffer Pointer to the external buffer array
/// @param size Size of the external buffer
inline void ring_buffer_init(ring_buffer_t *rb, uint8_t *buffer, size_t size)
{
    rb->buffer = buffer;
    rb->max = size;
    rb->head = 0;
    rb->tail = 0;
    rb->full = false;
}

/// @brief Function to check if the ring buffer is empty
/// @param rb Pointer to the ring buffer structure
/// @return 1 if the buffer is empty, 0 otherwise
inline bool ring_buffer_empty(ring_buffer_t *rb)
{
    if (!rb->full && (rb->head == rb->tail))
        return 1;
    else
        return 0;
}

/// @brief Function to check if the ring buffer is full
/// @param rb Pointer to the ring buffer structure
/// @return 1 if the buffer is full, 0 otherwise
inline bool ring_buffer_full(ring_buffer_t *rb)
{
    return rb->full;
}

/// @brief Function to put an element into the ring buffer
/// @param rb Pointer to the ring buffer structure
/// @param data The data to be added to the buffer
/// @note If the buffer is full, the oldest data will be overwritten
void ring_buffer_put(ring_buffer_t *rb, uint8_t data);

/// @brief Function to get an element from the ring buffer
/// @param rb Pointer to the ring buffer structure
/// @return The data retrieved from the buffer
uint8_t ring_buffer_get(ring_buffer_t *rb);

/// @brief Function to reset the ring buffer
/// @param rb Pointer to the ring buffer structure
void ring_buffer_reset(ring_buffer_t *rb);

#endif // _K_RINGBUFFER_H_