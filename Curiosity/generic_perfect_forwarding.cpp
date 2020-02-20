//#region [Declarations]
#include <iostream>
//#endregion

template <typename F, typename... Ts>
constexpr auto log_and_call(F &&f, Ts &&... ts) noexcept(
    noexcept(std::forward<F>(f)(std::forward<Ts>(ts)...)))
    -> decltype(std::forward<F>(f)(std::forward<Ts>(ts)...)) {
  std::cout << "calling `f`\n";
  return std::forward<F>(f)(std::forward<Ts>(ts)...);
}

int main() {
  auto f = [](int a, int b) { std::cout << "f: " << a << ", " << b << '\n'; };
  log_and_call(f, 2, 3);
}