cmake_minimum_required(VERSION 3.21)
project(Little_Compiler C)

set(CMAKE_C_STANDARD 11)

add_executable(Little_Compiler preprocessing.c preprocessing.h main.c)
