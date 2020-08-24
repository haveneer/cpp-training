#include <array>
#include <iostream>

// Fonctions prenant un tableau de 5 int en paramètres
// et retournant un tableau de 5 int ...

int (&f03(const int (&arr)[5]))[5] {
  static int that[5]; /* static pour éviter la copie d'une variable locale */
  for (std::size_t i = 0; i < 5; i++)
    that[i] += arr[i] + i;
  return that;
}

std::array<int, 5> f11(std::array<int, 5> const &arr) {
  std::array<int, 5> that{arr};
  for (std::size_t i = 0; i < that.size(); i++)
    that[i] += i;
  return that;
}

int main() {
  auto r03 = f03({0, 1, 2, 3, /* missing one */});
  std::cout << "f03({1,2,3,4) -> {";
  for (std::size_t i = 0; i < 5; ++i) {
    std::cout << " " << r03[i];
  }
  std::cout << " }\n";

  auto r11 = f11({0, 1, 2, 3, /* missing one */});
  std::cout << "f11({1,2,3,4) -> {";
  for (auto x : r11) {
    std::cout << " " << x;
  }
  std::cout << " }\n";
}