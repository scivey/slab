#include <stdio.h>
#include "point.h"

point_t* point_init(point_t* self, int x, int y) {
    self->x = x;
    self->y = y;
    return self;
}

void point_print(point_t* self) {
    printf("\n{ x: %i, y: %i }", self->x, self->y);
}
