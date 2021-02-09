#include <iostream>

using T = std::string;

void whatReferenceType(const T &a) {
  std::cout << "Pass by lvalue const reference\n";
}

void whatReferenceType(T &a) { // TODO: what happens if we remove this function ?
  std::cout << "Pass by lvalue mutable reference\n";
}

void whatReferenceType(T &&a) { // TODO: what happens if we remove this function ?
  std::cout << "Pass by rvalue reference\n";
}

int main() {
  T hello = "hello ";
  T world = "world";
  T text = hello + world;
  whatReferenceType(hello);
  whatReferenceType(text);
  whatReferenceType(T{});
  whatReferenceType(hello + world);
}