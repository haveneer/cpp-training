//#region [Declarations]
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
  Engineer(const std::string &name) : _name{name} {}
  // Avec override les implémentations doivent suivre l'interface
  std::string describe() const override { return "[Engineer: " + _name + "]"; }

public:
  std::string _name;
};

int main() {
  Employee *e = new Engineer{"John"};
  std::cout << e->describe() << "\n";
  delete e;
}