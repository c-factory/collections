/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    Test for the 'Collections' library
*/

#include "vector.h"
#include "tree_set.h"
#include "tree_map.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
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

#define assert_equals(a, b) if (a != b) { result = false; goto done; }
#define assert_diff(a, b) if (a == b) { result = false; goto done; }

static void string_destructor(void* ptr)
{
    dbg_release(ptr, strlen((char*)ptr) + 1);
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

// --- vector -----------------------------------------------------------------

static bool test_create_vector_and_check_size()
{
    bool result = true;
    vector_t *v = create_vector_ext(&debug_allocator, 0);
    for (int k = 0; k < 3; k++)
        add_item_to_vector(v, NULL);
    assert_equals(v->size, 3);
done:
    destroy_vector(v);
    return result;
}

static bool test_create_vector_with_non_zero_capacity()
{
    bool result = true;
    vector_t *v = create_vector_ext(&debug_allocator, 2);
    for (int k = 0; k < 3; k++)
        add_item_to_vector(v, NULL);
    assert_equals(v->size, 3);
done:
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
    int k;
    for (k = 0; k < count; k++)
        add_item_to_vector(v, &sequence[k]);
    assert_equals(v->size, count);
    for (k = 0; k < count; k++)
        buff[k] = *(int*)get_vector_item(v, k);
    assert_equals(0, memcmp(sequence, buff, sizeof(sequence)));
done:
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
done:
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
done:
    destroy_vector(v);
    return result;
}

static bool test_vector_index_of_and_destructor()
{
    bool result = true;
    int sequence[] = {3, 5, 7, 11, 13};
    const int count = sizeof(sequence) / sizeof(int);
    vector_t *v = create_vector_ext(&debug_allocator, 0);
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
done:
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
done:
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
done:
    destroy_vector(v);
    return result;
}

// --- tree-set ---------------------------------------------------------------

static const char* tree_set_data[] =
{
    "file", "selection", "view", "point", "anime", "terminal", "terminator", "goat",
    "c-factory", "iterator", "vector", "allocator", "4chan"
};

static const char* tree_set_sorted_data[] =
{
    "4chan", "allocator", "anime", "c-factory", "file", "goat", "iterator",
    "point", "selection", "terminal", "terminator", "vector", "view"  
};

static const size_t size_of_tree_set_data = sizeof(tree_set_data) / sizeof(char*);

static bool test_create_and_iterate_tree_set()
{
    bool result = true;

    tree_set_t *ts = create_tree_set_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < size_of_tree_set_data; k++)
        add_item_to_tree_set(ts, (void*)tree_set_data[k]);
    assert_equals(ts->size, size_of_tree_set_data);
    k = 0;
    iterator_t *i = create_iterator_from_tree_set(ts);
    while(has_next_item(i))
    {
        const char *s = (const char*)next_item(i);
        assert_equals(0, strcmp(s, tree_set_sorted_data[k]));
        k++;
    }
    destroy_iterator(i);
done:
    destroy_tree_set(ts);
    return result;
}

typedef struct
{
    size_t k;
    bool error;
} tree_set_traversal_data_t;

void tree_set_callback(void *obj, void *item)
{
    tree_set_traversal_data_t *data = (tree_set_traversal_data_t*)obj;
    if (0 != strcmp(tree_set_sorted_data[data->k], (char*)item))
        data->error = true;
    data->k++;
}

static bool test_create_and_traverse_tree_set()
{
    bool result = true;
    tree_set_t *ts = create_tree_set_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < size_of_tree_set_data; k++)
        add_item_to_tree_set(ts, (void*)tree_set_data[k]);
    tree_set_traversal_data_t data = {0};
    traverse_over_tree_set(ts, tree_set_callback, &data);
    assert_equals(data.error, false);
    assert_equals(data.k, size_of_tree_set_data);
done:
    destroy_tree_set(ts);
    return result;
}

