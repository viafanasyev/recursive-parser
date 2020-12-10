# Recursive parser

## Project description

This program is developed as a part of ISP RAS course.  
This program can parse and evaluate mathematical expressions with braces and next operations: `+`, `-`, `*`, `/`, `^`.  
Note that `^` operator is right-associative.

### Structure

* src/ : Main project
    * calculator.h, calculator.cpp : Definition and implementation of calculator that uses recursive parser;
    * main.cpp : Entry point for the program.

* test/ : Tests and testing library
    * calculator_tests.cpp : Tests for recursive parser calculator
    * testlib.h, testlib.cpp : Library for testing with assertions and helper macros;
    * main.cpp : Entry point for tests. Just runs all tests.

* doc/ : doxygen documentation

* Doxyfile : doxygen config file

### Run

#### Calculator

To calculate mathematical expression execute next commands in terminal:
```shell script
cmake . && make
./eval "20 + 30 - 10 * (4 + 3 * 7)"
```

#### Tests

To run tests execute next commands in terminal:
```shell script
cmake . && make
./tests
```

### Documentation

Doxygen is used to create documentation. You can watch it by opening `doc/html/index.html` in browser.  

### OS

Program is developed under Ubuntu 20.04.1 LTS.