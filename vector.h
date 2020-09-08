#pragma once

#include "allocator.h"

typedef struct
{
    const size_t size;
    const void const * data;
} vector_t;

typedef size_t vector_index_t;

vector_t * vector_create();
vector_t * vector_create_ext(const allocator_t *allocator, size_t init_size);
void vector_destroy(vector_t *iface);
void vector_destroy_all(vector_t *iface, void (*destructor)(void *));
void vector_push(vector_t *iface, void *item);
void * vector_get(vector_t *iface, vector_index_t index);
void * vector_set(vector_t *iface, vector_index_t index, void *item);
