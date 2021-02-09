//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

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