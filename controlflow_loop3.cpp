//#region [Declarations]
#include <iostream>
//#endregion

int main() { // TODO predict the output
  int n = 3;

  for (int i = 0; i < n / 2; ++i) {
    std::cout << "First for loop #" << i << '\n';
  }

  // Any third expression is allowed; you can do it, but DON'T DO THAT
  for (; --n; std::cout << "Count down: " << n << '\n');

  std::cout << "Before while loop\n";
  while (n == 0) {
    std::cout << "Inside while loop\n";
    n = !n;
  }
  std::cout << "After while loop\n";

  // comma (,) is an instruction separator discarding first value; DON'T DO THAT
  for (int i = 0, j = 0; j = i, j < n; i = (1, j + 1)) {
    std::cout << "Last for loop #" << i << '\n';
  }
}