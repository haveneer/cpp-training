//#region [Declarations]
#include <cmath>
#include <iomanip>
#include <iostream>
// clang-format off
//#endregion

int main() {
  static_assert(  1  /   2  ==  0  );
  static_assert(  1. /   2  ==  0.5);
  static_assert(  1  /   2. ==  0.5);

  static_assert(  8  %   3  ==  2  );
  static_assert(  8  % (-3) ==  2  );
  static_assert((-8) %   3  == -2  );
  static_assert((-8) % (-3) == -2  );

  // % is not defined on floating number
  // std::cout << 8. % 3 << '\n';

  //#region [Define an integer n]
  // clang-format on
  const int n = -7;
  //#endregion

  std::cout << "-- BAD RESULT --\n";
  if (n % 2 == 1) {
    std::cout << n << " is an odd number\n";
  } else {
    std::cout << n << " is an even number\n";
  }

  std::cout << "-- GOOD RESULT --\n";
  if (n % 2 != 0) {
    std::cout << n << " is an odd number\n";
  } else {
    std::cout << n << " is an even number\n";
  }

  //#region [Math vs modulo vs remainder]
  auto test = [](int a, int b) {
    std::cout << "----\n";
    double xa = a, xb = b;
    // mathematical modulo: implementation from Raymond T. Boute
    // http://portal.acm.org/citation.cfm?id=128862&coll=portal&dl=ACM
    // cf https://en.wikipedia.org/wiki/Modulo_operation
    std::cout << "mathematically: " << std::setw(2) << a << " mod " << std::setw(2)
              << b << " = " << (xa - std::floor(xa / std::abs(xb)) * std::abs(xb))
              << "\n";
    std::cout << "floor(" << std::setw(2) << a << ", " << std::setw(2) << b
              << ") = " << std::setw(2) << std::floor(xa / xb) << " -> "
              << std::setw(2) << (xa - std::floor(xa / xb) * xb) << "\n";
    std::cout << "trunc(" << std::setw(2) << a << ", " << std::setw(2) << b
              << ") = " << std::setw(2) << std::trunc(xa / xb) << " -> "
              << std::setw(2) << (xa - std::trunc(xa / xb) * xb)
              << " : this is operator % [" << (a % b) << "]\n";
    std::cout << "round(" << std::setw(2) << a << ", " << std::setw(2) << b
              << ") = " << std::setw(2) << std::round(xa / xb) << " -> "
              << std::setw(2) << (xa - std::round(xa / xb) * xb)
              << " : this is remainder function [" << std::remainder(a, b) << "]\n";
  };

  test(8, 3);
  test(8, -3);
  test(-8, 3);
  test(-8, -3);
  //#endregion
}