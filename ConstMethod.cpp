//#region [Declaration]
#include <iostream>
//#endregion

struct A {
  void foo() {
    attr = 1;
    std::cout << "lvalue / foo()\n";
  }
  void foo() const {
    /* attr = 1; */
    std::cout << "lvalue / foo() const\n";
  }

  //#region [ref-qualified]
  void reffoo() & {
    attr = 1;
    std::cout << "lvalue / reffoo() &\n";
  }
  void reffoo() && {
    attr = 1;
    std::cout << "rvalue / reffoo() &&\n";
  }
  void reffoo() const & {
    /* attr = 1; */
    std::cout << "lvalue / reffoo() const &\n";
  }
  void reffoo() const && {
    /* attr = 1; */
    std::cout << "rvalue / reffoo() const &&\n";
  }
  //#endregion

  int attr;
};

int main() {
  A a;
  a.foo();

  const A a_const = a;
  a_const.foo();

  //#region [Advanced ref-qualified]
  using AConst = const A;

  a.reffoo();
  a_const.reffoo();
  A().reffoo();
  AConst().reffoo();
  //#endregion
}