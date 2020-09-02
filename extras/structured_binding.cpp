//#region [declarations]
#include <iostream>
#include <memory>
#include <tuple>
#include <array>
//#endregion

struct MyStruct {
  int a;
  double b;
  std::shared_ptr<int> c;
};

auto f1() {
  MyStruct s{1, 3.14, std::make_shared<int>(42)};
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

  int e=1, f=2;
  auto [c,d] = std::tie(e,f); // also from tied values

  // int a[2] = {1,2}; 
  std::array<int,2> a = {1,2}; 

  auto [x,y] = a; // xr refers to a[0], yr refers to a[1] as values
  auto& [xr, yr] = a; // xr refers to a[0], yr refers to a[1] as references
  std::cout << (&xr==&a[0]) << " " << (&yr==&a[1]) << "\n"; 
}