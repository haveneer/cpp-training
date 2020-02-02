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

auto f(std::shared_ptr<Foo> p) {
  std::cout << *p << " (count=" << p.use_count() << ")\n";
}

int main() {
  { // Shared memory allocation
    std::shared_ptr<Foo> p1 = std::make_shared<Foo>(5);
    // std::shared_ptr<Foo> p1{new Foo{5}}; // equivalent to make_shared
    std::shared_ptr<Foo> p2 = p1;

    std::cout << *p1 << " (count=" << p1.use_count() << ")\n";
    *p2 = 42;
    std::cout << *p1 << " (count=" << p1.use_count() << ")\n";
    p1.reset();
    f(p2);
    // p2.reset(); // automatically called at the end of scope
  }

  { // unique ptr moved to a shared ptr
    std::cout << "---------------\n";
    std::unique_ptr<Foo> p(new Foo{5});
    std::shared_ptr<Foo> p2 = std::move(p); // p is null; p2 get resources
  }

  //#region [With array allocation]
  {
    std::cout << "---------------\n";
    // std::shared_ptr<Foo[]> q1{new Foo[5]}; // shared ptr on [] requires C++17
    // std::shared_ptr<Foo[]> q2 = std::make_shared<Foo[]>(5); // requires C++20

    // Hack to manage array with shared_ptr in C++11 (needs delete[] dtor)
    std::shared_ptr<Foo> q3(new Foo[2], std::default_delete<Foo[]>());
  }
  //#endregion
}