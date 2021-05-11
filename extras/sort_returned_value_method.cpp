#include <algorithm>
#include <iostream>
#include <vector>

std::vector<int> sort1(const std::vector<int> &v) {
  std::vector<int> that{v}; // NRVO

  std::sort(that.begin(), that.end());

  return that; // or std::move ?
}

void sort2(const std::vector<int> &v, std::vector<int> &that) {
  that = v;
  std::sort(that.begin(), that.end());
}

std::vector<int> sort3(std::vector<int> &&v) {
  std::vector<int> that{std::move(v)};

  std::sort(that.begin(), that.end());

  return that;
}

int main() {
  std::vector<int> v{1, 5, 9, 3, 0, 2, 5, 3};

  auto vr1 = sort1(v);

  std::vector<int> vr2;
  sort2(v, vr2);

  auto vr3 = sort3(std::vector{v});
  
  // Need a benchmark ?
  // see https://quick-bench.com/q/1Iy7PqsprxlYdXok78k8p5n1tOs
}