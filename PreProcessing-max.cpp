//#region [Declarations]
#include <iostream>
//#endregion

// TODO define maximum of two integers using a macro MAX
//#region [V1]
#define MAX_V1(a, b) (a > b) ? a : b
//#endregion
//#region [V2]
#define MAX_V2(a, b) ((a) > (b)) ? (a) : (b)
//#endregion
//#region [V3]
#define MAX_V3(a, b) (((a) > (b)) ? (a) : (b))
//#endregion

int main() {
  int a = 1;
  int b = 2;

  int m_v1 = MAX_V1(a | 1, b | 2);
  std::cout << "V1 : a=" << a << " b=" << b << " max=" << m_v1 << '\n';
  std::cout << "V2 : a=" << a << " b=" << b << " max=" << MAX_V2(a, b) << '\n';
  std::cout << '\n';
  std::cout << "V3 : a=" << a << " b=" << b << " max=" << MAX_V3(a++, b++) << '\n';
}