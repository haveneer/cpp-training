//#region [Collapse all]
#include <iomanip>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY_TYPE(X) \
  std::cout << std::setw(45) << #X << " : " << type<X>() << '\n'
//#endregion

int main() {
  struct X {};
  const X &x = X{}; // HINT because a rvalue can be assigned to a lvalue const ref
  // /!\ x is still valid (extended lifetime for temporary objects)

  using SumIntAndDoubleType = decltype(std::declval<int>() + std::declval<double>());
  DISPLAY_TYPE(SumIntAndDoubleType); // std::declval spontaneous build of object
                                     // at compile time (ONLY)
  // std::declval<int>(); // no runtime : error: symbol(s) not found

  struct Y {
    Y() = delete;
    auto foo() { return 1; }
  };
  DISPLAY_TYPE(decltype(std::declval<Y>())); // even for non-constructible types
  DISPLAY_TYPE(decltype(std::declval<Y>().foo())); // any symbolic op is possible
  DISPLAY_TYPE(std::decay_t<int[2]>);              // std::decay cleans up a type
  DISPLAY_TYPE(std::decay_t<int &&>);
  DISPLAY_TYPE(decltype(main));
  DISPLAY_TYPE(std::decay_t<decltype(main)>);
  DISPLAY_TYPE(std::decay_t<decltype(std::declval<Y>())>);
}