#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string_view>

/* http://en.cppreference.com/w/cpp/language/aggregate_initialization
 If the number of initializer clauses is less than the number of members or
 initializer clauses is completely empty, the remaining members are initialized by
 their brace-or-equal initializers, if provided in the class definition, and
 otherwise (since C++14) by empty lists, which performs value-initialization. If a
 member of a reference type is one of these remaining members, the program is
 ill-formed (references cannot be value-initialized)
*/

// http://en.cppreference.com/w/cpp/language/value_initialization
/*
 * The effects of value initialization are:
 * 1) If T is a class type with at least one user-provided constructor of any kind,
 *    the default constructor is called. (until C++14)
 * 1) If T is a class type with no default constructor or with a user-provided
 *    default constructor or with a deleted default constructor, the object is
 *    default-initialized. (since C++14)
 * 2) If T is an non-union class type without any user-provided constructors, then
 *    every non-static data member and base-class component of T is value-initialized
 *    (until C++11)
 * 2) If T is an non-union class type without any user-provided constructors, then
 *    the object is zero-initialized and then the implicitly-declared default
 *    constructor is called (unless it's trivial) (since C++11) (until C++14)
 * 2) If T is a class type without a user-provided or deleted default constructor
 *    (that is, it may be a class with a defaulted default constructor or with an
 *    implicitly-defined one) then the object is zero-initialized and then it is
 *    default-initialized if it has a non-trivial default constructor (since C++14)
 * 3) If T is an array type, each element of the array is value-initialized
 * 4) Otherwise, the object is zero-initialized.
 */

struct A {
  int x, y, z;
};

struct B {
  B() = default;
  B(int x0, int y0) : x(x0), y(y0) /*, z() */ {}
  int x, y, z;
};

constexpr int n = std::max(sizeof(A), sizeof(B));
char buffer[n];

#define DISPLAY(v)                                                                  \
  {                                                                                 \
    std::memset(buffer, 0xFF, n);                                                   \
    auto *p = (v);                                                                  \
    std::string_view msg = #v;                                                      \
    msg.remove_prefix(1);                                                           \
    msg.remove_suffix(1);                                                           \
    std::cout << std::setw(20) << std::left << msg << " : " << std::setw(2) << p->x \
              << " " << std::setw(2) << p->y << " " << std::setw(2) << p->z         \
              << std::endl;                                                         \
  }

int main() {
  DISPLAY((new A{1, 2}));
  DISPLAY((new (buffer) A{1, 2}));
  DISPLAY((new (buffer) A()));
  DISPLAY((new (buffer) A));

  DISPLAY((new B{1, 2}));
  DISPLAY((new (buffer) B{1, 2}));
  DISPLAY((new (buffer) B()));
  DISPLAY((new (buffer) B));
}