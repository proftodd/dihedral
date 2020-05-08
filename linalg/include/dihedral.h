#ifndef DIHEDRAL_H
#define DIHEDRAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "dihedral/amino_acid.h"
#include "dihedral/point.h"

const AminoAcid **read_aas(FILE *pdb_file, int *aa_count);

double angle_between(const Point *start, const Point *vertex, const Point *end);

double dihedral_angle(const Point *start, const Point *intersection_1, const Point *intersection_2, const Point *end);

#ifdef __cplusplus
}
#endif

#endif
