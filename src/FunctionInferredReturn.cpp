//#region [Declarations]
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
#define DISPLAY_TYPE(F)                                                     \
  {                                                                         \
    std::cout << std::setw(21) << #F << " : "                               \
              << type<std::remove_reference_t<decltype(F)>>() << std::endl; \
  }
//#endregion

//#region [details]
template <typename T1, typename T2> struct promote {};
template <> struct promote<int, int> { typedef int type; };
template <> struct promote<double, double> { typedef double type; };
template <> struct promote<int, double> { typedef double type; };
template <> struct promote<double, int> { typedef double type; };
//#endregion

// C++03
template <typename T1, typename T2>
//#region [TODO: How to define the return type in C++<11]
typename promote<T1, T2>::type
//#endregion
add_03(T1 const &a, T2 const &b) {
#define BODY() a + b // TODO: what happens if the body becomes 'return a'
  return BODY();
} // HINT Expand me: question inside

// C++11
template <typename T1, typename T2>
auto add11a(T1 const &a, T2 const &b) -> decltype(a + b) {
  return BODY();
}

template <typename T1, typename T2>
decltype(std::declval<T1>() + std::declval<T2>()) // cannot use args in heading form
add11b(T1 const &a, T2 const &b) {
  return BODY();
}

// C++14
template <typename T1, typename T2> //
auto add14a(T1 const &a, T2 const &b) {
  return BODY();
}

template <typename T1, typename T2> //
decltype(auto) add14b(T1 const &a, T2 const &b) {
  return BODY();
}

template <typename T1, typename T2> //
auto add14c(T1 const &a, T2 const &b) -> decltype(auto) {
  return BODY();
}

// Dealing with COMPLEX return types
auto f_inferred(const std::vector<int> &v) {
  return std::equal_range(v.begin(), v.end(), 0);
}

//#region [TODO: explicit the return type]
std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
//#endregion
f_byhand(const std::vector<int> &v) {
  return std::equal_range(v.begin(), v.end(), 0);
}

int main() {
  std::cout << "Display function types\n";
  DISPLAY_TYPE((add_03<int, double>));
  DISPLAY_TYPE((add11a<int, double>));
  DISPLAY_TYPE((add11b<int, double>));
  DISPLAY_TYPE((add14a<int, double>));
  DISPLAY_TYPE((add14b<int, double>));
  DISPLAY_TYPE((add14c<int, double>));
  DISPLAY_TYPE((f_inferred));
  DISPLAY_TYPE((f_byhand));
}