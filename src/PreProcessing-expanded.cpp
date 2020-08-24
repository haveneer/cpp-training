// Standard system include
#include <iostream>

// First time (user headers)
//#region [#include PreProcessing-advanced.hpp]
/* PreProcessing-advanced.hpp */

// Advanced include guard
// Portability cf https://en.wikipedia.org/wiki/Pragma_once#Portability
#pragma once

// more portable than #warning (cf MSVC)
#pragma message("Pre-processing " __FILE__)

// Don't reformat !
// clang-format off

// Check if __has_include feature is available
#ifdef __has_include
#  if __has_include(<optional>)
#    include <optional>
#    define HAS_OPTIONAL 1 // define a macro with a value
#  elif __has_include(<experimental/optional>)
#    include <experimental/optional>
#    define HAS_OPTIONAL 1
#    define EXPERIMENTAL_OPTIONAL // macro with no value
#  else
#     // or a #error "std::optional is missing"
#     pragma message ( "std::optional is not available" )
#     define HAS_OPTIONAL 0
#  endif
#endif

// clang-format on
//#endregion

//#region [#include PreProcessing-simple.hpp]
/* PreProcessing-simple.hpp */

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
//#endregion

// Second time ? (already done)
// #include "PreProcessing-advanced.hpp"
// #include "PreProcessing-simple.hpp"

// Utilisation de macros définies ci-dessus
FUNCTION(one, 1);
FUNCTION(two, 2);

int main() {
  OUTPUT1("Running " __FILE__);
  OUTPUT1("Hello, world!");
  std::cout << DATETIME << ": C++ version : " << VERSION << std::endl;
#if !defined(EXPERIMENTAL_OPTIONAL)
  std::cout << DATETIME << ": Has experimental std::optional" << std::endl;
#else
  std::cout << DATETIME << ": Has std::optional : " << HAS_OPTIONAL << std::endl;
#endif
  OUTPUT1(function_one());
  OUTPUT2(function_two());

  OUTPUT2(Bye bye);
  return RETURN_CODE;
}