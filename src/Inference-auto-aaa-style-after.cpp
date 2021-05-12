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
auto f2(double) { /*...*/ }
auto f3 = [](double) { /*...*/ };

using dict = std::set<std::string>;

template <typename T> using MyVec = std::vector<T, MyAllocator>;
//#endregion