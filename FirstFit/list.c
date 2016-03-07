#include "ff.h"

void list_init(struct free_list *list)  // initialize
{
    list->prev = list->next = list;
    list->size = 0;
}

void list_insert(struct free_list *node, struct free_list *list) // insert node as list's next
{
    struct free_list *next = list->next;
    struct free_list *prev = list->prev;
    list->next = next->prev = node;
    node->next = next;
    node->prev = list;
}

void list_unlink(struct free_list *node) // remove node
{
    if (node->prev == node->next) { // no more free space
        node->size = 0;
    } else {
        struct free_list *next = node->next;
        struct free_list *prev = node->prev;
        prev->next = next;
        next->prev = prev;
    }
}
