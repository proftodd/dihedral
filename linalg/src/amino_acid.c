#include <stdlib.h>
#include "dihedral/amino_acid.h"
#include "dihedral/point.h"

AminoAcid *AminoAcid_new(const char chain, const int residue, const Point *n, const Point *ca, const Point *c, const Point *o)
{
    AminoAcid *new_aa = malloc(sizeof(AminoAcid));
    if (new_aa) {
        new_aa->chain = chain;
        new_aa->residue = residue;
        new_aa->n = (Point *) n;
        new_aa->ca = (Point *) ca;
        new_aa->c = (Point *) c;
        new_aa->o = (Point *) o;
    }
    return new_aa;
}

int AminoAcid_dealloc(AminoAcid *aa)
{
    Point_dealloc(aa->n);
    Point_dealloc(aa->ca);
    Point_dealloc(aa->c);
    Point_dealloc(aa->o);
    free(aa);
    return !0;
}
