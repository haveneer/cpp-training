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
  Foo foo{10}; // Stack allocation for one Foo object
  std::cout << "foo=(" << foo << ")\n";

  // Default dynamic object allocation (no initialization)
  int *pa = new int;
  std::cout << "*pa= " << *pa << "\n";

  // Object dynamic allocation with given initial value
  int *pb = new int{10};
  std::cout << "*pb= " << *pb << "\n";

  int *pc = pb;
  std::cout << "*pc= " << *pc << "\n";

  int *pd = new int[10]; // dynamic allocation of not initialized array
  //#region [Print me]
  std::cout << "pd=( ";
  for (int i = 0; i < 10; ++i)
    std::cout << pd[i] << ' ';
  std::cout << ")\n";
  //#endregion

  int *pe = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; // initialized array
  //#region [Print me]
  std::cout << "pe=( ";
  for (int i = 0; i < 10; ++i)
    std::cout << pe[i] << ' ';
  std::cout << ")\n";
  //#endregion

  try {
    while (true) {
      new int[100000000ul]; // allocated memory will be freed by OS
    }
  } catch (std::bad_alloc &e) {
    std::cout << "Cannot allocate a such huge bunch of memory\n";
  }

  delete[] pe; // without this there are memory leaks /!\ np garbage collector
  delete[] pd;
  // delete pc; // don't deallocate pc; it would throw a double-free with pb
  delete pb;
  delete pa, pa = nullptr; // reset pointer to nullptr is a good practice
  delete pa, pa = nullptr; // deleting a nullptr is always valid
}