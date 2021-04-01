//#region [Declarations]
#include <iostream>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

int main() {
  auto sum = [](auto a, auto b) { return a + b; };
  std::cout << sum(1, 2) << '\n';
  std::cout << sum(3.0, 4.0) << '\n';
  std::cout << sum(5, 6.0) << '\n';

  std::cout << "----\n";

  auto update = [](auto &set, auto value) {
    std::cout << "Will update a " << type<decltype(set)>() << " with a "
              << type<decltype(value)>() << '\n';
    for (auto &e : set) {
      e += value;
    }
  };

  auto print = [](auto set) {
    for (const auto &e : set) {
      std::cout << e << ' ';
    }
    std::cout << '\n';
  };

  std::vector<int> v{1, 2, 3, 4};

  update(v, 2);
  print(v);

  // lazy control on accepted type
  update(v, 'c');
  print(v);
}