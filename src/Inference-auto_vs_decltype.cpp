//#region [declarations]
#include <iostream>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
#define DISPLAY_TYPE(x) std::cout << #x << " : " << type<decltype(x)>() << std::endl
#define DISPLAY_TYPE_T(x, T) std::cout << #x << " : " << type<T>() << std::endl
//#endregion

int main() {
  int a = 1;
  int & b = a;
  const int & c = a;

  auto vb_auto = b;
  auto vc_auto = c;
  decltype(b) vb_decltype = b;
  decltype(c) vc_decltype = c;

  DISPLAY_TYPE(vb_auto);
  DISPLAY_TYPE(vc_auto);
  DISPLAY_TYPE(vb_decltype);
  DISPLAY_TYPE(vc_decltype);
}