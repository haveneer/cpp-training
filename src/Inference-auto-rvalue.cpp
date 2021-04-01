//#region [declarations]
#include <iomanip>
#include <iostream>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
#define DISPLAY_TYPE(T, val)                                                   \
  {                                                                            \
    T x = val;                                                                 \
    std::cout << std::setw(14) << #T << " x = " #val " : "                     \
              << type<decltype(x)>() << std::endl;                             \
  }

#define DISPLAY_AUTO_TYPE(T, val)                                              \
  {                                                                            \
    auto &&x = val;                                                            \
    std::cout << "auto && from " << std::setw(14) << #T << " : "               \
              << type<decltype(x)>() << std::endl;                             \
  }

#define DISPLAY_ERRR(T, val, msg)                                              \
  {                                                                            \
    std::cout << std::setw(14) << #T << " x = " #val " : " << msg              \
              << std::endl;                                                    \
  }

int main() {
  //#endregion
  int i = 1;
  const int ci = 1;
  int &ri = i;
  const int &cri = i;
  int &&rri = 1;
  const int &&crri = 1;

  std::cout << "# All auto combinations\n";
  DISPLAY_TYPE(auto, i);
  DISPLAY_TYPE(auto, 1);
  DISPLAY_TYPE(const auto, i);
  DISPLAY_TYPE(const auto, 1);
  DISPLAY_TYPE(auto &, i);
  DISPLAY_ERRR(auto &, 1, "## error not a lvalue ##");
  DISPLAY_TYPE(const auto &, i);
  DISPLAY_TYPE(const auto &, 1);
  DISPLAY_TYPE(auto &&, i); // OK: for any lvalue or rvalue
  DISPLAY_TYPE(auto &&, 1);
  DISPLAY_ERRR(const auto &&, i, "## error not a rvalue ##");
  DISPLAY_TYPE(const auto &&, 1);

  std::cout << "\n# auto&& from all RHS types\n";
  DISPLAY_AUTO_TYPE(1, 1);
  DISPLAY_AUTO_TYPE(int, i);
  DISPLAY_AUTO_TYPE(int const, ci);
  DISPLAY_AUTO_TYPE(int &, ri);
  DISPLAY_AUTO_TYPE(int const &, cri);
  DISPLAY_AUTO_TYPE(int &&, rri);
  DISPLAY_AUTO_TYPE(int const &&, crri);
  //#region [end]
}
//#endregion