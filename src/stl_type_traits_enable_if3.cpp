//#region [Declarations]
#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
//#endregion

template <typename T,
          std::enable_if_t<(sizeof(T) < 32 &&
                            std::is_trivially_copy_constructible_v<T>)> * = nullptr>
std::string_view f(T t) {
  return "by copy";
}

template <typename T, std::enable_if_t<(
                          !(sizeof(T) < 32 &&
                            std::is_trivially_copy_constructible_v<T>))> * = nullptr>
std::string_view f(const T &t) {
  return "by const reference";
}

struct X {
  double v;
};

struct Y {
  Y() {}
  Y(const Y &y) : v(y.v) {}
  // Y(const Y &y) = default; // TODO: is there a difference ?
  double v;
};

#define DISPLAY(v) std::cout << std::setw(24) << #v << " : " << f(v) << '\n';

int main() {
  DISPLAY((1));
  DISPLAY((std::array<int, 4>{}));
  DISPLAY((std::array<int, 16>{}));
  DISPLAY((std::string_view{}));
  DISPLAY((std::string{}));
  DISPLAY((X{}));
  DISPLAY((Y{}));
}