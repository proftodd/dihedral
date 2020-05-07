#include <math.h>
#include "CUnit/Basic.h"
#include "dihedral.h"
#include "dihedral/point.h"

void test_angle_between()
{
    Point *start = Point_new(1.0, 0.0, 0.0);
    Point *vertex = Point_new(0.0, 0.0, 0.0);
    Point *end1 = Point_new(0.0, 0.0, 1.0);
    Point *end2 = Point_new(1.0, 1.0, 0.0);
    Point *end3 = Point_new(-1.0, 0.0, 0.0);
    Point *end4 = Point_new(-1.0, -1.0, 0.0);
    Point *end5 = Point_new(1.0, 0.0, 0.0);
    Point *end6 = Point_new(0.0, 0.0, 1.0);

    CU_ASSERT_DOUBLE_EQUAL(M_PI_2, angle_between(start, vertex, end1), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(M_PI_4, angle_between(start, vertex, end2), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(M_PI, angle_between(start, vertex, end3), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(3 * M_PI_4, angle_between(start, vertex, end4), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(0.0, angle_between(start, vertex, end5), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(M_PI_2, angle_between(start, vertex, end6), EPSILON);

    Point_dealloc(start);
    Point_dealloc(vertex);
    Point_dealloc(end1);
    Point_dealloc(end2);
    Point_dealloc(end3);
    Point_dealloc(end4);
    Point_dealloc(end5);
    Point_dealloc(end6);
}

void test_dihedral_angle()
{
    Point *start = Point_new(1.0, 0.0, 0.0);
    Point *intersection_1 = Point_new(0.0, 0.0, 0.0);
    Point *intersection_2 = Point_new(0.0, 1.0, 0.0);
    Point *end1 = Point_new(0.0, 1.0, 1.0);
    Point *end2 = Point_new(0.0, 1.0, -1.0);
    Point *end3 = Point_new(1.0, 1.0, 1.0);

    CU_ASSERT_DOUBLE_EQUAL(-M_PI_2, dihedral_angle(start, intersection_1, intersection_2, end1), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL( M_PI_2, dihedral_angle(start, intersection_1, intersection_2, end2), EPSILON);
    CU_ASSERT_DOUBLE_EQUAL(-M_PI_4, dihedral_angle(start, intersection_1, intersection_2, end3), EPSILON);

    Point_dealloc(start);
    Point_dealloc(intersection_1);
    Point_dealloc(intersection_2);
    Point_dealloc(end1);
    Point_dealloc(end2);
    Point_dealloc(end3);
}

int main(int argc, char **argv)
{
    CU_pSuite pSuite = NULL;
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Angles", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (NULL == CU_add_test(pSuite, "test angle between", test_angle_between)) ||
        (NULL == CU_add_test(pSuite, "test dihedral angle", test_dihedral_angle))
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
