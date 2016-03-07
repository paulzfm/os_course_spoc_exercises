#ifndef __FIRST_FIT_FF_H_
#define __FIRST_FIT_FF_H_

#include <stdlib.h>

#define MAX_MEM 1024

struct free_list {
    struct free_list *prev;
    struct free_list *next;
    size_t size; // in bytes
    int index;   // start index in memory
};

// free_list operators
void list_init(struct free_list *list)  // initialize
{
    list->prev = list->next = list;
    list->size = MAX_MEM;
}

void list_insert(struct free_list *node, struct free_list *list) // insert node as list's next
{
    struct free_list *next = list->next;
    struct free_list *prev = list->prev;
    list->next = next->prev = node;
    node->next = next;
    node->prev = prev;
}

void list_unlink(struct free_list *node)
{
  if (node->prev == node->next) { // no more free space
      node->size = 0;
  } else {
      struct free_list *next = node->next;
      struct free_list *prev = node->prev;
      prev->next = next;
      next->prev = prev;
  }
} // remove node

// first fit
// alloc a block whose size >= bytes, returns the bytes allocated
size_t ff_alloc(struct free_list *list, size_t bytes, void **start);
// free memory start ~ start + size, returns the bytes free
void ff_free(struct free_list *list, void *start, size_t bytes);

// tests
void ff_test();

#endif
