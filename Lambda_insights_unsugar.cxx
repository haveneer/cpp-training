/* ------------------------------------------- */

// This is fp internals
class __lambda_9_26 {
public:
  inline /*constexpr */ int operator()(int a, char b) const {
    return a + static_cast<int>(b);
  }

  using retType_9_26 = int (*)(int, char);
  inline /*constexpr */ operator retType_9_26() const noexcept {
    return __invoke;
  }

private:
  static inline int __invoke(int a, char b) { return a + static_cast<int>(b); }

} __lambda_9_26{};

using FuncPtr_9 = int (*)(int, char);
FuncPtr_9 fp = static_cast<int (*)(int, char)>(
    __lambda_9_26.operator __lambda_9_26::retType_9_26());
(*fp)(1, 2);

/* ------------------------------------------- */

// This is f3 internals
class __lambda_15_13 {
public:
  inline /*constexpr */ int operator()(int a, char b) const {
    return (a + static_cast<int>(b)) + data;
  }

private:
  int data;

public:
  __lambda_15_13(int _data) : data{_data} {}
};

__lambda_15_13 f3 = __lambda_15_13{data};
f3.operator()(1, 2);

/* ------------------------------------------- */

// This is f4 internals
class __lambda_18_13 {
public:
  template <class type_parameter_0_0, class type_parameter_0_1>
  inline /*constexpr */ auto operator()(type_parameter_0_0 a,
                                        type_parameter_0_1 b) const {
    return (a + b) + data;
  }

  template <> inline /*constexpr */ int operator()(int a, int b) const {
    return (a + b) + data;
  }

private:
  int data;

public:
  __lambda_18_13(int _data) : data{_data} {}
};

__lambda_18_13 f4 = __lambda_18_13{data};
f4.operator()(1, 2);
