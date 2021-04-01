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

//template<typename T> const T & as_const_ref(const T & x) { return x; }; // C++03
auto as_const_ref = [](const auto & x) -> auto & { return x; }; // C++14
//const auto & as_const_ref(const auto & x) { return x; } // Will be in C++20
//#endregion

int main() {
  const decltype(0u) a = 1u; // CHANGE ME as non-const
  decltype(&a) p = &a;
  decltype((a)) c = a;
  const decltype(a) &d = a;
  decltype(&as_const_ref(a)) const q = &a;

  DISPLAY_TYPE(a);
  DISPLAY_TYPE(p);
  DISPLAY_TYPE(c);
  DISPLAY_TYPE(d);
  DISPLAY_TYPE(q);

  //#region [Advanced]
  // clang-format off
  const std::vector<char> tab{'A', 'B', 'C', 'D'};
  DISPLAY_TYPE_T(val, decltype(*tab.begin()+a));

  for (decltype(tab.begin()) it = tab.begin(),
                            end = tab.end();
       it != end; ++it) {
    const decltype('A' + 0u) val = *it + a;
    std::cout << val << std::endl;
  }
  // clang-format on
  //#endregion
}