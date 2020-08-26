//#region [Declarations]
#include <algorithm>
#include <functional>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>
//#endregion

struct SinkIterator {
  struct Unit {
    void operator=(const Unit &) {}
  };

  Unit operator*() const { return {}; }
  void operator++() {}
};

int main() {
  // choose any single value container: vector, set, list, deque, forward_list, unordered_set 
  std::unordered_set<std::string> numbers = {"one", "two", "three", "four", "five"};
  std::list<int> lengths; // and any sequential container: vector, list, deque, forward_list
  //#region [C++03 style]
  //  std::transform(numbers.begin(), numbers.end(), std::back_inserter(lengths),
  //                 std::bind(&std::string::length, std::placeholders::_1)); // old school
  //  std::transform(numbers.begin(), numbers.end(), std::back_inserter(lengths),
  //                 std::mem_fn(&std::string::length)); // do not use deprecated mem_fun (bug in clang-5)
  //  lengths.clear(); // let's do it again
  //#endregion
  // C++11 style with lambda
  std::transform(numbers.begin(), numbers.end(), std::back_inserter(lengths),
                 [](const std::string &s) -> int { return s.length(); });
  // With binary operator and Custom output iterator
  std::transform(numbers.begin(), numbers.end(), lengths.begin(), SinkIterator{},
                 [](const std::string &s, int n) -> SinkIterator::Unit {
                   std::cout << s << " has " << n << " letters.\n";
                   return {};
                 });
}