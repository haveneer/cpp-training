//#region [Declarations]
#include <iostream>

class Matrix {
public:
  explicit Matrix(double d) : m_d{d} {
    std::cout << "Building Matrix{" << m_d << "}\n";
  }
  void operator=(double d) { m_d = d; }
  ~Matrix() { std::cout << "Destroying Matrix{" << m_d << "}\n"; }

  double value() const { return m_d; }

private:
  double m_d;
};
//#endregion

// A good exception type with std::exception parent
struct MyException : std::exception {
  MyException(const char *m) : message(m) {}
  const char *message;
};

void inverseMatrix(Matrix &m) {
  if (m.value() == 0)
    throw MyException{"Cannot inverse matrix"};
  else
    m = 1 / m.value();
}

int main() {
  try {
    // Follow object calls and ctor/dtor
    Matrix m1{1};
    inverseMatrix(m1);
    std::cout << "inverseMatrix(m1) : done\n";

    Matrix * m2 = new Matrix{2}; // TODO: Is it a good idea ??
    inverseMatrix(*m2);
    std::cout << "inverseMatrix(m2) : done\n";

    Matrix m3{0};
    inverseMatrix(m3);
    std::cout << "inverseMatrix(m3) : done\n";

    std::cout << m1.value() + m2->value() + m3.value() << '\n';
    delete m2; // TODO: end of m2. Are you sure ?
  } catch (MyException &e) {
    std::cout << "Catch exception: MyException{" << e.message << "}\n";
  } catch (...) {
    std::cout << "Catch and rethrow unknown exception\n";
    throw;
  }
}