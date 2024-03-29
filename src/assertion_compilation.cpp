//#region [Declarations]
#include <cassert> // not use by static_cast; just for testing replacement
#include <iostream>
//#endregion

void print(const char *message) {
  // error: non-constant condition for static assertion
  // static_assert(message != nullptr);
  std::cout << message << '\n';
}

struct Object {
  // Object() {} // TODO why breaks nothrow_default_constructible ?
  static_assert(sizeof(long) == 4 || sizeof(long) == 8,
                "Supports only 32bits and 64bits arithmetic"); // anywhere
};

int main() {
  static_assert(2 + 2 == 4, "Something awful is happening");

  // assertion error message is optional since C++17
  static_assert(1. + 1. == 2.);    // Some floating-point operations can be tested
  static_assert(0.1 + 0.2 != 0.3); // be careful: rounded computation here

  char message[] = "Hello world!";
  static_assert(sizeof(message) == 13); // size statically known

  static_assert(std::is_trivially_copyable<Object>::value); // protects memcpy usage
  static_assert(std::is_nothrow_default_constructible<Object>::value);
}