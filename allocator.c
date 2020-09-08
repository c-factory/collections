#include "allocator.h"
#include <stdio.h>

static void * sys_allocate(size_t size)
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
    sys_allocate,
    sys_release
};

const allocator_t * get_system_allocator()
{
    return &system_allocator;
}
