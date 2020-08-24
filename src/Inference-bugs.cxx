//#region [declarations]
#include <iostream>
#include <vector>
//#endregion

int main() {
  const int a = 1u; // silent conversion
  double *p = &a;
  char &c = a;
  const double & d = a; // silent conversion
  double * const q = &a;

  //#region [Advanced]
  // clang-format off
  const std::vector<char> tab{'A', 'B', 'C', 'D'};
  for (std::vector<char>::iterator it = tab.begin(),
                                  end = tab.end();
       it != end; ++it) {
    const int val = *it + a;
    std::cout << val << std::endl;
  }
  // clang-format on
  //#endregion
}