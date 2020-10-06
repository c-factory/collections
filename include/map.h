/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Data structures related to map interface
*/

#pragma once

#include "iterator.h"

typedef  struct
{
    void *key;
    void *value;
} pair_t;

typedef struct
{
    iterator_t base;
} map_iterator_t;

static __inline void destroy_map_iterator(map_iterator_t *iface)
{
    destroy_iterator(&iface->base);
}

static __inline bool has_next_pair(map_iterator_t *iface)
{
    return has_next_item(&iface->base);
}

static __inline const pair_t * next_pair(map_iterator_t *iface)
{
    return (const pair_t*)next_item(&iface->base);
}
