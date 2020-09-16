//#region [Collapse all]
#include <array>
#include <iostream>

std::array<int, 256> &f() {
  std::array<int, 256> a{};
  return a;
}

int main() {
  std::array<int, 256> &b = f();
  std::cout << b[255] << "\n";
}
//#endregion