#include <iostream>
#include <vector>

// The order doesn't matter
template <typename T> void foo(typename T::type) { std::cout << "1st" << std::endl; }
template <typename T> void foo(T) { std::cout << "2nd" << std::endl; }

struct MyStruct {
  using type = int;
};

template <typename T> typename T::size_type mysize(T const &t) { return t.size(); }

// We cannot overload on return type and could cause: 'mysize' is ambiguous
// template <typename T> T mysize(T const &t) { return t; }

int main() {
  foo<MyStruct>(2); //      ok - calls first version
  foo<int>(2);      // also ok - calls second version

  mysize(std::vector<int>(8)); // OK
  // mysize(8); // error: no matching function for call to 'mysize'
}