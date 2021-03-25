#pragma once
#include <cassert>

enum class TriangleProperty {
  eImpossible,
  eScalene,
  eIsocele,
  eEquilateral,
};

auto check_triangle(int j, int k, int l) -> TriangleProperty {
  auto matching_pair = 0;
  if ((j + k <= l) || (k + l <= j) || (l + j <= k)) {
    return TriangleProperty::eImpossible;
  } else {
    if (j == k)
      matching_pair++;
    if (j == l)
      matching_pair++;
    if (l == k)
      matching_pair++;
    if (matching_pair == 0) {
      return TriangleProperty::eScalene;
    } else if (matching_pair == 1) {
      return TriangleProperty::eIsocele;
    } else {
      assert(matching_pair == 3);
      return TriangleProperty::eEquilateral;
    }
  }
}
