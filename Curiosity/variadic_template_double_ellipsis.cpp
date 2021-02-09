//#region [declarations]
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY(x)                                                       \
  std::cout << std::setw(30) << #x << " : " << std::setw(6) << type<x>() \
            << std::endl;
//#endregion

// Obscure double ellipsis usage
template <typename T> struct X {};
template <typename T, typename... U> struct X<T(U..., ...)> /* double ellipsis */ {};

// Ready to use usage
template <typename T> T const &printf_helper(T const &x) { return x; }
char const *printf_helper(std::string const &x) { return x.c_str(); }

template <typename... Req, typename... Given>
int wrap_printf(int (*fn)(Req..., ...), // GCC/Clang allows to avoid comma (not VS)
                Given... args) {
  return fn(printf_helper(args)...);
}

int main() {
  DISPLAY(decltype(&std::printf));    // C ellipsis in printf args
  DISPLAY(X<decltype(std::fprintf)>); // watch U... and ...

  wrap_printf(&std::printf, "Hello %s\n", std::string("world!"));
  wrap_printf(&std::fprintf, stdout, std::string("Error %d"), 5);
}
