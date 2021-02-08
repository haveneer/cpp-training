//#region [Declarations]
#include <iostream>
//#endregion

template <typename F, typename... Ts>
constexpr auto log_and_call(F &&f, Ts &&...ts) noexcept(
    noexcept(std::forward<F>(f)(std::forward<Ts>(ts)...)))
    -> decltype(std::forward<F>(f)(std::forward<Ts>(ts)...)) {
  std::cout << "calling `f`\n";
  return std::forward<F>(f)(std::forward<Ts>(ts)...);
}

#define RETURNS(...) \
  noexcept(noexcept(__VA_ARGS__))->decltype(__VA_ARGS__) { return __VA_ARGS__; }

template <typename F, typename... Ts>
constexpr auto log_and_call2(F &&f, Ts &&...ts)
    RETURNS(std::forward<F>(f)(std::forward<Ts>(ts)...))

        int main() {
  auto f = [](int a, int b) { std::cout << "f: " << a << ", " << b << '\n'; };
  log_and_call(f, 2, 3);
}