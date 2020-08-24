//#region [Declaration]
#include <cassert>
#include <iostream>
#include <vector>
using Vector = std::vector<double>;
//#endregion

class IMatrix {
protected:
  IMatrix() = default;

public:
  virtual Vector product(const Vector &v) const = 0;
  virtual ~IMatrix() = default;
};

class DiagonalMatrix : public IMatrix {
public:
  DiagonalMatrix(const Vector &diag) : _diag{diag} {}
  Vector product(const Vector &v) const override;

private:
  Vector _diag;
};

Vector DiagonalMatrix::product(const Vector &v) const {
  assert(v.size() == _diag.size());
  const Vector::size_type n = v.size();
  Vector result(n);
  for (std::decay_t<decltype(n)> i = 0; i < n; ++i) {
    result[i] = v[i] * _diag[i];
  }
  return result;
}

int main() {
  IMatrix *m = new DiagonalMatrix{Vector{1, 2, 3, 4}};

  Vector v{0, 2, 4, 6};
  Vector r = m->product(v);
  for (auto e : r) {
    std::cout << e << "\n";
  }

  delete m;
}