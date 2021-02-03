//#region [declarations]
#include <iostream>
#include <string_view>
//#endregion

int main() {
  // Example from https://en.cppreference.com/w/cpp/string/basic_string_view
  constexpr std::string_view unicode[]{"▀▄─", "▄▀─", "▀─▄", "▄─▀"};

  for (int y{}, p{}; y != 6; ++y, p = ((p + 1) % 4)) {
    for (int x{}; x != 16; ++x)
      std::cout << unicode[p];
    std::cout << '\n';
  }
}