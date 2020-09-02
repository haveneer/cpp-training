//#region [Declarations]
#include <array>
#include <iostream>
//#endregion
#include <set>

int main() {
  std::array<int, 6> anArray = {{3, 2, 7, 5, 2, 8}};

  // Constructor using a list of values
  std::set<int> a{3, 2, 7, 5, 2, 8};
  // Constructor using a pair of iterators
  std::set<int> b{anArray.begin(), anArray.end()};

  //#region [print set]
  for (auto &&x : b) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  //#endregion

  std::pair<std::set<int>::iterator, bool>
      insertion_result1 = // very complex return type
      b.insert(1);        // insert new value
  if (insertion_result1.second) {
    std::cout << *insertion_result1.first << " has been inserted\n";
  }
  auto insertion_result2 = // you should use auto instead
      b.insert(1);         // insert new value
  if (insertion_result2.second) {
    std::cout << *insertion_result2.first << " has been inserted\n";
  }

  b.emplace(5); // do nothing (already in set) // modern variant of .insert()
  b.erase(2);   // remove existing value
  b.erase(4);   // do nothing (not existing value)

  auto finder = b.find(3);
  if (finder != b.end()) { // Value found
    std::cout << *finder << " has been found\n";
  }

  //#region [print set]
  for (auto &&x : b) {
    std::cout << x << " ";
  }
  std::cout << "\n";
  //#endregion

  b.clear();
  if (b.empty()) {
    std::cout << "After .clear(), set has now size = " << b.size() << "\n";
  }
}