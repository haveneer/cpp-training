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

auto minimal = [] {}; // do nothing
auto get1 = [] { return 1; };
auto sum = [](int a, int b) -> int { return a + b; };

int main() {
  int x = 2, n = 3;
  auto f1 = [n]() { return n; };
  auto f2 = [x](int a, int b) { return a * x + b; };
  auto f3 = [&x]() -> void { x++; };
  auto f4 = [&y=x, m=n]() -> void { y *= m; }; // rename capture (C++14)
  auto f5 = [&]() {
    n = x;
    x = 2;
    return x;
  };

  f1();
  f2(2, 4);
  f3();
  f4();
  f5();
  [&x, n] { x += n; }(); // anonymous

  std::cout << "n = " << n << "; x = " << x << "\n";
  //#region [Show types]
  std::cout << "------------\n";
  DISPLAY_HEADER();
  DISPLAY_TYPE(minimal);
  DISPLAY_TYPE(get1);
  DISPLAY_TYPE(sum);
  DISPLAY_TYPE(f1);
  DISPLAY_TYPE(f2);
  DISPLAY_TYPE(f3);
  DISPLAY_TYPE(f4);
  DISPLAY_TYPE(f5);
  //#endregion

  //#region [Advanced C++14]
  std::cout << "------------\n";
  auto gsum = [](auto a, auto b) { return a + b; };
  auto as_tuple = [](auto... args) { return std::make_tuple(args...); };

  std::cout << gsum(1.2, 2.4) << "\n";
  std::cout << gsum(1, 2) << "\n";
  //#endregion
}