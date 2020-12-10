/**
 * @file
 * @brief Definition of calculator that uses recursive parser
 */
#ifndef RECURSIVE_PARSER_CALCULATOR_H
#define RECURSIVE_PARSER_CALCULATOR_H

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <exception>

class SyntaxError : public std::exception {
private:
    static constexpr int MAX_INT_LENGTH = 10;

protected:
    int position;
    char* message;

public:
    SyntaxError(int position_, const char* cause_);

    ~SyntaxError() override;

    const char* what() const noexcept override;

    int at() const noexcept;
};

double eval(const char* expression);

#endif // RECURSIVE_PARSER_CALCULATOR_H
