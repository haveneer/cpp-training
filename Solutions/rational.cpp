#include <exception>
#include <iostream>

struct RationalNumber {
  int p, q;
};

// https://en.wikipedia.org/wiki/Euclidean_algorithm
int pgcd(int u, int v) {
  while (u > 0) {
    if (v > u) {
      std::swap(u, v);
    }
    u = u % v;
  }
  return v;
}

RationalNumber make_rational(int p) { return {p, 1}; }

RationalNumber make_rational(int p, int q) {
  if (q == 0) {
    throw std::invalid_argument{"Illegal null denominator"};
  }

  int sign = ((p < 0) ^ (q < 0)) ? -1 : 1;
  p = std::abs(p);
  q = std::abs(q);

  int r = pgcd(p, q);
  std::cout << "r=" << r << "\n";
  return {sign * p / r, q / r};
}

std::ostream &operator<<(std::ostream &o, const RationalNumber &r) {
  if (r.q == 1) {
    return o << r.p;
  } else {
    return o << r.p << '/' << r.q;
  }
}

RationalNumber operator+(const RationalNumber &r1, const RationalNumber &r2) {
  return make_rational(r1.p * r2.q + r1.q * r2.p, r1.q * r2.q);
}
RationalNumber operator+(const RationalNumber &r, int &n) {
  return make_rational(r.p + r.q * n, r.q);
}
RationalNumber operator+(int &n, const RationalNumber &r) {
  return make_rational(r.p + r.q * n, r.q);
}

int main() {
  RationalNumber a = make_rational(1, -2);
  RationalNumber b{1, 1};

  std::cout << a << " + " << b << " = " << (a + b) << '\n';
}