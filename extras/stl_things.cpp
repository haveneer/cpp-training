#include <string>
#include <iostream>
#include <algorithm>

int main() {
  std::string id = "if";
  if (auto keywords = {"if", "for", "while"};
      std::any_of(keywords.begin(), keywords.end(),
                  [&id](const char *kw) { return id == kw; })) {
    std::cerr << "Reserved keyword [" << id << "] are not allowed as identifier\n";
  }
}
  
