//#region [Collapse all]
#include <iostream>
//#endregion

// Use user literals as a unit suffix
struct Length {
  long double m;
};

Length operator""  _m(long double x) { return {x}; }
Length operator"" _cm(long double x) { return {x / 10}; }
Length operator"" _km(long double x) { return {x * 1000}; }

Length operator+(const Length &l1, const Length &l2) { return {l1.m + l2.m}; }

std::ostream &operator<<(std::ostream &o, const Length &l) {
  return o << l.m << "_m";
}

// Use user literals as special degree'minutes'seconds notation
constexpr long double operator""_deg(const char *str, std::size_t size) {
  long double angle = 0;
  const char *p = str;
  auto process = [&] {
    long double value = 0;
    for (; *p && *p != '\''; ++p) {
      if (std::isdigit(*p)) {
        value = 10 * value + (*p - '0');
      } else {
        throw std::out_of_range("Invalid value");
      }
    }
    if (*p == '\'')
      ++p;
    return value;
  };
  angle += process();        // degree
  angle += process() / 60;   // minutes
  angle += process() / 3600; // seconds
  if (*p) {
    throw std::out_of_range("Invalid value");
  }
  return angle;
};

//#region [implementation details]
enum class Classifier { Digit, Sep, Illegal };

template <char c> constexpr Classifier classify() {
  if constexpr (c >= '0' && c <= '9') {
    return Classifier::Digit;
  } else if constexpr (c == '\'') {
    return Classifier::Sep;
  } else {
    return Classifier::Illegal;
  }
}

template <int n, char c, bool doit> constexpr int update() {
  constexpr auto cl = classify<c>();
  static_assert(cl != Classifier::Illegal);
  if constexpr (doit && cl == Classifier::Digit) {
    return 10 * n + (c - '0');
  } else {
    return n;
  }
}

template <int n, char c> constexpr int updateIndex() {
  constexpr auto cl = classify<c>();
  static_assert(cl != Classifier::Illegal);
  if constexpr (cl == Classifier::Sep) {
    return n + 1;
  } else {
    return n;
  }
}

template <int degree, int minutes, int seconds, int index, char first, char... tail>
struct Process {
  inline static const long double value =
      Process<update<degree, first, index == 0>(),  // degree update
              update<minutes, first, index == 1>(), // minutes update
              update<seconds, first, index == 2>(), // seconds update
              updateIndex<index, first>(), tail...>::value;
};

template <int degree, int minutes, int seconds, int index, char c>
struct Process<degree, minutes, seconds, index, c> {
  static_assert(index <= 2);
  inline static const long double value = update<degree, c, index == 0>() +
                                          update<minutes, c, index == 1>() / 60. +
                                          update<seconds, c, index == 2>() / 3600.;
};
//#endregion

template <char... chars>                       // templated sequence of chars
constexpr long double operator""_deg() {       // in that case, return type
  return Process<0, 0, 0, 0, chars...>::value; // must be a native literal
};

int main() {
  auto length = 1._m + 1._km + 3._cm;
  std::cout << "length = " << length << '\n';

  std::cout << "1'59'6"_deg << '\n'; // using a string
  std::cout << 1'59'6_deg << '\n';   // using a sequence of template chars
}