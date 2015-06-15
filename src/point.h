#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

typedef struct {
    int x, y;
} point_t;

point_t* point_init(point_t* self, int x, int y);

void point_print(point_t* self);


#ifdef __cplusplus
    }
#endif
