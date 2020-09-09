/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The descriptor of memory allocators
*/

#pragma once

#include <stdlib.h>

typedef struct
{
    void *(*allocate)(size_t);
    void (*release)(void*, size_t);
} allocator_t;

extern const allocator_t * get_system_allocator();
