// include GTest tools
#include "gtest/gtest.h"

// include the features to test
#include "gtest-trivial-component.hpp"
#include "gtest-trivial-factorial.hpp"

/***************************************************/

TEST(SuitName, TestCaseName) {
  // Arrange local set-up
  Component *component = new Component{}; // FIXME better with unique_ptr !

  // Act
  component->initialize();

  // Assert
  EXPECT_TRUE(component != nullptr);
  ASSERT_EQ(0, component->getInitValue());

  // local tear-down
  delete component;
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, factorial(1));
  EXPECT_EQ(2, factorial(2));
  EXPECT_EQ(6, factorial(3));
  EXPECT_EQ(720, factorial(6));
}

// Tests factorial of 0.
TEST(FactorialTest, Zero) {
  EXPECT_EQ(1, factorial(0)); //
}

// Tests negative input.
TEST(FactorialTest, Negative) {
  EXPECT_EQ(0, factorial(-5)); //
}