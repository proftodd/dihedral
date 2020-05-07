#ifndef VECTOR_H
#define VECTOR_H

#ifdef __cplusplus
extern "C" {
#endif


#define EPSILON 1.0E-6

typedef struct Vector {
    int dimensions;
    double *fields;
} Vector;

Vector *Vector_alloc();
Vector *Vector_new(const int dimensions, ...);
int Vector_dealloc(Vector *v);

int Vector_equal(const Vector *v1, const Vector *v2);

double magnitude(const Vector *v);
double dot_product(const Vector *v1, const Vector *v2);
Vector *cross_product(const Vector *v1, const Vector *v2);

#ifdef __cplusplus
}
#endif

#endif
