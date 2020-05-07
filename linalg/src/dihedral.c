#include <math.h>
#include "dihedral.h"
#include "dihedral/point.h"
#include "linalg/vector.h"

double angle_between(const Point *start, const Point *vertex, const Point *end)
{
    if (end->x == vertex->x && end->y == vertex->y && end->z == vertex->z) {
        return 0.0;
    }
    if (end->x == start->x && end->y == start->y && end->z == start->z) {
        return 0.0;
    }
    Vector *start_vector = to_vector(vertex, start);
    Vector *end_vector = to_vector(vertex, end);
    double dp = dot_product(start_vector, end_vector);
    double mag_start = magnitude(start_vector);
    double mag_end = magnitude(end_vector);
    double angle = acos(dp / (mag_start * mag_end));

    Vector_dealloc(start_vector);
    Vector_dealloc(end_vector);

    return angle;
}

double dihedral_angle(const Point *start, const Point *intersection_1, const Point *intersection_2, const Point *end)
{
    return 0.0;
}
