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

int Point_dealloc(Point *p)
{
    free(p);
    return !0;
}

Vector *to_vector(const Point *from, const Point *to)
{
    double x = to->x - from->x;
    double y = to->y - from->y;
    double z = to->z - from->z;
    return Vector_new(3, x, y, z);
}
