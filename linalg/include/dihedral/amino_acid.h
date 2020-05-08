#ifndef AMINO_ACID_H
#define AMINO_ACID_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dihedral/point.h"

typedef struct AminoAcid {
    char chain;
    int residue;
    Point *n;
    Point *ca;
    Point *c;
    Point *o;
} AminoAcid;

AminoAcid *AminoAcid_new(const char chain, const int residue, const Point *n, const Point *ca, const Point *c, const Point *o);
int AminoAcid_dealloc(AminoAcid *aa);

#ifdef __cplusplus
}
#endif

#endif
