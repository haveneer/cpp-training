//#region [Declarations]
#include <algorithm>
#include <iostream>
#include <vector>
//#endregion

int main() {
  std::vector<int> v{{1, 2, 3, 4, 5, 6, 32, 64, 85, 41, 11, 7, 98}};

  int counter = 0; // immediate declaration and usage
  std::sort(v.begin(), v.end(), [&counter](auto a, auto b) {
    ++counter;
    return (a < b);
  });
  
  std::cout << counter << " comparaisons have been done\n";
  for (auto &&x : v) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}