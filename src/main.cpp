/**
 * @file
 */
#include <cstdio>
#include "calculator.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid arguments number (argc = %d)", argc);
        return -1;
    }

    try {
        printf("Result = %d", eval(argv[1]));
    } catch (const SyntaxError& e) {
        fprintf(stderr, "Syntax error: %s", e.what());
        return -1;
    }
    return 0;
}
