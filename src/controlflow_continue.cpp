//#region [Declarations]
#include <iostream>
//#endregion

int main() {
  for (int i = 0; i < 3; ++i) {
    std::cout << "#" << i << " : ";
    for (int j = 0; j < 5; ++j) {
      std::cout << " < " << j << ' ';
      if (j == 2)
        continue; // TODO and with a break ?
      std::cout << "> ";
    }
    std::cout << '\n';
  }
}