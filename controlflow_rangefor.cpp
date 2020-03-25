#include <array>
#include <iostream>

int main(int argc, char **argv) {
  
  // C++11 range loop
  int tab1[] = {1, 2, 3};
  for (int e : tab1) {
    std::cout << "tab1 contains: " << e << '\n';
  }
  std::array<int, 3> tab2 = {{4,5,6}};
  for (int e : tab2) {
    std::cout << "tab2 contains: " << e << '\n';
  }
}