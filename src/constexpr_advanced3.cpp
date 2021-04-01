constexpr unsigned pgcd(unsigned a, unsigned b) {
  if (a < b)
    return pgcd(b, a);
  while (b > 0) {
    auto r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main() {
  static_assert(pgcd(21, 15) == 3);
  static_assert(pgcd(70, 40) == 10);
}