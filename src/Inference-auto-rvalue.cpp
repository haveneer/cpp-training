//#region [declarations]
#include <iomanip>
#include <iostream>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
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