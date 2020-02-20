//#region [Declarations]
#include <cassert>
#include <iostream>
//#endregion

/***************** declarations *******************/

template <typename T> class Vector {
public:
  Vector(int n = 0) : m_size(n), m_data(new T[n]) {}
  Vector(const Vector<T> &v);
  Vector<T> &operator=(const Vector<T> &v);
  virtual ~Vector() { delete[] m_data; }

public:
  inline int size() const { return m_size; }

  T &operator()(int i) {
    assert(i >= 0 && i < m_size);
    return m_data[i];
  }
  const T &operator()(int i) const;

  Vector<T> operator*(T a) const;

  friend std::ostream &operator<<(std::ostream &o, const Vector<T> &v) {
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

template <typename T> Vector<T>::Vector(const Vector<T> &v) : m_size(v.m_size) {
  m_data = new T[m_size];
  for (int i = 0; i < m_size; ++i)
    m_data[i] = v(i);
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector<T> &v) {
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

template <typename T> Vector<T> Vector<T>::operator*(T a) const {
  const Vector<T> &v = *this;
  Vector<T> newv(m_size);
  for (int i = 0; i < m_size; ++i)
    newv(i) = a * v(i);
  return newv;
}

template <typename U> const U &Vector<U>::operator()(int i) const {
  assert(i >= 0 && i < m_size);
  return m_data[i];
}

// Fonctions

template <typename T> Vector<T> operator*(T a, const Vector<T> &v) {
  return v * a;
}

/***************** main *******************/

int main() {
  const int n = 10;

  Vector<int> u(n);
  for (int i = 0; i < n; ++i)
    u(i) = 10 + i; // initialisation
  std::cout << u << "\n";

  Vector<int> v;
  v = u;
  std::cout << v << "\n";

  Vector<int> w = v * 2;
  std::cout << w << "\n";

  Vector<int> x;
  x = 2 * w;
  std::cout << x << "\n";
}
