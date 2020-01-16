//#region [Declaration]
#include <iostream>
//#endregion

int main(int argc, const char *argv[]) {
  std::cout << "Program name: " << argv[0] << '\n';
  if (argc > 1) {
    std::cout << "Program arguments: \n";
    for (int i = 1; i < argc; ++i) {
      std::cout << '\t' << argv[i] << '\n';
    }
  } else {
    std::cout << "No argument\n";
  }

  // return 0; // Par convention le retour 0 ou
  //           // l'absence de retour signifie que
  //           // l'exécution c'est bien déroulée
}