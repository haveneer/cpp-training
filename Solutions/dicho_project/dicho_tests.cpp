// include GTest tools
#include "dicho.hpp"
#include "f.hpp"
#include "gtest/gtest.h"

TEST(dicho, Success) {
  x0 = 1; // global
  Real a = x0 / 2;
  Real b = 2 * x0;
  Real eps = 1e-9;

  int n = 0;
  ASSERT_NO_THROW(dicho(a, b, eps, &n));
  EXPECT_GT(eps, std::abs(b - a));
  EXPECT_NEAR(x0, (a + b) / 2, x0 * eps);
  EXPECT_LT(0, n);
  EXPECT_GT(100, n);
}

TEST(dicho, InvalidRange) { ASSERT_THROW(dicho(2, 1), std::invalid_argument); }

TEST(dicho, InvalidEpsilon) {
  x0 = 1; // global
  Real a = x0 / 2;
  Real b = 2 * x0;
  ASSERT_THROW(dicho(a, b, -1, nullptr), std::invalid_argument);
}

TEST(dicho, BadConverge) {
  // This example shows rounding error when x0 is large
  x0 = 40; // global
  Real a = x0 / 2;
  Real b = 2 * x0;
  const Real eps = 1e-9;

  int n = 0;
  EXPECT_NO_THROW(dicho(a, b, eps, &n));
  EXPECT_GT(eps, std::abs(b - a));
  const Real x = (a + b) / 2;
  EXPECT_FALSE(std::abs(x0 - x) <
               x0 * eps); // the opposite is expected if converged, but not true for
                          // this value of x0
  EXPECT_LT(0, n);
  EXPECT_GT(100, n);
}