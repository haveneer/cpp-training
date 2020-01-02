//#region [declarations]
#include <cassert>
#include <iostream>
//#endregion

int main() {
  int tab1[2][3][4] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                       0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                       0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
  // clang-format off
  int tab2[][3][4] = { { {0x00, 0x01, 0x02, 0x03},
                         {0x04, 0x05, 0x06, 0x07},
                         {0x08, 0x09, 0x0A, 0x0B} },
                       { {0x0C, 0x0D, 0x0E, 0x0F},
                         {0x10, 0x11, 0x12, 0x13},
                         {0x14, 0x15, 0x16, 0x17} } };
  // clang-format on

  for (int i = 0; i < 2; ++i)
    for (int j = 0; j < 3; ++j)
      for (int k = 0; k < 4; ++k) {
        assert(tab1[i][j][k] == tab2[i][j][k]);
        std::cout << tab1[i][j][k] << " ";
      }

  //#region [overflow example: what is tab[0][3][1] ?]
  if (tab1[0][3][1] == tab1[1][0][1])
    std::cout << "\ntab[0][3][1] is tab[1][0][1]" << std::endl;
  //#endregion
}