//#region [Declaration]
#include <iostream>
#include <string>
// WARNING: missing virtual destructor !
//#endregion

class Person {
public:
  Person(const std::string &name) : _name{name} {}
  std::string name() const { return _name; }

private:
  std::string _name;
};

class Student : public Person {
public:
  Student(const std::string &name, const std::string &id)
      : Person{name}, _id{id} {}
  std::string id() const { return _id; }

private:
  std::string _id;
};

class GraduatedStudent : public Student {
public:
  GraduatedStudent(const std::string &name, const std::string &id,
                   const std::string &graduation)
      : Student{name, id}, _graduation{graduation} {}
  std::string graduation() const { return _graduation; }

private:
  std::string _graduation;
};

int main() {
  Person p("Jane Smith");
  // id() method not available in Person
  std::cout << "Person: " << p.name() /* << " " << s.id() */ << "\n";

  Student s("John Doe", "414141");
  // name() method inherited from Person
  std::cout << "Student: " << s.name() << " " << s.id() << "\n";

  Person &rs = s;
  // id() method is no more available since Student is seen as a Person
  std::cout << "Student as Person&: "
            << rs.name() /* << " " << rs.id() */ << "\n";

  Person *ps = &s;
  // id() method is no more available since Student is seen as a Person
  std::cout << "Student as Person*: "
            << ps->name() /* << " " << ps->id() */ << "\n";
}
