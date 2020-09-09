/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Test for the 'Collections' library
*/

#include "vector.h"
#include <stdio.h>
#include <stdbool.h>

size_t memory_block_count = 0;
bool memory_corruption = false;

typedef struct
{
    size_t size;
} memory_block_t;

static void * dbg_allocate(size_t size)
{
    memory_block_t *block = malloc(size + sizeof(memory_block_t));
    if (!block)
    {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    block->size = size;
    memory_block_count++;
    return block + 1;
}

static void dbg_release(void *ptr, size_t size)
{
    if (ptr)
    {
        memory_block_t *block = (memory_block_t*)ptr - 1;
        if (block->size != size)
        {
            memory_corruption = true;
        }
        free(block);
        memory_block_count--;
    }
}

static allocator_t debug_allocator =
{
    dbg_allocate,
    dbg_release
};

typedef struct 
{
    const char *name;
    bool (*function)();
} test_t;

#define assert_equals(a, b) if (a != b) { result = false; break; }

bool test_create_vector_and_check_size()
{
    bool result = true;
    vector_t *v = create_vector_ext(&debug_allocator, 0);
    do
    {
        for (int k = 0; k < 3; k++)
            add_item_to_vector(v, NULL);
        assert_equals(v->size, 3);
    } while(false);
    destroy_vector(v);
    return result;
}

test_t test_list [] =
{
    { "create vector and check size", test_create_vector_and_check_size }
};

int main(void)
{
    size_t passed = 0, failed = 0;
    size_t k, count = sizeof(test_list) / sizeof(test_t);
    for (k = 0; k < count; k++)
    {
        test_t test = test_list[k];
        bool result = test.function();
        if (memory_block_count)
        {
            printf("[ leak ] %s\n", test.name);
            failed++;
        }
        else if (memory_corruption)
        {
            printf("[ corr ] %s\n", test.name);
            failed++;
        }
        else if (!result)
        {
            printf("[ fail ] %s\n", test.name);
            failed++;
        }
        else
        {
            printf("[  ok  ] %s\n", test.name);
            passed++;
        }
        memory_block_count = 0;
        memory_corruption = false;
    }
    printf("done, passed: %d, failed: %d, total: %d\n", passed, failed, (passed + failed));
}
