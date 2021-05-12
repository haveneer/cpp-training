struct Base final {
  int i;
}; // Base class: a final class, no virtual dtor

// struct DerivedBase : public Base {}; // error: cannot override final struct

class BaseClass {
public:
  virtual ~BaseClass() {}

public:
  virtual int f(int) { return 0; }    // Pure virtual interface are always better
  virtual int g() final { return 0; } // HINT: these non virtual methods are for
  virtual int h() { return 0; }       // pedagogic purpose ONLY

protected:
  void hidden_internal_method() {}
};

class DerivedClass final : public BaseClass {
public:
  DerivedClass() = default;
  int f(double) /* override */ { return 1; } // does not override any method of Class
  // int g() { return 1; }                   // error: cannot override final method
  int h() override { return 0; } //          // ok overrides BaseClass::h

public:
  using BaseClass::hidden_internal_method; // now public !
};

auto call_on_derived(DerivedClass &c) { // since DerivedClass is 'final',
                                        // no other derived class can be used
  c.hidden_internal_method();           // as parameter => the compiler can resolve
  return c.h();                         // virtual call at compile time: OPTIMIZATION
}

int main() {
  DerivedClass c;
  call_on_derived(c);
}