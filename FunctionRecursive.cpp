//#region [Declaration]
#include <chrono>
#include <iostream>
//#endregion

// TODO Écrivez une implémentation récursive de la suite de Fibonacci
auto rec_fib(unsigned n) {
  if (n < 2)
    return n;
  else
    return rec_fib(n - 1) + rec_fib(n - 2);
}

// TODO comment écrire cet algorithme sans payer le coût de la récursivité ?
//#region [Other versions]
namespace {
void tailrec_fib_acc(unsigned &fib2, const unsigned n, const unsigned fib0,
                     const unsigned fib1) {
  fib2 += fib0;
  if (n > 0)
    tailrec_fib_acc(fib2, n - 1, fib1, fib2);
}
} // namespace

auto tailrec_fib(unsigned n) {
  if (n < 2)
    return n;
  unsigned acc = 0;
  tailrec_fib_acc(acc, n, 0, 1);
  return acc;
}

auto norec_fib(unsigned n) {
  unsigned fib0 = 0, fib1 = 1;
  while (--n > 0) {
    unsigned fib2 = fib0 + fib1;
    fib0 = fib1;
    fib1 = fib2;
  }
  return fib1;
}
//#endregion

int main() {
  const unsigned n = 35;
  //#region [Computation and timers]
  const auto start = std::chrono::system_clock::now();
  const unsigned rec_fib_result = rec_fib(n);
  const auto rec_fib_end = std::chrono::system_clock::now();
  const unsigned tailrec_fib_result = tailrec_fib(n);
  const auto tailrec_fib_end = std::chrono::system_clock::now();
  const unsigned norec_fib_result = norec_fib(n);
  const auto norec_fib_end = std::chrono::system_clock::now();

  auto elapsed = [=](auto start, auto end) {
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start)
        .count();
  };
  //#endregion

  std::cout << "    rec_fib(" << n << ") = " << rec_fib_result << " in "
            << elapsed(start, rec_fib_end) << "_us\n";
  std::cout << "tailrec_fib(" << n << ") = " << tailrec_fib_result << " in "
            << elapsed(rec_fib_end, tailrec_fib_end) << "_us\n";
  std::cout << "  norec_fib(" << n << ") = " << norec_fib_result << " in "
            << elapsed(tailrec_fib_end, norec_fib_end) << "_us\n";
}