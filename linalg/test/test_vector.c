#include "CUnit/Basic.h"
#include "linalg/vector.h"

void test_dot_product()
{
    Vector *v1 = Vector_new(3, (double []) {1.0, 2.0, 3.0});
    Vector *v2 = Vector_new(3, (double []) {4.0, 5.0, 6.0});
    double dp = dot_product(v1, v2);

    CU_ASSERT(dp == 32.0);

    Vector_dealloc(v1);
    Vector_dealloc(v2);
}

void test_cross_product()
{
    Vector *v1 = Vector_new(3, (double []) {1.0, 0.0, 0.0});
    Vector *v2 = Vector_new(3, (double []) {0.0, 1.0, 0.0});
    Vector *cp = cross_product(v1, v2);

    CU_ASSERT(cp->dimensions == 3);
    CU_ASSERT(cp->fields[0] == 0.0);
    CU_ASSERT(cp->fields[1] == 0.0);
    CU_ASSERT(cp->fields[2] == 1.0);

    Vector_dealloc(v1);
    Vector_dealloc(v2);
    Vector_dealloc(cp);
}

int main(int argc, char **argv)
{
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Vector", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of dot_product()", test_dot_product)) ||
        (NULL == CU_add_test(pSuite, "test of cross_product()", test_cross_product))) {
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
