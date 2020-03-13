//#region [Declarations]
#include <cmath>
#include <iomanip>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

// clang-format off
#define HEADER_LINE()                                   \
  std::cout << std::setfill('-')                        \
            << std::setw(15) << ""                      \
            << " | " << std::setw(12) << ""             \
            << " | " << std::setw(14) << ""             \
            << " | " << std::setw(14) << ""             \
            << std::setfill(' ') << '\n';
#define HEADER() \
  HEADER_LINE(); \
  std::cout << std::setw(15) << "expression"       \
            << " | " << std::setw(12) << "type"    \
            << " | " << std::setw(14) << "address" \
            << " | " << std::setw(14) << "value" << '\n'; \
  HEADER_LINE();

#define EXPLAIN(expr) explain<decltype(expr)>(#expr, expr);

template <typename T>
void explain(const std::string &expr_as_string, const T &expr) {
  std::cout << std::setw(15) << expr_as_string
            << " | " << std::setw(12) << type<T>()
            << " | " << std::setw(14) << &expr
            << " | " << std::setw(14)
            << std::boolalpha << (expr) << '\n';
}

template <typename T> void explain(const std::string &expr_as_string, T &&expr) {
  std::cout << std::setw(15) << expr_as_string
            << " | " << std::setw(12) << type<T>()
            << " | " << std::setw(14) << "<no address>"
            << " | " << std::setw(14) << std::boolalpha << (expr) << '\n';
}
// clang-format off
//#endregion

int main() {
  int x = 1;
  int y = 0;
  int *p = &x;
  double d = 0.0;

  HEADER(/*    expression                                    */);
  EXPLAIN(     1 + 1                                           );
  EXPLAIN(     x                                               );
  EXPLAIN(     y = x                                           );
  EXPLAIN(     x + 1                                           );
  EXPLAIN(     x * x + 2 * x                                   );
  EXPLAIN(     y = x * x                                       );
  EXPLAIN(     x == 42                                         );
  EXPLAIN(     p                                               );
  EXPLAIN(     *p                                              );
  EXPLAIN(     p == &x                                         );
  EXPLAIN(     x > 2 * y                                       );
  EXPLAIN(     d = d + x                                       );
  EXPLAIN(     d                                               );
  EXPLAIN(     std::sin(d)                                     );
}