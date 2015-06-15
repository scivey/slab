#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

#include "free_list.h"
#include <stdlib.h>

typedef struct {
    void* data;
    size_t item_size;
    size_t actual_item_size;
    size_t total_count;
    size_t last_allocated_index;
    free_list_t* free_list;
} memory_slab_t;

memory_slab_t* memory_slab_init(memory_slab_t* self, size_t item_size, size_t total_count);

void* memory_slab_alloc(memory_slab_t* self);

void memory_slab_free(memory_slab_t* self, void* slab_item);


#ifdef __cplusplus
    }
#endif
