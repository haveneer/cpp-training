//#region [Collapse all]
#include <iostream>
#include <string>
class MyString : public std::string {
public:
  MyString() : m_attr(new int) {}
  ~MyString() { std::cout << "MyString is well destroyed" << std::endl; }

private:
  int *m_attr;
};

int main() {
  std::string *s = new MyString();
  delete s; // MyString::~MyString is not called !
}
//#endregion