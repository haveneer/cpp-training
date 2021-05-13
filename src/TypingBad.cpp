//#region [declarations]
#include <iostream>
//#endregion

class MyClass {
public:
  MyClass(int i) { m_field = i; } // prefer initialization list
  int &field() { return m_field; }
  int &otherField() { return m_other_field; }

private:
  int m_field;
  int m_other_field;
};

int main() {
  int *p; // inconsistent transition state
  p = new int(1);

  MyClass c(1.);
  std::cout << c.otherField() << '\n';

  /* do something else */
  
  delete p; // possible memory leak (TODO: Why ?)
}