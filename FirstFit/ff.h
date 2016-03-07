#ifndef __FIRST_FIT_FF_H_
#define __FIRST_FIT_FF_H_

#include <stdlib.h>

struct free_list {
    struct free_list *prev;
    struct free_list *next;
    size_t size;
};

// free_list operators
void list_init(struct free_list *list)  // initialize
{
  list->prev = list->next = list;
}
void list_insert(struct free_list *node, struct free_list *list) // insert node as list's next
{
  free_list *next = list->next;
  list->next = next->prev = node;
  node->next = next;
  node->prev = prev;
}
void list_unlink(struct free_list *node)
{
  if (node->prev == node->next)
  {
    //only one, how to delete?
  }else
  {
    free_list *next = list->next;
    free_list *prev = list->prev;
    prev->next = next;
    next->prev = prev;
    //free_a_block
    //ff_free()?
  }
} // remove node

// first fit
size_t ff_alloc(size_t bytes); // alloc a block whose size >= bytes
size_t ff_free(void *start, size_t bytes); // free memory start ~ start + size

void ff_test(); // test cases

#endif
