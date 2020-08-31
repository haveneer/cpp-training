#include "newton-vectorial--functions.hpp"
#include "newton-vectorial--matrix.hpp"
#include "newton-vectorial--vector.hpp"
#include "gtest/gtest.h"
#include <cassert>
#include <cmath>

auto f(const VectorNewton::Vector &x) -> VectorNewton::Vector {
  assert(x.size() == 2);
  VectorNewton::Vector r{x.size()};
  r(0) = x(0) * std::cos(x(1));
  r(1) = std::cos(x(0)) + std::sin(x(1));
  return r;
}

auto df(const VectorNewton::Vector &x) -> VectorNewton::Matrix {
  assert(x.size() == 2);
  VectorNewton::Matrix r{x.size()};
  r(0, 0) = std::cos(x(1));
  r(0, 1) = -x(0) * std::sin(x(1));
  r(1, 0) = -std::sin(x(0));
  r(1, 1) = std::cos(x(1));
  return r;
}

TEST(VectorNewton, MatrixOperation) {
  std::cout << "--------------------------------------------------\n";
  using namespace VectorNewton;
  constexpr const std::size_t N = 10;

  Matrix A{N};
  for (std::size_t i = 0; i < N; ++i)
    for (std::size_t j = 0; j < N; ++j)
      if (i == j)
        A(i, j) = 20;
      else if (i == j + 1 || j == i + 1)
        A(i, j) = -1;

  Vector rhs{N};
  for (std::size_t i = 0; i < N; ++i)
    rhs(i) = 1 + i;

  A(2, 2) = 0;

  std::cout << "A = \n" << A << std::endl;
  std::cout << "rhs = \n" << rhs << std::endl;

  Real condition_number = 0;
  Vector x = solve(A, rhs, &condition_number);
  std::cout << "x = \n" << x << std::endl;
  std::cout << "Condition number = " << condition_number << std::endl;
  Vector rhs2 = A * x;
  Real err = norm2(rhs - rhs2);
  std::cout << "err = " << err << "\n";
  ASSERT_LE(err, 1e-12);
}

TEST(VectorNewton, Solver) {
  std::cout << "--------------------------------------------------\n";
  using namespace VectorNewton;
  Vector xref{2};
  xref(0) = 1;
  xref(1) = 0.5;

  Vector rhs = f(xref);
  Vector xk{2};

  std::cout << "Newton iteration\n";
  for (std::size_t i = 0;; ++i) {
    Vector Fxk = f(xk) - rhs;
    Matrix J = df(xk);
    Vector delta = solve(J, -Fxk);
    std::cout << "Iteration " << std::setw(3) << i << " delta=" << norm2(delta)
              << "\n";
    if (norm2(delta) < 1e-12)
      break;
    xk += delta;
  };

  std::cout << "xref=" << xref << "\n";
  std::cout << "xsol=" << xk << "\n";
  const Real err = norm2(f(xk) - rhs);
  std::cout << "err = " << err << "\n";
  ASSERT_LE(err, 1e-14);
}
