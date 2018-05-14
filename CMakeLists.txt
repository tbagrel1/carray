cmake_minimum_required(VERSION 3.9)
project(cvector C CXX)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_executable(cvector main.c lib/cvector_core.h lib/cvector_interface.h includes/int_vect.c includes/int_vect.h includes/str_vect.c includes/str_vect.h includes/virtual_lib.c includes/virtual_lib.h)
target_link_libraries(cvector m)
