/**
 * @file
 */
#include <cstdio>
#include "calculator.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid arguments number (argc = %d)\n", argc);
        return -1;
    }

    try {
        printf("Result = %lg\n", eval(argv[1]));
    } catch (const SyntaxError& e) {
        fprintf(stderr, "Syntax error: %s\n", e.what());
        return -1;
    }
    return 0;
}
