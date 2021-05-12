#include <cstdint>

#include <benchmark/benchmark.h>
#include <ctime>
#include <map>
#include <random>
#include <unordered_map>

#define COUNT 500
#define SIZE 100

static void Random(benchmark::State &state) {
  for (auto _ : state) {
    std::mt19937 engine{123};
    std::uniform_int_distribution<int> dist{0, SIZE};
    std::map<int, double> m;
    for (int i = 0; i < COUNT; ++i) {
      benchmark::DoNotOptimize(dist(engine));
    }
  }
}
// Register the function as a benchmark
BENCHMARK(Random);

static void Map(benchmark::State &state) {
  for (auto _ : state) {
    std::mt19937 engine{123};
    std::uniform_int_distribution<int> dist{0, SIZE};
    std::map<int, double> m;
    for (int i = 0; i < COUNT; ++i) {
      m[dist(engine)]++;
    }
    benchmark::DoNotOptimize(m);
  }
}
// Register the function as a benchmark
BENCHMARK(Map);

static void UMap(benchmark::State &state) {
  for (auto _ : state) {
    std::mt19937 engine{123};
    std::uniform_int_distribution<int> dist{0, SIZE};
    std::unordered_map<int, double> m;
    for (int i = 0; i < COUNT; ++i) {
      m[dist(engine)]++;
    }
    benchmark::DoNotOptimize(m);
  }
}
// Register the function as a benchmark
BENCHMARK(UMap);

BENCHMARK_MAIN();