#include <stdio.h>
#include <stdlib.h>
#include "dihedral.h"
#include "dihedral/amino_acid.h"
#include "pdb.h"

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
    printf("Read %d amino acids from %s\n\n", aa_count, filename);

    AminoAcid *curr_aa, *prev_aa;
    double omega, phi, psi;

    printf("%s\n", "C   n    omega      phi      psi");
    for (int i = 1; i < aa_count; ++i) {
        prev_aa = (AminoAcid *) aa_array[i - 1];
        curr_aa = (AminoAcid *) aa_array[i];
        if (prev_aa->chain == curr_aa->chain && prev_aa->residue == curr_aa->residue - 1) {
            omega = dihedral_angle(
                prev_aa->ca,
                prev_aa->c,
                curr_aa->n,
                curr_aa->ca
            );
            phi = dihedral_angle(
                prev_aa->c,
                curr_aa->n,
                curr_aa->ca,
                curr_aa->c
            );
            psi = dihedral_angle(
                prev_aa->n,
                prev_aa->ca,
                prev_aa->c,
                curr_aa->n
            );
            printf("%c %3d %8.3f %8.3f %8.3f\n", curr_aa->chain, curr_aa->residue, omega, phi, psi);
        }
    }

    for (int i = 0; i < aa_count; ++i) {
        curr_aa = (AminoAcid *) aa_array[i];
        AminoAcid_dealloc(curr_aa);
    }
    free(aa_array);

    return 0;
}