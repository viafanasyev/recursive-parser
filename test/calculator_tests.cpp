/**
 * @file
 */
#include "testlib.h"
#include "../src/calculator.h"

TEST(eval_correctExpression, simpleExpressionWithoutBraces) {
    const char* expression = "2 + 3 * 5";
    ASSERT_EQUALS(eval(expression), 17);
}

TEST(eval_correctExpression, simpleExpressionWithBraces) {
    const char* expression = "(2 + 3) * 5";
    ASSERT_EQUALS(eval(expression), 25);
}

TEST(eval_correctExpression, complexExpressionWithoutBraces) {
    const char* expression = "2 + 3 * 5 - 7 * 20 / 10";
    ASSERT_EQUALS(eval(expression), 3);
}

TEST(eval_correctExpression, complexExpressionWithBraces) {
    const char* expression = "(2 + 3) * (5 - 7) * 20 / 10";
    ASSERT_EQUALS(eval(expression), -20);
}

TEST(eval_correctExpression, simpleExpressionWithPowerOperator) {
    const char* expression = "2 ^ 3 ^ 2";
    ASSERT_EQUALS(eval(expression), 512);
}

TEST(eval_correctExpression, complexExpressionWithPowerOperator) {
    const char* expression = "(2 + 3) ^ (7 - 5) * 20 / 10";
    ASSERT_EQUALS(eval(expression), 50);
}

TEST(eval_invalidExpression, invalidNumberOfOpenBraces) {
    const char* expression = "(2 + 3 * 5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 10);
    }
}

TEST(eval_invalidExpression, invalidNumberOfCloseBraces) {
    const char* expression = "2 + 3) * 5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 5);
    }
}

TEST(eval_invalidExpression, invalidOperator) {
    const char* expression = "2 + 3 & 5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 6);
    }
}

TEST(eval_invalidExpression, negativeNumber) {
    const char* expression = "2 + 3 * -5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 8);
    }
}

TEST(eval_invalidExpression, explicitPositiveNumber) {
    const char* expression = "2 + 3 * +5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 8);
    }
}

TEST(eval_invalidExpression, variable) {
    const char* expression = "2 + x * 5";
    try {
        eval(expression);
        ASSERT_TRUE(0);
    } catch (const SyntaxError& e) {
        ASSERT_EQUALS(e.at(), 4);
    }
}
