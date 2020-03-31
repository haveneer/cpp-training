//#region [Declarations]
#include <iostream>
#include <string>
//#endregion

struct Employee {
  std::string name;
  long id;
};

std::ostream &operator<<(std::ostream &os, const Employee &e) {
  return os << "Employee(" << e.name << ", " << e.id << ")";
}

int main() {
  Employee john{"John", 42};
  Employee simon{"Simon", 37};

  std::cout << john << " and " << simon;
}