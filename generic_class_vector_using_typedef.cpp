//#region [Declarations]
#include <cassert>
#include <iostream>
//#endregion
typedef int T;
/***************** declarations *******************/

class Vector {
public:
  Vector(int n = 0) : m_size(n), m_data(new T[n]) {}
  Vector(const Vector &v);
  Vector &operator=(const Vector &v);
  virtual ~Vector() { delete[] m_data; }

public:
  inline int size() const { return m_size; }

  T &operator()(int i) {
    assert(i >= 0 && i < m_size);
    return m_data[i];
  }
  const T &operator()(int i) const;

  Vector operator*(T a) const;

  friend std::ostream &operator<<(std::ostream &o, const Vector &v) {
    v.print(o);
    return o;
  }

private:
  void print(std::ostream &o) const {
    for (int i = 0; i < m_size; ++i)
      o << m_data[i] << " ";
  }
  int m_size;
  T *m_data;
};

/***************** definitions *******************/

Vector::Vector(const Vector &v) : m_size(v.m_size) {
  m_data = new T[m_size];
  for (int i = 0; i < m_size; ++i)
    m_data[i] = v(i);
}

Vector &Vector::operator=(const Vector &v) {
  if (this != &v) {
    if (m_size != v.m_size) {
      delete[] m_data;
      m_size = v.m_size;
      m_data = new T[m_size];
    }
    for (int i = 0; i < m_size; ++i)
      m_data[i] = v(i);
  }
  return *this;
}

Vector Vector::operator*(T a) const {
  const Vector &v = *this;
  Vector newv(m_size);
  for (int i = 0; i < m_size; ++i)
    newv(i) = a * v(i);
  return newv;
}

const T &Vector::operator()(int i) const {
  assert(i >= 0 && i < m_size);
  return m_data[i];
}

// Fonctions

Vector operator*(T a, const Vector &v) { return v * a; }

/***************** main *******************/

int main() {
  const int n = 10;

  Vector u(n);
  for (int i = 0; i < n; ++i)
    u(i) = 10 + i; // initialisation
  std::cout << u << "\n";

  Vector v;
  v = u;
  std::cout << v << "\n";

  Vector w = v * 2;
  std::cout << w << "\n";

  Vector x;
  x = 2 * w;
  std::cout << x << "\n";
}
