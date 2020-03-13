//#region [Declarations]
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
}