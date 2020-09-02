//#region [Collapse all]
#include <iostream>

template <typename ShapeT> class Shape {
public:
  ShapeT &self() { return static_cast<ShapeT&>(*this); }
  const ShapeT &self() const { return static_cast<const ShapeT&>(*this); }

  void print() const { // static interface
    std::cout << "A shape will be printed\n";
    self().print_impl();
    std::cout << "A shape has be printed\n";
  }
};

// Every derived class inherits from CRTP class instead of abstract class
class Square : public Shape<Square> {
public:
  void print_impl() const { std::cout << "Square\n"; }
};
class Circle : public Shape<Circle> {
public:
  void print_impl() const { std::cout << "Circle\n"; }
};

template <typename T> void f(const Shape<T> &s) { s.print(); }

int main() {
  Square s;
  Circle c;

  f(s);
  f(c);
}
//#endregion