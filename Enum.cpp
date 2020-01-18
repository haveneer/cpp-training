//#region [Declarations]
#include <iostream>
//#endregion


int main() {
  //#region [Unscoped enum]
  enum Color { Blue, Green, Red };

  Color color = Blue; // NOTA: Blue value has no prefix !
  std::cout << "color is " << color << '\n';
  // color = 2; // even if it is encoded on a integral type
  //            // you cannot assign an integer to it

  //#endregion

  //#region [Scoped enum]
  enum class Suit { Heart, Spade, Diamond, Club };
  Suit suit = Suit::Diamond; // NOTA: with a scope prefix !

  // error: invalid operands to binary expression
  // std::cout << "suit is " << suit << '\n';

  // with an explicit cast, it could be ok: do it carefully
  std::cout << "suit is " << static_cast<int>(suit) << '\n';
  //#endregion
}
