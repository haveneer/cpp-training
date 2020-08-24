//#region [Declarations]
#include <cstdlib>
#include <iostream>
#include <limits>

using Matrix = double;
//#endregion

double divide(double a, double b) {
  if (b == 0)
    return std::numeric_limits<double>::quiet_NaN();
  else
    return a / b;
}

[[nodiscard]] bool inverseMatrix1(Matrix &m) {
  if (m == 0)
    return false;
  else
    m = 1 / m;
  return true;
}

struct [[nodiscard]] MatrixError {
  bool isOk;
  const char *message;
};

MatrixError inverseMatrix2(Matrix &m) {
  if (m == 0)
    return {false, "null matrix"};
  else
    m = 1 / m;
  return {true, "Ok"};
}

int main() {
  // Error management using special return values
  auto d1 = divide(2, 0);
  std::cout << "d1 = " << d1 << " (is there an error ? " << (d1 != d1) << ")\n";

  // Error management using special argument (and errno)
  char *end{};
  const char *s1 = "-1231233456456456456456";
  auto l1 = std::strtol(s1, &end, 10);
  if (s1 != end) // Something has been read
    std::cout << "l1 = " << l1 << " (is there an error ? " << (errno == ERANGE)
              << ")\n";
  else
    std::cout << "l1 = cannot read\n";

  // Error management using return value
  Matrix m1{0};
  inverseMatrix1(m1); // warning: ignoring return value of function declared with 'nodiscard' attribute
  bool isOk = inverseMatrix1(m1);
  std::cout << "m1 = " << m1 << " (is there an error ? " << (!isOk) << ") \n";

  // Error management using dedicated error type
  inverseMatrix2(m1); // warning: ignoring return value of function declared with 'nodiscard' attribute
  MatrixError matrixError = inverseMatrix2(m1);
  std::cout << "m1 = " << m1 << " (is there an error ? " << (!matrixError.isOk) << ") \n";
}