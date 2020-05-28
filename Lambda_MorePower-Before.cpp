//#region [Declarations]
#include <algorithm>
#include <iostream>
#include <vector>
//#endregion

int counter = 0;
bool compare_and_count(int a, int b) {
  ++counter;
  return a < b;
}

/* far far away */

int main() {
  std::vector<int> v{{1, 2, 3, 4, 5, 6, 32, 64, 85, 41, 11, 7, 98}};
  
  counter = 0;
  std::sort(v.begin(), v.end(), compare_and_count);
  
  std::cout << counter << " comparaisons have been done\n";
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}