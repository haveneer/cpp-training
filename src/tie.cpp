//#region [declarations]
// Example from
// https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/structured-bindings

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <string>

#include <tuple>
//#endregion

struct S {
  int n;
  std::string s;
  double d;
  bool operator<(const S &rhs) const {
    // compares n to rhs.n,
    // then s to rhs.s,
    // then d to rhs.d
    return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
  }
};

int main() {
  std::set<S> mySet;

  // pre C++11:
  {
    S value{42, "Test", 3.14};
    // unpack manually
    std::pair<std::set<S>::iterator, bool> inserter = mySet.insert(value);
    std::set<S>::iterator &iter = inserter.first;
    const bool inserted = inserter.second;

    if (inserted)
      std::cout << "Value(" << iter->n << ", ...) was inserted\n";
  }
  
  // with C++11:
  {
    S value{42, "Test", 3.14};
    std::set<S>::iterator iter;
    bool inserted;

    // unpacks the return val of insert into iter and inserted
    std::tie(iter, inserted) = mySet.insert(value);

    if (inserted)
      std::cout << "Value(" << iter->n << ", ...) was inserted\n";
  }

  // with C++17:
  {
    S value{42, "Test", 3.14};
    const auto [iter, inserted] = mySet.insert(value);

    if (inserted)
      std::cout << "Value(" << iter->n << ", ...) was inserted\n";
  }
}