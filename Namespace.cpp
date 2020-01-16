//#region [Declarations]
#include <iostream>
//#endregion

// global scope is equivalent to namespace ::
int global_object = 0;
int global_object2 = 1;

namespace N1 {
int global_n1_object = 2;

namespace N2 { // nested namespace (in N1)
int global_n1_n2_object = 3;
}
} // namespace N1

namespace N3 {
int global_n3_object = 4;
}

namespace N4 {
int global_n4_object = 5;
int global_object2 = 6; // no conflict; same id as global (::) scope
} // namespace N4

namespace N1::N2 { // compact style with C++17
// int global_n1_n2_object = 7; // already in same scope/namespace
int global_n1_n2_object2 = 8; // new object in same N1::N2 namespace
using namespace N3; // use everything from N3 in current N1::N2 namespace
} // namespace N1::N2

using namespace N4; // all content from N4 is now available in global scope

int main() {
  int global_n1_n2_object2 = 9; // new object; does not shadow anything

  using namespace N1::N2;   // use everything from a given N1::N2 namespace
  global_n1_n2_object = 10; // object from N1::N2 namespace
  // local global_n1_n2_object2 (=9) has been shadowed by using namespace N1::N2

  using N1::global_n1_object; // use only one entity from given N1 namespace
  global_n1_object = 11;

  // following objects shadow existing previously defined objects
  double global_object = 3.14;
  double global_n1_n2_object = 2.72;

  // clang-format off
  std::cout << global_n1_object << "\n"; // local shadowing object
  std::cout << global_n3_object << "\n"; // inherited from using N3 in N1::N2
  std::cout << global_n1_n2_object << "\n";         // local shadowing object
  std::cout << N1::N2::global_n1_n2_object << "\n"; // original object
  std::cout << global_n1_n2_object2 << "\n";        // original object (shadowing local object)
  std::cout << global_object << "\n";      // local shadowing object
  std::cout << ::global_object << "\n";    // original global object
  // std::cout << global_object2 << "\n";  // ERROR: global_object2 is ambiguous
  std::cout << ::global_object2 << "\n";   // specify the one from global scope
  std::cout << N4::global_object2 << "\n"; // specify the one from N4 namespace
  std::cout << ::global_n4_object << "\n"; // from using N4 in global scope
  // clang-format on
}