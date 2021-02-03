//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string_view>
#include <cassert>
#define DISPLAY(s)                                                    \
  std::cout << #s << "=\"" << (s) << "\"" << std::setw(40 - s.size()) \
            << " with length=" << (s).size() << "\n";
// clang-format off
//#endregion

int main() {
  const char *c_string = "Hello Amazing C++ World";

  std::string_view sv1{c_string};    /* from null terminated string */ DISPLAY(sv1);
  
  std::string_view sv2{c_string, 5}; /* using a length limiter */      DISPLAY(sv2);

  std::string cpp_string{c_string}; 

  std::string_view sv3{cpp_string};  /* from a C++ string */           DISPLAY(sv3);

  using namespace std::literals;
  auto             sv4 = "Hello\0 Null World"sv; /* from literals */   DISPLAY(sv4);
  std::string_view sv5 = "Hello\0 Null World";                         DISPLAY(sv5);

  auto sv6 = sv1; sv6.remove_prefix(6); sv6.remove_suffix(6);          DISPLAY(sv6);

  assert(std::string{sv6} != std::string(sv6.data())); // DIFFERENT !
  std::cout << sv6.data() << "\n";
}