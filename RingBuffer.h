#ifndef RINGBUFFER_H_INCLUDED
#define RINGBUFFER_H_INCLUDED

#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 100

volatile char RING_BUFFER[BUF_SIZE];
volatile uint8_t buf_pointer;

void buf_push_char(char data);
char buf_pop_char();
bool buf_isEmpty();

#endif // RINGBUFFER_H_INCLUDED
