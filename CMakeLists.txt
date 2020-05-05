cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(dihedral LANGUAGES C VERSION 0.0.1)

enable_testing()

add_compile_options("-Wall")

include_directories(/usr/local/include)

add_subdirectory(linalg)
