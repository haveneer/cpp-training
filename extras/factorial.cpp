#include <iostream>

// Standard runtime function
int factorialF(int n) { return n < 2 ? 1 : n * factorialF(n - 1); }

#include <type_traits>

// compile time template version
template <typename T> T factorialT(T n) {
  static_assert(std::is_integral<T>::value, "factorial requires integral parameter");
  return n < 2 ? 1 : n * factorialT(n - 1);
}

// compile time constexpr version
constexpr int factorialFE(int n) noexcept {
  return n < 2 ? 1 : n * factorialFE(n - 1);
}

int main() {
  std::cout << factorialF(8) << "\n";

  // factorialT(3.); // error: static assertion failed: factorial requires integral
  // parameter
  factorialT(5);

  // Can do static computation
  static_assert(factorialFE(5) == 120);

  // and runtime computation
  int x = std::rand() % 20;
  std::cout << x << "! is " << factorialFE(x) << "\n";

  // A simple constexpr function which can fail
  auto factorial2 = [](int n) constexpr {
    if (n >= 0)
      return factorialFE(n - 1);
    else
      throw std::out_of_range("");
  };

  constexpr int n = 1;
  static constexpr int f2 = factorial2(n); // TODO: What happens if n is -1 ???
  std::cout << n << "! is " << f2 << "\n";
}