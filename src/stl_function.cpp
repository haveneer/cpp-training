//#region [Declarations]
#include <iomanip>
#include <iostream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY_HEADER()                                   \
  {                                                        \
    std::cout << std::setw(8) << "function"                \
              << " : " << std::setw(20) << "mapped to"     \
              << " : " << std::setw(30) << "original type" \
              << " : "                                     \
              << "as std::function" << std::endl;          \
  }

#define DISPLAY_TYPE(F_ORG, F_ASFUNCTION)                                          \
  {                                                                                \
    std::string forg_type = type<decltype(F_ORG)>();                               \
    if (forg_type.size() > 30)                                                     \
      forg_type = "<too awful to show>";                                           \
    std::cout << std::setw(8) << #F_ASFUNCTION << " : " << std::setw(20) << #F_ORG \
              << " : " << std::setw(30) << forg_type << " : "                      \
              << type<decltype(F_ASFUNCTION)>() << std::endl;                      \
  }

static struct Init {
  Init() { DISPLAY_HEADER(); }
} init;

//#endregion

#include <functional>

struct X {
} x;
struct Y {
  int data{};
} y;
struct Z {
  Y y;
} z;

Z f(X, Y) { return {}; }

struct Foo {
  Z field;
  Z f(X x, Y y) const { return {y}; }
  Z g(X &x, const Y &y) { return {y}; }
} foo;

int main() {
  //#region [Legacy style]
  Z (*old_fn1)(X, Y) = f; // Function pointer (same as C)
  old_fn1(x, y);

  Z Foo::*old_fn2 = &Foo::field; // Pointer to member field
  foo.*old_fn2;

  Z (Foo::*old_fn3)(X, Y) const = &Foo::f; // Pointer to class method
  (foo.*old_fn3)(x, y);

  class Functor {
  public:
    explicit Functor(const Foo &foo) : m_foo(foo) {}
    Z operator()(X x, Y y) { return m_foo.f(x, y); }

  private:
    Foo m_foo;
  };
  Functor functor(foo);
  functor(x, y);
  //#endregion

  //#region [Complete binding]
  std::function<Z(X, Y)> fn1 = f; // convenient handler to function pointer
  DISPLAY_TYPE(f, fn1);
  fn1(x, y);

  std::function<Z(Foo const &)> fn2 = &Foo::field; // access to a field
  DISPLAY_TYPE(&Foo::field, fn2);
  fn2(foo);

  std::function<Z(Foo const &, X, Y)> fn3 = &Foo::f; // const class if const method
  DISPLAY_TYPE(&Foo::f, fn3);
  fn3(foo, x, y);

  std::function<Z(Foo &, X &, const Y &)> fn4 = &Foo::g;
  DISPLAY_TYPE(&Foo::g, fn4);
  fn4(foo, x, y);

  auto fn4b = std::mem_fn(&Foo::g); // lighter than std::function and std::bind
  DISPLAY_TYPE(&Foo::g, fn4b);
  fn4b(foo, x, y);
  //#endregion

  //#region [Partial binding]
  using namespace std::placeholders;             // for _1, _2, _3...
  std::function<Z(Y)> fn5 = std::bind(f, x, _1); // first arg of f is now set to 'x'
  DISPLAY_TYPE(std::bind(f, x, _1), fn5);
  fn5(y);

  std::function<Z(X &)> fn6 =
      std::bind(&Foo::g, foo, _1, std::cref(y)); // TODO: without std::cref() ?
  y.data = 2;
  std::cout << "y.data = " << fn6(x).y.data << "\n";
  y.data = 3;
  std::cout << "y.data = " << fn6(x).y.data << "\n";
  //#endregion
}