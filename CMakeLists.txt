cmake_minimum_required(VERSION 3.9)
project(cvector C)

set(CMAKE_C_STANDARD 99)

add_library(cvector cvector.h main.c)
