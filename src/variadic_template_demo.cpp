//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#define DISPLAY(x) std::cout << #x << " is a " << type<decltype(x)>() << '\n'
//#endregion

// Variadic template class
template <typename... Ts> struct Tuple {};

// Variadic template function
template <typename... Ts> void f(Ts... args) {
  //#region [details]
  std::cout << "f call with " << sizeof...(args)
            << ((1 < sizeof...(args)) ? " args; " : " arg;  ") << " types= ";
  ((std::cout << type<decltype(args)>() << "   "), ...); // fold expression: C++17
  std::cout << '\n';
  //#endregion
}

int main() {
  // Allowed class instanciations
  Tuple<> t0;                         // no template parameter
  Tuple<int> t1;                      // one template parameter
  Tuple<float, std::string, bool> t3; // three template parameters
  DISPLAY(t0);
  DISPLAY(t1);
  DISPLAY(t3);

  // Allowed function calls
  f();                  // 0 argument function call
  f(1);                 // 1 argument function call
  f(1, "Hello", true);  // 3 arguments function call
  f(1., "Hello", true); // 3 arguments function call (different signature)
}