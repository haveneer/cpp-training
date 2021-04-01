//#region [declarations]
#include <iostream>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
#include <iomanip>
#define DISPLAY_TYPE(obj)                                                         \
  {                                                                               \
    std::string type_string = type<decltype(obj)>();                              \
    std::cout << type_string << std::setw(90 - type_string.size()) << #obj \
              << std::endl;                                                       \
  }

struct Widget {
  int a, b;
};

struct Employee {
  int id;
};

Widget get_widget() { return Widget{}; }

#include <chrono>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <atomic>
using namespace std::chrono_literals;
using namespace std::string_literals;
const int employee_id = 1;
std::mutex m;
using MyAllocator = std::allocator<void>;
// clang-format off
//#endregion

int main() {
  // Classic C++ declaration order

  const char *s = "Hello";                                 DISPLAY_TYPE(s);
  Widget w1 = get_widget();                                DISPLAY_TYPE(w1);
  Employee e1{employee_id};                                DISPLAY_TYPE(e1);
  Widget w2{12, 34};                                       DISPLAY_TYPE(w2);
 
  Widget *w3 = new Widget{};                               DISPLAY_TYPE(w3);
  std::unique_ptr<Widget> w4 = std::make_unique<Widget>(); DISPLAY_TYPE(w4);
 
  int xi = 42;                                             DISPLAY_TYPE(xi);
  float xf = 42.;                                          DISPLAY_TYPE(xf);
  unsigned long xl = 42;                                   DISPLAY_TYPE(xl);
  std::string xs = "42";                                   DISPLAY_TYPE(xs);
  std::chrono::nanoseconds xc{42};                         DISPLAY_TYPE(xc);

  long long xll = 42;                                      DISPLAY_TYPE(xll);
  /* */
  struct Employee e2{employee_id};                          DISPLAY_TYPE(e2);
  /* */

  /* Always Ok since C++11 */
  std::lock_guard<std::mutex> lock{m};                     DISPLAY_TYPE(lock);
  std::atomic<int> ai{};                                   DISPLAY_TYPE(ai);
}
//#region [extensions]
// clang-format on

int f1(double);
int f2(double);
int f3(double);

typedef std::set<std::string> dict;

template <class T> struct MyVec { typedef std::vector<T, MyAllocator> type; };
//#endregion