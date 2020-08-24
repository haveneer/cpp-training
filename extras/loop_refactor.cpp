#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using Data = std::string;

bool filter(const Data &data) { return data.size() > 5 && data[0] == 't'; }

bool find_predicate1(const std::vector<Data> &data) {
  // C++03 style
  std::vector<Data>::const_iterator it = data.begin();
  for (; it != data.end(); ++it) {
    if (filter(*it))
      return true;
  }
  return false;
}

bool find_predicate2(const std::vector<Data> &data) {
  // C++11 style with auto
  for (auto it = data.begin(); it != data.end(); ++it) {
    if (filter(*it))
      return true;
  }
  return false;
}

bool find_predicate3(const std::vector<Data> &data) {
  // C++11 style with range based for loop
  for (auto const &data : data) {
    if (filter(data))
      return true;
  }

  return false;
}

bool find_predicate4(const std::vector<Data> &data) {
  // C++11 style using STL algorithm (and begin/end function not members)
  return std::find_if(std::begin(data), std::end(data), filter) != std::end(data);
}

bool find_predicate5(const std::vector<Data> &data) {
  // C++11 style with embedded lamda function
  return std::find_if(begin(data), end(data), [](const Data &data) {
           return data.size() > 5 && data[0] == 't';
         }) != end(data);
}

int main() {
  std::vector<std::string> words = {"undef",    "nothing", "stocking", "floor",
                                    "suit",     "turkey",  "limit",    "measure",
                                    "goldfish", "west",    "talk"};

  std::cout << find_predicate1(words) << "\n";
  std::cout << find_predicate2(words) << "\n";
  std::cout << find_predicate3(words) << "\n";
  std::cout << find_predicate4(words) << "\n";
  std::cout << find_predicate5(words) << "\n";
}