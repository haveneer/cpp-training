//#region [declarations]
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on

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