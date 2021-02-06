//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <string_view>
#include <type_traits>

struct X {
} x;
//#endregion

struct T {
  std::string_view type;

  template <            // use a dummy type (int) defined if predicate is true
      typename Integer, // with a default value to be silently optional
      std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
  explicit T(Integer) : type("integral number") {}

  template <             //
      typename Floating, // use default associated type (void) with default value
      typename std::enable_if<std::is_floating_point_v<Floating>>::type * = nullptr>
  explicit T(Floating) : type("floating point number") {}

  template <          // use default associated type (void) with default value
      typename Other, // (use _t helper in place of ::type)
      typename std::enable_if_t<(!std::is_floating_point_v<Other> &&
                                 !std::is_integral_v<Other>)> * = nullptr> // void *
  explicit T(Other) : type("not a number") {}
};

#define DISPLAY(v) std::cout << std::setw(6) << #v << " is " << T{v}.type << '\n';

int main() {
  DISPLAY('c');
  DISPLAY(1.f);
  DISPLAY(x);
}
