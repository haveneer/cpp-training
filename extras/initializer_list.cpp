#include <iostream>
#include <vector>

struct TrivialObject {
  float first;
  int second;
  int third; // ignored if two args initialization
};

class Collection {
public:
  Collection(std::initializer_list<int> l) : m_n(l.size()), m_vector(l) {
    std::cout << "Build Collection from a list\n";
  }
  Collection(int n) : m_n{n} { std::cout << "Build Collection from an int\n"; }
  int size() const { return m_n; }
  void append(std::initializer_list<int> l) {
    m_n += l.size();
    m_vector.insert(m_vector.end(), l.begin(), l.end());
  }

private:
  int m_n;
  std::vector<int> m_vector;
};

int main() {
  // C++03 style
  int tab03[] = {1, 2, 3, 4};
  int n = sizeof(tab03) / sizeof(int);
  std::cout << "tab03 = {";
  for (int i = 0; i < n; ++i)
    std::cout << " " << tab03[i];
  std::cout << " }\n";

  // C++11 style
  auto tab11 = {1, 2, 3, 4};
  std::cout << "tab11 = {";
  for (auto x : tab11)
    std::cout << " " << x;
  std::cout << " }\n";

  TrivialObject scalar = {0.43f,
                          10}; // One TrivialObject, with first=0.43f and second=10
  TrivialObject anArray[] = {
      {13.4f, 3, 1}, {43.28f, 29}, {5.934f, 17}}; // An array of three TrivialObjects

  // Many styles of initialization (equivalent)
  Collection c1 = {1, 2, 3, 4};
  Collection c2({1, 2, 3, 4});
  Collection c3{1, 2, 3, 4};

  // OK also for scalar but...
  int a{6};

  // { } will prefer initializer_list rather than scalar initialization when available
  Collection c5{4};
  std::cout << "  c5{5} size = " << c5.size() << "\n";
  Collection c6(4);
  std::cout << "  c6(4) size = " << c6.size() << "\n";

  c6.append({1, 2, 3});
  std::cout << "  c6 size after append = " << c6.size() << "\n";
}