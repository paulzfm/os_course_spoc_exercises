#include "ff.h"
#include <stdio.h>

extern char mem[];

void ff_test(struct free_list *list)
{

  struct free_list *node = malloc(sizeof(struct free_list));
  list_init(list);
  node->index = 0;
  node->size = MAX_MEM;
  list_insert(node, list);    // insert first free block
  ff_print(list);
  char *buf[10];
  for(int i=0;i<10;++i)
  {
    ff_alloc(list, 1<<i, &buf[i]);
    ff_print(list);
  }
  for(int i=0;i<10;++i)
  {
    ff_free(list, buf[i], 1<<i);
    ff_print(list);
  }

}
int main()
{
    struct free_list *list = malloc(sizeof(struct free_list));

    ff_test(list);

    return 0;
}
