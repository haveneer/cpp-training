//#region [Declarations]
#include <iomanip>
#include <iostream>

static struct Init {
  Init() { std::cout.flags(std::ostream::boolalpha | std::ostream::left); }
} init;
//#endregion

int main() {
  int x, y, z;
  x = y = z = 0;

  //                                   and what if
  bool b1 = (z != 0) && (++x == 2); // (++x == 2) && (z != 0);
  bool b2 = (z == 0) || (++y == 2); // (++y == 2) || (z == 0);

  std::cout << "b1 = " << std::setw(5) << b1 << " x = " << x << '\n';
  std::cout << "b2 = " << std::setw(5) << b2 << " y = " << y << '\n';

  bool b3 = ((z == 0) || (++y == 1)) && (++x == 2); // side effect more insidious
  std::cout << "b3 = " << std::setw(5) << b3 << " x = " << x << " y = " << y << '\n';
}