int main() {
  bool b1; // TODO: which value ? /!\ DON'T DO THAT (cf RAII)

  // Initialisation avec les littéraux standards (true|false)
  bool b2 = true;   // copy initialization
  bool b3 ( true ); // constructor initialization
  bool b4 { true }; // uniform initialization (C++≥11)

  // using conversion from litterals (0 => false, ≠0 => true)
  bool b5_0 = 0; // false
  bool b5_1 = 1; // true
  bool b5_2 = 2; // true

  bool b6_0(0); // false
  bool b6_1(1); // true
  bool b6_2(2); // true

  // using uniform initialisation (conversion with checks)
  bool b7_0{0}; // false
  bool b7_1{1}; // true
  // bool b7_2{2}; // ERROR
}