//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <limits>

struct S {
  bool v_bool;
  int v_int;
  double v_double;
  std::string v_string;
};
//#endregion

int main() {
  S s = {true, 42, 3.141592653589793238, "Hello World!"};

  // clang-format off
  std::cout << "bool   = " << s.v_bool << '\n' 
            << "int    = " << s.v_int << '\n'
            << "double = " << s.v_double << '\n'
            << "string = " << s.v_string << '\n';
  
  // Fill 30 chars with '-'
  std::cout << std::setw(30) << std::setfill('-') << '\n';
  std::cout.fill(' ');

  const auto precision = std::cout.precision(); // save current precision
  // set new flags on stream (with maximal precision for floating number)
  std::cout << std::setprecision(std::numeric_limits<double>::digits10 + 1) 
            << std::boolalpha << std::showbase << std::scientific;
  
  std::cout << std::left // for string, use alignment on the left with a width of 7
            << std::setw(7) << "bool"   << "= " << s.v_bool << '\n'
            << std::setw(7) << "int"    << "= " << std::hex << s.v_int << '\n'
            << std::setw(7) << "double" << "= " << s.v_double << '\n'
            << std::setw(7) << "string" << "= " << s.v_string << '\n';
  // clang-format on
  // Restore flags on stream
  std::cout.precision(precision);
  std::cout.unsetf(std::ios_base::boolalpha);
  std::cout.unsetf(std::ios_base::showbase);
  std::cout.unsetf(std::ios_base::scientific);
}