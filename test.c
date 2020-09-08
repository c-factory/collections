#include "vector.h"
#include <stdio.h>

int main(void)
{
    vector_t *v = vector_create_ext(get_system_allocator(), free, 0);
    
    for (int i = 0; i < 20; i++) {
        int *pi = malloc(sizeof(int));
        *pi = i;
        vector_push(v, pi);
    }

    int *pi0 = malloc(sizeof(int));
    *pi0 = 777;
    vector_set(v, 10, pi0);

    for (vector_index_t k = 0; k < v->size; k++)
    {
        int x = *(int*)(vector_get(v, k));
        printf("%d\n", x);
    }

    vector_destroy(v);
}
