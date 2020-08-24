#include <iostream>

#define OP ,
#define STRING(s) #s

class A {
public:
  A(const int i) : m_i(i) { std::cout << "Building A(" << m_i << ")\n"; }
  A(const int i, const int j) : m_i(i+j) { std::cout << "Building A(" << m_i << ") from A(" << i << ") " << STRING(OP) << " A(" << j << ")\n"; }
  virtual ~A() { std::cout << "Destroying A(" << m_i << ")\n"; }
  int val() const { return m_i; }

private:
  int m_i;
};

A operator OP(const A &a, const A &b) {
  return A(a.val(), b.val());
}

int main() {
  A x = (A(1) OP A(2) OP A(4) OP A(8));
  //   std::cout << "Result is A(" << x.val() << ")\n";
  return 0;
}