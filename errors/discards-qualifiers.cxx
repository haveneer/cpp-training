//#region [Collapse all]
#include <iostream>
#include <string>

class Name {
public:
  Name(const std::string &name) : m_name(name) {}
  std::string name() { return m_name; }

private:
  std::string m_name;
};

void say(std::string msg, const Name & x) {
  std::cout << msg << " " << x.name() << "!\n";
}

int main() {
  Name john("John");
  say("Hello", john);
}
//#endregion