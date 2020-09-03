// Implicit conversion may be harmful

#include <iostream>

#define _explicit03_ explicit // on constructors
#define _explicit11_ // explicit // on conversions

// Trick; see https://stackoverflow.com/questions/3781520/how-to-test-if-preprocessor-symbol-is-defined-but-has-no-value
#define DO_EXPAND(VAL) VAL##1
#define EXPAND(VAL) DO_EXPAND(VAL)

class Year {
  int m_y;

public:
  // Constructors with only one arg should be explicit (C++03)
  _explicit03_ Year(int y) : m_y(y) {}
  // explicit conversion operator only since C++11
  _explicit11_ operator int() const { return m_y; }
};

class Month {
  int m_m;

public:
  // Constructors with only one arg should be explicit (C++03)
  _explicit03_ Month(int m) : m_m(m) {}
  _explicit03_ Month(const char *) {}
  // explicit conversion operator only since C++11
  _explicit11_ operator int() const { return m_m; }
};

class Date {
  bool m_defined;

public:
  Date() : m_defined(false) {}
  Date(int, Month, Year) : m_defined(true) {}
  // explicit conversion operator only since C++11
  _explicit11_ operator bool() const { return m_defined; }
};

int main() {
  //#region [Details]
#if EXPAND(_explicit03_) == 1
  std::cout << "Without C++03 explicit constructor\n";
#else
  std::cout << "With C++03 explicit constructor\n";
#endif
#if EXPAND(_explicit11_) == 1
  std::cout << "Without C++11 explicit conversion\n";
#else
  std::cout << "With C++11 explicit conversion\n";
#endif
  //#endregion

  // compiler error: with C++03 due to implicit conversion char->Month
  // (do not promote char to int)
  // Date d0(2013, 'a', 24);

  // compiler error: with C++11 due to implicit conversion Month->int
  // Date d1(Month(24), Month(4), Year(2013));

  Date d2(24, Month(4), Year(2013)); // Always OK
  Date d3(1, Month(1), Year(1970));

  if (d2) { /* do something */
    // Always OK (Date->bool)
  }

  if (d2 == d3) {
    return 1; // compiler error: with C++11 due to implicit conversion Date->bool
  } else {
    return 0; // without C++11 explicit : return 1 !!
  }
}