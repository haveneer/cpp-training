// include GTest tools
#include "gtest/gtest.h"
#include <cmath>
#include <limits>

TEST(FloatingNumber, ExactMatch) {
  EXPECT_EQ(0.3, 0.2 + 0.1); // NOT Equal
}

TEST(FloatingNumber, NearZero) {
  EXPECT_NEAR(0.3, 0.2 + 0.1, 0); //
}

TEST(FloatingNumber, NearCustomEpsilon) {
  EXPECT_NEAR(0.3, 0.2 + 0.1, 1e-16); //
}

TEST(FloatingNumber, 4ULP) {

  const double x = 0.3;

  auto ulp = [](double f) {
    // Definition of ULP in https://en.wikipedia.org/wiki/Unit_in_the_last_place
    // In radix b with precision p, if b^e ≤ |x| < b^{e+1},
    // then ULP(x) = b^{max(e,emin)−p+1}

    int f_exp{};
    double f_frac = std::frexp(f, &f_exp); // decompose number as fraction-exponent
    // i.e. f == f_frac * 2^f_exp

    auto e_min = std::numeric_limits<double>::min_exponent;
    auto b = std::numeric_limits<double>::radix;
    auto p = std::numeric_limits<double>::digits;

    // implicitly uses b as equal to 2 in ldexp
    return std::ldexp(1, std::max(f_exp, e_min) - p + 1);
  };

  std::cout << "ULP(" << x << ") = " << ulp(x) << "\n";

  EXPECT_DOUBLE_EQ(x, 0.2 + 0.1); // 4*ULP(f) near equality test
}

// This is the default main.
// If not defined gtest_main will do it for you.
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  /* return */ RUN_ALL_TESTS(); // result should be returned
  // (here fatal tests are ok)
  return EXIT_SUCCESS;
}
