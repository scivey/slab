#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "free_list.h"
#include "memory_slab.h"
#include "point.h"

TEST_CASE("free_list_push_back", "[free_list_push_back]") {
    free_list_t* list = (free_list_t*) malloc(sizeof(free_list_t));
    free_list_init(list, 100);
    free_list_push_back(list, 5);
    free_list_push_back(list, 8);
    free_list_push_back(list, 3);
    size_t* last_elem;

    last_elem = free_list_last_elem(list);
    REQUIRE( (*last_elem) == 3 );
    free_list_pop_back(list);

    last_elem = free_list_last_elem(list);
    REQUIRE( (*last_elem) == 8 );
    free_list_pop_back(list);

    last_elem = free_list_last_elem(list);
    REQUIRE( (*last_elem) == 5 );
    free_list_pop_back(list);

    REQUIRE (free_list_len(list) == 0);
}

TEST_CASE("free_list_len is accurate", "[free_list_len]") {
    free_list_t* list = (free_list_t*) malloc(sizeof(free_list_t));
    free_list_init(list, 100);
    REQUIRE( free_list_len(list) == 0  );
    free_list_push_back(list, 5);
    REQUIRE( free_list_len(list) == 1  );
    free_list_push_back(list, 8);
    REQUIRE( free_list_len(list) == 2  );
    free_list_pop_back(list);
    REQUIRE( free_list_len(list) == 1  );
    free_list_push_back(list, 10);
    REQUIRE( free_list_len(list) == 2  );
    free_list_push_back(list, 3);
    free_list_push_back(list, 4);
    free_list_push_back(list, 5);
    REQUIRE( free_list_len(list) == 5  );
}

TEST_CASE("free_list reallocs when it can't fit a new element", "[free_list_resizes]") {
    free_list_t* list = (free_list_t*) malloc(sizeof(free_list_t));
    free_list_init(list, 3);
    REQUIRE( list->allocated_count == 3 );

    free_list_push_back(list, 7);
    free_list_push_back(list, 13);
    free_list_push_back(list, 17);

    REQUIRE( list->allocated_count == 3 );

    free_list_push_back(list, 19);
    REQUIRE( list->allocated_count == 6 );

    free_list_push_back(list, 23);
    REQUIRE( list->allocated_count == 6 );

    free_list_push_back(list, 29);
    REQUIRE( list->allocated_count == 6 );
    free_list_push_back(list, 29);
    REQUIRE( list->allocated_count == 12 );
    free_list_push_back(list, 29);
    REQUIRE( list->allocated_count == 12 );

}

TEST_CASE("memory_slab recycles freed blocks", "[memory_slab]") {
    memory_slab_t* slab = (memory_slab_t*) malloc(sizeof(memory_slab_t));
    memory_slab_init(slab, sizeof(point_t), 100);
    point_t* pt1 = (point_t*) memory_slab_alloc(slab);
    point_init(pt1, 5, 10);
    point_t* pt2 = (point_t*) memory_slab_alloc(slab);
    point_init(pt2, 9, 3);
    point_t* pt3 = (point_t*) memory_slab_alloc(slab);
    point_init(pt3, 25, 21);

    REQUIRE( pt1->x == 5 );
    REQUIRE( pt1->y == 10 );

    REQUIRE( pt2->x == 9 );
    REQUIRE( pt2->y == 3 );

    REQUIRE( pt3->x == 25 );
    REQUIRE( pt3->y == 21 );

    memory_slab_free(slab, pt2);
    point_t* new_point = (point_t*) memory_slab_alloc(slab);
    REQUIRE( new_point == pt2 );
}
