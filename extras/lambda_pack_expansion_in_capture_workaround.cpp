//#region [declarations]
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
//#endregion

auto print = [](auto &&...args) {
  auto inner_printer = [](auto &&arg) {
    std::ostringstream oss;
    oss << std::setw(20) << type<decltype(arg)>(arg) << " : " << arg << '\n';
    return oss.str();
  };
  // cannot compose function in fold expression: requires a intermediate function
  (std::cout << ... << inner_printer(args)) << '\n';
};

template <typename... Args> auto delay_invoke_by_copy(Args... args) {
  return [args...]() -> decltype(auto) { return print(args...); };
}

// Since expansion pack [...args=std::move(args)...] is not yet allowed (before
// C++20), we use a temporary tuple.
// (cf http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0780r2.html)
template <typename... Args> auto delay_invoke_by_move(Args... args) {
  return [t = std::make_tuple(std::move(args)...)]() -> decltype(auto) {
    return std::apply(
        [](auto &&...args) -> decltype(auto) { return print(args...); }, t);
  };
}

int main() {
  auto result = 2.;
  auto p1 = delay_invoke_by_copy(1, " + one is ", result);
  auto p2 = delay_invoke_by_move(1, " + one is ", result);
  result = 3; // don't change the output
  p1();
  p2();
}
