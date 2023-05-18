#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <random>

namespace custom {
namespace details {
double /* constexpr */ sqrtNewtonRaphson(double x, double curr, double prev) {
  return curr == prev ? curr : sqrtNewtonRaphson(x, 0.5 * (curr + x / curr), curr);
}
} // namespace details

/* Constexpr version of the square root
 * Return value:
 * - For a finite and non-negative value of "x",
 *   returns an approximation for the square root of "x"
 * - Otherwise, returns NaN
 */
double /* constexpr */ sqrt(double x) {
  return x >= 0 && x < std::numeric_limits<double>::infinity()
             ? details::sqrtNewtonRaphson(x, x, 0)
             : std::numeric_limits<double>::quiet_NaN();
}
} // namespace custom

TEST(Sqrt, CheckOnKnownResults) {
  EXPECT_DOUBLE_EQ(custom::sqrt(0), 0);
  EXPECT_DOUBLE_EQ(custom::sqrt(1), 1);
  EXPECT_DOUBLE_EQ(custom::sqrt(4), 2);
  EXPECT_DOUBLE_EQ(custom::sqrt(9), 3);
  EXPECT_DOUBLE_EQ(custom::sqrt(1 << 10), 1 << 5);
  EXPECT_DOUBLE_EQ(custom::sqrt(1 << 20), 1 << 10);
}

TEST(Sqrt, CheckOnInvalidResults) {
  const auto NaN = std::numeric_limits<double>::quiet_NaN();
  EXPECT_TRUE(std::isnan(custom::sqrt(-1)));
  EXPECT_TRUE(std::isnan(custom::sqrt(std::numeric_limits<double>::infinity())));
}

TEST(Sqrt, CheckOnRandomNumbers) {
  std::random_device seed;
  auto gen = [engine = std::default_random_engine(seed()),
              dist = std::uniform_real_distribution<>(
                  0, std::numeric_limits<double>::max())]() mutable {
    return dist(engine);
  };

  for (int i = 0; i < 20; ++i) {
    const double x = gen();
    EXPECT_DOUBLE_EQ(custom::sqrt(x), std::sqrt(x));
  }
}