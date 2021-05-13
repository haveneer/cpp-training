//#region [Headers]
#include <array>
#include <benchmark/benchmark.h>
#include <map>
#include <type_traits>
#include <unordered_map>
#include <vector>
//#endregion
//#region [Configs]
#define COUNT 500
#define SIZE 1000

// local traits
struct UnsafeMode {};
struct SafeMode {};
struct InOrder {};
struct RandomOrder {};
//#endregion
//#region [Dummy structures]
struct DummyValue {
  template <typename T> void operator=(const T &) {}
  operator int() { return 1; }
};
struct DummyContainer {
  DummyValue operator[](std::size_t) { return {}; }
  DummyValue at(std::size_t) { return {}; }
};
//#endregion

template <typename Mode, typename Order, typename Container, auto... args>
void bench(benchmark::State &state) {
  benchmark::ClobberMemory();
  Container c(args...);
  benchmark::DoNotOptimize(c);
  for (std::size_t i = 0; i < SIZE; ++i) // same way to fill all container
    c[i] = 1;                            // not the most efficient for all
  auto indexer = []() {
    if constexpr (std::is_same_v<Order, RandomOrder>) {
      return [](const int i) {
        const unsigned i2 = i ^ 0x7777'7777;
        return (((i2 >> 16) + (i2 << 16)) % SIZE);
      };
    } else {
      static_assert(std::is_same_v<Order, InOrder>);
      return [](const int i) { return i; };
    }
  }();

  for (auto _ : state) {
    int val = 0;
    for (int i = 0; i < COUNT; ++i) {
      if constexpr (std::is_same_v<Mode, UnsafeMode>) {
        val += c[indexer(i)];
      } else {
        static_assert(std::is_same_v<Mode, SafeMode>);
        val += c.at(indexer(i));
      }
    }
    benchmark::DoNotOptimize(val);
    benchmark::ClobberMemory();
  }
}

#define ORDER RandomOrder // TODO Change me: InOrder or RandomOrder
#define COMMA ,           // google benchmark macro does not support true comma
BENCHMARK_TEMPLATE(bench, SafeMode, ORDER, DummyContainer)
    ->Name("Do Nothing Reference");
BENCHMARK_TEMPLATE(bench, UnsafeMode, ORDER, std::array<int COMMA SIZE>)
    ->Name("array::operator[]");
BENCHMARK_TEMPLATE(bench, SafeMode, ORDER, std::array<int COMMA SIZE>)
    ->Name("array::at");
BENCHMARK_TEMPLATE(bench, UnsafeMode, ORDER, std::vector<int>, SIZE)
    ->Name("vector::operator[]");
BENCHMARK_TEMPLATE(bench, SafeMode, ORDER, std::vector<int>, SIZE)
    ->Name("vector::at");
BENCHMARK_TEMPLATE(bench, UnsafeMode, ORDER, std::map<int COMMA int>)
    ->Name("map::operator[]");
BENCHMARK_TEMPLATE(bench, SafeMode, ORDER, std::map<int COMMA int>)
    ->Name("map::at");
BENCHMARK_TEMPLATE(bench, UnsafeMode, ORDER, std::unordered_map<int COMMA int>)
    ->Name("unordered_map::operator[]");
BENCHMARK_TEMPLATE(bench, SafeMode, ORDER, std::unordered_map<int COMMA int>)
    ->Name("unordered_map::at");

BENCHMARK_MAIN();