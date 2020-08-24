//#region [declarations]
#include <iostream>
#include <array>
//#endregion

struct Point {
  double x,y;
  int tag;
};

int main() {
  // without initialization // with default initialization
  int   i; //{};
  float x; //{};
  Point p; //{};

  std::cout << "i = " << i << std::endl;
  std::cout << "x = " << x << std::endl;
  std::cout << "p = (" << p.x << ", " << p.y << "; "
                       << p.tag << ")" << std::endl;
}