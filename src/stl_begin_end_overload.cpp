//#region [Collapse all]
#include <iostream>
#include <random>
//#endregion

struct RandomGenerator {
  std::random_device random_device;
  mutable std::default_random_engine eng{random_device()};
  mutable std::uniform_int_distribution<> dist{0, 1000};
  int operator()() const { return dist(eng); }
};

struct Sequence {
  RandomGenerator generator;
  int count;
};

struct Iterator {
  int position;
  const Sequence &sequence;

  int operator*() const { return sequence.generator(); }
  void operator++() { ++position; }
  bool operator!=(const Iterator &other) { return this->position != other.position; }
};

Iterator begin(const Sequence &s) { return {0, s}; }
Iterator end(const Sequence &s) { return {s.count, s}; }

int main() {
  for (auto x : Sequence{RandomGenerator(), 10}) {
    std::cout << x << " ";
  }
  std::cout << '\n';
}