//#region [declarations]
#include <iostream>
//#endregion

#define COMPILE_TIME_VALUE 1

constexpr bool test(int i) { return (3 * i + 1) % 2 == 0; }

constexpr bool strings_equal(const char *a, const char *b) {
  return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1));
}

constexpr auto do_something() { return "something"; }
constexpr auto do_something_else() { return "something else"; }

template <bool b> auto template_selector() {} // template specialization or enable_if
template <> auto template_selector<true>() { return do_something(); }
template <> auto template_selector<false>() { return do_something_else(); }

int main() {
  // Runtime
  if (test(COMPILE_TIME_VALUE)) {
    do_something();
  } else {
    do_something_else();
  }

  // Compile time
  if constexpr (test(COMPILE_TIME_VALUE)) {
    do_something();
  } else {
    do_something_else();
  }

  constexpr auto constexpr_selector = [](bool b) constexpr {
    if (b) // if inside a constexpr
      return do_something();
    else // constexpr code only
      return do_something_else();
  };
  constexpr_selector(test(COMPILE_TIME_VALUE)); // local but constexpr code only

  static_assert(
      strings_equal(constexpr_selector(test(COMPILE_TIME_VALUE)), "something"));

  template_selector<test(COMPILE_TIME_VALUE)>(); // what you want but bad locality
}