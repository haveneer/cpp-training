#include <cstdint>

// Special memory management :
// https://en.cppreference.com/w/cpp/header/memory_resource
// see also: https://stackoverflow.com/questions/38010544/polymorphic-allocator-when-and-why-should-i-use-it
// https://www.bfilipek.com/2020/08/pmr-dbg.html

// Copy following part into http://quick-bench.com
// http://quick-bench.com/IBMiNRYcqI3N82mJdeTYu9pPgho
// %<------------------------------------------------

#include <benchmark/benchmark.h>
#include <list>
#include <vector>

#if defined __has_include
#if __has_include(<memory_resource>)
#define HAS_PMR
#endif
#endif

#ifdef HAS_PMR
#include <memory_resource>

static void PMRList(benchmark::State &state) {
  for (auto _ : state) {
    std::byte stackBuf[2048];
    std::pmr::monotonic_buffer_resource rsrc(stackBuf, sizeof stackBuf);
    std::pmr::list<int> listOfThings{
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        &rsrc};
  }
}

BENCHMARK(PMRList);

static void PMRVector(benchmark::State &state) {
  for (auto _ : state) {
    std::byte stackBuf[2048];
    std::pmr::monotonic_buffer_resource rsrc(stackBuf, sizeof stackBuf);
    std::pmr::vector<int> listOfThings{
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19},
        &rsrc};
  }
}

BENCHMARK(PMRVector);

#endif /* HAS_MPR */

static void standardList(benchmark::State &state) {
  for (auto _ : state) {
    std::list<int> listOfThings{
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}};
  }
}

BENCHMARK(standardList);

static void standardVector(benchmark::State &state) {
  for (auto _ : state) {
    std::vector<int> listOfThings{
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}};
  }
}

BENCHMARK(standardVector);

BENCHMARK_MAIN();