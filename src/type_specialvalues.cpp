//#region [Declarations]
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

static struct Init {
  Init() { std::cout.flags(std::ostream::boolalpha); }
} init;

#define DISPLAY0(expr) std::cout << #expr " = " << std::setw(11) << (expr) << '\n';
#define DISPLAY1(expr) display(#expr, expr);

void display(const std::string &expr_as_string, const double &expr) {
  // clang-format off
  std::cout << std::setw(2) << expr_as_string
            << " = " << std::setw(13) << (expr)
            << " | std::sin(" << std::setw(2) << expr_as_string << ")"
            << " = " << std::setw(13) << std::sin(expr)
            << " | " << std::setw(2) << expr_as_string << "/2"
            << " = " << std::setw(13) << expr/2
            << '\n';
  // clang-format on
}
//#endregion

int main() {
  int a = (1 << 30); // = 1024^3 = 1073741824
  int b = 2 * a;
  int c = b - 1;
  int d = 2 * b;
  // int e = a / d; // code terminated due to division by 0
  //#region [Display]
  DISPLAY0(a);
  DISPLAY0(b);
  DISPLAY0(c);
  DISPLAY0(d);
  //#endregion

  std::cout << "---------------\n";
  double v = 0;
  double w = 1. / v;
  double x = v / v;
  double y = -1. / w;
  double z1 = std::numeric_limits<double>::epsilon();
  double z2 = std::numeric_limits<double>::min();
  double z3 = std::numeric_limits<double>::denorm_min();
  //#region [Display]
  DISPLAY1(v);
  DISPLAY1(w);
  DISPLAY1(x);
  DISPLAY1(y);
  DISPLAY1(z1);
  DISPLAY1(z2);
  DISPLAY1(z3);
  //#endregion

  // static_assert(x == x); // cannot be evaluated
  assert(x != x); // because NaN is not comparable!
}