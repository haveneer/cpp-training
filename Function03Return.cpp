//#region [Declarations]
#include <iostream>
//#endregion

int global_object = 0;

int get_global() { return global_object; }

// Useless const qualifier on return type
const int simple_return() { return 4; }

// const pointed value return
const int *pointer_return() { return &global_object; }

// Reference value return
int &reference_return() { return global_object; }

// TODO: Why this function has a bug ??
int buggy_function() {
  if (global_object > 0)
    return 1;
  /*
  // Is it better with this ?
  else
    return;
  */
}

int main() {
  std::cout << simple_return() << '\n';

  auto x = pointer_return();
  std::cout << *x << '\n';

  auto y = reference_return();
  y += 1;
  // TODO: what is the display of the following lines ?
  std::cout << y << " vs " << global_object << '\n';
  std::cout << buggy_function() << '\n';
}
