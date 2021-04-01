//#region [Collapse all]
#include <iomanip>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#define DISPLAY(a, b)                                                         \
  std::cout << std::right << std::setw(30) << #a << " : " << std::left        \
            << std::setw(12) << a << " | " << std::left << std::setw(13) << b \
            << " : " << #b << '\n';
//#endregion
using namespace std::string_literals;

auto foo(const int &) { return "lvalue"s; }
auto foo(int &&) { return "rvalue"s; }

template <typename T> auto indirectT(T &&x) { return foo(x) + " T=" + type<T>(); }
template <typename T> auto indirect_and_forwardT(T &&x) {
  return foo(std::forward<T>(x)) + " T=" + type<T>();
}

int main() {
  auto bar = [] { return 42; }; // our rvalue generator
  int i{};                      // our typical lvalue

  // Direct call behaves perfectly: choose the right foo() signature according arg
  DISPLAY(foo(bar()), foo(i));
  // Indirect call without forwarding : always choose lvalue signature
  DISPLAY(indirectT(bar()), indirectT(i)); //
  // Indirect call with forwarding : always choose the right signature
  DISPLAY(indirect_and_forwardT(bar()), indirect_and_forwardT(i));
}