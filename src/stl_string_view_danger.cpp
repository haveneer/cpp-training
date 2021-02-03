//#region [declarations]
#include <iomanip>
#include <iostream>
#include <map>
#include <string_view>
#define DISPLAY(s)                                                                \
  std::cout << #s << "=\"" << (s) << "\"" << std::setw(40 - s.size())             \
            << " with length=" << (s).size() << ": " << check(s.data(), s.size()) \
            << "\n";

std::string_view location;
#define LOCATE(msg)                                                  \
  {                                                                  \
    if (do_monitor || true)                                          \
      std::cout << "\tLine " << __LINE__ << "... (" << msg << ")\n"; \
    location = msg;                                                  \
  }

std::map<void *, std::tuple<std::size_t, std::string_view>> allocations;
bool do_monitor = true;
bool inside_allocator = false;

std::string_view check(const char *data, std::size_t n) {
  for (auto &&[p, x] : allocations) {
    const char *upper_p = static_cast<const char *>(p) + std::get<0>(x);
    if (data >= static_cast<const char *>(p) && data < upper_p) {
      if (data + n < upper_p) {
        return "valid data";
      } else {
        return "valid data but overflow";
      }
    }
  }
  return "dangling data";
}

void *operator new(std::size_t n) {
  void *p = malloc(n);
  if (do_monitor)
    std::cout << "\tnew() " << n << " bytes for '" << location << "'\n";
  if (!inside_allocator) {
    inside_allocator = true;
    allocations[p] = std::make_tuple(n, location);
    inside_allocator = false;
  }
  return p;
}

void delete_it(void *p) {
  free(p);
  if (allocations.find(p) != allocations.end()) {
    inside_allocator = true;
    std::size_t n = std::get<0>(allocations[p]);
    std::string_view loc = std::get<1>(allocations[p]);
    if (do_monitor)
      std::cout << "\tdelete() " << n << " bytes from '" << loc << "'\n";
    allocations.erase(p);
    inside_allocator = false;
  }
}

void operator delete(void *p) { return delete_it(p); }
void operator delete(void *p, std::size_t) { return delete_it(p); }
//#endregion

// TODO change return type to std::string
std::string_view getSubstringFromHint(const std::string_view &s,
                                      const std::string_view &hint) {
  LOCATE("Inside getSubstringFromHint");
  return s.substr(s.find(hint)); // do not own any memory; just a string_view
}

std::string makeTemporaryString() { return {"A long temporary string"}; }

int main() {
  do_monitor = false; // TODO: play with this flag to display allocation details

  LOCATE("cpp_string ctor");
  std::string cpp_string{"Hello C++ World"};
  LOCATE("cpp_string longer initial value");
  cpp_string = "Hello Amazing C++ World"; // TODO comment out this; what happens?
  LOCATE("new sv1 ctor");
  std::string_view sv1{cpp_string};
  DISPLAY(sv1);

  LOCATE("getSubstringFromHint function call");
  std::string_view sv2 = getSubstringFromHint(cpp_string + " of Madness", "C++");
  DISPLAY(sv2);

  LOCATE("reset cpp_string to a small string");
  cpp_string = "New short string";
  DISPLAY(sv1); /* sv1 is wrong, but not dangling pointer */
  DISPLAY(sv2);

  LOCATE("reset cpp_string to a very long string");
  cpp_string = "Hello Amazing C++ World (long string to avoid SSO)";
  DISPLAY(sv1); /* sv1 is wrong and dangling pointer */
  DISPLAY(sv2);

  LOCATE("make a string_view from a temporary string");
  const std::string_view &sv3{makeTemporaryString()};
  DISPLAY(sv3); // Dangling pointer

  LOCATE("make a const string& from a temporary string");
  const std::string &s3{makeTemporaryString()};
  DISPLAY(s3); // OK (no dangling ref; cf https://wg21.link/p0936 and C++17 Draft)
}