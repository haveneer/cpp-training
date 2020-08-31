//#region [Collapse all]
//#region [Declarations]
#include <iostream>
//#endregion

// Use fold sizeof
template <typename... T> int how_many(T const &... args) {
  return sizeof...(args);
}

// ------

// Same by hand
// nominal case
template <typename Head, typename... Tail>
int how_many2(Head const &, Tail const &... tail) {
  return 1 + how_many(tail...);
}
// terminal case (no arg)
int how_many2() { return 0; }

// ------

template <int... N> struct integer_sequence {};

template <int... N> void print(integer_sequence<N...> const &) {
  bool dummy[] = {(std::cout << N, true)...};
  std::cout << "\n";
  [](auto &&){}(dummy); // silent ignore of unused variable
}

int main() {
  std::cout << how_many(1, 2) << "\n";
  std::cout << how_many2(1, 2) << "\n";

  print(integer_sequence<1, 2, 3>());
}
//#endregion