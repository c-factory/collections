#include "vector.h"
#include <memory.h>

typedef struct
{
    size_t size;
    void **data;
    size_t capacity;
    const allocator_t *allocator;
    void (*destructor)(void *);
} vector_impl_t;

vector_t * vector_create()
{
    const allocator_t *allocator = get_system_allocator();
    vector_impl_t *this = allocator->allocate(sizeof(vector_impl_t));
    this->size = 0;
    this->capacity = 0;
    this->data = NULL;
    this->allocator = allocator;
    this->destructor = NULL;
    return (vector_t *)this;
}

vector_t * vector_create_ext(const allocator_t *allocator, void (*destructor)(void *), size_t init_size)
{
    vector_impl_t *this = allocator->allocate(sizeof(vector_impl_t));
    this->size = init_size;
    this->capacity = init_size;
    this->data = init_size ? allocator->allocate(init_size * sizeof(void*)) : NULL;
    this->allocator = allocator;
    this->destructor = destructor;
    return (vector_t *)this;
}

void vector_destroy(vector_t *iface)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (this->size)
    {
        if (this->destructor)
        {
            size_t k;
            for (k = 0; k < this->size; k++)
            {
                this->destructor(this->data[k]);
            }
        }
        this->allocator->release(this->data, this->size * sizeof(void*));
    }
    this->allocator->release(this, sizeof(vector_impl_t));
}

void vector_push(vector_t *iface, void *item)
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

void * vector_get(vector_t *iface, vector_index_t index)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    return index < this->size ? this->data[index] : NULL;
}

int vector_set(vector_t *iface, vector_index_t index, void *item)
{
    vector_impl_t *this = (vector_impl_t*)iface;
    if (index < this->size)
    {
        if (this->destructor)
            this->destructor(this->data[index]);
        this->data[index] = item;
        return 0;
    }
    return -1;
}
