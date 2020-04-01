//#region [Declarations]
#include <iostream>
#include <sstream>
#include <string>
//#endregion

struct Musician {
  std::string name;
  int age;
};

std::ostream &operator<<(std::ostream &os, const Musician &e) {
  //                     could be Musician without const& ^
  //                     but it will produce a useless copy at each call
  return os << "Musician(" << e.name << ", " << e.age << ")"; // Don't forget return
}

// Optional interface dedicated to temporary object (for optimization only)
std::ostream &operator<<(std::ostream &os, Musician &&e) {
  return os << "Musician(" << e.name << ", " << e.age << ")"; // Don't forget return
}

std::istream &operator>>(std::istream &is, Musician &e) {
  is >> e.name; // Could be more complex depending
  is >> e.age;  // on underlying types and values (cf stream_string.cpp)
  return is;    // Don't forget return (or in one line: is >> e.name >> e.age;)
}

int main() {
  Musician george{"George", 17};

  // std::cout << george << '\n'; // is equivalent to
  operator<<(operator<<(std::cout, george), '\n');
  // that's why the return type of operator<< is std::ostream&

  // /!\ objects must exist before filling them (could be in inconsistent state)
  Musician john, paul; // not really RAII compatible

  std::istringstream iss("Paul 18 John 20"); // read from string; could be from file
  iss >> paul >> john;
  std::cout << paul << " and " << john << '\n';

  std::cout << Musician{"Ringo", 20} << "\n"; // with temporary object
}