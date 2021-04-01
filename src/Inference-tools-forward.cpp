//#region [Collapse all]
#include <iomanip>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#define DISPLAY1(a, b)                                                     \
  std::cout << std::right << std::setw(21) << #a << "  : " << std::right    \
            << std::setw(24) << type<decltype(a)>() << " | " << std::left  \
            << std::setw(23) << type<decltype(b)>() << " : " << std::right \
            << std::setw(32) << #b << '\n';
#define DISPLAY2(a, b, note)                                                        \
  std::cout << std::right << std::setw(22) << #a << " : " << std::left              \
            << std::setw(14) << a.meta << " -> " << std::setw(6) << a.mode << " | " \
            << std::left << std::setw(6) << b.mode << " <- " << std::setw(13)       \
            << b.meta << " : " << std::right << std::setw(33) << #b << " // "       \
            << (note) << '\n';
using namespace std::string_literals;
//#endregion

struct Concrete {
  Concrete(int &param) : mode{"lvalue"}, value{param} {}  // make using copy
  Concrete(int &&param) : mode{"rvalue"}, value(param) {} // make using move
  //#region [addMeta method]
  Concrete &addMeta(std::string &&meta) {
    this->meta = meta;
    return *this;
  }
  //#endregion
  std::string mode, meta;
  int value;
};

template <typename T> auto direct_factory(T &&param) {
  return Concrete(param) //
      .addMeta("(thru: T="s + type<T>() + ")");
}
template <typename T> auto forward_factory(T &&param) {
  return Concrete(std::forward<T>(param)) //
      .addMeta("(thru: T="s + type<T>() + ")");
}

int main() {
  int param{}; // for demo, we use `int` because move of int do not invalidate data

  // argument before any call
  DISPLAY1(param, std::move(param));
  // Direct call behaves perfectly: choose the right ctor according arg
  DISPLAY2(Concrete(param), Concrete(std::move(param)), "Perfect");
  // Indirect call without forwarding : always choose lvalue signature
  DISPLAY2(direct_factory(param), direct_factory(std::move(param)), "Not perfect");
  // Indirect call with forwarding : always choose the right signature
  DISPLAY2(forward_factory(param), forward_factory(std::move(param)), "Perfect");
}