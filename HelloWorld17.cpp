#include <iostream>

auto print =[](auto&& arg, auto&& ...args){
    std::cout << std::forward<decltype(arg)>(arg);
    ((std::cout << ", " << std::forward<decltype(args)>(args)), ...);
    std::cout << std::endl;
};

int main() { // C++17
    print("Hello", "world!");
}
