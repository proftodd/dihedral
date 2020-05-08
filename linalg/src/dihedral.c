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

double angle_between(const Point *start, const Point *vertex, const Point *end)
{
    if (end->x == vertex->x && end->y == vertex->y && end->z == vertex->z) {
        return 0.0;
    }
    if (end->x == start->x && end->y == start->y && end->z == start->z) {
        return 0.0;
    }
    Vector *start_vector = to_vector(vertex, start);
    Vector *end_vector = to_vector(vertex, end);
    double dp = dot_product(start_vector, end_vector);
    double mag_start = magnitude(start_vector);
    double mag_end = magnitude(end_vector);
    double angle = acos(dp / (mag_start * mag_end));

    Vector_dealloc(start_vector);
    Vector_dealloc(end_vector);

    return angle;
}

double dihedral_angle(const Point *start, const Point *intersection_1, const Point *intersection_2, const Point *end)
{
    const Vector *b1 = to_vector(start, intersection_1);
    const Vector *b2 = to_vector(intersection_1, intersection_2);
    const Vector *b3 = to_vector(intersection_2, end);

    const Vector *cp12 = cross_product(b1, b2);
    const Vector *cp23 = cross_product(b2, b3);
    const Vector *cp1223 = cross_product(cp12, cp23);

    double numerator = dot_product(b2, cp1223);
    double denominator = magnitude(b2) * dot_product(cp12, cp23);
    double angle = atan2(numerator, denominator);

    Vector_dealloc((Vector *) b1);
    Vector_dealloc((Vector *) b2);
    Vector_dealloc((Vector *) b3);
    Vector_dealloc((Vector *) cp12);
    Vector_dealloc((Vector *) cp23);
    Vector_dealloc((Vector *) cp1223);

    return angle;
}
