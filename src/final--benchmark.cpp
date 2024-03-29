struct A {
  virtual int f() = 0;
};

struct B : A {
  int f() final override { return 1; }
};

struct C : A {
  int f() override { return 1; }
};

struct D : C {                   // not used; for illustration only
  int f() override { return 1; } // does not change optimizer behavior
};

int foo(B &b) { return b.f(); }

int bar(C &c) { return c.f(); }

//#region [Benchmark]
#include <benchmark/benchmark.h>

static void WithoutFinal(benchmark::State &state) {
  C *c = new C{}; // better optimization if stack allocated;
  int v = 0;      // here worst case
  for (auto _ : state) {
    v += bar(*c);
  }
  benchmark::DoNotOptimize(v);
}
// Register the function as a benchmark
BENCHMARK(WithoutFinal);

static void WithFinal(benchmark::State &state) {
  B *b = new B{}; // better optimization if stack allocated;
  int v = 0;      // here worst case
  for (auto _ : state) {
    v += foo(*b);
  }
  benchmark::DoNotOptimize(v);
}
// Register the function as a benchmark
BENCHMARK(WithFinal);

BENCHMARK_MAIN();
//#endregion