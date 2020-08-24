//#region [Declaration]
#include <iostream>
#include <string>
//#endregion

class Employee {
public:
  virtual std::string describe() const = 0;
  virtual ~Employee() = default;
};

class Engineer : public Employee {
public:
  std::string describe() const override { return "Engineer"; }
  ~Engineer() override { std::cout << "Engineer dtor\n"; }
};

class TestEngineer : public Engineer {
public:
  std::string describe() const override { return "TestEngineer"; }
  ~TestEngineer() override { std::cout << "TestEngineer dtor\n"; }
};

int main() {
  {
    // Employee e; // NOT CONSTRUCTIBLE
  }
  {
    TestEngineer t;
    std::cout << "t is: " << t.describe() << "\n";

    Engineer &e = t; // e is a reference on original object
    std::cout << "e is: " << e.describe() << "\n";
  }
  std::cout << "--------\n";
  {
    TestEngineer * pt = new TestEngineer{};
    std::cout << "pt is: " << pt->describe() << "\n";

    Engineer * pe = pt; // pe is a pointer on original object
    std::cout << "pe is: " << pe->describe() << "\n";

    delete pe;
  }
}