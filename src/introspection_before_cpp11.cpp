//#region [Declarations]
#include <iostream>
#include <vector>

struct Foo {
  typedef float type;
};
//#endregion

template <typename T> struct has_value_type {
  // yes and no have different sizes
  typedef char yes[1]; // sizeof(yes) == 1
  typedef char no[2];  // sizeof(no) == 2

  // Uses SFINAE (by hand)
  template <typename C> static yes &test(typename C::value_type *);
  template <typename> static no &test(...);

  // if the sizeof the result of calling test<T>(0) is equal to the sizeof(yes),
  // the first overload worked and T has a nested type named type.
  static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

int main() {
  std::cout << std::boolalpha;
  std::cout << has_value_type<int>::value << std::endl;
  std::cout << has_value_type<Foo>::value << std::endl;
  std::cout << has_value_type<std::vector<int>>::value << std::endl;
}