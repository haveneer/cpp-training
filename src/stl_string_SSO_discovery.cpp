//#region [Declarations]
#include <iomanip>
#include <iostream>
#include <string>
#define DISPLAY(s)                                                               \
  {                                                                              \
    std::cout << #s << "=\"" << (s) << "\"" << std::setw(50 - s.size())          \
              << " with length=" << (s).size() << " data=" << (void *)(s).data() \
              << "\n";                                                           \
  }
//#endregion
// TODO: how to detect Small String Optimization ?
int main() {
  std::size_t string_size = sizeof(std::string);
  std::cout << "sizeof(std::string) = " << string_size << "\n";
  int previous_state = -1;
  bool has_ellipsed = false;
  auto print_state = [](std::size_t size, int state) {
    if (state >= 0)
      std::cout << std::setw(3) << size << " "
                << ((state) ? "Long string" : "Small string") << "\n";
  };

  for (std::size_t size = 0; size <= string_size + 1; ++size) {
    std::string s1(size, '_'); // SSO or not SSO ?
    auto *s1ptr = s1.data();
    std::string s2{std::move(s1)};
    auto *s2ptr = s2.data();
    int current_state = (s1ptr == s2ptr);
    if (previous_state != current_state) {
      if (has_ellipsed)
        print_state(size - 1, previous_state);
      print_state(size, current_state);
      previous_state = current_state;
      has_ellipsed = false;
    } else {
      if (!has_ellipsed)
        std::cout << "...\n";
      has_ellipsed = true;
    }
  }
}