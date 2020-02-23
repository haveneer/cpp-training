//#region [Declarations]
#include <iostream>
#include <string>
//#endregion

int main()
{
  int a{42};
  int a_moved{std::move(a)}; // POD move is a copy
  std::cout << "a       = " << a << '\n';
  std::cout << "a_moved = " << a_moved << '\n';

  std::string s{"Hello World"};
  std::string s_moved{std::move(s)};
  std::cout << "s       = " << s << '\n'; // s will have an undetermined state
  std::cout << "s_moved = " << s_moved << '\n';
}