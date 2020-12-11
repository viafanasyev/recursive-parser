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
#include <map>

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

class SymbolTable {
private:
    struct keyCompare {
        bool operator()(const char* a, const char* b) const {
            return strcmp(a, b) < 0;
        }
    };

    std::map<const char*, size_t, keyCompare> symbols;
    size_t nextSymbolId = 0;

public:
    SymbolTable();

    void addSymbol(const char* name) noexcept;

    size_t getSymbolIdByName(const char* name) const noexcept;
    static double evalFuncById(size_t id, double arg);
};

double eval(const char* expression);

#endif // RECURSIVE_PARSER_CALCULATOR_H
