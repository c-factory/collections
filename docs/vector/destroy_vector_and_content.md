[Collections](../collections.md) &rarr; [Vector](vector.md) &rarr;

# destroy_vector_and_content

```c
    void destroy_vector_and_content(vector_t *iface, void (*destructor)(void *));
```

Destructs the vector and also the vector data using a destructor.

## Parameters

Argument|Description
--------|-----------
iface|Pointer to a `vector_t` interface
destructor|Destructor that will destroy each item

Destructor takes one argument (pointer to data). For example, as a destructor, the `free` library function can be used, for items, created by the `malloc` function. For complex structs, a programmer has to implement appropriate destructors.

## Example

```c
    #include "vector.h"
    #include <stdio.h>
    #include <string.h>

    int main()
    {
        vector_t *v = create_vector();
        char buff[256];
        printf("Write one or more lines and then press enter:\n");
        while(1)
        {
            printf("> ");
            fgets (buff, 255 , stdin);
            size_t len = strlen(buff);
            if (len < 2)
                break;
            char *str = malloc(len);
            memcpy(str, buff, len - 1);
            str[len - 1] = 0;
            add_item_to_vector(v, str);
        }
        printf("Done. Here the data you entered:\n");
        for (size_t k = 0; k < v->size; k++)
        {
            printf("%s\n", (char*)v->data[k]);
        }
        destroy_vector_and_content(v, free);
        return 0;
    }
```
