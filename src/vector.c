/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Implementation of the vector interface
*/

#include "vector.h"
#include <memory.h>

typedef struct
{
    size_t size;
    void **data;
    size_t capacity;
    const allocator_t *allocator;
} vector_impl_t;

vector_t * create_vector()
{
    const allocator_t *allocator = get_system_allocator();
    vector_impl_t *this = allocator->allocate(sizeof(vector_impl_t));
    this->size = 0;
    this->capacity = 0;
    this->data = NULL;
    this->allocator = allocator;
    return (vector_t *)this;
}

vector_t * create_vector_ext(const allocator_t *allocator, size_t init_capacity)
{
    vector_impl_t *this = allocator->allocate(sizeof(vector_impl_t));
    this->size = 0;
    this->capacity = init_capacity;
    this->data = init_capacity ? allocator->allocate(init_capacity * sizeof(void*)) : NULL;
    this->allocator = allocator;
    return (vector_t *)this;
}

void destroy_vector(vector_t *iface)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (this->data)
    {
        this->allocator->release(this->data, this->capacity * sizeof(void*));
    }
    this->allocator->release(this, sizeof(vector_impl_t));
}

void destroy_vector_and_content(vector_t *iface, void (*destructor)(void *))
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (this->data)
    {
        size_t k;
        for (k = 0; k < this->size; k++)
        {
            destructor(this->data[k]);
        }
        this->allocator->release(this->data, this->size * sizeof(void*));
    }
    this->allocator->release(this, sizeof(vector_impl_t));
}

void add_item_to_vector(vector_t *iface, void *item)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (this->size == this->capacity)
    {
        if (this->capacity)
        {
            this->capacity *= 2;
            void **tmp = this->allocator->allocate(this->capacity * sizeof(void*));
            size_t old_size = this->size * sizeof(void*);
            memcpy(tmp, this->data, old_size);
            this->allocator->release(this->data, old_size);
            this->data = tmp;
        }
        else
        {
            this->capacity = 16;
            this->data = this->allocator->allocate(this->capacity * sizeof(void*));
        }
    }
    this->data[this->size++] = item;
}

void insert_item_into_vector(vector_t *iface, vector_index_t index, void *item)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (index < this->size)
    {
        if (this->size == this->capacity)
        {
            void **tmp;
            size_t left_size = index;
            size_t right_size = this->size - left_size;
            this->capacity = this->capacity * 2;
            tmp = this->allocator->allocate(this->capacity * sizeof(void*));
            if (left_size) memcpy(tmp, this->data, left_size * sizeof(void*));
            tmp[left_size] = item;
            memcpy(tmp + left_size + 1, this->data + left_size, right_size * sizeof(void*));
            this->allocator->release(this->data, this->size * sizeof(void*));
            this->data = tmp;
            this->size++;
        }
        else
        {
            size_t k;
            for (k = this->size; k > index; k--)
                this->data[k] = this->data[k - 1];
            this->data[index] = item;
            this->size++;
        }        
    }
    else
    {
        add_item_to_vector(iface, item);
    }
}

void * remove_item_from_vector(vector_t *iface, vector_index_t index)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (index >= this->size)
        return NULL;

    void *item = this->data[index];
    size_t k;
    for (k = index; k < this->size - 1; k++)
        this->data[k] = this->data[k + 1];
    this->size--;
    return item;
}

void * get_vector_item(vector_t *iface, vector_index_t index)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    return index < this->size ? this->data[index] : NULL;
}

void * set_vector_item(vector_t *iface, vector_index_t index, void *item)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (index < this->size)
    {
        void *old_item = this->data[index];
        this->data[index] = item;
        return old_item;
    }
    else
    {
        add_item_to_vector(iface, item);
        return NULL;
    }
}

vector_index_t index_of_item_of_vector(vector_t *iface, void *item, int (*comparator)(void*, void*))
{
    vector_impl_t *this = (vector_impl_t*)iface;
    vector_index_t k;
    if (comparator)
    {
        for (k = 0; k < this->size; k++)
        {
            if (0 == comparator(item, this->data[k]))
                return k;
        }
    }
    else
    {
        for (k = 0; k < this->size; k++)
        {
            if (item == this->data[k])
                return k;
        }
    }
    return this->size;
}

typedef struct
{
    void (*destroy)(iterator_t *iface);
    bool (*has_next)(iterator_t *iface);
    void* (*next)(iterator_t *iface);
    vector_impl_t *vector;
    vector_index_t index;
} vector_iterator_t;

static void destroy_vector_iterator(iterator_t *iface)
{
    vector_iterator_t *this = (vector_iterator_t*)iface;
    this->vector->allocator->release(this, sizeof(vector_iterator_t));
}

static bool vector_iterator_has_next_item(iterator_t *iface)
{
    vector_iterator_t *this = (vector_iterator_t*)iface;
    return this->index < this->vector->size;
}

static void * vector_iterator_get_next_item(iterator_t *iface)
{
    vector_iterator_t *this = (vector_iterator_t*)iface;
    if (this->index < this->vector->size)
        return this->vector->data[this->index++];
    return NULL;
}

iterator_t * create_iterator_from_vector(vector_t *iface)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    vector_iterator_t *iter = this->allocator->allocate(sizeof(vector_iterator_t));
    iter->destroy = destroy_vector_iterator;
    iter->has_next = vector_iterator_has_next_item;
    iter->next = vector_iterator_get_next_item;
    iter->vector = this;
    iter->index = 0;
    return (iterator_t*)iter;
}
