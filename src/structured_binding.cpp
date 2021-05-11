//#region [declarations]
#include <array>
#include <iostream>
#include <memory>
#include <tuple>
#include <cassert>
//#endregion

struct MyStructBase {
  int a;
  double b;
  std::shared_ptr<int> c;
};

struct MyStruct : MyStructBase {};

auto f1() { return std::make_tuple(1, 3.14, std::make_shared<int>(42)); }
MyStruct f2() { return {{1, 3.14, std::make_shared<int>(42)}}; }

int main() {
  auto [a1, b1, c1] = f1(); // full structured bind required
  std::cout << a1 << " " << b1 << " " << *c1 << '\n';

  auto [a2, b2, c2] = f2(); // full structured bind required
  //                        // (can decompose trivial inheritance)
  std::cout << a2 << " " << b2 << " " << *c2 << '\n';

  const auto &[a3, b3, c3] = f2(); // TODO: try without const qualifier
  std::cout << a3 << " " << b3 << " " << *c3 << '\n';

  int e = 1, f = 2;
  auto [c, d] = std::tie(e, f); // also from tied values
  assert(&c == &e);             // std::tie itself implies referenced values
  assert(&d == &f);

  std::array<int, 2> a = {1, 2}; // classic: 'int a[] = {1,2, 3};'
  auto [x, y] = a;               // xr refers to a[0], yr refers to a[1] as values
  assert(&x != &a[0]);
  assert(&y != &a[1]);
  const auto &[xr, yr] = a; // xr refers to a[0], yr refers to a[1] as references
  assert(&xr == &a[0]);
  assert(&yr == &a[1]);
}