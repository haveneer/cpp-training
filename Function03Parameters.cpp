//#region [Declarations]
#include <iostream>
//#endregion

// Function without parameter
int no_input1() { return 1; }

// Function without parameter (alternative syntax)
int no_input2(void) { return 2; }

// Function with a set of formal parameters
int simple_function(int a, const int b, int & c, bool /* no_name not used */)
{
  a += 1;
  // b += 2; // error: cannot assign to variable 'b' with const-qualified type 'const int'
  c += 4;
  return a+b+c;
}

int main() {
  std::cout << no_input1() << '\n';
  std::cout << no_input2(/* no void here ! */) << '\n';

  int x = 0; // the names of arguments are distinct
  int y = 0; // from the names of parameters
  int z = 0;
  // TODO: what is the display of the following lines ?
  std::cout << (x+y+z) << " vs " << simple_function(x,y,z,false) << '\n';
  std::cout << (x+y+z) << " vs " << simple_function(x,y,z,false) << '\n';
}