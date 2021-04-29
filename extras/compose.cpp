#include <iostream>

template <typename F, typename G> struct compose {
  compose(F ff, G gg) : f(ff), g(gg) {}

  template <typename... Args>
  auto operator()(Args &&...args) -> decltype(std::declval<F>()(
      std::declval<G>()(std::forward<Args>(args)...))) {
    return f(g(std::forward<Args>(args)...));
  }

  F f;
  G g;
};

template <typename F, typename G> compose<F, G> compose11(F f, G g) {
  return compose<F, G>(f, g);
}

template <typename F, typename G> auto compose14(F f, G g) {
  auto that = [f, g](auto... args) { return f(g(args...)); };
  return that;
}

// C++17 CTAD
template <typename F, typename G> compose(F f, G g) -> compose<F, G>;

int f(double x) { return 10 * static_cast<int>(x); }
double g(int a, int b, int c) { return static_cast<double>(c) / (a + b); }

int main() {
  auto fg = compose(f, g);
  auto ffg = compose(f, fg);

  std::cout << fg(1, 2, 14) << "\n";
  std::cout << ffg(1, 2, 14) << "\n";
}