#include <iostream>

int f(int i) { return 0; }
int f(int *p) { return 1; }

int main() {
  int i = 0;
  int *p = 0; // FIXME: prefer nullptr

  std::cout << "f(i)       = " << f(i) << std::endl;
  std::cout << "f(p)       = " << f(p) << std::endl;
  // std::cout << "f(NULL)    = " << f(NULL) << std::endl; // error: ambiguous
  std::cout << "f(nullptr) = " << f(nullptr) << std::endl;

  {
    int *pi = nullptr;
    if (!pi) // or (pi == nullptr)
      std::cout << "pi is null" << std::endl;
  }
}