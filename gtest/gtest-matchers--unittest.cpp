// include GTest tools
#include <gmock/gmock.h>
#include "gtest/gtest.h"
#include <cmath>

// include the features to test
// #include "gtest-template-component.hpp"

/***************************************************/

MATCHER(IsEven, "") { return (arg % 2) == 0; }
MATCHER(IsNan, "NaN value") { return ::std::isnan(arg); }

TEST(SuitName, TestCaseName) {
  using ::testing::Not;
  using namespace ::testing;
  
  ASSERT_THAT(2, IsEven());
  ASSERT_THAT(2.0, Not(IsNan()));
}