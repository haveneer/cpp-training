int main() {
  // Without any const
  int a = 0;
  int &ra = a;
  ra = 1;

  // With a const object
  const int b = a;

  const int *pb = &b; // same as `int const * pb;`
  // int * pb2 = &b;  // error: invalid conversion from 'const int*' to 'int*'
  // *pb = 2;         // error: assignment of read-only location '* pb'
  pb = &a; // change reference object; still const even if source objet is not const
  // *pb = 2;         // error: assignment of read-only location '* pb'

  // int * const p0;  // error: uninitialized const 'p0'
  int * const pc = &a;
  *pc = 2;
  // pc = &a; // error: assignment of read-only variable 'pc'
  //          // cannot change the referenced object (even if it is the same :/)

  const int * const px = &a;
  const int * const py = &b;
  // Nothing can change: neither address nor value !

  const int &rb = b; // OK
  // int & rb2 = b;      // error: binding reference of type 'int&' to 'const int'
  //                     // discards qualifiers
  // rb = 2;             // error: assignment of read-only reference 'rb'
  // int & const rc = b; // error: 'const' qualifiers cannot be applied to 'int&'
}