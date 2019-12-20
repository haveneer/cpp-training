#ifndef CPP_TRAINING_PREPROCESSING_SIMPLE_HPP
#define CPP_TRAINING_PREPROCESSING_SIMPLE_HPP
// Il est de votre responsabilité de choisir un "guard" non ambigü

// Définition d'une macro simple
#define RETURN_CODE 0

// Récupération de la version de C++ si disponible
#ifdef __cplusplus
#define VERSION __cplusplus
#else
#define VERSION "Undefined"
#endif

// Définition d'une macro plus élaborée
#define DATETIME __DATE__ " - " __TIME__

// Définition de macros de type fonction
#define OUTPUT1(a) std::cout << DATETIME << ": " << a << '\n'
#define STR(X) #X // Transformation en string de X
#define OUTPUT2(a) std::cout << DATETIME << ": " << STR(a) << '\n'

// On crée même du code
#define FUNCTION(name, value) int function_##name() { return value; }

#endif /* CPP_TRAINING_PREPROCESSING_SIMPLE_HPP */
