//#region [Declarations]
#include <functional>
#include <iostream>
#include <string>
#include <utility>
//#endregion

struct Obj11 { // C++11
  ~Obj11() { std::cout << "Dtor of Obj11{ " << s << "}\n"; }

  std::function<void(const char *w)> f() {
    // return [s] { std::cout << s << "\n"; }; // error: 's' in capture list
    //                                         //        does not name a variable
    return [=](const char *w) { std::cout << s << w << "\n"; };
  }

  std::string s;
};

struct Obj14 { // C++14
  ~Obj14() { std::cout << "Dtor of Obj14{ " << s << "}\n"; }
  auto f() {
    // return [s] { std::cout << s << "\n"; }; // error: 's' in capture list
    //                                         //        does not name a variable
    return [s = s](auto w) { std::cout << s << w << "\n"; }; // s as named copy
    // return [self=*this](auto w) { std::cout << self.s << w << "\n"; }; // alt
  }

  std::string s;
};

//#region[utility]
template <class... Fs> struct overloaded : Fs... { using Fs::operator()...; };
template <class... Fs> overloaded(Fs...) -> overloaded<Fs...>;
//#endregion

struct Obj17 { // C++17
  ~Obj17() { std::cout << "Dtor of Obj17{ " << s << "}\n"; }
  auto f() {
    return overloaded{
        // capture class by copy (FIXME don't abuse like we do here)
        [*this](int w) { std::cout << s << "int " << w << "\n"; },
        [*this](const std::string &w) { std::cout << s << "string " << w << "\n"; }};
  }

  std::string s;
};

int main() {
  auto f1 = Obj11{"Obj11: Hello "}.f();
  f1("World"); // C++11 UB // s is a dangling reference (Obj11 has been destroyed)
  auto f2 = Obj14{"Obj14: Magic "}.f();
  f2(42); // C++14 OK (s has been captured by copy)
  auto f3 = Obj17{"Obj17: Wonderful "}.f();
  f3(42);   // C++17 OK
  f3("42"); // C++17 OK
}