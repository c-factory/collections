#pragma once

#include <stdbool.h>

typedef struct iterator_t iterator_t;

struct iterator_t
{
    void (*destroy)(iterator_t *iface);
    bool (*has_next)(iterator_t *iface);
    void* (*next)(iterator_t *iface);
};

static __inline void destroy_iterator(iterator_t *iface)
{
    iface->destroy(iface);
}

static __inline bool has_next_item(iterator_t *iface)
{
    return iface->has_next(iface);
}

static __inline void * next_item(iterator_t *iface)
{
    return iface->next(iface);
}
