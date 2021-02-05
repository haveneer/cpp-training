#include <cstdint>

// later: use https://github.com/google/benchmark
#ifndef QUICK_BENCH
namespace benchmark {

class State {
public:
  struct Iterator {
    uint64_t pos;
    void operator++() { ++pos; }
    auto operator*() const { return pos; }
    bool operator!=(const Iterator &other) const { return pos != other.pos; }
  };

public:
  State(uint64_t size) : m_size{size}, m_current{0} {}
  Iterator begin() const { return {m_current}; }
  Iterator end() const { return {m_size}; }

private:
  uint64_t m_size;
  uint64_t m_current;
};

template <typename T> void DoNotOptimize(const T &t) {}

} // namespace benchmark
#define BENCHMARK(X)
#endif

#include <ctime>
#include <map>
#include <unordered_map>
#include <random>

#define SIZE 100

static void Random(benchmark::State &state) {
  for (auto _ : state) {
    srandom(123);
    std::map<int, double> m;
    for (int i = 0; i < SIZE; ++i) {
      benchmark::DoNotOptimize(random() % SIZE);
    }
  }
}
// Register the function as a benchmark
BENCHMARK(Random);

static void Map(benchmark::State &state) {
  for (auto _ : state) {
    srandom(123);
    std::map<int, double> m;
    for (int i = 0; i < SIZE; ++i) {
      m[random() % SIZE]++;
    }
    benchmark::DoNotOptimize(m);
  }
}
// Register the function as a benchmark
BENCHMARK(Map);

static void UMap(benchmark::State &state) {
  for (auto _ : state) {
    srandom(123);
    std::unordered_map<int, double> m;
    for (int i = 0; i < SIZE; ++i) {
      m[random() % SIZE]++;
    }
    benchmark::DoNotOptimize(m);
  }
}
// Register the function as a benchmark
BENCHMARK(UMap);

// ------------------------------------------------>%
int main() {
  benchmark::State state{10*SIZE};
#ifdef HAS_PMR
  PMRList(state);
  PMRVector(state);
#endif
  Random(state);
  Map(state);
  UMap(state);
}