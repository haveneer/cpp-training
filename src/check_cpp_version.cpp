#include <iostream>

// more info, see https://sourceforge.net/p/predef/wiki/Compilers/

#define STRINGIFY(x) #x
#define VER_STRING(major, minor, patch) \
  STRINGIFY(major) "." STRINGIFY(minor) "." STRINGIFY(patch)

int main() {
#ifdef __GNUG__
#ifdef __clang__
#ifdef __apple_build_version__
  std::string cxx_compiler = "AppleClang";
#else
  std::string cxx_compiler = "Clang";
#endif
  std::string cxx_compiler_version =
      VER_STRING(__clang_major__, __clang_minor__, __clang_patchlevel__);
#else
  std::string cxx_compiler = "GCC";
  std::string cxx_compiler_version =
      VER_STRING(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#endif
#elif defined(_MSC_VER)
  std::string cxx_compiler = "MSVC";
  std::string cxx_compiler_version = STRINGIFY(_MSC_FULL_VER)
#else
  std::string cxx_compiler = "unknown compiler";
  std::string cxx_compiler_version = "";
#endif

  std::string cxx_standard = "undefined";
  switch (__cplusplus) {
  case 199711L:
    cxx_standard = "C++98";
    break;
  case 201103L:
    cxx_standard = "C++11";
    break;
  case 201402L:
    cxx_standard = "C++14";
    break;
  case 201703L:
    cxx_standard = "C++17";
    break;
  case 202002L:
    cxx_standard = "C++20";
    break;
  default:
    if (__cplusplus < 199711L)
      cxx_standard = "C++ pre-";
    else if (__cplusplus > 202002L)
      cxx_standard = "C++>20";
    else
      cxx_standard = "undefined";
  }

  std::cout << cxx_compiler << " " << cxx_compiler_version << " with "
            << cxx_standard << " standard\n";
}