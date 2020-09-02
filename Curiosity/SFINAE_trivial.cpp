#include <iostream>

template <typename T> void foo(typename T::type) { std::cout << "1st" << std::endl; }
template <typename T> void foo(T) { std::cout << "2nd" << std::endl; }

struct MyStruct {
  using type = int;
};

int main() {
  foo<MyStruct>(2);  // ok - calls first version
  foo<int>(2);       // also ok - calls second version
}