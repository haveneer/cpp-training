//#region [Declarations]
#include <iostream>
#ifndef _MSC_VER
#define PRINTME() std::cout << __PRETTY_FUNCTION__ << '\n'
#else
#define PRINTME() std::cout << __FUNCSIG__ << '\n'
#endif
//#endregion

// TODO: and if it is 'int f(int)' ?
int f(double) { PRINTME(); return 0; }

int g(int) { PRINTME(); return 0; }
int g(long) { PRINTME(); return 0; }

int h_int(int &) { PRINTME(); return 0; }
int h_long(long &) { PRINTME(); return 0; }

int h(int &) { PRINTME(); return 0; }
int h(long &) { PRINTME(); return 0; }

int main() {
  f(1);   // Conversion int->double
  f(1.0);

  g(1);   // La surcharge permet de trouver la "bonne" fonction
  g(1l);
  g(true);// ou la conversion la plus "simple" / "naturel"
  // g(1.0);  // mais parfois ce n'est pas possible "sans risque"
  //          // error: call to 'g' is ambiguous

  int i = 0;
  long x = 0;

  // Si le paramètre est une référence ou un pointeur les conversions sont plus limitées
  h_int(i);
  // h_long(i); // error: no matching function for call to 'h_long'
  // h_int(x); // error: no matching function for call to 'h_int'
  h_long(x);

  h(i);
  h(x);
}