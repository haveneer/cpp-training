//#region [declarations]
#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
//#endregion

// TODO Créer une classe IShape avec une methode virtuelle 'display'
// TODO Créer des enfants Circle, Square, ...
// TODO Créer une 'factory' de Shape dont la clef est un 'enum'
// TODO Construire un vecteur de IShape
// TODO Parcourir avec un algorithme de la STL pour parcourir et afficher les formes
// TODO Peut-on faire plus performant / plus fiable ? 

class IShape {
public:
  virtual ~IShape() = default;
  virtual void display() const = 0;
};

class Point : public IShape {
public:
  Point() {}
  ~Point() override = default;
  void display() const override { std::cout << "Point" << '\n'; }
};

class Circle : public IShape {
public:
  Circle(int radius) {}
  ~Circle() override = default;
  void display() const override { std::cout << "Circle" << '\n'; }
};

class Square : public IShape {
public:
  Square(int side) {}
  ~Square() override = default;
  void display() const override { std::cout << "Square" << '\n'; }
};

class Rectangle : public IShape {
public:
  Rectangle(int sidea, int sideb) {}
  ~Rectangle() override = default;
  void display() const override { std::cout << "Rectangle" << '\n'; }
};

template <int... dims> class Grid : public IShape {
public:
  Grid() {}
  ~Grid() override = default;
  void display() const override { // fold expression to print name including dims
    ((std::cout << "Grid< ") << ... << (std::to_string(dims) + " ")) << ">\n";
  }

private:
  int cells[(dims * ...)]; // compile time computation of the number of cells
                           // using fold expression
};

enum class Shape : int { Point, Circle, Square, Rectangle };

std::shared_ptr<IShape> runtimeMakeShape(Shape sh, const std::vector<int> &args) {
  switch (sh) {
  case Shape::Point:
    assert(args.size() == 0);
    return std::make_shared<Point>();
  case Shape::Circle:
    assert(args.size() == 1);
    return std::make_shared<Circle>(args[0]);
  case Shape::Square:
    assert(args.size() == 1);
    return std::make_shared<Square>(args[0]);
  case Shape::Rectangle:
    assert(args.size() == 2);
    return std::make_shared<Rectangle>(args[0], args[1]);
  default:
    assert(false); // should not be possible
  }
}

struct ShapeFactory {
  template <typename Shape, typename... Args>
  static std::shared_ptr<IShape> make(Args... args) {
    ++count;
    return std::make_shared<Shape>(args...);
  }

  static inline int count = 0;
};

int main() {
  // Weakly typed version (check args at runtime)
  std::vector<std::shared_ptr<IShape>> v1{runtimeMakeShape(Shape::Circle, {1}),
                                          runtimeMakeShape(Shape::Rectangle, {2, 3}),
                                          runtimeMakeShape(Shape::Square, {2})};
  // Strongly typed version (check args at compile time)
  std::vector<std::shared_ptr<IShape>> v2{ShapeFactory::make<Point>(),   //
                                          ShapeFactory::make<Circle>(1), //
                                          ShapeFactory::make<Rectangle>(2, 3),
                                          ShapeFactory::make<Square>(1),
                                          ShapeFactory::make<Grid<2, 4>>()};

  std::for_each(v2.begin(), v2.end(), [](auto s) { s->display(); });
}