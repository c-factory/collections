#pragma once

#include <stdlib.h>

typedef struct
{
    void *(*allocate)(size_t);
    void (*release)(void*, size_t);
} allocator_t;

extern const allocator_t * get_system_allocator();
