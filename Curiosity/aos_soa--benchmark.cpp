// alternative approach in
// https://www.fluentcpp.com/2018/12/21/an-soa-vector-with-an-stl-container-interface-in-cpp/

#include <benchmark/benchmark.h>
#include <cassert>
#include <gtest/gtest.h>
#include <iostream>
#include <tuple>
#include <vector>

template <std::size_t N> using int_type = std::integral_constant<std::size_t, N>;
template <std::size_t N> int_type<N> int_v = int_type<N>{};

/***************************************/
/// Trait to detect vector type

namespace detail {
template <typename T> std::false_type is_vector(T const &) {
  return std::false_type{};
}

template <typename T, typename Allocator>
std::true_type is_vector(const std::vector<T, Allocator> &) {
  return std::true_type{};
}
} // namespace detail

template <typename T>
using is_vector_t = decltype(detail::is_vector(std::declval<T>()));

/***************************************/
/// get a value from an index in scalar (=> index=0 only) or in a tuple

namespace detail {
template <typename> struct is_tuple : std::false_type {};
template <typename... T> struct is_tuple<std::tuple<T...>> : std::true_type {};

template <typename T>
auto &getValueHelper(const int_type<0>, T &d, std::false_type /* is_tuple */) {
  return d;
}

template <std::size_t I, typename... Ts>
auto &getValueHelper(const int_type<I>, std::tuple<Ts...> &d,
                     std::true_type /* is_tuple */) {
  return std::get<I>(d);
}

template <typename T> auto &getValueHelper(const int_type<0> i, T &d) {
  return getValueHelper(i, d, is_tuple<decltype(d)>{});
}
} // namespace detail

/***************************************/
/// converter from type or tuple to vector of type or tuple of vector

template <typename T> struct as_vector { using type = std::vector<T>; };

template <typename... Ts> struct as_vector<std::tuple<Ts...>> {
  using type = std::tuple<typename as_vector<Ts>::type...>;
};

template <typename T> using as_vector_t = typename as_vector<T>::type;

/***************************************/

// This structure makes a tuple of vector of types from a tuple of types
// Warning: cannot manage bool type because vector<bool> is a specialized class
template <typename T> class soa {
public:
  using data_type = as_vector_t<T>;

public:
  soa(std::size_t n) : soa(n, detail::is_vector(m_data)) {}

private:
  // Internal delegated constructors
  soa(std::size_t n, std::true_type &&) : m_data(n) {}
  soa(std::size_t n, std::false_type &&) { resize(n); }

public:
  auto size() const { return size(m_data); }
  void resize(std::size_t n) { resize(n, m_data); }

  template <std::size_t I> //
  decltype(auto) operator()(const int_type<I> &i, const int j) {
    return getArray(i, m_data)[j];
  }

  decltype(auto) operator()(const int j) { return getTuple(j, m_data); }

private:
  data_type m_data;

private:
  /// size utilities
  template <typename Data> static auto size(const Data &d) {
    return size(d, detail::is_vector(d));
  }

  template <typename Data> static auto size(const Data &d, std::true_type &&) {
    return d.size();
  }

  template <typename Data> static auto size(const Data &d, std::false_type &&) {
    return size(std::get<0>(d));
  }

  /// resize utilities
  template <typename Type, typename Alloc>
  static void resize(std::size_t n, std::vector<Type, Alloc> &d) {
    d.resize(n);
  }

  template <typename... Types> //
  static void resize(std::size_t n, std::tuple<Types...> &d) {
    resize(n, d, int_type<0>{},
           typename std::tuple_size<std::tuple<Types...>>::type{});
  }

  template <typename Tuple, std::size_t I, std::size_t N>
  static void resize(std::size_t n, Tuple &d, int_type<I> &&,
                     const int_type<N> &sz) {
    resize(n, std::get<I>(d));
    resize(n, d, int_type<I + 1>{}, sz);
  }

  template <typename Tuple, std::size_t N>
  static void resize(std::size_t, Tuple &, int_type<N> &&, const int_type<N> &) {}

  /// accessor utilities
  template <typename Type, typename Alloc>
  inline static auto &getArray(const int_type<0>, std::vector<Type, Alloc> &d) {
    return d;
  }

  template <std::size_t I, typename... Types> //
  inline static auto &getArray(const int_type<I> &, std::tuple<Types...> &d) {
    return std::get<I>(d);
  }

  template <typename Type, typename Alloc>
  inline static auto &getTuple(const int j, std::vector<Type, Alloc> &d) {
    return d[j];
  }

  template <typename... Ts>
  inline static auto getTuple(const int j, std::tuple<std::vector<Ts>...> &d) {
    return make_tuple_ref_helper(j, d, std::make_index_sequence<sizeof...(Ts)>{});
  }

  template <typename... Ts, std::size_t... Is>
  inline static auto make_tuple_ref_helper(const int j,
                                           std::tuple<std::vector<Ts>...> &d,
                                           std::index_sequence<Is...>) {
    return std::tuple<Ts &...>{std::get<Is>(d)[j]...};
  }
};

