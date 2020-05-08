#ifndef PDB_H
#define PDB_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "dihedral/amino_acid.h"

const AminoAcid **read_aas(FILE *pdb_file, int *aa_count);

#ifdef __cplusplus
}
#endif

#endif
