// cf https://stackoverflow.com/questions/59035103/is-this-an-old-c-style-constructor
struct T {
  T() {}
  T(int i) {}
};

int main() {
  int i = 42;
  // #1 : new T named t using int ctor
  { T t(i); }
  // #2 : new T named t using int ctor
  { T t = T(i); }
  // #3 : /!\ new T named i using default ctor
  { T(i); }
  // #4 : new T using int ctor (unnamed result)
  { T{i}; }
  // #5 : new T using int ctor (unnamed result)
  { T(2); }
}