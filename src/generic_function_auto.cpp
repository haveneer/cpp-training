//#region [Declarations]
#include <iostream>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
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