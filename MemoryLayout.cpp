//#region [declarations]
#include <iostream>
//#endregion
double bss_var2; /* Uninitialized variable stored in bss filled with 0 */
short bss_var1; /* idem: what happens if bss_var1 is moved before bss_var2 ?? */

char data_var[4] = "ABC"; /* Initialized variable stored in data */

int main() {
  int auto_var = 1; /* Automatic variable allocated in stack */

  static char static_var = 'Z'; /* Initialized variable stored in data */

  // What is the result ?? (NB: may change when code optimization is enabled)
  std::cout << "result is: " << data_var[4] << std::endl;

  //#region [dynamic allocation]
#if (0)
  /* Dynamic memory allocation in heap */
  short * heap_var = new short[10000];
  delete[] heap_var;
#endif
  //#endregion
}