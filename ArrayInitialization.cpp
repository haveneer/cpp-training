//#region [declarations]
#include <array>
#include <iostream>
#include <valarray>
#include <vector>

#define DEBUG_ARRAY(tab) \
  std::cout << #tab << ": "; \
  for(auto i : tab) { std::cout << i << " "; } \
  std::cout << std::endl;
//#endregion

int main() {
  int ta1[5]; // non-initialized data
  int ta2[5] {}; // filled with 0
  int ta3[5] { 1, 2, 3 }; // fill missing values with 0
  int ta4[ ] { 1, 2, 3, 4, 5 }; // deduce size
  // int ta5[5] { 1, 2, 3, 4, 5, 6 }; // ERROR: too many values
  int n = 3;
  int ta6[n]; // C99 style : fill with non-initialized data

  std::array<int, 5> tb1; // fill with non-initialized data
  std::array<int, 5> tb2 {}; // fill with 0
  std::array<int, 5> tb3 { { 1, 2, 3 } }; // fill missing values with 0
  std::array<int, 5> tb4 { { 1, 2, 3, 4, 5 } };
  // std::array<int,5> tb5 = { 1, 2, 3, 4, 5, 6 }; // ERROR: too many values

  std::vector<int> tc0; // empty vector
  std::vector<int> tc2 ( 5 ); // /!\ vector of size 5
  std::vector<int> tcX { 5 }; // /!\ vector with value 5
  std::vector<int> tc3 { 1, 2, 3 }; // automatic fit
  std::vector<int> tc4 { 1, 2, 3, 4, 5 }; // automatic fit

//#region [display array contents]
  DEBUG_ARRAY(ta1);
  DEBUG_ARRAY(ta2);
  DEBUG_ARRAY(ta3);
  DEBUG_ARRAY(ta4);
  // DEBUG_ARRAY(ta5);
  DEBUG_ARRAY(ta6);
  DEBUG_ARRAY(tb1);
  DEBUG_ARRAY(tb2);
  DEBUG_ARRAY(tb3);
  DEBUG_ARRAY(tb4);
  DEBUG_ARRAY(tc0);
  DEBUG_ARRAY(tc2);
  DEBUG_ARRAY(tcX);
  DEBUG_ARRAY(tc3);
  DEBUG_ARRAY(tc4);
//#endregion
}