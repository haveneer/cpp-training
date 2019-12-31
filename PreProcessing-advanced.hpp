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
