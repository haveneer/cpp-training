//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <string>

struct T {
  explicit T(std::string expr_) : expr{std::move(expr_)} {}
  explicit T(const T &t) = default;

  T(const T &a, const std::string &symb, const T &b)
      : expr{"(" + a.expr + " " + symb + " " + b.expr + ")"} {}
  T(const std::string &symb, const T &b) : expr{"(" + symb + b.expr + ")"} {}
  T(const T &a, const std::string &symb) : expr{"(" + a.expr + symb + ")"} {}

  T operator=(const T &t) const { return T{*this, "=", t}; }
  T operator[](const int i) const { return T{*this, '[' + std::to_string(i) + ']'}; }
  T operator[](const T &i) const { return T{*this, '[' + i.expr + ']'}; }
  T operator()(const T &i) const { return T{*this, '(' + i.expr + ')'}; }

  const std::string expr;
};

T operator+(const T &a, const T &b) { return T{a, "+", b}; }
T operator!(const T &b) { return T{"!", b}; }
T operator&&(const T &a, const T &b) { return T{a, "&&", b}; }
T operator||(const T &a, const T &b) { return T{a, "||", b}; }
T operator*(const T &b) { return T{"*", b}; }
T operator++(const T &b) { return T{"++", b}; }
T operator++(const T &a, int) { return T{a, "++"}; }
T operator--(const T &b) { return T{"--", b}; }
T operator--(const T &a, int) { return T{a, "--"}; }
T operator~(const T &b) { return T{"~", b}; }
T operator&(const T &a, const T &b) { return T{a, "&", b}; }
T operator|(const T &a, const T &b) { return T{a, "|", b}; }
T operator^(const T &a, const T &b) { return T{a, "^", b}; }
T operator-(const T &a, const T &b) { return T{a, "-", b}; }
T operator*(const T &a, const T &b) { return T{a, "*", b}; }
T operator/(const T &a, const T &b) { return T{a, "/", b}; }
T operator%(const T &a, const T &b) { return T{a, "%", b}; }
T operator-(const T &b) { return T{"-", b}; }
T operator+=(const T &a, const T &b) { return T{a, "+=", b}; }
T operator&(const T &b) { return T{"&", b}; }
T operator,(const T &a, const T &b) { return T{a, ",", b}; }

#define HEADER_LINE()                                   \
  std::cout << std::setfill('-') << std::setw(20) << "" \
            << " | " << std::setw(32) << "" << std::setfill(' ') << '\n';
#define HEADER()                                                   \
  HEADER_LINE();                                                   \
  std::cout << std::setw(20) << "original expression"              \
            << " | " << std::setw(32) << "interpreted as" << '\n'; \
  HEADER_LINE();

#define EXPLAIN(x) \
  std::cout << std::setw(20) << #x << " | " << std::setw(32) << (x).expr << '\n';
// clang-format off
//#endregion

int main() {
  T a{"a"}, b{"b"}, c{"c"}, d{"d"}, e{"e"}, i{"i"}, p{"p"};

  HEADER();
  EXPLAIN(    a + b + c                   );
  EXPLAIN(    a * b + c                   );
  EXPLAIN(    a + b * c                   );
  EXPLAIN(    a = b = c                   );
  EXPLAIN(    c = a + b                   );
  EXPLAIN(    a || b && c && d            );
  EXPLAIN(    d = a && !b || c            );
  EXPLAIN(    ++*p++                      );
  EXPLAIN(    a | ~b & c ^ d              );
  EXPLAIN(    a[0]++ + a[1]++             );
  EXPLAIN(    a + b * c / d % -e          );
  EXPLAIN(    ++p[i]                      );
  EXPLAIN(    a += b += c += d            );
  EXPLAIN(    a --- b                     );
  EXPLAIN(    a &&& b                     );
  EXPLAIN(    (a, b, c, (d, e))           );
}