//#region [Declarations]
#include <cassert>
#include <string>
#include <tuple>
using namespace std::string_literals;
//#endregion

//#region [Implementation details]
template <typename... Ts> struct any_of : private std::tuple<Ts...> {
  using std::tuple<Ts...>::tuple;
  template <typename T> constexpr bool operator==(const T &t) const {
    return std::apply([&t](const auto &... ts) { return ((ts == t) || ...); },
                      static_cast<const std::tuple<Ts...> &>(*this));
  }
  template <typename T>
  friend constexpr bool operator==(const T &lh, const any_of &rh) {
    return rh == lh;
  }
};

template <typename T, typename... Ts>
constexpr bool operator!=(const T &lh, const any_of<Ts...> &rh) {
  return !(rh == lh);
}
template <typename T, typename... Ts>
constexpr bool operator!=(const any_of<Ts...> &lh, const T &rh) {
  return !(rh == lh);
}

template <typename... Ts> any_of(Ts...)->any_of<Ts...>;
//#endregion

int main() {
  //#region [Variable declarations]
  enum class Thing { Chair, Table, Car, Bike, Sofa, Window, Computer, Door };
  const Thing x = Thing::Sofa;
  const int y = 1;
  const std::string z = "1";
  //#endregion

  // ** DRY in action **
  // What do you prefer ?

  static_assert(x == Thing::Chair || x == Thing::Table || x == Thing::Sofa);
  // or
  static_assert(x == any_of(Thing::Chair, Thing::Table, Thing::Sofa));

  static_assert(y != 2 && y != 5 && y != 3);
  // or
  static_assert(y != any_of(2, 5, 3));

  assert(z == "1" || z == "2" || z == "3");
  // or
  assert(z == any_of("1", "2", "3"));
}