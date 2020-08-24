enum class Suit { Heart, Spade, Diamond, Club };

//#region [Declarations]
#include <cassert>
#include <iostream>
#include <random>

static struct {
  std::random_device random_device;
  std::default_random_engine eng{random_device()};
  std::uniform_int_distribution<> dist{0, 3};
  Suit operator()() { return static_cast<Suit>(dist(eng)); }
} roll;

static struct Init {
  Init() { puts("---------------------"); }
} init;
//#endregion

int main() {

  switch (Suit suit = roll(); // initialization embedded in switch
          suit) { // warning: enumeration value 'Diamond' not handled in switch
  case Suit::Heart:
    // int n = 1;   // note:   crosses initialization of 'int n'
  case Suit::Spade: // error: jump to case label
    // merged cases since not break before (within Suit::Heart)
    puts("You win a teddy bear or a cup cake");
    break;
  // case Suit::Diamond: // error: duplicate case value 'Diamond'
  //   puts("You win a socket");
  case Suit::Club: {
    int n = 2;
    std::cout << "You win " << n << " sockets\n";
  } break;
    // case Suit::Diamond: // missing case detected by compiler
    //  puts("You win a socket");
    //  break;
  }

  // TODO: is there any bug in the following switch ?
  int x = 0;
  const char *message = nullptr;
  switch (x & 1) { // (x & 1) is easier
  case 0:
    message = "is an even number";
  case 1:
    message = "is an odd number";
  }
  assert(message != nullptr);
  std::cout << x << " " << message << '\n';
}