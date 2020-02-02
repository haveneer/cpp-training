//#region [Declaration]
#include <iostream>
#include <memory>
//#endregion

class Foo {
public:
  Foo() : Foo(0) {}
  explicit Foo(const int n) : m_n(n) {
    std::cout << "Ctor Foo(" << m_n << ") @" << this << "\n";
  }
  ~Foo() { std::cout << "Dtor Foo(" << m_n << ") @" << this << "\n"; }

  Foo(const Foo &) = delete;
  void operator=(const Foo &) = delete;
  Foo &operator=(const int n) {
    m_n = n;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &o, const Foo &that) {
    return o << "Foo(" << that.m_n << ") @" << &that;
  }

private:
  int m_n;
};

int main() {
  std::shared_ptr<Foo> p1 = std::make_shared<Foo>(5);
  std::weak_ptr<Foo> wp1 = p1; // wp1 tries to point on p1

  { // wp1 can point on underlying p1
    std::cout << "---------------\n";
    std::shared_ptr<Foo> p2 = wp1.lock();
    if (p2)
      std::cout << *p2 << "\n";
  }

  p1.reset(); // p1 is released

  { // wp1 cannot point on (deleted) underlying p1
    std::cout << "---------------\n";
    std::shared_ptr<Foo> p3 = wp1.lock();
    if (p3)
      std::cout << "nope :(\n";
  }
}
