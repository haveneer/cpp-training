//#region [Declarations]
#include <iostream>
#include <vector>

bool shared_flag; // may be located in any compilation unit

class FakeMutex;

class FakeLock {
public:
  FakeLock(FakeMutex &) { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ~FakeLock() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};

class FakeMutex {
public:
  FakeMutex() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
  ~FakeMutex() { std::cout << __PRETTY_FUNCTION__ << '\n'; }
};
//#endregion

constexpr auto architecture_size() {
  // compile-tme evaluation
  if constexpr (sizeof(void *) == 4) {
    return 32;
  } else if constexpr (sizeof(void *) == 8) {
    return 64;
  } else {
    // even discarded statement must be well formed
    // error: cannot initialize variable of type 'int *' with an rvalue of type 'int'
    // int * p = 1;

    // but do not participate in function return type deduction
    return; // not an int value
  }
}

FakeMutex mutex;
extern bool shared_flag; // protected by mutex

int main() {
  std::cout << "--------------\n";

  constexpr std::size_t arch = architecture_size();

  std::string str = "Hello world; how'r u?";
  std::string token = "w";
  if (auto pos = str.find(token); pos != std::string::npos) {
    std::cout << "Token [" << token << "] found at position " << pos << "\n";
  }

  std::cout << "--- Before ---\n";
  if (FakeLock lock{mutex}; shared_flag) {
    std::cout << "Do unsafe job\n";
  } else {
    std::cout << "Cannot process unsafe job\n";
  }
  std::cout << "--- After ---\n";
}