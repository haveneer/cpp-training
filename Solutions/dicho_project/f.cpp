#include "f.hpp"
#include <cmath>

const Real e = std::exp(1);
Real x0 = 40; // TODO: increase x0 from 1 to 40

// definition de f
Real f(Real x) { return x - x0 + std::exp(x) - std::pow(e, x); }
