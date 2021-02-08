//#region [Declarations]
#include <iostream>
#include <type_traits>
#include <vector>

struct Foo {
  typedef float value_type;
};
//#endregion

//#region [C++11]
template <typename, typename = void> // default behavior
constexpr bool has_value_type_11_v = false;

template <typename T>
constexpr bool
    has_value_type_11_v< // you can also use sizeof(X) in place of std::declval<X>()
        T, decltype(std::declval<typename T::value_type>(), void())> = true;
//#endregion

//#region [C++17]
template <typename, typename = void> // default behavior
constexpr bool has_value_type_17_v = false;

template <typename T>
constexpr bool has_value_type_17_v<T, std::void_t<typename T::value_type>> = true;
//#endregion

int main() {
  std::cout << std::boolalpha;
  std::cout << has_value_type_11_v<int> << " " << has_value_type_17_v<int> << "\n";
  std::cout << has_value_type_11_v<Foo> << " " << has_value_type_17_v<Foo> << "\n";
  using Vec = std::vector<int>;
  std::cout << has_value_type_11_v<Vec> << " " << has_value_type_17_v<Vec> << "\n";
}