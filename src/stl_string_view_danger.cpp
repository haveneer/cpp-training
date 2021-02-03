//#region [declarations]
#include <iomanip>
#include <iostream>
#include <map>
#include <string_view>

//#ifdef WIN32
//#define HIDE_DANGLING_DATA
//#endif

#ifdef HIDE_DANGLING_DATA
#define DISPLAY(s)                                                        \
  {                                                                       \
    if (auto v = check(s.data(), s.size()); v == "valid data")            \
      std::cout << #s << "=\"" << (s) << "\"" << std::setw(50 - s.size()) \
                << " with length=" << (s).size() << ": " << v << "\n";    \
    else {                                                                \
      std::string_view alts = " CANNOT DISPLAY ";                         \
      std::cout << #s << "=" << alts << std::setw(50 - alts.size())       \
                << " with length=" << (s).size() << ": " << v << "\n";    \
    }                                                                     \
  }
#else
#define DISPLAY(s)                                                                  \
  {                                                                                 \
    std::cout << #s << "=\"" << (s) << "\"" << std::setw(50 - s.size())             \
              << " with length=" << (s).size() << ": " << check(s.data(), s.size()) \
              << "\n";                                                              \
  }
#endif

std::string_view location;
#define LOCATE(msg)                                                        \
  {                                                                        \
    if (do_monitor || true)                                                \
      std::cout << "\tLine " << std::setw(3) << __LINE__ << "... (" << msg \
                << ")\n";                                                  \
    location = msg;                                                        \
  }

std::map<void *, std::tuple<std::size_t, std::string_view>> *allocations = nullptr;
bool do_monitor = true;
bool inside_allocator = false;

std::string_view check(const char *data, std::size_t n) {
  for (auto &&[p, x] : *allocations) {
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
  if (!inside_allocator) {
    if (allocations == nullptr) {
      inside_allocator = true;
      allocations =
          new std::map<void *, std::tuple<std::size_t, std::string_view>>{};
      inside_allocator = false;
    }
    if (do_monitor)
      std::cout << "\tnew() " << n << " bytes for '" << location << "'\n";
    inside_allocator = true;
    (*allocations)[p] = std::make_tuple(n, location);
    inside_allocator = false;
  }
  return p;
}

void delete_it(void *p) {
  free(p);
  if (auto finder = allocations->find(p); finder != allocations->end()) {
    inside_allocator = true;
    auto &&[n, loc] = finder->second;
    if (do_monitor)
      std::cout << "\tdelete() " << n << " bytes from '" << loc << "'\n";
    allocations->erase(p);
    inside_allocator = false;
  }
}

void operator delete(void *p) noexcept { return delete_it(p); }
void operator delete(void *p, std::size_t /*unused*/) noexcept {
  return delete_it(p);
}
//#endregion

// TODO: change return type to std::string
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
  cpp_string = "Hello Amazing C++ World"; // TODO: comment out this; what happens?
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
  const std::string_view &sv3{makeTemporaryString()}; // TODO: and without &
  DISPLAY(sv3);                                       // Dangling pointer

  LOCATE("make a const string& from a temporary string");
  const std::string &s4{makeTemporaryString()};
  DISPLAY(s4); // OK (no dangling ref; cf https://wg21.link/p0936 and C++17 Draft)
}