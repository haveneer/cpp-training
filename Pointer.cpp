//#region [declarations]
#include <iostream>
//#endregion

int main() {
  int val;          // non initialized stack variable
  int *p = nullptr; // pointer initialized to nullptr

  p = &val; // p now points on val
  *p = 1;   // object pointed by p is set to 1

  std::cout << "p   : " << p << std::endl;
  std::cout << "val : " << val << std::endl;

  std::cout << "sizeof(val) : " << sizeof(val) << std::endl;
  std::cout << "sizeof(p)   : " << sizeof(p) << std::endl;

  int *q = p + 1; // pointer arithmetic
  std::cout << "p+1 : " << q << std::endl;

  // char * s = &val; // illegal pointer assignment (wrong type)

  //#region [pointer of pointer on array]
  int c[] = {10, 20, 30, 40, 50};
  p = c; // new assignment on another same-type object

  int **pp = &p; // p is an object, thus p has an address...
  (*pp)++; // move forward *pp

  int *cc[2] = {&c[0], &c[1]+1}; // array of pointers
  for (auto z : cc) (*z)++;

  std::cout << "Relocated *p is now " << *p << std::endl; // where is p ?
  //#endregion
}