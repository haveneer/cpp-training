//#region [Declarations]
#include <iostream>
//#endregion

struct Number {
  int val;

  // Operator overload inside type: first operand is implicitly current object
  auto operator+(const Number &that) { return Number{val + that.val}; }
  auto operator+(const int &that) { return Number{val + that}; }
  auto operator<=(const Number &that) const { return val <= that.val; }
};

// Operator overload out of any class. Explicit object operands
Number operator-(const Number &a, const Number &b) { return {a.val + b.val}; }

// Usually operator<< is an operator overload for object streaming.
decltype(auto) operator<<(std::ostream &o, const Number &a) {
  return o << a.val;
}

// /!\ consistency of your operator overload is your responsability
Number operator*(const Number &a, const Number &b) { return {a.val - b.val}; }

// Overload with a custom meaning (be careful to associativity and priority)
Number operator!(const Number &a) {
  Number r{1};
  for (Number i{1}; i <= a; i = i + 1)
    r = r * i;
  return r;
}

int main() {
  Number a{1};
  Number b{2};

  Number c = a + b;
  std::cout << a << " + " << b << " = " << c << '\n';

  Number d = a - b;
  std::cout << a << " - " << b << " = " << d << '\n';

  std::cout << "!" << c << " = " << !c << '\n';
}