static bool test_create_and_destroy_tree_set_with_content()
{
    bool result = true;
    tree_set_t *ts = create_tree_set_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < size_of_tree_set_data; k++)
    {
        size_t len = strlen(tree_set_data[k]);
        char *copy = debug_allocator.allocate(len + 1);
        memcpy(copy, tree_set_data[k], len + 1);
        add_item_to_tree_set(ts, (void*)copy);
    }
    assert_equals(ts->size, size_of_tree_set_data);
    k = 0;
    iterator_t *i = create_iterator_from_tree_set(ts);
    while(has_next_item(i))
    {
        const char *s = (const char*)next_item(i);
        assert_equals(0, strcmp(s, tree_set_sorted_data[k]));
        k++;
    }
    destroy_iterator(i);
done:
    destroy_tree_set_and_content(ts, string_destructor);
    return result;
}

static bool test_create_tree_set_and_add_data_twice()
{
    bool result = true;
    tree_set_t *ts = create_tree_set_ext((void*)strcmp, &debug_allocator);
    size_t k;
    bool ret_val;
    for (k = 0; k < size_of_tree_set_data; k++)
    {
        ret_val = add_item_to_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, true);
    }
    for (k = 0; k < size_of_tree_set_data; k++)
    {
        ret_val = add_item_to_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, false);
    }
    assert_equals(ts->size, size_of_tree_set_data);
done:
    destroy_tree_set(ts);
    return result;
}

static bool test_seek_and_destroy_data_in_tree_set()
{
    bool result = true;
    tree_set_t *ts = create_tree_set_ext((void*)strcmp, &debug_allocator);
    size_t k;
    bool ret_val;
    for (k = 0; k < size_of_tree_set_data; k++)
        add_item_to_tree_set(ts, (void*)tree_set_data[k]);
    assert_equals(ts->size, size_of_tree_set_data);
    for (k = 0; k < size_of_tree_set_data; k++)
    {
        ret_val = is_there_item_in_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, true);
        ret_val = remove_item_from_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, true);
        ret_val = is_there_item_in_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, false);
        ret_val = remove_item_from_tree_set(ts, (void*)tree_set_data[k]);
        assert_equals(ret_val, false);
    }
    assert_equals(ts->size, 0);
done:
    destroy_tree_set(ts);
    return result;
}

// --- tree map ---------------------------------------------------------------

static const char** map_keys = tree_set_data;
static const size_t count_of_map_keys = size_of_tree_set_data;
static const char** map_sorted_keys = tree_set_sorted_data;
static const int map_values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const int map_sorted_values[] = {13, 12, 5, 9, 1, 8, 10, 4, 2, 6, 7, 11, 3};

static bool test_create_and_iterate_tree_map()
{
    bool result = true;
    tree_map_t *tm = create_tree_map_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < count_of_map_keys; k++)
        add_pair_to_tree_map(tm, (void*)map_keys[k], (void*)&map_values[k]);
    assert_equals(tm->size, count_of_map_keys);
    k = 0;
    map_iterator_t *i = create_iterator_from_tree_map(tm);
    while(has_next_pair(i))
    {
        const pair_t *p = next_pair(i);
        assert_equals(0, strcmp(p->key, map_sorted_keys[k]));
        assert_equals(*((int*)p->value), map_sorted_values[k]);
        k++;
    }
    destroy_map_iterator(i);
done:
    destroy_tree_map(tm);
    return result;
}

typedef struct
{
    size_t k;
    bool error;
} tree_map_traversal_data_t;

void tree_map_callback(void *obj, const pair_t* pair)
{
    tree_map_traversal_data_t *data = (tree_map_traversal_data_t*)obj;
    if (0 != strcmp(map_sorted_keys[data->k], (char*)pair->key))
        data->error = true;
    if (map_sorted_values[data->k] != *((int*)pair->value))
        data->error = true;
    data->k++;
}

static bool test_create_and_traverse_tree_map()
{
    bool result = true;
    tree_map_t *tm = create_tree_map_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < count_of_map_keys; k++)
        add_pair_to_tree_map(tm, (void*)map_keys[k], (void*)&map_values[k]);
    assert_equals(tm->size, count_of_map_keys);
    tree_map_traversal_data_t data = {0};
    traverse_over_tree_map(tm, tree_map_callback, &data);
    assert_equals(data.error, false);
    assert_equals(data.k, count_of_map_keys);
done:
    destroy_tree_map(tm);
    return result;
}

