template <typename T> struct X {
  // function in template class
  static void f() {}
  // template function in template class
  template <typename U> static void fT() {}
  // non-template class in template class
  struct t {};
  // template class in template class
  template <typename U> struct tT {};
};

// calling a template instantiated template thing of instantiated template class
void f_has_f_of_Xi() { X<int>::f(); }
void f_has_fi_of_Xi() { X<int>::fT<int>(); }
void f_has_t_of_Xi() { X<int>::t _{}; }
void f_has_ti_of_Xi() { X<int>::tT<int> _{}; }

// calling a template instantiated thing of non-instantiated template class
template <typename T> void fT_has_f_of_Xi() { X<int>::f(); }
template <typename T> void fT_has_fi_of_Xi() { X<int>::fT<int>(); }
template <typename T> void fT_has_fT_of_Xi() { X<int>::fT<T>(); }
template <typename T> void fT_has_t_of_Xi() { X<int>::t _{}; }
template <typename T> void fT_has_ti_of_Xi() { X<int>::tT<int> _{}; }
template <typename T> void fT_has_tT_of_Xi() { X<int>::tT<T> _{}; }

// calling a template non-instantiated thing of non-instantiated template class
template <typename T> void fT_has_f_of_XT() { X<T>::f(); }
template <typename T> void fT_has_fi_of_XT() { X<T>::template fT<int>(); }
template <typename T> void fT_has_fT_of_XT() { X<T>::template fT<T>(); }
template <typename T> void fT_has_t_of_XT() { typename X<T>::t _{}; }
template <typename T> void fT_has_ti_of_XT() { typename X<T>::template tT<int> _{}; }
template <typename T> void fT_has_tT_of_XT() { typename X<T>::template tT<T> _{}; }

int main() {
  f_has_f_of_Xi();
  f_has_fi_of_Xi();
  f_has_t_of_Xi();
  f_has_ti_of_Xi();

  fT_has_f_of_Xi<int>();
  fT_has_fi_of_Xi<int>();
  fT_has_fT_of_Xi<int>();
  fT_has_t_of_Xi<int>();
  fT_has_ti_of_Xi<int>();
  fT_has_tT_of_Xi<int>();

  fT_has_f_of_XT<int>();
  fT_has_fi_of_XT<int>();
  fT_has_fT_of_XT<int>();
  fT_has_t_of_XT<int>();
  fT_has_ti_of_XT<int>();
  fT_has_tT_of_XT<int>();
}