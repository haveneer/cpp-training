//#region [Prologue; NB: delimiter is an empty string]
#include <fstream>
#include <iostream>

// clang-format off
struct S {
  bool        v_bool;   char          v_char;
  int         v_int;    double        v_double;
  std::string v_string; unsigned long v_long;
};
// clang-format on

int main() {
  S s_out = {true, 'H', 42, 3.141592653589793238, "Hello", -1ul};
  const char *delim = "";
  {
    std::ofstream file("output.txt");
    // clang-format off
    file << s_out.v_bool   << delim << s_out.v_char   << delim
         << s_out.v_int    << delim << s_out.v_double << delim
         << s_out.v_string << delim << s_out.v_long   << delim;
    // clang-format on
  } // stream (file) is closed when object goes out of scope

  S s{};
  {
    std::ifstream file("output.txt");
    //#endregion
    file >> s.v_bool >> s.v_char >> s.v_int >> s.v_double >> s.v_string >> s.v_long;
    // good() returns true when everything is okay.
    std::cout << "good: " << file.good() << '\n';
    // bad() returns true when a fatal error has occurred.
    std::cout << "bad : " << file.bad() << '\n';
    // fail() returns true after an unsuccessful stream operation
    //        like an unexpected type of input being encountered.
    // NB: if (file) … <=> if (!file.fail()) 
    std::cout << "fail: " << file.fail() << '\n';
    // eof() returns true when the end of file is reached.
    std::cout << "eof : " << file.eof() << '\n';
    //#region [Epilogue]
  }
  // clang-format off
  std::cout <<   "bool   = " << s.v_bool   << "\nchar   = " << s.v_char
            << "\nint    = " << s.v_int    << "\ndouble = " << s.v_double
            << "\nstring = " << s.v_string << "\nlong   = " << s.v_long
            << '\n';
  // clang-format on
}
//#endregion