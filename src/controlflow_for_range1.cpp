//#region [Declarations]
#include <array>
#include <iostream>
#include <vector>
//#endregion

int main() {
  int v1[] = {1, 2, 3, 4, 5};
  for (int i : v1) {       // element by copy with explicit type [not preferred]
    std::cout << i << " "; // element by copy is never desirable
  }
  std::cout << '\n';

  for (int i : {1, 2, 3, 4, 5}) { // the initializer may be a braced-init-list
    std::cout << i << ' ';
  }
  std::cout << '\n';

  std::vector<int> v2(5);
  for (int &i : v2) { // element by reference (can change element value)
    i += 5;           // without &, any change on variable does not affect container
  }

  const std::array<double, 5> v3{{1, 2, 3, 4, 5}};
  double sum = 0;
  for (const double &x : v3) { // using const reference (no copy, no changes)
    sum += x;                  // const is required since the container is const
  }
}