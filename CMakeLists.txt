cmake_minimum_required(VERSION 3.16)
project(recursive-parser)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wfloat-equal)

add_executable(
        eval
        src/main.cpp
        src/calculator.h
        src/calculator.cpp)

add_executable(
        tests
        test/main.cpp
        test/testlib.h
        test/testlib.cpp
        test/calculator_tests.cpp
        src/calculator.h
        src/calculator.cpp)
