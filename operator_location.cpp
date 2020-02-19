//#region [Declarations]
#include <iostream>
//#endregion

class Number {
private:
  int m_val;

public:
  Number(const int v) : m_val(v) {}
  int value() const { return m_val; }

  // Operator overload inside type: first operand is implicitly current object
  // Can use private attribute
  auto operator+(const Number &that) const {
    return Number{m_val + that.m_val};
  }
  Number operator-(const Number &that) const { return {m_val - that.m_val}; }
  auto operator<=(const Number &that) const { return m_val <= that.m_val; }
};

// Mixed type: this one _cannot_ be in Number class
auto operator+(const int a, const Number &b) { return Number{a} + b; }
// Mixed type: this one _can_ be in Number class
auto operator+(const Number &a, const int b) { return a + Number{b}; }

// Mixed type: this one _cannot_ be in Number class
auto operator-(const int a, const Number &b) { return Number{a} - b; }
// Mixed type: this one _can_ be in Number class
auto operator-(const Number &a, const int b) { return a - Number{b}; }

// Usually operator<< is an operator overload for object streaming.
decltype(auto) operator<<(std::ostream &o, const Number &a) {
  return o << a.value();
}

int main() {
  Number a{1};
  int b{2};

  Number c = a + b;
  std::cout << a << " + " << b << " = " << c << '\n';

  Number d = b - a;
  std::cout << b << " - " << a << " = " << d << '\n';
}
