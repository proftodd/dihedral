#ifndef POINT_H
#define POINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linalg/vector.h"

typedef struct Point {
    const double x;
    const double y;
    const double z;
} Point;

Point *Point_new(const double x, const double y, const double z);
Point *Point_new_fromString(const char *string);
int Point_dealloc(Point *p);

int Point_equal(const Point *p1, const Point *p2);

Vector *to_vector(const Point *from, const Point *to);

#ifdef __cplusplus
}
#endif

#endif
