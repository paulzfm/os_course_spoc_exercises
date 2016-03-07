#include "ff.h"

static char mem[MAX_MEM];

size_t ff_alloc(struct free_list *list, size_t bytes, void **start)
{
    struct free_list *node;
    for (node = list; node != list; node = node->next) { // traverse free list
        if (node->size >= bytes) { // find!
            *start = mem + node->index;
            struct free_list *here = node->prev;
            list_unlink(node);
            if (node->size > bytes) { // split
                node->size -= bytes;
                node->index += bytes;
                list_insert(node, here);
            } else {
                free(node);
            }
            return bytes;
        }
    }

    // not found
    return 0;
}

void ff_free(struct free_list *list, void *start, size_t bytes)
{
    // construct new node
    struct free_list *new_node = malloc(sizeof(struct free_list));
    new_node->size = bytes;
    new_node->index = (char*)start - mem;

    struct free_list *node;
    for (node = list; node != list; node = node->next) { // traverse free list
        if (node->index > new_node->index) { // insert after node
            list_insert(new_node, node);
            if (new_node->next->index == new_node->index + bytes) { // merge next
                new_node->size += new_node->next->size;
                list_unlink(new_node->next);
                free(new_node->next);
            }
            if (new_node->prev->index == new_node->index - new_node->prev->size) { // merge prev
                new_node->prev->size += new_node->size;
                list_unlink(new_node);
                free(new_node);
            }
            return;
        }
    }
}
