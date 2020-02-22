//#region [Declarations]
#include <iostream>
class Object;
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

Object *pf = nullptr;
void f1();
void f2();

void f() {
  f1();
  if (pf->value() > 1)
    return;
  f2();
}

//#region [details]
void f1() { pf = new Object{}; }
void f2() { delete pf; }
//#endregion

int main() {
  for (int i = 0; i < 5; ++i)
    f();
}