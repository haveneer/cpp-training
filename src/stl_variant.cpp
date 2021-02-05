//#region [Declarations]
#include <cassert>
#include <iomanip>
#include <iostream>
#include <variant>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
#define DISPLAY_TYPE(F) \
  { std::cout << std::setw(14) << #F << " : " << type<decltype(F)>() << std::endl; }
//#endregion

class X {
public:
  X(const char c, const int i, const double f) : m_c(c), m_i(i), m_f(f) {}

private:
  const char m_c;
  const int m_i;
  const double m_f;
};

int main() {
  std::variant<char, int, double> v1;
  v1 = 'Z'; // can be set by any supported types (as declared)
  v1 = 3;
  v1 = 4.2; // 4.2f also allowed
  // v1 = "string"; // error: no viable overloaded '=' // not supported type
  std::cout << "sizeof(std::variant<char, int, double>) = " << sizeof(v1) << '\n';

  std::get<double>(v1);    // you can identify an alternative by its type
  std::get<2>(v1);         // or by its position
  assert(v1.index() == 2); // runtime info of available value

  std::variant<std::string> v2("Hello World");
  v2 = "null terminated c string"; // allowed because not ambiguous conversion

  // std::variant<X> v3; // error: not allowed because X is not default constructible
  std::variant<std::monostate, X> v4; // Ok using std::monostate as default
  DISPLAY_TYPE(std::get<0>(v4));
  v4.emplace<X>('Z', 3, 4.2); // Build inplace (no copy) an object from ctor args

  // Runtime check/access to values
  try {                 // an exception occurs if not available
    std::get<char>(v1); // now, v1 contains a double not a char
  } catch (const std::bad_variant_access &e) {
    std::cout << "Exception: " << e.what() << '\n';
  }
  assert(!std::holds_alternative<char>(v1)); // could be done as runtime check

  auto pval = std::get_if<char>(&v1); // returns a pointer (nullptr if not found)
  DISPLAY_TYPE(pval);
  if (pval) {
    std::cout << "v1 contains a char '" << pval << "'\n";
  } else {
    std::cout << "v1 does not contain any char\n";
  }
}