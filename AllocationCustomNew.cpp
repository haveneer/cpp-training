//#region [Declarations]
#include <cstddef>
#include <iostream>
#include <new>
#include <memory>

#if defined(__clang__) && __cplusplus >= 201703L && __clang_major__ < 6
// This is a minimal workaround for clang 5.0 with missing std::byte type
namespace std {
enum class byte : unsigned char {};
}
#endif
//#endregion

class Foo {
public:
  // See also new[] and delete[]
  static void *operator new(std::size_t sz) {
    std::cout << "custom new for size " << sz << '\n';
    return ::operator new(sz);
  }
  static void *operator new(std::size_t sz, void *ptr) {
    std::cout << "custom placement new for size " << sz << '\n';
    return ::operator new(sz, ptr);
  }
  static void operator delete(void *ptr, std::size_t sz) {
    std::cout << "custom delete for size " << sz << '\n';
    ::operator delete(ptr);
  }

public:
  //#region [details]
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
  //#endregion
};

int main() {
  // Standard allocation
  std::unique_ptr foo1 = std::make_unique<Foo>(6);
  std::cout << "foo1=" << *foo1 << ")\n";

  // Stack allocation and placement new
  std::byte buffer[sizeof(Foo)]; // before C++17 uses 'unsigned char'
  //                             // in place of std::byte
  Foo *foo2 = new (buffer) Foo{10};
  std::cout << "foo2=" << *foo2 << ")\n";
  foo2->~Foo(); // rare case of explicit destructor call
  // delete foo2; // do not call it: it was not dynamically allocated

  int *foo3 = new (std::nothrow) int[1ull<<40]; // return nullptr if fails
  std::cout << "foo3=" << foo3 << '\n';
  delete[] foo3; // delete nullptr is legal
}