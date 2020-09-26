#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

// in f.h
using Real = double;
Real f(Real x);

// in f.cpp
const Real e = std::exp(1);
Real x0 = 1; // TODO: increase x0 from 1 to 40

Real f(Real x) { return x - x0 + std::exp(x) - std::pow(e, x); }

// in main.cpp

// The maximum error of a single floating-point operation is
// 0.5 units in the last place.
// http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition
double ulp(double f); // Unit in the Last Place function (is close to abs(f)*epsilon)

// "dichotomie" (aka bisection algorithm) to search f(x)=0 for x \in [a,b]
// algorithm stops if |b_n-a_n| < eps or after 100 iterations
// Output:
// a,b: updated current search interval
// *niter: number of algorithm steps used (if niter != nullptr)
template <typename F> // C++20 supports auto argument type
void dicho(double &a, double &b, F f, double eps, int *niter) {
  if (a > b) {
    throw std::invalid_argument("[a;b] is an empty interval");
  }
  if (eps <= 0) {
    throw std::invalid_argument("eps should be > 0");
  }

  int n = 0;
  Real fa = f(a);
  Real fb = f(b);
  if (fa * fb > 0) {
    throw std::invalid_argument("f(a) and f(b) have same sign");
  }

  // algorithm kernel
  while (fa * fb <= 0 && (b - a) >= eps) {
    Real c = (a + b) / 2, fc = f(c);
    if (fa * fc <= 0) {
      b = c;
      fb = fc;
    } else {
      assert(fc * fb <= 0); // should be true
      a = c;
      fa = fc;
    }
    if (++n >= 100) {
      if (niter != nullptr)
        *niter = n;
      throw std::runtime_error("STOP: max iteration count reached");
    }
  }
  if (niter != nullptr)
    *niter = n;
}

int main(int argc, char **argv) {
  if (argc > 1) {
    x0 = std::stod(argv[1]);
  }

  Real a = x0 / 2, fa = f(a);
  Real b = 2 * x0, fb = f(b);
  std::cout.precision(20); // set visual precision

  try {
    int n = 0;
    dicho(a, b, f, 1e-9, &n);
    std::cout << "After " << n << " iterations\n";
    std::cout << "a = " << a << "  f(a) = " << f(a) << "\n";
    std::cout << "b = " << b << "  f(b) = " << f(b) << "\n";
    std::cout.precision(6); // set visual precision
    std::cout << "|b-a| = " << std::abs(b - a)
              << " (ulp bound=" << std::max(ulp(a), ulp(b)) << ")\n";
  } catch (std::invalid_argument &e) {
    std::cerr << "Invalid Argument Error: " << e.what() << "\n";
  } catch (std::runtime_error &e) {
    std::cerr << "Runtime Error: " << e.what() << "\n";
  }
}

// in dicho.cpp

double ulp(double f) {
  // Definition of ULP in https://en.wikipedia.org/wiki/Unit_in_the_last_place
  // In radix b with precision p, if b^e ≤ |x| < b^{e+1},
  // then ULP(x) = b^{max(e,emin)−p+1}

  int f_exp{};
  /* double f_frac = */ std::frexp(f,
                                   &f_exp); // decompose number as fraction-exponent
  // i.e. f == f_frac * 2^f_exp

  auto e_min = std::numeric_limits<double>::min_exponent;
  // auto b = std::numeric_limits<double>::radix;
  auto p = std::numeric_limits<double>::digits;

  // implicitly uses b as equal to 2 in ldexp
  return std::ldexp(1, std::max(f_exp, e_min) - p + 1);
};
