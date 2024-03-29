//#region [Declarations]
// doc https://rosettacode.org/wiki/Y_combinator
//     https://humanreadablemag.com/issues/1/articles/the-y-combinator-for-programmers
#include <cmath>
#include <functional>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

// Y combinator = λf.(λx.xx)(λy.f(yy))
// std::function<int(int)> is required because compiler cannot infer type
// it cannot be replaced by a decltype()
// Thus, this expression cannot be constexpr : https://godbolt.org/z/so97bedzP
constexpr auto Y = [](auto &&f) {
  return [](auto &&x) { return x(x); }([=](auto &&y) -> std::function<int(int)> {
    return f([=](auto &&a) { return (y(y))(a); });
  });
};

template <typename F> struct recursive {
  F f; // the lambda will be stored here

  //  // a forwarding operator()
  //  template <typename... Ts>
  //  constexpr decltype(auto) operator()(Ts &&... ts) {
  //    // std:ref will be constexpr in C++20
  ////    return f(std::ref(*this), std::forward<Ts>(ts)...);
  //    return f(*this, std::forward<Ts>(ts)...);
  //  }

  // a forwarding operator() (const version)
  template <typename... Ts> constexpr decltype(auto) operator()(Ts &&...ts) const {
    // std:cref will be constexpr in C++20
    // return f(std::cref(*this), std::forward<Ts>(ts)...);
    return f(*this, std::forward<Ts>(ts)...);
  }
};

// helper to build recursive object
template <typename F> recursive<std::decay_t<F>> rec14(F &&f) {
  return {std::forward<F>(f)}; // build a recursive<>
}

// With C++17 and CTAD we can add a deduction guide and a simpler 𝛌 function
// with C++20 this deduction guide could be not necessary
template <typename F> recursive(F) -> recursive<F>;
// helper to build recursive object
auto const rec17 = [](auto f) { return recursive{std::move(f)}; };

int main() {
  // do not use std::function to make recursive anonymous function:
  // it could be very slower than true lambdas

  constexpr auto almost_fac = [](auto f) {
    return [=](auto n) { return n <= 1 ? n : n * f(n - 1); };
  };
  constexpr auto almost_fib = [](auto f) {
    return [=](auto n) { return n < 2 ? 1 : f(n - 1) + f(n - 2); };
  };

  auto yfib = Y(almost_fib); // cannot be constexpr : https://godbolt.org/z/so97bedzP
  auto yfac = Y(almost_fac); // 
  std::cout << yfac(6) << '\n';
  std::cout << yfib(6) << '\n';
  //  static_assert((yfib(6) == 13), "");
  //  static_assert((yfac(6) == 720), "");

  constexpr auto fib = rec17([](auto fib, int i) -> int {
    if (i == 0 || i == 1)
      return 1;
    else
      return fib(i - 1) + fib(i - 2);
  });

  std::cout << "fib(n) return type is: " << type<decltype(fib(6))>() << '\n';
  static_assert((fib(6) == 13), "");
  std::cout << fib(6) << '\n';

  constexpr auto sum_interval = rec17([](auto sum, int a, int b) {
    if (a > b) {
      return 0;
    } else {
      return b * b + sum(a, b - 1);
    }
  });

  constexpr auto sum_from_1 = rec17([](auto sum, int b) -> int {
    if (1 > b) {
      return 0;
    } else {
      return b * b + sum(b - 1);
    }
  });
  static_assert((sum_interval(1, 3) == 14), "");
  std::cout << sum_interval(1, 3) << '\n';

  static_assert((sum_from_1(3) == 14), "");
  //  static_assert((ysum_from_1(3) == 14), "");
  std::cout << sum_from_1(3) << '\n';
}