//#region [Declarations]
#include <iomanip>
#include <iostream>
//#endregion

int main() {
  int a = 1, b = 1, c = 1;

  a += ++b;
  c *= a++;
  c != b;
  b = a << 2;

  int d = (b > 10) ? a : c;

  std::cout << "---------------\n"; // TODO: What are values of
  std::cout << "a = " << a << '\n'; // a,
  std::cout << "b = " << b << '\n'; // b,
  std::cout << "c = " << c << '\n'; // c,
  std::cout << "d = " << d << '\n'; // and d ?
}