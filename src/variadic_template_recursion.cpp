//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif

#define DISPLAY(x)                                                       \
  {                                                                      \
    auto result = (x);                                                   \
    std::string_view msg = #x;                                           \
    msg.remove_prefix(1);                                                \
    msg.remove_suffix(1);                                                \
    std::cout << std::setw(20) << msg << " = " << std::setw(5) << result \
              << " (type=" << type<decltype(result)>() << ")\n";         \
  }
//#endregion

// TODO: imagine how to do it before opening the details
namespace details {
auto sum() /* deduced return type */ { return 0; }

template <typename T> // TODO: what happens without this function ?
auto sum(const T &head) /* deduced return type */ {
  return head;
}

template <typename Head, typename... Tail>
auto sum(const Head &head, Tail... tail) /* deduced return type */ {
  return head + sum(tail...); // TODO: could you do it without a deduced return type?
}
} // namespace details

// Variadic template function
template <typename... Ts> auto sum(Ts... args) { return details::sum(args...); }

int main() {
  DISPLAY((sum()));
  DISPLAY((sum(false)));
  DISPLAY((sum(1, 2.3, true)));
}