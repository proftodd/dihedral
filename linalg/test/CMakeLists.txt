find_library (CUNIT NAMES CUnit cunit)
set(common_test_target_deps ${CUNIT} linalg)

foreach(test
        test_vector;
    )
    add_executable(${test} "${test}.c")
    target_link_libraries(${test} ${common_test_target_deps})
    add_test("${test}_app" ${test})
endforeach(test)
