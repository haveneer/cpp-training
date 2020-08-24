#include <iostream>

struct Object {
  Object() {}
  Object(const Object &o) { std::cout << "Copying ctor\n"; }
  void operator=(const Object &o) { std::cout << "Coping =\n"; }
#if 1 // TODO switch me and see
  Object(Object &&o) { std::cout << "Moving ctor\n"; }
  void operator=(Object &&o) { std::cout << "Moving =\n"; }
#endif
};

void exchange(Object &o1, Object &o2) {
  Object tmp(std::move(o1));
  o1 = std::move(o2);
  o2 = std::move(tmp);
};

int main() {
  Object o1, o2;
  exchange(o1, o2);
}