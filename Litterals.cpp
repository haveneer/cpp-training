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

#ifdef __clang__
std::ostream &operator<<(std::ostream &o, const std::nullptr_t &p) {
  return o << static_cast<void *>(p);
}
#endif

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#include <iomanip>
#define DISPLAY(obj)                                                           \
  {                                                                            \
    std::string type_string = type<decltype(obj)>();                           \
    std::cout << type_string << ":" << std::setw(70 - type_string.size())      \
              << #obj << " : " << (obj) << std::endl;                            \
  }

int main() {
  // clang-format off
  //#endregion
  DISPLAY( nullptr                                             ); /* C++11 */
  DISPLAY( true                                                );
  DISPLAY( false                                               );
  DISPLAY( "Hello, world"                                      );
  DISPLAY( "Hello\0world"                                      ); // cut at \0
  DISPLAY( "\\How\nare\tyou\x20?"                              );
  DISPLAY( u"\\How\nare\tyou\x20?"                             ); /* C++11 */
  DISPLAY( R"delim(Whatever even "stranges" things)delim"      ); /* C++11 */
  DISPLAY( 'W'                                                 );
  DISPLAY( '+'                                                 );
  DISPLAY( 314                                                 );
  DISPLAY( 314U                                                );
  DISPLAY( 18446744073709550592ull                             ); /* C++11 */
  DISPLAY( 0b100111                                            ); /* C++14 */
  DISPLAY( 012345670                                           );
  DISPLAY( 0x123DEF                                            );
  DISPLAY( 6'700'417                                           );
  DISPLAY( 3.1415 /* floating numbers are double by default */ );
  DISPLAY( 3.1415f                                             );
  DISPLAY( 3.1415L                                             );
  DISPLAY( 1.23456789e-10                                      );
  DISPLAY( 0xf.fp0f                                            );
  DISPLAY( 0x1p10L                                             );

  using namespace std::string_literals;
  DISPLAY( "Hello\0world"s /* ATTN: wrong HTML display */      ); /* C++ 14 */

  using namespace std::literals::complex_literals;
  DISPLAY( 5i                                                  ); /* C++14 */
  DISPLAY( 5if                                                 ); /* C++14 */

  using namespace std::chrono_literals;
  DISPLAY( 5min                                                ); /* C++14 */
  DISPLAY( 5ms                                                 ); /* C++14 */
  //#region [ending]
  // clang-format on
}
//#endregion