//#region [declarations]
#include <iostream>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
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