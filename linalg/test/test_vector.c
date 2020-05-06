#include <math.h>
#include "CUnit/Basic.h"
#include "linalg/vector.h"

void test_magnitude()
{
    Vector *v = Vector_new(3, (double []) {1.0, 2.0, 2.0});

    double mag = magnitude(v);

    CU_ASSERT_DOUBLE_EQUAL(3.0, mag, EPSILON);

    Vector_dealloc(v);
}

void test_dot_product()
{
    Vector *v1 = Vector_new(3, (double []) {1.0, 2.0, 3.0});
    Vector *v2 = Vector_new(3, (double []) {4.0, 5.0, 6.0});
    double dp = dot_product(v1, v2);

    CU_ASSERT(dp == 32.0);

    Vector_dealloc(v1);
    Vector_dealloc(v2);
}

void dot_product_returns_nan_if_vectors_are_not_same_dimension()
{
    Vector *v1 = Vector_new(3, (double []) {1.0, 2.0, 3.0});
    Vector *v2 = Vector_new(2, (double []) {1.0, 20});

    double dp = dot_product(v1, v2);

    CU_ASSERT(isnan(dp));

    Vector_dealloc(v1);
    Vector_dealloc(v2);
}

void test_cross_product()
{
    Vector *i = Vector_new(3, (double []) {1.0, 0.0, 0.0});
    Vector *j = Vector_new(3, (double []) {0.0, 1.0, 0.0});
    Vector *k = Vector_new(3, (double []) {0.0, 0.0, 1.0});
    Vector *cp;

    cp = cross_product(i, j);
    CU_ASSERT(Vector_equal(k, cp));
    Vector_dealloc(cp);

    cp = cross_product(k, i);
    CU_ASSERT(Vector_equal(j, cp));
    Vector_dealloc(cp);

    cp = cross_product(j, k);
    CU_ASSERT(Vector_equal(i, cp));
    Vector_dealloc(cp);

    Vector_dealloc(i);
    Vector_dealloc(j);
    Vector_dealloc(k);
}

void cross_product_returns_1d_vector_with_NAN_if_vectors_are_not_both_3d()
{
    Vector *v1 = Vector_new(3, (double []) {1.0, 0.0, 0.0});
    Vector *v2 = Vector_new(4, (double []) {1.0, 2.0, 3.0, 4.0});

    Vector *cp = cross_product(v1, v2);

    CU_ASSERT(cp->dimensions == 1);
    CU_ASSERT(isnan(cp->fields[0]));

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

    if (
        (NULL == CU_add_test(pSuite, "test vector magnitude", test_magnitude)) ||
        (NULL == CU_add_test(pSuite, "test of dot_product()", test_dot_product)) ||
        (NULL == CU_add_test(pSuite, "dot product returns NAN if vectors are not same dimension", dot_product_returns_nan_if_vectors_are_not_same_dimension)) ||
        (NULL == CU_add_test(pSuite, "test of cross_product()", test_cross_product)) ||
        (NULL == CU_add_test(pSuite, "cross product returns 1d vector with NAN if vectors are not both 3d", cross_product_returns_1d_vector_with_NAN_if_vectors_are_not_both_3d))
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
