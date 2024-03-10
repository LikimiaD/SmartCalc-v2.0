#include <gtest/gtest.h>

#include "../model/calculator_model.h"

TEST(GraphModelTest, ReplaceXTest) {
  GraphModel graphModel;

  std::string line1 = "2*x + 3";
  std::string expected1 = "2*25 + 3";
  std::string result1 = graphModel.replaceX(line1, 25.0);
  EXPECT_EQ(result1, expected1);

  std::string line2 = "x^2 - 5(x) + 6";
  std::string expected2 = "-3^2 - 5(-3) + 6";
  std::string result2 = graphModel.replaceX(line2, -3.0);
  EXPECT_EQ(result2, expected2);

  std::string line3 = "2 + 3";
  std::string expected3 = "2 + 3";
  std::string result3 = graphModel.replaceX(line3, 10.0);
  EXPECT_EQ(result3, expected3);
}