/* - typedef
- I/O
- initalization
- operator
- overload
- exception

Gnuplot avec "set terminal dumb" pour le mode Ascii Art */

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>

using Real = double;

struct DReal {
  Real value;
  Real dvalue;
};

std::ostream &operator<<(std::ostream &o, const DReal &r) {
  return o << "(" << r.value << "," << r.dvalue << ")";
}

DReal constant(const Real a) { return {a}; }
DReal x_at(const Real v) { return {v, 1}; }
DReal operator+(const DReal &f, const DReal &g) {
  return {f.value + g.value, f.dvalue + g.dvalue};
}
DReal operator-(const DReal &f, const DReal &g) {
  return {f.value - g.value, f.dvalue - g.dvalue};
}
DReal operator*(const DReal &f, const DReal &g) {
  return {f.value * g.value, g.value * f.dvalue + f.value * g.dvalue};
}

class MyException : std::exception {
public:
  explicit MyException(const char *what) : m_what(what) {}
  const char *what() const noexcept override { return m_what; }

private:
  const char *m_what;
};

DReal operator/(const DReal &f, const DReal &g) {
  if (g.value == 0.) {
    throw MyException{"Null denominator"};
  }
  return {f.value / g.value,
          (f.dvalue * g.value - g.dvalue * f.value) / (g.value * g.value)};
}

DReal sin(const DReal &g) { return {sin(g.value), g.dvalue * cos(g.value)}; }
DReal sqrt(const DReal &g) {
  return DReal{0.5 * g.dvalue} / DReal{sqrt(g.value)};
}

auto sqr = [](const DReal &f) -> DReal { return f * f; };
auto cube = [](const DReal &f) -> DReal { return f * f * f; };

// template<typename F> void plot(const char * filename, const Real xmin, const
// Real xmax, const int n, const F & f) {
void plot(const char *filename, const Real xmin, const Real xmax, const int n,
          const std::function<DReal(DReal)> &f) {
  std::ofstream out(filename);
  Real dx = (xmax - xmin) / n;
  Real x = xmin;
  for (int i = 0; i <= n; ++i, x += dx) {
    try {
      DReal fx = f(x_at(x));
      out << x << " " << fx.value << " " << fx.dvalue << "\n";
    } catch (MyException &e) {
      std::cout << "Exception " << e.what() << " at position x=" << x << "\n";
    }
  }
}

int main() {
  Real Pi = 4 * atan(1);
  std::cout << "Pi is " << DReal{Pi} << std::endl;

  Real x0 = Pi / 2;
  try {
    DReal v = cube(sin(x_at(x0)));
    std::cout << "sin(x^3) at " << x0 << " : " << v << "\n";
  } catch (MyException &e) {
    std::cout << "Exception catched while evaluating sin(x)^3 at " << x0
              << "\n";
  }

  Real x1 = 1;
  try {
    DReal v = constant(1) / cube(x_at(x1));
    std::cout << "1/x^3 at " << x1 << " : " << v << "\n";
  } catch (MyException &e) {
    std::cout << "Exception catched while evaluating 1/x^3 at " << x1 << "\n";
  }

  auto sin3 = [](DReal x) -> DReal { return cube(sin(x) + constant(1)); };
  auto inv = [](DReal x) -> DReal { return constant(1) / x; };

  // plot("sin3.gp",0,Pi,50,sin3);
  plot("f.gp", 0, 1, 20, inv);
  plot("f.gp", 0, 1, 20, [inv](DReal x) -> DReal { return sin(inv(x)); });

  return 0;
}