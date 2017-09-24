cmake_minimum_required(VERSION 3.8)
project(tbagrel_project)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.c carray.c carray.h)
add_executable(tbagrel_project ${SOURCE_FILES})
