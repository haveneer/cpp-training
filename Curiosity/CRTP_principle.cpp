#include <iostream>

/* Static polymorphism */
template <class DerivedT>
struct Base
{
  void interface()
  {
    // ...
    static_cast<DerivedT*>(this)->implementation();
    // ...
  }
};

// Curiously recurring template pattern (CRTP)
struct Derived : public Base<Derived>
{
  void implementation()
  {
    std:: cout << "This is " << typeid(*this).name() << std::endl;
  }
};

template<typename T>
void foo(Base<T> & b) { b.interface(); } // static dispatch

int main() {
  Derived d;
  foo(d);
}