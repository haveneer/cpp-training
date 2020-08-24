//#region [Declarations]
#include <iostream>
#include <cstdio>
// Ascii art table
// ┌──┬──┐
// │  │  │
// ├──┼──┤
// │  │  │
// └──┴──┘

//#endregion

int main() {
  int roll = 3;                   // technically, this is done using jumps
  switch (roll) {                 // ──────┐
  case 1:                         //   x───┤ roll != 1; not evaluated
    puts("You win a teddy bear"); //       |
    break;                        //       |
  case 2:                         //   x───┤ roll != 2; not evaluated
    puts("You win a cup cake");   //       |
    break;                        //       |
  case 3:                         // o <───┘ roll == 3; evaluate it !
    puts("You win a socket");     // |
    break;                        // └─────────────────────────────────┐
  case 4:                         //         bypassed; not evaluated   | 
    puts("You win a meal");       //                                   |
    break;                        //                                   |
  default:                        //         bypassed; not evaluated   |
    puts("You win nothing");      //                                   |
    break;                        //                                   |
  }                               //                                   |
  // after switch                 // <─────────────────────────────────┘
}