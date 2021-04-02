//#region [Collapse all]
#include <initializer_list>
#include <iostream>
#include <vector>
//#endregion

struct Collection {                                           // Fake collection
  Collection(std::initializer_list<int> l) : latest_data(l) { // default {} ctor
    std::cout << "Ctor from list of " << latest_data.size() << '\n';
  }
  Collection(int n) { // only when explicit () call
    std::cout << "Ctor from int " << n << '\n';
  }
  void append(std::initializer_list<int> l) { latest_data = l; }

  std::initializer_list<int> latest_data; // HINT DON'T DO THIS: bug is coming
};

int main(int argc, const char *argv[]) {
  Collection c1 = {1, 2, 3, 4}; // Many (equivalent) styles of initialization
  Collection c2({1, 2, 3, 4});
  Collection c3{1, 2, 3, 4};
  // Collection c4(1, 2, 3, 4); // error: no matching constructor for initialization
  std::puts("--------------------");
  Collection c5{4}; // { } uses initializer_list ctor when available
  Collection c6(4); // (rather than scalar ctor)
  // Also available for your methods
  c6.append({1, 2, 3});          // { } are required here
  c6.append({4, (argc + 1), 6}); // OK, even if not constants

  //#region [Danger Zone]
  std::puts("--------------------");
  std::cout << "{ ";
  for (auto x : c6.latest_data) { // TODO: seems to be Ok; what is the problem?
    std::cout << x << " ";
  }
  std::cout << "}\n";

  int array[] = {3, 1, 4, 1, 5, 9, 2};
  // std::initializer_list<int> // error: calling a private constructor
  //    l(std::begin(array), std::size(array));
  //#endregion
}