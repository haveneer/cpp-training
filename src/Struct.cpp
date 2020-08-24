//#region [Declaration]
#include <iostream>
//#endregion

// Structure classique
struct Point {
  double x;
  double y;
};

// Same struct content is not same struct !
struct OtherPoint {
  double x;
  double y;
};

int main() {
  Point p{1, 2}; // initialization list
  // OtherPoint q{p}; // same struct content is not same struct !
  std::cout << "p =(" << p.x << ',' << p.y << ")\n";
  // Point p2{.x = 2, .y = 1}; // Designated initializers: requires C99 or C++20 
  // std::cout << "p2=(" << p2.x << ',' << p2.y << ")\n";

  // You can define struct anywhere, even in a function
  struct Node {
    int tag;
    Point point;
  };

  Node n; // Not initialized by default
  std::cout << "[BEFORE] Node n content: tag=" << n.tag << " point=("
            << n.point.x << "," << n.point.y << ")\n";
  n = {42, p}; // Assignment again using initializer list
  std::cout << "[AFTER ] Node n content: tag=" << n.tag << " p=(" << n.point.x
            << "," << n.point.y << ")\n";
}