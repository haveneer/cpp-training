//#region [Declarations]
#include <functional>
#include <iostream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

template <template <typename> class M> struct Monad {
  template <typename A> static M<A> pure(const A &);

  template <typename A, typename B>
  static M<B> mbind(const M<A> &, M<B> (*)(const A &));
};

template <typename T> class Maybe {
public:
  Maybe() : m_is_nothing{true} {}
  Maybe(const T &t) : m_is_nothing{false}, m_value{t} {}

  bool isNothing() const { return m_is_nothing; }
  const T &value() const { return m_value; }

private:
  bool m_is_nothing;
  T m_value;
};

template <> struct Monad<Maybe> {
  template <typename T> static Maybe<T> pure(const T &v) { return {v}; }

  template <typename A, typename B>
  static Maybe<B>
  bind(const Maybe<A> &action,
       const std::function<Maybe<B>(const A &)> &function) { // FIXME
    if (action.isNothing())
      return {};
    else
      return function(action.value());
  }
};

int main() {
  auto opt = Monad<Maybe>::pure(1);
  std::cout << type<decltype(opt)>() << '\n';

  std::function<Maybe<char>(const int &)> f = [](const int &i) {
    return Maybe{'a'};
  };
  auto r = Monad<Maybe>::bind(opt, f);
  std::cout << type<decltype(r)>() << '\n';
}