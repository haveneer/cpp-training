//#region [Declarations]
#include <exception>
#include <iostream>

struct forbidden_exception : std::exception {};
struct normal_exception : std::exception {};
//#endregion

struct ExceptionalDestructor {
  ~ExceptionalDestructor() { // dtor cannot throw an exception
    // Throwing an exception in destructor leads to a fatal terminate() call
    throw forbidden_exception{};
  }
};

int main() {
  try {
    // Stack unwinding will destroy the object
    ExceptionalDestructor obj{}; // it will throw illegally an exception
    throw normal_exception{};
  } catch (std::exception &e) {
    // Never reached due a terminate()
    std::cout << "Catched exception\n";
  }
}