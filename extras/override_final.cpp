struct Base final {
  int i;
}; // Base class: a final class, no virtual dtor

// struct DerivedBase : public Base {}; // illegal: cannot override final struct

class BaseClass {
public:
  virtual ~BaseClass() {}

public:
  virtual int f(int) { return 0; }
  virtual int g() final { return 0; }
  virtual int h() { return 0; }
};

class DerivedClass final : public BaseClass {
public:
  DerivedClass() = default;
  int f(double) /* override */ { return 1; } // does not override any method of Class
  // int g() { return 1; }          // illegal: cannot override final method
  int h() override { return 0; } // ok overrides BaseClass::h
};


int main() {
  return 0;
}