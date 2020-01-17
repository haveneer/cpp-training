#include <iostream>

int main() {
  int n = 3;

  if (n) {
    std::cout << "n is not zero\n";
  }

  // clang-format off
  if (n) { /* ... */ }
  else { /* ... */ }

  if (n) { /* ... */ }
  else if (n-1) { /* ... */ }
  // clang-format on

  // for(initializer;condition;expression) { }
  for (int i = 0; i < n / 2; ++i) {
    std::cout << "First for loop #" << i << '\n';
  }

  // Any third expression is allowed, but don't do that
  for (; --n; std::cout << "Count down: " << n << '\n') {
  }

  std::cout << "Before while loop\n";
  while(n == 0) {
    std::cout << "Inside while loop\n";
    n = 1;
  }
  std::cout << "After while loop\n";
}