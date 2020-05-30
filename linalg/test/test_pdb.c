#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "pdb.h"
#include "dihedral/amino_acid.h"

#define TEST_FILE "9ZZZ.pdb"

void test_read_pdb()
{
    FILE *fp = fopen("9ZZZ.pdb", "r");
    if (!fp) {
        CU_ASSERT(0);
    }

    int aa_count = 0;
    AminoAcid **observed_aas = (AminoAcid **) read_aas(fp, &aa_count);
    CU_ASSERT_EQUAL(aa_count, 2);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->n->x, -10.259, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->n->y, 32.951, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->n->z, 35.052, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->ca->x, -11.137, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->ca->y, 33.755, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->ca->z, 35.924, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->c->x, -12.287, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->c->y, 34.427, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->c->z, 35.174, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->o->x, -12.049, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->o->y, 35.172, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[0]->o->z, 34.215, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->n->x, -13.481, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->n->y, 33.908, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->n->z, 35.414, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->ca->x, -14.699, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->ca->y, 34.44, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->ca->z, 34.794, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->c->x, -15.26, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->c->y, 35.626, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->c->z, 35.578, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->o->x, -15.222, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->o->y, 35.61, EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(observed_aas[1]->o->z, 36.815, EPSILON);

    for (int i = 0; i < aa_count; ++i) {
        AminoAcid_dealloc(observed_aas[i]);
    }
    free(observed_aas);
}

int main(int argc, char **argv)
{
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("PDB", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(pSuite, "test read pdb file", test_read_pdb) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    unsigned int return_value;
    if ((return_value = CU_get_error())) {

    } else {
        CU_pRunSummary runSummary = CU_get_run_summary();
        return_value = runSummary->nTestsFailed + runSummary->nAssertsFailed;
    }

    CU_cleanup_registry();
    return return_value;
}