//#region [Declarations]
#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>
//#endregion

int f1(int a, int b) { return a + 2 * b; }

int main() {
  // non auto lambda assignment: why ?
  std::function<void(void)> fend = [] { std::cout << "the end\n"; };

  std::vector<int> v{1, 2, 3, 4, 5}; // data

  // C++03 style
  int r1 = std::accumulate(v.begin(), v.end(), 0, f1);

  // C++11 feature : F2 is a local type (not possible with C++03)
  struct F2 {
    int operator()(int a, int b) const { return a + 2 * b; }
  } f2;
  int r2 = std::accumulate(v.begin(), v.end(), 0, f2);

  auto f3 = [](int a, int b) { return a + 2 * b; };
  int r3 = std::accumulate(v.begin(), v.end(), 0, f3);

  int count = 0; // local variable
  auto f4 = [&count](int a, int b) {
    count++;
    return a + 2 * b;
  };
  int r4 = std::accumulate(v.begin(), v.end(), 0, f4);

  // C++14 lambda with auto parameters
  std::for_each(v.begin(), v.end(),
                [](auto &&x) { std::cout << x << std::endl; });

  std::cout << "Results: " << r1 << " " << r2 << " " << r3 << " " << r4 << "\n";
  fend();
}
