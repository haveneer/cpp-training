#include <iostream>

template <typename T>
struct has_typedef_type
{
  // yes et no sont de tailles différentes
  typedef char yes[1]; // sizeof(yes) == 1
  typedef char no[2];   // sizeof(no) == 2

  // Uses SFINAE (by hand)
  template <typename C> static yes& test(typename C::type*);
  template <typename> static no& test(...);

  // if the sizeof the result of calling test<T>(0) is equal to the sizeof(yes),
  // the first overload worked and T has a nested type named type.
  static const bool value = sizeof(test<T>(0)) == sizeof(yes);
};

struct foo { typedef float type; };

int main()
{
  std::cout << std::boolalpha;
  std::cout << has_typedef_type<int>::value << std::endl;
  std::cout << has_typedef_type<foo>::value << std::endl;
}