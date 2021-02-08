//#region [Declarations]
#include <iostream>
//#endregion

int main() {
  //#region [Unscoped enum]
  enum Color { Blue, Green, Red };
  enum Fruit { Berry, Avocado, Apple };

  Color color = Blue; // NOTA: Blue value has no prefix !
  std::cout << "color is " << color << '\n';
  // color = 2; // even if it is encoded on a integral type
  //            // you cannot assign an integer to it

  Fruit fruit = Berry;
  if (fruit == color) { // a warning but it compiles and runs
    std::cout << "fruit and color are equal\n";
  } else {
    std::cout << "fruit and color are not equal\n";
  }
  //#endregion

  //#region [Scoped enum]
  std::cout << "---------\n";
  enum class Suit { Heart, Spade, Diamond, Club };
  Suit suit = Suit::Heart; // NOTA: with a scope prefix !

  // C++14: you also can define the underlying integral type (to optimize allocation)
  enum class Value : unsigned char { Figure, Number };
  Value value = Value::Figure;

  // error: invalid operands to binary expression
  // std::cout << "suit is " << suit << '\n';

  // error: invalid operands to binary expression ('Suit' and 'Value')
  // (suit == value);

  // with an explicit cast, it could be ok: do it carefully
  std::cout << "suit is " << static_cast<int>(suit) << '\n';

  std::cout << "sizeof(Suit)=" << sizeof(Suit) << "\n";
  std::cout << "sizeof(Value)=" << sizeof(Value) << "\n";
  //#endregion
}