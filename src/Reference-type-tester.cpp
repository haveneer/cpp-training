#include <iostream>

using T = std::string;

void whatReferenceType(T & a) {
  std::cout << "This is a lvalue\n";
}

void whatReferenceType(T && a) {
  std::cout << "This is a rvalue\n";
}

int main() {
  std::string hello = "hello ";
  std::string world = "world";
  std::string text = hello + world;
  whatReferenceType(hello);
  whatReferenceType(text);
  whatReferenceType(hello + world);
}