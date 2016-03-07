#include "ff.h"

int main()
{
    struct free_list *list = malloc(sizeof(struct free_list));
    list_init(list);

    ff_test(list);

    return 0;
}
