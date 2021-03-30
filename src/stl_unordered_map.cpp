//#region [Declarations]
#include <cctype> // pour tolower et isalpha
#include <iostream>
#include <sstream>
#include <string>
//#endregion
#include <unordered_map>

void display(const std::unordered_map<char, int> &counts, const int min_occur = 30) {
  std::cout << "-------------\n";
  for (auto &&kv : counts) {
    auto &&key = kv.first;
    auto &&value = kv.second;
    if (value > min_occur)
      std::cout << key << " -> " << value << " occurrences\n";
  }

  std::cout << "-------------\n";
  for (char key = 'a'; key <= 'z'; ++key) {
    // int value = counts[key]; // error: no viable overloaded operator[] for type 'const std::unordered_map<char, int>'
    try {
      int value = counts.at(key);
      if (value > min_occur)
        std::cout << key << " -> " << value << " occurrences\n";
    } catch (std::out_of_range &e) {
      // current key does not exist
    }
  }
  // or using counts.find(key) != counts.end(); to check if a key exists
}

int main() {
  std::unordered_map<char, int> char_counts;

  std::string text = R""(
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Praesent dapibus mauris eu nunc malesuada, 
nec auctor nisl dapibus. Cras congue orci consequat, fringilla ligula non, rhoncus sem. 
Proin feugiat faucibus tellus ac pharetra. Vestibulum id sagittis erat. 
Interdum et malesuada fames ac ante ipsum primis in faucibus. 
Sed venenatis id velit ac auctor. Sed ut iaculis libero, at accumsan metus. 
Etiam dapibus turpis massa, sed congue quam auctor vitae. 
Vestibulum accumsan consequat mi, porttitor blandit lorem bibendum nec.
)"";

  std::istringstream iss(text);
  while (iss) {
    char c{};
    iss >> c;
    if (std::isalpha(c)) {
      // this is equivalent to: insert(std::make_pair(key, T())).first->second
      char_counts[std::tolower(c)]++; // implicitly create new key if not exists
    }
  }

  display(char_counts);
}