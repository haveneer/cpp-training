/***********************************************************************
 * rvalues.cc : an example of usage for temporary object copy avoiding *
 * This version uses r-values and move operator from C++11             *
 *                                                                     *
 * Author : Pascal Havé                                                *
 * This example is a part of the lecture 'C++ Express' given for       *
 * CEMRACS 2012 (http://smai.emath.fr/cemracs/cemracs12)               *
 ***********************************************************************/

#include <iostream>
#include <string>

static const int N = 10;

class MyVector {
public:
  static int m_alloc_count, m_copy_count;

public:
  MyVector(int val, const std::string name)
      : m_data(new int[N]), m_name(name), m_moved(0) {
    ++m_alloc_count;
    std::cout << "New Vector " << m_name << "\n";
    for (int i = 0; i < N; ++i)
      m_data[i] = val;
  }
  virtual ~MyVector() {
    std::cout << "Delete Vector " << m_name << " moved=" << m_moved << "\n";
    delete[] m_data, m_data = nullptr;
  }
  int size() const { return N; }

public:
  MyVector(const MyVector &v) : m_data(new int[N]), m_moved(0) {
    ++m_alloc_count;
    ++m_copy_count;
    m_name = "copy(" + v.m_name + ")";
    std::cout << "Copy Vector " << v.m_name << " in " << m_name << "\n";
    for (int i = 0; i < N; ++i)
      m_data[i] = v.m_data[i];
  }
  MyVector &operator=(const MyVector &v) {
    if (this != &v) {
      ++m_copy_count;
      std::string new_name = "copy(" + v.m_name + ")";
      std::cout << "Copy Vector " << v.m_name << " in " << m_name << " and becomes "
                << new_name << "\n";
      m_name = new_name;
      for (int i = 0; i < N; ++i)
        m_data[i] = v.m_data[i];
    } else {
      std::cout << "Auto copy of " << m_name << "\n";
    }
    return *this;
  }
  MyVector(MyVector &&v) : m_moved(0) {
    m_name = "move(" + v.m_name + ")";
    std::cout << "Move Vector " << v.m_name << " in " << m_name << "\n";
    m_data = v.m_data;
    v.m_data = nullptr;
    m_moved += v.m_moved;
    v.m_moved = 0;
  }
  MyVector &operator=(MyVector &&v) {
    if (this != &v) {
      std::string new_name = "move(" + v.m_name + ")";
      std::cout << "Move Vector " << v.m_name << " in " << m_name << " and becomes "
                << new_name << "\n";
      delete[] m_data;
      m_data = v.m_data;
      v.m_data = nullptr;
      m_moved += v.m_moved;
      v.m_moved = 0;
    } else {
      std::cout << "Auto move of " << m_name << "\n";
    }
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &o, const MyVector &v) {
    o << "( ";
    for (int i = 0; i < N; ++i)
      o << v.m_data[i] << " ";
    o << ")";
    return o;
  }

private:
public:
  int *m_data;
  std::string m_name;
  int m_moved;
};

int MyVector::m_alloc_count = 0;
int MyVector::m_copy_count = 0;

MyVector operator+(const MyVector &a, const MyVector &b) {
  MyVector r(0, "rto((" + a.m_name + ")+(" + b.m_name + "))"); // RTO
  // std::cout << "Add1 Vector " << a.m_name << " with " << b.m_name << " in " <<
  // r.m_name << "\n";
  for (int i = 0; i < N; ++i)
    r.m_data[i] = a.m_data[i] + b.m_data[i];
  return r;
}

MyVector &&operator+(MyVector &&a, const MyVector &b) {
  std::cout << "Add2 Vector " << a.m_name << " with " << b.m_name
            << " inplace first\n";
  a.m_moved++;
  for (int i = 0; i < N; ++i)
    a.m_data[i] += b.m_data[i];
  return std::move(a);
}

MyVector &&operator+(const MyVector &a, MyVector &&b) {
  std::cout << "Add3 Vector " << a.m_name << " with " << b.m_name
            << " inplace second\n";
  for (int i = 0; i < N; ++i)
    b.m_data[i] += a.m_data[i];
  b.m_moved++;
  return std::move(b);
}

MyVector &&operator+(MyVector &&a, MyVector &&b) {
  std::cout << "Add4 Vector " << a.m_name << " with " << b.m_name
            << " inplace second\n";
  for (int i = 0; i < N; ++i)
    b.m_data[i] += a.m_data[i];
  b.m_moved++;
  return std::move(b);
}

int main() {
  MyVector a(1, "a"), b(2, "b"), c(3, "c"), d(4, "d");
  std::cout << "--------\n";
  MyVector::m_copy_count = 0;
  MyVector::m_alloc_count = 0;
  c = (a + (b + b));
  std::cout << "Copy count = " << MyVector::m_copy_count << "\n";
  std::cout << "Allocation count = " << MyVector::m_alloc_count << "\n";
  // std::cout << "c = " << c << "\n";
  std::cout << "--------\n";
  MyVector::m_copy_count = 0;
  MyVector::m_alloc_count = 0;
  d = MyVector(3, "tmp3") + MyVector(5, "tmp5");
  std::cout << "Copy count = " << MyVector::m_copy_count << "\n";
  std::cout << "Allocation count = " << MyVector::m_alloc_count << "\n";
  // std::cout << "d = " << d << "\n";
  std::cout << "--------\n";
  return 0;
}