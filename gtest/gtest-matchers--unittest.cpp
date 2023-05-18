// include GTest tools
#include "gtest/gtest.h"
#include <cmath>
#include <gmock/gmock.h>

/***************************************************/

// more details in
// https://github.com/google/googletest/blob/master/docs/gmock_cheat_sheet.md#defining-matchers
MATCHER(MyIsEven, "") { return (arg % 2) == 0; }
// IsNan is now alailable in gtest v1.12
MATCHER(MyIsNan, "NaN value") { return ::std::isnan(arg); }

MATCHER_P(MyIsDivisibleBy, n, "") {
    *result_listener << "where the remainder is " << (arg % n);
    return (arg % n) == 0;
}

TEST(SuitName, TestCaseName) {
    using ::testing::Not;
    using namespace ::testing;

    ASSERT_THAT(2, MyIsEven());
    ASSERT_THAT(2.0, Not(MyIsNan()));
    ASSERT_THAT(12, MyIsDivisibleBy(4));
}