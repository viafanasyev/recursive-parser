/**
 * @file
 * @brief Implementation of calculator that uses recursive parser
 *
 * The calculator parses mathematical expressions using next grammar:
 *
 *     G = E '\0'
 *     E = T ([+|-] T)*
 *     T = F ([*|/] F)*
 *     F = P (^ P)*
 *     P = '(' E ')' | N
 *     N = [0-9]+
 *
 */
#include <cctype>
#include <cmath>
#include <vector>
#include "calculator.h"

SyntaxError::SyntaxError(int position_, const char* cause_) {
    position = position_;
    size_t messageLen = strlen(cause_) + 4 + MAX_INT_LENGTH;
    message = (char*)calloc(messageLen + 1, sizeof(char));
    snprintf(message, messageLen, "%s at %d", cause_, position_);
}

SyntaxError::~SyntaxError() {
    free(message);
}

const char* SyntaxError::what() const noexcept {
    return message;
}

int SyntaxError::at() const noexcept {
    return position;
}

int getExpression(const char* expression, int& pos);

int getTerm(const char* expression, int& pos);

int getFactor(const char* expression, int& pos);

int getParenthesised(const char* expression, int& pos);

int getNumber(const char* expression, int& pos);

void skipSpaces(const char* expression, int& pos);

int eval(const char* expression) {
    int pos = 0;
    skipSpaces(expression, pos);
    int result = getExpression(expression, pos);
    if (expression[pos] != '\0') {
        throw SyntaxError(pos, "Invalid symbol");
    }
    ++pos;
    return result;
}

int getExpression(const char* expression, int& pos) {
    int result = getTerm(expression, pos);
    skipSpaces(expression, pos);
    int term = 0;
    char op = 0;
    while (expression[pos] == '+' || expression[pos] == '-') {
        op = expression[pos++];
        skipSpaces(expression, pos);

        term = getTerm(expression, pos);
        skipSpaces(expression, pos);

        result = (op == '+' ? result + term : result - term);
    }
    return result;
}

int getTerm(const char* expression, int& pos) {
    int result = getFactor(expression, pos);
    skipSpaces(expression, pos);
    int factor = 0;
    char op = 0;
    while (expression[pos] == '*' || expression[pos] == '/') {
        op = expression[pos++];
        skipSpaces(expression, pos);

        factor = getFactor(expression, pos);
        skipSpaces(expression, pos);

        result = (op == '*' ? result * factor : result / factor);
    }
    return result;
}

int getFactor(const char* expression, int& pos) {
    int result = getParenthesised(expression, pos);
    skipSpaces(expression, pos);
    int operand = 0;
    std::vector<int> operands;
    while (expression[pos] == '^') {
        ++pos;
        skipSpaces(expression, pos);

        operand = getParenthesised(expression, pos);
        skipSpaces(expression, pos);

        operands.push_back(operand);
    }
    if (!operands.empty()) { // Calculating right-to-left because '^' is right-associative
        size_t i = operands.size() - 1;
        while (i > 0) {
            operands[i - 1] = pow(operands[i - 1], operands[i]);
            --i;
        }
        result = pow(result, operands[0]);
    }
    return result;
}

int getParenthesised(const char* expression, int& pos) {
    if (expression[pos] != '(') {
        return getNumber(expression, pos);
    }
    ++pos;
    skipSpaces(expression, pos);

    int result = getExpression(expression, pos);

    if (expression[pos] != ')') {
        throw SyntaxError(pos, "Expected closing parenthesis");
    }
    ++pos;

    return result;
}

int getNumber(const char* expression, int &pos) {
    int result = 0;
    const int startPos = pos;
    while (isdigit(expression[pos])) {
        result = result * 10 + (expression[pos++] - '0');
    }
    if (pos == startPos) {
        throw SyntaxError(pos, "Expected number");
    }
    return result;
}

void skipSpaces(const char* expression, int& pos) {
    while (std::isspace(expression[pos])) ++pos;
}
