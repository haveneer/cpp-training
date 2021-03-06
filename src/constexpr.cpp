//#region [Declarations]
#include <iostream>

template <int N> void check_static() { std::cout << N << "\n"; }
//#endregion

// A simple constexpr function
constexpr int factorial1(int n) noexcept {
  return n < 2 ? 1 : n * factorial1(n - 1);
}

constexpr bool float_function(double x) { return x > 3.5; }

int main() {
  check_static<factorial1(5)>();

  int x = std::rand() % 20;
  std::cout << x << "! is " << factorial1(x) << "\n";

  check_static<float_function(5.0)>();
  check_static<float_function(0.5)>();

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

  // Better than #if preprocessing directive; code is fully checked
  if constexpr (false) {
    int i = 0;
    // int *p = i; // error: Error even though in discarded statement
  }
}