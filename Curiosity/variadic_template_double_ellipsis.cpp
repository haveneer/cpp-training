//#region [declarations]
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <string>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

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
