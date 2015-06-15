#include <stdio.h>
#include <stdlib.h>

#include "free_list.h"
#include "memory_slab.h"
#include "point.h"


int main() {
    memory_slab_t* slab = (memory_slab_t*) malloc(sizeof(memory_slab_t));
    memory_slab_init(slab, sizeof(point_t), 50);
    point_t* pt_1 = (point_t*) memory_slab_alloc(slab);
    point_init(pt_1, 10, 20);
    point_t* pt_2 = (point_t*) memory_slab_alloc(slab);
    point_init(pt_2, 5, 8);
    point_t* pt_3 = (point_t*) memory_slab_alloc(slab);
    point_init(pt_3, 213, 100);

    point_print(pt_1);
    point_print(pt_2);
    point_print(pt_3);

    memory_slab_free(slab, pt_3);

    point_t* pt_4 = (point_t*) memory_slab_alloc(slab);
    point_init(pt_4, 50, 40);

    point_print(pt_1);
    point_print(pt_2);
    point_print(pt_3);
    point_print(pt_4);
}
