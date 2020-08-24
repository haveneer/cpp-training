//#region [Declaration]
#include <iostream>
#ifndef _MSC_VER
#define PRINTME() std::cout << __PRETTY_FUNCTION__ << '\n'
#else
#define PRINTME() std::cout << __FUNCSIG__ << '\n'
#endif
//#endregion

struct BaseF0 {
  BaseF0() { PRINTME(); }
  ~BaseF0() { PRINTME(); }
};

struct F0 : BaseF0 {
  F0() { PRINTME(); }
  ~F0() { PRINTME(); }
};

struct Base {
  Base() { PRINTME(); }
  ~Base() { PRINTME(); }

  F0 f0;
};

struct BaseF1 {
  BaseF1() { PRINTME(); }
  ~BaseF1() { PRINTME(); }
};

struct F1 : BaseF1 {
  F1() { PRINTME(); }
  ~F1() { PRINTME(); }
};

struct BaseF2 {
  BaseF2() { PRINTME(); }
  ~BaseF2() { PRINTME(); }
};

struct F2 : BaseF2 {
  F2() { PRINTME(); }
  ~F2() { PRINTME(); }
};

struct Main : Base {
  Main() { PRINTME(); }
  ~Main() { PRINTME(); }

  F1 f1;
  F2 f2;
};

int main() {
  Main a;
  std::cout << "------\n";
}