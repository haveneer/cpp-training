#include <array>
#include <charconv> // C++17
#include <iostream>
#include <string>

int main() {
  char str[] = {" 42 a"};
  int result;
  std::cout << "Using std::from_chars (C++17)\n";
  auto [p, ec] = std::from_chars(str, str + sizeof(str), result);
  std::cout << "ec is success = " << (ec == std::errc{}) << '\n';
  std::cout << "result = " << result << '\n';
  std::cout << "p = " << p << '\n';

  std::cout << "\nUsing std::stoi (C++11)\n";
  std::size_t pos;
  try {
    result = std::stoi(str, &pos);
  } catch (std::invalid_argument &e) {
    std::cout << "Caught invalid_argument exception : " << e.what() << '\n';
  } catch (std::out_of_range &e) {
    std::cout << "Caught out_of_range exception : " << e.what() << '\n';
  } catch (...) {
    std::cout << "Caught unknown exception\n";
  }
  std::cout << "pos = " << pos << '\n';
  std::cout << "result = " << result << '\n';
}