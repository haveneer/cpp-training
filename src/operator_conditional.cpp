//#region [Declarations]
#include <iostream>

// Global definitions for a smart main body
int a = 0, b = 0, a_value = 0, b_value = 0, ab_value = 0;
int f(int) { return 0; }
int g(int) { return 0; }
//#endregion

int main() {

  // TODO: How to you do the same (with const) without a conditional operator ?
  const int v1 = (a < b) ? f(a_value) : g(b_value);

  // TODO: How to you do the same (with reference) without a conditional operator ?
  const int &v2 = (a < b) ? a_value : b_value;

  // Multiline format for conditional operator
  const int v3 = (a < b)           // test
                     ? f(a_value)  // true case
                     : g(b_value); // false case

  // error: incompatible operand types ('double' and 'const char *')
  // auto v_error = (a<b) ? 1. : " ";

  // BAD PRACTICE : nested conditional operators
  const int v_bad = (a < b) ? a_value : (a > b) ? b_value : ab_value;
}