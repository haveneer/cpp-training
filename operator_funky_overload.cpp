//#region [Declarations]
#include <iostream>
#include <typeinfo>
#include <vector>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
//#endregion

class MatrixLike {
public:
  virtual double operator()(int i, int j) const = 0;
};

class Matrix : public MatrixLike {
public:
  double operator()(int i, int j) const override { return i + j; };
};

//#region [Composition]
template <typename MatrixLikeT, typename F>
class TransformedMatrix : public MatrixLike {
public:
  TransformedMatrix(MatrixLikeT m, F f)
      : m_m{std::move(m)}, m_f(std::move(f)) {}

  double operator()(int i, int j) const override { return m_f(m_m(i, j)); };

private:
  const MatrixLikeT m_m;
  const F m_f;
};

template <
    typename MatrixLikeT, typename G,
    std::enable_if_t<
        std::is_base_of<MatrixLike, std::decay_t<MatrixLikeT>>::value, int> = 0>
auto operator|(MatrixLikeT &&m, G &&g) {
  //  std::cout << std::is_base_of<MatrixLike, MatrixLikeT>::value << '\n';
  return TransformedMatrix{std::forward<MatrixLikeT>(m), std::forward<G>(g)};
}

template <typename F, typename G,
          std::enable_if_t<!std::is_base_of<MatrixLike, std::decay_t<F>>::value,
                           int> = 0>
auto operator|(F &&f, G &&g) {
  //  std::cout << std::is_base_of<MatrixLike, F>::value << '\n';
  return [f = std::forward<F>(f), g = std::forward<G>(g)](double x) {
    return g(f(x));
  };
}
//#endregion

struct Multiply {
  double factor;
  auto operator()(const double &x) const { return factor * x; }
};

auto add(const double &a) {
  return [=](double x) { return a + x; };
}

class Database {
  friend struct FieldAccessor;

public:
  struct FieldAccessor {
    Database &database;
    const std::string &name;

    // Defines has_to_string to know if type T has to_string method overload.
    template <typename, typename = void>
    struct has_to_string : std::false_type {};

    //    // Compact version
    //    template <typename T>
    //    struct has_to_string<
    //        T, std::void_t<decltype(std::to_string(std::declval<T>()))>>
    //        : std::true_type {};

    template <typename...> using try_to_instantiate = void;

    template <typename T>
    using to_string_expression = decltype(std::to_string(std::declval<T>()));

    template <typename T>
    struct has_to_string<T, try_to_instantiate<to_string_expression<T>>>
        : std::true_type {};
    // end of 'has_to_string' definition

    template <typename T>
    std::enable_if_t<!has_to_string<T>{}> operator+=(T &&t) {
      database.m_data.emplace_back(name, type<T>(), "[not evaluated]");
    }

    template <typename T>
    std::enable_if_t<has_to_string<T>{}> operator+=(T &&t) {
      database.m_data.emplace_back(name, type<T>(), std::to_string(t));
    }
  };

public:
  FieldAccessor operator[](const std::string &name) {
    return FieldAccessor{*this, name};
  }

  const auto &data() const { return m_data; }

private:
  std::vector<std::tuple<std::string, std::string, std::string>> m_data;
};

struct File {
  std::string filename;

  void operator<<=(const Database &db) {
    std::cout << "Will write in '" << filename << "':\n";
    for (auto &&e : db.data()) {
      std::cout << "  " << std::get<0>(e) << " : " << std::get<1>(e) << " -> "
                << std::get<2>(e) << '\n';
    }
  }
};

int main() {
  Database database;
  Matrix matrix;

  auto transform = Multiply{2} | add(2);
  database["Value"] += (matrix | transform)(1, 2);
  database["Value"] += (matrix | [](double x) { return -x; });
  File{"dbfile"} <<= database;
}