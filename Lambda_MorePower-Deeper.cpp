//#region [Declarations]
#include <algorithm>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>
using namespace std::string_literals;
//#endregion

// clang-format off
struct Circle { void draw() const { std::cout << "Draw a Circle\n"; } };
struct Square { void draw() const { std::cout << "Draw a Square\n"; } };
struct Triangle { void draw() const { std::cout << "Draw a Triangle\n"; } };
// clang-format on

// New composite type
using Shape = std::variant<Circle, Square, Triangle>;

//#region [Renderer class details]
class Renderer {
public:
  explicit Renderer(std::string name) : m_name{std::move(name)} {}
  Renderer(const Renderer &c) : m_name{"Copy of "s + c.m_name}, m_counter{0} {}
  Renderer(Renderer &&c) noexcept
      : m_name{"Move of "s + std::move(c.m_name)}, m_counter{0} {}
  ~Renderer() {
    std::cout << m_name << " Renderer has been called " << m_counter << " times\n";
  }
  auto render(const Shape &sh) {
    ++m_counter;
    std::visit([](auto &sh) { sh.draw(); }, sh);
  }

private:
  std::string m_name;
  int m_counter = 0;
};
//#endregion

int main() {
  std::vector<Shape> v{Circle{}, Square{}, Triangle{}};

  auto printer = [renderer = Renderer{"First"}](auto &sh) mutable {
    renderer.render(sh);
  };

  // TODO 3 forms; make your choice; what happens for each ?
  // std::for_each(v.begin(), v.end(), printer);
  std::for_each(v.begin(), v.end(), [&printer](auto &sh) { printer(sh); });
  // std::for_each(
  //     v.begin(), v.end(),
  //     [renderer = Renderer{"Second"}](auto &sh) mutable { renderer.render(sh); });
}