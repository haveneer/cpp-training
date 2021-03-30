//#region [declarations]
#include <iostream>
//#endregion

template <typename T, T v> struct Constant03 { constexpr static T value = v; };
template <auto v> struct Constant17 { constexpr static decltype(v) value = v; };

template <typename T, T value> constexpr T ConstantT11 = value;
template <auto value> constexpr auto ConstantT17 = value;

template <auto... vs> struct HeterogenousValueList {
  void print() { (std::cout << ... << vs) << '\n'; }
};

//#region [details]
enum class Enum { X };
std::ostream &operator<<(std::ostream &o, Enum) { return o << "Enum::X"; }

struct Class {
  void f() {}
};

int f(int) { return 42; }

static constexpr char str_value[] = " string ";

static int obj = 1;
//#endregion

template <auto *f> struct Caller {
  int operator()(int i) { return f(i); }
};

int main() {
  static_assert(Constant03<int, 3>::value == Constant17<3>::value);
  static_assert(ConstantT11<int, 3> == ConstantT17<3>);

  HeterogenousValueList<&obj, str_value, 100, ' ', f, ' ', &Class::f, ' ', Enum::X>
      l;
  l.print();

  Caller<f> caller;
  std::cout << "caller(1) = " << caller(1) << '\n';
}
