//#region [Collapse all]
#include <iostream>
class X {
public:
  X() : state(global_state++) {}
  X(const X &x0) {
    state = global_state++;
    std::cout << "DTOR COPY X(" << x0.state << ")\n";
  }
  void operator=(const X &x0) {
    state = global_state++;
    std::cout << "ASSIGN COPY X(" << x0.state << ")\n";
  }

public:
  int state;
  inline static int global_state = 0;
};

X f(X x2) {
  std::cout << "x2 is " << x2.state << "\n";
  X x_false; // state==3
  X x_true;  // state==4
  if (x2.state) {
    return x_true;
  } else {
    return x_false;
  }
}

int main() {
  X x0;
  auto r = f(x0).state;
  std::cout << "f(x0) is " << r << "\n"; // state==5
}
//#endregion