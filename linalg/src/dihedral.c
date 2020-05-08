#include <math.h>
#include <stdlib.h>
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
    const Vector *b1 = to_vector(start, intersection_1);
    const Vector *b2 = to_vector(intersection_1, intersection_2);
    const Vector *b3 = to_vector(intersection_2, end);

    const Vector *cp12 = cross_product(b1, b2);
    const Vector *cp23 = cross_product(b2, b3);
    const Vector *cp1223 = cross_product(cp12, cp23);

    double numerator = dot_product(b2, cp1223);
    double denominator = magnitude(b2) * dot_product(cp12, cp23);
    double angle = atan2(numerator, denominator);

    Vector_dealloc((Vector *) b1);
    Vector_dealloc((Vector *) b2);
    Vector_dealloc((Vector *) b3);
    Vector_dealloc((Vector *) cp12);
    Vector_dealloc((Vector *) cp23);
    Vector_dealloc((Vector *) cp1223);

    return angle;
}
