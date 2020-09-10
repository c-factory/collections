/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Test for the 'Collections' library
*/

#include "vector.h"
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

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

static bool test_create_vector_and_check_size()
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

static bool test_create_vector_with_non_zero_capacity()
{
    bool result = true;
    vector_t *v = create_vector_ext(&debug_allocator, 2);
    do
    {
        for (int k = 0; k < 3; k++)
            add_item_to_vector(v, NULL);
        assert_equals(v->size, 3);
    } while(false);
    destroy_vector(v);
    return result;
}

static bool test_vector_push_and_get()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    const int count = sizeof(sequence) / sizeof(int);
    int buff[count];
    vector_t *v = create_vector_ext(&debug_allocator, 0);
    do
    {
        int k;
        for (k = 0; k < count; k++)
            add_item_to_vector(v, &sequence[k]);
        assert_equals(v->size, count);
        for (k = 0; k < count; k++)
            buff[k] = *(int*)get_vector_item(v, k);
        assert_equals(0, memcmp(sequence, buff, sizeof(sequence)));
    } while(false);
    destroy_vector(v);
    return result;
}

static bool test_vector_iterator()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    const int count = sizeof(sequence) / sizeof(int);
    int buff[count];
    vector_t *v = create_vector_ext(&debug_allocator, 0);
    do
    {
        int k;
        for (int k = 0; k < count; k++)
            add_item_to_vector(v, &sequence[k]);
        assert_equals(v->size, count);
        k = 0;
        iterator_t *i = create_iterator_from_vector(v);
        while(has_next_item(i))
            buff[k++] = *(int*)next_item(i);
        destroy_iterator(i);
        assert_equals(k, count);
        assert_equals(0, memcmp(sequence, buff, sizeof(sequence)));
    } while(false);
    destroy_vector(v);
    return result;
}

static bool test_vector_set()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    int sample[] = {3, 5, 17, 11, 13, 19};
    const int count = sizeof(sequence) / sizeof(int);
    vector_t *v = create_vector_ext(&debug_allocator, 4);
    do
    {
        int k;
        for (k = 0; k < count; k++)
            add_item_to_vector(v, &sequence[k]);
        int i0 = 17, i1 = 19;
        int *j = set_vector_item(v, 2, &i0);
        assert_equals(j, &sequence[2]);
        j = set_vector_item(v, 7, &i1);
        assert_equals(j, NULL);
        iterator_t *i = create_iterator_from_vector(v);
        k = 0;
        while(has_next_item(i))
            assert_equals(*(int*)next_item(i), sample[k++]);
        destroy_iterator(i);
    } while(false);
    destroy_vector(v);
    return result;
}

static void int_destructor(void* ptr)
{
    dbg_release(ptr, sizeof(int));
}

static int int_comparator(void *a, void *b)
{
    int *ia = (int*)a;
    int *ib = (int*)b;
    if (*ia > *ib) return 1;
    else if (*ia < *ib) return -1;
    else return 0;
}

static bool test_vector_index_of_and_destructor()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    const int count = sizeof(sequence) / sizeof(int);
    vector_t *v = create_vector_ext(&debug_allocator, 0);
    do
    {
        int k;
        for (k = 0; k < count; k++)
        {
            int *i = dbg_allocate(sizeof(int));
            *i = sequence[k];
            add_item_to_vector(v, i);
        };
        assert_equals(v->size, count);
        int j = 7;
        assert_equals(2, index_of_item_of_vector(v, &j, int_comparator));
        j = 17;
        assert_equals(count, index_of_item_of_vector(v, &j, int_comparator));
    } while(false);
    destroy_vector_and_content(v, int_destructor);
    return result;
}

static bool test_vector_insert()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    int sample[] = {3, 5, 17, 7, 11, 13, 19};
    const int count = sizeof(sequence) / sizeof(int);
    vector_t *v = create_vector_ext(&debug_allocator, 4);
    do
    {
        int k;
        for (k = 0; k < count; k++)
            add_item_to_vector(v, &sequence[k]);
        int i0 = 17, i1 = 19;
        insert_item_into_vector(v, 2, &i0);
        insert_item_into_vector(v, 10, &i1);
        iterator_t *i = create_iterator_from_vector(v);
        k = 0;
        while(has_next_item(i))
            assert_equals(*(int*)next_item(i), sample[k++]);
        destroy_iterator(i);
    } while(false);
    destroy_vector(v);
    return result;
}

static bool test_vector_remove()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    int sample[] = {5, 11};
    const int count = sizeof(sequence) / sizeof(int);
    vector_t *v = create_vector_ext(&debug_allocator, 4);
    do
    {
        int k;
        for (k = 0; k < count; k++)
            add_item_to_vector(v, &sequence[k]);
        int *j;
        j = remove_item_from_vector(v, 2);
        assert_equals(j, &sequence[2]);
        j = remove_item_from_vector(v, 0);
        assert_equals(j, &sequence[0]);
        j = remove_item_from_vector(v, v->size - 1);
        assert_equals(j, &sequence[4]);
        j = remove_item_from_vector(v, 10);
        assert_equals(j, NULL);
        iterator_t *i = create_iterator_from_vector(v);
        k = 0;
        while(has_next_item(i))
            assert_equals(*(int*)next_item(i), sample[k++]);
        destroy_iterator(i);
    } while(false);
    destroy_vector(v);
    return result;
}

test_t test_list [] =
{
    { "create vector and check size", test_create_vector_and_check_size },
    { "create vector with non zero capacity", test_create_vector_with_non_zero_capacity },
    { "test vector's push and get", test_vector_push_and_get },
    { "test vector's iterator", test_vector_iterator },
    { "test vector's index_of and destructor", test_vector_index_of_and_destructor },
    { "test vector's set", test_vector_set },
    { "test vector's insert", test_vector_insert },
    { "test vector's remove", test_vector_remove },
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
