//#region [Declarations]
#include <iostream>
#include <string>
#include <utility>
#include <variant>

// TODO: what happens if we replace + operator by * operator ?
auto TwiceVisitor = [](auto &t) { t = t + t; };

auto GenericPrintVisitor = [](const auto &t) {
  std::cout << "GenericPrint: " << t << '\n';
};

auto SpecializedPrintVisitor = [](const auto &t) {
  using type = std::decay_t<decltype(t)>;

  if constexpr (std::is_same_v<type, float>)
    std::cout << "SpecializedPrint for float: '" << t << "'\n";

  if constexpr (std::is_same_v<type, int>)
    std::cout << "SpecializedPrint for int: '" << t << "'\n";

  if constexpr (std::is_same_v<type, std::string>)
    std::cout << "SpecializedPrint for string: '" << t << "'\n";
};

// Lambda overloader C++17 version
#if 1
template <typename... Ts> struct overload : Ts... {
  // overload(Ts... ts) : Ts(ts)... {} // can be replaced by CTAD
  using Ts::operator()...;
};
// Custom Template Argument Deduction Rules
template <typename... Ts> overload(Ts...) -> overload<Ts...>;
#endif

//#region [Lambda overloader C++14 version]
#if 0
template <typename T, typename... Ts>
struct Overloader : T, Overloader<Ts...> {
  using T::operator();
  using Overloader<Ts...>::operator();
  // […]
};

template <typename T> struct Overloader<T> : T {
  using T::operator();
};

template <typename... T>
constexpr auto overload(T&&... t) {
  return Overloader<T...>{std::forward<T>(t)...};
}
#endif
//#endregion
//#endregion

int main() {
  std::variant<int, float, std::string> v;

  v = 158;
  std::visit(GenericPrintVisitor, v);
  std::visit(TwiceVisitor, v);
  std::visit(SpecializedPrintVisitor, v);
  std::puts("");

  v = "Hello";
  std::visit(GenericPrintVisitor, v);
  std::visit(TwiceVisitor, v);
  std::visit(SpecializedPrintVisitor, v);
  std::puts("");

  std::visit(overload{
                 [](const int &i) { std::cout << "int: " << i << '\n'; },
                 [](const float &f) { std::cout << "float: " << f << '\n'; },
                 [](const std::string &s) { std::cout << "string: " << s << '\n'; },
                 [](auto x) {
                   std::cout << "Unknown: " << x << '\n';
                 } // default case (useless here)
             },
             v);
}