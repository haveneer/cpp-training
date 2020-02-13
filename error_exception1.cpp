//#region [Declarations]
#include <iostream>
using MyException = int;
//#endregion

void goDeeper() {
  std::cout << "Entering in goDeeper()\n";
  throw MyException{42};
  std::cout << "Exiting from goDeeper()\n";
}

void goDeep() {
  std::cout << "Entering in goDeep()\n";
  goDeeper();
  std::cout << "Exiting from goDeep()\n";
}

void go() {
  std::cout << "Entering in go()\n";
  goDeep();
  std::cout << "Exiting from go()\n";
}

int main() {
  try {
    std::cout << "Before computation\n";
    go();
    std::cout << "Computation done\n";
  } catch (MyException &e) {
    std::cout << "Catch exception: MyException{" << e << "}\n";
  }
}