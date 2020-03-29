//#region [Declarations]
#include <iostream>
//#endregion

// global scope is equivalent to namespace ::
int object = 0;
int object2 = 1;

namespace N1 {
int n1_object = 2;

namespace N2 { // nested namespace (in N1)
int n1_n2_object = 3;
}
} // namespace N1

namespace N3 {
int n3_object = 4;
}

namespace N4 {
int n4_object = 5;
int object2 = 6; // no conflict; same id as global (::) scope
} // namespace N4

namespace N1::N2 { // compact style with C++17
// int n1_n2_object = 7; // already in same scope/namespace
int n1_n2_object2 = 8; // new object in same N1::N2 namespace
using namespace N3;    // use everything from N3 in current N1::N2 namespace
} // namespace N1::N2

using namespace N4; // all content from N4 is now available in global scope

int main() {
  int n1_n2_object2 = 9; // new object; does not shadow anything

  using namespace N1::N2; // use everything from a given N1::N2 namespace
  n1_n2_object = 10;      // object from N1::N2 namespace
  // local n1_n2_object2 (=9) has been shadowed by using namespace N1::N2

  using N1::n1_object; // use only one entity from given N1 namespace
  n1_object = 11;

  // following objects shadow existing previously defined objects
  double object = 3.14;
  double n1_n2_object = 2.72;

  std::cout << n1_object << "\n";            // local shadowing object
  std::cout << n3_object << "\n";            // inherited from using N3 in N1::N2
  std::cout << n1_n2_object << "\n";         // local shadowing object
  std::cout << N1::N2::n1_n2_object << "\n"; // original object
  std::cout << n1_n2_object2 << "\n";        // original object (shadowing local obj)
  std::cout << object << "\n";               // local shadowing object
  std::cout << ::object << "\n";             // original global object
  // std::cout << object2 << "\n";  // error: object2 is ambiguous
  std::cout << ::object2 << "\n";   // specify the one from global scope
  std::cout << N4::object2 << "\n"; // specify the one from N4 namespace
  std::cout << ::n4_object << "\n"; // from using N4 in global scope
}