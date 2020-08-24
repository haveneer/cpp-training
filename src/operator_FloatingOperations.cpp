using Number = double;

//#region [Declarations]
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

constexpr int bit_size(unsigned long n) {
  // equivalent to fls function (from C lib)
  int r = 1;
  while (n >>= 1u)
    ++r;
  return r;
}

constexpr std::size_t size =
    (1 + bit_size(std::numeric_limits<Number>::max_exponent) +
     std::numeric_limits<Number>::digits) /
    8;

#define HEADER()                                                              \
  display0();                                                                 \
  display0("expression", "hexfloat", "hex " + std::to_string(size * 8) + "b", \
           "approx. value", ' ');                                             \
  display0()

#define FOOTER() display0()

void display0(const std::string &expr_as_string = "",
              const std::string &expr_as_hexfloat = "",
              const std::string &expr_as_hex = "", const std::string &expr = "",
              const char fill = '-') {
  constexpr int hex_size = size * 2;
  // clang-format off
  std::cout << std::setfill(fill)
            << std::setw(16) << expr_as_string << " "
            << std::setw(hex_size+8) << expr_as_hexfloat << " "
            << std::setw(hex_size) << expr_as_hex << " "
            << std::setw(14) << expr
            << std::setfill(' ')
            << '\n';
  // clang-format on
}

#define DISPLAY(expr) display(#expr, (expr))

void display(const std::string &expr_as_string, const Number &expr) {
  constexpr std::size_t hex_size = size * 2;
  const auto *expr_byte_ptr = reinterpret_cast<const unsigned char *>(&expr);
  char expr_hex[2 * size + 1];
  for (std::size_t i = 0; i < size; ++i)
    sprintf(&expr_hex[2 * i], "%02x", expr_byte_ptr[size - i - 1]);
  expr_hex[2 * size] = 0; // make sure it is null terminated.

  // clang-format off
  std::cout << std::setw( 16) << expr_as_string << " "
            << std::setw(hex_size+8) << std::hexfloat << expr << " "
            // << std::setw(hex_size) << std::hex << expr_as_int << " "
            << std::setw(hex_size) << expr_hex << " "
            << std::setw(14) << std::defaultfloat << expr
            << '\n';
  // clang-format on
}
//#endregion

int main() {
  Number eps = std::numeric_limits<Number>::epsilon();
  Number min = std::numeric_limits<Number>::min();
  Number denorm_min = std::numeric_limits<Number>::denorm_min();
  Number pi = 3.1415926535897932384626L; // extended long double precision literal

  HEADER();
  DISPLAY(eps);
  DISPLAY(-eps);
  DISPLAY(min);
  DISPLAY(denorm_min);
  DISPLAY(1. + eps - 1.);   // Exact
  DISPLAY(2. + eps - 2.);   // Not exact
  DISPLAY(0.1 + 0.2 - 0.3); // Not exact : explain the accuracy if Number is float
  DISPLAY(std::tan(pi / 2));
  DISPLAY(std::sin(pi));
  FOOTER();

  static_assert(0.1 + 0.2 != 0.3);                   // Rounded computation
  static_assert(0.1 + 0.2 + 0.3 != 0.2 + 0.3 + 0.1); // And not commutative operation
  static_assert(0.7f != 0.7);              // Different accuracies, different values
  assert(std::abs(0.1 + 0.2 - 0.3) < eps); // Any floating test should be aware

  for (Number v = 0; v <= 0.3; v += 0.1) // TODO: what is the output ?
    std::cout << v << '\n';              // TODO: and if max value is 0.4 ?
}