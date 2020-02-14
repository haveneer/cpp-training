#include <cstddef>

struct static_only {
  void *operator new(std::size_t) = delete;
};

struct widget : static_only {};

int main() {
  widget w;
  // widget *pw = new widget; // dynamic allocation is forbidden
}
