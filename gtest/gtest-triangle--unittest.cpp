// include GTest tools
#include "gtest/gtest.h"

// include the features to test
#include "gtest-triangle.hpp"

/***************************************************/

TEST(Triangle, Possible) {
  EXPECT_EQ(check_triangle(2, 3, 4), TriangleProperty::eScalene);
  EXPECT_EQ(check_triangle(3, 3, 3), TriangleProperty::eEquilateral);
  EXPECT_EQ(check_triangle(3, 3, 5), TriangleProperty::eIsocele);
  EXPECT_EQ(check_triangle(5, 3, 3), TriangleProperty::eIsocele);
  EXPECT_EQ(check_triangle(3, 5, 3), TriangleProperty::eIsocele);
}

TEST(Triangle, Impossible) {
  EXPECT_EQ(check_triangle(0, 4, 3), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(-1, 5, 3), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(1, 2, 3), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(3, 2, 1), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(1, 3, 2), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(5, 3, 1), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(3, 5, 1), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(1, 3, 5), TriangleProperty::eImpossible);
  EXPECT_EQ(check_triangle(0, 0, 0), TriangleProperty::eImpossible);
}
