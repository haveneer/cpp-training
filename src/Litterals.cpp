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

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

#include <iomanip>
#define DISPLAY(obj)                                                           \
  {                                                                            \
    std::string type_string = type<decltype(obj)>();                           \
    std::cout << type_string << ":" << std::setw(70 - type_string.size())      \
              << #obj << " : " << (obj) << std::endl;                            \
  }

int main() {
  
  // clang-format off
  // DISPLAY( nullptr                                             ); /* C++11 */
  //#endregion
  DISPLAY( true                                                );
  DISPLAY( false                                               );
  DISPLAY( "Hello, world"                                      );
  DISPLAY( "Hello\0world"                                      ); // cut at \0
  DISPLAY( "\\How\nare\tyou\x20?"                              );
  DISPLAY( u"\\How\nare\tyou\x20?"                             ); /* C++11 */
  DISPLAY( R"delim(Whatever even "strange" things)delim"       ); /* C++11 */
  DISPLAY( 'W'                                                 );
  DISPLAY( '+'                                                 );
  DISPLAY( 314                                                 );
  DISPLAY( 314U                                                );
  DISPLAY( 18446744073709550592ull                             ); /* C++11 */
  DISPLAY( 1'844'674'407'370'955'0592ull                       ); /* C++14 */
  DISPLAY( 0b100111                                            ); /* C++14 */
  DISPLAY( 012345670                                           );
  DISPLAY( 0x123DEF                                            );
  DISPLAY( 6'700'417                                           ); /* C++14 */
  DISPLAY( 3.1415 /* floating numbers are double by default */ );
  DISPLAY( 3.1415f                                             );
  DISPLAY( 3.1415L                                             );
  DISPLAY( 1.23456789e-10                                      );
  DISPLAY( 0xf.fp0f                                            ); /* C++17 */
  DISPLAY( 0x1p10L                                             );

  using namespace std::string_literals;
  DISPLAY( "Hello\0world"s /* ATTN: wrong HTML display */      ); /* C++14 */

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