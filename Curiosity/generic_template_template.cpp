//#region [Collapse all]
//#region [Declarations]
#include <iostream>
#include <list>
#include <vector>
//#endregion

template <template <class, class> class V, class Allocator>
void f(const V<char, Allocator> &v) {
  for (auto &&e : v) {
    std::cout << e;
  }
  std::cout << '\n';
}

int main() {
  std::vector<char> v = {'H', 'e', 'l', 'l', 'o'};
  std::list<char> l = {'W', 'o', 'r', 'l', 'd'};
  f(v);
  f(l);
}
//#endregion