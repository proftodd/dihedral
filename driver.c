#include <stdio.h>
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
    const AminoAcid **aa_list = read_aas(file, &aa_count);
    fclose(file);

    printf("%s\n", "Done!");
    printf("Read %d amino acids from %s\n", aa_count, filename);
    AminoAcid *aa;
    Point *p;
    for (int i = 0; i < aa_count; ++i) {
        aa = (AminoAcid *) aa_list[i];
        p = aa->n;
        printf("%c %3d N:(%8.3f,%8.3f,%8.3f)\n", aa->chain, aa->residue, p->x, p->y, p->z);
    }

    return 0;
}