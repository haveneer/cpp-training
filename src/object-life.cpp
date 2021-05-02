#include <iostream>
#include <tuple>

#include "colorize.hpp"

struct Object {
  Object(std::string name = "") : name{name} {
    std::cout << "Object default ctor [" << name << "] " << Colorize{this}
              << std::endl;
  }
  Object(const Object &obj) : name{obj.name} {
    std::cout << "Object copy ctor [" << obj.name << "] " << Colorize{&obj} << " -> "
              << Colorize{this} << std::endl;
  }
  Object &operator=(const Object &obj) {
    std::cout << "Object copy = [" << obj.name << "] " << Colorize{&obj} << " -> ["
              << name << "] " << Colorize{this} << std::endl;
    if (this != &obj) {
      name = obj.name;
    }
    return *this;
  }
  Object(Object &&obj) : name{std::move(obj.name)} {
    std::cout << "Object move ctor [" << obj.name << "] " << Colorize{&obj} << " -> "
              << Colorize{this} << std::endl;
  }
  Object &operator=(Object &&obj) {
    std::cout << "Object move = [" << obj.name << "] " << Colorize{&obj} << " -> ["
              << name << "] " << Colorize{this} << std::endl;
    name = std::move(obj.name);
    return *this;
  }
  ~Object() {
    std::cout << "Object destroy [" << name << "] " << Colorize{this} << std::endl;
  }

  std::string name;
};

std::ostream &operator<<(std::ostream &o, const Object &obj) {
  return o << "Object{" << Colorize{&obj} << "}";
}

int main() {
  auto x = Object();
  auto y = x;
  auto z = std::move(y);
  y = x;
  z = std::move(y);
}
