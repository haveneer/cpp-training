//#region [Declaration]
#include <iostream>
//#endregion

class Point3D {
public:
  double _x, _y, _z;

public:
  // Don't initialize attributes
  Point3D() = default;
  // Same : don't initialize attributes
//  Point3D() { }
  // Always initialize attributes
//  Point3D() : _x{}, _y{}, _z{} {}

  // field-by-field copy constructor
//  Point3D(const Point3D & ) = default;
  // Same :field-by-field copy constructor
//  Point3D(const Point3D & p) : _x(p._x), _y(p._y), _z(p._z) { }
  // Copy constructor only allows argument by reference
//  Point3D(const Point3D p) : _x(p._x), _y(p._y), _z(p._z) { }

  // Do nothing (DANGEROUS)
//  Point3D(const Point3D & ) { }


  // If non-standard constructor is defined, the default ctor is disabled
  Point3D(const double v) : _x(v), _y(v), _z(v) { }

  // /!\ copy operator must be defined : cf rule of 3/5/0
};

int main() {
  Point3D p;
  Point3D q{}; // uniform initializer
  Point3D r = q;

  std::cout << "p = (" << p._x << " " << p._y << " " << p._z << ")\n";
  std::cout << "q = (" << q._x << " " << q._y << " " << q._z << ")\n";
  std::cout << "r = (" << r._x << " " << r._y << " " << r._z << ")\n";
}