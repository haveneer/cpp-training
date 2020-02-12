//#region [Declarations]
#include <functional>
#include <iomanip>
#include <iostream>

template <typename R, typename C, typename... A>
typename std::function<R(A...)> mem_func_to_func(R (C::*)(A...) const);

template <typename> struct fn_sig;
template <typename T> struct fn_sig<std::function<T>> { using type = T; };

template <typename T>
auto lambda_to_fp(T) -> decltype(mem_func_to_func(&T::operator()));

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY_HEADER()                                                       \
  std::cout << std::setw(12) << u8"\u03BB" << "  : " << std::setw(12)          \
            << "C++ type" << std::setw(20) << "equivalent type"                \
            << "\n"

#define DISPLAY_TYPE(F)                                                        \
  {                                                                            \
    using std_func = decltype(lambda_to_fp(F));                                \
    std::cout << std::setw(12) << #F << " : " << std::setw(12)                 \
              << type<decltype(F)>() << std::setw(20)                          \
              << type<typename fn_sig<std_func>::type>() << "\n";              \
  }
//#endregion

int main() {
  // All these 𝛌-functions are equivalent
  auto f1 = [] { return 2; };
  auto f2 = []() { return 2; };
  auto f3 = [](void) { return 2; };

  // All these 𝛌-functions are equivalent
  auto g1 = [](int i) { return 2 * i; };
  auto g2 = [](int i) -> decltype(2 * i) { return 2 * i; };
  auto g3 = [](int i) -> int { return 2 * i; };

  //#region [Show types]
  DISPLAY_HEADER();
  DISPLAY_TYPE(f1);
  DISPLAY_TYPE(f2);
  DISPLAY_TYPE(f3);
  DISPLAY_TYPE(g1);
  DISPLAY_TYPE(g2);
  DISPLAY_TYPE(g3);
  //#endregion
}
