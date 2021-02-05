#include <algorithm>
#include <iostream>
#include <memory>
#include <variant>
#include <vector>

struct RationalNumber {
  int p, q;
  double value() const { return static_cast<double>(p) / q; }
};

RationalNumber operator*(const RationalNumber &a, const RationalNumber &b) {
  return {a.p * b.p, a.q * b.q};
}

RationalNumber operator*(const RationalNumber &a, int b) { return {a.p * b, a.q}; }
RationalNumber operator*(int a, const RationalNumber &b) { return b * a; }
double operator*(const RationalNumber &a, double b) { return b * a.value(); }
double operator*(double a, const RationalNumber &b) { return b * a; }

struct PolymorphNumber {
  PolymorphNumber() = default;
  PolymorphNumber(int u) : m_data(u) {}
  PolymorphNumber(double u) : m_data(u) {}
  PolymorphNumber(const RationalNumber &u) : m_data(u) {}

  template <typename Visitor> void visit(Visitor visitor) const {
    std::visit(visitor, m_data);
  }

  //  template <typename Visitor> void visit(Visitor visitor) {
  //    std::visit(visitor, m_data);
  //  }

private:
  const std::variant<int, RationalNumber, double> m_data;
};

std::ostream &operator<<(std::ostream &os, const RationalNumber &r) {
  return os << r.p << " / " << r.q;
}

std::ostream &operator<<(std::ostream &os, const PolymorphNumber &x) {
  x.visit([&os](auto const &e) { os << e; });
  return os;
}

PolymorphNumber operator*(const PolymorphNumber &a, const PolymorphNumber &b) {
  std::unique_ptr<PolymorphNumber> r; // work around to avoid copy of PolymorphNumber
  a.visit([&](auto &&xa) {
    b.visit([&](auto &&xb) { r = std::make_unique<PolymorphNumber>(xa * xb); });
  });
  return *r;
}

int main() {
  std::vector<PolymorphNumber> numbers;

  std::cout << "sizeof(int) = " << sizeof(int) << '\n';
  std::cout << "sizeof(double) = " << sizeof(double) << '\n';
  std::cout << "sizeof(RationalNumber) = " << sizeof(RationalNumber) << '\n';
  std::cout << "sizeof(std::variant<int, RationalNumber, double>) = "
            << sizeof(std::variant<int, RationalNumber, double>) << '\n';
  std::cout << "sizeof(PolymorphNumber) = " << sizeof(PolymorphNumber) << '\n';

  numbers.emplace_back(4);
  numbers.emplace_back(RationalNumber{2, 3});
  numbers.emplace_back(3.14);

  std::vector<PolymorphNumber> results;

  for (auto x : numbers) {
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(results),
                   [x](auto const &n) { return x * n; });
  }

  for (auto &&x : results)
    std::cout << x << "\n";
}
