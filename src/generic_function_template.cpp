//#region [Declarations]
#include <iostream>
//#endregion

int min(int a, int b) { return (a < b) ? a : b; }
double min(double a, double b) { return (a < b) ? a : b; }

// We can say that a and b have same type
template <typename T> T max(T a, T b) { return (a > b) ? a : b; }

// Without inferred return type, it could be complex to write (required C++14)
template <typename T1, typename T2> auto sum(T1 a, T2 b) /* -> ??? */ {
  return a + b;
}

//#region [Horror of old C++03]
// With C++11      /!\ T1 and T2 must be default constructible !
template <typename T1, typename T2> decltype(T1{} + T2{}) sum_alt(T1 a, T2 b) {
  return a + b;
}

// With C++11 even if T1 and T2 are default constructible
template <typename T1, typename T2>
decltype(std::declval<T1>() + std::declval<T2>()) sum_alt2(T1 a, T2 b) {
  return a + b;
}

// C++03: all by hand
template <typename T1, typename T2> struct promote {};
template<> struct promote<int, int> { typedef int type; };
template<> struct promote<double, double> { typedef double type; };
template<> struct promote<int, double> { typedef double type; };
template<> struct promote<double, int> { typedef double type; };

template <typename T1, typename T2>
typename promote<T1, T2>::type sum_alt3(T1 a, T2 b) {
  return a + b;
}
//#endregion

int main() {
  std::cout << min(1, 2) << '\n';
  std::cout << min(3.0, 4.0) << '\n';
  // std::cout << min(5,6.0) << '\n'; // error: call to 'min' is ambiguous

  std::cout << max(1, 2) << '\n';
  std::cout << max(3.0, 4.0) << '\n';
  // std::cout << max(5,6.0) << '\n'; // error: call to 'max' is ambiguous
  std::cout << max<double>(5, 6.0) << '\n'; // explicit template type

  std::cout << sum(1, 2) << '\n';
  std::cout << sum(3.0, 4.0) << '\n';
  std::cout << sum(5, 6.0) << '\n';
  std::cout << sum<int, double>(5, 6.0) << '\n'; // almost same

  //#region [Horror of older C++]
  std::cout << sum_alt3(1, 2) << '\n';
  std::cout << sum_alt3(3.0, 4.0) << '\n';
  std::cout << sum_alt3(5, 6.0) << '\n';
  //#endregion
}