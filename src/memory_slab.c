#include <stdio.h>
#include <stdlib.h>

#include "memory_slab.h"
#include "free_list.h"

memory_slab_t* memory_slab_init(memory_slab_t* self, size_t item_size, size_t total_count) {
    free_list_t* free_list = (free_list_t*) malloc(sizeof(free_list_t));
    free_list_init(free_list, 1000);
    self->free_list = free_list;
    self->last_allocated_index = 0;
    self->total_count = total_count;
    self->item_size = item_size;
    self->actual_item_size = item_size + sizeof(size_t);
    self->data = malloc(self->actual_item_size * total_count);
    return self;
}

size_t* memory_slab_get_item_index_ptr(memory_slab_t* self, void* slab_item) {
    char* ptr = (char*) slab_item;
    ptr += self->item_size;
    return (size_t*) ptr;
}

void* memory_slab_alloc(memory_slab_t* self) {
    char* elem_ptr;
    size_t elem_index;
    if (free_list_len(self->free_list)) {
        elem_index = *(free_list_last_elem(self->free_list));
        free_list_pop_back(self->free_list);
    } else {
        self->last_allocated_index++;
        elem_index = self->last_allocated_index;
    }
    elem_ptr = ( (char*) self->data ) + (elem_index * self->actual_item_size);
    size_t* data_index_ptr = memory_slab_get_item_index_ptr(self, (void*) elem_ptr);
    *data_index_ptr = elem_index;
    return (void*) elem_ptr;
}

void memory_slab_free(memory_slab_t* self, void* slab_item) {
    size_t* item_index = memory_slab_get_item_index_ptr(self, slab_item);
    free_list_push_back(self->free_list, *item_index);
}
