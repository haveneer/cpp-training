#include "gtest/gtest.h"
#include <cmath>
#include <iostream>

TEST(MyTest, Feature1) {
  EXPECT_EQ(1, 1);                // Non fatal error: continue
  ASSERT_STREQ("hello", "world"); // fatal error: stop
  EXPECT_EQ(1, 1);                // never executed
}

// Disbaled by name
TEST(DISABLED_MyTest, Feature2) { ASSERT_EQ(1, 2); }
TEST(MyTest, DISABLED_Feature3) { ASSERT_EQ(1, 2); }

TEST(MyTest, Feature4) {
  ASSERT_EQ(1, 2);
  GTEST_SKIP(); // modern disable style from 1.10.0
  ASSERT_EQ(3, 4);
}

double square_root(double num) {
  if (num < 0.0) {
    std::cerr << "Error: Negative Input\n";
    exit(1);
  }
  return std::sqrt(num);
}

TEST(MyTest, SquareRoot) {
  EXPECT_DOUBLE_EQ(square_root(4), 2 + 1e-14);  // exact floating point match
  EXPECT_NEAR(square_root(4), 2 + 1e-14, 1e-8); // exact floating point match
  EXPECT_EXIT(square_root(-4), ::testing::ExitedWithCode(1),
              "Error: Negative Input"); // parse std::cerr using regex
}

// This is the default main.
// If not defined gtest_main will do it for you.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  /* return */ RUN_ALL_TESTS(); // result should be returned
                                // (here fatal tests are ok)
  return EXIT_SUCCESS;
}
