//#region [Declarations]
#include <cassert>
#include <cmath>
#include <iostream>
#include <tuple>
#include <functional>
//#endregion

#include <optional>

long my_sqrt1(const long n, bool &ok) {
  ok = (n >= 0);
  return (ok) ? std::sqrt(n) : 0;
}

bool my_sqrt2(const long n, long &r) {
  const bool ok = (n >= 0);
  r = (ok) ? std::sqrt(n) : 0;
  return ok;
}

std::tuple<long, bool> my_sqrt3(const long n) {
  const bool ok = (n >= 0);
  const long r = (ok) ? std::sqrt(n) : 0;
  return {r, ok};
}

std::optional<long> my_sqrt4(const long n) {
  return (n >= 0) ? std::optional<long>{std::sqrt(n)} : std::nullopt;
}

int main() {
  const long n = -42;

  bool b1{};
  long r1 = my_sqrt1(n, b1);
  //#region [Process r1]
  if (b1) {
    std::cout << "sqrt(" << n << ") is " << r1 << "\n";
  } else {
    std::cout << "sqrt(" << n << ") does not exist\n";
  }
  //#endregion

  //#region [Process r2]
  long r2{};
  bool b2 = my_sqrt2(n, r2);
  if (b2) {
    std::cout << "sqrt(" << n << ") is " << r2 << "\n";
  } else {
    std::cout << "sqrt(" << n << ") does not exist\n";
  }
  //#endregion

  auto [r3, b3] = my_sqrt3(n); // Structured binding from a std::tuple
  //#region [Process r3]
  if (b3) {
    std::cout << "sqrt(" << n << ") is " << r3 << "\n";
  } else {
    std::cout << "sqrt(" << n << ") does not exist\n";
  }
  //#endregion

  auto r4opt = my_sqrt4(n); // std::optional HERE
  if (r4opt) {
    std::cout << "sqrt(" << n << ") is " << r4opt.value() << "\n";
  } else {
    std::cout << "sqrt(" << n << ") does not exist\n";
  }

  r4opt.emplace(n);              // set a new value
  r4opt.reset();                 // reset the option to std::nullopt
  assert(r4opt == std::nullopt); // comparable to std::nullopt (any T)
  std::cout << "Get or default: " << r4opt.value_or(0) << "\n"; // get default value
  std::cout << "sizeof(r4opt) = " << sizeof(r4opt) << "\n";     // could be expensive

  std::string a_string = "Hello";
  std::optional<std::reference_wrapper<std::string>> r5ref;
  r5ref = std::ref(a_string); // std::ref creates a std::reference_wrapper
  std::cout << "Get optional ref: " << r5ref->get() << '\n';
  assert(&a_string == &r5ref->get()); // same address; not a copy
}