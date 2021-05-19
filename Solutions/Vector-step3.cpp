//#region [declarations]
#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>
#include <iterator>
//#endregion

template <typename T> class Vector {
public:
  // Without 'explicit', indirect instanciation as [](Vector<int> v){}(2) is allowed
  explicit Vector(int size) : m_size{size}, m_v{std::make_unique<T[]>(size)} {}
  Vector(const Vector &v) : Vector(v.m_size) { // delegated constructor
    raw_copy(m_v.get(), v.m_v.get(), m_size);
  }
  Vector(Vector &&v) : m_size{v.m_size}, m_v{std::move(v.m_v)} { v.m_size = 0; }
  // after move unique_ptr is reset to nullptr; hence, v.m_v is null

  // explicit C++11 : no implicit conversion
  explicit operator bool() { return m_size != 0; }

  auto &operator[](int i) { return m_v[i]; } // requires a lvalue ref return type
  auto operator[](int i) const { return m_v[i]; }

  Vector &operator=(const Vector &v) { // required to satisfy 3/5/0 rule
    if (this != &v) {                  // to prevent work/bug on case 'v=v'
      if (m_size != v.m_size) {        // if memory allocation is not good
        m_size = v.m_size;
        m_v = std::make_unique<T[]>(m_size); // rvalue copy operator
        // m_v.reset(new int[m_size]); // equivalent but we prefer to avoid 'new'
      }
      raw_copy(m_v.get(), v.m_v.get(), m_size);
    }
    return *this; // rvalue return permits chaining : v1 = v2 = v3
  }
  Vector &operator=(Vector &&v) {        // required to satisfy 3/5/0 rule
    m_size = std::exchange(v.m_size, 0); // a = exchange(b, c) => a = b, b =c
    m_v = std::move(v.m_v);              // then v.m_v is null
    return *this;
  }

  void print(std::ostream &o) const;

  auto begin() const { return m_v.get(); }
  auto end() const { return begin() + m_size; }
  auto begin() { return m_v.get(); }
  auto end() { return begin() + m_size; }

  auto size() const { return m_size; }

public:
  using iterator = T *; // not mandatory but gives a more compliant 'STL style'
  typedef const T *const_iterator;
  using value_type = T; // useful to be compliant with STL style

private:
  static void raw_copy(T *dst, const T *src, int size) {
    // Prefer optimized copy for trivially copiable data
    if constexpr (std::is_trivially_copy_constructible_v<T>) {
      std::memcpy(dst, src, sizeof(T) * size);
    } else {
      for (auto i = 0; i < size; ++i)
        dst[i] = src[i];
    }
  }

private:
  int m_size;
  std::unique_ptr<T[]> m_v;
};

template <typename X> void Vector<X>::print(std::ostream &o) const {
  o << "Vector(size=" << m_size << "; " << m_v.get() << " : ";
  std::copy(this->begin(), this->end(), std::ostream_iterator<X>(o, " "));
  o << ')';
}

template <typename U> auto &operator<<(std::ostream &o, const Vector<U> &v) {
  v.print(o);
  return o;
}

template <typename T1, typename T2>
auto operator+(const Vector<T1> &x1, const Vector<T2> &x2) {
  assert(x1.size() == x2.size());
  // using T3 = decltype(T1{}+T2{}); // T1 and T2 must be default constructible.
  using T3 = decltype(std::declval<T1>() + std::declval<T2>()); // Ok in any case
  Vector<T3> x3(x1.size());
  for (int i = 0; i < x1.size(); ++i) {
    x3[i] = x1[i] + x2[i];
  }
  return x3;
}

template <typename T, typename F>
typename Vector<T>::iterator      // typename required to say explicitly
                                  // that iterator is a type in the template class
transform1(Vector<T> &v, F &&f) { // TODO F using &&, & or no ref specifier ?
  // for (typename Vector<T>::iterator i = v.begin(), e = v.end(); i != e; ++i) //OLD
  for (auto &x : v) {
    x = f(x);
  }
  return v.end(); // not really useful; just matchs 'classical' std::transform output
}

auto transform2 = [](auto &v, auto &&f) { // OK may be to 'open'
  for (auto &x : v) { // the 'auto' style signature will not filter
    x = f(x);         // bad input types; errors will be located
  }                   // inside function body
  return v.end();
};

template <typename T> void f(Vector<T> &v) {
  for (auto &x : v) {
    x++;
  }
}

void g(Vector<int> v) {}

int main() {
  Vector<int> v1(3);
  std::cout << v1 << '\n';
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 2;
  v1[2]++;
  std::cout << v1 << '\n';
  Vector<int> v2(5);
  std::cout << v2 << '\n';
  v2 = v1;
  std::cout << v2 << '\n';

  // std::pair<int,double> p1{1,1.}; // explicit template parameter
  // std::pair p2{1,1.}; // C++17

  Vector /*<C++17 deduced>*/ v3{std::move(v1)};
  std::cout << v1 << '\n';
  std::cout << v3 << '\n';
  Vector<int>::iterator i = v3.begin();
  v2 = std::move(v3);
  // *i ? => i now points on the first element of v2
  std::cout << v2 << '\n';
  std::cout << v3 << '\n';

  Vector<double> v4(3);
  v4[0] = v4[1] = v4[2] = 1.5;
  Vector /*<C++17 deduced>*/ v5 = v2 + v4;
  std::cout << v5 << '\n';

  f(v2);
  std::cout << v2 << '\n';

  auto l = [count = 0](int i) mutable { return ++count; };
  std::cout << l(1) << '\n';
  std::cout << l(1) << '\n';
  std::cout << l(1) << '\n';
  std::cout << l(1) << '\n';

  /* Vector<int>::iterator i = */ transform1(
      v2, [count = 0](int i) mutable { return ++count; }); // return value not used
  transform2(v2, l);
  std::transform(v2.begin(), v2.end(), v2.begin(), l);
  std::cout << v2 << '\n';

  // g(10); // cf explicit on ctor
  //  bool b = v2; // cf explicit on operator bool

  // Using the too open algorithm2 signature: strange things may occur
  // std::string a = "Hello World";
  // transform2(a, [](int i) { return i * i; });
  // int b = 0;
  // transform2(b, [](int i) { return i * i; }); // error: invalid range expression
  //                                             // of type 'int'; no viable 'begin'

  std::vector<decltype(v2)::value_type> w; // same type as v2
  w.reserve(v2.size());
  int count = 0;
  std::copy_if(v2.begin(), v2.end(), std::back_inserter(w), [&count](auto x) {
    bool condition = (x >= 2);
    if (condition)
      ++count;
    return condition;
  });
  assert(static_cast<size_t>(count) == w.size()); // NB: size() is not signed in STL
}