//#region [Declarations]
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

static struct Init {
  Init() { std::cout.flags(std::ostream::boolalpha); }
} init;

#define DISPLAY(v) std::cout << std::setw(60) << #v << " : " << v << '\n';

//#endregion

#include <type_traits>

enum class X : char { Yes, No };

struct Y {
  int i;
  char c;
};

int main() {
  DISPLAY((std::is_integral<char>::value));
  DISPLAY((std::is_arithmetic<X>::value));
  DISPLAY((std::is_aggregate<Y>::value));
  DISPLAY((std::is_constructible<Y, int>::value)); // constructible with not all args
  DISPLAY((std::is_constructible<std::string, char *>::value));
  DISPLAY((std::is_same<float, int>::value));
  DISPLAY((std::is_same_v<std::remove_const_t<const int &>, int &>)); // C++14 helper
  DISPLAY((std::is_same_v<std::decay_t<const int &>, int>));

  DISPLAY((std::is_convertible_v<float, int>));
  DISPLAY((std::is_base_of_v<std::istream, std::ifstream>));
  DISPLAY((std::is_class_v<std::vector<int>>));
  DISPLAY((std::is_polymorphic<std::istream>::value)); // has virtual method
  DISPLAY((std::is_pointer_v<void *>));
  DISPLAY((std::is_trivially_copyable_v<int>));
  
}