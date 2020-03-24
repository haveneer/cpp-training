//#region [Declarations]
#include <iostream>
#include <limits>
#include <random>
#include <cassert>

static struct {
  std::random_device random_device;
  std::default_random_engine eng{random_device()};
  std::uniform_int_distribution<> dist{0, 1};
  bool operator()() { return dist(eng); }
} random_boolean;

const double NaN = std::numeric_limits<double>::quiet_NaN(); // NaN ready to be used
//#endregion

int seed = 1; // [coliru] change me to generate another random number sequence

int main() {
  double x = random_boolean() - random_boolean();
  if (x > 0) // TODO: how do you write this using explicit block delimiters
    std::cout << "x is positive\n";
  else if (x < 0)
    std::cout << "x is negative\n";
  else if (x == 0)
    std::cout << "x is zero\n";
  else // TODO: is there any value of x which matchs this case ?
    std::cout << "x has an unexpected value\n";

  int n = random_boolean() - random_boolean() + random_boolean();
  std::cout << "n = " << n << '\n';

  // TODO: fix indentation of the following code section
  // TODO: how do you write this using explicit block delimiters ?
  // clang-format off
  if (n > 0)
  if (n > 1)
    assert(n == 2);
  else
    assert(n == 1);
  else if (n < 0)
    assert(n == -1);
  else
    assert(n == 0);
  // clang-format on

  // TODO: what happens if we remove block delimiters ?
  if (n > 0) {
    if (n == 2)
      std::cout << "n has the maximal value\n";
  } else {
    if (n < 0)
      std::cout << "n has the minimal value\n";
  }
}