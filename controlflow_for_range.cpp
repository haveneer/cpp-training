//#region [Declarations]
#include <array>
#include <iostream>
#include <list>
#include <valarray>
#include <vector>
//#endregion

int main() {
  int v1[5] = {1, 2, 3, 4, 5};
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

  // HINT: if you can, always use auto type
  // FIXME replace element type in previous example using type inference
  const std::valarray<double> v4 = {1, 2, 3, 4, 5};
  for (auto &x : v4) {     // using reference, you ask 'no copy'
    std::cout << x << ' '; // const will be inferred automagically
    // x *= 2;             // since container is const and you cannot modify it
  }
  std::cout << '\n';

  std::list<int> v5{1, 2, 3, 4, 5};
  for (auto &x : v5) { // also compatible with non indexed containers
    x += 1;
    std::cout << x << ' ';
  }
  std::cout << '\n';

  const char *messages[] = {"Hello", "World", ";", "do", "you", "have", "fun?"};
  for (auto &word : messages) {
    std::cout << word << ' ';
  }
  std::cout << '\n';

  // error: invalid range expression of type 'int *';
  // no viable 'begin' function available
  //  int *manual_array = new int[20];
  //  for (int &i : manual_array) { i = 20; }
}