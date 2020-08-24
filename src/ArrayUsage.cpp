//#region [declarations]
#include <iostream>
#include <array>
//#endregion

int main() {
  // std::array<double, 5> constants = {{ 3.14, 2.718, 1.618, 1.414 }};
  double constants[5] = { 3.14, 2.718, 1.618, 1.414 };

  std::cout << "Pi is " << constants[0] << std::endl;
  constants[0] = 3.14159;
  std::cout << "Pi is " << constants[0] << std::endl;

  std::cout << "last value is " << constants[4] << std::endl;
  constants[4] = 1.732;
  std::cout << "last value is " << constants[4] << std::endl;

  // constants[5] = 0; // compile, run: silent overflow access error !!!

  //#region [sizeof and pointer]
  // The array only contains its values
  std::cout << "\nsizeof(constants) = " << sizeof(constants) << std::endl;
  std::cout << "sizeof(double) = " << sizeof(double) << std::endl;
  std::cout << "constants array size = " << sizeof(constants)/sizeof(double) << std::endl;

  double * p = constants;
  std::cout << "last value is " << *(p+4) << std::endl;
  //#endregion
}