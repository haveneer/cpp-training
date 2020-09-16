//#region [Collapse all]
int main() {
  int i = 0, j = 10;
  if ((j > 0) && (i = 10)) { // conditional side-effect
    return 0;
  } else {
    return 1;
  }
}
//#endregion