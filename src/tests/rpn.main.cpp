#include <gtest/gtest.h>

#include "../model/calculator_model.h"

#define EPS 1e-7

TEST(RPNModelClass, inputLine) {
  std::string line = "1+1";
  RPNModel model;
  model.inputLine(line);
  EXPECT_EQ(model.getDefaultLine(), line);
}

TEST(RPNModelClass, readLineContainsX) {
  std::string line = "1+1";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  line = "1+x";
  model.inputLine(line);
  EXPECT_TRUE(model.readLine());
}

TEST(RPNModelClass, readLine) {
  std::string line = "1+1";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "1 1 +");
}

TEST(RPNModelClass, largeEquations) {
  std::string line = "2*(3+4)-5/2";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 / -");

  model.clear();
  line = "(2 + 3) * (4 - 5) / 6";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 + 4 5 - * 6 /");

  model.clear();
  line = "2 * (3 + 4) - (5 / 2)";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 / -");

  model.clear();
  line = "2 * (3 + 4) - (5 / (2 + 3))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / -");

  model.clear();
  line = "2 * (3 ^ 4) - (5 / (2 + 3))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 ^ * 5 2 3 + / -");
}
TEST(RPNModelClass, largeEquationsWithFunctions) {
  std::string line = "cos(2*(3+4)-5/2)";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 / - c");

  model.clear();
  line = "sin((2 + 3) * (4 - 5) / 6)";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 + 4 5 - * 6 / s");

  model.clear();
  line = "tan(2 * (3 + 4) - (5 / 2))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 / - t");

  model.clear();
  line = "arccos(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - o");

  model.clear();
  line = "arcsin(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - i");

  model.clear();
  line = "arctan(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - a");

  model.clear();
  line = "sqrt(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - q");

  model.clear();
  line = "log(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - l");

  model.clear();
  line = "ln(2 * (3 + 4) - (5 / (2 + 3)))";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 4 + * 5 2 3 + / - n");
}
TEST(RPNModelClass, onlyFunctions) {
  std::string line = "-cos(2) * sin(3)";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 c u 3 s *");

  model.clear();
  line = "tan(2) / arccos(3)";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 t 3 o /");

  model.clear();
  line = "arcsin(2) + arctan(3)";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 i 3 a +");

  model.clear();
  line = "2mod3";
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 3 m");
}
TEST(RPNModelClass, onlyFunctionsAndOperators) {
  std::string line =
      "-cos(2) * sin(3) + tan(2) / arccos(3) - arcsin(2) + arctan(3)";
  RPNModel model;
  model.inputLine(line);
  EXPECT_FALSE(model.readLine());
  EXPECT_EQ(model.getDefaultLine(), line);
  EXPECT_EQ(model.getRPNLine(), "2 c u 3 s * 2 t 3 o / + 2 i - 3 a +");
}
TEST(RPNModelClass, solveRPN) {
  std::string line = "1+1";
  RPNModel model;
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 2, EPS);

  line = "2*(3+4)-5/2";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 11.5, EPS);

  line = "(2 + 3) * (4 - 5) / 6";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), -0.83333333333333337, EPS);

  line = "2 * (3 + 4) - (5 / 2)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 11.5, EPS);

  line = "2 * (3 + 4) - (5 / (2 + 3))";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 13, EPS);

  line = "2 * (3 ^ 4) - (5 / (2 + 3))";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 161, EPS);
}
TEST(RPNModelClass, solveRPNFunctions) {
  std::string line = "cos(2)";
  RPNModel model;
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), cos(2), EPS);

  line = "sin(3)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), sin(3), EPS);

  line = "tan(4)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), tan(4), EPS);

  line = "arcsin(1)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), asin(1), EPS);

  line = "arctan(7)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), atan(7), EPS);

  line = "sqrt(8)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), sqrt(8), EPS);

  line = "log(9)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), log10(9), EPS);

  line = "ln(10)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ;
  ASSERT_NEAR(model.solveRPN(), log(10), EPS);

  line = "3mod2";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 1, EPS);

  line = "arccos(0.5)";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), acos(0.5), EPS);

  line = "2 * (3 + 4) - (5 / (2 + 3))";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 13, EPS);

  line = "2 * (3 ^ 4) - (5 / (2 + 3))";
  model.clear();
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), 161, EPS);
}
TEST(RPNModelClass, sovleRPNOnlyFunctionsLarge) {
  std::string line = "-cos(2) * sin(3)";
  RPNModel model;
  model.inputLine(line);
  model.readLine();
  ASSERT_NEAR(model.solveRPN(), -cos(2) * sin(3), EPS);
}