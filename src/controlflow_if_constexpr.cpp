//#region [Declarations]
#include <iostream>
#include <type_traits>
#ifndef _MSC_VER
#define PRINTME() std::cout << __PRETTY_FUNCTION__ << '\n'
#else
#define PRINTME() std::cout << __FUNCSIG__ << '\n'
#endif

//#endregion

constexpr auto architecture_size() {
  // compile-tme evaluation
  if constexpr (sizeof(void *) == 4) {
    return 32;
  } else if constexpr (sizeof(void *) == 8) {
    return 64;
  } else {
    // even discarded statement must be well formed
    // error: cannot initialize variable of type 'int *' with an rvalue of type 'int'
    // int * p = 1;

    // but do not participate in function return type deduction
    return; // not an int value
  }
}

template <class T> struct dependent_false : std::false_type {};
template <typename T> T f() {
  if constexpr (std::is_arithmetic_v<T>) {
    return T{1};
  } else {
    static_assert(dependent_false<T>::value, "Must be arithmetic");
  }
}

int main(int argc, char **argv) {

  std::cout << "Running on " << architecture_size() << " bits arch\n";

  f<double>(); // only available for arithmetic types
  // f<int*>(); // error: static_assert failed due to requirement
  //            //        'dependent_false<void *>::value' "Must be arithmetic"
}