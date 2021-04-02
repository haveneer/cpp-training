#include <iostream>

// Example with outside class definition of begin/end functions
// In that cas, they have also different types (requires C++17)

template <typename State, typename Function, typename StopCondition>
struct Generator {
  const State seed;
  const Function function;
  const StopCondition stop_condition;
};

// C++17 CTAD
template <typename State, typename Function, typename StopCondition>
Generator(State seed, Function function, StopCondition stop_condition)
    -> Generator<State, Function, StopCondition>;

template <typename State, typename Function> struct Item {
  State operator*() const { return value; }
  void operator++() { value = function(value); }
  State value;
  const Function function;
};

template <typename StopCondition> struct Terminator {
  const StopCondition stop_condition;
};

template <typename State, typename Function, typename StopCondition>
bool operator!=(const Item<State, Function> &item,
                const Terminator<StopCondition> &terminator) {
  return !terminator.stop_condition(item.value);
}

template <typename State, typename Function, typename StopCondition>
Item<State, Function> begin(const Generator<State, Function, StopCondition> &c) {
  return {c.seed, c.function};
}

template <typename State, typename Function, typename StopCondition>
Terminator<StopCondition> end(const Generator<State, Function, StopCondition> &c) {
  return {c.stop_condition};
}

int main() {
  auto syracuse = [](int n) -> int {
    if (n % 2 == 0)
      return n / 2;
    else
      return 3 * n + 1;
  };

  for (auto x : Generator{10, syracuse, [](int n) { return n == 1; }}) {
    std::cout << x << "\n";
  }
}