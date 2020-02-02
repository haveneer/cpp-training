//#region [Declarations]
#include <cstddef>
#include <iostream>
//#endregion

class Foo {
public:
  // include array allocation and disallocation
  explicit Foo(const std::size_t size) : m_size{size}, m_data{new int[size]} {}
  ~Foo() { delete[] m_data; }

  // Following 3-5-0 rule, we have to manage copy operator and ctor
  Foo(const Foo &) = delete;
  void operator=(const Foo &) = delete;

  //#region [details]
  friend std::ostream &operator<<(std::ostream &o, const Foo &that) {
    o << " ";
    for (std::size_t i = 0; i < that.m_size; ++i) {
      o << that.m_data[i] << " ";
    }
    return o;
  }
  //#endregion
private:
  const std::size_t m_size = 0; // non-static data member is a C++11 extension
  int *const m_data = nullptr;  // in-class initialization of
};

int main() {
  Foo foo{10};
  std::cout << "foo=(" << foo << ")\n";

  // Default object allocation
  int *pa = new int;
  std::cout << "*pa= " << *pa << "\n";

  // Object allocation with given initial value
  int *pb = new int{10};
  std::cout << "*pb= " << *pb << "\n";

  int *pc = pb;
  std::cout << "*pc= " << *pc << "\n";

  // delete pc; // don't disallocate pc; it would throw a double-free with pb
  delete pb; // without this there are memory leaks
  delete pa;
}