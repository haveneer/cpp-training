//#region [Declarations]
#include <iostream>
//#endregion

// Unscoped enum
enum Color {
  Blue,
  Green,
  Red
};

enum class Suit {
  Heart,
  Spade,
  Diamond,
  Club
};

int main() {
  Color color = Blue; // NOTA: Blue value has no prefix !
  std::cout << "color is " << color << '\n';
  // color = 2; // even if it is encoded on a integral type
  //            // you cannot assign an integer to it

  Suit suit = Suit::Diamond; // NOTA: with a scope prefix !

  // error: invalid operands to binary expression
  // std::cout << "suit is " << suit << '\n';

  // with an explicit cast, it could be ok: do it carefully
  std::cout << "suit is " << static_cast<int>(suit) << '\n';
}
