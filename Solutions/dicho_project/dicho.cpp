#include "dicho.hpp"
#include "f.hpp"
#include <cassert>
#include <stdexcept>

// simplified version
double dicho(double a, double b) {
  dicho(a, b, 1e-6, nullptr);
  return (a + b) / 2;
}

// "dichotomie" (aka bisection algorithm) to search f(x)=0 for x \in [a,b]
// algorithm stops if |b_n-a_n| < eps or after 100 iterations
// Output:
// a,b: updated current search interval
// *niter: number of algorithm steps used (if niter != nullptr)
void dicho(double &a, double &b, double eps, int *niter) {
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