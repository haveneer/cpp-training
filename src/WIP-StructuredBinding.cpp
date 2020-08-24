//#region [declarations]
#include <iostream>
#include <tuple>
//#endregion

int main() {

  // Structured Bindings

  using Number = double;

  int e=1;
  int f=2;

  auto [c,d] = std::tie(e,f);

  int a[2] = {1,2};

  auto [x,y] = a; // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
  auto& [xr, yr] = a; // xr refers to a[0], yr refers to a[1]


  //#region []
  //#endregion
}