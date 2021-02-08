#include <iostream>

struct A {
  A() : A(0) { std::cout << "Ping" << std::endl; }

  // infinite loops in delegated ctor are prohibited
  // (detected at compile time or runtime)
  A(int x) /* : A() */ { std::cout << "Pong" << std::endl; }
};

int main() { A a(0); }