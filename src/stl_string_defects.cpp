//#region [declarations]
#include <iostream>
#include <string>

void *operator new(std::size_t n) {
  std::cout << "new() " << n << " bytes\n";
  return malloc(n);
}
#define LOCATE() std::cout << "Line " << __LINE__ << "...\n"
//#endregion

std::string getSubstringFromHint(const std::string &s, const std::string &hint) {
  return s.substr(s.find(hint));
}

int main() {
  LOCATE();
  std::string sentence{"Hello Amazing C++ World (long, very long string to avoid SSO)"};
  LOCATE();
  std::string subStr = getSubstringFromHint(sentence, "C++");
  LOCATE();
  std::cout << subStr << '\n';

  // TODO: how many heap allocations ?
  //#region[the answer]
  std::cout << "(at least) 3 allocations:\n"
            << " 1  : 'sentence' ctor      (if not SSO)\n"
            << "+1  : 'hint' arg ctor      (if not SSO)\n"
            << "+1  : function result ctor (if not SSO)\n"
            << "+0-2: string copy if RVO is not available\n";
  //#endregion
}