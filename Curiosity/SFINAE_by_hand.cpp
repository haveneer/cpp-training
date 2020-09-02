//#region [Collapse all]
//#region [Declarations]
#include <iostream>
#include <type_traits>
//#endregion

template <bool B> using bool_ = std::integral_constant<bool, B>;

template <typename... Args> using requires = void;

template <typename T, typename EnableIf = void>
struct has_size_member : bool_<false> {};

#define has_member(T, M) decltype(std::declval<T>() M)

template <typename T>
struct has_size_member<T, requires<has_member(T, .size()), typename T::size_type>>
    : bool_<true> {};

// Examples
struct A {
  using size_type = unsigned;
  size_type size() { return 0; }
};

struct B {
  using no_size_type = unsigned;
  int no_size() { return 0; }
};

int main() {
  std::cout << "A has size() and size_type: " << has_size_member<A>::value << '\n';
  std::cout << "B has size() and size_type: " << has_size_member<B>::value << '\n';
}
//#endregion