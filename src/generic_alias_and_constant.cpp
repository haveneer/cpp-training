//#region [declarations]
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

template <typename T> constexpr T zero = 0.; // Constants always in the best type
template <typename T> constexpr T pi = T(3.1415926535897932384626L);

template <typename T> T compute_disk_area_from_radius(T radius) {
  return pi<T> * radius * radius;
}

void step1() {
  std::cout << std::setprecision(20);
  std::cout << compute_disk_area_from_radius<float>(1) << '\n';
  std::cout << compute_disk_area_from_radius<double>(1) << '\n';
  std::cout << compute_disk_area_from_radius<long double>(1) << '\n';
}

template <typename T>
using Container = std::list<T>; // choose any of set, list, vector

void step2() { // Generic management; TODO change Container type to test it
  Container<short> container;
  std::generate_n(std::inserter(container, container.end()), 17,
                  [n = 0]() mutable { return 1 << (n++); });
  std::for_each(container.begin(), container.end(),
                [n = 0](auto x) mutable { std::cout << n++ << " : " << x << '\n'; });
}

// decay: applies type transformations as when passing a function argument by value
template <typename T>
using simplify =
    typename std::conditional<std::is_pointer_v<T>, // note all _t and _v suffixes
                              typename std::decay_t<std::remove_pointer_t<T>>,
                              typename std::decay_t<T>>::type;

template <typename T> void print_type() {
  std::cout << std::setw(13) << type<T>() << " -> " << type<simplify<T>>() << '\n';
}

void step3() {
  print_type<int>();
  print_type<int &>();
  print_type<volatile int &>();
  print_type<const int &>();
  print_type<int *const>();
  print_type<const int *>();
}

int main() {
  step1();
  step2();
  step3();
}