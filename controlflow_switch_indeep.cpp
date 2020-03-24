//#region [Expand to get full code]
// https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAM1QDsCBlZAQwBtMQBGAFlICsupVs1qhkAUgBMAISnTSAZ0ztkBPHUqZa6AMKpWAVwC2tEJNJb0AGTy1MAOWMAjTMTMBWUgAdUCwuto9QxMzb19/Ohs7RyMXN0lPJRU1OgYCZmICIONTcyTMVQC0jIIoh2dXD0V0zOyQvJrS23LYyoSASkVUA2JkDgByWwIAaipOCHbh8QB2aWHiTAIe2mHOcQBmOZmAEXEABgBBIdHJCanZ%2BcXl4ckNrendw%2BOqdbOZuYWl4hX1u/PHg77I70YZGZi2CDHDLAZCkYbIBAZYYAKmR0IAbpN3kDhsNjsQ7kCccMAPQk%2BHCUQAWhoxDBI1QVCoxIUAHdCAjhhBocgsbNiSwlDcQPMNtsxhM/k4FswANaEw64wWYYbrEUE9bi07tKUy%2BWbAXMIXudViqja3WYOUKg5Ko0qgBsps1Ep1m2G0qt%2Btkivh9tWe04zq1kvdnutBt9ypue0kwddlojPttfqF6z2atFLotYb1NrtQu4e248fGbrm4e9huNexNWZD5Y9ecjKejDr2TvrCdzXvzwywVGYBlYBHjr3LxJ2xLJFJEwBpJHpwzoRN9n2uGuTO36nVYIH67n6pFM/T2R9Q%2B50cjkwwU3V6Kqk604R9Hp53nVlIAdkgAdA7n04TgAA5QKAkDgIATiEfduCPE8z1IC9%2BiPBQQD2Ug3zPTo4FgJA0CMLw8HYMgKAgAiiJIlBKWASC9gwqhiIIVw0IgJx90QpxbAyABPfcX1IAijC0AgAHlaFYPj31ILAwVEdgOKPfAFkKdFMDQ6TMAADwKAxmP4o8hmURShDwaVeL0LADMw4g8CMRTOhoegmDYDgeH4QQaJQa8ZFMpw0MgTpUC8FJaA0qkFAIdAxQkGQ5E4aZhipUT1lQ5QClCzRtDqUxOAsbQyhiOJBB8PxQpykrwlCwqKjcPL8kKVJGgq%2Br0sa2hikyGrWjq6oShavquuaIrKk4To7x6PouF3fdD2PEzkK04CHSpB1uFnURhkg389h2rlcEIEgpkkZ84T0QjiNcY7n0mK84pkV8HM6BArSwNwJlIL91mmX91gdUDgPAgHwJg/o4NIezOHo%2BbpOQ1D0Mwp7QckeCFv3R733aTo1OIPwNG4IA%3D%3D
#include <iostream>

int f1() { return 1; }
int f2() { return 2; }
int f3() { return 3; }

int main(int argc, char **argv) {
  int r;

  // clang-format off
  switch (argc) {
  case 2: r=f1(); break;
  case 3: r=f2(); break;
  case 5: r=f2(); break;
  case 6: r=f1(); break;
  case 101: r=f2(); break;
  case 202: r=f1(); break;
  case 303: r=f2(); break;
  case 404: r=f1(); break;
  case 505: r=f2(); break;
  case 606: r=f1(); break;
  default: r=f3();
  }
  // clang-format on

  std::cout << "r = " << r << '\n';
  return 0;
}
//#endregion