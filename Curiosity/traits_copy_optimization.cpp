#include <cstring> // pour memcpy
#include <iostream>

template <bool B> using bool_ = std::integral_constant<bool, B>;

template <typename T>
using is_trivially_copyable_t = typename std::is_trivially_copyable<T>::type;
// prior to C++11, std::is_trivially_copyable can be defined as a trait class written
// by hand using ad-hoc specialization 
//   struct TrueType {};
//   struct FalseType {};
//   template <typename T> struct is_trivially_copyable { typedef FalseType type; };
//   template <> struct is_trivially_copyable<bool> { typedef TrueType type; };
//   template <> struct is_trivially_copyable<int> { typedef TrueType type; };
//   template <> struct is_trivially_copyable<double> { typedef TrueType type; };
//   ...

template <typename T, int N> class TinyVector {
public:
  TinyVector() = default;
  TinyVector(const TinyVector<T, N> &v) {
    is_trivially_copyable_t<T> select;
    internal_copy(v, select);
  }
  TinyVector &operator=(const TinyVector<T, N> &that) {
    if (this != &that) {
      is_trivially_copyable_t<T> select;
      internal_copy(that, select);
    }
    return *this;
  }

private:
  void internal_copy(const TinyVector<T, N> &v, bool_<true> const &) {
    std::cout << "Use fast memory copy" << std::endl;
    ::memcpy(m_data, v.m_data, N * sizeof(T));
  }
  void internal_copy(const TinyVector<T, N> &v, bool_<false> const &) {
    std::cout << "Use copy constructor" << std::endl;
    for (int i = 0; i < N; ++i)
      m_data[i] = v.m_data[i];
  }

private:
  T m_data[N];
};

/**************** use objects ****************/

struct BasicStruct {
  int a;
  double b;
};

class ComplexObject {
public:
  ComplexObject() = default;
  ComplexObject(const ComplexObject &o) : m_a(o.m_a), m_b(o.m_b) {}
  ComplexObject &operator=(const ComplexObject &that) {
    if (this != &that) {
      m_a = that.m_a;
      m_b = that.m_b;
    }
    return *this;
  }

private:
  int m_a;
  double m_b;
};

/****************** main ****************/

int main() {
  std::cout << "Building TinyVector<int,4> :\n";
  TinyVector<int, 4> v1;
  v1 = TinyVector<int, 4>();
  std::cout << "Building TinyVector<BasicStruct,4>:\n";
  TinyVector<BasicStruct, 4> v2;
  v2 = TinyVector<BasicStruct, 4>();
  std::cout << "Building TinyVector<ComplexObject,4>:\n";
  TinyVector<ComplexObject, 4> v3;
  v3 = TinyVector<ComplexObject, 4>();
}