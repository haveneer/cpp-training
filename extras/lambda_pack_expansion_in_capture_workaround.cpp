//#region [declarations]
#include <iomanip>
#include <iostream>
#include <sstream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

auto print = [](auto &&...args) {
  auto inner_printer = [](auto &&arg) {
    std::ostringstream oss;
    oss << std::setw(20) << type<decltype(arg)>() << " : " << arg << '\n';
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
