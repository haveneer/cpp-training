//#region [Declarations]
#include <iostream>
//#endregion

int main() {
  const int n = 2; // TODO predict the output when n=2, n=1 and n=0
  int i{};

  i = 0;
  while (i < n) {
    std::cout << "while loop; i = " << i << '\n';
    ++i;
    int n = 4; // local variable inside do block [do not interferer with outside] 
  }

  i = 0;
  do {
    std::cout << "do … while loop; i = " << i << '\n';
    ++i;
    int n = 4; // local variable inside do block [do not interferer with outside]
  } while (i < n);
}