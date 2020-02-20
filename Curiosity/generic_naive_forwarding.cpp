//#region [Declarations]
#include <iostream>
//#endregion

template <typename F, typename... Ts> auto log_and_call(F f, Ts... ts) {
  std::cout << "calling `f`\n";
  return f(ts...);
}

int main() {
  auto f = [](int a, int b) { std::cout << "f: " << a << ", " << b << '\n'; };
  log_and_call(f, 2, 3);
}