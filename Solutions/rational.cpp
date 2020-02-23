#include <exception>
#include <iostream>

struct rational {
  int p;
  int q;
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

rational make_rational(int p) { return {p, 1}; }

rational make_rational(int p, int q) {
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

std::ostream &operator<<(std::ostream &o, const rational &r) {
  if (r.q == 1) {
    return o << r.p;
  } else {
    return o << r.p << '/' << r.q;
  }
}

rational operator+(const rational &r1, const rational &r2) {
  return make_rational(r1.p * r2.q + r1.q * r2.p, r1.q * r2.q);
}
rational operator+(const rational &r, int &n) {
  return make_rational(r.p + r.q * n, r.q);
}
rational operator+(int &n, const rational &r) {
  return make_rational(r.p + r.q * n, r.q);
}

int main() {
  rational a = make_rational(1, -2);
  rational b{1, 1};

  std::cout << a << " + " << b << " = " << (a + b) << '\n';
}