#include <iostream>
#include <map>

int main() {
  std::multimap<char, int> mymm;
  mymm.insert(std::pair<char, int>('a', 10));

  mymm.insert(std::pair<char, int>('b', 20));
  mymm.insert(std::pair<char, int>('b', 30));
  mymm.insert(std::pair<char, int>('b', 40));

  mymm.insert(std::pair<char, int>('c', 50));
  mymm.insert(std::pair<char, int>('c', 60));

  mymm.insert(std::pair<char, int>('d', 60));

  std::cout << "mymm contains:\n";
  for (char ch = 'a'; ch <= 'd'; ch++) {
    std::cout << ch << " =>";
    /* clang-format off
       In place of 'auto', the real returned type is:
       std::pair<std::multimap<char, int>::iterator, std::multimap<char, int>::iterator>
       clang-format on */
    auto ret = mymm.equal_range(ch);
    for (auto it = ret.first; it != ret.second; ++it)
      std::cout << " " << (*it).second;
    std::cout << std::endl;
  }

  return 0;
}