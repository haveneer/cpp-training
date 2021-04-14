// include GTest tools
#include "gtest/gtest.h"
#include <cmath>
#include <gmock/gmock.h>

/***************************************************/

// more details in
// https://github.com/google/googletest/blob/master/docs/gmock_cheat_sheet.md#defining-matchers
MATCHER(IsEven, "") { return (arg % 2) == 0; }
MATCHER(IsNan, "NaN value") { return ::std::isnan(arg); }
MATCHER_P(IsDivisibleBy, n, "") {
  *result_listener << "where the remainder is " << (arg % n);
  return (arg % n) == 0;
}

TEST(SuitName, TestCaseName) {
  using ::testing::Not;
  using namespace ::testing;

  ASSERT_THAT(2, IsEven());
  ASSERT_THAT(2.0, Not(IsNan()));
  ASSERT_THAT(12, IsDivisibleBy(4));
}