//#region [Collapse all]
#include <iostream>
//#endregion

// expression template primitives

template <typename X> struct Expr {
  explicit Expr(const X &e) : ast(e) {}
  const X ast;
};

struct Ops {
  struct Id {};
  struct Add {};
};

template <typename X> auto id(const X &x) { // terminal object
  auto a = [x](auto visitor) { return visitor(Ops::Id{}, x); };
  return Expr<decltype(a)>(a);
}

template <typename X1, typename X2>
auto operator+(const Expr<X1> &e1, const Expr<X2> &e2) {
  auto a = [&e1, &e2](auto visitor) { return visitor(Ops::Add{}, e1, e2); };
  return Expr<decltype(a)>(a);
}

// visitor functor tools

std::ostream &operator<<(std::ostream &o, Ops::Add) { return o << "+"; }

struct Printer {
  template <typename X> //
  auto operator()(Ops::Id, X &x) {
    std::cout << x;
  }

  template <typename X> //
  auto operator()(const Expr<X> &e) {
    e.ast(*this);
  }

  template <typename Op, typename X1, typename X2> //
  auto operator()(const Op op, const Expr<X1> &e1, const Expr<X2> &e2) {
    std::cout << '(';
    e1.ast(*this);
    std::cout << ')' << op << '(';
    e2.ast(*this);
    std::cout << ')';
  }
};

struct Computer {
  template <typename X> //
  auto operator()(Ops::Id, X &x) {
    return x;
  }

  template <typename X> //
  auto operator()(const Expr<X> &e) {
    return e.ast(*this);
  }

  template <typename X1, typename X2> //
  auto operator()(const Ops::Add, const Expr<X1> &e1, const Expr<X2> &e2) {
    return e1.ast(*this) + e2.ast(*this);
  }
};

int main() {
  auto e = id(1) + id(2) + id(3);
  
  Printer{}(e);
  std::cout << "\nresult= " << Computer{}(e) << '\n';
}