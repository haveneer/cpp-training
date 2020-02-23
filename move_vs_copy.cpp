//#region [Declarations]
// inspired from
// https://www.modernescpp.com/index.php/copy-versus-move-semantic-a-few-numbers

#include <array>
#include <chrono>
#include <deque>
#include <forward_list>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
//#endregion

const int SIZE = 100000; // smaller for online tests

//#region [bench function]
template <typename T> void bench_copy_vs_move(T t, const std::string &cont) {
  std::cout << std::fixed << std::setprecision(6);
  std::cout << cont << std::endl;

  std::ofstream devNull("/dev/null");

  auto start = std::chrono::system_clock::now();
  T t1(t);
  auto duration = std::chrono::system_clock::now() - start;
  auto copyTime = std::chrono::duration<double>(duration).count();

  auto begin = std::begin(t1); // work around too aggressive optimization
  for(int i=0;i<SIZE/2;++i) ++begin;
    devNull << &*begin;

  start = std::chrono::system_clock::now();
  T t2(std::move(t));
  duration = std::chrono::system_clock::now() - start;
  auto moveTime = std::chrono::duration<double>(duration).count();

  begin = std::begin(t2); // work around too aggressive optimization
  for(int i=0;i<SIZE/2;++i) ++begin;
  devNull << &*begin;

  std::cout << "    Copy: " << copyTime << " sec "
            << "/ Move: " << moveTime << " sec" << std::endl;

  std::cout << std::setprecision(2);
  std::cout << "  Ratio (copy time/move time): " << (copyTime / moveTime)
            << std::endl;
  //  std::cout << std::endl;
}
//#endregion

int main() {
  std::cout << "SIZE = " << SIZE << std::endl;
  {
    std::array<int, SIZE / 100> myArray{};
    bench_copy_vs_move(myArray, "std::array<int,SIZE/100>");
  }

  {
    std::vector<int> myVec(SIZE);
    bench_copy_vs_move(myVec, "std::vector<int>(SIZE)");
  }

  {
    std::deque<int> myDec(SIZE);
    bench_copy_vs_move(myDec, "std::deque<int>(SIZE)");
  }

  {
    std::list<int> myList(SIZE);
    bench_copy_vs_move(myList, "std::list<int>(SIZE)");
  }

  {
    std::forward_list<int> myForwardList(SIZE);
    bench_copy_vs_move(myForwardList, "std::forward_list<int>(SIZE)");
  }

  {
    std::string myString(SIZE, ' ');
    bench_copy_vs_move(myString, "std::string(SIZE,' ')");
  }

  std::vector<int> tmpVec(SIZE);
  std::iota(tmpVec.begin(), tmpVec.end(), 0);

  {
    std::set<int> mySet(tmpVec.begin(), tmpVec.end());
    bench_copy_vs_move(mySet, "std::set<int>");
  }

  {
    std::unordered_set<int> myUnorderedSet(tmpVec.begin(), tmpVec.end());
    bench_copy_vs_move(myUnorderedSet, "std::unordered_set<int>");
  }

  {
    std::map<int, int> myMap;
    for (auto i = 0; i <= SIZE; ++i)
      myMap[i] = i;
    bench_copy_vs_move(myMap, "std::map<int,int>");
  }

  {
    std::unordered_map<int, int> myUnorderedMap;
    for (auto i = 0; i <= SIZE; ++i)
      myUnorderedMap[i] = i;
    bench_copy_vs_move(myUnorderedMap, "std::unordered_map<int,int>");
  }
}