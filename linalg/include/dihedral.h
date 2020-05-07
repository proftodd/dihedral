#ifndef DIHEDRAL_H
#define DIHEDRAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "dihedral/point.h"

const Point **read_points(FILE *pdb_file, int *p_count);

double angle_between(const Point *start, const Point *vertex, const Point *end);

double dihedral_angle(const Point *start, const Point *intersection_1, const Point *intersection_2, const Point *end);

#ifdef __cplusplus
}
#endif

#endif