//#region [Declarations]
#include <array>
#include <iomanip>
#include <iostream>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY(x) \
  std::cout << std::setw(30) << #x << " : " << type<decltype(x)>() << '\n';

template <typename T, typename T1, typename T2>
using check_same_t =
    std::enable_if_t<std::is_same_v<T, T1> && std::is_same_v<T, T2>>;
//#endregion

template <typename T> struct A {
  A(const T &t) {}
};

// template <typename T> A(T) -> A<T>; // implicit
template <class T> A(A<T>) -> A<A<T>>; // Custom rule: TODO: what happens if removed?

template <typename T1, typename T2> struct B {
  B(const T1 &t1, const T2 &t2) {}
  template <typename T> B(const T &t, check_same_t<T, T1, T2> * = 0) {}
};

//   template <typename T1, typename T2> B(T1, T2) -> B<T1, T2>; // implicit
template <class T> B(T) -> B<T, T>; // Custom rule: TODO: what happens if removed?

template <typename T> struct C {
  C(T t) {}
  template <typename Iter> C(Iter beg, Iter end) {}
};

template <typename Iter> // Additional custom deduction rule
C(Iter b, Iter e)->C<typename std::iterator_traits<Iter>::value_type>;

int main() {
  // clang-format off
  A<int> a1(3);             /* explicit  C++03                    */  DISPLAY(a1);
  A a2(3);                  /* implicitly generated C++17         */  DISPLAY(a2); 
  A a3(a2);                 /* custom rule                        */  DISPLAY(a3);

  B<int, double> b1(1, 2.); /* explicit C++03                     */  DISPLAY(b1);
  B b2(1, 2.);              /* implicitly generated C++17         */  DISPLAY(b2);
  B<int, int> b3(3);        /* explicit C++03                     */  DISPLAY(b3);
  B b4(3);                  /* custom rule                        */  DISPLAY(b4);

  C c1(7);                  /* implicitly generated C++17         */  DISPLAY(c1);
  std::array v{1., 2., 3.}; /* implicitly generated C++17         */  DISPLAY(v);
  C c2(v.begin(), v.end()); /* custom rule                        */  DISPLAY(c2);
  // C e{5, 6}; // error: no viable constructor or deduction guide for
  //            //        deduction of template arguments of 'C'
  //            // since there is no std::iterator_traits<int>::value_type
}