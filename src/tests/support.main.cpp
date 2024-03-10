#include <gtest/gtest.h>

#include "../model/calculator_model.h"

TEST(SupportClassTest, isDoublePart) {
  EXPECT_TRUE(Support::isDoublePart('0'));
  EXPECT_TRUE(Support::isDoublePart('1'));
  EXPECT_TRUE(Support::isDoublePart('x'));
  EXPECT_TRUE(Support::isDoublePart('.'));
  EXPECT_FALSE(Support::isDoublePart('a'));
  EXPECT_FALSE(Support::isDoublePart('A'));
}
TEST(SupportClassTest, isOpenBracket) {
  EXPECT_TRUE(Support::isOpenBracket('('));
  EXPECT_FALSE(Support::isOpenBracket(')'));
  EXPECT_FALSE(Support::isOpenBracket('a'));
  EXPECT_FALSE(Support::isOpenBracket('A'));
}
TEST(SupportClassTest, isCloseBracket) {
  EXPECT_TRUE(Support::isCloseBracket(')'));
  EXPECT_FALSE(Support::isCloseBracket('('));
  EXPECT_FALSE(Support::isCloseBracket('a'));
  EXPECT_FALSE(Support::isCloseBracket('A'));
}
TEST(SupportClassTest, isFunctionSym) {
  EXPECT_TRUE(Support::isFunctionSym('c'));
  EXPECT_TRUE(Support::isFunctionSym('s'));
  EXPECT_TRUE(Support::isFunctionSym('a'));
  EXPECT_TRUE(Support::isFunctionSym('l'));
  EXPECT_TRUE(Support::isFunctionSym('t'));
  EXPECT_TRUE(Support::isFunctionSym('m'));
  EXPECT_FALSE(Support::isFunctionSym('x'));
  EXPECT_FALSE(Support::isFunctionSym('0'));
  EXPECT_FALSE(Support::isFunctionSym('A'));
}
TEST(SupportClassTest, isUnaryMinus) {
  std::string line = "1-1";
  std::size_t index = 1;
  EXPECT_FALSE(Support::isUnaryMinus(line, index));
  line = "-1-1";
  index = 0;
  EXPECT_TRUE(Support::isUnaryMinus(line, index));
  line = "1+(-1)";
  index = 3;
  EXPECT_TRUE(Support::isUnaryMinus(line, index));
}
TEST(SupportClassTest, isOperator) {
  EXPECT_TRUE(Support::isOperator('+'));
  EXPECT_TRUE(Support::isOperator('-'));
  EXPECT_TRUE(Support::isOperator('*'));
  EXPECT_TRUE(Support::isOperator('/'));
  EXPECT_FALSE(Support::isOperator('x'));
  EXPECT_FALSE(Support::isOperator('0'));
  EXPECT_FALSE(Support::isOperator('A'));
}