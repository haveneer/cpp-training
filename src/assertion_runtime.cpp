#include <cassert>

int sum(const int *tab, int size) {
  // classical assertion
  assert(tab != nullptr);
  // HINT: extra string message using comma operator
  // requires extra () since assert only accepts one arg
  assert(("size must be positive", size > 0));
  int result = 0;
  for (int i = 0; i < size; ++i)
    result += tab[i];
  return result;
}

int main() {
  int v[5] = {1, 2, 3, 4, 5};
  assert(sum(v, 5) == 15);
}