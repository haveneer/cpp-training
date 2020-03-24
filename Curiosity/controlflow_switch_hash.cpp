//#region [Prologue]
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>

// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
constexpr size_t fnv_hash(const char *input) {
  size_t hash = sizeof(size_t) == 8 ? 0xcbf29ce484222325 : 0x811c9dc5;
  const size_t prime = sizeof(size_t) == 8 ? 0x00000100000001b3 : 0x01000193;

  while (*input) {
    hash ^= static_cast<size_t>(*input);
    hash *= prime;
    ++input;
  }

  return hash;
}

constexpr size_t operator"" _hash(const char *s, std::size_t) { return fnv_hash(s); }

int f1() { return 1; }
int f2() { return 2; }
int f3() { return 3; }

int main(int argc, char **argv) {
  int r;

  std::array<const char *, 12> values{{"undef", "nothing", "stocking", "floor",
                                       "suit", "turkey", "limit", "measure",
                                       "goldfish", "west", "talk"}};

  const char *v = values[rand() % values.size()];
  std::cout << "v = " << v << " [" << std::hex << fnv_hash(v) << std::dec << "]\n";

  // clang-format off
  //#endregion
  switch (fnv_hash(v)) {
  case "stocking"_hash: r=f1(); break;
  case "floor"_hash:    r=f2(); break;
  case "suit"_hash:     r=f2(); break;
  case "turkey"_hash:   r=f1(); break;
  case "limit"_hash:    r=f2(); break;
  case "measure"_hash:  r=f1(); break;
  case "goldfish"_hash: r=f2(); break;
  case "west"_hash:     r=f1(); break;
  case "talk"_hash:     r=f2(); break;
  default: r=f3();
  }
//#region [Epilogue]
  // clang-format on

  std::cout << "r = " << r << '\n';
  return 0;
}
//#endregion