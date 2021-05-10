//#region [Collapse all]
#include <cassert>
#include <iostream>
#include <vector>
//#endregion

// a macro
#define PRINT(employee) std::cout << "Employee(id=" << employee.id << ")\n";

struct Employee { // trivial object (no special function or field)
  int id{};
  int age = {}; // brace initializations ensure
  float wage{}; // a default initialization for all these objects
};

Employee makeEmployee() { return {1, 42, 60000.0f}; } // returned object init

int main() { // modern C++ (before AAA rule)
  Employee defaultEmployee;
  Employee emptyEmployee{};
  Employee john{1, 42, 60000.0f};
  Employee johnny = {john};

  int anArray[]{3, 2, 7, 5, 8};
  std::vector<int> a{1, 2, 3, 4, 5}; // initializer list ctor: error in C++03
  std::vector<int> b{&anArray[0], &anArray[0] + 5}; // /!\ iterator range ctor

  Employee bill = makeEmployee();

  Employee employees[] = {{1, 20, 20000}, {2, 50, 40000}, {4, 35, 35000}};
  assert(sizeof(employees) / sizeof(Employee) == 3);

  PRINT((Employee{1, 42, 60000.0f})); // without extra (), it will not compile
}
