//#region [declarations]
#include <iostream>
//#endregion

//#region [function definitions]
int global = 1;
int &setGlobal() { return global; }
int getGlobal() { return global; }

void set_ref(int &x) { x = 0; }
void from_const_ref(const int &x) {}
void set_rvalue_ref(int &&x) { x = 0; }
int &rvalue_ref(int &&x) { return x; }
//#endregion

int main() { // Error messages come from GCC 9.2

  //#region [With objects]
  int a = 42;  // OK: lvalue = rvalue
  int b = a;   // OK: lvalue = lvalue
  int *p = &a; // OK: lvalue = rvalue
  *p = 666;    // OK: lvalue = rvalue
  // 42 = a;        // error: lvalue required as left operand of assignment
  // int * q = &42; // error: lvalue required as unary '&' operand
  // 42 = 3.14;     // error: lvalue required as left operand of assignment

  char *v = "Hello";
  // v[0] = 'W'; // Attention au runtime ! Ce n'est qu'un warning
  //             // warning: ISO C++ forbids converting a string constant to 'char*'

  const char *w = "Hello";
  const char **x = &w;
  //#endregion

  //#region [With functions returns]
  setGlobal() = 0; // OK: lvalue = rvalue
  // getGlobal() = 0; // error: lvalue required as left operand of assignment
  //#endregion

  //#region [With Expressions]
  int c = 1;
  int d = 2;
  int e = c + d; // OK: lvalue = rvalue
  // 3 = c + d; // error: lvalue required as left operand of assignment
  //#endregion

  //#region [Lvalue reference]
  int i = 1;
  int &iref = i; // lvalue reference
  std::cout << "&i=" << &i << ", &iref=" << &iref << std::endl;
  i++; // i == 2

  // int &jref = 1; // error: cannot bind non-const lvalue reference of type
  //                // 'int&' to an rvalue of type 'int'

  // set_ref(1);  // error: cannot bind non-const lvalue reference of type
  //              // 'int&' to an rvalue of type 'int'
  int j = 1;
  set_ref(j);
  //#endregion

  //#region [const Lvalue reference]
  const int &kref = 1;
  from_const_ref(1);
  // kref++; // error: increment of read-only reference 'kref'

  const int m = 2;
  // m = 3; // error: assignment of read-only variable 'm'
  //#endregion

  //#region [/!\ Advanced]
  std::cout << "-- Advanced --\n";
  ((i < 3) ? a : b) = 7; // conditional returns an lvalue
  // ((i < 3) ? a : m) = 7; // error: assignment of read-only location 'a'
  //                        // error: assignment of read-only location 'm'

  std::cout << "BEFORE i=" << i << ", a=" << a << ", b=" << b << ", c=" << c
            << ", d=" << d << std::endl;
  set_ref(++i);
  set_ref(a = b);
  set_ref((c, d));
  std::cout << "AFTER  i=" << i << ", a=" << a << ", b=" << b << ", c=" << c
            << ", d=" << d << std::endl;
  // set_ref(i++); // error: cannot bind non-const lvalue reference of type
  //                    // 'int&' to an rvalue of type 'int'

  set_rvalue_ref(42);
  // set_rvalue_ref(i); // error: cannot bind rvalue reference of type 'int&&' to
  // lvalue of type 'int'

  // int & q = rvalue_ref(e); // error: cannot bind rvalue reference of type 'int&&'
  // to lvalue of type 'int'
  int &r = rvalue_ref(42) += 1; // WARNING
  std::cout << "r=" << r << std::endl;

  int &&s = 42;
  s += 1;
  std::cout << "s=" << s << std::endl;

  int *&&t = &r; // &r is an rvalue of type int*
  (*t) += 1;
  std::cout << "t=" << t << ", r=" << &r << ", " << r << std::endl;

  int &&u = std::move(e); // data from argument may be stolen

  auto cout_ref = &std::cout;
  *cout_ref << "Hello\n";
  //#endregion
}