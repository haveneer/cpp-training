//#region [Declarations]
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
// clang-format off
//#endregion

struct S { int v_int; double v_double; std::string v_string; };

int main() {
  S s_out = {42, 3.141592653589793238, "Hello World!"};
  {
    std::ofstream file("output.dat", std::ios::binary); // binary output
    file.write(reinterpret_cast<const char *>(&s_out.v_int), sizeof(int));
    file.write(reinterpret_cast<const char *>(&s_out.v_double), sizeof(double));
    // TODO Why following line is wrong ? (even it compiles)
    // file.write(reinterpret_cast<const char *>(&s_out.v_string), sizeof(std::string));
    // The right code should be like:
    const std::size_t string_size = s_out.v_string.size();
    file.write(reinterpret_cast<const char *>(&string_size), sizeof(std::size_t));
    file.write(reinterpret_cast<const char *>(s_out.v_string.c_str()), string_size);
  } // file close at end of scope

  S s{};
  std::ifstream file("output.dat", std::ios::binary); // binary intput
  file.read(reinterpret_cast<char *>(&s.v_int), sizeof(int));
  /* check */ assert(!file.fail() && !file.eof());
  file.read(reinterpret_cast<char *>(&s.v_double), sizeof(double));
  /* check */ assert(!file.fail() && !file.eof());
  std::size_t string_size = -1;
  file.read(reinterpret_cast<char *>(&string_size), sizeof(std::size_t));
  /* check */ assert(!file.fail() && !file.eof());
  s.v_string.resize(string_size);
  // file.read(s.v_string.data(), string_size); // direct read in .data() requires C++17
  file.read(&s.v_string[0], string_size); // work around for C++ <17
  /* check */ assert(!file.fail() && !file.eof()); // everything good up to here
  /* check */ assert(file.peek() == std::ifstream::traits_type::eof()); // the end

  //#region [Display read data]
  auto precision = std::cout.precision();
  std::cout.precision(20); 
  std::cout << std::left // for string, use alignment on the left with a width of 7
            << std::setw(7) << "int"    << "= " << s.v_int << '\n'
            << std::setw(7) << "double" << "= " << s.v_double << '\n'
            << std::setw(7) << "string" << "= " << s.v_string << '\n';
  std::cout.precision(precision);
  //#endregion
}