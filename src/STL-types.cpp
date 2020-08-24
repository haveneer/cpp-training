//#region [Declarations]
#include <cmath>
#include <complex>
#include <iomanip>
#include <iostream>
#include <string>
//#endregion

int main() {
  double a = 1;
  double b = 2;
  std::complex<double> p{a, b};
  std::string a_as_string = std::to_string(a);
  std::string b_as_string = std::to_string(b);
  std::string p_as_string = a_as_string + " + " + b_as_string + 'i';

  std::complex<double> r1 = std::exp(p);

  double r2re = std::exp(a) * std::cos(b);
  double r2im = std::exp(a) * std::sin(b);
  std::complex<double> r2{r2re, r2im};

  std::cout << "Check computation of exp(" << p_as_string << ")\n"
            << "error is " << std::abs(r1 - r2) << '\n';
}