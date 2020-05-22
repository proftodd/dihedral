#include <stdio.h>
#include <stdlib.h>
#include "pdb.h"
#include "dihedral/amino_acid.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Usage: %s <PDB filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening %s\n", argv[1]);
        return 1;
    }

    int aa_count = 0;
    const AminoAcid **aa_array = read_aas(file, &aa_count);
    fclose(file);

    printf("%s\n", "Done!");
    printf("Read %d amino acids from %s\n", aa_count, filename);
    AminoAcid *aa;
    Point *n, *ca, *c, *o;
    for (int i = 0; i < aa_count; ++i) {
        aa = (AminoAcid *) aa_array[i];
        n = aa->n;
        ca = aa->ca;
        c = aa->c;
        o = aa->o;
        printf("%c %3d ", aa->chain, aa->residue);
        if (n) {
            printf("N:(%8.3f,%8.3f,%8.3f), ", n->x, n->y, n->z);
        } else {
            printf("%s", "N: NA                         , ");
        }
        if (ca) {
            printf("CA:(%8.3f,%8.3f,%8.3f), ", ca->x, ca->y, ca->z);
        } else {
            printf("%s", "CA: NA                         , ");
        }
        if (c) {
            printf("C:(%8.3f,%8.3f,%8.3f), ", c->x, c->y, c->z);
        } else {
            printf("%s", "C: NA                         , ");
        }
        if (o) {
            printf("O:(%8.3f,%8.3f,%8.3f)\n", o->x, o->y, o->z);
        } else {
            printf("%s", "O: NA                         \n");
        }
    }

    for (int i = 0; i < aa_count; ++i) {
        aa = (AminoAcid *) aa_array[i];
        AminoAcid_dealloc(aa);
    }
    free(aa_array);

    return 0;
}