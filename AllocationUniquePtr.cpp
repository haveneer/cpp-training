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

//#region [Functions]
auto f_by_copy(std::unique_ptr<Foo> p) {
  std::cout << "By copy: " << *p << "\n";
}

auto f_by_ref(std::unique_ptr<Foo> &p) {
  std::cout << "By ref: " << *p << "\n";
}

auto f_by_move(std::unique_ptr<Foo> &&p) {
  std::unique_ptr<Foo> &q = p; // TODO: what if not ref ?
  std::cout << "By move: " << *q << "\n";
}
//#endregion

int main() {
  {
    std::unique_ptr<Foo> p(new Foo{3});
    std::unique_ptr<Foo> p1 = std::make_unique<Foo>(4); // Requires C++14
    // std::unique_ptr<int> p2 = p1; // error: use of deleted function
    //                               // unique_ptr(const unique_ptr&) = delete;
    std::unique_ptr<Foo> p3 = std::move(p1); // p1 is lost
    std::cout << "p1 is alive ? " << (bool)p1 << "\n";
    // f_by_copy(p); // error: call to implicitly-deleted
    //               // copy constructor of 'std::unique_ptr<Foo>'
    f_by_ref(p);
    f_by_move(std::move(p)); // p could be lost, borrowed to the function
    std::cout << "p is alive ? " << (bool)p << "\n";
    f_by_copy(std::move(p)); // p is lost, borrowed to the function
    std::cout << "p is alive ? " << (bool)p << "\n";
    std::cout << "---------------\n";
    // p3.reset(); // automatically called at the end of scope
    // p1.reset(); // do nothing since p1 has already been moved
  }

  //#region [With array allocation]
  // Managing array with unique_ptr is available since C++11
  std::cout << "---------------\n";
  std::unique_ptr<Foo[]> q1{new Foo[2]};
  std::unique_ptr<Foo[]> q2 = std::make_unique<Foo[]>(2); // requires C++14
  //#endregion
}