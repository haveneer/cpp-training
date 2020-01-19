#include <iostream>

int main() {
  const char *input = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---"
                      ".+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
  char memory[30000] = {};

  const char *iptr = input;
  char *mptr = memory;

  while (*iptr) {
//    std::cout << "BEFORE at " << (iptr - input) << " on " << *iptr << " : ["
//              << (mptr - memory) << "] = " << int(*mptr) << "\n";
    switch (*iptr) {
    case '>':
      mptr++;
      break;
    case '<':
      mptr--;
      break;
    case '+':
      (*mptr)++;
      break;
    case '-':
      (*mptr)--;
      break;
    case '.':
      std::cout << (*mptr);
      break;
    case ',':
      std::cerr << "Input instruction not implemented\n";
      exit(1);
    case '[':
      if (*mptr == 0) {
        int c = 0;
        while (*iptr) {
          if (*iptr == '[')
            ++c;
          else if (*iptr == ']')
            --c;
          if (c == 0)
            break;
          iptr--;
        }
      }
      break;
    case ']':
      if (*mptr != 0) {
        int c = 0;
        while (input <= iptr) {
          if (*iptr == '[')
            ++c;
          else if (*iptr == ']')
            --c;
          if (c == 0)
            break;
          iptr--;
        }
      }
      break;
    default:
      std::cerr << "Undefined instruction '" << *iptr << "'\n";
      exit(1);
    }
//    std::cout << "AFTER  at " << (iptr - input) << " on " << *iptr << " : [" << (mptr - memory)
//              << "] = " << int(*mptr) << "\n";
    if (*iptr)
      ++iptr;
  }
  std::cout << "\n[End]\n";
}