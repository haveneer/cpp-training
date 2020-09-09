using Number = double;

//#region [Declarations]
#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <cstring>

/* exciting blog on floating numbers:
 * https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 * https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html#689
 */

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
           "bin", "approx. value", "Custom IEEE754 decoding", ' ');           \
  display0()

#define FOOTER() display0()

void display0(const std::string &expr_as_string = "",
              const std::string &expr_as_hexfloat = "",
              const std::string &expr_as_hex = "",
              const std::string &expr_as_int = "", const std::string &expr = "",
              const std::string &analysis = "", const char fill = '-') {
  constexpr int hex_size = size * 2;
  // clang-format off
  std::cout << std::setfill(fill)
            << std::setw(30) << expr_as_string << " "
            << std::setw(hex_size+8) << expr_as_hexfloat << " "
            << std::setw(hex_size) << expr_as_hex << " "
            << std::setw(hex_size*4) << expr_as_int << " "
            << std::setw(14) << expr
            << std::setw(52) << analysis
            << std::setfill(' ')
            << '\n';
  // clang-format on
}

#define DISPLAY(expr) display(#expr, (expr), computeNumber(expr))

template <typename T> struct float_integer {};
template <> struct float_integer<double> { using type = std::uint64_t; };
template <> struct float_integer<float> { using type = std::uint32_t; };

void display(const std::string &expr_as_string, const Number &expr,
             const std::string &extra = "") {
  constexpr std::size_t hex_size = size * 2;
  using expr_as_int_t = typename float_integer<Number>::type;
  const expr_as_int_t expr_as_int = *reinterpret_cast<const expr_as_int_t *>(&expr);

  // clang-format off
  std::cout << std::setw( 30) << expr_as_string << " "
            << std::setw(hex_size+8) << std::hexfloat << expr << " "
            << std::setw(hex_size) << std::hex << expr_as_int << " " << std::dec
            << std::bitset<hex_size*4>(expr_as_int) << " "
            << std::setw(14) << std::defaultfloat << expr << " "
            << std::setw(52) << extra
            << '\n';
  // clang-format on
}

//#endregion

auto computeNumber(const Number &expr) {
  using int_type = float_integer<Number>::type;
  const int_type expr_as_int = *reinterpret_cast<const int_type *>(&expr);

  constexpr std::size_t max_exp = std::numeric_limits<Number>::max_exponent;
  constexpr std::size_t exp_bsize = bit_size(max_exp);
  constexpr std::size_t fraction_bsize = std::numeric_limits<Number>::digits;
  constexpr std::size_t bsize = 8 * size;

  auto my_exp2 = [](int n) {
    Number r = 1.;
    if (n > 0) {
      for (int i = 0; i < n; ++i)
        r *= 2;
    } else if (n < 0) {
      for (int i = 0; i < -n; ++i)
        r /= 2;
    }
    return r;
  };

  const int_type fraction = expr_as_int & ((1ul << (fraction_bsize - 1)) - 1);
  const int_type exponent =
      (expr_as_int >> (fraction_bsize - 1)) & ((1ul << exp_bsize) - 1ul);
  const bool sign_bit = expr_as_int & (1ul << (bsize - 1));

  std::ostringstream oss;
  oss << "[s=" << sign_bit << " e=" << std::dec << exponent << " f=" << std::hex
      << fraction << std::dec << "]";

  auto compare = [](const Number &a, const Number &b, std::ostream &oss) {
    if ((std::isnan(a) && std::isnan(b)) || (a == b))
      oss << "[  OK  ]" << std::setw(12) << "";
    else
      oss << "[FAILED]" << std::setw(12) << b;
  };

  if (exponent == ((1ul << exp_bsize) - 1)) { // NaNs and Infs
    if (fraction == 0) {                    // Infs
      auto r = std::numeric_limits<Number>::infinity();
      if (sign_bit)
        r = -r;
      compare(expr, r, oss);
    } else { // NaNs
      compare(expr, std::numeric_limits<Number>::quiet_NaN(), oss);
    }
  } else {
    const bool denormalized = (exponent == 0);

    Number r = (denormalized) ? 0. : 1.;
    for (int i = 1; i <= fraction_bsize - 1; ++i)
      if (expr_as_int & (1ul << ((fraction_bsize - 1) - i)))
        r += my_exp2(-i);

    if (denormalized)
      r *= my_exp2(-(max_exp - 2));
    else
      r *= my_exp2(exponent - (max_exp - 1));

    if (sign_bit)
      r = -r;
    compare(expr, r, oss);
  }
  return oss.str();
}

Number asNumber(const float_integer<Number>::type &expr_as_int) {
  Number expr = 0;
  std::memcpy(&expr, &expr_as_int, sizeof(Number));
  return expr;
}

template <unsigned long... b> auto bits() { return asNumber((0ul | ... | (1ul << b))); }

struct float_bit {
  const unsigned long long n = 0;
  operator Number() { return asNumber(static_cast<float_integer<Number>::type>(n)); }
};

constexpr auto operator"" _b(const unsigned long long i) {
  return float_bit{1ul << i};
}
constexpr auto operator|(const float_bit &a, const float_bit &b) {
  return float_bit{a.n | b.n};
}

constexpr float_bit minus = {1ul << (size * 8 - 1)};
constexpr auto exponent(const unsigned long i) {
  return float_bit{i << (std::numeric_limits<Number>::digits - 1u)};
}

int main() {
  using limits = std::numeric_limits<Number>;

  auto eps = limits::epsilon();

  HEADER();
  DISPLAY(limits::epsilon());
  DISPLAY(limits::min());
  DISPLAY(limits::max());
  DISPLAY(limits::min() / 10);
  DISPLAY(limits::denorm_min());
  DISPLAY(limits::infinity());
  DISPLAY(-limits::infinity());
  DISPLAY(limits::quiet_NaN());
  DISPLAY(limits::signaling_NaN());
  DISPLAY(1. + eps - 1.); // Exact
  DISPLAY(2. + eps - 2.); // Not exact

  FOOTER();

  DISPLAY(0);
  DISPLAY(1);
  DISPLAY(1.1);
  DISPLAY(314);

  FOOTER();

  DISPLAY(bits<>());
  DISPLAY(bits<0>());
  DISPLAY(bits<1>());
  DISPLAY(bits<2>());
  DISPLAY(5_b); // min
  DISPLAY(minus | 5_b);
  DISPLAY(exponent(1));
  DISPLAY(exponent(1) | 5_b);

  FOOTER();

  DISPLAY(bits<48>());
  DISPLAY(bits<49>());
  DISPLAY(bits<50>());
  DISPLAY(bits<51>());
  DISPLAY(bits<52>());
  DISPLAY(bits<53>());
  DISPLAY(bits<54>());
  DISPLAY(bits<55>());
  DISPLAY(bits<56>());
  DISPLAY(bits<57>());
  DISPLAY(bits<58>());
  DISPLAY(bits<59>());
  DISPLAY(bits<60>());
  DISPLAY(bits<61>());
  DISPLAY(bits<62>());
  DISPLAY(bits<63>());

  FOOTER();
}