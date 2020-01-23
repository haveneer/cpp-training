// from
// https://stackoverflow.com/questions/33693486/how-can-i-use-cmake-to-test-processes-that-are-expected-to-fail-with-an-exceptio

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
  pid_t pid = fork();
  if (pid == -1) {
    // fork fails
    return 1;
  } else if (pid) {
    // Parent - wait child and interpret its result
    int status = 0;
    wait(&status);
    if (WIFSIGNALED(status))
      return 0; // Signal-terminated means success
    else
      return 1;
  } else {
    // Child - execute wrapped command
    execvp(argv[1], argv + 1);
    exit(1); // reached only if execvp fails
  }
}