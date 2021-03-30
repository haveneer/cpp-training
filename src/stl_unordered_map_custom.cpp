//#region [Declarations]
#include <cctype> // pour tolower et isalpha
#include <iostream>
#include <sstream>
#include <string>
//#endregion
#include <unordered_map>

struct MyKey {
  std::string first_name;
  std::string last_name;
};

// Required equality operator
bool operator==(const MyKey &key1, const MyKey &key2) {
  return key1.first_name == key2.first_name && key1.last_name == key2.last_name;
}

// Custom hash function
size_t my_hash_function(const MyKey &key) {
  return std::hash<std::string>()(key.first_name) ^
         std::hash<std::string>()(key.last_name);
}

// Overload std::hash
namespace std {
template <> class hash<MyKey> {
public:
  size_t operator()(const MyKey &key) const { return my_hash_function(key); }
};
} // namespace std

int main() {
  // using explicit hash function and a initial buckets size
  std::unordered_map<MyKey, int, decltype(&my_hash_function)> data(100,
                                                                   my_hash_function);
  // default overloaded std::hash function and default size
  // std::unordered_map<MyKey, int> data;

  data[MyKey{"John", "Do"}] = 1;
  data[MyKey{"James", "Bond"}] = 1;

  for (auto [k, v] : data) {
    std::cout << k.first_name << " " << k.last_name << " " << v << std::endl;
  }
}