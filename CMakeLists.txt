cmake_minimum_required(VERSION 3.21)
project(Little_Compiler CXX C)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
add_executable(Recursive_Descent main.c  pair.h pair.c scanner.h scanner.c recursive_descent.h recursive_descent.c)
add_executable(Little_Compiler main.c preprocessing.h preprocessing.c pair.h pair.c scanner.h scanner.c recursive_descent.h recursive_descent.c)
set_property(TARGET Little_Compiler PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test")

#add_executable(Little_Compiler scanner.c  pair.c)