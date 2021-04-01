//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#define DISPLAY(x) \
  std::cout << std::setw(20) << #x << " : " << std::setw(6) << (x) << '\n'
//#endregion

struct Foo {
  void size();
};

template <typename T, typename = void> // default behavior
constexpr bool has_size_method_v = false;
// template <typename T> // lookup for size method without signature (C++11)
// constexpr bool has_size_method_v<T, decltype(&T::size, void())> = true;
// template <typename T> // lookup for size method with signature (C++11)
// constexpr bool has_size_method_v<T, decltype(std::declval<T>().size(), void())> =
//    true;
template <typename T> // lookup for size method without signature (C++17)
constexpr bool has_size_method_v<T, std::void_t<decltype(&T::size)>> = true;

int main() {
  using Vec = std::vector<int>;
  std::cout << std::boolalpha;

  DISPLAY(has_size_method_v<int>);
  DISPLAY(has_size_method_v<Foo>);
  DISPLAY(has_size_method_v<Vec>);
}