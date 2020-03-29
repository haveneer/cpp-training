template <typename T> struct LazyError {
  static T error(const T &t) { return t.error(); }
};

int main() {
  LazyError<int> bug;
  // bug.error(1); // error: member reference base type 'const int' is not a structure or union
}