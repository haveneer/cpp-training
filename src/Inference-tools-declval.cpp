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

#define DISPLAY_TYPE(X) \
  std::cout << std::setw(45) << #X << " : " << type<X>() << '\n'
//#endregion

int main() {
  struct X {};
  const X &x = X{}; // HINT because a rvalue can be assigned to a lvalue const ref
  // /!\ x is still valid (extended lifetime for temporary objects)

  using SumIntAndDoubleType = decltype(std::declval<int>() + std::declval<double>());
  DISPLAY_TYPE(SumIntAndDoubleType); // std::declval spontaneous build of object
                                     // at compile time (ONLY)
  // std::declval<int>(); // no runtime : error: symbol(s) not found

  struct Y {
    Y() = delete;
    auto foo() { return 1; }
  };
  DISPLAY_TYPE(decltype(std::declval<Y>())); // even for non-constructible types
  DISPLAY_TYPE(decltype(std::declval<Y>().foo())); // any symbolic op is possible
  DISPLAY_TYPE(std::decay_t<int[2]>);              // std::decay cleans up a type
  DISPLAY_TYPE(std::decay_t<int &&>);
  DISPLAY_TYPE(decltype(main));
  DISPLAY_TYPE(std::decay_t<decltype(main)>);
  DISPLAY_TYPE(std::decay_t<decltype(std::declval<Y>())>);
}