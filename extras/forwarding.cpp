#include <iostream>

int bar() { return 1337; }

void foo(int const &) { std::cout << "lvalue\n"; }
void foo(int &&) { std::cout << "rvalue\n"; }

void indirect(int &&x) { foo(x); }
void indirect_and_forward(int &&x) { foo(std::forward<int>(x)); }

int main() {
  // Direct call behaves perfectly:
  // choose the right foo() signature according bar() output
  foo(bar());
  // Indirect call without forwarding
  // Always choose lvalue signature
  indirect(bar());
  // Indirect call with forwarding
  // Always choose the right signature
  indirect_and_forward(bar());
}