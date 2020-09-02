#include <iostream>
#include <fstream>
#include <string>
#include <type_traits>
#include <vector>

int main() {
  std::cout << std::is_same<float, int>::value << "\n";
  std::cout << std::is_convertible<float, int>::value << "\n";
  std::cout << std::is_base_of<std::istream, std::ifstream>::value << "\n";
  std::cout << std::is_class<std::vector<int>>::value << "\n";
  std::cout << std::is_constructible<std::string, char *>::value << "\n";
  std::cout << std::is_polymorphic<std::istream>::value << "\n";
  std::cout << std::is_pointer<void *>::value << "\n";
  std::cout << std::is_trivially_copyable<int>::value << "\n";
}