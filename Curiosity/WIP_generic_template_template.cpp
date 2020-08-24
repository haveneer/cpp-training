//#region [Declarations]
#include <functional>
#include <iostream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
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
  std::cout << type(opt) << '\n';

  std::function<Maybe<char>(const int &)> f = [](const int &i) {
    return Maybe{'a'};
  };
  auto r = Monad<Maybe>::bind(opt, f);
  std::cout << type(r) << '\n';
}