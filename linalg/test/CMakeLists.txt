find_library (CUNIT NAMES CUnit cunit)
set(common_test_target_deps ${CUNIT} linalg)

foreach(test
        test_vector;
        test_point;
        test_dihedral;
        test_pdb;
    )
    add_executable(${test} "${test}.c")
    target_link_libraries(${test} ${common_test_target_deps})
    add_test("${test}_app" ${test})
endforeach(test)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/9ZZZ.pdb DESTINATION ${CMAKE_CURRENT_BINARY_DIR})