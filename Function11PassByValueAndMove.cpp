//#region [Declarations]
#include <array>
#include <iostream>
#include <vector>
#define BIG_NUMBER 1000
//#endregion

struct BigStruct {
  //#region [MONITORING]
  BigStruct() : value{0} {}
  BigStruct(const BigStruct &that) : value{that.value}, tab{that.tab} {
    std::cout << "COPY ";
  }
  BigStruct(BigStruct &&that)
      : value{std::move(that.value)}, tab{std::move(that.tab)} {
    std::cout << "MOVE ";
  }
  //#endregion

  int value;
  std::vector<int> tab; // unknown size, could be large
  // std::array<int, BIG_NUMBER> tab; // trivially copiable; std::move has no effect on it
};

// clang-format off
void f_by_value(BigStruct x)            { BigStruct local_x = x;            local_x.value += 1; std::cout << '\n'; }
void f_by_const_ref(const BigStruct &x) { BigStruct local_x = x;            local_x.value += 1; std::cout << '\n'; }
void f_by_value_and_move(BigStruct x)   { BigStruct local_x = std::move(x); local_x.value += 1; std::cout << '\n'; }
// clang-format on

int main() {
  BigStruct a{};

  f_by_value(a);                    // 2 COPIES
  f_by_value(BigStruct{});          // 1 COPY
  f_by_const_ref(a);                // 1 COPY
  f_by_const_ref(BigStruct{});      // 1 COPY
  f_by_value_and_move(a);           // 1 COPY
  f_by_value_and_move(BigStruct{}); // ZERO COPY
}
