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
using namespace std::chrono_literals;
using namespace std::string_literals;
const int employee_id = 1;
std::mutex m;
using MyAllocator = std::allocator<void>;
// clang-format off
//#endregion

int main() {
  // Modern C++ style

  auto s = "Hello";                               DISPLAY_TYPE(s);
  auto w1 = get_widget();                         DISPLAY_TYPE(w1);
  auto e1 = Employee{employee_id};                DISPLAY_TYPE(e1);
  auto w2 = Widget{12, 34};                       DISPLAY_TYPE(w2);
                                                  
  auto w3 = new Widget{}; /* prefer unique_ptr */ DISPLAY_TYPE(w3);
  auto w4 = std::make_unique<Widget>();           DISPLAY_TYPE(w4);
                                                  
  auto xi = 42;                                   DISPLAY_TYPE(xi);
  auto xf = 42.f;                                 DISPLAY_TYPE(xf);
  auto xl = 42ul;                                 DISPLAY_TYPE(xl);
  auto xs = "42"s; /* C++14 */                    DISPLAY_TYPE(xs);
  auto xc = 42ns;  /* C++14 */                    DISPLAY_TYPE(xc);

  // auto xll = long long{42}; // error (composed type name) 
  auto xll = 42LL;                                DISPLAY_TYPE(xll);
  // auto e2 = class Employee {employee_id}; // error (composed type name) 
  auto e2 = Employee{employee_id};                DISPLAY_TYPE(e2);

  /* Failing prior to C++17 due to not copyable nor movable; OK with C++17 */ 
  auto lock = std::lock_guard<std::mutex>{m};     DISPLAY_TYPE(lock);
  auto ai = std::atomic<int>{};                   DISPLAY_TYPE(ai);
}
//#region [extensions]
// clang-format on

auto f1(double) -> int;
auto f2(double) { /*...*/ };
auto f3 = [](double) { /*...*/ };

using dict = std::set<std::string>;

template <typename T> using MyVec = std::vector<T, MyAllocator>;
//#endregion