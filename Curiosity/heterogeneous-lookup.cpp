#include <cassert>
#include <set>
#include <string>
#include <string_view>

struct Product {
  std::string name;
  std::string description;
  double price;
};

bool operator<(const Product &p1, const Product &p2) { return p1.name < p2.name; }

// Heterogeneous compare used by C++ 14 std::less<>
// It reduces creation of temporary objects while comparing
bool operator<(const Product &p1, const std::string_view &name2) {
  return p1.name < name2;
}
bool operator<(const std::string_view &name1, const Product &p2) {
  return name1 < p2.name;
}

struct MyComparator { // my custom comparator compatible with heterogeneous lookup
  bool operator()(const Product &p1, const Product &p2) const {
    return p1.name < p2.name;
  }
  bool operator()(const Product &p1, const std::string_view &name2) const {
    return p1.name < name2;
  }
  bool operator()(const std::string_view &name1, const Product &p2) const {
    return name1 < p2.name;
  }
  using is_transparent = int; // enable heterogeneous lookup
};

int main() {
  std::set<Product> products1{
      {"Car", "This is a super car that costs a lot", 100'000.0},
      {"Ball", "A cheap but nice-looking ball to play", 100.0},
      {"Orange", "Something to eat and refresh", 50.0}};

  // products1.find("Car"); // Cannot compare Product and 'const char *' using
  // default comparator

  std::set<Product, std::less<>> products2{
      // use C++14 heterogeneous comparator
      {"Car", "This is a super car that costs a lot", 100'000.0},
      {"Ball", "A cheap but nice-looking ball to play", 100.0},
      {"Orange", "Something to eat and refresh", 50.0}};

  auto finder2 = products2.find("Car"); // Can compare Product and 'const char *'
                                        // this 'find' method is not the same
                                        // it use a template type + SFINAE
                                        // see std::less<void> + is_transparent
  assert(finder2 != products2.end());

  std::set<Product, MyComparator> products3{
      {"Car", "This is a super car that costs a lot", 100'000.0},
      {"Ball", "A cheap but nice-looking ball to play", 100.0},
      {"Orange", "Something to eat and refresh", 50.0}};

  auto finder3 = products3.find("Car"); // My custom 'transparent' comparator
  assert(finder3 != products3.end());
  
  // Exists also for unordered_map & unordered_set 
}