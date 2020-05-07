#include "CUnit/Basic.h"
#include "dihedral/point.h"
#include "linalg/vector.h"

void test_to_vector()
{
    Point *p1 = Point_new(0.0, 0.0, 0.0);
    Point *p2 = Point_new(1.0, 1.0, 1.0);

    Vector *v = to_vector(p1, p2);
    Vector *expected = Vector_new(3, 1.0, 1.0, 1.0);
    CU_ASSERT(Vector_equal(expected, v));

    Point_dealloc(p1);
    Point_dealloc(p2);
    Vector_dealloc(v);
    Vector_dealloc(expected);
}

int main(int argc, char **argv)
{
    CU_pSuite pSuite = NULL;
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Point", NULL, NULL);
    if (pSuite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(pSuite, "test points to vector", test_to_vector) == NULL)
    ) {
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