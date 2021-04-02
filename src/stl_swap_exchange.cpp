//#region [declarations]
#include <atomic>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cassert>

class Counter {
public:
  Counter() {
    assert(m_instance == nullptr);
    m_instance = this;
  }
  // ~Counter() { display("dtor"); }
  static void add(std::string location) {
    assert(m_instance != nullptr);
    m_instance->m_counters[location]++;
  }
  static void display(const std::string &message) {
    assert(m_instance != nullptr);
    auto &counters = m_instance->m_counters;
    std::cout << "--- " << message << '\n';
    std::vector<std::pair<std::string, int>> summary;
    summary.reserve(counters.size());
    std::copy(counters.begin(), counters.end(), std::back_inserter(summary));
    std::sort(summary.begin(), summary.end(),
              [](auto &&a, auto &&b) { return a.second > b.second; });
    for (auto [k, v] : summary) {
      std::cout << std::setw(30) << k << " : " << v << '\n';
    }
    if (counters.empty())
      std::puts("Nothing new");
    counters.clear();
  }

private:
  inline static Counter *m_instance = nullptr;
  std::unordered_map<std::string, int> m_counters;
} _counter_;

#ifndef _MSC_VER
#define COUNT_ME() Counter::add(__PRETTY_FUNCTION__)
#else
#define COUNT_ME() Counter::add(__FUNCSIG__)
#endif
//#endregion

struct X {
  // struct to debug what happens (using rule of 5)
  X() { COUNT_ME(); }
  X(const X &x) { COUNT_ME(); }
  X(X &&x) { COUNT_ME(); }
  ~X() { COUNT_ME(); }

  void operator=(const X &) { COUNT_ME(); }
  void operator=(X &&) { COUNT_ME(); }
};

template <typename T> void trivial_swap(T &a, T &b) {
  T c = b;
  b = a;
  a = c;
}

template <typename T> void better_swap(T &a, T &b) {
  T c = std::move(b);
  b = std::move(a);
  a = std::move(c);
}

int main() {
  {
    X x1, x2;
    std::swap(x1, x2);
    Counter::display("std::swap two elements");
    std::vector<X> a(7), b(11);
    Counter::display("Build two vectors");
    std::swap(a, b);
    Counter::display("std::swap vectors");
    trivial_swap(a, b);
    Counter::display("By hand trivial swap");
    better_swap(a, b);
    Counter::display("By hand better swap");
  }
  // -------------------------------------------
  {
    std::vector<int> a = {1, 2, 3, 4};
    auto b = std::exchange(a, {1, 2, 3, 4});
  }
  // --------------------------
  { // And its atomic brother's
    std::atomic<int> a = 1;
    int b = std::atomic_exchange(&a, 2);
  }
}