//#region [Declarations]
#include <cmath>
#include <iostream>
//#endregion

// Declaration
template <typename T> struct Point3D {
  T x;
  T y;
  T z;

  double norm2() const { return std::sqrt(x * x + y * y + z * z); }
  double norm0() const;
};

// Definition out of class
template <typename T> double Point3D<T>::norm0() const {
  return std::max(std::abs(x), std::max(std::abs(y), std::abs(z)));
}

// --- free functions

template <typename T>
Point3D<T> operator+(const Point3D<T> &p1, const Point3D<T> &p2) {
  return {p1.x + p2.x, p1.y + p2.y, p1.z + p2.z};
}

//#region [With advanced parametrization]
template <typename T, unsigned N = 3> struct Array { T data[N]; };

template <typename T, unsigned N> const T *begin(const Array<T, N> &a) {
  return a.data;
}

template <typename T, unsigned N> const T *end(const Array<T, N> &a) {
  return a.data + N;
}
//#endregion

int main() {
  Point3D<int> pi{1, 2, 3};
  std::cout << (pi + pi).norm2() << '\n';
  std::cout << (pi + pi).norm0() << '\n';

  Point3D<double> pd{1., 2., 3.};
  std::cout << (pd + pd).norm2() << '\n';
  std::cout << (pd + pd).norm0() << '\n';

  //#region [With advanced parametrization]
  std::cout << "----\n";
  Array<double, 10> a{};
  for (auto e : a)
    std::cout << e << ' ';
  std::cout << '\n';
  //#endregion
}