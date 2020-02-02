//#region [Declaration]
// Exemple inspiré de https://cpppatterns.com/patterns/rule-of-five.html
#include <utility>
//#endregion

class resource {
  int x = 0;
};

class Foo {
public:
  Foo() : p{new resource{}} {}
  Foo(const Foo &other) : p{new resource{*(other.p)}} {}
  Foo(Foo &&other) : p{other.p} { other.p = nullptr; }
  Foo &operator=(const Foo &other) {
    if (&other != this) {
      delete p;
      p = nullptr;
      p = new resource{*(other.p)};
    }
    return *this;
  }
  Foo &operator=(Foo &&other) {
    if (&other != this) {
      delete p;
      p = other.p;
      other.p = nullptr;
    }
    return *this;
  }
  ~Foo() { delete p; }

private:
  resource *p;
};


int main() {
  Foo a;
  Foo b;
  a = b;
  b = std::move(a);
}
