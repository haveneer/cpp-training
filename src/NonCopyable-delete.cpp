struct NonCopyable {
  NonCopyable() = default;
  virtual ~NonCopyable() = default;

  NonCopyable(const NonCopyable &) = delete;
  NonCopyable(NonCopyable &&) = delete;
  void operator=(const NonCopyable &) = delete;
  void operator=(NonCopyable &&) = delete;
};

class A : NonCopyable {
public:
  A() : m_data(new int[5]) {}
  ~A() { delete[] m_data; }

private:
  int *m_data; // default copy is not safe with pointer
};

// This should be compared to explicit ctor which avoids conversion
void call_with_true_double_only(float) = delete;
void call_with_true_double_only(double param) {}

int main() {
  A a, b;
  // A x{a}; // error: use of deleted function 'A::A(const A&)'
  // b = a; // error: use of deleted function 'A& A::operator=(const A&)'

  call_with_true_double_only(3.);
  // call_with_true_double_only(3.f); // error: use of deleted function 'void call_with_true_double_only(float)'
}