template <typename T> struct aos : private std::vector<T> {
  using std::vector<T>::vector;
  using std::vector<T>::size;
  using std::vector<T>::resize;

  template <std::size_t I> //
  decltype(auto) operator()(const int_type<I> &i, const int j) {
    auto &row = std::vector<T>::operator[](j);
    return detail::getValueHelper(i, row, detail::is_tuple<T>{});
  }
  T &operator()(const int j) { return std::vector<T>::operator[](j); }
};

#include <string>
using data = std::tuple<double, std::string, int>;

const std::size_t N = 1000;

static void SingleSOA(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  soa<int> array(N);
  for (auto _ : state) {
    for (std::size_t i = 0; i < N; ++i) {
      array(int_v<0>, i)++;
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(array);
  }
}
// Register the function as a benchmark
BENCHMARK(SingleSOA);

static void SingleAOS(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  aos<int> array(N);
  for (auto _ : state) {
    for (std::size_t i = 0; i < N; ++i) {
      array(int_v<0>, i)++;
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(array);
  }
}
// Register the function as a benchmark
BENCHMARK(SingleAOS);

static void MultiSOA(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  soa<data> array(N);
  for (auto _ : state) {
    for (std::size_t i = 0; i < N; ++i) {
      array(int_v<0>, i)++;
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(array);
  }
}
// Register the function as a benchmark
BENCHMARK(MultiSOA);

static void MultiAOS(benchmark::State &state) {
  // Code inside this loop is measured repeatedly
  aos<data> array(N);
  for (auto _ : state) {
    for (std::size_t i = 0; i < N; ++i) {
      array(int_v<0>, i)++;
    }
    // Make sure the variable is not optimized away by compiler
    benchmark::DoNotOptimize(array);
  }
}
// Register the function as a benchmark
BENCHMARK(MultiAOS);

// For benchmark results see:
// https://quick-bench.com/q/z06vbXBcwSFBV9ylrjad0BDhcnU
// https://godbolt.org/z/GebrqsYzG
// -----------------------------------------------------
// Benchmark           Time             CPU   Iterations
//-----------------------------------------------------
// SingleSOA         293 ns          174 ns      4454495
// SingleAOS         289 ns          172 ns      4260708
// MultiSOA          316 ns          185 ns      3813173
// MultiAOS         1820 ns          757 ns       950312

TEST(ASO_VS_OSA, Benchmark) { ::benchmark::RunSpecifiedBenchmarks(); }

// soa and aos have the same API to compare performance
template <template<typename...> class S, typename T> void templateTest() {
  S<T> c(5);
  c(int_v<0>, 4) = 3;
  c.resize(10);
  if constexpr (detail::is_tuple<T>::value) {
    assert(&c(int_v<0>, 4) == &std::get<0>(c(4)));
    std::cout << c.size() << " " << std::get<0>(c(4)) << "\n";
  } else {
    assert(&c(int_v<0>, 4) == &c(4));
    std::cout << c.size() << " " << detail::getValueHelper(int_v<0>, c(4)) << "\n";
  }
}

TEST(ASO_VS_OSA, SingleSOA) { templateTest<soa, int>(); }
TEST(ASO_VS_OSA, SingleAOS) { templateTest<aos, int>(); }
TEST(ASO_VS_OSA, MultiSOA) { templateTest<soa, data>(); }
TEST(ASO_VS_OSA, MultiAOS) { templateTest<aos, data>(); }
