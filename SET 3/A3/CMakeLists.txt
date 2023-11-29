cmake_minimum_required(VERSION 3.25)
project(assemblyTestProgram)

set(CMAKE_CXX_STANDARD 17)

add_executable(assemblyTestProgram main.cpp heap_sort.h random_vec.h quick_sort.h)
