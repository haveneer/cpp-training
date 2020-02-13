//#region [Declarations]
#include <iostream>

struct Matrix {
  double m_value;
  double value() const { return m_value; }
};
//#endregion

// A good exception type with std::exception parent
struct MyException : std::exception {
  MyException(const char *m) : message(m) {}
  const char *message;
};

Matrix sumMatrix(const Matrix &m1, const Matrix &m2) noexcept {
  return Matrix{m1.value() + m2.value()};
}

void inverseMatrix(Matrix &m) {
  if (m.value() == 0)
    throw MyException{"Cannot inverse matrix"};
  else
    m.m_value = 1 / m.value();
}

int main() {
  Matrix m1{1};
  Matrix m2{2};
  Matrix m3 = sumMatrix(m1, m2);

  // noexcept is a part of function signature
  Matrix (*fps1)(const Matrix &, const Matrix &) noexcept = sumMatrix;
  // same
  Matrix (*fps2)(const Matrix &, const Matrix &) noexcept(true) = sumMatrix;
  // non-throwing function is implicitly convertible to potentially-throwing
  // function (since C++17)
  Matrix (*fps3)(const Matrix &, const Matrix &) noexcept(false) = sumMatrix;

  // error: cannot initialize a variable
  // potentially-throwing function cannot be converted to non-throwing function
  // void (*fpi1)(Matrix &) noexcept = inverseMatrix;
  // same
  // void (*fpi2)(Matrix &) noexcept(true) = inverseMatrix;

  // Ok
  void (*fpi3)(Matrix &) noexcept(false) = inverseMatrix;

  // clang-format off
  // noexcept as an operator to check if an expression can throw an exception
  std::cout << std::boolalpha
            << "sumMatrix is noexcept: "     << noexcept(sumMatrix(m1,m2)) << '\n'
            << "inverseMatrix is noexcept: " << noexcept(inverseMatrix(m1)) << '\n'
            << "Matrix is noexcept: "        << noexcept(Matrix{1}) << '\n'
            << "~Matrix is noexcept: "       << noexcept(std::declval<Matrix>().~Matrix()) << '\n';
  // clang-format on

  // Exact noexcept value using noexcept operator
  void (*fpi4)(Matrix &) noexcept(
      noexcept(inverseMatrix(std::declval<Matrix &>()))) = inverseMatrix;
}