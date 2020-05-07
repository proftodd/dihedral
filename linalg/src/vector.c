#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include "linalg/vector.h"

Vector *Vector_alloc()
{
    Vector *my_vector = malloc(sizeof(Vector));
    if (my_vector) {
        my_vector->dimensions = 0;
        my_vector->fields = NULL;
    }
    return my_vector;
}

Vector *Vector_new(int dimensions, ...)
{
    Vector *my_vector = Vector_alloc();
    if (my_vector) {
        my_vector->fields = malloc(sizeof(double) * dimensions);
        if (my_vector->fields) {
            my_vector->dimensions = dimensions;
            va_list args;
            va_start(args, dimensions);
            for (int i = 0; i < dimensions; ++i) {
                double value = va_arg(args, double);
                my_vector->fields[i] = value;
            }
            va_end(args);
        } else {
            free(my_vector);
            my_vector = NULL;
        }
    }
    return my_vector;
}

int Vector_dealloc(Vector *v)
{
    if (v && v->fields) {
        free(v->fields);
    }
    free(v);
    return !0;
}

int Vector_equal(const Vector *v1, const Vector *v2)
{
    if (v1->dimensions != v2->dimensions) {
        return 0;
    }
    for (int i = 0; i < v1->dimensions; ++i) {
        if (fabs(v1->fields[i] - v2->fields[i]) >= EPSILON) {
            return 0;
        }
    }
    return !0;
}

double magnitude(const Vector *v)
{
    double squared_distance = 0.0;
    for (int i = 0; i < v->dimensions; ++i) {
        squared_distance += v->fields[i] * v->fields[i];
    }
    return sqrt(squared_distance);
}

double dot_product(const Vector *v1, const Vector *v2)
{
    if (v1->dimensions != v2->dimensions) {
        return NAN;
    }
    double dp = 0;
    for (int i = 0; i < v1->dimensions; ++i) {
        dp += v1->fields[i] * v2->fields[i];
    }
    return dp;
}

Vector *cross_product(const Vector *v1, const Vector *v2)
{
    if (v1->dimensions != 3 || v2->dimensions != 3) {
        return Vector_new(1, NAN);
    }
    double i = v1->fields[1] * v2->fields[2] - v1->fields[2] * v2->fields[1];
    double j = -1.0 * (v1->fields[0] * v2->fields[2] - v1->fields[2] * v2->fields[0]);
    double k = v1->fields[0] * v2->fields[1] - v1->fields[1] * v2->fields[0];
    return Vector_new(3, i, j, k);
}
