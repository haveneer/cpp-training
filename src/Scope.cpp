//#region [Declarations]
#include <iostream>

#ifdef DEBUG_TYPE
#include "type.hpp" // advanced type printing
#else // clang-format off
#include <typeinfo>
template <typename T> std::string type() { if (std::is_same_v<std::remove_extent_t<std::remove_const_t< std::remove_pointer_t<std::remove_reference_t<T>>>>, T>) return typeid(T).name(); else if (std::is_array_v<T>) return type<std::remove_extent_t<T>>() + "[]"; else if (std::is_const_v<T>) return type<std::remove_const_t<T>>() + " const"; else if (std::is_pointer_v<T>) return type<std::remove_pointer_t<T>>() + "*"; else if (std::is_reference_v<T>) return type<std::remove_reference_t<T>>() + ((std::is_lvalue_reference_v<T>) ? "&" : "") + ((std::is_rvalue_reference_v<T>) ? "&&" : ""); else std::string("cannot decode ") + typeid(T).name(); }
#endif              // clang-format on
//#endregion

using global_type = int;

int global_object = 0;

// Functions declaration/definition are only allowed in global scope
int global_function() {
  int local_object_in_global_function = 1;
  return local_object_in_global_function;
}

// local_object_in_global_function is not available here

int main() {
  using local_main_type = double;
  int local_main_object = 2;
  {
    using local_nested_main_type = char;
    int local_nested_main_object = 3;
    {
      using local_nested_nested_main_type = long;
      int local_nested_nested_main_object = 4;
      // double local_nested_nested_main_object = 4.5; // error: identifier redefinition

      // all global_* and local_* are available here

      local_nested_nested_main_object = global_object + 4;
    }

    // all local_nested_nested_* are no more available

    if (true) {
      int local_statement_nested_main_object = 5;

      int local_nested_nested_main_object = 6; // new object; no shadow

      // following objects shadow existing previously defined objects
      // they are no more available
      int global_type = 666; // this variable shadow a type
      int global_object = 666;
      int local_main_object = 666;
      int local_nested_main_object = 666;
    }
  }

  // all local_nested_* are no more available; global_* local_main_* are available again
  //#region [TODO: what are the values of visible entities ?]
  std::cout << type<global_type>() << "\n";
  std::cout << global_object << "\n";
  std::cout << type< decltype(global_function)>() << "\n";
  std::cout << type<local_main_type>() << "\n";
  std::cout << local_main_object << "\n";
  //#endregion

  // Examples with implicit block in statements
  if (bool local_statement_object1 = true; local_statement_object1)
    int local_statement_object2 = 6; // in same scope than local_statement_object1

  for (int local_statement_object3 = false; local_statement_object3;)
    using local_statement_type = bool; // in same scope than local_statement_object3
}

// global_* are still available here