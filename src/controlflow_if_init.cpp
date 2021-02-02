//#region [Declarations]
#include <iostream>
#include <vector>
#include <string>
#ifndef _MSC_VER
#define PRINTME() std::cout << __PRETTY_FUNCTION__ << '\n'
#else
#define PRINTME() std::cout << __FUNCSIG__ << '\n'
#endif

bool shared_flag; // may be located in any compilation unit

class FakeMutex;

class FakeLock {
public:
  FakeLock(FakeMutex &) { PRINTME(); }
  ~FakeLock() { PRINTME(); }
};

class FakeMutex {
public:
  FakeMutex() { PRINTME(); }
  ~FakeMutex() { PRINTME(); }
};
//#endregion

FakeMutex mutex;
extern bool shared_flag; // protected by mutex

int main(int argc, char ** argv) {
  std::cout << "--------------\n";
  if (int k = argc; argv[k]) {
    std::cerr << "Catastrophe: last argv should be null\n";
  }

  // Be careful, if you mix it with comma operator (FIXME)
  const int n = argc;
  if (int k = n, argv[n]; true) {
    std::cerr << "What argv is it ? argv[0] = " << argv[0] << "\n";
  }
  
  std::string str = "Hello world; how'r u?";
  std::string token = "w";
  if (auto pos = str.find(token); pos != std::string::npos) {
    std::cout << "Token [" << token << "] found at position " << pos << "\n";
  }

  std::string value = "1234";
  if (auto i = std::stoi(value); i > 0) { std::cout << "Positive value\n"; }

  std::cout << "--- Before ---\n";
  // A perfect solution for effectful scoped object
  if (FakeLock lock{mutex}; shared_flag) {
    std::cout << "Do unsafe job\n";
  } else {
    std::cout << "Cannot process unsafe job\n";
  }
  std::cout << "--- After ---\n";
}