#include "ff.h"
#include <stdio.h>

/*int main()
{
    struct free_list *list = malloc(sizeof(struct free_list));
    struct free_list *node = malloc(sizeof(struct free_list));
    list_init(list);
    node->index = 0;
    node->size = MAX_MEM;
    list_insert(node, list);    // insert first free block
    ff_print(list);

    // ff_test(list);
    char *buf1, *buf2, *buf3;
    ff_alloc(list, 16, &buf1);
    ff_print(list);
    ff_alloc(list, 16, &buf2);
    ff_print(list);
    ff_alloc(list, 16, &buf3);
    ff_print(list);
    ff_free(list, buf2, 16);
    ff_print(list);
    ff_free(list, buf1, 16);
    ff_print(list);
    ff_free(list, buf3, 16);
    ff_print(list);

    return 0;
}*/
