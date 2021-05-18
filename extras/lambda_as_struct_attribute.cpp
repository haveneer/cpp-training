//#region [declarations]
#include <iostream>
#include <functional>
//#endregion

template <typename Lambda> struct X {
  X(Lambda l) : lambda{l} {}
  Lambda lambda; // any lambda type (very performant)
};

struct Y {
  std::function<void()> lambda; // lambda with a given signature (not performant)
};

int main() {
  auto f = [] {};

  X<decltype(f)> x1(f); // C++ pre17
  X x2(f);              // C++ 17

  Y y{f};
}