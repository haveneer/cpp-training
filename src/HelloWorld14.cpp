#include <iostream>

template<typename Arg, typename... Args>
void print(Arg&& arg, Args&& ...args){
  std::cout << std::forward<Arg>(arg);
  int _[]{0, (void(std::cout << ',' << std::forward<Args>(args)), 0)...};
  (void)_; // disable warning on unused variable 
  std::cout << std::endl;
}

int main() { // C++11 / C++14
  print("Hello", "world!");
}