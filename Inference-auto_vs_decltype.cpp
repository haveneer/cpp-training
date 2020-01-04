//#region [declarations]
#include <iostream>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
#define DISPLAY_TYPE(x) std::cout << #x << " : " << type<decltype(x)>() << std::endl
#define DISPLAY_TYPE_T(x, T) std::cout << #x << " : " << type<T>() << std::endl
//#endregion

int main() {
  int a = 1;
  int & b = a;
  const int & c = a;

  auto vb_auto = b;
  auto vc_auto = c;
  decltype(b) vb_decltype = b;
  decltype(c) vc_decltype = c;

  DISPLAY_TYPE(vb_auto);
  DISPLAY_TYPE(vc_auto);
  DISPLAY_TYPE(vb_decltype);
  DISPLAY_TYPE(vc_decltype);
}