//#region [Declarations]
#include <cmath>
#include <iostream>
#include <type_traits>
//#endregion

// Specialization for 'kind' of number
template <typename T> // does not exist if T is not an integral type
std::enable_if_t<std::is_integral_v<T>, T> power(T x, std::uint32_t n) {
  std::cout << "Integral implementation: " << x << "^" << n << " = ";
  T r = 1;
  while (n > 0) {
    if (n % 2 != 0) {
      r *= x;
    }
    x = x * x;
    n >>= 1;
  }
  std::cout << r << '\n';
  return r;
}

template <typename T> // does not exist if T is not a floating point type
std::enable_if_t<std::is_floating_point_v<T>, T> power(T x, std::uint32_t n) {
  T r = std::pow(x, n);
  std::cout << "FP implementation: " << x << "^" << n << " = " << r << '\n';
  return r;
}

int main() {
  // Better than using a pre-processor directive
  using integral_64bits_t = std::enable_if_t<(sizeof(void *) == 8), int64_t>;
  integral_64bits_t z = 0; // type does not exist if not 64bits arch

  power(2, 10);
  power(2., 10);
  // power(X{}, 10); // error: no matching function for call to 'power'
}