static bool test_create_and_destroy_tree_map_with_content()
{
    bool result = true;
    tree_map_t *tm = create_tree_map_ext((void*)strcmp, &debug_allocator);
    size_t k;
    for (k = 0; k < count_of_map_keys; k++)
    {
        size_t len = strlen(map_keys[k]);
        char *key_copy = debug_allocator.allocate(len + 1);
        memcpy(key_copy, map_keys[k], len + 1);
        int *value_copy = debug_allocator.allocate(sizeof(int));
        *value_copy = map_values[k];
        add_pair_to_tree_map(tm, (void*)key_copy, (void*)value_copy);
    }
    assert_equals(tm->size, count_of_map_keys);
    k = 0;
    map_iterator_t *i = create_iterator_from_tree_map(tm);
    while(has_next_pair(i))
    {
        const pair_t *p = next_pair(i);
        assert_equals(0, strcmp(p->key, map_sorted_keys[k]));
        assert_equals(*((int*)p->value), map_sorted_values[k]);
        k++;
    }
    destroy_map_iterator(i);
done:
    destroy_tree_map_and_content(tm, string_destructor, int_destructor);
    return result;
}

static bool test_create_tree_map_and_add_pairs_twice()
{
    bool result = true;
    tree_map_t *tm = create_tree_map_ext((void*)strcmp, &debug_allocator);
    size_t k;
    void *old_value;
    for (k = 0; k < count_of_map_keys; k++)
    {
        old_value = add_pair_to_tree_map(tm, (void*)map_keys[k], (void*)&map_values[k]);
        assert_equals(old_value, NULL);
    }
    for (k = 0; k < count_of_map_keys; k++)
    {
        old_value = add_pair_to_tree_map(tm, (void*)map_keys[k], NULL);
        assert_equals(old_value, &map_values[k]);
    }
done:
    destroy_tree_map(tm);
    return result;
}

static bool test_seek_and_destroy_data_in_tree_map()
{
    bool result = true;
    tree_map_t *tm = create_tree_map_ext((void*)strcmp, &debug_allocator);
    size_t k;
    const pair_t *pair;
    void *value;
    for (k = 0; k < count_of_map_keys; k++)
        add_pair_to_tree_map(tm, (void*)map_keys[k], (void*)&map_values[k]);
    assert_equals(tm->size, count_of_map_keys);
    for (k = 0; k < count_of_map_keys; k++)
    {
        pair = get_pair_from_tree_map(tm, (void*)map_keys[k]);
        assert_diff(pair, NULL);
        value = remove_pair_from_tree_map(tm, (void*)map_keys[k]);
        assert_equals(value, &map_values[k]);
        pair = get_pair_from_tree_map(tm, (void*)map_keys[k]);
        assert_equals(pair, NULL);
        value = remove_pair_from_tree_map(tm, (void*)map_keys[k]);
        assert_equals(value, NULL);
    }
    assert_equals(tm->size, 0);
done:
    destroy_tree_map(tm);
    return result;
}

test_t test_list [] =
{
    { "create vector and check size", test_create_vector_and_check_size },
    { "create vector with non zero capacity", test_create_vector_with_non_zero_capacity },
    { "vector's push and get", test_vector_push_and_get },
    { "vector's iterator", test_vector_iterator },
    { "vector's index_of and destructor", test_vector_index_of_and_destructor },
    { "vector's set", test_vector_set },
    { "vector's insert", test_vector_insert },
    { "vector's remove", test_vector_remove },
    { "create and iterate tree set", test_create_and_iterate_tree_set },
    { "create and traverse tree set", test_create_and_traverse_tree_set },
    { "create and destroy tree set with content", test_create_and_destroy_tree_set_with_content },
    { "create tree set and add data twice", test_create_tree_set_and_add_data_twice },
    { "seek and destroy data in tree set", test_seek_and_destroy_data_in_tree_set },
    { "create and iterate tree map", test_create_and_iterate_tree_map },
    { "create and traverse tree map", test_create_and_traverse_tree_map },
    { "create and destroy tree map with content", test_create_and_destroy_tree_map_with_content },
    { "create tree map and add pairs twice", test_create_tree_map_and_add_pairs_twice },
    { "seek and destroy data in tree map", test_seek_and_destroy_data_in_tree_map },
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
