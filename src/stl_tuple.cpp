//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <tuple>
#include <type_traits>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
#define DISPLAY_TYPE(F) \
  { std::cout << std::setw(14) << #F << " : " << type<decltype(F)>() << std::endl; }
//#endregion

//#region [from tuple custom tools]
template <class T, class Tuple, size_t... Is>
T custom_construct_from_tuple(Tuple &&tuple, std::index_sequence<Is...>) {
  return T{std::get<Is>(std::forward<Tuple>(tuple))...};
}

template <class T, class Tuple> T custom_construct_from_tuple(Tuple &&tuple) {
  return custom_construct_from_tuple<T>(
      std::forward<Tuple>(tuple),
      std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

template <class T, class Tuple> struct is_constructible_from_tuple {};

template <class T, class... Args>
struct is_constructible_from_tuple<T, std::tuple<Args...>>
    : std::integral_constant<bool, std::is_constructible_v<T, Args...>> {};
//#endregion

class X {
public:
  X(const char c, const int i, const double f) : m_c(c), m_i(i), m_f(f) {}

private:
  const char m_c;
  const int m_i;
  const double m_f;
};

struct Y {
  // no explicit constructor => not std::is_constructible
  const char c;
  const int i;
  const double f;
};

auto print = [](auto &&...args) {
  std::cout << "Print anything :";
  ((std::cout << " " << args), ...);
  std::cout << std::endl;
};

int main() {
  // clang-format off
  using MyTuple = std::tuple<char, int, double>;
  MyTuple v1{'Z', 3, 4.2};                                                DISPLAY_TYPE(v1);

  auto v2 = std::make_tuple('Z', 3, 4.2); /* type defined by objects */   DISPLAY_TYPE(v2);

  // access to tuple size
  static_assert(std::tuple_size<MyTuple>::value == 3);

  // access to element type and value
  std::tuple_element<0, MyTuple>::type e0 = std::get<0>(v1);              DISPLAY_TYPE(e0);
  auto &e1 = std::get<1>(v1);                                             DISPLAY_TYPE(e1);
  e1 *= 2;
  std::get<1>(v1) *= 2;                                                 

  // tie variable
  char c1 = '\0';
  int i1 = 0;
  std::tie(c1, i1, std::ignore) = v1; // also available with std::pair
  auto & [c2, i2, _] = v1; // C++17 Structured binding declaration

  auto result = std::apply([](auto a, auto b, auto c) { return a + b + c; }, v2);
                                                                          DISPLAY_TYPE(result);
  std::apply(print, v1);

  //#region [Collapse all]
  // std::cout << std::boolalpha;
  std::cout << std::string(51,'-') << "\n";
  std::cout << "   "
            << std::setw(24) << "constructible from tuple" << " "
            << std::setw(7) << "trivial" << " "
            << std::setw(15) << "standard_layout"
            << "\n";

  std::cout << "X: " 
            << std::setw(24) << is_constructible_from_tuple<X, MyTuple>::value << " "
            << std::setw(7) << std::is_trivial<X>::value << " " 
            << std::setw(15) << std::is_standard_layout<X>::value
            << "\n";
  std::cout << "Y: "
            << std::setw(24) << is_constructible_from_tuple<Y, MyTuple>::value << " "
            << std::setw(7) << std::is_trivial<Y>::value << " "
            << std::setw(15) << std::is_standard_layout<Y>::value
            << "\n";
  std::cout << std::string(51,'-') << "\n";
  //#endregion

  auto x = std::make_from_tuple<X>(v1);                                   DISPLAY_TYPE(x);
  //  auto y = std::make_from_tuple<Y>(v1); /* not available in C++17 */  DISPLAY_TYPE(y);
  auto x2 = custom_construct_from_tuple<X>(v1);                           DISPLAY_TYPE(x2);
  auto y2 = custom_construct_from_tuple<Y>(v1);                           DISPLAY_TYPE(y2);
}