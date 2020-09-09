#include "vector.h"
#include <stdio.h>

int main(void)
{
    vector_t *v = create_vector_ext(get_system_allocator(), 0);
    
    for (int i = 0; i < 16; i++) {
        int *pi = malloc(sizeof(int));
        *pi = i;
        add_item_to_vector(v, pi);
    }

    int *pi1 = malloc(sizeof(int));
    *pi1 = 777;
    int *pi0 = (int*)set_vector_item(v, 10, pi1);
    free(pi0);

    int *pi2 = malloc(sizeof(int));
    *pi2 = 333;
    insert_item_into_vector(v, 3, pi2);

    int *pi3 = malloc(sizeof(int));
    *pi2 = 555;
    insert_item_into_vector(v, 5, pi2);

    iterator_t *it = create_iterator_from_vector(v);
    while (has_next_item(it))
    {
        int x = *(int*)(next_item(it));
        printf("%d\n", x);
    }
    destroy_iterator(it);

    destroy_vector(v);
}
