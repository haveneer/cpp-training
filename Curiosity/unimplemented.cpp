// https://godbolt.org/z/W6GPdGEhc

template <typename T, bool B = false> inline void error_unimplemented() {
  static_assert(B, "unimplemented instruction");
}

template <typename T> inline void foo(T f) { error_unimplemented<T>(); }

template <> inline void foo<float>(float f) {
  // implementation
}

int main() {
  foo(1.f);
  // foo("bar"); //assertion failure
}
