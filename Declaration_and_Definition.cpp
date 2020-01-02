int alpha; // declare and define variable `alpha` with type `int`;
extern double beta; // only declare variable `beta` with type `double`

typedef double Number; // declare type `Integer` (old style)
using Number = double; // (same) declare type `Integer` (new style)

extern Number beta; // (same) only declare variable `beta` with type `Number`

int f(Number x, int n); // declare function (Number,int)->int (old style)
int f(Number, int); // (same) declare function (old style) : parameter names are not mandatory

int f(Number /* no_name */, int n) { // declare and define function `f`
  Number y; // declare and define variable `y` (value not specified)
  int m = n; // declare and define variable `m` (with value `x`)
  return m%2;
}

struct Point; // declare structure type `Point`

void g(Point p); // declare function `g` using not defined (only declared) type p
// void g(Point p) { } // Cannot define function `h` since p is not fully defined

void h(Point * p) { } // Well defined; why ?

struct Point {
  Number x,y,z;
  int tag;
};

int main() {
  f(1.0, 2);
}