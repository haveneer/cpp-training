//#region [declarations]
#include <iostream>
//#endregion

template <typename T> auto f(T x) -> T { return x * 4; } // C++03
template <> auto f<int>(int x) -> int { return x << 2; } // C++03

auto g14 = [](auto x) -> auto { return x * 4; }; // C++14
// auto g20(auto x) -> auto { return x * 4; }; // C++20

void step1() {
  std::cout << f<double>(2) << std::endl;
  std::cout << f<int>(2) << std::endl;
  std::cout << g14(2) << std::endl;
}

void step2() {
  auto apply_callback = [](auto callback) {
    return [=](auto &&...ts) // generic lambda, ts is a parameter pack
    {
      callback(std::forward<decltype(ts)>(ts)...);
      return [=] { callback(ts...); }; // capture [callback, ts...] by copy
    };
  };

  auto p1 = apply_callback([](auto v1, auto v2) { std::cout << v1 << v2 << '\n'; });
  auto p2 = p1("Hello ", 3.14); // call callback with args
  p2();                         // call last call with same args
}

int main() {
  step1();
  step2();
}