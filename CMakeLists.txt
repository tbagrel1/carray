cmake_minimum_required(VERSION 3.9)
project(cvector C CXX)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(cvector cvector.h main.c tests/cvector_import.h)
add_executable(cvector_tests cvector.h tests/tests.cpp tests/cvector_import.h)

target_link_libraries(cvector m)
target_link_libraries(cvector_tests gtest gtest_main pthread m)
