//#region [Declarations]
#include <iostream>
#include <vector>
//#endregion

int main() { // TODO predict the output
  std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  std::cout << "{";
  for (std::size_t i = 0, s=0; i < v.size(); ++i) {
    if (v[i]%2==0)
      continue;
    if (s > 0) std::cout << ", ";
    std::cout << v[i];
    if (++s > 5) {
      std::cout << "...";
      break;
    }
  }
  std::cout << "}\n";
}