#include <array>
#include <iostream>

int main(int argc, char **argv) {
  int n = 5;

  // comma (,) is an instruction separator discarding first value
  for (int i = 0, j = 0; j = i, j < n; i = (1, j + 1)) {
    std::cout << "Second for loop #" << i << '\n';
  }

  // C++17 style : initialization in if
  if (int k = argc; argv[k]) {
    std::cerr << "Catastrophe: last argv should be null\n";
  }

  // Be careful, if you mix it with comma operator
  if (int k = argc, argv[k]; true) {
    std::cerr << "What argv is it ? argv[0] = " << argv[0] << "\n";
  }

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