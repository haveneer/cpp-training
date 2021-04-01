//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#define DISPLAY(x) std::cout << '\n' << #x << " is a " << type<decltype(x)>() << '\n'
//#endregion

template <typename Head, typename... Tail> void show(Head arg0, Tail... args) {
  std::cout << arg0;
  // List sequence trick, to evaluate in order pack expansion
  int dummy[/* sizeof...(args) */] = {(std::cout << ", " << args, 0)...};
  (void)dummy; // disable warning on unused variable
  std::cout << '\n';
}

std::string strs(std::initializer_list<int> ints) {
  std::string r{};
  for (auto i : ints) {
    r += std::to_string(i);
  }
  return r;
}

std::string str(int i) { return "str" + std::to_string(i); }

int f(int i) { return 2 * i; }

// Variadic template function
template <typename... Ts> void demo(Ts... args) {
  show(args...);
  show(args + 1 ...);
  show(&args + 1 ...);
  show(str(args)...);
  show(3 + f(args)...);
  show(strs({args...}) + str(args)...);

  auto v = {args...}; // or std::vector v = {args...} using CTAD (C++17)
  for (auto &&x : v)
    std::cout << x << "  ";
  DISPLAY(v);
}

// Surprising but somewhat useful expansion
template <typename... Ts> class MultiInheritance : public Ts... {
  std::tuple<Ts...> data;
};

auto sum11() { return 0; }
template <typename T0, typename... Ts>
auto sum11(T0 s, Ts... ts) { // requires a recursion to combine data
  return s + sum11(ts...);
}

int main() {
  demo(1, 2, 3, 4); // see demo for details
  std::cout << "sum = " << sum11(1, 2, 3, 4) << "\n";
}