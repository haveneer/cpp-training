//#region [Preambule]
//#region [Declarations]
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//#endregion

std::vector<std::string> split(const char *str, const char *delimiters) {
  std::vector<std::string> tokens; // NRVO
  std::array<uint64_t, 4> fast_delimiters{};
  for (const char *delim = delimiters; *delim != '\0'; ++delim) {
    const auto c = static_cast<unsigned char>(*delim);
    fast_delimiters[c >> 6u] |= (1u << (c & 0b111111u));
  }
  auto is_delimiter = [&](const unsigned char c) {
    return (fast_delimiters[c >> 6u] & (1u << (c & 0b111111u))) != 0;
  };

  const char *begin = str;
  const char *p = begin;
  for (; *p != '\0'; ++p) {
    if (is_delimiter(*p)) {
      if (begin != p) { // there is a not-empty word
        tokens.emplace_back(begin, p - begin);
      }
      begin = p + 1;
    }
  }
  if (begin != p) { // there is a not-empty word
    tokens.emplace_back(begin, p - begin);
  }
  return tokens;
}

auto text =
    //#region [long text]
    R"#(Lorem ipsum dolor sit amet, consectetur adipiscing elit. 
    Nam tristique mi non quam aliquam, in lacinia sapien condimentum. 
    Pellentesque rhoncus ut tortor aliquam dictum. 
    In ut magna et odio iaculis ornare. 
    Mauris pharetra augue diam, consectetur volutpat magna consequat vel. 
    Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; 
    Nulla tincidunt, eros vitae malesuada suscipit, augue tortor imperdiet felis, a pretium ante magna at sapien. 
    Ut eleifend ipsum quis pellentesque tristique. Morbi volutpat sagittis tortor at interdum. 
    Nulla imperdiet blandit gravida. Morbi dignissim aliquet vehicula. Nullam posuere fermentum tempor. 
    Proin scelerisque, augue ac mattis pretium, quam libero gravida felis, ornare ultrices eros tortor id libero. 
    Aliquam iaculis lectus velit, at dignissim ante efficitur eget.)#";
//#endregion
//#endregion

// Custom type supporting range-based for
class FibonacciGenerator {
public:
  explicit FibonacciGenerator(unsigned n) : m_n(n) {}

  class iterator {
  protected:
    friend class FibonacciGenerator;
    explicit iterator(unsigned n) : m_n(n) {}

  public:
    unsigned operator*() const { return m_n; }
    bool operator!=(const iterator &other) { return m_n != other.m_n; }
    void operator++() { m_n = (m_n % 2) ? 3 * m_n + 1 : m_n / 2; }

  private:
    unsigned m_n;
  };
  
  // begin and end may have different types, but they have to be comparable
  [[nodiscard]] iterator begin() const { return iterator{m_n}; }
  [[nodiscard]] iterator end() const { return iterator{1}; }

private:
  const unsigned m_n;
};

int main() {
  // Realistic example
  std::map<std::string, int> occurrences;
  const auto words = split(text, " \t\n.,;:");

  for (auto &word : words) {
    occurrences[word]++;
    // std::cout << word << '\n';
  }

  for (auto &&[word, count] : occurrences) { // C++17 structured binding
    if (count > 2) {
      std::cout << std::setw(15) << word << " : " << count << '\n';
    }
  }

  // Custom type supporting range-based for
  FibonacciGenerator generator(100);
  for (auto &&x : generator) {
    std::cout << x << ' ';
  }
  std::cout << "1 \n";
}
