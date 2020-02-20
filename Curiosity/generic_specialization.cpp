//#region [Collapse all]
#include <iostream>
#include <typeinfo>

/* Déclarations et spécialisations simples */
template <typename T> struct A {
  enum { value = sizeof(T) };
};
template <> struct A<void *> {
  enum { value = 0 };
};

template <int i> int f(int x) { return x + i; }
template <> int f<0>(int x) { return x; }

// Spécialisation
template <typename U, typename V> struct B {
  enum { value = 0 };
};
template <typename W> struct B<W, double> {
  enum { value = 2 };
};
template <typename W> struct B<W, W> {
  enum { value = 4 };
};

/* Quelques instanciations */
int main() {
  std::cout << "A<int> : " << A<int>::value << '\n';
  std::cout << "A<void*> : " << A<void *>::value << '\n';
  std::cout << "typeid(A<int>).name() : " << typeid(A<int>).name() << '\n';

  std::cout << "f<1>(1) : " << f<1>(1) << '\n';
  std::cout << "f<0>(1) : " << f<0>(1) << '\n';

  std::cout << "B<int,double> : " << B<int, double>::value << '\n';
  std::cout << "B<int,int>  : " << B<int, int>::value << '\n';
}
//#endregion