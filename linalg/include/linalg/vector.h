#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif


#define EPSILON 1.0E-6

typedef struct Vector {
    unsigned short dimensions;
    double *fields;
} Vector;

Vector *Vector_alloc();
Vector *Vector_new(unsigned short dimensions, double *fields);
int Vector_dealloc(Vector *v);

int Vector_equal(Vector *v1, Vector *v2);

double dot_product(Vector *v1, Vector *v2);
Vector *cross_product(Vector *v1, Vector *v2);

#ifdef __cplusplus
}
#endif

#endif
