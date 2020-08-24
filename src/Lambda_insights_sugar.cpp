//#region [Declarations]
#include <iostream>
//#endregion

int main() {
  int data{1};

  // 𝛌-function without capture are convertible to function pointer
  int (*fp)(int, char) = [](int a, char b) { return a + b; };
  std::cout << (*fp)(1, 2) << '\n';

  // error: no viable conversion
  // int (*fp2)(int, char) = [data](int a, char b){ return a+b;};

  auto f3 = [data](int a, char b) { return a + b + data; };
  std::cout << f3(1, 2) << '\n';

  auto f4 = [data](auto a, auto b) { return a + b + data; };
  std::cout << f4(1, 2) << '\n';
}