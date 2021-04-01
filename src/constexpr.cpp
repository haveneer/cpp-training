//#region [Declarations]
#include <iostream>
//#endregion

// A simple constexpr function
constexpr int factorial1(int n) noexcept {
  return n < 2 ? 1 : n * factorial1(n - 1);
}

// very few math functions are constexpr (due to expected side effect and errno)
constexpr double pi = 3.14159265358979323846; // not only integer computations
constexpr bool float_function(double x) { return x > pi; }

template <int N> void static_check() { std::cout << N << '\n'; }

int main() {
  static_check<factorial1(5)>(); // compile time call

  int x = std::rand() % 20;
  std::cout << x << "! is " << factorial1(x) << "\n"; // runtime call

  static_check<float_function(5.0)>();
  static_check<float_function(0.5)>();

  // A simple constexpr function which can fail
  auto factorial2 = [](int n) constexpr {
    if (n >= 0)
      return factorial1(n - 1);
    else
      throw std::out_of_range("");
  };

  constexpr int n = 1;
  static constexpr int f2 = factorial2(n); // TODO: What happens if n is -1 ???
  std::cout << n << "! is " << f2 << "\n";
}