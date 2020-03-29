//#region [Declarations]
#include <array>
#include <iostream>
#define BIG_NUMBER 1000
//#endregion

struct BigStruct {
  int value;
  std::array<int, BIG_NUMBER> tab;
};

void f_by_value(BigStruct x) {
  /* cannot change outside argument */
  x.value += 1; /* can change parameter value */
}
void f_by_const_value(const BigStruct x) {
  /* cannot change outside argument */
  // x.value += 1; /* cannot change parameter value
}
void f_by_ref(BigStruct &x) {
  /* can change outside argument */
  x.value += 1; /* can change parameter value; could be a return value */
}
void f_by_ptr(BigStruct *x) {
  /* can change outside argument */
  x->value += 1; /* can change parameter value; could be a return value */
}
void f_by_const_ref(const BigStruct &x) {
  /* cannot change outside argument */
  // x.value += 1; /* cannot change parameter value
}

int main() {
  BigStruct a{.value = 1, .tab = {{1}}}; // C99 style

  f_by_value(a);       // COPY; ok for small objects
  f_by_const_value(a); // COPY; ok for small objects
                       // For big objects:
  f_by_ref(a);         // NO COPY, but value may be modified
  f_by_ptr(&a);        // NO COPY, but pointer style :/
  f_by_const_ref(a);   // NO COPY, value cannot be modified
}