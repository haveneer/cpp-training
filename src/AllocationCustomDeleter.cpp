//#region [Declarations]
#include <iostream>
#include <memory>
#include <new>
//#endregion

struct Deleter {
  void operator()(int *ptr) const {
    std::cout << "Deleter(" << ptr << ")" << std::endl;
  }
};

void custom_delete(int *ptr) {
  std::cout << "custom_delete(" << ptr << ")" << std::endl;
}

int main() {
  {
    // For unique_ptr the Deleter is an element of the signature but cost nothing
    std::unique_ptr<int> p1{new int{1}};
    std::cout << "Size of std::unique_ptr<int> is " << sizeof(p1) << "\n";

    std::unique_ptr<int, Deleter> p2{new int{2}};
    std::cout << "Size of std::unique_ptr<int, Deleter> is " << sizeof(p2) << "\n";

    // except if only for instantiated deleter (then a memory overhead occurs)
    std::unique_ptr<int, decltype(&custom_delete)> p3{new int{3}, &custom_delete};
    std::cout << "Size of std::unique_ptr<int, decltype(&custom_delete)> is "
              << sizeof(p3) << "\n";
  }

  {
    // For shared_ptr the cost of the Deleter always occurs
    std::shared_ptr<int> q1{new int{1}};
    std::cout << "Size of std::shared_ptr<int> is " << sizeof(q1) << "\n";

    std::shared_ptr<int> q2{new int{2}, Deleter{}};
    std::cout << "Size of std::shared_ptr<int, Deleter> is " << sizeof(q2) << "\n";

    // a memory overhead occurs only for instantiated deleter
    std::shared_ptr<int> q3{new int{3}, custom_delete};
    std::cout << "Size of std::shared_ptr<int, decltype(&custom_delete)> is "
              << sizeof(q3) << "\n";
  }
}