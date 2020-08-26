#include <vector>
//#region [Declarations]
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
#define INFO_HEADER()                                                           \
  std::cout << std::setw(4) << "" << std::setw(9) << ".size()" << std::setw(13) \
            << ".capacity()"                                                    \
            << "  content\n";
#define INFO(v) info(v, #v)

template <typename T> void info(const std::vector<T> &v, const std::string &v_name) {
  std::cout << std::setw(4) << v_name << std::setw(9) << v.size() << std::setw(13)
            << v.capacity() << "  ";
  std::ostream_iterator<int> out_it(std::cout, " ");
  std::copy(v.begin(), v.end(), out_it);
  std::cout << "\n";
}
//#endregion

int main() {
  std::array<int, 5> cpp_array = {{1, 2, 3, 4, 5}}; /* quelques données de références */

  // Diverses constructions similaires de std::vector
  // clang-format off
  INFO_HEADER();
  std::vector<int> v1{1, 2, 3, 4, 5};                           INFO(v1);
  std::vector<int> v2{cpp_array.begin(), cpp_array.end()};      INFO(v2);

  // Constructions bien différentes
  std::vector<int> v3{1, 2}; /* {} => initialization list   */  INFO(v3);
  std::vector<int> v4(1, 2); /* () => (n,value) constructor */  INFO(v4);

  std::vector<int> v5; /* construction itérative */             INFO(v5);
  v5.push_back(1);       INFO(v5);       v5.push_back(2);       INFO(v5);
  v5.push_back(3);       INFO(v5);       v5.push_back(4);       INFO(v5);
  v5.push_back(5);       INFO(v5);

  std::vector<int> v6; v6.reserve(10);                          INFO(v6);
  v6.push_back(1); /* ajout classique d'un élément à la fin */  INFO(v6);
  v6.push_back(2);                                              INFO(v6);
  v6.emplace_back(3); /* emplace_back permet la construction */ INFO(v6);
  v6.emplace_back(4); /* in-situ de l'argument (C++11)       */ INFO(v6);
  v6.emplace_back(5); /* utile pour les objets complexes     */ INFO(v6);
  v6.shrink_to_fit();                                           INFO(v6);
  v6.pop_back();                                                INFO(v6);
  auto v7 = v5;            /* copie ajustée des données */      INFO(v7);
  auto v8 = std::move(v6); /* déplacement des données   */      INFO(v8);
                                                                INFO(v6);
  v8.clear(); /* on vide le container, mais pas l'allocation */ INFO(v8);
}