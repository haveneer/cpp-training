//#region [declarations]
#include <iostream>
#include <string_view>

void *operator new(std::size_t n) {
  std::cout << "new() " << n << " bytes\n";
  return malloc(n);
}
//#endregion

std::string_view getSubstringFromHint(const std::string_view &s,
                                      const std::string_view &hint) {
  return s.substr(s.find(hint));
}

int main() {
  std::string_view sentence{"Hello Amazing C++ World"};

  auto subStr = getSubstringFromHint(sentence, "C++");
  std::cout << subStr << '\n';

  // TODO: how many heap allocations ?
  //#region[the answer]
  std::cout << "0 allocation\n";
  //#endregion
}