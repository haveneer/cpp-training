//#region [Declarations]
// doc https://rosettacode.org/wiki/Y_combinator
//     https://humanreadablemag.com/issues/1/articles/the-y-combinator-for-programmers
#include <cmath>
#include <functional>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
//#endregion

// Y combinator : C++ try again ?
auto Y = [](auto &&f) {
  auto A = [f](auto &&x) { return [f, x](auto &&y) { return f(x(x))(y); }; };
  return A(A);
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
  std::cout << sum_from_1(3) << '\n';

  //  auto s = [](auto &&x) { return std::sin(x); };
  //  auto ys = Y(s);
  //  std::cout << ys(1) << "\n";
}