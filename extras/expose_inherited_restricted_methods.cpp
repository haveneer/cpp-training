//#region [Collapse all]
#include <iostream>
#include <vector>
//#endregion

template <typename T> struct Block : private std::vector<T> {
  using parent = std::vector<T>;

  // using parent::vector; // error: confusion between vector type and ctor
  using parent::template vector<T>::vector; // template keyword avoids ambiguity
  using parent::size;                       //
  using parent::operator[];
};
//#region [See also link]
// Using 'template' keyword is like using 'typename' to suppress ambiguity on types
// https://en.cppreference.com/w/cpp/language/dependent_name#The_template_disambiguator_for_dependent_names
//#endregion

int main() {
  Block<double> f{1, 2, 3, 4};
  std::cout << f.size() << "\n";
}