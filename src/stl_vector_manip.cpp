#include <vector>
//#region [Declarations]
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#define INFO_HEADER()                                                           \
  std::cout << std::setw(4) << "" << std::setw(9) << ".size()" << std::setw(13) \
            << ".capacity()"                                                    \
            << "  content\n";
#define INFO(v) info(v, #v)

template <typename T> void info(const std::vector<T> &v, const std::string &v_name) {
  std::cout << std::setw(4) << v_name << std::setw(9) << v.size() << std::setw(13)
            << v.capacity() << "  ";
  std::ostream_iterator<int> out_it(std::cout, " ");
  std::copy(v.begin(), v.end(), out_it);
  std::cout << "\n";
}
//#endregion

int main() {
  // clang-format off
                                                                INFO_HEADER();
  std::vector<int> v{1, 2, 3, 4, 5};                            INFO(v);

  v[3] = 30;    /* unchecked fast access */                     INFO(v);
  v.at(4) = 40; /* slower checked access */                     INFO(v);

  try {
    // v[5] = 100; // illegal unchecked access
    v.at(5) = 50; // illegal checked access: throw exception when fails
  } catch (std::exception &e) {
    std::cout << "Caught exception: " << e.what() << '\n';
  }

  // old C++03 style
  for (std::vector<int>::iterator i = v.begin(), e = v.end(); i != e; ++i) {
    *i += 1;
  }                                                             INFO(v);
  // C++11 style with explicit iterators 
  for (auto i = v.begin(), e = v.end(); i != e; ++i) {
    *i += 1;
  }                                                             INFO(v);
  // C++11 style with ranged for loop
  for (auto &x : v) {
    x += 1;
  }                                                             INFO(v);
}