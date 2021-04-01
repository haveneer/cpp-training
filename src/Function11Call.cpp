//#region [Declarations]
#include <iomanip>
#include <iostream>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
#define DISPLAY_TYPE(F)                                                        \
  {                                                                            \
    std::cout << std::setw(12) << #F << " : " << type<decltype(F)>()           \
              << std::endl;                                                    \
  }
//#endregion

// Same function with three styles
int f03(int i) { return i * i; }
auto f11(int i) -> int { return i * i; }
auto f14(int i) { return i * i; }

// Function with return type deduction
auto f14mixed(int i, double x) { return i+x; }

// Functions with return type deduction or true type return
auto f14_id(int & i) { return i; }
decltype(auto) f14_true_id(int & i) { return i; }

int main() {
  std::cout << "Display function types\n";
  DISPLAY_TYPE(f03);
  DISPLAY_TYPE(f11);
  DISPLAY_TYPE(f14);
  DISPLAY_TYPE(f14mixed);
  DISPLAY_TYPE(f14_id);
  DISPLAY_TYPE(f14_true_id);

  //#region [Advanced]
  auto fT = [](auto i) { return i*i; };
  DISPLAY_TYPE(fT);
//#endregion
}