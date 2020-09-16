//#region [Collapse all]
#include <iostream>
int main() {
  int * p = new int[10];
  int * q = p;
  for(int i=0;i<=10;++i) {
    p[i] = 0;
    std::cout << p[i] << "\n";
  }
  delete[] p;
  delete[] q;
}
//#endregion