//#region [format]
int main() {
  int assign_now = 0;
  // clang-format off
//#endregion

      int       *        p1 ;               // pointeur modifiable et possibilité de modifier l'objet pointé
const int       *        p2 ;               // pointeur modifiable et impossibilité de modifier l'objet pointé
      int const *        p2b;               // identique à p2 (synonyme)
      int       * const  p3  = &assign_now; // pointeur non modifiable et possibilité de modifier l'objet pointé
const int       * const  p4  = &assign_now; // pointeur non modifiable et impossibilité de modifier l'objet pointé
      int const * const  p4b = &assign_now; // identique à p4 (synonyme)

      int       &        r1  =  assign_now; // référence avec possibilité de modifier l'objet pointé
const int       &        r2  =  assign_now; // référence avec impossibilité de modifier l'objet pointé
//    int       & const  r3;                // error: 'const' qualifiers cannot be applied to 'int&'
                                            // Cette forme n'existe pas
//#region [format]
  // clang-format on
}
//#endregion