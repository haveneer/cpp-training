//#region [Collapse all]
#include <iostream>
class X {
public:
  X(int) {}
  X(const char *) {}
};

void f(const X &) {
  std::cout << "f(X)" << std::endl;
}

void f(int) {
  std::cout << "f(int)" << std::endl;
}

int main() {
  f(123);
  f("123");
}
//#endregion