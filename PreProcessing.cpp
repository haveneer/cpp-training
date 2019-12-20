// Standard system include
#include <iostream>

// First time (use headers)
#include "PreProcessing-advanced.hpp"
#include "PreProcessing-simple.hpp"

// Second time ?
#include "PreProcessing-advanced.hpp"
#include "PreProcessing-simple.hpp"

// Utilisation de macros définies ci-dessus
FUNCTION(one, 1);
FUNCTION(two, 2);

int main() {
  OUTPUT1("Running " __FILE__);
  OUTPUT1("Hello, world!");
  std::cout << DATETIME << ": C++ version : " << VERSION << std::endl;
#if !defined(EXPERIMENTAL_OPTIONAL)
  std::cout << DATETIME << ": Has experimental std::optional" << std::endl;
#else
  std::cout << DATETIME << ": Has std::optional : " << HAS_OPTIONAL << std::endl;
#endif
  OUTPUT1(function_one());
  OUTPUT2(function_two());

  OUTPUT2(Bye bye);
  return RETURN_CODE;
}