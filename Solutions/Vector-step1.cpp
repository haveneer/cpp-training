//#region [declarations]
#include <iostream>
#include <memory>
#include <utility>
//#endregion

class Vector {
public:
  Vector(int size) : m_size{size}, m_v{std::make_unique<int[]>(size)} {}
  Vector(const Vector &v) : Vector(v.m_size) { // delegated constructor
    for (auto i = 0; i < m_size; ++i)
      m_v[i] = v.m_v[i];
  }
  Vector(Vector &&v) : m_size{v.m_size}, m_v{std::move(v.m_v)} { v.m_size = 0; }
  // after move unique_ptr is reset to nullptr; hence, v.m_v is null

  auto &operator[](int i) { return m_v[i]; } // requires a lvalue ref return type
  auto operator[](int i) const { return m_v[i]; }

  Vector &operator=(const Vector &v) { // required to satisfy 3/5/0 rule
    if (this != &v) {                  // to prevent work/bug on case 'v=v'
      if (m_size != v.m_size) {        // if memory allocation is not good
        m_size = v.m_size;
        m_v = std::make_unique<int[]>(m_size); // rvalue copy operator
        // m_v.reset(new int[m_size]); // equivalent but we prefer to avoid 'new'
      }
      for (int i = 0; i < m_size; ++i)
        m_v[i] = v.m_v[i];
    }
    return *this; // rvalue return permits chaining : v1 = v2 = v3
  }
  Vector &operator=(Vector &&v) {        // required to satisfy 3/5/0 rule
    m_size = std::exchange(v.m_size, 0); // a = exchange(b, c) => a = b, b =c
    m_v = std::move(v.m_v);              // then v.m_v is null
    return *this;
  }

  void print(std::ostream &o) const;

private:
  int m_size;
  std::unique_ptr<int[]> m_v;
};

void Vector::print(std::ostream &o) const {
  o << "Vector(size=" << m_size << "; " << m_v.get() << " : ";
  for (int i = 0; i < m_size; ++i)
    o << m_v[i] << ' ';
  o << ')';
}

auto &operator<<(std::ostream &o, const Vector &v) {
  v.print(o);
  return o;
}

void f(Vector v) {}

int main() {

  Vector v1(3);
  std::cout << v1 << '\n';
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 2;
  v1[2]++;
  std::cout << v1 << '\n';
  Vector v2(5);
  std::cout << v2 << '\n';
  v2 = v1;
  std::cout << v2 << '\n';
  Vector v3{std::move(v1)}; // exactly equivalent to : auto v3 = std::move(v1);
  std::cout << v1 << '\n';
  std::cout << v3 << '\n';
  v2 = std::move(v3);
  std::cout << v2 << '\n';
  std::cout << v3 << '\n';

  // TODO for range compatibility for Vector
  // TODO define an algo using lambda on Vector
  // TODO make it generic / template
  // TODO optional: noexcept specifier
}