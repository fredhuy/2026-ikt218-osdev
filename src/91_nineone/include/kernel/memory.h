#ifndef MEMORY_H
#define MEMORY_H

#include <libc/stdint.h>
#include <libc/stddef.h>


typedef struct {
    uint8_t status;
    uint32_t size;
} alloc_t;

void init_kernel_memory(uint32_t* kernel_end);

void print_memory_layout();

#endif