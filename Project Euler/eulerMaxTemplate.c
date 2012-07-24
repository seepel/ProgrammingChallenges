#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int max = 1000;
  if(argc > 1) {
    max = atoi(argv[1]);
  }
  return 0;
}
