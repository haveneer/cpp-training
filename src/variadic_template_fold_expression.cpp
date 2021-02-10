//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <string>
using namespace std::string_literals;

struct T {
  explicit T(std::string expr_) : expr{std::move(expr_)} {}
  T(const T &t) = default;
  T(T &&t) = default;

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
T operator<(const T &a, const T &b) { return T{a, "<", b}; }
T operator<<(const T &a, const T &b) { return T{a, "<<", b}; }

T f(const T &a) { return T{"f("s + a.expr + ")"}; }

decltype(auto) operator<<(std::ostream &o, const T &t) { return o << t.expr; }

#define HEADER()                                      \
  std::cout << std::setw(32) << "original expression" \
            << "   interpreted as\n";
#define EXPLAIN(x) std::cout << std::setw(32) << #x << " : " << (x) << '\n';
#define HEADER2()                                     \
  std::cout << "\n"                                   \
            << std::setw(43) << "original expression" \
            << "   result\n";
#define EXPLAIN2(x) std::cout << std::setw(43) << #x << " : " << (x) << '\n';
//#endregion

// Variadic template function
template <typename... Ts> void demo(const Ts &...args) {
  T init{"init"}, x{"x"}, y{"y"};
  HEADER();
  EXPLAIN((args + ...));
  EXPLAIN((... / args));
  EXPLAIN((args & ... & init));
  EXPLAIN((init / ... / args));
  EXPLAIN((args = ... = x));
  EXPLAIN(((x * args) * ...));              // mandatory brackets around (x + args)
  EXPLAIN(((args + x / args) * ...));       // repeated pack
  EXPLAIN(((x < args && args < y) || ...)); // repeated pack
  EXPLAIN((args + ... + (args * ...)));     // nested fold expression
  EXPLAIN((f(args) ^ ...));
  EXPLAIN((init << ... << args));
  HEADER2();
  EXPLAIN2(((std::cout << ... << args), " (display)"));
}

template <typename... Ts> auto sum17(const Ts &...ts) { return (ts + ...); }

int main() {
  T a{"a"}, b{"b"}, c{"c"}, d{"d"};
  demo(a, b, c, d);
  EXPLAIN2(sum17(1.2, 2, 3.f));
}