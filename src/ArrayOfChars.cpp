//#region [declarations]
#include <array>
#include <cstring>
#include <iostream>
//#endregion

int main() {
  char hello_world1[] = {'H', 'e', 'l', 'l', 'o', ' ',
                         'w', 'o', 'r', 'l', 'd', '1', '\0'};
  std::cout << hello_world1 << ":\n";
  for (auto c : hello_world1)
    std::cout << "'" << c << "', ";

  char hello_world2[] = "Hello world2";
  std::cout << "\n" << hello_world2 << ":\n";
  for (auto c : hello_world2)
    std::cout << "'" << c << "', ";

  std::cout << "\n\nDo not confuse the array size with the string length\n";
  std::cout << "array size: " << sizeof(hello_world1) << std::endl;
  std::cout << "string length: " << std::strlen(hello_world1) << std::endl;

  //#region [useless 0 vs mandatory 0]
  char x = 0; // or ' ';
  char hello_world3[] = {'H', 'e', 'l', 'l', 'o', x,
                         'w', 'o', 'r', 'l', 'd', '3', x};
  std::cout << "\n" << hello_world3 << ":\n";
  for (auto c : hello_world3)
    std::cout << "'" << c << "', ";
  //#endregion

  //#region [std::array of chars]
  std::array<char, 20> hello_world4 = {{ 'H', 'e', 'l', 'l', 'o', ' ',
                                         'w', 'o', 'r', 'l', 'd', '4', '\0'}};
  std::cout << "\n\n" << hello_world4.data() << ":\n";
  for (auto c : hello_world4)
    std::cout << "'" << c << "', ";
  //#endregion
}