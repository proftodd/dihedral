#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dihedral.h"
#include "dihedral/amino_acid.h"
#include "dihedral/point.h"
#include "linalg/vector.h"

#define LINE_LENGTH 80
#define MAX_AA 10000

const AminoAcid **read_aas(FILE *pdb_file, int *aa_count)
{
    char line[LINE_LENGTH + 1];
    AminoAcid **aa_list = malloc(MAX_AA * sizeof(AminoAcid));
    int count = 0;
    int line_len;
    char next;
    char name[4] = "   ";
    char chain = '\0';
    char prev_chain = '\0';
    int residue = 0;
    int prev_residue = 0;
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    Point *n = NULL;
    Point *ca = NULL;
    Point *c = NULL;
    Point *o = NULL;
    while (fgets(line, sizeof(line), pdb_file)) {
        line_len = strlen(line);
        if (line[line_len - 1] == '\r' || line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0';
        }
        next = getc(pdb_file);
        if (!(next == '\r' || next == '\n')) {
            ungetc(next, pdb_file);
        }

        if (strncmp(line, "ATOM", 4) == 0 && count < MAX_AA) {
            for (int i = 0; i < 3; ++i) {
                name[i] = line[i + 13];
            }
            chain = line[21];
            sscanf(line + 22, " %3d %8lf %8lf %8lf", &residue, &x, &y, &z);
            if ((prev_chain != chain || prev_residue != residue) && n && ca && c && o) {
                aa_list[count] = AminoAcid_new(chain, residue, n, ca, c, o);
                ++count;
                prev_chain = chain;
                prev_residue = residue;
            }
            if (strcmp(name, "N  ") == 0) {
                n = Point_new(x, y, z);
            }
            if (strcmp(name, "CA ") == 0) {
                ca = Point_new(x, y, z);
            }
            if (strcmp(name, "C  ") == 0) {
                c = Point_new(x, y, z);
            }
            if (strcmp(name, "O  ") == 0) {
                o = Point_new(x, y, z);
            }
        }
    }
    *aa_count = count;
    return (const AminoAcid **) aa_list;
}
