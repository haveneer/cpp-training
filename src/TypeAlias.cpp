//#region [declarations]
#include <iostream>
#include <map>
#include <vector>
#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else
#include <typeinfo>
template <typename T> std::string type() { return typeid(T).name(); }
#endif
#define DISPLAY_TYPE(x) std::cout << #x << " : " << type<decltype(x)>() << std::endl
#define DISPLAY_TYPE_T(x, T) std::cout << #x << " : " << type<T>() << std::endl

void extended_main();
//#endregion

int main() {

  using Number = double; // equivalent to: typedef double Number;
  Number x{1.0}, y{1.0};
  Number z = x + y;

  DISPLAY_TYPE(z);

  //#region [Advanced]
  std::cout << "-- Advanced --\n";
  extended_main();
}

// /!\ template declaration are now allowed in blocks
template<typename T>
using V = std::vector<T>;

typedef std::map<std::string, std::vector<std::string>> MapString;
template<typename T1, typename T2> using Map = std::map<T1, std::vector<T2>>;

template<typename...>
using void_t = void;

void extended_main() {

  std::vector<int> tab{2};
  DISPLAY_TYPE(tab);

  Map<int, bool> mapIntBool;
  DISPLAY_TYPE(mapIntBool);

  DISPLAY_TYPE_T(void,void_t<>);
  //#endregion
}