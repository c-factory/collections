/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The vector interface
    It is a structure in that elements are stored contiguously
*/

#pragma once

#include "allocator.h"
#include "iterator.h"

typedef struct
{
    const size_t size;
    const void * const * data;
} vector_t;

typedef size_t vector_index_t;

vector_t * create_vector();
vector_t * create_vector_ext(const allocator_t *allocator, size_t init_capacity);
void destroy_vector(vector_t *iface);
void destroy_vector_and_content(vector_t *iface, void (*destructor)(void *));
void add_item_to_vector(vector_t *iface, void *item);
void insert_item_into_vector(vector_t *iface, vector_index_t index, void *item);
void * remove_item_from_vector(vector_t *iface, vector_index_t index);
void * get_vector_item(vector_t *iface, vector_index_t index);
void * set_vector_item(vector_t *iface, vector_index_t index, void *item);
vector_index_t index_of_item_of_vector(vector_t *iface, void *item, int (*comparator)(void*, void*));
iterator_t * create_iterator_from_vector(vector_t *iface);
