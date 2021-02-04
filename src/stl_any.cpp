//#region [Declarations]
#include <functional>
#include <iomanip>
#include <iostream>
#include <typeinfo>
#include <vector>
#include <any>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
std::string demangle(const std::type_info &type) { return demangle(type.name()); }
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
const char *demangle(const std::type_info &type) { return type.name(); }
#endif
#define DISPLAY_TYPE(F) \
  { std::cout << std::setw(14) << #F << " : " << type<decltype(F)>() << std::endl; }
//#endregion

int main() {
  std::any a; // can contain any object
  std::cout << "a has " << ((a.has_value()) ? "a" : "no") << " value\n";
  a = "Hello World";
  std::cout << demangle(a.type()) << ": " << std::any_cast<const char *>(a) << '\n';
  a = 3.1415;
  std::cout << demangle(a.type()) << ": " << std::any_cast<double>(a) << '\n';

  try { // You can try to get the value for a given type
    std::cout << std::any_cast<float>(a) << '\n'; // /!\ no conversion allowed
  } catch (const std::bad_any_cast &e) { // exception will occur if the type is wrong
    std::cout << "Exception: " << e.what() << '\n';
  }

  // TODO: what happens if we remove '&' in v1 declaration
  auto &v1 = a.emplace<std::vector<int>>({1, 2, 3}); // build from parameters
  DISPLAY_TYPE(v1); // is a _almost_ std::vector<int>
  v1[0] = v1[1] = v1[2] = 0;
  std::cout << std::setw(17) << "a.type() : " << demangle(a.type()) << '\n';
  auto v2 = std::any_cast<std::vector<int>>(a); // TODO: same question: & or not ?
  DISPLAY_TYPE(v2);                             // is a std::vector<int>
  std::cout << v2[0] << " " << v2[1] << "  " << v2[2] << '\n'; // 0 or not 0 ?
  a.reset();                                                   // clear

  // Don't throw the type: you will not able to recover it
  std::any a1 = [] { std::cout << "Lambda #1.\n"; }; // how to get back the lambda ?
  std::cout << std::setw(17) << "a1.type() : " << demangle(a1.type()) << '\n';
  using Lambda = std::function<void(void)>;
  try { // std::function is compatible but not exact type
    std::any_cast<Lambda>(a1)();
  } catch (const std::bad_any_cast &e) {
    std::cout << "Exception: " << e.what() << '\n';
  }

  // Not optimal but convenient (cast to std::function)
  auto a2 = std::make_any<Lambda>([] { std::cout << "Lambda #2.\n"; });
  std::cout << std::setw(17) << "a2.type() : " << demangle(a2.type()) << "\n";
  std::any_cast<Lambda>(a2)();

  // Optimal but not convenient
  auto l3 = [] { std::cout << "Lambda #3.\n"; };
  auto a3 = std::make_any<decltype(l3)>(l3);
  std::cout << std::setw(17) << "a3.type() : " << demangle(a3.type()) << "\n";
  std::any_cast<decltype(l3)>(a3)();
}