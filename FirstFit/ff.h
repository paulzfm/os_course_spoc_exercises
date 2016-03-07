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
void list_init(struct free_list *list);  // initialize
void list_insert(struct free_list *node, struct free_list *list); // insert node as list's next
void list_unlink(struct free_list *node); // remove node

// first fit
// alloc a block whose size >= bytes, returns the bytes allocated
size_t ff_alloc(struct free_list *list, size_t bytes, char **start);
// free memory start ~ start + size, returns the bytes free
void ff_free(struct free_list *list, char *start, size_t bytes);

// debug
void ff_print(struct free_list *list);

// tests
void ff_test(struct free_list *list);

#endif
