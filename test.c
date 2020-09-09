#include "vector.h"
#include <stdio.h>

int main(void)
{
    vector_t *v = create_vector_ext(get_system_allocator(), 0);
    
    for (int i = 0; i < 20; i++) {
        int *pi = malloc(sizeof(int));
        *pi = i;
        add_item_to_vector(v, pi);
    }

    int *pi1 = malloc(sizeof(int));
    *pi1 = 777;
    int *pi0 = (int*)set_vector_item(v, 10, pi1);
    free(pi0);

    iterator_t *it = create_iterator_from_vector(v);
    while (has_next_item(it))
    {
        int x = *(int*)(next_item(it));
        printf("%d\n", x);
    }
    destroy_iterator(it);

    destroy_vector(v);
}
