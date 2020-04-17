#include <iostream>
#include <memory>
#include <tuple>

struct Struct {
  int a;
  double b;
  std::shared_ptr<int> c;
};

auto f1() {
  Struct s{1, 3.14, std::make_shared<int>(42)};
  return s;
}

auto f2() {
  std::tuple<int, double, std::shared_ptr<int>> t{1, 3.14,
                                                  std::make_shared<int>(42)};
  return t;
}

int main() {
  auto [a1, b1, c1] = f1(); // full structured bind required
  std::cout << a1 << " " << b1 << " " << *c1 << '\n';

  auto [a2, b2, c2] = f2(); // full structured bind required
  std::cout << a2 << " " << b2 << " " << *c2 << '\n';
}