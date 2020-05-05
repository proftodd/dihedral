file(GLOB linalg_sources src/*.c)
add_library(linalg STATIC ${linalg_sources})
target_include_directories(linalg PUBLIC include)
install(TARGETS linalg DESTINATION lib)
install(
    DIRECTORY include/linalg
    DESTINATION include/linalg
    FILES_MATCHING PATTERN "*.h"
)

add_subdirectory(test)
