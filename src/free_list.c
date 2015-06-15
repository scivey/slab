#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "free_list.h"

void free_list_init(free_list_t* self, size_t initial_alloc_count) {
    self->data = (size_t*) malloc(sizeof(size_t) * initial_alloc_count);
    self->allocated_count = initial_alloc_count;
    self->size = 0;
}

size_t* free_list_get_end_ptr(free_list_t* self) {
    return self->data + self->size;
}

void free_list_resize(free_list_t* self, size_t new_size) {
    size_t* new_data = (size_t*) malloc(sizeof(size_t) * new_size);
    memcpy(new_data, self->data, self->size * sizeof(size_t));
    void* old_data = (void*) self->data;
    self->data = new_data;
    free(old_data);
    self->allocated_count = new_size;
}

void free_list_push_back(free_list_t* self, size_t elem) {
    if (self->size >= self->allocated_count) {
        free_list_resize(self, 2 * self->allocated_count);
    }
    size_t* list_elem = free_list_get_end_ptr(self);
    *list_elem = elem;
    self->size++;
}

void free_list_pop_back(free_list_t* self) {
    self->size--;
}

size_t* free_list_last_elem(free_list_t* self) {
    return (self->data + self->size) - 1;
}

size_t free_list_len(free_list_t* self) {
    return self->size;
}
