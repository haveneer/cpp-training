//#region [Collapse all]
int main() {
  // pointer to const int:
  const int *pci = new int{2};

  // pointer to int:
  int *pi = nullptr;

  /* ... */

  // constraint error
  // pi = pci; // error: assigning to 'int *' from incompatible type 'const int *'

  // dangerous but permitted
  pi = (int *)pci; // or const_cast<int*>(pci);
  *pi = 0;
}
//#endregion