#pragma once

enum class TriangleProperty {
  eImpossible,
  eScalene,
  eIsocele,
  eEquilateral,
};

auto check_triangle(int j, int k, int l) -> TriangleProperty;