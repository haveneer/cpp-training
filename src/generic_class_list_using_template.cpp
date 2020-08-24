#include <cassert>
#include <iostream>

/***************** début de list.hpp *******************/
template <typename T> class List {
private:
  class Element {
    friend class List;

  public:
    Element(const T &t) : m_value(t), m_next(nullptr) {}

  private:
    T m_value;
    Element *m_next;
  };

public:
  class Iterator {
    friend class List;

  public:
    Iterator() : m_element(nullptr) {}
    T &operator*() { return m_element->m_value; }
    void operator++() {
      assert(m_element);
      m_element = m_element->m_next;
    }
    bool operator!=(const Iterator &i) const {
      return m_element != i.m_element;
    }

  private:
    Element *m_element;

  private:
    Iterator(Element *e) : m_element(e) {}
  };

public:
  List() : m_size(0), m_first(nullptr), m_last(&m_first) {}
  List(const List &v) : m_size(0), m_first(nullptr), m_last(&m_first) {
    *this = v;
  }
  List &operator=(const List &v);
  virtual ~List() { clear(); }

public:
  Iterator begin() { return Iterator(m_first); }
  Iterator end() { return Iterator(0); }
  inline int size() const { return m_size; }
  List &operator<<(const T &t);
  void clear();
  friend std::ostream &operator<<(std::ostream &o, const List &v) {
    v.print(o);
    return o;
  }

private:
  void print(std::ostream &o) const;
  int m_size;
  Element *m_first, **m_last;
};
/***************** fin de list.hpp *******************/
/***************** début de list.cpp *******************/

template <typename T> List<T> &List<T>::operator=(const List<T> &v) {
  if (m_size)
    clear();
  List &list = *this;
  Element *p = v.m_first;
  while (p != nullptr) {
    list << p->m_value;
    p = p->m_next;
  }
  assert(m_size == v.m_size);
  return *this;
}

template <typename T> void List<T>::clear() {
  Element *p = m_first;
  while (p != nullptr) {
    Element *e = p;
    p = p->m_next;
    delete e;
    --m_size;
  }
  assert(m_size == 0);
  m_last = &m_first;
}

template <typename T> List<T> &List<T>::operator<<(const T &t) {
  *m_last = new Element(t);
  m_last = &(*m_last)->m_next;
  ++m_size;
  return *this;
}
template <typename T> void List<T>::print(std::ostream &o) const {
  o << "[size=" << m_size << "] ";
  Element *p = m_first;
  while (p != nullptr) {
    o << p->m_value << " ";
    p = p->m_next;
  }
}

/***************** fin de list.cpp *******************/
int main() {
  const int n = 10;
  List<int> u;
  for (int i = 0; i < n; ++i)
    u << i; // initialisation std::cout << u << "\n";
  List<int> v(u);
  for (List<int>::Iterator i = v.begin(); i != v.end(); ++i)
    *i += 1;
  v << n + 1 << n + 2;
  std::cout << v << "\n";
}