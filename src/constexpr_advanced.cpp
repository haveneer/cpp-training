//#region [Declarations]
#include <cstddef> // std::size_t
#include <stdexcept>
//#endregion

template <typename T, std::size_t N> class MyTable {
public:
  using value_type = T;
  using size_type = std::size_t;

private:
  value_type vals[N];

public:
  constexpr MyTable() : vals{{}} {}
  constexpr const value_type &operator[](size_type n) const { return vals[n]; }
  constexpr value_type &operator[](size_type n) { return vals[n]; }
};

constexpr unsigned long factorial(int n) {
  return n < 0    ? throw std::out_of_range("Invalid negative argument")
         : n == 0 ? 1ULL
                  : n * factorial(n - 1);
}

template <std::size_t N> constexpr auto generateTable() {
  MyTable<unsigned long, N> res;
  for (std::size_t i = 0; i != N; ++i)
    res[i] = factorial(i);
  return res;
}

template <typename T, std::size_t N>
constexpr auto findValue(const MyTable<T, N> &tab, const T &val) -> bool {
  for (std::size_t i = 0; i < N; ++i)
    if (tab[i] == val)
      return true;
  return false;
}

int main() {
  // constexpr auto bad_call = factorial(-1);
  constexpr const auto static_table = generateTable<20>();

  constexpr auto val = 120UL;
  // auto val = 120UL;           // TODO: What happens here ?
  // constexpr auto val = 121UL; // TODO:      and here ?
  static_assert(findValue(static_table, val), "Not found");
}