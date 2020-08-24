//#region [Declarations]
#include <iostream>
#include <map>
#include <vector>

class A;
std::map<const A *, int> names;
char name(const A *a) {
  int &n = names[a];
  if (n == 0)
    n = names.size();
  return 'a' + n - 1;
}
//#endregion

class A {
public:
  A() : data_(100) { std::cout << "new " << name(this) << " : A()\n"; }

  A(A const &s) : data_(s.data_) {
    std::cout << "new " << name(this) << " : A(const& " << name(&s) << ")\n";
  }
  A(A &&s) : data_(std::move(s.data_)) {
    std::cout << "new " << name(this) << " : A(&& " << name(&s) << ")\n";
  }

  ~A() = default;

  A &operator=(A const &s) {
    if (&s == this) {
      std::cout << name(this) << " = (const& " << name(&s) << "): self copy\n";
    } else {
      std::cout << name(this) << " = (const& " << name(&s) << ")\n";
      data_ = s.data_;
    }
    return *this;
  }

  A &operator=(A &&s) {
    std::cout << name(this) << " = (&& " << name(&s) << ")\n";
    data_ = std::move(s.data_);
    return *this;
  }

private:
  std::vector<int> data_;
};

int main() {
  A a, b, c;
  A d = a;
  A e{a};
  b = A{};
  c = b;
  d = std::move(b);
  d = d;
}