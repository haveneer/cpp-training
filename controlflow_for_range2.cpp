//#region [Declarations]
#include <array>
#include <iostream>
#include <list>
#include <valarray>
#include <vector>
//#endregion

int main() {
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