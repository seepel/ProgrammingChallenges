#include <stdio.h>

void printPrimes(int n) {
  int i;
  for(i=2; i*i <= n; i++) {
    if(n % i == 0)
      printf("%d ", i);
    while(n % i == 0) {
      n /= i;
    }
  }
  if(n > 1)
    printf("%d ", n);
  printf("\n");
}

int main(int argc, char **argv) {
    int max = 10;
  if(argc > 1) {
    max = atoi(argv[1]);
  }

  int i;
  for(i=2; i!=max; i++) {
    printf("%d: ", i);
    printPrimes(i);
  }
  return 0;
}
