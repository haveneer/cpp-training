//#region [declarations]
#include <cstdlib>
#include <iostream>

// or from https://gitlab.inria.fr/jwintz/lecture-cpp/-/tree/master/Demo/5-FixByPragmas-common

#ifdef __clang__
#pragma clang diagnostic push // starts the code block in which rules are modified
#pragma clang diagnostic ignored "-Wsign-conversion"
#pragma clang diagnostic ignored "-Wold-style-cast"
#pragma clang diagnostic ignored "-Wparentheses"
#pragma clang diagnostic ignored "-Wcast-qual"
#pragma clang diagnostic ignored "-Wdeprecated"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wreserved-id-macro"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wundef"
#pragma clang diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma clang diagnostic ignored "-Wundefined-func-template"
#pragma clang diagnostic ignored "-Wc++98-compat"
#pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wnon-virtual-dtor"

// something to do

#pragma clang diagnostic pop // go back to normal rules

#elif !defined(__INTEL_COMPILER) and defined(__GNUG__) // __GNUG__ defined for gcc, clang and Intel compilers...

# pragma GCC diagnostic push // starts the code block in which rules are modified
# pragma GCC diagnostic ignored "-Wsign-conversion"

// something to do

#pragma GCC diagnostic pop // go back to normal rules 
#endif
//#endregion


int main() {

  //#region []
  //#endregion
}