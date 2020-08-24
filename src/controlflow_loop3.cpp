//#region [Declarations]
#include <iostream>
//#endregion

int main() {
  const int n = 2; // TODO predict the output when n=2, n=1 and n=0

  {
    int i = 0;
    do {
      std::cout << "do … while loop; i = " << i << '\n';
      ++i;
    } while (i < n);
  }

  {
    int i = 0;
    for (bool test = true; test; test = i < n) {
      std::cout << "for loop; i = " << i << '\n';
      ++i;
    }
  }
}