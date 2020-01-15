//#region [Declarations]
#include <iostream>
//#endregion

class Employee {
public:
  virtual std::string describe() const = 0;
  virtual ~Employee() = default;
};

class Engineer : public Employee {
public:
  Engineer(const std::string & name) :  _name{name} { }
  std::string describe() const override { return "[Engineer: " + _name + "]"; }

public:
  std::string _name;
};

int main() {
  Employee *e = new Engineer{"John"};
  std::cout << e->describe() << "\n";
  delete e;
}