#include <vector>
//#region [Declarations]
#include <algorithm>
#include <array>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#define INFO_HEADER()                                                           \
  std::cout << std::setw(4) << "" << std::setw(9) << ".size()" << std::setw(13) \
            << ".capacity()" << std::setw(10) << "is_sorted"                    \
            << "  content\n";

#define INFO(v) info(v, #v)

template <typename T> void info(const std::vector<T> &v, const std::string &v_name) {
  std::cout << std::setw(4) << v_name << std::setw(9) << v.size() << std::setw(13)
            << v.capacity() << std::setw(10)
            << (std::is_sorted(v.begin(), v.end()) ? "true" : "false") << "  ";
  std::ostream_iterator<int> out_it(std::cout, " ");
  std::copy(v.begin(), v.end(), out_it);
  std::cout << "\n";
}

#define EXPLAIN(f, v) explain(f, v, #f)

template <typename V>
void explain(const typename V::const_iterator &finder, const V &v,
             const std::string &f_name) {
  if (finder != v.end()) {
    std::cout << f_name << " has found value " << *finder << " at position "
              << std::distance(v.begin(), finder) << "\n";
  } else {
    std::cout << f_name << " has not found any value "
              << "\n";
  }
}

// clang-format off
// Constraints on finders were:
// for(int r = 0 ; r < 100000 ; ++r) {
//  std::cout << "=============================\n";
//  std::cout << "r = " << r << "\n";
//  std::cout << "=============================\n";
// std::mt19937 mersenne_engine{/* seed = */r};
//  if (finder1 == v.end() || ((finder1+1) != v.end() && *(finder1+1) == 20)) continue; 
//  if (finder2 == v.begin() || *finder2==20) continue; 
//  if (finder3 != v.end()) continue;
//  if (*finder4 >= 20) break; 
// }
//#endregion

int main() {
  std::mt19937 mersenne_engine{/* seed = */ 417}; // Unconstrained random generator
  std::uniform_int_distribution<int> dist{1, 52}; // With a distribution model
                                                                INFO_HEADER();
  std::vector<int> v(10);                                       INFO(v);
  std::generate(v.begin(), v.end(), // fill with random value
                [&] { return dist(mersenne_engine);});          
  v = {1, 44, 52, 20, 6, 7, 28, 11, 14, 11}; /* prefer this */  INFO(v);
  
  auto finder1 = std::find(v.begin(), v.end(), 20);             EXPLAIN(finder1, v);
  auto finder2 = std::find_if(v.begin(), v.end(), // find with predicate
                              [](auto x) { return x >= 20; });  EXPLAIN(finder2, v);
  // std::lower_bound is faster than std::find on sorted container __ONLY__ 
  auto finder3 = std::lower_bound(v.begin(), v.end(), 19);      EXPLAIN(finder3, v);
  std::sort(v.begin(), v.end()); /* if we sort it */            INFO(v);
  // ... on sorted container std::lower_bound is faster than std::find 
  auto finder4 = std::lower_bound(v.begin(), v.end(), 19);      EXPLAIN(finder4, v);

  std::shuffle(std::begin(v), std::end(v), mersenne_engine);    INFO(v);
  // the iterators are focused on a location not a value
                                                                EXPLAIN(finder4,v);
  v.insert(finder4, 666);                                       INFO(v);
  /* after insert/erase, iterator could be invalid */           // EXPLAIN(finder4,v);
}
