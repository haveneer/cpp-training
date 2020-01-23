//#region [Declarations]
#include <exception>
#include <iostream>

struct forbidden_exception : std::exception {};
//#endregion


void f() noexcept {
  // Throwing an exception in noexcept function leads to a fatal terminate() call
  throw forbidden_exception{};
}

int main() {
  try {
    f();
  } catch (std::exception &e) {
    // Will be never reached due a terminate from f illegal exception
    std::cout << "Catched exception\n";
  }
}