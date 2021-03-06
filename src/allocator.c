/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Implementation of memory allocators
*/

#include "allocator.h"
#include <stdio.h>

void * nnalloc(size_t size)
{
    void * ptr = malloc(size);
    if (!ptr)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    return ptr;
}

static void sys_release(void *ptr, size_t size)
{
    free(ptr);
}

static allocator_t system_allocator =
{
    nnalloc,
    sys_release
};

const allocator_t * get_system_allocator()
{
    return &system_allocator;
}
