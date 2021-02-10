//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

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