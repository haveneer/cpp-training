//#region [Declarations]
#include <iostream>
//#endregion

class Table {
public:
  //#region [Constructors and destructor]
  Table() : m_size{0}, m_data{nullptr} {}
  explicit Table(unsigned n, double default_value = 0.)
      : m_size{n}, m_data{new double[m_size]} {
    for (unsigned i = 0; i < n; ++i)
      m_data[i] = default_value;
  }
  ~Table() { delete[] m_data; }
  //#endregion

  Table(const Table &t) : m_size{t.m_size}, m_data{new double[m_size]} {
    for (unsigned i = 0; i < m_size; ++i)
      m_data[i] = t.m_data[i];
  }
  Table &operator=(const Table &t) {
    //#region [FIXME self assignment]
    // if (&t == this) return *this; // FIXME
    //#endregion

    delete[] m_data; // What is the issue here ?
    m_size = t.m_size;
    m_data = new double[m_size];
    for (unsigned i = 0; i < m_size; ++i)
      m_data[i] = t.m_data[i];
    return *this;
  }

  /* explicit */ operator unsigned() { return m_size; } // FIXME explicit

  //#region [Implementation details]
  double &operator[](const unsigned i) { return m_data[i]; }
  double operator[](const unsigned i) const { return m_data[i]; }
  unsigned size() const { return m_size; }

private:
  unsigned m_size;
  double *m_data;
  //#endregion
};

std::ostream &operator<<(std::ostream &o, const Table &t) {
  o << "[ ";
  for (unsigned i = 0; i < t.size(); ++i)
    o << t[i] << ' ';
  o << ']';
  return o;
}

int main() {
  Table t1{5, 1.0};
  std::cout << "t1: " << t1 << '\n';
  Table t2{20, 2.0};
  std::cout << "t2: " << t2 << '\n';
  t1 = t2;
  std::cout << "t1 after: " << t1 << '\n';
  t2 = t2;
  std::cout << "t2 after: " << t2 << '\n';

  auto t3 = 3.0;
  t3 = t2;
  std::cout << "t3: " << t3 << '\n';
}