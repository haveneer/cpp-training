//#region [Declarations]
#include <iostream>
#include <memory>
//#endregion

// Objects of Test cannot be dynamically allocated
class Test {
private:
  // Notice this, new operator function is private
  void *operator new(std::size_t size);

private:
  int x;

public:
  Test() {
    x = 9;
    std::cout << "Constructor is called\n";
  }
  void display() { std::cout << "x = " << x << "\n"; }
  ~Test() { std::cout << "Destructor is executed\n"; }
};

int main() {
  // Uncommenting following line would cause a compile time error.
  // Test* obj=new Test();
  Test t; // Ok, object is allocated at compile time
  t.display();
  return 0;
} // object goes out of scope, destructor will be called