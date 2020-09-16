//#region [Collapse all]
#include <iostream>

class X {};

std::ostream operator<<(std::ostream o, const X &) { return o << "X{}"; }

int main() { std::cout << X{} << std::endl; }
//#endregion