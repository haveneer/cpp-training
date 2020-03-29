#include <functional>
#include <iostream>
#include <vector>

struct Nop {};

template <typename FCond> struct IfCond {
  // IfCond(FCond f) : _cond(f){}; // replaced by CTAD
  FCond _cond;
};
template <typename FCond> IfCond(FCond)->IfCond<FCond>;

template <typename FCond, typename FThen = Nop, typename FElse = Nop>
struct IfCondThenElse {
  FCond _cond;
  FThen _then = Nop{};
  FElse _else = Nop{};

  void operator()() {
    static_assert(!std::is_same_v<FThen, Nop>, "then case required");
    static_assert(!std::is_same_v<FElse, Nop>, "else case required");
    if (_cond())
      _then();
    else
      _else();
  }
};

template <typename FCond, typename FThen>
auto operator%(IfCond<FCond> ifcond, FThen f) {
  return IfCondThenElse<FCond, FThen>{ifcond._cond, f};
}

template <typename FCond, typename FThen, typename FElse>
auto operator%(IfCondThenElse<FCond, FThen, Nop> ifcondthen, FElse f) {
  return IfCondThenElse<FCond, FThen, FElse>{ifcondthen._cond, ifcondthen._then, f};
}

// clang-format off
#define if_(x) IfCond{[=] { return (x); }} % [=]
#define else_ % [=]
// clang-format on

int main() {

  bool condition = true;

  auto x = if_(condition) {
    std::cout << "a\n";
    return 1;
  }
  else_ {
    std::cout << "b\n";
    return std::vector<int>{};
  };

  auto y = if_(condition) {
    std::cout << "a\n";
    return 1;
  };

  /* auto z = */ x();
  // y(); // ill-formed expression (no else case)
}