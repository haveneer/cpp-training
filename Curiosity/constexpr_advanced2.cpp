constexpr bool test_constexpr(bool make_constexpr) {
  return make_constexpr ? true : throw 0;
}

// Use SFINAE to find the 'best' matching function
// If the third template arg can be computed, this one is the 'best' match
// could be template <typename F, F & f, auto... Args, auto = f(Args...)>
template <auto &F, auto... Args, auto = F(Args...)>
constexpr bool is_constexpr(int) {
  return true;
}

// else SFINAE will try this one, always ok but a lesser priority (cf ... arg)
template <auto &F, auto... Args> constexpr bool is_constexpr(...) { return false; }

// This function is constexpr if it be can evaluated
constexpr auto is_even = [](int n) { return (n % 2 == 0) ? true : throw 0; };

int main() {
  // static_assert(is_constexpr<is_even, 3>(0), "is_even(3) is not constexpr");
  static_assert(is_constexpr<is_even, 2>(0), "is_even(2) is not constexpr");
}