#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dihedral.h"
#include "dihedral/amino_acid.h"
#include "dihedral/point.h"
#include "linalg/vector.h"

#define LINE_LENGTH 80

typedef struct AAList {
    struct AAList *next;
    AminoAcid *aa;
    int count;
} AAList;

const AminoAcid **read_aas(FILE *pdb_file, int *aa_count)
{
    char line[LINE_LENGTH + 1];

    AAList *aa_list = malloc(sizeof(AAList));
    aa_list->next = NULL;
    aa_list->aa = NULL;
    aa_list->count = 0;

    char name[4] = "";
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
    while (fgets(line, LINE_LENGTH + 1, pdb_file)) {
        if (6 == sscanf(line, "ATOM %*4s %3s %*3s %c %3d %8lf %8lf %8lf", name, &chain, &residue, &x, &y, &z)) {
            if ((prev_chain != chain || prev_residue != residue) && (n && ca && c && o)) {
                AAList *new = malloc(sizeof(AAList));
                new->next = aa_list;
                new->aa = AminoAcid_new(chain, residue, n, ca, c, o);
                new->count = aa_list->count + 1;
                aa_list = new;
                prev_chain = chain;
                prev_residue = residue;
                n = NULL;
                ca = NULL;
                c = NULL;
                o = NULL;
            }
            if (strcmp(name, "N") == 0) {
                n = Point_new(x, y, z);
            }
            if (strcmp(name, "CA") == 0) {
                ca = Point_new(x, y, z);
            }
            if (strcmp(name, "C") == 0) {
                c = Point_new(x, y, z);
            }
            if (strcmp(name, "O") == 0) {
                o = Point_new(x, y, z);
            }
        }
    }

    if (n != NULL || ca != NULL || c != NULL || o != NULL) {
        AAList *new = malloc(sizeof(AAList));
        new->next = aa_list;
        new->aa = AminoAcid_new(chain, residue, n, ca, c, o);
        new->count = aa_list->count + 1;
        aa_list = new;
    }

    *aa_count = aa_list->count;
    AminoAcid **aa_array = malloc(sizeof(AminoAcid) * *aa_count);
    AAList *that = NULL;
    while (aa_list) {
        if (aa_list->count) {
            aa_array[aa_list->count - 1] = aa_list->aa;
        }
        that = aa_list;
        aa_list = aa_list->next;
        free(that);
    }

    return (const AminoAcid **) aa_array;
}
