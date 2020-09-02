//#region [Declarations]
#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
//#endregion

template <typename Comparator>
void display(const std::map<char, int, Comparator> &counts,
             const int min_occur = 30) {
  for (auto &&kv : counts) {
    auto &&key = kv.first;
    auto &&value = kv.second;
    if (value > min_occur)
      std::cout << key << " -> " << value << " occurrences\n";
  }
  std::cout << "-------------\n";
}

struct CaseInsensitiveComparator {
  bool operator()(const char &a, const char &b) const {
    return std::tolower(a) < std::tolower(b);
  }
};

int main() {

  std::string text = R""(
RepublIc owner historian data category  preparation politics management menu promotion 
speaker goal homework feedback hearing boyfriend friendship location tension beer 
coffee tooth opportunity reputation contribution association week community library 
confusion hall drawer hair statement interaction county drawing shirt tradition 
queen performance debt literature office depth language passenger president
)"";

  std::map<char, int, CaseInsensitiveComparator> char_counts;
  for (std::istringstream iss(text); iss;) {
    char c{};
    iss >> c;
    if (std::isalpha(c)) {
      char_counts[c]++;
    }
  }
  display(char_counts);

  std::istringstream iss(text);
  std::vector<std::string> words{
      std::istream_iterator<std::string>(iss), // TODO What if ()
      std::istream_iterator<std::string>()};   // in place of {}

  auto length_compare = [](const std::string &a, const std::string &b) {
    if (a.size() != b.size())
      return a.size() < b.size();
    else
      return a > b;
  };
  std::set<std::string, decltype(length_compare)> s(length_compare);
  s.insert(words.begin(), words.end());
  std::copy_n(s.begin(), 10, std::ostream_iterator<std::string>(std::cout, " "));
  std::cout << "\n";
}