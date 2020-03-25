//#region [Declarations]
#include <iostream>
#include <vector>
//#endregion

int main() {
  std::vector<int> v{1, 2, 3, 4, 5, 6};

  { // All these loops are equivalent
    int sum = 0;
    std::size_t i = 0; // vector indexes are unsigned numbers
    while (i < v.size()) {
      sum += v[i];
      ++i;
    }
    std::cout << "Sum is " << sum << '\n';
  }

  { // All these loops are equivalent
    int sum = 0;
    for (std::size_t i = 0; i < v.size(); ++i) {
      sum += v[i];
    }
    std::cout << "Sum is " << sum << '\n';
  }

  { // All these loops are equivalent
    int sum = 0;
    std::size_t i = 0;
    for (; i < v.size();) {
      sum += v[i];
      ++i;
    }
    std::cout << "Sum is " << sum << '\n';
  }
}