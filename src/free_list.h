#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

#include <stdlib.h>

typedef struct {
    size_t* data;
    size_t allocated_count;
    size_t size;
} free_list_t;

void free_list_init(free_list_t* self, size_t initial_alloc_count);

void free_list_push_back(free_list_t* self, size_t elem);

void free_list_pop_back(free_list_t* self);

size_t* free_list_nth(free_list_t* self, size_t index);

void free_list_resize(free_list_t* self, size_t new_size);

size_t* free_list_last_elem(free_list_t* self);

size_t free_list_len(free_list_t* self);


#ifdef __cplusplus
    }
#endif
