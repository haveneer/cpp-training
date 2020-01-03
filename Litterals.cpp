//#region [declarations]
#include <chrono>
#include <complex>
#include <iostream>

template <class _Rep, class _Period>
std::ostream &operator<<(std::ostream &o,
                         const std::chrono::duration<_Rep, _Period> &d) {
  // using output_unit = std::chrono::seconds;
  using output_unit =
      std::chrono::duration<double>; // seconds with floating representation
  return o << std::chrono::duration_cast<output_unit>(d).count();
}

std::ostream &operator<<(std::ostream &o, const std::nullptr_t & p) {
  return o << static_cast<void *>(p);
}

int main() {
  // clang-format off
  //#endregion
  std::cout << nullptr                                                     << std::endl;
  std::cout << true                                                        << std::endl;
  std::cout << false                                                       << std::endl;
  std::cout << "Hello, world"                                              << std::endl;
  std::cout << "\\How\nare\tyou\x20?"                                      << std::endl;
  std::cout << u"\\How\nare\tyou\x20?" /* C++11 */                         << std::endl;
  std::cout << R"delim(Ce que vous voulez même des trucs "bizarres")delim" << std::endl;
  std::cout << 'W'                                                         << std::endl;
  std::cout << '+'                                                         << std::endl;
  std::cout << 314                                                         << std::endl;
  std::cout << 314U                                                        << std::endl;
  std::cout << 18446744073709550592ull /* C++11 */                         << std::endl;
  std::cout << 0b100111 /* C++14 */                                        << std::endl;
  std::cout << 012345670                                                   << std::endl;
  std::cout << 0x123DEF                                                    << std::endl;
  std::cout << 6'700'417                                                   << std::endl;
  std::cout << 3.1415                                                      << std::endl;
  std::cout << 3.1415f                                                     << std::endl;
  std::cout << 3.1415L                                                     << std::endl;
  std::cout << 1.23456789e-10                                              << std::endl;
  std::cout << 0xf.fp0f                                                    << std::endl;
  std::cout << 0x1p10L                                                     << std::endl;

  using namespace std::literals::complex_literals; // cf std::complex C++14
  std::cout << 5i                                                          << std::endl;
  std::cout << 5if                                                         << std::endl;

  using namespace std::chrono_literals; // cf std::chrono C++14
  std::cout << 5min                                                        << std::endl;
  std::cout << 5ms                                                         << std::endl;
  //#region [ending]
  // clang-format on
}
//#endregion
