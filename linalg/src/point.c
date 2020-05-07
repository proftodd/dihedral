#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "linalg/vector.h"
#include "dihedral/point.h"

Point *Point_new(const double x, const double y, const double z)
{
    Point *my_point;
    if ((my_point = malloc(sizeof(Point)))) {
        my_point->x = x;
        my_point->y = y;
        my_point->z = z;
    }
    return my_point;
}

Point *Point_new_fromString(const char *string)
{
    double x, y, z;
    sscanf(string + 30, "%8lf%8lf%8lf", &x, &y, &z);
    return Point_new(x, y, z);
}

int Point_dealloc(Point *p)
{
    free(p);
    return !0;
}

int Point_equal(const Point *p1, const Point *p2)
{
    return
        fabs(p1->x - p2->x) < EPSILON &&
        fabs(p1->y - p2->y) < EPSILON &&
        fabs(p1->z - p2->z) < EPSILON;
}

Vector *to_vector(const Point *from, const Point *to)
{
    double x = to->x - from->x;
    double y = to->y - from->y;
    double z = to->z - from->z;
    return Vector_new(3, x, y, z);
}
