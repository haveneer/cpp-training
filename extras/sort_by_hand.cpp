//#region [Collapse all]
#include <iostream>
#include <vector>
//#endregion

template <typename LessComparator>
void sort(std::vector<int> &t, const LessComparator &compare) {
  const size_t n = t.size();
  for (size_t i = n; i > 1; i--) {
    for (size_t j = 1; j < i; j++) {
      if (compare(t[j], t[j - 1])) { /* swap if < */
        std::swap(t[j], t[j - 1]);
      }
    }
  }
}

int main() {
  std::vector<int> data(20);

  // Local print function
  auto print = [&data](const char *msg) {
    std::cout << msg << "\n\t";
    for (auto &&x : data)
      std::cout << x << " ";
    std::cout << "\n";
  };

  // Initialisation
  for (auto &x : data) {
    x = rand() % (10 * data.size());
  }

  print("Before:");

  // Ascending ordering
  auto less_compare = [](int a, int b) -> bool { return a < b; };
  sort(data, less_compare);
  print("After < comparator:");

  // Descending ordering
  sort(data, [](int a, int b) -> bool { return a > b; });
  print("After > comparator:");

  // TODO: what ordering is it ?
  sort(data, [](int a, int b) -> bool {
    const bool is_same_parity = (a + b) % 2 == 0;
    return (is_same_parity) ? a < b : a % 2 == 0;
  });
  print("After parity comparator:");
}