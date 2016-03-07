#include "ff.h"
#include <stdio.h>

char mem[MAX_MEM];

size_t ff_alloc(struct free_list *list, size_t bytes, char **start)
{
    struct free_list *node;
    for (node = list->next; node != list; node = node->next) { // traverse free list
        if (node->size >= bytes) { // find!
            *start = mem + node->index;
            if (node->size > bytes) { // split
                node->size -= bytes;
                node->index += bytes;
            } else {
                list_unlink(node);
                // free(node);
            }
            return bytes;
        }
    }

    // not found
    return 0;
}

void ff_free(struct free_list *list, char *start, size_t bytes)
{
    // construct new node
    struct free_list *new_node = malloc(sizeof(struct free_list));
    new_node->prev = new_node->next = NULL;
    new_node->size = bytes;
    new_node->index = start - mem;

    struct free_list *node;
    for (node = list->next; node != list; node = node->next) { // traverse free list
        if (node->index > new_node->index) { // insert before node
            node = node->prev;
            list_insert(new_node, node);
            if (new_node->next->index == new_node->index + bytes) { // merge next
                new_node->size += new_node->next->size;
                list_unlink(new_node->next);
                // free(new_node->next);
            }
            if (node->index + node->size == new_node->index) { // merge prev
                node->size += new_node->size;
                list_unlink(new_node);
                // free(new_node);
            }
            return;
        }
    }
}

void ff_print(struct free_list *list)
{
    struct free_list *node;
    for (node = list->next; node != list; node = node->next) {
        printf("(%zu bytes, @%d) ", node->size, node->index);
    }
    printf("\n");
}
