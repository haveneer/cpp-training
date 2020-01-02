int main() {
  bool b1; // quelle valeur ? /!\ A éviter (cf RAII)

  // Initialisation avec les littéraux standards (true|false)
  bool b2 = true;   // copy initialization
  bool b3 ( true ); // constructor initialization
  bool b4 { true }; // uniform initialization (C++≥11)

  // avec conversion de littéraux (0 => false, ≠0 => true)
  bool b5_0 = 0; // false
  bool b5_1 = 1; // true
  bool b5_2 = 2; // true

  bool b6_0(0); // false
  bool b6_1(1); // true
  bool b6_2(2); // true

  // avec initialisation uniforme (conversion contrôlée)
  bool b7_0{0}; // false
  bool b7_1{1}; // true
  // bool b7_2{2}; // ERROR
}