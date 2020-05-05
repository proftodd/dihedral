#include <stdlib.h>
#include "linalg/vector.h"

Vector *Vector_alloc()
{
    Vector *my_vector = malloc(sizeof(Vector));
    if (!my_vector) {
        // throw an error here
    }
    my_vector->dimensions = 0;
    my_vector->fields = NULL;
    return my_vector;
}

Vector *Vector_new(unsigned short dimensions, double *fields)
{
    Vector *my_vector = Vector_alloc();
    my_vector->dimensions = dimensions;
    my_vector->fields = malloc(sizeof(double) * dimensions);
    if (!(my_vector->fields)) {
        // throw an error here
    }
    for (int i = 0; i < dimensions; ++i) {
        my_vector->fields[i] = fields[i];
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

double dot_product(Vector *v1, Vector *v2)
{
    double dp = 0;
    for (int i = 0; i < v1->dimensions; ++i) {
        dp += v1->fields[i] * v2->fields[i];
    }
    return dp;
}

Vector *cross_product(Vector *v1, Vector *v2)
{
    return Vector_alloc();
}
