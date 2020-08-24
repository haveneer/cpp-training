//#region [Declarations]
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
// clang-format off
//#endregion

struct S { int v_int; double v_double; std::string v_string; };

int main() {
  S s_out = {42, 3.141592653589793238, "Hello World!"};
  const char delim = '\0'; // use non ambiguous delimiter
  {
    std::ofstream file("output.txt");
    file << s_out.v_int << delim; 
    file << s_out.v_double << delim;
    file << s_out.v_string << delim;
  } // file close at end of scope

  S s{};
  std::ifstream file("output.txt");
  std::string chunk; // read chunk by chunk using delimiter
  if (!std::getline(file, chunk, delim)) std::abort(); // hard stop if fails
  {
    std::istringstream reader(chunk);
    reader >> s.v_int;
    assert(!reader.fail() && reader.eof()); // check if OK
  }
  if (!std::getline(file, chunk, delim)) std::abort(); // hard stop if fails
  {
    std::istringstream reader(chunk);
    reader >> s.v_double;
    assert(!reader.fail() && reader.eof()); // check if OK
  }
  if (!std::getline(file, chunk, delim)) std::abort(); // hard stop if fails
  { s.v_string = chunk; } // string => full token is what we want
  file >> chunk;
  assert(file.fail() && file.eof()); // nothing more to read

  std::cout << "int    = " << s.v_int << '\n' 
            << "double = " << s.v_double << '\n' // TODO: why not accurate ?
            << "string = " << s.v_string << '\n';
}