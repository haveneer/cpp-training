#include "newton-vectorial--functions.hpp"
#include <cassert>
#include <cmath>
#include <exception>
#include <iomanip>
#include <iterator>
#include <vector>

namespace VectorNewton {

std::ostream &operator<<(std::ostream &o, const Matrix &m) {
  for (std::size_t i = 0; i < m.size(); ++i) {
    for (std::size_t j = 0; j < m.size(); ++j) {
      o << std::setw(6) << m(i, j) << " ";
    }
    o << "\n";
  }
  return o;
}

std::ostream &operator<<(std::ostream &o, const Vector &v) {
  for (std::size_t i = 0; i < v.size(); ++i) {
    o << std::setw(6) << v(i) << " ";
  }
  return o;
}

Vector operator*(const Matrix &m, const Vector &x) {
  assert(m.size() == x.size());
  const std::size_t n = m.size();
  Vector r{n};
  for (std::size_t i = 0; i < n; ++i) {
    for (std::size_t j = 0; j < n; ++j) {
      r(i) += m(i, j) * x(j);
    }
  }
  return r;
}

namespace {

auto LUSolver(const Matrix &LU, const std::vector<std::size_t> &pivot) {
  return [n = LU.size(), &pivot, &LU](Vector pivot_b) {
    Vector x{n};
    // Solve the linear equation Lx = B for x, where L is a lower triangular
    // matrix.
    for (std::size_t k = 0; k < n; ++k) {
      if (pivot[k] != k) {
        std::swap(pivot_b(k), pivot_b(pivot[k]));
      }
      x(k) = pivot_b(k);
      for (std::size_t i = 0; i < k; ++i)
        x(k) -= x(i) * LU(k, i);
      x(k) /= LU(k, k);
    }

    // Solve the linear equation Ux = y, where y is the solution obtained above
    // of Lx = B and U is an upper triangular matrix.
    // The diagonal part of the upper triangular part of the matrix is
    // assumed to be 1.0.
    for (std::size_t k = n; k-- > 0;) {
      for (std::size_t i = k + 1; i < n; ++i)
        x(k) -= x(i) * LU(k, i);
    }
    return x;
  };
};

auto conditionNumberEstimator(const Matrix &m, const Matrix &LU,
                              const std::vector<std::size_t> &pivot) {
  auto inner_solve = LUSolver(LU, pivot);
  const std::size_t n = LU.size();
  Vector rmax{n}, rmin{n};
  for (std::size_t i = 0; i < n; ++i)
    rmin(i) = rmax(i) = 1;
  for (std::size_t cv = 0; cv < 5; ++cv) { // 5 iterations is arbitrary
    Vector vmax = m * rmax;
    const Real vnormmax = norm2(vmax);
    Vector vmin = inner_solve(rmin.copy());
    const Real vnormmin = norm2(vmin);
    for (std::size_t i = 0; i < n; ++i) {
      rmax(i) = vmax(i) / vnormmax;
      rmin(i) = vmin(i) / vnormmin;
    }
  }
  const Real lmax = norm2(m * rmax);
  const Real lmin = 1.0 / norm2(solve(m, rmin));
  //    std::cout << "Lmax=" << lmax << "\n";
  //    std::cout << "Lmin=" << lmin << "\n";
  return lmax / lmin;
}

} // namespace

Vector solve(const Matrix &m, const Vector &b, Real *condition_number) {
  // Inspiré de
  // http://www.mymathlib.com/c_source/matrices/linearsystems/crout_pivot.c

  assert(m.size() == b.size());
  const std::size_t n = m.size();

  Matrix LU = m.copy();
  std::vector<std::size_t> pivot(n, 0);

  {
    // For each row and column, k = 0, ..., n-1,
    for (std::size_t k = 0; k < n; ++k) {
      // find the pivot row
      pivot[k] = k;
      Real max = std::abs(LU(k, k));
      for (std::size_t j = k + 1; j < n; ++j) {
        if (max < std::abs(LU(j, k))) {
          max = std::abs(LU(j, k));
          pivot[k] = j;
        }
      }

      // and if the pivot row differs from the current row,
      // then interchange the two rows.
      if (pivot[k] != k)
        for (std::size_t j = 0; j < n; ++j) {
          std::swap(LU(k, j), LU(pivot[k], j));
        }

      // and if the matrix is singular, return error
      if (LU(k, k) == 0.0)
        throw std::runtime_error{"Singular matrix"};

      // otherwise find the upper triangular matrix elements for row k.
      for (std::size_t j = k + 1; j < n; ++j) {
        LU(k, j) /= LU(k, k);
      }

      // update remaining matrix
      for (std::size_t i = k + 1; i < n; ++i)
        for (std::size_t j = k + 1; j < n; ++j)
          LU(i, j) -= LU(i, k) * LU(k, j);
    }
  }

  //  std::cout << "pivot: ";
  //  std::copy(pivot.begin(), pivot.end(),
  //            std::ostream_iterator<std::size_t>(std::cout, " "));
  //  std::cout << std::endl;

  if (condition_number != nullptr) {
    *condition_number = conditionNumberEstimator(m, LU, pivot);
  }

  return LUSolver(LU, pivot)(b.copy());
}

Vector operator-(const Vector &a, const Vector &b) {
  assert(a.size() == b.size());
  const std::size_t n = a.size();
  Vector r{n};
  for (std::size_t i = 0; i < n; ++i) {
    r(i) = a(i) - b(i);
  }
  return r;
}

Vector operator-(const Vector &a) {
  const std::size_t n = a.size();
  Vector r{n};
  for (std::size_t i = 0; i < n; ++i) {
    r(i) = -a(i);
  }
  return r;
}

void operator+=(Vector &a, const Vector &b) {
  const std::size_t n = a.size();
  for (std::size_t i = 0; i < n; ++i) {
    a(i) += b(i);
  }
}

Real norm2(const Vector &x) {
  const std::size_t n = x.size();
  Real r = 0;
  for (std::size_t i = 0; i < n; ++i) {
    r += x(i) * x(i);
  }
  return std::sqrt(r);
}

} // namespace VectorNewton