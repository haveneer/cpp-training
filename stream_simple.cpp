#include <fstream>
#include <iostream>
// clang-format off

struct S {
  bool        v_bool;   char          v_char;
  int         v_int;    double        v_double;
  std::string v_string; unsigned long v_long;
};

int main() {
  S s_out = {true, 'H', 42, 3.141592653589793238, "Hello!", -1ul};
  const char *delim = " ";
  {
    std::ofstream file("output.txt");
    file << s_out.v_bool   << delim << s_out.v_char   << delim
         << s_out.v_int    << delim << s_out.v_double << delim
         << s_out.v_string << delim << s_out.v_long   << delim;
  } // stream (file) is closed when object goes out of scope

  S s{};
  {
    std::ifstream file("output.txt");
    file >> s.v_bool   >> s.v_char   >> s.v_int 
         >> s.v_double >> s.v_string >> s.v_long;
  } // stream (file) is closed when object goes out of scope

  std::cout <<   "bool   = " << s.v_bool   << "\nchar   = " << s.v_char
            << "\nint    = " << s.v_int    << "\ndouble = " << s.v_double
            << "\nstring = " << s.v_string << "\nlong   = " << s.v_long
            << '\n';
  // TODO what happens when delim is an empty string
  // TODO or/and v_string is "Hello World!" ?
  //#region [Then, this is the content of output.txt]
  // 1H423.14159Hello World!18446744073709551615
  //#endregion
}