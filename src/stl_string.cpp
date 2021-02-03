//#region [Declarations]
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>
/* Entropy area */
//#endregion

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

template <typename T> T random_element(const std::vector<T> &v) {
  std::random_device random_device;
  std::mt19937 engine{random_device()};
  std::uniform_int_distribution<int> dist(0, v.size() - 1);
  return v[dist(engine)];
}

int main() {
  // clang-format off
  std::vector<std::string> pronouns({"my", "a", "the", "your", "our"});
  std::string input_nouns = "cat bicycle baker computer bed finger balloon door spoon guitar theory salad client tree sofa mountain basket";
  // std::getline(std::cin, input_nouns); // or read from stdin
  if (input_nouns.empty()) return 1; // premature exit
  std::vector<std::string> nouns(split(input_nouns, ' '));
  std::vector<std::string> adjectives({"red", "lazy", "giant", "crazy", "funny", "smart", "nervous", "flat", "delicious", "boring", "chatty"});
  std::vector<std::string> verbs({"eats", "carries", "watches", "talks to", "buys", "paints", "stretches", "breaks", "smells", "respects"});
  std::vector<std::string> names({"Paul", "Fred", "Bernardo", "Isa", "Alex", "Maurice", "Vincent", "David"});
  // clang-format on

  std::string sentence;
  for (auto x : {pronouns, adjectives, nouns, verbs, pronouns, adjectives, nouns}) {
    sentence += random_element(x) + ' ';
  }
  sentence.resize(sentence.size() - 1); // remove final useless space
  std::string key = "the";
  std::size_t found = sentence.find(key);
  if (found != std::string::npos) {
    std::string name = random_element(names);
    sentence.insert(found + key.length(), " " + name + "'s");
  }
  sentence += '.';          // final point
  sentence[0] += 'A' - 'a'; // upcase

  std::cout << sentence << "\n";

  std::ofstream file("sentence.dat"); // always with 'const char *'
  file.write(sentence.c_str(), sentence.length());
}