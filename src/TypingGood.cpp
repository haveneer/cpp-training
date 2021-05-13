//#region [declarations]
#include <cassert>
#include <iostream>
#include <memory>
//#endregion

struct MyClass {
  int field{}; // {} is a convient bonus if you don't call aggregate initializer
  int otherField{};
};

int main() {
  auto p = std::make_unique<int>(1); /// AAA + RAII

  auto c = MyClass{1}; // MyClass{1.}; => error: narrowing conversion
  assert(c.otherField == 0);
  std::cout << c.otherField << '\n';

  /* do something else */
}