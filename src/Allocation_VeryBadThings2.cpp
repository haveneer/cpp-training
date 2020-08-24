//#region [Declarations]
#include <iostream>
class Object;
int h(Object *) { throw std::exception{}; }
//#endregion

class Object {
public:
  Object() : m_v{g_counter++} { std::cout << "Build Object #" << m_v << '\n'; }
  ~Object() { std::cout << "Destroy Object #" << m_v << '\n'; }
  int value() const { return m_v; }

private:
  const int m_v;
  inline static int g_counter = 0; /* inline initialization due to 'inline' */
};

void g() {
  Object *p = new Object;
  if (p->value() >= 2)
    return;
  delete p;
}

int main() {

  g(); // first ok
  g(); // second ok
  g(); // third... not ok

  std::cout << "-----\n";

  try {
    Object *p = new Object[4];
    h(p);
    delete[] p;
  } catch (std::exception &e) {
    std::cout << "Something goes wrong...\n";
    // objects never desallocated
  }
}