#include <exception>
#include <iostream>

void formated_print(const char *s) {
  while (*s) {
    if (*s == '%') {
      if (*(s + 1) == '%') {
        ++s;
      } else {
        throw std::runtime_error("invalid format string: missing arguments");
      }
    }
    std::cout << *s++;
  }
}

template <typename T, typename... Args>
void formated_print(const char *s, T value, Args... args) {
  while (*s) {
    if (*s == '%' && *(s+1) != '%') {
      std::cout << value;
      return formated_print(s + 1, args...);
    }
    std::cout << *s++;
  }
}

int main() {
  formated_print("This is a interpreted string printer\n");
  formated_print("This is an % string with % components\n","interpreted",2);
  std::cout << "\n";
}