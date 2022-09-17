cmake_minimum_required(VERSION 3.23)

project(algorithms)

find_package(GTest REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(TEST_EXECUTABLE tests)

file(GLOB_RECURSE SRC LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/src/.hpp)
file(GLOB_RECURSE NON_MOD_TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/non_modifying_operations/*.cpp)
file(GLOB_RECURSE MOD_TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/modifying_operations/*.cpp)
file(GLOB_RECURSE CMP_OP_TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/comparison_operations/*.cpp)
file(GLOB_RECURSE MINMAX_OP_TESTS LIST_DIRECTORIES false ${PROJECT_SOURCE_DIR}/test/minmax_operations/*.cpp)

add_executable(${TEST_EXECUTABLE} ${NON_MOD_TESTS} ${MOD_TESTS} ${CMP_OP_TESTS} ${MINMAX_OP_TESTS} ${SRC})

target_include_directories(${TEST_EXECUTABLE} PUBLIC GTEST_INCLUDE_DIRS PUBLIC src/)
target_link_libraries(${TEST_EXECUTABLE} GTest::gtest_main)

add_test(tests ${TEST_EXECUTABLE})
