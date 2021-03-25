//#region [Declarations]
#include <iostream>
// include GTest tools
#include "gtest/gtest.h"
#include <tuple>
//#endregion

#include "gtest-parametric-permutation.hpp"
#include "gtest-parametric-sequence.hpp"
#include "gtest-triangle.hpp"

// parametrized TestSuit level fixture
class MyParametrizedTest
    : public ::testing::TestWithParam<std::tuple<int, int, int>> {
protected:                // needs to be accessible by sub-classes (e.g. TEST*)
  void SetUp() override { // don't forget 'override' (TODO why ?)
    // Retrieve info about running test
    const testing::TestInfo *const test_info =
        testing::UnitTest::GetInstance()->current_test_info();
    if (m_verbose)
      std::cout << test_info->test_suite_name() << "." << test_info->name() << "\n";
  }
  static inline bool m_verbose = true;
};

using TriangleSuccessTestSuit = MyParametrizedTest;
TEST_P(TriangleSuccessTestSuit, Job) {
  auto [j, k, l] = GetParam();
  EXPECT_NE(check_triangle(j, k, l), TriangleProperty::eImpossible);
}

INSTANTIATE_TEST_SUITE_P(Part1, TriangleSuccessTestSuit,
                         testing::Values(std::make_tuple(2, 3, 4),
                                         std::make_tuple(3, 3, 3),
                                         std::make_tuple(3, 3, 5),
                                         std::make_tuple(5, 3, 3),
                                         std::make_tuple(3, 5, 3)));

using TriangleFailureTestSuit1 = MyParametrizedTest;
TEST_P(TriangleFailureTestSuit1, Job) {
  auto [j, k, l] = GetParam();
  EXPECT_EQ(check_triangle(j, k, l), TriangleProperty::eImpossible);
}

std::vector<int> other_values = {2, 5, 0, -1};
INSTANTIATE_TEST_SUITE_P(Part2, TriangleFailureTestSuit1,
                         testing::Combine(testing::Values(1), testing::Values(3),
                                          testing::ValuesIn(other_values)));

/////////////////////////////////////////////////////

using TriangleFailureTestSuit2 = MyParametrizedTest;
TEST_P(TriangleFailureTestSuit2, Job) {
  auto [j, k, l] = GetParam();
  EXPECT_EQ(check_triangle(j, k, l), TriangleProperty::eImpossible);
}

// Sequence and Permutation are custom generators
INSTANTIATE_TEST_SUITE_P(Part3, TriangleFailureTestSuit2,
                         Sequence<TriangleFailureTestSuit2::ParamType>({
                             testing::Values(std::make_tuple(0, 4, 3)),
                             testing::Values(std::make_tuple(-1, 5, 3)),
                             Permutation<TriangleFailureTestSuit2::ParamType>(
                                 testing::Values(std::make_tuple(1, 2, 3))),
                             Permutation<TriangleFailureTestSuit2::ParamType>(
                                 testing::Values(std::make_tuple(1, 3, 5))),
                             testing::Values(std::make_tuple(0, 0, 0)),
                         }));
