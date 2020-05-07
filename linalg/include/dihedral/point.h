#ifndef POINT_H
#define POINT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "linalg/vector.h"

typedef struct Point {
    double x;
    double y;
    double z;
} Point;

Point *Point_new(const double x, const double y, const double z);
int Point_dealloc(Point *p);

Vector *to_vector(const Point *from, const Point *to);

#ifdef __cplusplus
}
#endif

#endif
