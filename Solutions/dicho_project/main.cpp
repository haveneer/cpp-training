#include "dicho.hpp"
#include "f.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <stdexcept>

int main(int argc, char **argv) {
  if (argc > 1) {
    x0 = std::stod(argv[1]);
  }

  Real a = x0 / 2;
  Real b = 2 * x0;
  std::cout.precision(20); // set visual precision

  try {
    int n = 0;
    dicho(a, b, 1e-9, &n);
    std::cout << "After " << n << " iterations\n";
    std::cout << "a = " << a << "  f(a) = " << f(a) << "\n";
    std::cout << "b = " << b << "  f(b) = " << f(b) << "\n";
    std::cout.precision(6); // set visual precision
    std::cout << "|b-a| = " << std::abs(b - a) << "\n";
  } catch (std::invalid_argument &e) {
    std::cerr << "Invalid Argument Error: " << e.what() << "\n";
  } catch (std::runtime_error &e) {
    std::cerr << "Runtime Error: " << e.what() << "\n";
  }
}
